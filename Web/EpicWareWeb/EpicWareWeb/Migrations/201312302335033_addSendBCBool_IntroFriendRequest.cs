namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class addSendBCBool_IntroFriendRequest : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.IntroFriendRequests", "sendedBC", c => c.Boolean(nullable: false));
        }
        
        public override void Down()
        {
            DropColumn("dbo.IntroFriendRequests", "sendedBC");
        }
    }
}
