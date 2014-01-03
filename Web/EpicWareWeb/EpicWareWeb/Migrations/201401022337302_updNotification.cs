namespace EpicWareWeb.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class updNotification : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.NotificationTypes",
                c => new
                    {
                        notificationTypeID = c.Int(nullable: false, identity: true),
                        type = c.String(),
                        resultLink = c.String(),
                    })
                .PrimaryKey(t => t.notificationTypeID);
            
            AddColumn("dbo.Notifications", "read", c => c.Boolean(nullable: false));
            AddColumn("dbo.Notifications", "notificationType_notificationTypeID", c => c.Int());
            AddForeignKey("dbo.Notifications", "notificationType_notificationTypeID", "dbo.NotificationTypes", "notificationTypeID");
            CreateIndex("dbo.Notifications", "notificationType_notificationTypeID");
        }
        
        public override void Down()
        {
            DropIndex("dbo.Notifications", new[] { "notificationType_notificationTypeID" });
            DropForeignKey("dbo.Notifications", "notificationType_notificationTypeID", "dbo.NotificationTypes");
            DropColumn("dbo.Notifications", "notificationType_notificationTypeID");
            DropColumn("dbo.Notifications", "read");
            DropTable("dbo.NotificationTypes");
        }
    }
}
