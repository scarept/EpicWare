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
    public class Mission
    {
        [DataMember]
        public int missionID { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "descricao")]
        public string description { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "nivel")]
        public int level { get; set; }
    }
}