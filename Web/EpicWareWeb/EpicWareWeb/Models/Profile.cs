using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class Profile
    {
        public int profileID { get; set; }
        public string name { get; set; }
        public string lastName { get; set; }
        public string nickname { get; set; }
        public DateTime birthday { get; set; }
        public string country { get; set; }
        public int phoneNumber { get; set; }
        public string email { get; set; }
        public string linkedinProfile { get; set; }
        public string facebookProfile { get; set; }
        public string twitterProfile { get; set; }
        public string gender { get; set; }
        public string pathImg { get; set; }
    }
}