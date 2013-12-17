namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class UserLanguageEtcUpdt : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Languages",
                c => new
                    {
                        languageID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                    })
                .PrimaryKey(t => t.languageID);
            
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
            
            AddColumn("dbo.Users", "language_languageID", c => c.Int());
            AddForeignKey("dbo.Users", "language_languageID", "dbo.Languages", "languageID");
            CreateIndex("dbo.Users", "language_languageID");
        }
        
        public override void Down()
        {
            DropIndex("dbo.IntroFriendRequests", new[] { "userC_userID" });
            DropIndex("dbo.IntroFriendRequests", new[] { "userB_userID" });
            DropIndex("dbo.IntroFriendRequests", new[] { "userA_userID" });
            DropIndex("dbo.Missions", new[] { "User_userID" });
            DropIndex("dbo.Users", new[] { "language_languageID" });
            DropForeignKey("dbo.IntroFriendRequests", "userC_userID", "dbo.Users");
            DropForeignKey("dbo.IntroFriendRequests", "userB_userID", "dbo.Users");
            DropForeignKey("dbo.IntroFriendRequests", "userA_userID", "dbo.Users");
            DropForeignKey("dbo.Missions", "User_userID", "dbo.Users");
            DropForeignKey("dbo.Users", "language_languageID", "dbo.Languages");
            DropColumn("dbo.Users", "language_languageID");
            DropTable("dbo.IntroFriendRequests");
            DropTable("dbo.Missions");
            DropTable("dbo.Languages");
        }
    }
}
