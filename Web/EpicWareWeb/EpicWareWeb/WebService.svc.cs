using EpicWareWeb.DAL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace EpicWareWeb
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "WebService" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select WebService.svc or WebService.svc.cs at the Solution Explorer and start debugging.
    public class WebService : IWebService
    {
        public int getNumberUsers()
        {
            DataContext db = new DataContext();
            return db.users.Count();            
        }
    }
}

