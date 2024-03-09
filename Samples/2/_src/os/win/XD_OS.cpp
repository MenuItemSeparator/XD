//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: win platform implementation easy class os.
//============================================================================//
#include "xd_os.h"
#include "win/XD_WDGT.h"

#include "base/xd.h"
#include "base/xd_lang.h"
#include "base/xd_code.h"
#include "base/xd_log.h"

#include "math/xd_i2.h"
#include "math/xd_i4.h"

namespace nXD{
//============================================================================//
WDGT*
gfWdgtPtrFromOsType(OS::WDGT_T _descriptor)
{
	WDGT* result = RCAST(WDGT*, _descriptor);
	return result;
}
//============================================================================//
OS::WDGT_T
gfOsTypeFromWdgtPtr(WDGT* _widget)
{
	OS::WDGT_T result = RCAST(OS::WDGT_T, _widget);
	return result;
}
//============================================================================//
OS::OS()
	: m_key_lsnr(nullptr),
	  m_pointer_lsnr(nullptr)
{}
//============================================================================//
x_result
OS::iWorkingDirectoryGetX(XD_STRING& _result)
{
	_result.fAllocate(mXD_MAGIC("minimum size", 1024));
	GetCurrentDirectory(1024, _result.fDataA());
	return A_A;
}
//============================================================================//
OS::WDGT_T
OS::iWdgtCreateP()
{
	WDGT* n_widget = new WDGT;
	const OS::WDGT_T result = gfOsTypeFromWdgtPtr(n_widget);
	return result;
}
//============================================================================//
static LRESULT CALLBACK
DefWndProc(HWND hWnd, UINT msg, WPARAM wparam,LPARAM lparam)
{
	return DefWindowProc(hWnd,msg,wparam,lparam);
}
//============================================================================//
x_result
OS::iWdgtInitX(str _utf8_name, I4 _border, WDGT_T _wdgt )
{
mXD_WTF("Legacy stupid code!");
mBLOCK("Prepare widget");
	if(_wdgt->m_wdgt_class.fSize() == 0)
		_wdgt->m_wdgt_class.fSet("XD_WDGT_CLASS");
	if(_wdgt->m_hinstance == nullptr)
		_wdgt->m_hinstance = GetModuleHandle(nullptr);

	str class_name = _wdgt->m_wdgt_class.fGet();
	WDGT* wdgt = gfWdgtPtrFromOsType(_wdgt);

	if(nullptr == wdgt){
		mERRORP("No wdgt ptr");
		return X_X;
	}

mBLOCK("Creating window");
	WNDCLASSEXA wndcl;
	memset(&wndcl,0,sizeof(WNDCLASSEX));
	wndcl.lpszClassName = class_name;
	wndcl.cbSize = sizeof(WNDCLASSEX);
	wndcl.hbrBackground = HBRUSH(3);
	wndcl.hInstance = _wdgt->m_hinstance;
	wndcl.hIcon = nullptr;
	wndcl.hIconSm = nullptr;
	wndcl.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndcl.lpszMenuName = nullptr;
	wndcl.style = CS_HREDRAW | CS_VREDRAW;
	wndcl.cbWndExtra = 0;
	wndcl.cbClsExtra = 0;
	wndcl.lpfnWndProc = DefWndProc;

mBLOCK("Wnd class create");
	si4 hres = RegisterClassExA(&wndcl);
	if(!hres)
	{//1
		mERROR("wdgt class creation");
		return X_X;
	}//1

mBLOCK("Window create");
	DWORD exstyle = 0;
	UINT  wnd_style = 0;
	if(true)
	{//1
		wnd_style = WS_POPUP;
		exstyle = WS_EX_WINDOWEDGE;
	}//1

	HWND core = CreateWindowExA(exstyle, class_name, _utf8_name, wnd_style,
			_border.l,
			_border.t,
			_border.r,
			_border.d,
			nullptr, nullptr, GetModuleHandle(nullptr), wdgt );
	if(!core)
	{//1
		mERROR("wdgt creation");
		return X_X;
	}//1

	wdgt->fSetHwnd(core);
	wdgt->fSetMode(SCAST(si4, wnd_style));
	wdgt->fSizeA() = _border.fSize();

	return A_A;
}
//============================================================================//
x_result
OS::iWdgtDestroyX(WDGT_T _wdgt)
{
	BOOL result = DestroyWindow(_wdgt->m_core);
	UnregisterClassA(_wdgt->m_wdgt_class.fGet(), _wdgt->m_hinstance);
	mXD_CHECK(result);
	return A_A;
}
//============================================================================//
si4
OS::iWdgtShowX(bool _do, WDGT_T _wdgt)
{
	WDGT* wdgt = gfWdgtPtrFromOsType(_wdgt);
	if(!wdgt)
	{
		mERRORF("it is no widget");
		return X_X;
	}
	if(_do)
	{
		ShowWindow(wdgt->fGetHwnd(),SW_SHOWNORMAL);
	}
	else
	{
		ShowWindow(wdgt->fGetHwnd(),SW_HIDE);
	}
	return A_A;
}
//============================================================================//
#define mTRANSLATE_VKODE(from, to) case from: res = to; break
inline
XDE_KEY
gTranslateKey(const MSG& msg)
{
	XDE_KEY res = XDE_KEY_UNKNOWN;
	switch(msg.wParam)
	{//1
		mTRANSLATE_VKODE(   VK_LEFT,       XDE_KEY_LEFT     );
		mTRANSLATE_VKODE(   VK_RIGHT,      XDE_KEY_RIGHT    );
		mTRANSLATE_VKODE(   VK_UP,         XDE_KEY_UP       );
		mTRANSLATE_VKODE(   VK_DOWN,       XDE_KEY_DOWN     );
		mTRANSLATE_VKODE(   VK_ESCAPE,     XDE_KEY_ESC      );
		mTRANSLATE_VKODE(   VK_SPACE,      XDE_KEY_SPACE    );
	}//1
	return res;
}
#undef mTRANSLATE_VKODE
//============================================================================//
si4
OS::fSyncX()
{
	MSG msg;
	memset(&msg,0,sizeof(MSG));
	XDE_INPUT input_type = XDE_INPUT_;
	XDE_KEY key = XDE_KEY_;
	while(PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
	{//1
		TranslateMessage(&msg);
		switch(msg.message)
		{//2
		case WM_LBUTTONDOWN:
			input_type = XDE_INPUT_DOWN;
			key = XDE_KEY_MOUSE_L;
			break;
		case WM_KEYDOWN:
			if(m_key_lsnr != nullptr)
			{//3
				INPUT_KEY result;
				result.type = XDE_INPUT_DOWN;
				result.key = gTranslateKey(msg);
				m_key_lsnr->onKey(result);
			}//3
			break;
		case WM_MOUSEMOVE:
			if(!m_pointer_lsnr == false)
			{
				POINT pos;
				GetCursorPos(&pos);
				RECT rt;
				GetWindowRect(msg.hwnd, &rt);
				nXD::I4 m_pos(SCAST(si4, pos.x),
							SCAST(si4, pos.y),
							SCAST(si4, rt.left),
							SCAST(si4, rt.top));
				m_pointer_lsnr->onPointer(0, m_pos);
			}
		}//2

		mXD_WTF();
		if( m_key_lsnr && input_type != XDE_INPUT_ && key != XDE_KEY_)
		{
			INPUT_KEY result;
			result.type = input_type;
			result.key = key;
			m_key_lsnr->onKey(result);
		}
		DispatchMessage(&msg);
	}//1
	return A_A;
}
//============================================================================//
uip
OS::iWdgtDescriptorGet(OS::WDGT_T _wdgt)
{
	WDGT* wdgt = gfWdgtPtrFromOsType(_wdgt);
	return RCAST(uip, wdgt->fGetHwnd());
}
//============================================================================//
si4
OS::iScreenSizeGetX(nXD::I2& xd_out result)
{
	result.x =  GetSystemMetrics(SM_CXSCREEN);
	result.y =  GetSystemMetrics(SM_CYSCREEN);
	return A_A;
}
//============================================================================//
void
OS::iWdgtCursorGet(OS::WDGT_T _wdgt, nXD::F4& _cur)
{
	WDGT* wdgt = gfWdgtPtrFromOsType(_wdgt);
	POINT pos;
	GetCursorPos(&pos);
	RECT rt;
	GetWindowRect(wdgt->fGetHwnd(), &rt);
	_cur.fSet(SCAST(si4, pos.x),
			  SCAST(si4, pos.y),
			  SCAST(si4, rt.left),
			  SCAST(si4, rt.top));
}
//============================================================================//
si4
OS::iCurentDirectorySetX(const char* _path)
{
	BOOL result = SetCurrentDirectoryA(_path);

	if(result != 0)
		return A_A;

	return X_X;
}
//============================================================================//
x_result
OS::iGetSystemErrorX(XD_STRING& _err_str)
{
	LPVOID lpMsgBuf = nullptr;
	DWORD dw = GetLastError();
	if(!dw)
		return A_A;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		RCAST(LPTSTR, &lpMsgBuf),
		0, nullptr );

	_err_str.fSet(RCAST(str, lpMsgBuf));

	LocalFree(lpMsgBuf);
	return X_X;
}
//============================================================================//
nXD::I2&
OS::iWdgtSizeA(WDGT_T wdgt)
{
	return wdgt->fSizeA();
}
//============================================================================//
}//ns
