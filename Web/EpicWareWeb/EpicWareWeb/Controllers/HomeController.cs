using EpicWareWeb.DAL;
using EpicWareWeb.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace EpicWareWeb.Controllers
{
    public class HomeController : Controller
    {
        DataContext db = new DataContext();
        public ActionResult Index()
        {
            ViewBag.Message = "Modify this template to jump-start your ASP.NET MVC application.";
            
            /*View Bag whit number of active users on website*/
            List<User> users = db.users.ToList();
            int count = 0;
            foreach(User user in users)
            {
                if(user.active)
                    count++;

            }
            ViewBag.numberUsers = count;

            /*TagCloudAllUsers*/
            List<string> newListTags = new List<string>();
            foreach(Tag tag in db.tags.ToList())
            {
                newListTags.Add(tag.tag);
            }
            ViewBag.allTagUsers = newListTags;

            /*TagCloudConnection*/
            List<string> newListTagsConnection = new List<string>();
            foreach(TagConnection tag in db.tagConnections)
            {
                newListTagsConnection.Add(tag.tag);
            }
            ViewBag.allTagsConnection = newListTagsConnection;

            return View();
        }

        //public ActionResult About()
        //{
        //    ViewBag.Message = "Your app description page.";

        //    return View();
        //}

        //public ActionResult Contact()
        //{
        //    ViewBag.Message = "Your contact page.";

        //    return View();
        //}
    }
}
