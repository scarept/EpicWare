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
    public class User
    {
        
        [DataMember]
        public int userID { get; set; }

        [DataMember]
        public int UserProfileID { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "usertags")]
        public virtual List<Tag> userTags { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "conexoes")]
        public virtual List<Connection> listConnections { get; set; }

        [DataMember]
        [Required]
        [Display(ResourceType = typeof(LanguageModels), Name = "linguagem")]
        public virtual Language language { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "pontoacoes")]
        public virtual List<ScoreUser> scores { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "notificacoes")]
        public virtual List<Notification> notifications { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "missoes")]
        public virtual List<Mission> missions { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "estadoHumor")]
        public virtual Mood mood { get; set; }

        [DataMember]
        public virtual Profile userProfile { get; set; }

        [DataMember]
        [DataType(DataType.EmailAddress)]
        [Required]
        [Display(ResourceType = typeof(LanguageModels), Name = "email")]
        public string email { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "ativo")]
        public bool active { get; set; }

    }
}