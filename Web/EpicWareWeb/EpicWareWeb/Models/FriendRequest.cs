using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class FriendRequest
    {
        public int friendRequestID { get; set; }
        public virtual User user1 { get; set; }
        public virtual User user2 { get; set; }
        public virtual Game game { get; set; }
        public virtual TagConnection tagConnection { get; set; }
        public int strenght { get; set; }
    }
}