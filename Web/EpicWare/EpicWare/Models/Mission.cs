using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace EpicWare.Models
{
    public class Mission
    {
        [Display(Name="ID")]
        public int ID { get; set; }

        [DataType(DataType.Text)]
        //[Display(Name = "Var Mission Description")]
        public string description { get; set; }
        
        [DataType(DataType.Currency)]
        //[Display(Name = "Var Mission Number")]
        public int number { get; set; }

    }
}