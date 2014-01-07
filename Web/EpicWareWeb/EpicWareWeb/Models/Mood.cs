﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace EpicWareWeb.Models
{
    [Serializable]
    [DataContract]
    public class Mood
    {
        [DataMember]
        public int moodID { get; set; }

        [DataMember]
        public string name { get; set; }
    }
}