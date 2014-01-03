using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class NotificationType
    {
        public int notificationTypeID { get; set; }
        public string type { get; set; }
        public string resultLink { get; set; }
    }
}