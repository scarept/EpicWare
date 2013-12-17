using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class FriendRequest
    {
        public int friendRequestID { get; set; }
        public User user1 { get; set; }
        public User user2 { get; set; }
        public Game game { get; set; }
    }
}