using System;
using System.Data;
using System.Data.SqlClient;

namespace SocialGameService
{
    public abstract class BaseGateway
    {
        public BaseGateway()
        {
        }

        private const string _CONNSTR = @"Data Source = 172.31.101.74,1433\SQLEXPRESS;Initial Catalog=epicwar2e;User ID=sa;Password=EpicWar3";
        //private const string _CONNSTR = @"Data Source = 172.31.101.74,1433\SQLEXPRESS;Initial Catalog=epicware;User ID=sa;Password=EpicWar3";

        private string CONNSTR
        {
            get { return _CONNSTR; }
        }

        private SqlTransaction myTx;

        protected SqlTransaction CurrentTransaction
        {
            get { return myTx; }
        }

        protected SqlConnection GetConnection(bool open)
        {
            SqlConnection cnx = new SqlConnection(CONNSTR);
            if (open)
                cnx.Open();
            return cnx;
        }

        protected DataSet ExecuteQuery(SqlConnection cnx, string sql)
        {
            try
            {
                SqlDataAdapter da = new SqlDataAdapter(sql, cnx);
                DataSet ds = new DataSet();
                da.Fill(ds);
                return ds;
            }
            catch (SqlException ex)
            {
                return null;
            }
        }

        protected DataSet ExecuteQuery(SqlCommand sql)
        {
            try
            {
                SqlDataAdapter da = new SqlDataAdapter(sql);
                DataSet ds = new DataSet();
                da.Fill(ds);
                return ds;
            }
            catch (SqlException ex)
            {
                throw new ApplicationException("Erro a executar o Query", ex);
            }
        }

        protected void FillDataSet(SqlConnection cnx, string sql, DataSet ds, string tableName)
        {
            try
            {
                SqlDataAdapter da = new SqlDataAdapter(sql, cnx);
                da.Fill(ds, tableName);
            }
            catch (SqlException ex)
            {
                throw new ApplicationException("Erro a preencher o DataSet", ex);
            }
        }

        protected int ExecuteNonQuery(SqlConnection cnx, string sql)
        {
            SqlCommand cmd = new SqlCommand(sql, cnx);
            return cmd.ExecuteNonQuery();
        }

        protected int ExecuteNonQuery(SqlTransaction tx, string sql)
        {
            SqlCommand cmd = new SqlCommand(sql, tx.Connection, tx);
            return cmd.ExecuteNonQuery();
        }

        protected int ExecuteNonQuery(SqlTransaction tx, SqlCommand cmd)
        {
            cmd.Transaction = tx;
            return cmd.ExecuteNonQuery();
        }

        public void BeginTransaction()
        {
            try
            {
                if (myTx == null)
                    myTx = GetConnection(true).BeginTransaction();
            }
            catch (SqlException ex)
            {
                throw new ApplicationException("Erro a efectuar a transacção", ex);
            }
        }

        public void CommitTransaction()
        {
            if (myTx != null)
            {
                SqlConnection cnx = myTx.Connection;
                myTx.Commit();
                cnx.Close();
            }
        }

        public void RoolbackTransaction()
        {
            if (myTx != null)
            {
                SqlConnection cnx = myTx.Connection;
                myTx.Rollback();
                cnx.Close();
            }
        }
    }
}
