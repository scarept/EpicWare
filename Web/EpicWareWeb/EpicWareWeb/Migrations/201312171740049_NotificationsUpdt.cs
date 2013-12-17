namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class NotificationsUpdt : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.Notifications", "pathImg", c => c.String());
        }
        
        public override void Down()
        {
            DropColumn("dbo.Notifications", "pathImg");
        }
    }
}
