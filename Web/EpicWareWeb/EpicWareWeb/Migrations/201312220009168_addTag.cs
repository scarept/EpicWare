namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class addTag : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Tags",
                c => new
                    {
                        tagID = c.Int(nullable: false, identity: true),
                        tag = c.String(),
                        User_userID = c.Int(),
                    })
                .PrimaryKey(t => t.tagID)
                .ForeignKey("dbo.Users", t => t.User_userID)
                .Index(t => t.User_userID);
            
        }
        
        public override void Down()
        {
            DropIndex("dbo.Tags", new[] { "User_userID" });
            DropForeignKey("dbo.Tags", "User_userID", "dbo.Users");
            DropTable("dbo.Tags");
        }
    }
}
