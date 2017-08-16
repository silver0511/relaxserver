/*
 * file_name: LogConst.h
 * file_detail:log const define
 * created by silver0511
 */


#ifndef __RX__LOGCONST_H__
#define __RX__LOGCONST_H__

#include "stdafx.h"

RELAX_NAMESPACE_BEGIN

#define FILE_NAME_LENGTH	                (255)	    // max file size
#define DEF_MAX_TRANS_BUFFER                (128)
#define DEF_ONCE_LOG_BUFFER_SIZE            (2048)	    // max one log size 2k
#define DEF_LOG_MAX_LINE                    (999999)
#define DEF_LOG_TRACE_COUNT                 (10000)     // write log max cache

//log display type
#define		DEF_DISPLAY_TYPE_FILE			(1)			// write log file
#define		DEF_DISPLAY_TYPE_CONSOLE		(2)			// console log
#define		DEF_DISPLAY_TYPE_THREAD			(3)			// write log in logthread
#define		DEF_DISPLAY_TYPE_ALL			(4)			// both

//priority from 0->9 with high->low
#define LOG_EMERG       (0)
#define LOG_ALERT       (1)
#define LOG_CRIT        (2)
#define LOG_ERR         (3)
#define LOG_WARNING     (4)
#define LOG_NOTICE      (5)
#define LOG_INFO        (6)
#define LOG_DEBUG       (7)
#define LOG_DEBUG_1	    (8)
#define LOG_DEBUG_2	    (9)

#define __FUNCTION__ __PRETTY_FUNCTION__

RELAX_NAMESPACE_END

#endif //__RX__LOGCONST_H__
