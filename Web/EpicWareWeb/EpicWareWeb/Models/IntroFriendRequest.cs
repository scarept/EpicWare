using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
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
        [Display(ResourceType = typeof(LanguageModels), Name = "messageAB")]
        public string messageAB { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "messageBC")]
        public string messageBC { get; set; }
    }
}