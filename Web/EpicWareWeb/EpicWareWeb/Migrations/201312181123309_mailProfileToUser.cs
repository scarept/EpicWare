namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class mailProfileToUser : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.Users", "email", c => c.String());
            DropColumn("dbo.Profiles", "email");
        }
        
        public override void Down()
        {
            AddColumn("dbo.Profiles", "email", c => c.String());
            DropColumn("dbo.Users", "email");
        }
    }
}
