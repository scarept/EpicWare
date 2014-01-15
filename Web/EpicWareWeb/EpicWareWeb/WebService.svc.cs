using EpicWareWeb.Controllers;
using EpicWareWeb.DAL;
using EpicWareWeb.Models;
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.Web.Http.ModelBinding;
using System.Web.Security;
using WebMatrix.WebData;

namespace EpicWareWeb
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "WebService" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select WebService.svc or WebService.svc.cs at the Solution Explorer and start debugging.
    public class WebService : IWebService
    {
        DataContext db = new DataContext();
        public int getNumberUsers()
        {
            DataContext db = new DataContext();
            return db.users.Count();            
        }

        public int getNumberDownloads()
        {
            DateTime now = DateTime.Now;
            DateTime later = DateTime.Now.AddHours(-1);
            
            int count = 0;
            foreach (Download d in db.downloads)
            {
                if (d.time > later && d.time < now)
                {
                    count++;
                }
            }
            return count;
        }

        public User getUserByID(int id, string user, string pass)
        {
            if(Membership.ValidateUser(user,pass)){
                return removeProxyUser(db.users.Find(id));
            }else{
                return null;
            }
            
        }

        public IList<int> getUserFriendsByUserId(int id,string user, string pass)
        {
            if(Membership.ValidateUser(user,pass)){
                User userTmp = db.users.Find(id);
                List<int> returnList = new List<int>(); ;
                foreach(Connection conn in userTmp.listConnections)
                {
                    if(conn.userConnected.active)
                        returnList.Add(conn.userConnected.userID);
                }
                return returnList;
            }else{
                return null;
            }
            
        }

        public User getUserByAutetication(string userTmp, string password)
        {
            if (Membership.ValidateUser(userTmp, password))
            {
                try
                {
                    int id_login;
                    id_login = WebSecurity.GetUserId(userTmp);
                    var user = from d in db.users where d.UserProfileID == id_login select d;
                    List<User> tempList = user.ToList();
                    return removeProxyUser(tempList.ElementAt(0));
                }
                catch (Exception)
                {
                    return null;
                }

            }
            else
            {
                return null;
            }
          }
           
        public IList<Word> GetEveryWord()
        {
            HangmanGateway hg = new HangmanGateway();
            IList<Word> words;

            try
            {
                words = hg.getEveryWord();
            }
            catch (SqlException)
            {
                return null;
            }

            return words;

        }

        public IList<int> getAllUsersID()
        {
            List<int> returnList = new List<int>();
            foreach (User user in db.users)
            {
                if (user.active)
                    returnList.Add(user.userID);
            }
            return returnList;
        }

        public int getConnectioStrenght(int id1, int id2)
        {
            User user = db.users.Find(id1);
            foreach(Connection conn in user.listConnections)
            {
                if(conn.userConnected.userID == id2)
                {
                    return conn.strenght;
                }
            }
            return -1;
        }

        public int getNumberTagsForUserId(int id, string user, string pass)
        {
            if (Membership.ValidateUser(user, pass))
            {
                return db.users.Find(id).userTags.Count();
            }
            else
            {
                return -1;
            }
        }

        public int getStrenghtConnection(int id1, int id2, string user, string pass)
        {
            if (Membership.ValidateUser(user, pass))
            {
                User user1 = db.users.Find(id1);
                foreach (Connection conn in user1.listConnections)
                {
                    if (conn.userConnected.userID == id2)
                    {
                        return conn.strenght;
                    }
                }
                return -1;
            }else
            {
                return -1;
            }
            
        }

        public UserData getUserData(int id, string user, string pass)
        {
            UserData userData = new UserData();
            if (Membership.ValidateUser(user, pass))
            {
                try
                {
                    User userT = db.users.Find(id);
                    userData.firstName = userT.userProfile.name;
                    userData.lastName = userT.userProfile.lastName;
                    userData.numberOfUserTags = userT.userTags.Count();
                    return userData;
                }
                catch (Exception)
                {
                    return userData;
                }
            }
            else
            {
                return userData;
            }

            
        }

        public bool createFriendRequest(int id1, int id2, string user, string pass)
        {
            if (Membership.ValidateUser(user, pass))
            {
                try
                {
                    User user1 = db.users.Find(id1);
                    User user2 = db.users.Find(id2);

                    /*Create Friend Request*/
                    FriendRequest fR = new FriendRequest();

                    /* Strenght */
                    int forçaInt = 1;
                    fR.strenght = forçaInt;

                    /* Tag Connection */
                    TagConnection tagConn = db.tagConnections.Find(1);
                    fR.tagConnection = tagConn;

                    /*Users*/
                    fR.user1 = user1;
                    fR.user2 = user2;

                    db.friendRequests.Add(fR);
                    db.SaveChanges();

                    try
                    {
                        /* Create Notification */
                        Notification note = new Notification();
                        NotificationType nTyp = new NotificationType();
                        note.message = @EpicWareWeb.Views.User.User.pedidoAmizadePeloJogo + " : " + user1.userProfile.nickname;
                        note.time = DateTime.Now;
                        note.read = false;
                        note.notificationType = nTyp;
                        user2.notifications.Add(note);
                    }
                    catch (Exception) { }

            

                    

                    db.Entry(user1).State = EntityState.Modified;
                    db.Entry(user2).State = EntityState.Modified;
                    db.SaveChanges();
                    return true;
                    
                }catch(Exception)
                {
                    return false;
                }

            }
            else { return false; }
            

        }

        /*Retorna uma lista com os id dos pedidos de amizade recebidos pendentes*/
        public List<int> getFRReceivedPending(int id, string user, string pass)
        {
            List<int> intRetunr = new List<int>();
            if (Membership.ValidateUser(user, pass))
            {
                var frQuery = from d in db.friendRequests
                           where d.user2.userID == id
                           select d;
            List<FriendRequest> list = frQuery.ToList();
            
            foreach (FriendRequest item in list)
            {
                intRetunr.Add(item.friendRequestID);
            }
            return intRetunr;
            }else{
                return null;
            }
            
        }
        
        /* Permite aceitar o pedido de amizade pelo jogo sem ter que jogar nenhum minijogo*/
        public bool acceptFriendRequest(int idFriendRequest, string user, string pass)
        {
            
            if (Membership.ValidateUser(user, pass))
            {
                /*Get friend request*/
            FriendRequest fR = db.friendRequests.Find(idFriendRequest);

            User user1 = fR.user1;
            User user2 = fR.user2;

            Connection conn1 = new Connection();
            Connection conn2 = new Connection();

            /* Strenght */
            conn1.strenght = 1;
            conn2.strenght = 1;

            /* Tag Connection */
            conn1.tagConnection = db.tagConnections.Find(1);
            conn2.tagConnection = db.tagConnections.Find(1);

            /* Owner */
            conn1.Owner = user1;
            conn2.Owner = user2;

            /* User Connected */
            conn1.userConnected = user2;
            conn2.userConnected = user1;

            /* Save connections on all users and remove FrindRequest*/
            user1.listConnections.Add(conn1);
            user2.listConnections.Add(conn2);

            /* Create Notification */
            Notification note = new Notification();
            note.message = user2.userProfile.nickname + " " + EpicWareWeb.Views.User.User.fraceite;
            note.time = DateTime.Now;
            note.read = false;
            NotificationType nTyp = new NotificationType();
            nTyp.type = "game"; // Notificação de jogo
            nTyp.resultLink = "/LAPR5/User/Profile/" + user1.userID;
            note.notificationType = nTyp;
            user1.notifications.Add(note);
            try
            {
                db.Entry(user2).State = EntityState.Modified;
                db.Entry(user1).State = EntityState.Modified;
                db.SaveChanges();
                db.friendRequests.Remove(fR);
                db.SaveChanges();
                return true;
            }
            catch (Exception)
            {
                return false;
            }
            }else{
                return false;
            }
            
        
                
         



        }

        /* Rejeitar pedido de amizade pelo jogo */
        public bool rejectFriendRequest(int idFriendRequest, string user, string pass)
        {
            if (Membership.ValidateUser(user, pass))
            {
                try
                {
                    FriendRequest fR = db.friendRequests.Find(idFriendRequest);
                    db.friendRequests.Remove(fR);
                    db.SaveChanges();
                    return true;
                }catch(Exception)
                {
                    return false;
                }
            }
            else
            {
                return false;
            }

        }

        /* Permite registar qual o jogo que quem recebeu o pedido de amizade quer que o outro jogue para ser seu amigo */
        public bool selectGameToPlay(int idFriendRequest, int idGame, string user, string pass)
        {
            if (Membership.ValidateUser(user, pass))
            {
                FriendRequest fR = db.friendRequests.Find(idFriendRequest);
                Game game = db.games.Find(idGame);
                fR.game = game;
                try
                {
                    db.Entry(fR).State = EntityState.Modified;
                    db.SaveChanges();
                    return true;
                }
                catch (Exception)
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
            



        }

        /* Permite o registo de uma resultado de um jogo */
        public bool registerGameResult(int idFriendRequest,bool win,int points, string user, string pass)
        {
            if (Membership.ValidateUser(user, pass))
            {
                FriendRequest fR = db.friendRequests.Find(idFriendRequest);
                if (win)
                {
                    try
                    {
                        /* Create Notification */
                        Notification note = new Notification();
                        note.message = "O pedido de amizade foi aceite por ter ganho o desafio";
                        note.time = DateTime.Now;
                        note.read = false;
                        NotificationType nTyp = new NotificationType();
                        nTyp.type = "game"; // Notificação de jogo
                        note.notificationType = nTyp;

                        User userTmp = fR.user1;
                        acceptFriendRequest(idFriendRequest, user, pass);
                        ScoreUser score = new ScoreUser();
                        score.MyProperty = fR.game;
                        score.points = points;
                        userTmp.scores.Add(score);
                        userTmp.notifications.Add(note);
                        db.Entry(userTmp).State = EntityState.Modified;
                        db.SaveChanges();
                        return true;
                    }
                    catch (Exception)
                    {
                        return false;
                    }
                }
                else
                {
                    try
                    {
                        /* Create Notification */
                        Notification note = new Notification();
                        note.message = "O pedido de amizade foi rejeitado por ter perdido o desafio";
                        note.time = DateTime.Now;
                        note.read = false;
                        NotificationType nTyp = new NotificationType();
                        nTyp.type = "game"; // Notificação de jogo
                        note.notificationType = nTyp;
                        User userTmp = fR.user1;
                        userTmp.notifications.Add(note);
                        db.Entry(userTmp).State = EntityState.Modified;
                        db.friendRequests.Remove(fR);
                        db.SaveChanges();
                        return true;
                    }
                    catch (Exception)
                    {
                        return false;
                    }

                }
            }
            else
            {
                return false;
            }
            
        }

        /*Retorna uma lista de inteiros com os id's dos pedidos de amizade que aguradam que quem pediu jogo o jogo*/
        public List<int> waitingGamePlay(int idUser, string user, string pass)
        {
            List<int> intReturn = new List<int>();
            if (Membership.ValidateUser(user, pass))
            {
                var frQuery = from d in db.friendRequests
                              where d.user1.userID == idUser
                              && d.game != null
                              select d;
                List<FriendRequest> list = frQuery.ToList();
                foreach(FriendRequest item in list)
                {
                    intReturn.Add(item.friendRequestID);
                }
                return intReturn;
            }
            else
            {
                return null;
            }

        }

        /*Retorna o Objeto pedido de amizade dado um determinado id*/
        public FriendRequest getFriendRequestById(int id, string user, string pass)
        {
            FriendRequest fR = removeProxyFriendRequest(db.friendRequests.Find(id));
            return fR;
        }

        /*AUX METHODS*/

        private User removeProxyUser(User tmp)
        {
            User user = new User();
            //user.active = tmp.active;
            //user.email = tmp.email;
            //user.language = tmp.language;
            //user.missions = tmp.missions;
            user.mood = tmp.mood;
            //user.notifications = removeProxyNotifications(tmp.notifications);
            //user.scores = tmp.scores;
            user.userID = tmp.userID;
            //user.UserProfileID = tmp.UserProfileID;
            //user.userTags = tmp.userTags;

            user.userProfile = new Profile();
            //user.userProfile.birthday = tmp.userProfile.birthday;
            //user.userProfile.country = tmp.userProfile.country;
            //user.userProfile.facebookProfile = tmp.userProfile.facebookProfile;
            user.userProfile.gender = tmp.userProfile.gender;
            user.userProfile.lastName = tmp.userProfile.lastName;
            //user.userProfile.linkedinProfile = tmp.userProfile.linkedinProfile;
            user.userProfile.name = tmp.userProfile.name;
            user.userProfile.nickname = tmp.userProfile.nickname;
            //user.userProfile.pathImg = tmp.userProfile.pathImg;
            //user.userProfile.phoneNumber = tmp.userProfile.phoneNumber;
            user.userProfile.profileID = tmp.userProfile.profileID;
            //user.userProfile.twitterProfile = tmp.userProfile.twitterProfile;
            return user;
        }

        private List<Notification> removeProxyNotifications(List<Notification> listNote)
        {
            List<Notification> returnList = new List<Notification>();
            foreach(Notification tmp in listNote)
            {
                Notification note = new Notification();
                NotificationType nTyp = new NotificationType();
                note.message = tmp.message;
                note.notificationID = tmp.notificationID;
                note.read = tmp.read;
                note.time = tmp.time;
                note.notificationType = nTyp;


                if(tmp.notificationType != null)
                {
                    nTyp.notificationTypeID = tmp.notificationType.notificationTypeID;
                    nTyp.resultLink = tmp.notificationType.resultLink;
                    nTyp.type = tmp.notificationType.type;

                    note.notificationType = nTyp;
                }


                returnList.Add(note);
            }


            return returnList;
        }

        private FriendRequest removeProxyFriendRequest(FriendRequest tmp)
        {
            FriendRequest fRreturn = new FriendRequest();
            fRreturn.friendRequestID = tmp.friendRequestID;
            fRreturn.game = db.games.Find(tmp.game.gameID);
            fRreturn.strenght = tmp.strenght;
            fRreturn.tagConnection = db.tagConnections.Find(tmp.tagConnection.tagConnectionID);
            fRreturn.user1 = removeProxyUser(tmp.user1);
            fRreturn.user2 = removeProxyUser(tmp.user2);
            return fRreturn;
        }


    }
}

