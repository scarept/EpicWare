namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class updProfileFacLink : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.Profiles", "linkedinProfile", c => c.String());
            AddColumn("dbo.Profiles", "facebookProfile", c => c.String());
            DropColumn("dbo.Profiles", "linkdinProfile");
            DropColumn("dbo.Profiles", "facebookProfice");
        }
        
        public override void Down()
        {
            AddColumn("dbo.Profiles", "facebookProfice", c => c.String());
            AddColumn("dbo.Profiles", "linkdinProfile", c => c.String());
            DropColumn("dbo.Profiles", "facebookProfile");
            DropColumn("dbo.Profiles", "linkedinProfile");
        }
    }
}
