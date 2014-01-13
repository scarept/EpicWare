namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class addRefLanguage : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.Languages", "reference", c => c.String());
        }
        
        public override void Down()
        {
            DropColumn("dbo.Languages", "reference");
        }
    }
}
