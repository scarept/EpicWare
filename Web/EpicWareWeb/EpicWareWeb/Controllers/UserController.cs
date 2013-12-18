using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using EpicWareWeb.Models;
using EpicWareWeb.DAL;
using WebMatrix.WebData;
using System.Web.Security;
using IDEIBiblio.Controllers;

namespace EpicWareWeb.Controllers
{
    public class UserController : Controller
    {
        private DataContext db = new DataContext();

        //
        // GET: /User/

        public ActionResult Index()
        {
            return View(db.users.ToList());
        }

        //
        // GET: /User/Details/5

        public ActionResult Details(int id = 0)
        {
            User user = db.users.Find(id);
            if (user == null)
            {
                return HttpNotFound();
            }
            return View(user);
        }

        //
        // GET: /User/Create

        public ActionResult Create()
        {
            return View();
        }

        //
        // POST: /User/Create

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create(User user, FormCollection collection)
        {
            RegisterModel reg_model_tmp = new RegisterModel();
            if (ModelState.IsValid)
            {
                
                reg_model_tmp.UserName = collection.Get("reg_mod.UserName");
                reg_model_tmp.Password = collection.Get("reg_mod.Password");
                reg_model_tmp.ConfirmPassword = collection.Get("reg_mod.ConfirmPassword");

                WebSecurity.CreateUserAndAccount(reg_model_tmp.UserName, reg_model_tmp.Password);
                WebSecurity.Login(reg_model_tmp.UserName, reg_model_tmp.Password);
                int id = WebSecurity.GetUserId(reg_model_tmp.UserName);
                user.UserProfileID = id;
                Roles.AddUserToRole(reg_model_tmp.UserName, "User");
                
            }
            if (ModelState.IsValid)
            {
                db.users.Add(user);
                db.SaveChanges();
                MailController mailSend = new MailController();
                mailSend.sendMail(user.email, "Registo de conta", "Username/Nikname: " + reg_model_tmp.UserName + "\nPassword: " +reg_model_tmp.Password);
                return RedirectToAction("Create", "Profile");
            }

            return View(user);
        }

        //
        // GET: /User/Edit/5

        public ActionResult Edit(int id = 0)
        {
            User user = db.users.Find(id);
            if (user == null)
            {
                return HttpNotFound();
            }
            return View(user);
        }

        //
        // POST: /User/Edit/5

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit(User user)
        {
            if (ModelState.IsValid)
            {
                db.Entry(user).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(user);
        }

        //
        // GET: /User/Delete/5

        public ActionResult Delete(int id = 0)
        {
            User user = db.users.Find(id);
            if (user == null)
            {
                return HttpNotFound();
            }
            return View(user);
        }

        //
        // POST: /User/Delete/5

        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            User user = db.users.Find(id);
            db.users.Remove(user);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }

        public User UserAutenticated()
        {
            try
            {
                int id_login;
                if (WebSecurity.Initialized)
                {
                    id_login = WebSecurity.CurrentUserId;
                }
                else
                {
                    WebSecurity.InitializeDatabaseConnection("DefaultConnection", "UserProfile", "UserId", "UserName", autoCreateTables: true);
                    id_login = WebSecurity.CurrentUserId;
                }
                var user = from d in db.users where d.UserProfileID == id_login select d;
                List<User> tempList = user.ToList();
                return tempList.ElementAt(0);
            }
            catch (Exception)
            {
                return null;
            }
        }
    }
}