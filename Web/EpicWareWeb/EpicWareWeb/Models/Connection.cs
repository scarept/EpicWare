using System;
using System.Collections.Generic;
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
        public int strenght { get; set; }

        [DataMember]
        public virtual TagConnection tagConnection { get; set; }

        [DataMember]
        public virtual User userConnected { get; set; }
        
    }
}