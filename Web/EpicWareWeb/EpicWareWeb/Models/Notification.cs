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
    public class Notification
    {
        [DataMember]
        public int notificationID { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "notificacao")]
        public string message { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "datahora")]
        public DateTime time { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "lida")]
        public bool read { get; set; }

        [DataMember]
        public virtual NotificationType notificationType { get; set; }
    }
}