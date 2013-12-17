using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class User
    {
        public int userID { get; set; }
        public List<string> userTags { get; set; }
        public List<Connection> listConnections { get; set; }
        public Language language { get; set; }
        public List<ScoreUser> scores { get; set; }
        public List<Notification> notifications { get; set; }
        public List<Mission> missions { get; set; }
        public Mood mood { get; set; }
        public Profile userProfile { get; set; }
        public bool active { get; set; }
    }
}