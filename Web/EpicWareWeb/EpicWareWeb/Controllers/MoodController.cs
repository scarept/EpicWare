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
    public class MoodController : Controller
    {
        private DataContext db = new DataContext();

        //
        // GET: /Mood/

        public ActionResult Index()
        {
            return View(db.moods.ToList());
        }

        //
        // GET: /Mood/Details/5

        public ActionResult Details(int id = 0)
        {
            Mood mood = db.moods.Find(id);
            if (mood == null)
            {
                return HttpNotFound();
            }
            return View(mood);
        }

        //
        // GET: /Mood/Create

        public ActionResult Create()
        {
            return View();
        }

        //
        // POST: /Mood/Create

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create(Mood mood)
        {
            if (ModelState.IsValid)
            {
                db.moods.Add(mood);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(mood);
        }

        //
        // GET: /Mood/Edit/5

        public ActionResult Edit(int id = 0)
        {
            Mood mood = db.moods.Find(id);
            if (mood == null)
            {
                return HttpNotFound();
            }
            return View(mood);
        }

        //
        // POST: /Mood/Edit/5

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit(Mood mood)
        {
            if (ModelState.IsValid)
            {
                db.Entry(mood).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(mood);
        }

        //
        // GET: /Mood/Delete/5

        public ActionResult Delete(int id = 0)
        {
            Mood mood = db.moods.Find(id);
            if (mood == null)
            {
                return HttpNotFound();
            }
            return View(mood);
        }

        //
        // POST: /Mood/Delete/5

        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            Mood mood = db.moods.Find(id);
            db.moods.Remove(mood);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}