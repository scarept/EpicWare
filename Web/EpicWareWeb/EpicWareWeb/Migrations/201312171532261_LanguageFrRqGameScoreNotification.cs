namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class LanguageFrRqGameScoreNotification : DbMigration
    {
        public override void Up()
        {
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
                "dbo.Notifications",
                c => new
                    {
                        notificationID = c.Int(nullable: false, identity: true),
                        message = c.String(),
                        time = c.DateTime(nullable: false),
                    })
                .PrimaryKey(t => t.notificationID);
            
        }
        
        public override void Down()
        {
            DropIndex("dbo.FriendRequests", new[] { "game_gameID" });
            DropIndex("dbo.FriendRequests", new[] { "user2_userID" });
            DropIndex("dbo.FriendRequests", new[] { "user1_userID" });
            DropForeignKey("dbo.FriendRequests", "game_gameID", "dbo.Games");
            DropForeignKey("dbo.FriendRequests", "user2_userID", "dbo.Users");
            DropForeignKey("dbo.FriendRequests", "user1_userID", "dbo.Users");
            DropTable("dbo.Notifications");
            DropTable("dbo.FriendRequests");
            DropTable("dbo.Games");
        }
    }
}
