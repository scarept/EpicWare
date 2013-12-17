namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class missionUpdt : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Profiles",
                c => new
                    {
                        profileID = c.Int(nullable: false, identity: true),
                        name = c.String(),
                        lastName = c.String(),
                        nickname = c.String(),
                        birthday = c.DateTime(nullable: false),
                        country = c.String(),
                        phoneNumber = c.Int(nullable: false),
                        email = c.String(),
                        linkdinProfile = c.String(),
                        facebookProfice = c.String(),
                        twitterProfile = c.String(),
                        gender = c.String(),
                    })
                .PrimaryKey(t => t.profileID);
            
            AddColumn("dbo.Missions", "level", c => c.Int(nullable: false));
            DropColumn("dbo.Missions", "leval");
        }
        
        public override void Down()
        {
            AddColumn("dbo.Missions", "leval", c => c.Int(nullable: false));
            DropColumn("dbo.Missions", "level");
            DropTable("dbo.Profiles");
        }
    }
}
