using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace EpicWareWeb.Models
{
    [Serializable]
    [DataContract]
    public class IntroFriendRequest
    {
        [DataMember]
        public int introFriendRequestID { get; set; }

        [DataMember]
        public virtual User userA { get; set; }

        [DataMember]
        public virtual User userB { get; set; }

        [DataMember]
        public virtual User userC { get; set; }

        [DataMember]
        public bool sendedBC { get; set; }

        [DataMember]
        public string messageAB { get; set; }

        [DataMember]
        public string messageBC { get; set; }
    }
}