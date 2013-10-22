// Ls3IconShlExt.h : Declaration of the CLs3IconShlExt

#pragma once
#include "resource.h"       // main symbols
#include <shlobj.h>
#include "Ls3Icons_i.h"


// Positions of the icons in the DLL file
#define IDX_LODLS3 0
#define IDX_LOD0LS3 1
#define IDX_LOD1LS3 2
#define IDX_LOD2LS3 3
#define IDX_LOD3LS3 4
#define IDX_LS3 5



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CLs3IconShlExt

class ATL_NO_VTABLE CLs3IconShlExt :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLs3IconShlExt, &CLSID_Ls3IconShlExt>,
	public ILs3IconShlExt,
	public IPersistFile,
	public IExtractIcon
{
public:
	CLs3IconShlExt()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LS3ICONSHLEXT)

DECLARE_NOT_AGGREGATABLE(CLs3IconShlExt)

BEGIN_COM_MAP(CLs3IconShlExt)
	COM_INTERFACE_ENTRY(ILs3IconShlExt)
	COM_INTERFACE_ENTRY(IPersistFile)
	COM_INTERFACE_ENTRY(IExtractIcon)
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

	// IPersistFile
	STDMETHOD(GetClassID)(CLSID*) { return E_NOTIMPL; }
	STDMETHOD(IsDirty)() { return E_NOTIMPL; }
	STDMETHOD(Save)(LPCOLESTR, BOOL) { return E_NOTIMPL; }
	STDMETHOD(SaveCompleted)(LPCOLESTR) { return E_NOTIMPL; }
	STDMETHOD(GetCurFile)(LPOLESTR*) { return E_NOTIMPL; }

	STDMETHOD(Load)(LPCOLESTR wszFile, DWORD /*dwMode*/)
	{
		wchar_t debug_buf[2048];
		wsprintf(debug_buf, L"Ls3Icons: Load() called for file %s\r\n", wszFile);
		OutputDebugString(debug_buf);

		USES_CONVERSION;
		lstrcpyn(m_szFilename, OLE2CT(wszFile), MAX_PATH);
		return S_OK;
	}

	// IExtractIcon
	STDMETHOD(GetIconLocation)(UINT uFlags, LPTSTR szIconFile, UINT cchMax,
		int* piIndex, UINT* pwFlags)
	{
		wchar_t debug_buf[2048];
		wsprintf(debug_buf, L"Ls3Icons: GetIconLocation() called for file %s\r\n", m_szFilename);
		OutputDebugString(debug_buf);

		// The icons are all in this DLL, so get the full path to the DLL, which
		// we'll return through the szIconFile parameter.
		GetModuleFileName(_AtlBaseModule.GetResourceInstance(), szIconFile,
			cchMax);

		// Default symbol is .ls3
		*piIndex = IDI_LS3;

		size_t fileNameLength = wcslen(m_szFilename);
		LPWSTR endOfString;
		if (fileNameLength >= 8) {
			// Get 8-character substring from end of file name
			// and compare it to .lod.ls3
			endOfString = &(m_szFilename[fileNameLength - 8]);
			if (_wcsicmp(endOfString, L".lod.ls3") == 0) {
				*piIndex = IDX_LODLS3;
			}

			else if (fileNameLength >= 9) {
				// Get 9-character substring from end of file name
				// and compare it to .lodX.ls3 for X in {0, 1, 2, 3}
				endOfString = &(m_szFilename[fileNameLength - 9]);

				if (_wcsicmp(endOfString, L".lod0.ls3") == 0) {
					*piIndex = IDX_LOD0LS3;
				}
				else if (_wcsicmp(endOfString, L".lod1.ls3") == 0) {
					*piIndex = IDX_LOD1LS3;
				}
				else if (_wcsicmp(endOfString, L".lod2.ls3") == 0) {
					*piIndex = IDX_LOD2LS3;
				}
				else if (_wcsicmp(endOfString, L".lod3.ls3") == 0) {
					*piIndex = IDX_LOD3LS3;
				}
			}
		}

		return S_OK;
	}

	STDMETHODIMP Extract(LPCTSTR pszFile, UINT nIconIndex, HICON* phiconLarge,
		HICON* phiconSmall, UINT nIconSize)
	{
		// The shell should extract the image from this DLL itself
		return S_FALSE;
	}


protected:
	// Full path to the file of which the thumbnail should be generated
	TCHAR m_szFilename[MAX_PATH];

};

OBJECT_ENTRY_AUTO(__uuidof(Ls3IconShlExt), CLs3IconShlExt)
