#pragma once

#include <strsafe.h>
#include "Ls3Icons.h"

// Positions of the icons in the DLL file
#define IDX_LODLS3 0
#define IDX_LOD0LS3 1
#define IDX_LOD1LS3 2
#define IDX_LOD2LS3 3
#define IDX_LOD3LS3 4
#define IDX_LS3 5

extern HINSTANCE g_hInst;

class CShellExt: public IPersistFile, public IExtractIcon
{
protected:
	DWORD m_ObjRefCount;

public:
	CShellExt();
	virtual ~CShellExt();

	// IUnknown
	STDMETHOD(QueryInterface)(REFIID riid, LPVOID* ppvObj);
	STDMETHOD_(ULONG, AddRef)(void);
	STDMETHOD_(ULONG, Release)(void);

	// IPersistFile
	STDMETHOD(GetClassID)(CLSID*) { return E_NOTIMPL; }
	STDMETHOD(IsDirty)() { return E_NOTIMPL; }
	STDMETHOD(Save)(LPCOLESTR, BOOL) { return E_NOTIMPL; }
	STDMETHOD(SaveCompleted)(LPCOLESTR) { return E_NOTIMPL; }
	STDMETHOD(GetCurFile)(LPOLESTR*) { return E_NOTIMPL; }

	STDMETHOD(Load)(LPCOLESTR wszFile, DWORD /*dwMode*/);

	// IExtractIcon
	STDMETHOD(GetIconLocation)(UINT uFlags, LPTSTR szIconFile, UINT cchMax, int* piIndex, UINT* pwFlags);
	STDMETHOD(Extract)(LPCTSTR pszFile, UINT nIconIndex, HICON* phiconLarge, HICON* phiconSmall, UINT nIconSize);

protected:
	// Full path to the file of which the thumbnail should be generated
	TCHAR m_szFilename[MAX_PATH];
};
