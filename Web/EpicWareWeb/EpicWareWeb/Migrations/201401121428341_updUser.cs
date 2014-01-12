namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class updUser : DbMigration
    {
        public override void Up()
        {
            AlterColumn("dbo.Profiles", "name", c => c.String(nullable: false));
            AlterColumn("dbo.Profiles", "lastName", c => c.String(nullable: false));
            AlterColumn("dbo.Profiles", "nickname", c => c.String(nullable: false));
        }
        
        public override void Down()
        {
            AlterColumn("dbo.Profiles", "nickname", c => c.String());
            AlterColumn("dbo.Profiles", "lastName", c => c.String());
            AlterColumn("dbo.Profiles", "name", c => c.String());
        }
    }
}
