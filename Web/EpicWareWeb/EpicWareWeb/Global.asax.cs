using EpicWareWeb.Controllers;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Web;
using System.Web.Http;
using System.Web.Mvc;
using System.Web.Optimization;
using System.Web.Routing;

namespace EpicWareWeb
{
    // Note: For instructions on enabling IIS6 or IIS7 classic mode, 
    // visit http://go.microsoft.com/?LinkId=9394801

    public class MvcApplication : System.Web.HttpApplication{
        
        protected void Application_Start()
        {
            AreaRegistration.RegisterAllAreas();

            WebApiConfig.Register(GlobalConfiguration.Configuration);
            FilterConfig.RegisterGlobalFilters(GlobalFilters.Filters);
            RouteConfig.RegisterRoutes(RouteTable.Routes);
            BundleConfig.RegisterBundles(BundleTable.Bundles);
            AuthConfig.RegisterAuth();
        }

        protected void Application_AcquireRequestState(object sender, EventArgs e) {
            string lang;
            try
            {
                UserController ctrUsr = new UserController();
                lang = ctrUsr.UserAutenticated().language.reference;
                //Create culture info object
                CultureInfo ci = new CultureInfo(lang);
                System.Threading.Thread.CurrentThread.CurrentUICulture = ci;
                System.Threading.Thread.CurrentThread.CurrentCulture = CultureInfo.CreateSpecificCulture(ci.Name);
            }catch(Exception)
            {
                if(HttpContext.Current.Request.Cookies.AllKeys.Contains("language")){
                    lang = HttpContext.Current.Request.Cookies["language"].Value;
                }else{
                    lang = "pt-PT";
                }
                
                //Create culture info object
                CultureInfo ci = new CultureInfo(lang);
                System.Threading.Thread.CurrentThread.CurrentUICulture = ci;
                System.Threading.Thread.CurrentThread.CurrentCulture = CultureInfo.CreateSpecificCulture(ci.Name);
            }


        }
    }
}