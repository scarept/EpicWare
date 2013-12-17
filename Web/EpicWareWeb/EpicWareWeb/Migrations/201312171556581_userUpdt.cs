namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class userUpdt : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.Users", "mood_moodID", c => c.Int());
            AddColumn("dbo.Users", "userProfile_profileID", c => c.Int());
            AddColumn("dbo.Notifications", "User_userID", c => c.Int());
            AddColumn("dbo.Missions", "User_userID", c => c.Int());
            AddForeignKey("dbo.Users", "mood_moodID", "dbo.Moods", "moodID");
            AddForeignKey("dbo.Users", "userProfile_profileID", "dbo.Profiles", "profileID");
            AddForeignKey("dbo.Notifications", "User_userID", "dbo.Users", "userID");
            AddForeignKey("dbo.Missions", "User_userID", "dbo.Users", "userID");
            CreateIndex("dbo.Users", "mood_moodID");
            CreateIndex("dbo.Users", "userProfile_profileID");
            CreateIndex("dbo.Notifications", "User_userID");
            CreateIndex("dbo.Missions", "User_userID");
        }
        
        public override void Down()
        {
            DropIndex("dbo.Missions", new[] { "User_userID" });
            DropIndex("dbo.Notifications", new[] { "User_userID" });
            DropIndex("dbo.Users", new[] { "userProfile_profileID" });
            DropIndex("dbo.Users", new[] { "mood_moodID" });
            DropForeignKey("dbo.Missions", "User_userID", "dbo.Users");
            DropForeignKey("dbo.Notifications", "User_userID", "dbo.Users");
            DropForeignKey("dbo.Users", "userProfile_profileID", "dbo.Profiles");
            DropForeignKey("dbo.Users", "mood_moodID", "dbo.Moods");
            DropColumn("dbo.Missions", "User_userID");
            DropColumn("dbo.Notifications", "User_userID");
            DropColumn("dbo.Users", "userProfile_profileID");
            DropColumn("dbo.Users", "mood_moodID");
        }
    }
}
