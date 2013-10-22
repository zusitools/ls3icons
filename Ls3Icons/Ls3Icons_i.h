

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0602 */
/* at Tue Oct 22 00:58:03 2013
 */
/* Compiler settings for Ls3Icons.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0602 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Ls3Icons_i_h__
#define __Ls3Icons_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILs3IconShlExt_FWD_DEFINED__
#define __ILs3IconShlExt_FWD_DEFINED__
typedef interface ILs3IconShlExt ILs3IconShlExt;

#endif 	/* __ILs3IconShlExt_FWD_DEFINED__ */


#ifndef __Ls3IconShlExt_FWD_DEFINED__
#define __Ls3IconShlExt_FWD_DEFINED__

#ifdef __cplusplus
typedef class Ls3IconShlExt Ls3IconShlExt;
#else
typedef struct Ls3IconShlExt Ls3IconShlExt;
#endif /* __cplusplus */

#endif 	/* __Ls3IconShlExt_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ILs3IconShlExt_INTERFACE_DEFINED__
#define __ILs3IconShlExt_INTERFACE_DEFINED__

/* interface ILs3IconShlExt */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ILs3IconShlExt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EFD58E87-69A5-4340-880C-5FD1475CE09D")
    ILs3IconShlExt : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct ILs3IconShlExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILs3IconShlExt * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILs3IconShlExt * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILs3IconShlExt * This);
        
        END_INTERFACE
    } ILs3IconShlExtVtbl;

    interface ILs3IconShlExt
    {
        CONST_VTBL struct ILs3IconShlExtVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILs3IconShlExt_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILs3IconShlExt_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILs3IconShlExt_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILs3IconShlExt_INTERFACE_DEFINED__ */



#ifndef __Ls3IconsLib_LIBRARY_DEFINED__
#define __Ls3IconsLib_LIBRARY_DEFINED__

/* library Ls3IconsLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Ls3IconsLib;

EXTERN_C const CLSID CLSID_Ls3IconShlExt;

#ifdef __cplusplus

class DECLSPEC_UUID("9B289D33-F22D-459E-9D97-CD9FBB326D35")
Ls3IconShlExt;
#endif
#endif /* __Ls3IconsLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


