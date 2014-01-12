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
    public class Country
    {
        [DataMember]
        public int countryID { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "pais")]
        public string name { get; set; }
    }
}