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
            foreach (Connection con in user.listConnections)
            {
                if(con.userConnected == user)
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
            User userAuth = new UserController().UserAutenticated();
            var fR = from d in db.friendRequests where d.user1 == userAuth && d.user2 == user select d;
            FriendRequest tmp = fR.ToList().ElementAt(0);
            if (tmp == null)
                return false;
            else
                return true;
        }
        
        // Return if user autenticated have friend requested by user parameter
        [Authorize]
        public bool friendRequestReceived(User user)
        {
            User userAuth = new UserController().UserAutenticated();
            var fR = from d in db.friendRequests where d.user2 == userAuth && d.user1 == user select d;
            FriendRequest tmp = fR.ToList().ElementAt(0);
            if (tmp == null)
                return false;
            else
                return true;
        }

        // List of Friends Requested Pending of user autenticated
        [Authorize]
        public List<FriendRequest> friendsRequestedPending()
        {
            User userAuth = new UserController().UserAutenticated();
            var fRP = from d in db.friendRequests where d.user2.userID == userAuth.userID select d;
            return fRP.ToList();
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
                    if (con.userConnected == con2.userConnected)
                    {
                        flag = true;
                    }
                    if (flag)
                        continue;
                    returnList.Add(con2.userConnected);
                }
            }
            return returnList;
        }

        //public bool addFriend(User user)
        //{

        //}

    }
}
