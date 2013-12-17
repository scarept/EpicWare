namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class userUpdt : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.Users", "UserProfileID", c => c.Int(nullable: false));
        }
        
        public override void Down()
        {
            DropColumn("dbo.Users", "UserProfileID");
        }
    }
}
