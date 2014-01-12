using EpicWareWeb.Controllers;
using EpicWareWeb.DAL;
using EpicWareWeb.Models;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
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

        //public User teste()
        //{
        //    //User teste = new User();
        //    //teste.active = true;
        //    //teste.email = "a";
        //    //teste.language = new Language();
        //    //teste.language.name = "";
        //    //teste.listConnections = new List<Connection>();
        //    //teste.missions = new List<Mission>();
        //    //teste.mood = new Mood();
        //    //teste.mood.name = "";
        //    //teste.notifications = new List<Notification>();
        //    //teste.scores = new List<ScoreUser>();
        //    //teste.userID = 1;
        //    //teste.userProfile = new Profile();
        //    //teste.UserProfileID = 1;
        //    //teste.userTags = new List<Tag>();

        //    //teste.userProfile.country = new Country();
        //    //teste.userProfile.country.name = "";
        //    //teste.userProfile.facebookProfile = "";
        //    //teste.userProfile.gender = "";
        //    //teste.userProfile.lastName = "";
        //    //teste.userProfile.linkedinProfile = "";
        //    //teste.userProfile.name = "";
        //    //teste.userProfile.nickname = "";
        //    //teste.userProfile.pathImg = "";
        //    //teste.userProfile.phoneNumber = 1;
        //    //teste.userProfile.profileID = 1;
        //    //teste.userProfile.twitterProfile = "";

        //    User teste = removeProxyUser(db.users.Find(1));
        //    return teste;
        //}


        /*AUX METHODS*/

        private User removeProxyUser(User tmp)
        {
            User user = new User();
            user.active = tmp.active;
            user.email = tmp.email;
            user.language = tmp.language;
            user.missions = tmp.missions;
            user.mood = tmp.mood;
            user.notifications = removeProxyNotifications(tmp.notifications);
            user.scores = tmp.scores;
            user.userID = tmp.userID;
            user.UserProfileID = tmp.UserProfileID;
            user.userTags = tmp.userTags;

            user.userProfile = new Profile();
            user.userProfile.birthday = tmp.userProfile.birthday;
            user.userProfile.country = tmp.userProfile.country;
            user.userProfile.facebookProfile = tmp.userProfile.facebookProfile;
            user.userProfile.gender = tmp.userProfile.gender;
            user.userProfile.lastName = tmp.userProfile.lastName;
            user.userProfile.linkedinProfile = tmp.userProfile.linkedinProfile;
            user.userProfile.name = tmp.userProfile.name;
            user.userProfile.nickname = tmp.userProfile.nickname;
            user.userProfile.pathImg = tmp.userProfile.pathImg;
            user.userProfile.phoneNumber = tmp.userProfile.phoneNumber;
            user.userProfile.profileID = tmp.userProfile.profileID;
            user.userProfile.twitterProfile = tmp.userProfile.twitterProfile;
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
                note.notificationID = note.notificationID;
                note.read = tmp.read;
                note.time = tmp.time;

                nTyp.notificationTypeID = tmp.notificationType.notificationTypeID;
                nTyp.resultLink = tmp.notificationType.resultLink;
                nTyp.type = tmp.notificationType.type;

                note.notificationType = nTyp;

                returnList.Add(note);
            }


            return returnList;
        }


    }
}

