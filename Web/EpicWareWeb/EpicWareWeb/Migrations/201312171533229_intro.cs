namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class intro : DbMigration
    {
        public override void Up()
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
            DropForeignKey("dbo.IntroFriendRequests", "userC_userID", "dbo.Users");
            DropForeignKey("dbo.IntroFriendRequests", "userB_userID", "dbo.Users");
            DropForeignKey("dbo.IntroFriendRequests", "userA_userID", "dbo.Users");
            DropTable("dbo.IntroFriendRequests");
        }
    }
}
