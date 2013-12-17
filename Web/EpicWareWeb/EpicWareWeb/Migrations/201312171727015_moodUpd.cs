namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class moodUpd : DbMigration
    {
        public override void Up()
        {
            DropForeignKey("dbo.Connections", "tagConnection_tagConnectionID", "dbo.TagConnections");
            DropForeignKey("dbo.Connections", "userConnected_userID", "dbo.Users");
            DropForeignKey("dbo.Users", "language_languageID", "dbo.Languages");
            DropForeignKey("dbo.Users", "mood_moodID", "dbo.Moods");
            DropForeignKey("dbo.Users", "userProfile_profileID", "dbo.Profiles");
            DropForeignKey("dbo.ScoreUsers", "User_userID", "dbo.Users");
            DropForeignKey("dbo.Notifications", "User_userID", "dbo.Users");
            DropForeignKey("dbo.Missions", "User_userID", "dbo.Users");
            DropForeignKey("dbo.FriendRequests", "user1_userID", "dbo.Users");
            DropForeignKey("dbo.FriendRequests", "user2_userID", "dbo.Users");
            DropForeignKey("dbo.FriendRequests", "game_gameID", "dbo.Games");
            DropForeignKey("dbo.IntroFriendRequests", "userA_userID", "dbo.Users");
            DropForeignKey("dbo.IntroFriendRequests", "userB_userID", "dbo.Users");
            DropForeignKey("dbo.IntroFriendRequests", "userC_userID", "dbo.Users");
            DropIndex("dbo.Connections", new[] { "tagConnection_tagConnectionID" });
            DropIndex("dbo.Connections", new[] { "userConnected_userID" });
            DropIndex("dbo.Users", new[] { "language_languageID" });
            DropIndex("dbo.Users", new[] { "mood_moodID" });
            DropIndex("dbo.Users", new[] { "userProfile_profileID" });
            DropIndex("dbo.ScoreUsers", new[] { "User_userID" });
            DropIndex("dbo.Notifications", new[] { "User_userID" });
            DropIndex("dbo.Missions", new[] { "User_userID" });
            DropIndex("dbo.FriendRequests", new[] { "user1_userID" });
            DropIndex("dbo.FriendRequests", new[] { "user2_userID" });
            DropIndex("dbo.FriendRequests", new[] { "game_gameID" });
            DropIndex("dbo.IntroFriendRequests", new[] { "userA_userID" });
            DropIndex("dbo.IntroFriendRequests", new[] { "userB_userID" });
            DropIndex("dbo.IntroFriendRequests", new[] { "userC_userID" });
            DropTable("dbo.TagConnections");
            DropTable("dbo.Connections");
            DropTable("dbo.Users");
            DropTable("dbo.Languages");
            DropTable("dbo.ScoreUsers");
            DropTable("dbo.Notifications");
            DropTable("dbo.Missions");
            DropTable("dbo.Profiles");
            DropTable("dbo.Games");
            DropTable("dbo.FriendRequests");
            DropTable("dbo.IntroFriendRequests");
        }
        
        public override void Down()
        {
            CreateTable(
                "dbo.IntroFriendRequests",
                c => new
                    {
                        introFriendRequestID = c.Int(nullable: false, identity: true),
                        messageAB = c.String(),
                        messageBC = c.String(),
                        userA_userID = c.Int(),
                        userB_userID = c.Int(),
                        userC_userID = c.Int(),
                    })
                .PrimaryKey(t => t.introFriendRequestID);
            
            CreateTable(
                "dbo.FriendRequests",
                c => new
                    {
                        friendRequestID = c.Int(nullable: false, identity: true),
                        user1_userID = c.Int(),
                        user2_userID = c.Int(),
                        game_gameID = c.Int(),
                    })
                .PrimaryKey(t => t.friendRequestID);
            
            CreateTable(
                "dbo.Games",
                c => new
                    {
                        gameID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                    })
                .PrimaryKey(t => t.gameID);
            
            CreateTable(
                "dbo.Profiles",
                c => new
                    {
                        profileID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                        lastName = c.String(),
                        nickname = c.String(),
                        birthday = c.DateTime(nullable: false),
                        country = c.String(),
                        phoneNumber = c.Int(nullable: false),
                        email = c.String(),
                        linkdinProfile = c.String(),
                        facebookProfice = c.String(),
                        twitterProfile = c.String(),
                        gender = c.String(),
                    })
                .PrimaryKey(t => t.profileID);
            
            CreateTable(
                "dbo.Missions",
                c => new
                    {
                        missionID = c.Int(nullable: false, identity: true),
                        description = c.String(),
                        level = c.Int(nullable: false),
                        User_userID = c.Int(),
                    })
                .PrimaryKey(t => t.missionID);
            
            CreateTable(
                "dbo.Notifications",
                c => new
                    {
                        notificationID = c.Int(nullable: false, identity: true),
                        message = c.String(),
                        time = c.DateTime(nullable: false),
                        User_userID = c.Int(),
                    })
                .PrimaryKey(t => t.notificationID);
            
            CreateTable(
                "dbo.ScoreUsers",
                c => new
                    {
                        scoreUserID = c.Int(nullable: false, identity: true),
                        User_userID = c.Int(),
                    })
                .PrimaryKey(t => t.scoreUserID);
            
            CreateTable(
                "dbo.Languages",
                c => new
                    {
                        languageID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                    })
                .PrimaryKey(t => t.languageID);
            
            CreateTable(
                "dbo.Users",
                c => new
                    {
                        userID = c.Int(nullable: false, identity: true),
                        active = c.Boolean(nullable: false),
                        language_languageID = c.Int(),
                        mood_moodID = c.Int(),
                        userProfile_profileID = c.Int(),
                    })
                .PrimaryKey(t => t.userID);
            
            CreateTable(
                "dbo.Connections",
                c => new
                    {
                        connectionID = c.Int(nullable: false, identity: true),
                        strenght = c.Int(nullable: false),
                        tagConnection_tagConnectionID = c.Int(),
                        userConnected_userID = c.Int(),
                    })
                .PrimaryKey(t => t.connectionID);
            
            CreateTable(
                "dbo.TagConnections",
                c => new
                    {
                        tagConnectionID = c.Int(nullable: false, identity: true),
                        tag = c.String(),
                    })
                .PrimaryKey(t => t.tagConnectionID);
            
            CreateIndex("dbo.IntroFriendRequests", "userC_userID");
            CreateIndex("dbo.IntroFriendRequests", "userB_userID");
            CreateIndex("dbo.IntroFriendRequests", "userA_userID");
            CreateIndex("dbo.FriendRequests", "game_gameID");
            CreateIndex("dbo.FriendRequests", "user2_userID");
            CreateIndex("dbo.FriendRequests", "user1_userID");
            CreateIndex("dbo.Missions", "User_userID");
            CreateIndex("dbo.Notifications", "User_userID");
            CreateIndex("dbo.ScoreUsers", "User_userID");
            CreateIndex("dbo.Users", "userProfile_profileID");
            CreateIndex("dbo.Users", "mood_moodID");
            CreateIndex("dbo.Users", "language_languageID");
            CreateIndex("dbo.Connections", "userConnected_userID");
            CreateIndex("dbo.Connections", "tagConnection_tagConnectionID");
            AddForeignKey("dbo.IntroFriendRequests", "userC_userID", "dbo.Users", "userID");
            AddForeignKey("dbo.IntroFriendRequests", "userB_userID", "dbo.Users", "userID");
            AddForeignKey("dbo.IntroFriendRequests", "userA_userID", "dbo.Users", "userID");
            AddForeignKey("dbo.FriendRequests", "game_gameID", "dbo.Games", "gameID");
            AddForeignKey("dbo.FriendRequests", "user2_userID", "dbo.Users", "userID");
            AddForeignKey("dbo.FriendRequests", "user1_userID", "dbo.Users", "userID");
            AddForeignKey("dbo.Missions", "User_userID", "dbo.Users", "userID");
            AddForeignKey("dbo.Notifications", "User_userID", "dbo.Users", "userID");
            AddForeignKey("dbo.ScoreUsers", "User_userID", "dbo.Users", "userID");
            AddForeignKey("dbo.Users", "userProfile_profileID", "dbo.Profiles", "profileID");
            AddForeignKey("dbo.Users", "mood_moodID", "dbo.Moods", "moodID");
            AddForeignKey("dbo.Users", "language_languageID", "dbo.Languages", "languageID");
            AddForeignKey("dbo.Connections", "userConnected_userID", "dbo.Users", "userID");
            AddForeignKey("dbo.Connections", "tagConnection_tagConnectionID", "dbo.TagConnections", "tagConnectionID");
        }
    }
}
