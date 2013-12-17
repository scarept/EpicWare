namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class ProfileUpdt : DbMigration
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
                        pathImg = c.String(),
                    })
                .PrimaryKey(t => t.profileID);
            
            AddColumn("dbo.Users", "userProfile_profileID", c => c.Int());
            AddForeignKey("dbo.Users", "userProfile_profileID", "dbo.Profiles", "profileID");
            CreateIndex("dbo.Users", "userProfile_profileID");
        }
        
        public override void Down()
        {
            DropIndex("dbo.Users", new[] { "userProfile_profileID" });
            DropForeignKey("dbo.Users", "userProfile_profileID", "dbo.Profiles");
            DropColumn("dbo.Users", "userProfile_profileID");
            DropTable("dbo.Profiles");
        }
    }
}
