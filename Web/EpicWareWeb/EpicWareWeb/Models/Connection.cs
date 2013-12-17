using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class Connection
    {
        public int connectionID { get; set; }
        public int strenght { get; set; }
        public virtual TagConnection tagConnection { get; set; }
        public virtual User userConnected { get; set; }
        
    }
}