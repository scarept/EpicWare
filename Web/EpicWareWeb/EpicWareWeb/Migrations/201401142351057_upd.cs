namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class upd : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.Missions", "currentLeavel", c => c.Int(nullable: false));
            AddColumn("dbo.Missions", "finalLeavel", c => c.Int(nullable: false));
            DropColumn("dbo.Missions", "currentLevel");
            DropColumn("dbo.Missions", "finalLevel");
        }
        
        public override void Down()
        {
            AddColumn("dbo.Missions", "finalLevel", c => c.Int(nullable: false));
            AddColumn("dbo.Missions", "currentLevel", c => c.Int(nullable: false));
            DropColumn("dbo.Missions", "finalLeavel");
            DropColumn("dbo.Missions", "currentLeavel");
        }
    }
}
