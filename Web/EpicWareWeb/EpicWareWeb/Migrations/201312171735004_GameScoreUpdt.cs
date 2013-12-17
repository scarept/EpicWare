namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class GameScoreUpdt : DbMigration
    {
        public override void Up()
        {
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
            
            CreateTable(
                "dbo.Games",
                c => new
                    {
                        gameID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                    })
                .PrimaryKey(t => t.gameID);
            
        }
        
        public override void Down()
        {
            DropIndex("dbo.ScoreUsers", new[] { "User_userID" });
            DropForeignKey("dbo.ScoreUsers", "User_userID", "dbo.Users");
            DropTable("dbo.Games");
            DropTable("dbo.ScoreUsers");
        }
    }
}
