#include <Windows.h>
#include "tp_stub.h"
//#include "KAGParser.h"

extern iTJSDispatch2 * TVPCreateNativeClass_KAGParser();

#define EXPORT(hr) extern "C" __declspec(dllexport) hr __stdcall

#ifdef _MSC_VER
// アーキテクチャ別にエクスポート名を分岐
  #ifdef _WIN64
    #pragma comment(linker, "/EXPORT:V2Link=V2Link")
    #pragma comment(linker, "/EXPORT:V2Unlink=V2Unlink")
  #else
    #pragma comment(linker, "/EXPORT:V2Link=_V2Link@4")
    #pragma comment(linker, "/EXPORT:V2Unlink=_V2Unlink@0")
  #endif
#endif

// DllMain
BOOL WINAPI DllEntryPoint(HINSTANCE hinst, DWORD reason, LPVOID reserved)
{
	return TRUE;
}

static iTJSDispatch2 *origKAGParser = NULL;
static tjs_int GlobalRefCountAtInit = 0;

//---------------------------------------------------------------------------
EXPORT(HRESULT) V2Link(iTVPFunctionExporter *exporter)
{
	TVPInitImportStub(exporter);

	iTJSDispatch2 * global = TVPGetScriptDispatch();
	if (global) {
		tTJSVariant val;
		if (TJS_SUCCEEDED(global->PropGet(0, TJS_W("KAGParser"), NULL, &val, global))) {
			origKAGParser = val.AsObject();
			val.Clear();
		}
		iTJSDispatch2 * tjsclass = TVPCreateNativeClass_KAGParser();
		val = tTJSVariant(tjsclass);
		tjsclass->Release();
		global->PropSet(TJS_MEMBERENSURE, TJS_W("KAGParser"), NULL, &val, global);
		global->Release();
	}
	GlobalRefCountAtInit = TVPPluginGlobalRefCount;
	return S_OK;
}
//---------------------------------------------------------------------------
EXPORT(HRESULT) V2Unlink()
{
	if(TVPPluginGlobalRefCount > GlobalRefCountAtInit) return E_FAIL;

	iTJSDispatch2 * global = TVPGetScriptDispatch();
	if (global)	{
		global->DeleteMember(0, TJS_W("KAGParser"), NULL, global);
		if (origKAGParser) {
			tTJSVariant val(origKAGParser);
			origKAGParser->Release();
			origKAGParser = NULL;
			global->PropSet(TJS_MEMBERENSURE, TJS_W("KAGParser"), NULL, &val, global);
		}
		global->Release();
	}

	TVPUninitImportStub();
	return S_OK;
}
