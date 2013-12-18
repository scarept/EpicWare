using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using EpicWareWeb.Models;
using EpicWareWeb.DAL;

namespace EpicWareWeb.Controllers
{
    public class ProfileController : Controller
    {
        private DataContext db = new DataContext();

        //
        // GET: /Profile/

        public ActionResult Index()
        {
            return View(db.Profiles.ToList());
        }

        //
        // GET: /Profile/Details/5

        public ActionResult Details(int id = 0)
        {
            Profile profile = db.Profiles.Find(id);
            if (profile == null)
            {
                return HttpNotFound();
            }
            return View(profile);
        }

        //
        // GET: /Profile/Create

        public ActionResult Create()
        {
            fillsDropDownList();
            return View();
        }

        //
        // POST: /Profile/Create

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create(Profile profile)
        {
            UserController usrCtr = new UserController();
            User user = usrCtr.UserAutenticated();
            user.userProfile.birthday = new DateTime();
            user.userProfile.birthday = profile.birthday;
            user.userProfile.country = profile.country;
            user.userProfile.facebookProfile = profile.facebookProfile;
            user.userProfile.gender = profile.gender;
            user.userProfile.linkedinProfile = profile.linkedinProfile;
            user.userProfile.phoneNumber = profile.phoneNumber;
            user.userProfile.twitterProfile = profile.twitterProfile;

            if (ModelState.IsValid)
            {
                db.Entry(user).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index","Home");
            }

            return View(profile);
        }

        //
        // GET: /Profile/Edit/5

        public ActionResult Edit(int id = 0)
        {
            Profile profile = db.Profiles.Find(id);
            if (profile == null)
            {
                return HttpNotFound();
            }
            return View(profile);
        }

        //
        // POST: /Profile/Edit/5

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit(Profile profile)
        {
            if (ModelState.IsValid)
            {
                db.Entry(profile).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(profile);
        }

        //
        // GET: /Profile/Delete/5

        public ActionResult Delete(int id = 0)
        {
            Profile profile = db.Profiles.Find(id);
            if (profile == null)
            {
                return HttpNotFound();
            }
            return View(profile);
        }

        //
        // POST: /Profile/Delete/5

        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            Profile profile = db.Profiles.Find(id);
            db.Profiles.Remove(profile);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }

        private void fillsDropDownList(object selectedCountry = null)
        {
            var coutrysQuery = from d in db.countrys
                               select d;
            var selectList = new SelectList(coutrysQuery, "ID", "nome", selectedCountry);
            ViewBag.naturalidades = selectList;
        } 
        }
    }
