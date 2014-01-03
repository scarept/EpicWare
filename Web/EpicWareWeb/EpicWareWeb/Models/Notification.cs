using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class Notification
    {
        public int notificationID { get; set; }
        public string message { get; set; }
        public DateTime time { get; set; }
        public bool read { get; set; }
        public virtual NotificationType notificationType { get; set; }
    }
}