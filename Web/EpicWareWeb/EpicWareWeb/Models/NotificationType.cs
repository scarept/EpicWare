using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace EpicWareWeb.Models
{
    [Serializable]
    [DataContract]
    public class NotificationType
    {
        [DataMember]
        public int notificationTypeID { get; set; }

        [DataMember]
        public string type { get; set; }

        [DataMember]
        public string resultLink { get; set; }
    }
}