using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace SocialGameService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in both code and config file together.
    public class Service1 : IService1
    {
        public int Add(int x, int y)
        {
            return x + y;
        }

        public IList<string> getInfoUser(int id)
        {
            IList<string> conteudo;
            SocialNetworkGateway SN = new SocialNetworkGateway();
            conteudo = SN.getInfoUser(id);
            return conteudo;
        }

        public IList<int> getUserConnected(int id)
        {
            IList<int> conectionsList;
            SocialNetworkGateway SN = new SocialNetworkGateway();
            conectionsList = SN.getConnection(id);
            return conectionsList;
        }

        public IList<int> getAllUsers(){
            IList<int> users;
            SocialNetworkGateway sn = new SocialNetworkGateway();
            users = sn.getAllUsers();
            return users;
        }

        public IList<Word> GetEveryWord()
        {
            HangmanGateway hg = new HangmanGateway();
            IList<Word> words;

            try
            {
                words = hg.getEveryWord();
            }
            catch (SqlException ex)
            {
                return null;
            }

            return words;

        }

        public int getConnectionStrenght(int id1, int id2) {
            SocialNetworkGateway sn = new SocialNetworkGateway();
            return sn.getConnectionStrenght(id1, id2);
        }
    }
}
