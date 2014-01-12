namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class updSomeRequireds : DbMigration
    {
        public override void Up()
        {
            DropForeignKey("dbo.Users", "language_languageID", "dbo.Languages");
            DropIndex("dbo.Users", new[] { "language_languageID" });
            AlterColumn("dbo.Users", "email", c => c.String(nullable: false));
            AlterColumn("dbo.Users", "language_languageID", c => c.Int(nullable: false));
            AlterColumn("dbo.Profiles", "name", c => c.String(nullable: false));
            AlterColumn("dbo.Profiles", "lastName", c => c.String(nullable: false));
            AlterColumn("dbo.Profiles", "nickname", c => c.String(nullable: false));
            AddForeignKey("dbo.Users", "language_languageID", "dbo.Languages", "languageID", cascadeDelete: true);
            CreateIndex("dbo.Users", "language_languageID");
        }
        
        public override void Down()
        {
            DropIndex("dbo.Users", new[] { "language_languageID" });
            DropForeignKey("dbo.Users", "language_languageID", "dbo.Languages");
            AlterColumn("dbo.Profiles", "nickname", c => c.String());
            AlterColumn("dbo.Profiles", "lastName", c => c.String());
            AlterColumn("dbo.Profiles", "name", c => c.String());
            AlterColumn("dbo.Users", "language_languageID", c => c.Int());
            AlterColumn("dbo.Users", "email", c => c.String());
            CreateIndex("dbo.Users", "language_languageID");
            AddForeignKey("dbo.Users", "language_languageID", "dbo.Languages", "languageID");
        }
    }
}
