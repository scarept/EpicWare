using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class IntroFriendRequest
    {
        public int introFriendRequestID { get; set; }
        public virtual User userA { get; set; }
        public virtual User userB { get; set; }
        public virtual User userC { get; set; }
        public bool sendedBC { get; set; }
        public string messageAB { get; set; }
        public string messageBC { get; set; }
    }
}