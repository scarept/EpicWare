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
using EpicWareWeb.Filters;
using System.IO;

namespace EpicWareWeb.Controllers
{
    public class UserController : Controller
    {
        private DataContext db = new DataContext();

        
         //GET: /User/

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
            fillLanguagesList();
            User user = new User();
            user.userProfile = new Profile();
            return View(user);
        }

        //
        // POST: /User/Create

        [HttpPost]
        [ValidateAntiForgeryToken]
        [InitializeSimpleMembership]
        public ActionResult Create(User user, FormCollection collection, string langSelect)
        {
            RegisterModel reg_model_tmp = new RegisterModel();
            if (ModelState.IsValid)
            {
                try
                {
                    Language lang = db.languages.Find(Convert.ToInt32(langSelect));
                    user.language = lang;
                }
                catch (Exception){}
                
                reg_model_tmp.UserName = collection.Get("reg_mod.UserName");
                reg_model_tmp.Password = collection.Get("reg_mod.Password");
                reg_model_tmp.ConfirmPassword = collection.Get("reg_mod.ConfirmPassword");
                user.userProfile.birthday = new DateTime(1900, 01, 01);
                user.userProfile.nickname = reg_model_tmp.UserName;
                Mood mood = db.moods.Find(2); // Default is normal
                user.mood = mood;
                user.active = true;
                db.users.Add(user);
                db.SaveChanges();
                MailController mailSend = new MailController();
                mailSend.sendMail(user.email, "Registo de conta", "Username/Nikname: " + reg_model_tmp.UserName + "\nPassword: " + reg_model_tmp.Password);
                //if (!WebSecurity.Initialized)
                //{
                //    new AccountController().InitilizeBdAccounts();
                //}
                WebSecurity.CreateUserAndAccount(reg_model_tmp.UserName, reg_model_tmp.Password);
                WebSecurity.Login(reg_model_tmp.UserName, reg_model_tmp.Password);
                int id = WebSecurity.GetUserId(reg_model_tmp.UserName);

                user.UserProfileID = id;
                db.Entry(user).State = EntityState.Modified;
                db.SaveChanges();
                Roles.AddUserToRole(reg_model_tmp.UserName, "User");
                return RedirectToAction("CreateProfile");
            }

            return View(user);
        }

        /* EDIT METHODS */

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
        // GET: /User/EditProfile/5
        public ActionResult CreateProfile()
        {
            User user = UserAutenticated();
            ViewBag.profileSend = user.userProfile;
            ViewBag.userAuth = user;
            fillsDropDownListCountry();
            fillsDropDownListGenders();
            return View(user);
        }

        //
        // POST: /User/EditProfile/5

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult CreateProfile(FormCollection collection, string naturalSelect, string genderSelect, HttpPostedFileBase file)
        {
            User userAuth = UserAutenticated();
            
            /* BIRTHDAY */
            string data = collection.Get("MyDate");
            string[] arrData = data.Split('/');
            int year = Convert.ToInt32(arrData.ElementAt(2));
            int month = Convert.ToInt32(arrData.ElementAt(0));
            int day = Convert.ToInt32(arrData.ElementAt(1));
            userAuth.userProfile.birthday = new DateTime(year, month, day);

            /* PHONE */
            string phone = collection.Get("profile.phoneNumber");
            int phoneNumber = Convert.ToInt32(phone);
            userAuth.userProfile.phoneNumber = phoneNumber;

            /* USERTAGS */
            string tags = collection.Get("tags");
            string[] tagsV = tags.Split(',');
            if (userAuth.userTags == null)
            {
                userAuth.userTags = new List<Tag>();
            }
            foreach (string tag in tagsV)
            {
                Tag t = new Tag();
                t.tag = tag;
                userAuth.userTags.Add(t);
            }

            /* SOCIAL NETWORKS*/
            string linkedin = collection.Get("profile.linkedinProfile");
            userAuth.userProfile.linkedinProfile = linkedin;
            string facebook = collection.Get("profile.facebookProfile");
            userAuth.userProfile.facebookProfile = facebook;
            string twitter = collection.Get("profile.twitterProfile");
            userAuth.userProfile.twitterProfile = twitter;

            /* COUNTRY */
            Country country = db.countrys.Find(Convert.ToInt32(naturalSelect));
            userAuth.userProfile.country = country;

            /* GENDER */
            if (genderSelect == EpicWareWeb.Views.User.User.masculino)
            {
                userAuth.userProfile.gender = "M";
            }else{
                userAuth.userProfile.gender = "F";
            }
            /* PROFILE IMAGE */
            if (file != null)
            {
                // Get extention
                string[] ext = file.FileName.Split('.');
                string extention = ext.ElementAt(ext.Count() - 1);
                
                string pic = userAuth.userID + "." + extention;
                string path = Path.Combine(Server.MapPath("~/Images/Profiles/"), pic);

                file.SaveAs(path);
                userAuth.userProfile.pathImg = "/Images/Profiles/" + pic;
            }

            if (ModelState.IsValid)
            {
                db.Entry(userAuth).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            
            return View();
        }

        public ActionResult Profile()
        {
            return View();
        }

        //
        // GET: /User/Delete/5

        //public ActionResult Delete(int id = 0)
        //{
        //    User user = db.users.Find(id);
        //    if (user == null)
        //    {
        //        return HttpNotFound();
        //    }
        //    return View(user);
        //}

        ////
        //// POST: /User/Delete/5

        //[HttpPost, ActionName("Delete")]
        //[ValidateAntiForgeryToken]
        //public ActionResult DeleteConfirmed(int id)
        //{
        //    User user = db.users.Find(id);
        //    db.users.Remove(user);
        //    db.SaveChanges();
        //    return RedirectToAction("Index");
        //}

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

        private void fillLanguagesList(object selectedLanguage = null)
        {
            var languageQuery = from d in db.languages
                                select d;
            var selectList = new SelectList(languageQuery, "languageID", "name", selectedLanguage);
            ViewBag.linguagens = selectList;
        }

        private void fillsDropDownListCountry(object selectedCountry = null)
        {
            var coutrysQuery = from d in db.countrys
                               select d;

            var selectList = new SelectList(coutrysQuery, "countryID", "name", selectedCountry);
            ViewBag.naturalidades = selectList;
        }

        private void fillsDropDownListGenders(object selectedGender = null)
        {
            List<string> gendersList = new List<string>();
            gendersList.Add(EpicWareWeb.Views.User.User.masculino);
            gendersList.Add(EpicWareWeb.Views.User.User.feminino);

            var selectList = new SelectList(gendersList);
            ViewBag.genders = selectList;
        }

    }
}