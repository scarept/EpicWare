using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class User
    {
        public int userID { get; set; }
        public int UserProfileID { get; set; }
        public List<string> userTags { get; set; }
        public virtual List<Connection> listConnections { get; set; }
        public Language language { get; set; }
        public virtual List<ScoreUser> scores { get; set; }
        public virtual List<Notification> notifications { get; set; }
        public virtual List<Mission> missions { get; set; }
        public virtual Mood mood { get; set; }
        public virtual Profile userProfile { get; set; }
        public bool active { get; set; }
    }
}