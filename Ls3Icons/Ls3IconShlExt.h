// Ls3IconShlExt.h : Declaration of the CLs3IconShlExt

#pragma once
#include "resource.h"       // main symbols



#include "Ls3Icons_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CLs3IconShlExt

class ATL_NO_VTABLE CLs3IconShlExt :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLs3IconShlExt, &CLSID_Ls3IconShlExt>,
	public ILs3IconShlExt
{
public:
	CLs3IconShlExt()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LS3ICONSHLEXT)

DECLARE_NOT_AGGREGATABLE(CLs3IconShlExt)

BEGIN_COM_MAP(CLs3IconShlExt)
	COM_INTERFACE_ENTRY(ILs3IconShlExt)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



};

OBJECT_ENTRY_AUTO(__uuidof(Ls3IconShlExt), CLs3IconShlExt)
