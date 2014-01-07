using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EpicWareWeb{

    public class HangmanGateway : BaseGateway
    {


        public IList<Word> getEveryWord()
        {

            SqlCommand sql = new SqlCommand();

            try
            {
                Word tempWord;
                IList<Word> words = new List<Word>();
                DataSet ds = ExecuteQuery(GetConnection(true), "SELECT W.nome as wName, T.nome as tName, L.Name as lName FROM HangmanWord W, HangmanTopic T, Languages L WHERE W.topicID = T.topicID and T.languageID = L.languageID");
                DataTable dt = ds.Tables[0];

                foreach (DataRow r in dt.Rows)
                {

                    tempWord.text = r["wName"].ToString();
                    tempWord.topic = r["tName"].ToString();
                    tempWord.language = r["lName"].ToString();

                    words.Add(tempWord);
                }

                return words;
            }
            catch (SqlException)
            {
                return null;
            }
        }
    }
}
