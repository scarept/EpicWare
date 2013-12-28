using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SocialGameService
{
    class SocialNetworkGateway : BaseGateway
    {
        public IList<string> getInfoUser(int id)
        {

            SqlCommand sql = new SqlCommand();
            IList<string> words = new List<string>();
            try
            {
                DataSet ds = ExecuteQuery(GetConnection(true), "select p.name as Name, p.lastname as LastName, p.gender as Gender, usr.email as Mail, p.nickname as NickName, cnt.name as Country, p.phoneNumber as PhoneNumber from Profiles p, Users usr, Countries cnt where usr.UserProfileID = " + id + " and usr.userProfile_profileID = p.profileID and p.country_countryID =  cnt.countryID");
                DataRow row = ds.Tables[0].Rows[0];
                words.Add(row["Name"].ToString());
                words.Add(row["LastName"].ToString());
                words.Add(row["Gender"].ToString());
                words.Add(row["Mail"].ToString());
                words.Add(row["NickName"].ToString());
                words.Add(row["Country"].ToString());
                words.Add(row["PhoneNumber"].ToString());
                
                return words;
            }
            catch (SqlException ex)
            {
                return null;
            }
        }
    }
}
