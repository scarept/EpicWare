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

        public User getUserByID(int id, string user, string pass)
        {
            if(Membership.ValidateUser(user,pass)){
                return removeProxyUser(db.users.Find(id));
            }else{
                return null;
            }
            
        }

        public IList<User> getUserFriendsByUserId(int id,string user, string pass)
        {
            if(Membership.ValidateUser(user,pass)){
                User userTmp = db.users.Find(id);
                List<User> returnList = new List<User>(); ;
                foreach(Connection conn in userTmp.listConnections)
                {
                    if(conn.userConnected.active)
                        returnList.Add(removeProxyUser(conn.userConnected));
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
            user.notifications = tmp.notifications;
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
    }
}

