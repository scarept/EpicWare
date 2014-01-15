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
        public int currentLeavel { get; set; }

        [DataMember]
        public int finalLeavel { get; set; }

        public bool missionDone { get; set; }
    }
}