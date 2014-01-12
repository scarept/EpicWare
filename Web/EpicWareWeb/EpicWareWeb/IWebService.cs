﻿using EpicWareWeb.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace EpicWareWeb
{

    [Serializable]
    [DataContract]
    public struct Word
    {
        [DataMember]
        public string text;

        [DataMember]
        public string topic;

        [DataMember]
        public string language;
    }

    [Serializable]
    [DataContract]
    public struct UserData
    {
        [DataMember]
        public string firstName;

        [DataMember]
        public string lastName;

        [DataMember]
        public int numberOfUserTags;
    }

    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IWebService" in both code and config file together.
    [ServiceContract]
    public interface IWebService
    {
        [OperationContract]
        int getNumberUsers();

        [OperationContract]
        int getNumberDownloads();

        [OperationContract]
        User getUserByID(int id, string user, string pass);

        [OperationContract]
        IList<int> getUserFriendsByUserId(int id, string user, string pass);

        [OperationContract]
        User getUserByAutetication(string user, string password);

        [OperationContract]
        IList<Word> GetEveryWord();

        [OperationContract]
        IList<int> getAllUsersID();

        [OperationContract]
        int getConnectioStrenght(int id1, int id2);

        [OperationContract]
        int getNumberTagsForUserId(int id, string user, string pass);

        [OperationContract]
        int getStrenghtConnection(int id1, int id2, string user, string pass);

        [OperationContract]
        UserData getUserData(int id, string user, string pass);
    }
}
