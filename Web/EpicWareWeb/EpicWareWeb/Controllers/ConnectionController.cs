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

        public ActionResult Index()
        {
            return View();
        }

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

        public List<FriendRequest> friendsRequestedPending()
        {
            User userAuth = new UserController().UserAutenticated();
            var fRP = from d in db.friendRequests where d.user2 == userAuth select d;
            return fRP.ToList();
        }

    }
}
