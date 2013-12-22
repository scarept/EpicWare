namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class newDBEpic2 : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Moods",
                c => new
                    {
                        moodID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                    })
                .PrimaryKey(t => t.moodID);
            
            CreateTable(
                "dbo.TagConnections",
                c => new
                    {
                        tagConnectionID = c.Int(nullable: false, identity: true),
                        tag = c.String(),
                    })
                .PrimaryKey(t => t.tagConnectionID);
            
            CreateTable(
                "dbo.Connections",
                c => new
                    {
                        connectionID = c.Int(nullable: false, identity: true),
                        strenght = c.Int(nullable: false),
                        User_userID = c.Int(),
                        Owner_userID = c.Int(),
                        tagConnection_tagConnectionID = c.Int(),
                        userConnected_userID = c.Int(),
                    })
                .PrimaryKey(t => t.connectionID)
                .ForeignKey("dbo.Users", t => t.User_userID)
                .ForeignKey("dbo.Users", t => t.Owner_userID)
                .ForeignKey("dbo.TagConnections", t => t.tagConnection_tagConnectionID)
                .ForeignKey("dbo.Users", t => t.userConnected_userID)
                .Index(t => t.User_userID)
                .Index(t => t.Owner_userID)
                .Index(t => t.tagConnection_tagConnectionID)
                .Index(t => t.userConnected_userID);
            
            CreateTable(
                "dbo.Users",
                c => new
                    {
                        userID = c.Int(nullable: false, identity: true),
                        UserProfileID = c.Int(nullable: false),
                        email = c.String(),
                        active = c.Boolean(nullable: false),
                        language_languageID = c.Int(),
                        mood_moodID = c.Int(),
                        userProfile_profileID = c.Int(),
                    })
                .PrimaryKey(t => t.userID)
                .ForeignKey("dbo.Languages", t => t.language_languageID)
                .ForeignKey("dbo.Moods", t => t.mood_moodID)
                .ForeignKey("dbo.Profiles", t => t.userProfile_profileID)
                .Index(t => t.language_languageID)
                .Index(t => t.mood_moodID)
                .Index(t => t.userProfile_profileID);
            
            CreateTable(
                "dbo.Languages",
                c => new
                    {
                        languageID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                    })
                .PrimaryKey(t => t.languageID);
            
            CreateTable(
                "dbo.ScoreUsers",
                c => new
                    {
                        scoreUserID = c.Int(nullable: false, identity: true),
                        User_userID = c.Int(),
                    })
                .PrimaryKey(t => t.scoreUserID)
                .ForeignKey("dbo.Users", t => t.User_userID)
                .Index(t => t.User_userID);
            
            CreateTable(
                "dbo.Notifications",
                c => new
                    {
                        notificationID = c.Int(nullable: false, identity: true),
                        pathImg = c.String(),
                        message = c.String(),
                        time = c.DateTime(nullable: false),
                        User_userID = c.Int(),
                    })
                .PrimaryKey(t => t.notificationID)
                .ForeignKey("dbo.Users", t => t.User_userID)
                .Index(t => t.User_userID);
            
            CreateTable(
                "dbo.Missions",
                c => new
                    {
                        missionID = c.Int(nullable: false, identity: true),
                        description = c.String(),
                        level = c.Int(nullable: false),
                        User_userID = c.Int(),
                    })
                .PrimaryKey(t => t.missionID)
                .ForeignKey("dbo.Users", t => t.User_userID)
                .Index(t => t.User_userID);
            
            CreateTable(
                "dbo.Profiles",
                c => new
                    {
                        profileID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                        lastName = c.String(),
                        nickname = c.String(),
                        birthday = c.DateTime(nullable: false),
                        phoneNumber = c.Int(nullable: false),
                        linkedinProfile = c.String(),
                        facebookProfile = c.String(),
                        twitterProfile = c.String(),
                        gender = c.String(),
                        pathImg = c.String(),
                        country_countryID = c.Int(),
                    })
                .PrimaryKey(t => t.profileID)
                .ForeignKey("dbo.Countries", t => t.country_countryID)
                .Index(t => t.country_countryID);
            
            CreateTable(
                "dbo.Countries",
                c => new
                    {
                        countryID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                    })
                .PrimaryKey(t => t.countryID);
            
            CreateTable(
                "dbo.Games",
                c => new
                    {
                        gameID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                    })
                .PrimaryKey(t => t.gameID);
            
            CreateTable(
                "dbo.FriendRequests",
                c => new
                    {
                        friendRequestID = c.Int(nullable: false, identity: true),
                        user1_userID = c.Int(),
                        user2_userID = c.Int(),
                        game_gameID = c.Int(),
                    })
                .PrimaryKey(t => t.friendRequestID)
                .ForeignKey("dbo.Users", t => t.user1_userID)
                .ForeignKey("dbo.Users", t => t.user2_userID)
                .ForeignKey("dbo.Games", t => t.game_gameID)
                .Index(t => t.user1_userID)
                .Index(t => t.user2_userID)
                .Index(t => t.game_gameID);
            
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
                .PrimaryKey(t => t.introFriendRequestID)
                .ForeignKey("dbo.Users", t => t.userA_userID)
                .ForeignKey("dbo.Users", t => t.userB_userID)
                .ForeignKey("dbo.Users", t => t.userC_userID)
                .Index(t => t.userA_userID)
                .Index(t => t.userB_userID)
                .Index(t => t.userC_userID);
            
        }
        
        public override void Down()
        {
            DropIndex("dbo.IntroFriendRequests", new[] { "userC_userID" });
            DropIndex("dbo.IntroFriendRequests", new[] { "userB_userID" });
            DropIndex("dbo.IntroFriendRequests", new[] { "userA_userID" });
            DropIndex("dbo.FriendRequests", new[] { "game_gameID" });
            DropIndex("dbo.FriendRequests", new[] { "user2_userID" });
            DropIndex("dbo.FriendRequests", new[] { "user1_userID" });
            DropIndex("dbo.Profiles", new[] { "country_countryID" });
            DropIndex("dbo.Missions", new[] { "User_userID" });
            DropIndex("dbo.Notifications", new[] { "User_userID" });
            DropIndex("dbo.ScoreUsers", new[] { "User_userID" });
            DropIndex("dbo.Users", new[] { "userProfile_profileID" });
            DropIndex("dbo.Users", new[] { "mood_moodID" });
            DropIndex("dbo.Users", new[] { "language_languageID" });
            DropIndex("dbo.Connections", new[] { "userConnected_userID" });
            DropIndex("dbo.Connections", new[] { "tagConnection_tagConnectionID" });
            DropIndex("dbo.Connections", new[] { "Owner_userID" });
            DropIndex("dbo.Connections", new[] { "User_userID" });
            DropForeignKey("dbo.IntroFriendRequests", "userC_userID", "dbo.Users");
            DropForeignKey("dbo.IntroFriendRequests", "userB_userID", "dbo.Users");
            DropForeignKey("dbo.IntroFriendRequests", "userA_userID", "dbo.Users");
            DropForeignKey("dbo.FriendRequests", "game_gameID", "dbo.Games");
            DropForeignKey("dbo.FriendRequests", "user2_userID", "dbo.Users");
            DropForeignKey("dbo.FriendRequests", "user1_userID", "dbo.Users");
            DropForeignKey("dbo.Profiles", "country_countryID", "dbo.Countries");
            DropForeignKey("dbo.Missions", "User_userID", "dbo.Users");
            DropForeignKey("dbo.Notifications", "User_userID", "dbo.Users");
            DropForeignKey("dbo.ScoreUsers", "User_userID", "dbo.Users");
            DropForeignKey("dbo.Users", "userProfile_profileID", "dbo.Profiles");
            DropForeignKey("dbo.Users", "mood_moodID", "dbo.Moods");
            DropForeignKey("dbo.Users", "language_languageID", "dbo.Languages");
            DropForeignKey("dbo.Connections", "userConnected_userID", "dbo.Users");
            DropForeignKey("dbo.Connections", "tagConnection_tagConnectionID", "dbo.TagConnections");
            DropForeignKey("dbo.Connections", "Owner_userID", "dbo.Users");
            DropForeignKey("dbo.Connections", "User_userID", "dbo.Users");
            DropTable("dbo.IntroFriendRequests");
            DropTable("dbo.FriendRequests");
            DropTable("dbo.Games");
            DropTable("dbo.Countries");
            DropTable("dbo.Profiles");
            DropTable("dbo.Missions");
            DropTable("dbo.Notifications");
            DropTable("dbo.ScoreUsers");
            DropTable("dbo.Languages");
            DropTable("dbo.Users");
            DropTable("dbo.Connections");
            DropTable("dbo.TagConnections");
            DropTable("dbo.Moods");
        }
    }
}
