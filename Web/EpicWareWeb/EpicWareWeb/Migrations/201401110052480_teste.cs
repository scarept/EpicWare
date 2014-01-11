namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class teste : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.ScoreUsers", "points", c => c.Int(nullable: false));
            AddColumn("dbo.ScoreUsers", "MyProperty_gameID", c => c.Int());
            AddForeignKey("dbo.ScoreUsers", "MyProperty_gameID", "dbo.Games", "gameID");
            CreateIndex("dbo.ScoreUsers", "MyProperty_gameID");
        }
        
        public override void Down()
        {
            DropIndex("dbo.ScoreUsers", new[] { "MyProperty_gameID" });
            DropForeignKey("dbo.ScoreUsers", "MyProperty_gameID", "dbo.Games");
            DropColumn("dbo.ScoreUsers", "MyProperty_gameID");
            DropColumn("dbo.ScoreUsers", "points");
        }
    }
}
