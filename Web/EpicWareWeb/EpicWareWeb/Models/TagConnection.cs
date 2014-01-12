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
    public class TagConnection
    {
        [DataMember]
        public int tagConnectionID { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "tag")]
        public string tag { get; set; }
    }
}