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
            //ViewBag.Message = "Modify this template to jump-start your ASP.NET MVC application.";
            
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

        [Authorize]
        
        [ValidateAntiForgeryToken]
        public ActionResult Search(FormCollection collection)
        {
            string txt = collection.Get("pesquisa").ToLower();
            string[] txtA = txt.Split(new Char[] { ' ' });
            List<User> users = new List<User>();

            foreach(User user in db.users.ToList())
            {
                bool inserido = false;
                if (matchWords(user, txtA))
                {
                    if (!users.Contains(user))
                    {
                        users.Add(user);
                        inserido = true;
                    }
                    
                }
                if(!inserido)
                {
                    foreach(Tag tag in user.userTags)
                    {
                        if (matchWords(tag, txtA))
                        {
                            if (!users.Contains(user))
                            {
                                users.Add(user);
                                inserido = true;
                            }
                        }
                    }
                }
                    
            }


            return View(users);
        }

        
        private bool matchWords(User user, string[] txtA)
        {
            string[] txtFirstName = user.userProfile.name.ToLower().Split(new Char[] { ' ' });
            string[] txtLasttName = user.userProfile.lastName.ToLower().Split(new Char[] { ' ' });

            foreach(string item in txtA)
            {
                if (txtFirstName.Contains(item) || txtLasttName.Contains(item) || user.userProfile.nickname.Contains(item))
                {
                    return true;
                }
            }
            return false;

        }
        private bool matchWords(Tag tag, string[] txtA)
        {
            foreach (string item in txtA)
            {
                if (item.ToLower() == tag.tag.ToLower())
                {
                    return true;
                }
            }
            return false;
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
