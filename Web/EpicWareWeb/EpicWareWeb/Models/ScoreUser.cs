using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace EpicWareWeb.Models
{
    [Serializable]
    [DataContract]
    public class ScoreUser
    {
        [DataMember]
        public int scoreUserID { get; set; }
    }
}