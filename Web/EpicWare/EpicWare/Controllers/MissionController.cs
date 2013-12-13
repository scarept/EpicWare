using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using EpicWare.Models;
using EpicWare.Dal;

namespace EpicWare.Controllers
{
    public class MissionController : Controller
    {
        private DataContext db = new DataContext();

        //
        // GET: /Mission/

        public ActionResult Index()
        {
            return View(db.missions.ToList());
        }

        //
        // GET: /Mission/Details/5

        public ActionResult Details(int id = 0)
        {
            Mission mission = db.missions.Find(id);
            if (mission == null)
            {
                return HttpNotFound();
            }
            return View(mission);
        }

        //
        // GET: /Mission/Create

        public ActionResult Create()
        {
            return View();
        }

        //
        // POST: /Mission/Create

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create(Mission mission)
        {
            if (ModelState.IsValid)
            {
                db.missions.Add(mission);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(mission);
        }

        //
        // GET: /Mission/Edit/5

        public ActionResult Edit(int id = 0)
        {
            Mission mission = db.missions.Find(id);
            if (mission == null)
            {
                return HttpNotFound();
            }
            return View(mission);
        }

        //
        // POST: /Mission/Edit/5

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit(Mission mission)
        {
            if (ModelState.IsValid)
            {
                db.Entry(mission).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(mission);
        }

        //
        // GET: /Mission/Delete/5

        public ActionResult Delete(int id = 0)
        {
            Mission mission = db.missions.Find(id);
            if (mission == null)
            {
                return HttpNotFound();
            }
            return View(mission);
        }

        //
        // POST: /Mission/Delete/5

        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            Mission mission = db.missions.Find(id);
            db.missions.Remove(mission);
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