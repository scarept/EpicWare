using System;
using System.Collections.Generic;
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
        public string description { get; set; }

        [DataMember]
        public int level { get; set; }
    }
}