namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class rmImgNotification : DbMigration
    {
        public override void Up()
        {
            DropColumn("dbo.Notifications", "pathImg");
        }
        
        public override void Down()
        {
            AddColumn("dbo.Notifications", "pathImg", c => c.String());
        }
    }
}
