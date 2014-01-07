using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace EpicWareWeb.Models
{
    [Serializable]
    [DataContract]
    public class Notification
    {
        [DataMember]
        public int notificationID { get; set; }

        [DataMember]
        public string message { get; set; }

        [DataMember]
        public DateTime time { get; set; }

        [DataMember]
        public bool read { get; set; }

        [DataMember]
        public virtual NotificationType notificationType { get; set; }
    }
}