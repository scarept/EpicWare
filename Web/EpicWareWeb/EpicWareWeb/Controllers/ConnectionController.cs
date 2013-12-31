using EpicWareWeb.DAL;
using EpicWareWeb.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace EpicWareWeb.Controllers
{
    public class ConnectionController : Controller
    {
        public DataContext db = new DataContext();
        //
        // GET: /Connection/

        // Return if user is friend of user autenticated
        [Authorize]
        public bool isFriends(User user)
        {
            UserController ctrUser = new UserController();
            User userAuth = ctrUser.UserAutenticated();

            bool flag = false;
            foreach (Connection con in userAuth.listConnections)
            {
                if(con.userConnected.userID == user.userID)
                {
                    flag = true;
                }
            }
            return flag;

        }
        
        // Return if user autenticated have requested "friend-request" for user parameter
        [Authorize]
        public bool friendRequested(User user)
        {
            try
            {
                User userAuth = new UserController().UserAutenticated();
                var fR = from d in db.friendRequests where d.user1.userID == userAuth.userID && d.user2.userID == user.userID select d;
                FriendRequest tmp = fR.ToList().ElementAt(0);
                return true;
            }
            catch (Exception)
            {
                return false;
            }
            
        }
        
        // Return if user autenticated have friend requested by user parameter
        [Authorize]
        public bool friendRequestReceived(User user)
        {
            try
            {
                User userAuth = new UserController().UserAutenticated();
                var fR = from d in db.friendRequests where d.user2.userID == userAuth.userID && d.user1.userID == user.userID select d;
                FriendRequest tmp = fR.ToList().ElementAt(0);
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }

        // List of Friends Requested Pending of user autenticated
        [Authorize]
        public List<FriendRequest> friendsRequestedPending()
        {
            try
            {
                User userAuth = new UserController().UserAutenticated();
                var fRP = from d in db.friendRequests where d.user2.userID == userAuth.userID select d;
                return fRP.ToList();
            }
            catch (Exception)
            {
                return new List<FriendRequest>();
            }
            
        }

        // List of intro requests in middle action
        public List<IntroFriendRequest> introsRequestMiddlePending()
        {
            try
            {
                User userAuth = new UserController().UserAutenticated();
                var fRP = from d in db.introes where d.userB.userID == userAuth.userID select d;
                return fRP.ToList();
            }
            catch (Exception)
            {
                return new List<IntroFriendRequest>();
            }

        }

        // List of intros received pending
        public List<IntroFriendRequest> introsRequestPending()
        {
            try
            {
                User userAuth = new UserController().UserAutenticated();
                var fRP = from d in db.introes where d.userC.userID == userAuth.userID select d;
                return fRP.ToList();
            }
            catch (Exception)
            {
                return new List<IntroFriendRequest>();
            }
        }

        // List of No Coomon Friends between User Autenticated and User parameter
        public List<User> noCommonFriends(User user)
        {
            User userAuth = new UserController().UserAutenticated();
            List<User> returnList = new List<User>();
            foreach (Connection con in user.listConnections)
            {
                bool flag = false;
                foreach (Connection con2 in userAuth.listConnections)
                {
                    if (con.userConnected.userID == con2.userConnected.userID)
                    {
                        flag = true;
                    }
                    if (flag)
                        continue;
                    returnList.Add(con.userConnected);
                }
            }
            return returnList;
        }

        // List of No Coomon Connections between User Autenticated and User parameter
        public List<Connection> noCommonConnections(User user)
        {
            User userAuth = new UserController().UserAutenticated();
            List<Connection> returnList = new List<Connection>();
            foreach (Connection con in user.listConnections)
            {
                bool flag = false;
                foreach (Connection con2 in userAuth.listConnections)
                {
                    if (con.userConnected.userID == con2.userConnected.userID)
                    {
                        flag = true;
                    }
                    if (flag)
                        continue;
                    if(con.userConnected.userID != userAuth.userID)
                        returnList.Add(con);
                }
            }
            return returnList;
        }

        // Return if user auth is owner of Profile visited
        public bool amI(User user)
        {
            UserController ctrUser = new UserController();
            User userAuth = ctrUser.UserAutenticated();
            return userAuth.userID == user.userID;
        }

        //public bool addFriend(User user)
        //{

        //}

    }
}
