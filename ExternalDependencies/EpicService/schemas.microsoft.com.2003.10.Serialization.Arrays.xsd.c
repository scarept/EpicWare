﻿
// File generated by Wsutil Compiler version 1.0095 
#include <WebServices.h>
#include "schemas.microsoft.com.2003.10.Serialization.Arrays.xsd.h"

typedef struct _schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions 
{
    struct  // global types
    {
        char unused;
        struct  // ArrayOfint
        {
            WS_FIELD_DESCRIPTION Int;
            WS_FIELD_DESCRIPTION* ArrayOfintFields [1]; 
        } ArrayOfintdescs; // end of ArrayOfint
    } globalTypes;  // end of global types
    struct  // XML dictionary
    {
        struct  // XML string list
        {
            WS_XML_STRING ArrayOfintTypeName;  // ArrayOfint
            WS_XML_STRING ArrayOfintTypeNamespace;  // http://schemas.microsoft.com/2003/10/Serialization/Arrays
            WS_XML_STRING ArrayOfintIntLocalName;  // int
        } xmlStrings;  // end of XML string list
        WS_XML_DICTIONARY dict;
    } dictionary;  // end of XML dictionary
} _schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions;

const static _schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions =
{
    { // global types
        0,
        {  // ArrayOfint
            {  // field description for Int
            WS_REPEATING_ELEMENT_FIELD_MAPPING,
            0,
            0,
            WS_INT32_TYPE,
            0,
            WsOffsetOf(ArrayOfint, Int),
            0,
            0,
            WsOffsetOf(ArrayOfint, IntCount),
            (WS_XML_STRING*)&schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfintIntLocalName, // int
            (WS_XML_STRING*)&schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfintTypeNamespace, // http://schemas.microsoft.com/2003/10/Serialization/Arrays
            0,
            },    // end of field description for Int
            {  // fields description for ArrayOfint
            (WS_FIELD_DESCRIPTION*)&schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.globalTypes.ArrayOfintdescs.Int,
            },
        },    // ArrayOfint
    }, // end of global types
    {  // dictionary 
        {  // xmlStrings
            WS_XML_STRING_DICTIONARY_VALUE("ArrayOfint",&schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.dictionary.dict, 0),
            WS_XML_STRING_DICTIONARY_VALUE("http://schemas.microsoft.com/2003/10/Serialization/Arrays",&schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.dictionary.dict, 1),
            WS_XML_STRING_DICTIONARY_VALUE("int",&schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.dictionary.dict, 2),
        },  // end of xmlStrings
        
        {  // schemas_microsoft_com_2003_10_Serialization_Arrays_xsddictionary
          // e387d822-1fc8-4415-afd8-f61c98a412db 
        { 0xe387d822, 0x1fc8, 0x4415, { 0xaf, 0xd8, 0xf6,0x1c, 0x98, 0xa4, 0x12, 0xdb } },
        (WS_XML_STRING*)&schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.dictionary.xmlStrings,
        3,
        TRUE,
        },
    },  //  end of dictionary
}; //  end of schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions

const _schemas_microsoft_com_2003_10_Serialization_Arrays_xsd schemas_microsoft_com_2003_10_Serialization_Arrays_xsd =
{
    {  // globalTypes
        {
        sizeof(ArrayOfint),
        __alignof(ArrayOfint),
        (WS_FIELD_DESCRIPTION**)&schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.globalTypes.ArrayOfintdescs.ArrayOfintFields,
        WsCountOf(schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.globalTypes.ArrayOfintdescs.ArrayOfintFields),
        (WS_XML_STRING*)&schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfintTypeName, // ArrayOfint
        (WS_XML_STRING*)&schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfintTypeNamespace, // http://schemas.microsoft.com/2003/10/Serialization/Arrays
        0,
        0,
        0,
        },   // end of struct description for ArrayOfint
    },  // globalTypes
    {  // globalElements
        {
            (WS_XML_STRING*)&schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfintTypeName, // ArrayOfint
            (WS_XML_STRING*)&schemas_microsoft_com_2003_10_Serialization_Arrays_xsdLocalDefinitions.dictionary.xmlStrings.ArrayOfintTypeNamespace, // http://schemas.microsoft.com/2003/10/Serialization/Arrays
            WS_STRUCT_TYPE,
            (void*)&schemas_microsoft_com_2003_10_Serialization_Arrays_xsd.globalTypes.ArrayOfint,
        },
    },  // globalElements
}; // end of _schemas_microsoft_com_2003_10_Serialization_Arrays_xsd
