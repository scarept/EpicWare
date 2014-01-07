using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace EpicWareWeb.Models
{
    [Serializable]
    [DataContract]
    public class FriendRequest
    {
        [DataMember]
        public int friendRequestID { get; set; }

        [DataMember]
        public virtual User user1 { get; set; }

        [DataMember]
        public virtual User user2 { get; set; }

        [DataMember]
        public virtual Game game { get; set; }

        [DataMember]
        public virtual TagConnection tagConnection { get; set; }

        [DataMember]
        public int strenght { get; set; }
    }
}