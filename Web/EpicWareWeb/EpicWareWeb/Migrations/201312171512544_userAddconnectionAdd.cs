namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class userAddconnectionAdd : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Connections",
                c => new
                    {
                        connectionID = c.Int(nullable: false, identity: true),
                        strenght = c.Int(nullable: false),
                        tagConnection_tagConnectionID = c.Int(),
                        userConnected_userID = c.Int(),
                    })
                .PrimaryKey(t => t.connectionID)
                .ForeignKey("dbo.TagConnections", t => t.tagConnection_tagConnectionID)
                .ForeignKey("dbo.Users", t => t.userConnected_userID)
                .Index(t => t.tagConnection_tagConnectionID)
                .Index(t => t.userConnected_userID);
            
            CreateTable(
                "dbo.Users",
                c => new
                    {
                        userID = c.Int(nullable: false, identity: true),
                        active = c.Boolean(nullable: false),
                    })
                .PrimaryKey(t => t.userID);
            
        }
        
        public override void Down()
        {
            DropIndex("dbo.Connections", new[] { "userConnected_userID" });
            DropIndex("dbo.Connections", new[] { "tagConnection_tagConnectionID" });
            DropForeignKey("dbo.Connections", "userConnected_userID", "dbo.Users");
            DropForeignKey("dbo.Connections", "tagConnection_tagConnectionID", "dbo.TagConnections");
            DropTable("dbo.Users");
            DropTable("dbo.Connections");
        }
    }
}
