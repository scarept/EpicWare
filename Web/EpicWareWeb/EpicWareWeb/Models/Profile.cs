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
        [Required]
        [Display(ResourceType = typeof(LanguageModels), Name = "nome")]
        public string name { get; set; }

        [DataMember]
        [Required]
        [Display(ResourceType = typeof(LanguageModels), Name = "ultNome")]
        public string lastName { get; set; }

        [DataMember]
        [Required]
        [Display(ResourceType = typeof(LanguageModels), Name = "nickname")]
        public string nickname { get; set; }

        [DataMember]
        [DisplayFormat(ApplyFormatInEditMode = true, DataFormatString = "{0:MM/dd/yyyy}")]
        [Display(ResourceType = typeof(LanguageModels), Name = "dataNascimento")]
        public DateTime birthday { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "pais")]
        public virtual Country country { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "numTelefone")]
        [DataType(DataType.PhoneNumber)]
        public int phoneNumber { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "linkedinPofile")]
        public string linkedinProfile { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "facebookPofile")]
        public string facebookProfile { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "twitterPofile")]
        public string twitterProfile { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "genero")]
        public string gender { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "pathImg")]
        public string pathImg { get; set; }
        
    }
}