namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class downLoadAdd : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Downloads",
                c => new
                    {
                        downloadID = c.Int(nullable: false, identity: true),
                        time = c.DateTime(nullable: false),
                    })
                .PrimaryKey(t => t.downloadID);
            
        }
        
        public override void Down()
        {
            DropTable("dbo.Downloads");
        }
    }
}
