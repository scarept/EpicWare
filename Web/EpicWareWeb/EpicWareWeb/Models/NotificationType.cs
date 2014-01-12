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
    public class NotificationType
    {
        [DataMember]
        public int notificationTypeID { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "tipoNotificação")]
        public string type { get; set; }

        [DataMember]
        public string resultLink { get; set; }
    }
}