using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class Download
    {
        public int downloadID { get; set; }

        [Display(ResourceType = typeof(LanguageModels), Name = "datahora")]
        public DateTime time { get; set; }
    }
}