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
    public class Profile
    {
        [DataMember]
        public int profileID { get; set; }

        [DataMember]
        public string name { get; set; }

        [DataMember]
        public string lastName { get; set; }

        [DataMember]
        public string nickname { get; set; }

        [DataMember]
        [DisplayFormat(ApplyFormatInEditMode = true, DataFormatString = "{0:MM/dd/yyyy}")]
        public DateTime birthday { get; set; }

        [DataMember]
        public virtual Country country { get; set; }

        [DataMember]
        public int phoneNumber { get; set; }

        [DataMember]
        public string linkedinProfile { get; set; }

        [DataMember]
        public string facebookProfile { get; set; }

        [DataMember]
        public string twitterProfile { get; set; }

        [DataMember]
        public string gender { get; set; }

        [DataMember]
        public string pathImg { get; set; }
        
    }
}