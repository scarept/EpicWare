namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class addCountry : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Countries",
                c => new
                    {
                        countryID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                    })
                .PrimaryKey(t => t.countryID);
            
            AddColumn("dbo.Profiles", "country_countryID", c => c.Int());
            AddForeignKey("dbo.Profiles", "country_countryID", "dbo.Countries", "countryID");
            CreateIndex("dbo.Profiles", "country_countryID");
            DropColumn("dbo.Profiles", "country");
        }
        
        public override void Down()
        {
            AddColumn("dbo.Profiles", "country", c => c.String());
            DropIndex("dbo.Profiles", new[] { "country_countryID" });
            DropForeignKey("dbo.Profiles", "country_countryID", "dbo.Countries");
            DropColumn("dbo.Profiles", "country_countryID");
            DropTable("dbo.Countries");
        }
    }
}
