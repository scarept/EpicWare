﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace EpicWareWeb.Models
{
    public class User
    {
        public int userID { get; set; }
        public int UserProfileID { get; set; }
        public List<string> userTags { get; set; }
        public virtual List<Connection> listConnections { get; set; }
        public Language language { get; set; }
        public virtual List<ScoreUser> scores { get; set; }
        public virtual List<Notification> notifications { get; set; }
        public virtual List<Mission> missions { get; set; }
        public virtual Mood mood { get; set; }
        public virtual Profile userProfile { get; set; }
        public string email { get; set; }
        public bool active { get; set; }

        public User()
        {
            userTags = new List<string>();
            listConnections = new List<Connection>();
            language = new Language();
            scores = new List<ScoreUser>();
            notifications = new List<Notification>();
            missions = new List<Mission>();
            mood = new Mood();
            userProfile = new Profile();
            active = true;
        }
    }
}