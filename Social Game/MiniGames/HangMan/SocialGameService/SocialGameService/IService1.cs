﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace SocialGameService
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

    [ServiceContract]
    public interface IService1
    {

        [OperationContract]
        IList<Word> GetEveryWord();

        [OperationContract]
        int Add(int x, int y);
    }
}
