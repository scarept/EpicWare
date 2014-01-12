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
    public class ScoreUser
    {
        /*
         * Mission complete -> 5 points
         * MiniGames        -> 2 point
         * 
         */
        [DataMember]
        public int scoreUserID { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "jogo")]
        public Game MyProperty { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "pontos")]
        public int points { get; set; }
    }
}