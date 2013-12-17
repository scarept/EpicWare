namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class tagConnUpd : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.TagConnections",
                c => new
                    {
                        tagConnectionID = c.Int(nullable: false, identity: true),
                        tag = c.String(),
                    })
                .PrimaryKey(t => t.tagConnectionID);
            
        }
        
        public override void Down()
        {
            DropTable("dbo.TagConnections");
        }
    }
}
