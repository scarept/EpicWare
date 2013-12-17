﻿using EpicWareWeb.Models;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace EpicWareWeb.DAL
{
    public class DataContext : DbContext
    {
        public DataContext() : base("DefaultConnection") { }
        public DbSet<Mood> moods { get; set; }
        public DbSet<TagConnection> tagConnections { get; set; }
        public DbSet<Connection> connections { get; set; }
        public DbSet<User> users { get; set; }
    }
}