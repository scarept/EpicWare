using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class Mood
    {
        public int moodID { get; set; }
        public string name { get; set; }
    }
}