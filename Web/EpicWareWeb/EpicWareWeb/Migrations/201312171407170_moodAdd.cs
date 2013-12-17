namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class moodAdd : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Moods",
                c => new
                    {
                        moodID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                    })
                .PrimaryKey(t => t.moodID);
            
        }
        
        public override void Down()
        {
            DropTable("dbo.Moods");
        }
    }
}
