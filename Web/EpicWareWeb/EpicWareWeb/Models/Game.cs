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
    public class Game
    {
        [DataMember]
        public int gameID { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "jogo")]
        public string name { get; set; } 
    }
}