/*
 * file_name: stdafx.h
 * file_detail:
 * created by silver0511
 */

#ifndef __RX__STDAFX_H__
#define __RX__STDAFX_H__

#ifndef RELAX_NAMESPACE
    #define RELAX_NAMESPACE relax
#endif
#ifndef RELAX_NAMESPACE_BEGIN
    #define RELAX_NAMESPACE_BEGIN namespace relax {
#endif
#ifndef RELAX_NAMESPACE_END
    #define RELAX_NAMESPACE_END }
#endif
#ifndef USING_RELAX_NAMESPACE
    #define USING_RELAX_NAMESPACE using namespace relax;
#endif

RELAX_NAMESPACE_BEGIN

#ifndef OUT
    #define OUT
#endif


#ifndef SAFE_DELETE
    #define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif
#ifndef SAFE_RELEASE
    #define SAFE_RELEASE(p)		 { if(p) { (p)->release(); (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
    #define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif

#ifndef TRUE
    #define TRUE                (1)
#endif
#ifndef FALSE
    #define FALSE               (0)
#endif
#ifndef NULL
    #define NULL				(0)
#endif

RELAX_NAMESPACE_END

#endif //__RX__STDAFX_H__
