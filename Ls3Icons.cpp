// Ls3Icons.cpp: implementation of the CLs3Icons class.
//
//////////////////////////////////////////////////////////////////////
#include <shlobj.h>
#include <windows.h>
#include <strsafe.h>

#include "Ls3Icons.h"

#include "ClassFactory.h"

#include <olectl.h>

// data
HINSTANCE g_hInst;
UINT g_DllRefCount;

#pragma data_seg(".text")
#define INITGUID
#include <initguid.h>
#include "Guid.h"
#pragma data_seg()

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		g_hInst = (HINSTANCE)hModule;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

/*---------------------------------------------------------------*/
// DllCanUnloadNow()
/*---------------------------------------------------------------*/
STDAPI DllCanUnloadNow(VOID) { return (g_DllRefCount ? S_FALSE : S_OK); }

/*---------------------------------------------------------------*/
// DllGetClassObject()
/*---------------------------------------------------------------*/
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppReturn)
{
	*ppReturn = NULL;

	// do we support the CLSID?
	if (!IsEqualCLSID(rclsid, CLSID_Ls3Icons))
		return CLASS_E_CLASSNOTAVAILABLE;

	// call the factory
	CClassFactory* pClassFactory = new CClassFactory();
	if (pClassFactory == NULL)
		return E_OUTOFMEMORY;

	// query interface for the a pointer
	HRESULT hResult = pClassFactory->QueryInterface(riid, ppReturn);
	pClassFactory->Release();
	return hResult;
}

/*---------------------------------------------------------------*/
// DllGetRegisterServer()
/*---------------------------------------------------------------*/

typedef struct {
	HKEY hRootKey;
	LPCTSTR lpszSubKey;
	LPCTSTR lpszValueName;
	LPCTSTR lpszData;
} REGSTRUCT, *LPREGSTRUCT;

STDAPI DllRegisterServer(VOID)
{
	INT i;
	HKEY hKey;
	LRESULT lResult;
	DWORD dwDisp;
	TCHAR szSubKey[MAX_PATH];
	TCHAR szCLSID[MAX_PATH];
	TCHAR szModule[MAX_PATH];
	LPWSTR pwsz;
	STRSAFE_LPWSTR ppszDestEnd;

	// get the CLSID in string form
	StringFromIID(CLSID_Ls3Icons, &pwsz);

	if (pwsz) {
		*szCLSID = 0;
		// WideCharToMultiByte(CP_ACP, 0, pwsz, -1, szCLSID, ARRAYSIZE(szCLSID), NULL, NULL);
		StringCchCopy(szCLSID, ARRAYSIZE(szCLSID), pwsz);

		LPMALLOC pMalloc;
		CoGetMalloc(1, &pMalloc);
		if (pMalloc) {
			pMalloc->Free(pwsz);
			pMalloc->Release();
		}
	}

	// get this DLL's path and file name
	GetModuleFileName(g_hInst, szModule, ARRAYSIZE(szModule));

	// CLSID entries
	REGSTRUCT ClsidEntries[] = {
		// clang-format off
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s"), NULL, TEXT("Ls3Icons"),
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s"), TEXT("InfoTip"), TEXT("Ls3Icons."),
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s\\InprocServer32"), NULL, TEXT("%s"),
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s\\InprocServer32"), TEXT("ThreadingModel"), TEXT("Apartment"),
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s\\DefaultIcon"), NULL, TEXT("%s,0"),
		NULL, NULL, NULL, NULL
		// clang-format on
	};

	for (i = 0; ClsidEntries[i].hRootKey; i++) {
		// create the sub key string.
		StringCchPrintf(szSubKey, ARRAYSIZE(szSubKey), ClsidEntries[i].lpszSubKey, szCLSID);
		lResult = RegCreateKeyEx(
			ClsidEntries[i].hRootKey, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &dwDisp);

		if (lResult == NOERROR) {
			TCHAR szData[MAX_PATH];
			ppszDestEnd = &szData[ARRAYSIZE(szData)] - 1;
			StringCchPrintfEx(szData, ARRAYSIZE(szData), &ppszDestEnd, nullptr, STRSAFE_FILL_BEHIND_NULL,
				ClsidEntries[i].lpszData, szModule);
			lResult = RegSetValueEx(hKey, ClsidEntries[i].lpszValueName, 0, REG_SZ, (LPBYTE)szData,
				(LPBYTE)ppszDestEnd - (LPBYTE)&szData[0] + 2);

			RegCloseKey(hKey);
		}
		else
			return SELFREG_E_CLASS;
	}

	// File extension
	lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT, TEXT("Zusi3DEditorls3"), 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_WRITE, NULL, &hKey, &dwDisp);

	if (lResult != NOERROR) {
		return SELFREG_E_CLASS;
	}
	else {
		TCHAR szData[MAX_PATH];
		ppszDestEnd = &szData[ARRAYSIZE(szData)] - 1;
		StringCchCopyEx(szData, ARRAYSIZE(szData), TEXT("%1"), &ppszDestEnd, nullptr, STRSAFE_FILL_BEHIND_NULL);
		lResult = RegSetValueEx(
			hKey, TEXT("DefaultIcon"), 0, REG_SZ, (LPBYTE)szData, (LPBYTE)ppszDestEnd - (LPBYTE)&szData[0] + 2);

		RegCloseKey(hKey);
	}

	lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT, TEXT("Zusi3DEditorls3\\ShellEx\\IconHandler"), 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &dwDisp);

	if (lResult != NOERROR) {
		return SELFREG_E_CLASS;
	}
	else {
		TCHAR szData[MAX_PATH];
		ppszDestEnd = &szData[ARRAYSIZE(szData)] - 1;
		StringCchCopyEx(szData, ARRAYSIZE(szData), szCLSID, &ppszDestEnd, nullptr, STRSAFE_FILL_BEHIND_NULL);
		lResult
			= RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)szData, (LPBYTE)ppszDestEnd - (LPBYTE)&szData[0] + 2);

		RegCloseKey(hKey);
	}

	// register the extension as approved by NT
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	GetVersionEx(&osvi);

	if (VER_PLATFORM_WIN32_NT == osvi.dwPlatformId) {
		StringCchCopy(szSubKey, ARRAYSIZE(szSubKey),
			TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Shell"
				 " Extensions\\Approved"));
		lResult = RegCreateKeyEx(
			HKEY_LOCAL_MACHINE, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &dwDisp);

		if (lResult == NOERROR) {
			TCHAR szData[MAX_PATH];
			ppszDestEnd = &szData[ARRAYSIZE(szData)] - 1;
			StringCchCopyEx(
				szData, ARRAYSIZE(szData), TEXT("Ls3Icons"), &ppszDestEnd, nullptr, STRSAFE_FILL_BEHIND_NULL);
			lResult = RegSetValueEx(
				hKey, szCLSID, 0, REG_SZ, (LPBYTE)szData, (LPBYTE)ppszDestEnd - (LPBYTE)&szData[0] + 2);

			RegCloseKey(hKey);
		}
		else
			return SELFREG_E_CLASS;
	}

	return S_OK;
}

/*---------------------------------------------------------------*/
// DllUnregisterServer()
/*---------------------------------------------------------------*/
STDAPI DllUnregisterServer(VOID)
{
	INT i;
	HKEY hKey;
	LRESULT lResult;
	// DWORD dwDisp;
	TCHAR szSubKey[MAX_PATH];
	TCHAR szCLSID[MAX_PATH];
	LPWSTR pwsz;

	// get the CLSID in string form
	StringFromIID(CLSID_Ls3Icons, &pwsz);

	if (pwsz) {
		*szCLSID = 0;
		// WideCharToMultiByte(CP_ACP, 0, pwsz, -1, szCLSID, ARRAYSIZE(szCLSID), NULL, NULL);
		StringCchCopy(szCLSID, ARRAYSIZE(szCLSID), pwsz);
		LPMALLOC pMalloc;
		CoGetMalloc(1, &pMalloc);
		if (pMalloc) {
			pMalloc->Free(pwsz);
			pMalloc->Release();
		}
	}

	// CLSID entries
	REGSTRUCT ClsidEntries[] = {
		// clang-format off
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s\\InprocServer32"), NULL, NULL,
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s\\DefaultIcon"), NULL, NULL,
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s"), NULL, NULL,
		NULL, NULL, NULL, NULL
		// clang-format on
	};

	for (i = 0; ClsidEntries[i].hRootKey; i++) {
		// create the sub key string.
		StringCchPrintf(szSubKey, ARRAYSIZE(szSubKey), ClsidEntries[i].lpszSubKey, szCLSID);
		lResult = RegDeleteKey(ClsidEntries[i].hRootKey, szSubKey);
	}

	// File extension
	lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, TEXT("Zusi3DEditorls3"), 0, KEY_SET_VALUE, &hKey);
	if (lResult == ERROR_SUCCESS) {
		lResult = RegDeleteValue(hKey, TEXT("DefaultIcon"));
		RegCloseKey(hKey);
	}

	lResult = RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("Zusi3DEditorls3\\ShellEx\\IconHandler"));

	// register the extension as approved by NT
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	GetVersionEx(&osvi);

	if (VER_PLATFORM_WIN32_NT == osvi.dwPlatformId) {
		lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
			TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Shell"
				 " Extensions\\Approved"),
			0, KEY_SET_VALUE, &hKey);
		if (lResult == ERROR_SUCCESS) {
			lResult = RegDeleteValue(hKey, szCLSID);
			RegCloseKey(hKey);
		}
	}

	return S_OK;
}
