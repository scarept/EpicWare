namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class LanguageAddScoreUserAdd : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Languages",
                c => new
                    {
                        languageID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                    })
                .PrimaryKey(t => t.languageID);
            
            CreateTable(
                "dbo.ScoreUsers",
                c => new
                    {
                        scoreUserID = c.Int(nullable: false, identity: true),
                        User_userID = c.Int(),
                    })
                .PrimaryKey(t => t.scoreUserID)
                .ForeignKey("dbo.Users", t => t.User_userID)
                .Index(t => t.User_userID);
            
            AddColumn("dbo.Users", "language_languageID", c => c.Int());
            AddForeignKey("dbo.Users", "language_languageID", "dbo.Languages", "languageID");
            CreateIndex("dbo.Users", "language_languageID");
        }
        
        public override void Down()
        {
            DropIndex("dbo.ScoreUsers", new[] { "User_userID" });
            DropIndex("dbo.Users", new[] { "language_languageID" });
            DropForeignKey("dbo.ScoreUsers", "User_userID", "dbo.Users");
            DropForeignKey("dbo.Users", "language_languageID", "dbo.Languages");
            DropColumn("dbo.Users", "language_languageID");
            DropTable("dbo.ScoreUsers");
            DropTable("dbo.Languages");
        }
    }
}
