namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class mission : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Missions",
                c => new
                    {
                        missionID = c.Int(nullable: false, identity: true),
                        description = c.String(),
                        leval = c.Int(nullable: false),
                    })
                .PrimaryKey(t => t.missionID);
            
        }
        
        public override void Down()
        {
            DropTable("dbo.Missions");
        }
    }
}
