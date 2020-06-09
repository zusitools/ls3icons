// ShellExt.cpp: implementation of the CShellExt class.
//
//////////////////////////////////////////////////////////////////////
#include <shlobj.h>
#include <tchar.h>
#include <windows.h>

#include "Guid.h"
#include "ShellExt.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShellExt::CShellExt() { m_ObjRefCount = 1; }

CShellExt::~CShellExt() { }

STDMETHODIMP_(DWORD) CShellExt::Release(void)
{
	if (--m_ObjRefCount == 0) {
		delete this;
		return 0;
	}

	return m_ObjRefCount;
}

STDMETHODIMP_(DWORD) CShellExt::AddRef(void) { return ++m_ObjRefCount; }

STDMETHODIMP CShellExt::QueryInterface(REFIID riid, LPVOID* ppReturn)
{
	*ppReturn = NULL;

	if (IsEqualIID(riid, IID_IUnknown))
		*ppReturn = this;
	else if (IsEqualIID(riid, IID_IPersistFile))
		*ppReturn = (IPersistFile*)this;
	else if (IsEqualIID(riid, IID_IExtractIcon))
		*ppReturn = (IExtractIcon*)this;

	if (*ppReturn) {
		LPUNKNOWN pUnk = (LPUNKNOWN)(*ppReturn);
		pUnk->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

STDMETHODIMP CShellExt::Load(LPCOLESTR wszFile, DWORD /*dwMode*/)
{
	wchar_t debug_buf[2048];
	StringCchPrintf(debug_buf, ARRAYSIZE(debug_buf), L"Ls3Icons: Load() called for file %s\r\n", wszFile);
	OutputDebugString(debug_buf);

	return StringCchCopy(m_szFilename, ARRAYSIZE(m_szFilename), wszFile);
}

STDMETHODIMP CShellExt::GetIconLocation(UINT uFlags, LPTSTR szIconFile, UINT cchMax, int* piIndex, UINT* pwFlags)
{
	wchar_t debug_buf[2048];
	StringCchPrintf(
		debug_buf, ARRAYSIZE(debug_buf), L"Ls3Icons: GetIconLocation() called for file %s\r\n", m_szFilename);
	OutputDebugString(debug_buf);

	// The icons are all in this DLL, so get the full path to the DLL, which
	// we'll return through the szIconFile parameter.
	GetModuleFileName(g_hInst, szIconFile, cchMax);

	// Default symbol is .ls3
	*piIndex = IDX_LS3;

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

	StringCchPrintf(debug_buf, ARRAYSIZE(debug_buf), L"Ls3Icons: GetIconLocation() returning file %s, index %d\r\n",
		szIconFile, *piIndex);
	OutputDebugString(debug_buf);

	return S_OK;
}

STDMETHODIMP CShellExt::Extract(
	LPCTSTR pszFile, UINT nIconIndex, HICON* phiconLarge, HICON* phiconSmall, UINT nIconSize)
{
	// The shell should extract the image from this DLL itself
	return S_FALSE;
}
