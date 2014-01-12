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
    public class Connection
    {
        [DataMember]
        public int connectionID { get; set; }

        [DataMember]
        public User Owner { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "forca")]
        public int strenght { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "tagConexao")]
        public virtual TagConnection tagConnection { get; set; }

        [DataMember]
        [Display(ResourceType = typeof(LanguageModels), Name = "utilizadorConectado")]
        public virtual User userConnected { get; set; }
        
    }
}