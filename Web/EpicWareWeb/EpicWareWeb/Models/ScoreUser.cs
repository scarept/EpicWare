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
        /*
         * Mission complete -> 5 points
         * MiniGames        -> 2 point
         * 
         */
        [DataMember]
        public int scoreUserID { get; set; }

        [DataMember]
        public Game MyProperty { get; set; }

        [DataMember]
        public int points { get; set; }
    }
}