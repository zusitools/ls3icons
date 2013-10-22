// dllmain.h : Declaration of module class.

class CLs3IconsModule : public ATL::CAtlDllModuleT< CLs3IconsModule >
{
public :
	DECLARE_LIBID(LIBID_Ls3IconsLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_LS3ICONS, "{196FBE9A-7D52-4FC1-96E2-2813EDDAEA06}")
};

extern class CLs3IconsModule _AtlModule;
