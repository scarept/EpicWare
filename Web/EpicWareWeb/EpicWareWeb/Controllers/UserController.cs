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
        [Authorize]
        public ActionResult Index()
        {
            return View(db.users.ToList());
        }

        //
        // GET: /User/Details/5
        [Authorize]
        public ActionResult Details(int id = 0)
        {
            User user = db.users.Find(id);
            if (user == null)
            {
                return HttpNotFound();
            }
            return View(user);
        }

        /* PERFIL MANAGER*/

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
        [Authorize]
        public ActionResult Edit(int id = 0)
        {
            fillLanguagesList();
            User user = UserAutenticated();
            ViewBag.profileSend = user.userProfile;
            fillDropDownListMood(user.mood);

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
        [Authorize]
        public ActionResult Edit(FormCollection collection, string langSelect, string moodSelect,HttpPostedFileBase file)
        {
            User userAuth = UserAutenticated();

            /* MOOD */
            userAuth.mood = null;
            Mood tmp = db.moods.Find(Convert.ToInt32(moodSelect));
            userAuth.mood = tmp;

            /* LANGUAGE */
            userAuth.language = null;
            Language l = db.languages.Find(Convert.ToInt32(langSelect));
            userAuth.language = l;

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
                return RedirectToAction("Profile", new { id = userAuth.userID });
            }
            return View();
        }

        //
        // GET: /User/EditProfile/5
        [Authorize]
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
        [Authorize]

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
            else
            {
                userAuth.userProfile.pathImg = "/Images/Profiles/default.gif";
            }

            if (ModelState.IsValid)
            {
                db.Entry(userAuth).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            
            return View();
        }
        [Authorize]
        public ActionResult DesactivateAccount(int id = 0)
        {
            return View();
        }


        public ActionResult NotActive(int id = 0)
        {
            User user = db.users.Find(id);
            return View(user);
        }

        [HttpPost]
        [Authorize]
        public ActionResult ReativateAccount()
        {
            User user = UserAutenticated();
            user.active = true;
            if (ModelState.IsValid)
            {
                db.Entry(user).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index", "Home");
            }
            return View();
        }

        public ActionResult NoReativateAccount()
        {
            WebSecurity.Logout();
            return RedirectToAction("Index", "Home");
        }

        [HttpPost]
        [Authorize]
        public ActionResult DesactivateAccount()
        {
            User user = UserAutenticated();
            user.active = false;
            WebSecurity.Logout();
            if (ModelState.IsValid)
            {
                db.Entry(user).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index","Home");
            }
            return View();
        }



        /* VISUALIZAÇÃO */ 

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

        public ActionResult Profile(int id = 0)
        {
            User user;
            if (id == 0)
            {
                user = UserAutenticated();

            }
            else
            {
                user = db.users.Find(id);
            }
            if (user.userID == UserAutenticated().userID)
            {
                //Size of network 3º level
                int count = 0;
                count += user.listConnections.Count();

                ConnectionController ctrConn = new ConnectionController();
                foreach (Connection conn in user.listConnections)
                {
                    count += ctrConn.noCommonConnections(conn.userConnected).Count();
                }
                ViewBag.networkSize = count;
            }

            
            return View(user);
        }

        /* FRINDS SUGESTION */
        // Based on frinds of friends
        [Authorize]
        public ActionResult FriendsSugestion()
        {
            User userAuth = UserAutenticated();
            ConnectionController ctrConn = new ConnectionController();
            List<User> sugestionFriends = new List<User>();
            foreach(Connection conn in userAuth.listConnections)
            {
                List<User> frindsOfFriend = ctrConn.noCommonFriends(conn.userConnected);
                sugestionFriends.AddRange(frindsOfFriend);
            }
            return View(sugestionFriends);
        }


        /* FRIEND REQUEST*/

        //[HttpPost]
        //[Authorize]
        //public ActionResult Profile(int id = 0)
        //{
        //    return View();
        //}


        // Get
        [Authorize]
        public ActionResult AddFriend(int id = 0)
        {
            fillDropDownListTagConnection();
            User user = db.users.Find(id);
            return View(user);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        [Authorize]
        public ActionResult AddFriend(string tagSelect, FormCollection collection)
        {
            User userAuth = UserAutenticated();
            User user = db.users.Find(Convert.ToInt32(collection.Get("userID")));

            /*Create Friend Request*/
            FriendRequest fR = new FriendRequest();

            /* Strenght */
            string força = collection.Get("conn.strenght");
            int forçaInt = Convert.ToInt32(força);
            fR.strenght = forçaInt;

            /* Tag Connection */
            TagConnection tagConn = db.tagConnections.Find(Convert.ToInt32(tagSelect));
            fR.tagConnection = tagConn;
            
            /*Users*/
            fR.user1 = userAuth;
            fR.user2 = user;

            if (ModelState.IsValid)
            {
                db.friendRequests.Add(fR);
                db.SaveChanges();
            }

            /* Create Notification */
            Notification note = new Notification();
            note.notificationType = db.notificationsType.Find(1); // FR type
            note.message = @EpicWareWeb.Views.User.User.novopedidoamizade + " : " + userAuth.userProfile.nickname;
            note.time = DateTime.Now;
            note.read = false;
            user.notifications.Add(note);

            if (ModelState.IsValid)
            {
                db.Entry(user).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Profile", new { id = userAuth.userID });
            }
            return RedirectToAction("Profile", new { id = userAuth.userID });
        }

        [Authorize]
        public ActionResult ListFriendRequest()
        {
            ConnectionController ctrConn = new ConnectionController();
            ViewBag.introsVB = ctrConn.introsRequestPending();
            return View(ctrConn.friendsRequestedPending());
        }

        [Authorize]
        public ActionResult AcceptFR(FormCollection collection)
        {
            /*Get friend request*/
            int fRId = Convert.ToInt32(collection.Get("friendRequestID"));
            FriendRequest fR = db.friendRequests.Find(fRId);


            User userAuth = UserAutenticated();
            User user = fR.user1;

            Connection conn1 = new Connection();
            Connection conn2 = new Connection();

            /* Strenght */
            conn1.strenght = fR.strenght;
            conn2.strenght = fR.strenght;

            /* Tag Connection */
            conn1.tagConnection = fR.tagConnection;
            conn2.tagConnection = fR.tagConnection;

            /* Owner */
            conn1.Owner = userAuth;
            conn2.Owner = user;

            /* User Connected */
            conn1.userConnected = user;
            conn2.userConnected = userAuth;

            /* Save connections on all users and remove FrindRequest*/
            userAuth.listConnections.Add(conn1);
            user.listConnections.Add(conn2);

            /* Create Notification */
            Notification note = new Notification();
            note.message = userAuth.userProfile.nickname + EpicWareWeb.Views.User.User.fraceite;
            note.time = DateTime.Now;
            note.read = false;
            NotificationType nTyp = new NotificationType();
            nTyp.type = "FA"; // FRAccept
            nTyp.resultLink = "~/User/Profile/" + userAuth.userID;
            note.notificationType = nTyp;
            user.notifications.Add(note);

            if (ModelState.IsValid)
            {
                db.Entry(user).State = EntityState.Modified;
                db.Entry(userAuth).State = EntityState.Modified;
                db.SaveChanges();
                db.friendRequests.Remove(fR);
                db.SaveChanges();
            }
            return RedirectToAction("ListFriendRequest");
        }

        [Authorize]
        public ActionResult RejectFR(FormCollection collection)
        {
            /*Get friend request*/
            int fRId = Convert.ToInt32(collection.Get("friendRequestID"));
            FriendRequest fR = db.friendRequests.Find(fRId);

            if (ModelState.IsValid)
            {
                db.friendRequests.Remove(fR);
                db.SaveChanges();
            }
            return RedirectToAction("ListFriendRequest");
        }


        /* INTRODUTION REQUEST */ 

        //Get
        [Authorize]
        public ActionResult IntrodutionRequest(int id = 0)
        {
            User user = db.users.Find(id);
            ConnectionController ctrConn = new ConnectionController();
            return View(ctrConn.noCommonConnections(user));
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        [Authorize]
        public PartialViewResult IntrodutionRequest(FormCollection collection)
        {
            string friendID = collection.Get("friend.userID");
            User userFriend = db.users.Find(Convert.ToInt32(friendID));

            string toIntroID = collection.Get("toIntro.userID");
            User userToIntro = db.users.Find(Convert.ToInt32(toIntroID));

            string txtIntro = collection.Get("txtIntro");

            IntroFriendRequest introFR = new IntroFriendRequest();
            introFR.sendedBC = false;
            introFR.userA = UserAutenticated();
            introFR.userB = userFriend;
            introFR.userC = userToIntro;
            introFR.messageAB = txtIntro;

            /* Create Notification */
            Notification note = new Notification();
            note.notificationType = db.notificationsType.Find(2); // IR type
            note.message = @EpicWareWeb.Views.User.User.oseuamigo + " <b>" + introFR.userB.userProfile.nickname + "</b> " + EpicWareWeb.Views.User.User.recomendou + " <b>" + introFR.userA.userProfile.nickname + "</b> " + EpicWareWeb.Views.User.User.paraSerSeuAmigo;
            note.time = DateTime.Now;
            note.read = false;
            userFriend.notifications.Add(note);

            if (ModelState.IsValid)
            {
                db.Entry(userFriend).State = EntityState.Modified;
                db.SaveChanges();
                db.introes.Add(introFR);
                db.SaveChanges();
            }
            return PartialView ("_IntroSended");

        }

        [HttpPost]
        public PartialViewResult RequestIntroAjax(int id1, int id2)
        {
            User userConnected = db.users.Find(Convert.ToInt32(id2));
            User userFriend = db.users.Find(Convert.ToInt32(id1));

            ViewBag.userConnectedVB = userConnected;
            ViewBag.userFriendVB = userFriend;

            return PartialView("_TxtIntrodution");
        }



        /* INTRODUTION MANAGE MIDDLE ACTION */

        [Authorize]
        public ActionResult ListIntrosFriendRequestMiddle()
        {
            ConnectionController ctrConn = new ConnectionController();
            return View(ctrConn.introsRequestMiddlePending());
        }

        
        [HttpPost]
        [Authorize]
        [ValidateAntiForgeryToken]
        public PartialViewResult ResponseMiddleIntroAjax(int id)
        {
            IntroFriendRequest intro = db.introes.Find(id);
            ViewBag.intro = intro;
            return PartialView("_IntroSendBC");
        }

        public RedirectToRouteResult SendMiddleIntroAjax(int id, FormCollection collection)
        {
            string msgBC = collection.Get("txtIntro");
            IntroFriendRequest intro = db.introes.Find(id);
            intro.messageBC = msgBC;
            intro.sendedBC = true;

            /* Create Notification UserA */
            Notification note = new Notification();
            NotificationType nTyp = new NotificationType();
            note.message = @EpicWareWeb.Views.User.User.introReqNotMiddleAceept + ". "+ EpicWareWeb.Views.User.User.de + ": <b>" + intro.userB.userProfile.nickname + "</b> " 
            + EpicWareWeb.Views.User.User.para + ": <b>" + intro.userC.userProfile.nickname + "</b>";
            note.read = false;
            note.time = DateTime.Now;
            //nTyp.type = "IRM";
            nTyp.resultLink = "~/User/Profile/" + intro.userA.userID;
            note.notificationType = nTyp;
            intro.userA.notifications.Add(note);



            if (ModelState.IsValid)
            {
                db.Entry(intro).State = EntityState.Modified;
                db.SaveChanges();
            }
            return RedirectToAction("ListIntrosFriendRequestMiddle");

        }

        [HttpPost]
        [Authorize]
        [ValidateAntiForgeryToken]
        public PartialViewResult RejectMiddleIntroAjax(int id)
        {
            IntroFriendRequest intro = db.introes.Find(id);

            /* Create Notification */
            Notification note = new Notification();
            note.message = intro.userB.userProfile.nickname + " " + EpicWareWeb.Views.User.User.rejeitouIR + " " + intro.userC.userProfile.nickname;
            note.read = false;
            note.time = DateTime.Now;

            NotificationType nTyp = new NotificationType();
            nTyp.resultLink = "~/User/Profile/"+intro.userA.userID;
            note.notificationType = nTyp;
            User user = intro.userA;
            user.notifications.Add(note);
           
            if (ModelState.IsValid)
            {
                db.Entry(user).State = EntityState.Modified;
                db.introes.Remove(intro);
                db.SaveChanges();
            }
                return PartialView("_empty");
        }


        /* INTRODUTION RESPONSE */

        public RedirectToRouteResult AcceptIntroFR(IntroFriendRequest intro)
        {
            User userAuth = UserAutenticated();
            User user = intro.userA;

            Connection conn1 = new Connection();
            Connection conn2 = new Connection();

            /* Strenght */
            conn1.strenght = 1; // one by default of introdution
            conn2.strenght = 1;

            /* Tag Connection */
            conn1.tagConnection = db.tagConnections.Find(1); // Amigo by default
            conn2.tagConnection = db.tagConnections.Find(1);

            /* Owner */
            conn1.Owner = userAuth;
            conn2.Owner = user;

            /* User Connected */
            conn1.userConnected = user;
            conn2.userConnected = userAuth;

            /* Save connections on all users and remove FrindRequest*/
            userAuth.listConnections.Add(conn1);
            user.listConnections.Add(conn2);

            if (ModelState.IsValid)
            {
                db.Entry(user).State = EntityState.Modified;
                db.Entry(userAuth).State = EntityState.Modified;
                db.SaveChanges();
                db.introes.Remove(intro);
                db.SaveChanges();
            }
            return RedirectToAction("ListFriendRequest");
        }

        public RedirectToRouteResult RejectIntroFR(IntroFriendRequest intro)
        {
            if (ModelState.IsValid)
            {
                db.introes.Remove(intro);
                db.SaveChanges();
            }
            return RedirectToAction("ListFriendRequest");      
        }
        /**/
        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }

        /* NOTIFICATIONS */
        
        [HttpGet]
        public PartialViewResult Notifications()
        {
            User user = UserAutenticated();
            return PartialView("_Notifications", user);
        }

        public ActionResult ListNotifications()
        {
            User user = UserAutenticated();
            List<Notification> send = new List<Notification>(); 
            foreach(Notification item in user.notifications)
            {
                if (!item.read)
                {
                    item.read = true;
                    //send.Add(item); Mostra todas e diz quais foram lidas. Descomentar para so mostrar nao lidas
                }
             }
            if (ModelState.IsValid)
            {
                db.Entry(user).State = EntityState.Modified;
                db.SaveChanges();
            }
            return View(user.notifications);
        }

        /* DOWNLOAD GAME */
        [HttpGet]
        public RedirectResult DownloadGame()
        {
            if(ModelState.IsValid)
            {
                Download dw = new Download();
                dw.time = DateTime.Now;
                db.downloads.Add(dw);
                db.SaveChanges();
            }
            return RedirectPermanent("~/DownloadGame/game.exe");
        }


        /* AUX METHODS */

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

       

        /*DROP DOWN LIST AUX*/
        
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

        private void fillDropDownListTagConnection(object selectedTag = null)
        {
            var tagQuery = from d in db.tagConnections
                                  orderby d.tag
                                  select d;
            var selectTag = new SelectList(tagQuery, "tagConnectionID", "tag", selectedTag);
            ViewBag.tagConnections = selectTag; 
        }

        private void fillDropDownListMood(object selectedMood = null)
        {
            var moodQuery = from d in db.moods
                           orderby d.moodID
                           select d;
            var selectTag = new SelectList(moodQuery, "moodID", "name", selectedMood);
            ViewBag.moods = selectTag;
        }

    }
}