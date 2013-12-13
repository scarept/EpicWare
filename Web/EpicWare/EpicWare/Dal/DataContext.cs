using EpicWare.Models;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace EpicWare.Dal
{
    public class DataContext : DbContext
    {
        public DataContext():base("DefaultConnection"){}

        public DbSet<Mission> missions { get; set; }
    }
}