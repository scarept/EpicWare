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
    public class Tag
    {
        [DataMember]
        public int tagID { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "tag")]
        public string tag { get; set; }
    }
}