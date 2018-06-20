/*
 * file_name: platform.h
 * file_detail:
 * created by silver0511
 */

#ifndef __RX_PLATFORM_H__
#define __RX_PLATFORM_H__

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dlfcn.h>
#include <netdb.h>
#include <ifaddrs.h>

#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <thread>

#include "stdafx.h"
//include stl
#include <vector>
#include <queue>
#if __cplusplus > 199711L
#include<unordered_map>
#endif

using namespace std;

RELAX_NAMESPACE_BEGIN

//////////////////////////////////////////////////////////////////////////
#define RX_DEFAULT_CACHE_SIZE 8192
//////////////////////////////////////////////////////////////////////////
typedef signed char       	byte;
typedef unsigned char       ubyte;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;
typedef long long           int64;
typedef unsigned long long	uint64;

typedef uint				IPTYPE;
typedef uint64				SOCKET;

//类型定义
typedef uint64		SESSIONID;	//session id
typedef uint64		USERID;		//user id
typedef uint64		MESSAGEID;	//message id
typedef uint64		SERVERID;	//server id
//////////////////////////////////////////////////////////////////////////

#define  GET_ERRNO()	errno

//hash_map
#if __cplusplus > 199711L
	#define rx_hash_map        std::unordered_map
#else
	#define rx_hash_map        __gnu_cxx::hash_map
#endif

#ifndef INVALID_SOCKET
	#define INVALID_SOCKET  0
#endif


#ifndef zero_memory
	#define zero_memory(p, t) memset(p,0,t)
#endif  //zero_memory


//无效值
#define INVALID_INT32			(0xFFFFFFFF)
#define INVALID_INT64	 		(0xFFFFFFFFFFFFFFFULL)


//////////////////////////////////////////////////////////////////////////
//DLL_EXPORT
// Used for dll exporting and importing
#define  DLL_EXPORT   extern "C"
#define  DLL_IMPORT   extern "C"

// Can't use extern "C" when DLL exporting a class
#define  DLL_CLASS_EXPORT
#define  DLL_CLASS_IMPORT

// Can't use extern "C" when DLL exporting a global
#define  DLL_GLOBAL_EXPORT   extern
#define  DLL_GLOBAL_IMPORT   extern

#define __cdecl


//////////////////////////////////////////////////////////////////////////

#define TO_UPPER(c) ((((c) >= 'a') && ((c) <= 'z')) ? (c)+'A'-'a' : (c))
#define TO_NIBBLE(c) ((((c) >= 'A')&&((c) <= 'F')) ? (((c)-'A')+10) : ((c)-'0'))
#define BYTES_TO_KBPS(n) (float)(((((float)n)*8.0f)/1024.0f))
#define IS_SJIS(a,b) ((a >= 0x81 && a <= 0x9f || a >= 0xe0 && a<=0xfc) && (b >= 0x40 && b <= 0x7e || b >= 0x80 && b<=0xfc))
#define IS_EUC(a) (a >= 0xa1 && a <= 0xfe)
#define IS_ASCII(a) (a <= 0x7f)
#define IS_PLAINASCII(a) (((a >= '0') && (a <= '9')) || ((a >= 'a') && (a <= 'z')) || ((a >= 'A') && (a <= 'Z')))
#define IS_UTF8(a,b) ((a & 0xc0) == 0xc0 && (b & 0x80) == 0x80 )
#define IS_ESCAPE(a,b) ((a == '&') && (b == '#'))
#define IS_HTMLSPECIAL(a) ((a == '&') || (a == '\"') || (a == '\'') || (a == '<') || (a == '>'))

//////////////////////////////////////////////////////////////////////////
//大头小头
#define SWAP16(v) ( ((v&0xff)<<8) | ((v&0xff00)>>8) )
#define SWAP24(v) (((v&0xff)<<16) | ((v&0xff00)) | ((v&0xff0000)>>16) )
#define SWAP32(v) (((v&0xff)<<24) | ((v&0xff00)<<8) | ((v&0xff0000)>>8) | ((v&0xff000000)>>24))
#define SWAP64(v) ((SWAP4(v)|((uint64_t)SWAP4(v+4)<< 32)))


#if _BIG_ENDIAN
	#define CHECK_ENDIAN16(v) v=SWAP16(v)
	#define CHECK_ENDIAN24(v) v=SWAP24(v)
	#define CHECK_ENDIAN32(v) v=SWAP32(v)
	#define CHECK_ENDIAN64(v) v=SWAP64(v)
#else//!_BIG_ENDIAN
	#define CHECK_ENDIAN16
	#define CHECK_ENDIAN24
	#define CHECK_ENDIAN32
	#define CHECK_ENDIAN64
#endif //_BIG_ENDIAN


#if defined(_MSC_VER)
	#pragma warning(push)
	#pragma warning(disable : 4100)	// unreferenced formal parameter
	#pragma warning(disable : 4127) // conditional expression is constant
	#pragma warning(disable : 4201)	// nonstandard extension used : nameless struct/union
	#pragma warning(disable : 4244) // type conversion warning.
	#pragma warning(disable : 4251) //  needs to have dll-interface to be used by clients of class 'xxClass'
#endif //(_MSC_VER)

RELAX_NAMESPACE_END

#endif /* __RX_PLATFORM_H__ */
