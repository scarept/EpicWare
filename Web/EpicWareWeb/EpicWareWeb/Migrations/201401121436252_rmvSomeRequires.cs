namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class rmvSomeRequires : DbMigration
    {
        public override void Up()
        {
            AlterColumn("dbo.Profiles", "name", c => c.String());
            AlterColumn("dbo.Profiles", "lastName", c => c.String());
            AlterColumn("dbo.Profiles", "nickname", c => c.String());
        }
        
        public override void Down()
        {
            AlterColumn("dbo.Profiles", "nickname", c => c.String(nullable: false));
            AlterColumn("dbo.Profiles", "lastName", c => c.String(nullable: false));
            AlterColumn("dbo.Profiles", "name", c => c.String(nullable: false));
        }
    }
}
