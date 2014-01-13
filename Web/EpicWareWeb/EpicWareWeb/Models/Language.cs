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
    public class Language
    {
        [DataMember]
        public int languageID { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "linguagem")]
        public string name { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "linguagem")]
        public string reference { get; set; }
    }
}