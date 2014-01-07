using System;
using System.Collections.Generic;
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
        public string name { get; set; } 
    }
}