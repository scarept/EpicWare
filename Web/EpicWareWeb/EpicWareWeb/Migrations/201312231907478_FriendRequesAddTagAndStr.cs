namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class FriendRequesAddTagAndStr : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.FriendRequests", "strenght", c => c.Int(nullable: false));
            AddColumn("dbo.FriendRequests", "tagConnection_tagConnectionID", c => c.Int());
            AddForeignKey("dbo.FriendRequests", "tagConnection_tagConnectionID", "dbo.TagConnections", "tagConnectionID");
            CreateIndex("dbo.FriendRequests", "tagConnection_tagConnectionID");
        }
        
        public override void Down()
        {
            DropIndex("dbo.FriendRequests", new[] { "tagConnection_tagConnectionID" });
            DropForeignKey("dbo.FriendRequests", "tagConnection_tagConnectionID", "dbo.TagConnections");
            DropColumn("dbo.FriendRequests", "tagConnection_tagConnectionID");
            DropColumn("dbo.FriendRequests", "strenght");
        }
    }
}
