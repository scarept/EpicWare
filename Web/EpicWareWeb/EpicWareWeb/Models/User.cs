using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace EpicWareWeb.Models
{
    [Serializable]
    [DataContract]
    public class User
    {
        
        [DataMember]
        public int userID { get; set; }

        [DataMember]
        public int UserProfileID { get; set; }

        [DataMember]
        public virtual List<Tag> userTags { get; set; }

        [DataMember]
        public virtual List<Connection> listConnections { get; set; }

        [DataMember]
        public virtual Language language { get; set; }

        [DataMember]
        public virtual List<ScoreUser> scores { get; set; }

        [DataMember]
        public virtual List<Notification> notifications { get; set; }

        [DataMember]
        public virtual List<Mission> missions { get; set; }

        [DataMember]
        public virtual Mood mood { get; set; }

        [DataMember]
        public virtual Profile userProfile { get; set; }

        [DataMember]
        public string email { get; set; }

        [DataMember]
        public bool active { get; set; }

    }
}