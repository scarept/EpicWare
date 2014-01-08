﻿
// File generated by Wsutil Compiler version 1.0095 
// This file defines C/C++ functions, callbacks, types that correspond to operations,
// and types specified in WSDL and XSD files processed by Wsutil compiler. The generated 
// type definitions, function and callback declarations can be used with various 
// Web Services APIs either in applications that send and receive requests to and 
// from a running web service, or in the implementation of web services, or in both. 
//
// If Wsutil has generated this file from an XSD file, the file contains definition of 
// C/C++ structures types that correspond to types defined in the XSD file. 
// For example, if the following XSD complexType is defined in the XSD file
//
//      <xsd:complexType name="AddRequest">
//          <xsd:sequence>
//              <xsd:element minOccurs="0" name="a" type="xsd:int" />
//              <xsd:element minOccurs="0" name="b" type="xsd:int" />
//          </xsd:sequence>
//      </xsd:complexType>
// 
// this file contains the following definitions of the structure 
//      // AddRequest (xsd:complexType)
//      // <AddRequest xmlns='http://tempuri.org'>
//      // WS_STRUCT_DESCRIPTION* = &calculator_xsd.globalTypes.AddRequest
//      struct AddRequest
//      {
//          int a;
//          int b;
//      };
//
// For more information on how to use the C/C++ types generated in this file to read or write elements of XML documents that conform to 
// this XSD, please see the documentation for 
// WsReadType() and WsWriteType() functions.
// 
#if _MSC_VER > 1000 
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

// The following types were generated:

//     struct _getNumberUsers;
//     struct _getNumberUsersResponse;
//     struct _getNumberDownloads;
//     struct _getNumberDownloadsResponse;
//     struct _getUserByID;
//     struct _getUserByIDResponse;
//     struct _getUserFriendsByUserId;
//     struct _getUserFriendsByUserIdResponse;
//     struct _getUserByAutetication;
//     struct _getUserByAuteticationResponse;
//     struct _GetEveryWord;
//     struct _GetEveryWordResponse;
//     struct _getAllUsersID;
//     struct _getAllUsersIDResponse;

// The following header files must be included in this order before this one

// #include <WebServices.h>
// #include "EpicWareWeb.Models.xsd.h"
// #include "EpicWareWeb.xsd.h"
// #include "schemas.microsoft.com.2003.10.Serialization.Arrays.xsd.h"

////////////////////////////////////////////////
// C structure definitions for generated types
////////////////////////////////////////////////

typedef struct _getNumberUsers _getNumberUsers;

// typeDescription: n/a
typedef struct _getNumberUsersResponse 
{
    int getNumberUsersResult;
} _getNumberUsersResponse;

typedef struct _getNumberDownloads _getNumberDownloads;

// typeDescription: n/a
typedef struct _getNumberDownloadsResponse 
{
    int getNumberDownloadsResult;
} _getNumberDownloadsResponse;

// typeDescription: n/a
typedef struct _getUserByID 
{
    int id;
    WCHAR* user; // optional
    WCHAR* pass; // optional
} _getUserByID;

// typeDescription: n/a
typedef struct _getUserByIDResponse 
{
    struct User* getUserByIDResult; // optional
} _getUserByIDResponse;

// typeDescription: n/a
typedef struct _getUserFriendsByUserId 
{
    int id;
    WCHAR* user; // optional
    WCHAR* pass; // optional
} _getUserFriendsByUserId;

// typeDescription: n/a
typedef struct _getUserFriendsByUserIdResponse 
{
    unsigned int getUserFriendsByUserIdResultCount;
    _Field_size_opt_(getUserFriendsByUserIdResultCount)struct User** getUserFriendsByUserIdResult; // optional
} _getUserFriendsByUserIdResponse;

// typeDescription: n/a
typedef struct _getUserByAutetication 
{
    WCHAR* user; // optional
    WCHAR* password; // optional
} _getUserByAutetication;

// typeDescription: n/a
typedef struct _getUserByAuteticationResponse 
{
    struct User* getUserByAuteticationResult; // optional
} _getUserByAuteticationResponse;

typedef struct _GetEveryWord _GetEveryWord;

// typeDescription: n/a
typedef struct _GetEveryWordResponse 
{
    unsigned int GetEveryWordResultCount;
    _Field_size_opt_(GetEveryWordResultCount)struct Word* GetEveryWordResult;
} _GetEveryWordResponse;

typedef struct _getAllUsersID _getAllUsersID;

// typeDescription: n/a
typedef struct _getAllUsersIDResponse 
{
    unsigned int getAllUsersIDResultCount;
    _Field_size_opt_(getAllUsersIDResultCount)int* getAllUsersIDResult;
} _getAllUsersIDResponse;

////////////////////////////////////////////////
// Global web service descriptions.
////////////////////////////////////////////////

typedef struct _tempuri_org_xsd
{
    struct // globalElements
    {
        // xml element: getNumberUsers ("http://tempuri.org/")
        // c type: _getNumberUsers
        // elementDescription: tempuri_org_xsd.globalElements.getNumberUsers
        WS_ELEMENT_DESCRIPTION getNumberUsers;
        
        // xml element: getNumberUsersResponse ("http://tempuri.org/")
        // c type: _getNumberUsersResponse
        // elementDescription: tempuri_org_xsd.globalElements.getNumberUsersResponse
        WS_ELEMENT_DESCRIPTION getNumberUsersResponse;
        
        // xml element: getNumberDownloads ("http://tempuri.org/")
        // c type: _getNumberDownloads
        // elementDescription: tempuri_org_xsd.globalElements.getNumberDownloads
        WS_ELEMENT_DESCRIPTION getNumberDownloads;
        
        // xml element: getNumberDownloadsResponse ("http://tempuri.org/")
        // c type: _getNumberDownloadsResponse
        // elementDescription: tempuri_org_xsd.globalElements.getNumberDownloadsResponse
        WS_ELEMENT_DESCRIPTION getNumberDownloadsResponse;
        
        // xml element: getUserByID ("http://tempuri.org/")
        // c type: _getUserByID
        // elementDescription: tempuri_org_xsd.globalElements.getUserByID
        WS_ELEMENT_DESCRIPTION getUserByID;
        
        // xml element: getUserByIDResponse ("http://tempuri.org/")
        // c type: _getUserByIDResponse
        // elementDescription: tempuri_org_xsd.globalElements.getUserByIDResponse
        WS_ELEMENT_DESCRIPTION getUserByIDResponse;
        
        // xml element: getUserFriendsByUserId ("http://tempuri.org/")
        // c type: _getUserFriendsByUserId
        // elementDescription: tempuri_org_xsd.globalElements.getUserFriendsByUserId
        WS_ELEMENT_DESCRIPTION getUserFriendsByUserId;
        
        // xml element: getUserFriendsByUserIdResponse ("http://tempuri.org/")
        // c type: _getUserFriendsByUserIdResponse
        // elementDescription: tempuri_org_xsd.globalElements.getUserFriendsByUserIdResponse
        WS_ELEMENT_DESCRIPTION getUserFriendsByUserIdResponse;
        
        // xml element: getUserByAutetication ("http://tempuri.org/")
        // c type: _getUserByAutetication
        // elementDescription: tempuri_org_xsd.globalElements.getUserByAutetication
        WS_ELEMENT_DESCRIPTION getUserByAutetication;
        
        // xml element: getUserByAuteticationResponse ("http://tempuri.org/")
        // c type: _getUserByAuteticationResponse
        // elementDescription: tempuri_org_xsd.globalElements.getUserByAuteticationResponse
        WS_ELEMENT_DESCRIPTION getUserByAuteticationResponse;
        
        // xml element: GetEveryWord ("http://tempuri.org/")
        // c type: _GetEveryWord
        // elementDescription: tempuri_org_xsd.globalElements.GetEveryWord
        WS_ELEMENT_DESCRIPTION GetEveryWord;
        
        // xml element: GetEveryWordResponse ("http://tempuri.org/")
        // c type: _GetEveryWordResponse
        // elementDescription: tempuri_org_xsd.globalElements.GetEveryWordResponse
        WS_ELEMENT_DESCRIPTION GetEveryWordResponse;
        
        // xml element: getAllUsersID ("http://tempuri.org/")
        // c type: _getAllUsersID
        // elementDescription: tempuri_org_xsd.globalElements.getAllUsersID
        WS_ELEMENT_DESCRIPTION getAllUsersID;
        
        // xml element: getAllUsersIDResponse ("http://tempuri.org/")
        // c type: _getAllUsersIDResponse
        // elementDescription: tempuri_org_xsd.globalElements.getAllUsersIDResponse
        WS_ELEMENT_DESCRIPTION getAllUsersIDResponse;
        
    } globalElements;
    struct // externallyReferencedTypes
    {
        WS_STRUCT_DESCRIPTION getNumberUsers;
        WS_STRUCT_DESCRIPTION getNumberUsersResponse;
        WS_STRUCT_DESCRIPTION getNumberDownloads;
        WS_STRUCT_DESCRIPTION getNumberDownloadsResponse;
        WS_STRUCT_DESCRIPTION getUserByID;
        WS_STRUCT_DESCRIPTION getUserByIDResponse;
        WS_STRUCT_DESCRIPTION getUserFriendsByUserId;
        WS_STRUCT_DESCRIPTION getUserFriendsByUserIdResponse;
        WS_STRUCT_DESCRIPTION getUserByAutetication;
        WS_STRUCT_DESCRIPTION getUserByAuteticationResponse;
        WS_STRUCT_DESCRIPTION GetEveryWord;
        WS_STRUCT_DESCRIPTION GetEveryWordResponse;
        WS_STRUCT_DESCRIPTION getAllUsersID;
        WS_STRUCT_DESCRIPTION getAllUsersIDResponse;
    } externallyReferencedTypes;
} _tempuri_org_xsd;

extern const _tempuri_org_xsd tempuri_org_xsd;

#ifdef __cplusplus
}
#endif

