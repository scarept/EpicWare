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

        public IList<int> getConnection(int id)
        {
            SqlCommand sql = new SqlCommand();
            IList<int> connections = new List<int>();
            try
            {
                DataSet ds = ExecuteQuery(GetConnection(true), "select userConnected_userID as Cone from Connections where User_userID = " + id);
                foreach(DataRow dr in ds.Tables[0].Rows)
                {
                    connections.Add(int.Parse(dr["Cone"].ToString()));
                }
                return connections;
            }
            catch(SqlException ex)
            {
                return null;
            }
        }

        public IList<int> getAllUsers() {
            SqlCommand sql = new SqlCommand();
            IList<int> users = new List<int>();
            try
            {
                DataSet ds = ExecuteQuery(GetConnection(true), "select userID from Users");
                foreach (DataRow dr in ds.Tables[0].Rows)
                    users.Add(int.Parse(dr["userID"].ToString()));

                return users;
            }
            catch (SqlException ex) {
                return null;
            }
        }

        public int getConnectionStrenght(int id1, int id2) { 
            SqlCommand sql = new SqlCommand();
            int strenght = -1;
            try
            {
                DataSet ds = ExecuteQuery(GetConnection(true), "select strenght from connections where User_userID = " + id1 + " and userConnected_userID = " + id2);
                foreach (DataRow dr in ds.Tables[0].Rows)
                    strenght = int.Parse(dr["strenght"].ToString());

                return strenght;
            }
            catch (SqlException ex) {
                return -1;
            }
        }

    }
}
