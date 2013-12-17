using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class Mission
    {
        public int missionID { get; set; }
        public string description { get; set; }
        public int level { get; set; }
    }
}