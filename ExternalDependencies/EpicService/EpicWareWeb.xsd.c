﻿
// File generated by Wsutil Compiler version 1.0095 
#include <WebServices.h>
#include "EpicWareWeb.xsd.h"

typedef struct _EpicWareWeb_xsdLocalDefinitions 
{
    struct  // global types
    {
        char unused;
        struct  // ArrayOfWord
        {
            struct  // Word
            {
                WS_FIELD_DESCRIPTION language;
                WS_FIELD_DESCRIPTION text;
                WS_FIELD_DESCRIPTION topic;
                WS_FIELD_DESCRIPTION* WordFields [3]; 
            } Worddescs; // end of Word
            WS_FIELD_DESCRIPTION Word;
            WS_FIELD_DESCRIPTION* ArrayOfWordFields [1]; 
        } ArrayOfWorddescs; // end of ArrayOfWord
        struct  // UserData
        {
            WS_FIELD_DESCRIPTION firstName;
            WS_FIELD_DESCRIPTION lastName;
            WS_FIELD_DESCRIPTION numberOfUserTags;
            WS_FIELD_DESCRIPTION* UserDataFields [3]; 
        } UserDatadescs; // end of UserData
    } globalTypes;  // end of global types
    struct  // XML dictionary
    {
        struct  // XML string list
        {
            WS_XML_STRING ArrayOfWordTypeName;  // ArrayOfWord
            WS_XML_STRING ArrayOfWordTypeNamespace;  // http://schemas.datacontract.org/2004/07/EpicWareWeb
            WS_XML_STRING WordTypeName;  // Word
            WS_XML_STRING WordlanguageLocalName;  // language
            WS_XML_STRING WordtextLocalName;  // text
            WS_XML_STRING WordtopicLocalName;  // topic
            WS_XML_STRING UserDataTypeName;  // UserData
            WS_XML_STRING UserDatafirstNameLocalName;  // firstName
            WS_XML_STRING UserDatalastNameLocalName;  // lastName
            WS_XML_STRING UserDatanumberOfUserTagsLocalName;  // numberOfUserTags
        } xmlStrings;  // end of XML string list
        WS_XML_DICTIONARY dict;
    } dictionary;  // end of XML dictionary
} _EpicWareWeb_xsdLocalDefinitions;

const static _EpicWareWeb_xsdLocalDefinitions EpicWareWeb_xsdLocalDefinitions =
{
    { // global types
        0,
        {  // ArrayOfWord
            {  // Word
                {  // field description for language
                WS_ELEMENT_FIELD_MAPPING,
                (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.WordlanguageLocalName, // language
                (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
                WS_WSZ_TYPE,
                0,
                WsOffsetOf(Word, language),
                 WS_FIELD_OPTIONAL| WS_FIELD_NILLABLE,
                0,
                0xffffffff
                },    // end of field description for language
                {  // field description for text
                WS_ELEMENT_FIELD_MAPPING,
                (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.WordtextLocalName, // text
                (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
                WS_WSZ_TYPE,
                0,
                WsOffsetOf(Word, text),
                 WS_FIELD_OPTIONAL| WS_FIELD_NILLABLE,
                0,
                0xffffffff
                },    // end of field description for text
                {  // field description for topic
                WS_ELEMENT_FIELD_MAPPING,
                (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.WordtopicLocalName, // topic
                (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
                WS_WSZ_TYPE,
                0,
                WsOffsetOf(Word, topic),
                 WS_FIELD_OPTIONAL| WS_FIELD_NILLABLE,
                0,
                0xffffffff
                },    // end of field description for topic
                {  // fields description for Word
                (WS_FIELD_DESCRIPTION*)&EpicWareWeb_xsdLocalDefinitions.globalTypes.ArrayOfWorddescs.Worddescs.language,
                (WS_FIELD_DESCRIPTION*)&EpicWareWeb_xsdLocalDefinitions.globalTypes.ArrayOfWorddescs.Worddescs.text,
                (WS_FIELD_DESCRIPTION*)&EpicWareWeb_xsdLocalDefinitions.globalTypes.ArrayOfWorddescs.Worddescs.topic,
                },
            },    // Word
            {  // field description for Word
            WS_REPEATING_ELEMENT_FIELD_MAPPING,
            0,
            0,
            WS_STRUCT_TYPE,
            (void*)&EpicWareWeb_xsd.globalTypes.Word,
            WsOffsetOf(ArrayOfWord, Word),
            0,
            0,
            WsOffsetOf(ArrayOfWord, WordCount),
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.WordTypeName, // Word
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
            0,
            },    // end of field description for Word
            {  // fields description for ArrayOfWord
            (WS_FIELD_DESCRIPTION*)&EpicWareWeb_xsdLocalDefinitions.globalTypes.ArrayOfWorddescs.Word,
            },
        },    // ArrayOfWord
        {  // UserData
            {  // field description for firstName
            WS_ELEMENT_FIELD_MAPPING,
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.UserDatafirstNameLocalName, // firstName
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
            WS_WSZ_TYPE,
            0,
            WsOffsetOf(UserData, firstName),
             WS_FIELD_OPTIONAL| WS_FIELD_NILLABLE,
            0,
            0xffffffff
            },    // end of field description for firstName
            {  // field description for lastName
            WS_ELEMENT_FIELD_MAPPING,
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.UserDatalastNameLocalName, // lastName
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
            WS_WSZ_TYPE,
            0,
            WsOffsetOf(UserData, lastName),
             WS_FIELD_OPTIONAL| WS_FIELD_NILLABLE,
            0,
            0xffffffff
            },    // end of field description for lastName
            {  // field description for numberOfUserTags
            WS_ELEMENT_FIELD_MAPPING,
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.UserDatanumberOfUserTagsLocalName, // numberOfUserTags
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
            WS_INT32_TYPE,
            0,
            WsOffsetOf(UserData, numberOfUserTags),
             WS_FIELD_OPTIONAL,
            0,
            0xffffffff
            },    // end of field description for numberOfUserTags
            {  // fields description for UserData
            (WS_FIELD_DESCRIPTION*)&EpicWareWeb_xsdLocalDefinitions.globalTypes.UserDatadescs.firstName,
            (WS_FIELD_DESCRIPTION*)&EpicWareWeb_xsdLocalDefinitions.globalTypes.UserDatadescs.lastName,
            (WS_FIELD_DESCRIPTION*)&EpicWareWeb_xsdLocalDefinitions.globalTypes.UserDatadescs.numberOfUserTags,
            },
        },    // UserData
    }, // end of global types
    {  // dictionary 
        {  // xmlStrings
            WS_XML_STRING_DICTIONARY_VALUE("ArrayOfWord",&EpicWareWeb_xsdLocalDefinitions.dictionary.dict, 0),
            WS_XML_STRING_DICTIONARY_VALUE("http://schemas.datacontract.org/2004/07/EpicWareWeb",&EpicWareWeb_xsdLocalDefinitions.dictionary.dict, 1),
            WS_XML_STRING_DICTIONARY_VALUE("Word",&EpicWareWeb_xsdLocalDefinitions.dictionary.dict, 2),
            WS_XML_STRING_DICTIONARY_VALUE("language",&EpicWareWeb_xsdLocalDefinitions.dictionary.dict, 3),
            WS_XML_STRING_DICTIONARY_VALUE("text",&EpicWareWeb_xsdLocalDefinitions.dictionary.dict, 4),
            WS_XML_STRING_DICTIONARY_VALUE("topic",&EpicWareWeb_xsdLocalDefinitions.dictionary.dict, 5),
            WS_XML_STRING_DICTIONARY_VALUE("UserData",&EpicWareWeb_xsdLocalDefinitions.dictionary.dict, 6),
            WS_XML_STRING_DICTIONARY_VALUE("firstName",&EpicWareWeb_xsdLocalDefinitions.dictionary.dict, 7),
            WS_XML_STRING_DICTIONARY_VALUE("lastName",&EpicWareWeb_xsdLocalDefinitions.dictionary.dict, 8),
            WS_XML_STRING_DICTIONARY_VALUE("numberOfUserTags",&EpicWareWeb_xsdLocalDefinitions.dictionary.dict, 9),
        },  // end of xmlStrings
        
        {  // EpicWareWeb_xsddictionary
          // 2a927002-63b3-4479-98e7-efb4bc9ea785 
        { 0x2a927002, 0x63b3, 0x4479, { 0x98, 0xe7, 0xef,0xb4, 0xbc, 0x9e, 0xa7, 0x85 } },
        (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings,
        10,
        TRUE,
        },
    },  //  end of dictionary
}; //  end of EpicWareWeb_xsdLocalDefinitions

const _EpicWareWeb_xsd EpicWareWeb_xsd =
{
    {  // globalTypes
        {
        sizeof(ArrayOfWord),
        __alignof(ArrayOfWord),
        (WS_FIELD_DESCRIPTION**)&EpicWareWeb_xsdLocalDefinitions.globalTypes.ArrayOfWorddescs.ArrayOfWordFields,
        WsCountOf(EpicWareWeb_xsdLocalDefinitions.globalTypes.ArrayOfWorddescs.ArrayOfWordFields),
        (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeName, // ArrayOfWord
        (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
        0,
        0,
        0,
        },   // end of struct description for ArrayOfWord
        {
        sizeof(Word),
        __alignof(Word),
        (WS_FIELD_DESCRIPTION**)&EpicWareWeb_xsdLocalDefinitions.globalTypes.ArrayOfWorddescs.Worddescs.WordFields,
        WsCountOf(EpicWareWeb_xsdLocalDefinitions.globalTypes.ArrayOfWorddescs.Worddescs.WordFields),
        (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.WordTypeName, // Word
        (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
        0,
        0,
        0,
        },   // end of struct description for Word
        {
        sizeof(UserData),
        __alignof(UserData),
        (WS_FIELD_DESCRIPTION**)&EpicWareWeb_xsdLocalDefinitions.globalTypes.UserDatadescs.UserDataFields,
        WsCountOf(EpicWareWeb_xsdLocalDefinitions.globalTypes.UserDatadescs.UserDataFields),
        (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.UserDataTypeName, // UserData
        (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
        0,
        0,
        0,
        },   // end of struct description for UserData
    },  // globalTypes
    {  // globalElements
        {
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeName, // ArrayOfWord
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
            WS_STRUCT_TYPE,
            (void*)&EpicWareWeb_xsd.globalTypes.ArrayOfWord,
        },
        {
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.WordTypeName, // Word
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
            WS_STRUCT_TYPE,
            (void*)&EpicWareWeb_xsd.globalTypes.Word,
        },
        {
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.UserDataTypeName, // UserData
            (WS_XML_STRING*)&EpicWareWeb_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfWordTypeNamespace, // http://schemas.datacontract.org/2004/07/EpicWareWeb
            WS_STRUCT_TYPE,
            (void*)&EpicWareWeb_xsd.globalTypes.UserData,
        },
    },  // globalElements
}; // end of _EpicWareWeb_xsd
