using EpicWareWeb.Models;
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
        public DbSet<ScoreUser> scores { get; set; }
        public DbSet<Game> games { get; set; }
        public DbSet<FriendRequest> friendRequests { get; set; }
        public DbSet<Notification> notifications { get; set; }
        public DbSet<IntroFriendRequest> introes { get; set; }
        public DbSet<Mission> missions { get; set; }
        public DbSet<Language> languages { get; set; }
        public DbSet<Profile> Profiles { get; set; }
    }
}