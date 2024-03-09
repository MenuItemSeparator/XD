#pragma once

#include "base/xd.h"
#include "base/xd_lang.h"
#include "base/xd_type.h"
#include "math/xd_f4.h"
#include "base/xd_callback.h"
#include "base/xd_string.h"
#include "math/xd_i2.h"
#include "math/xd_i4.h"
#include "math/xd_f2.h"

namespace nXD{

struct WDGT;

class OS
{
public xd_types:

	struct INPUT_KEY
	{
		XDE_INPUT	type;
		XDE_KEY		key;
	};

	enum HandleResult {
		HandleResult_Error = -1,
		HandleResult_Ok = 0,
		HandleResult_Interupt = 1,
		HandleResult_,
	};

	class KeyListener {
	public:
		virtual HandleResult onKey(const INPUT_KEY&) = 0;

		virtual ~KeyListener() {}
	};

	class PointerListener{
	public:
		virtual HandleResult onPointer(si4, const I4&) = 0;

		virtual ~PointerListener() {}
	};

	using WDGT_T = WDGT*;
	//typedef	WDGT* WDGT_T;

public xd_functional:
	OS();

	si4 fSyncX();
	si4 fRunX()
	{
		mFUNC_IMPL_ERR();
		mSNIPLET()
		{
			while(true)
				fSyncX();
		}
		return X_X;
	}
	x_result fDestroyX() { /*TODO:fDestroyX*/ return A_A;}

	OS& fKeyListenerSetA(KeyListener* _value){
		m_key_lsnr = _value;
		return *this;
	}

	OS& fPointerListenerSetA(PointerListener* _value){
		m_pointer_lsnr = _value;
		return *this;
	}

public xd_interface:
	static x_result iScreenSizeGetX(nXD::I2& xd_out result);
	static x_result iCurentDirectorySetX(str _path);
	static x_result iWorkingDirectoryGetX(XD_STRING& _result);
	static x_result iGetSystemErrorX(XD_STRING& _err_str);

public xd_func_block("Widget"):
	/// Create widget context.
	static WDGT_T iWdgtCreateP();
	static x_result iWdgtDestroyX(WDGT_T _wdgt);

	/// Initialize widget context.
	static x_result iWdgtInitX(const char* _utf8_name,
							   nXD::I4 _border,
							   WDGT_T _wdgt );
	/// Get cursor position relative widget.
	static void iWdgtCursorGet(WDGT_T _wdgt, nXD::F4& _cur);
	// Show/hide widget.
	static si4 iWdgtShowX(bool _do, WDGT_T _wdgt);
	/// Getting widget descriptor.
	static uip iWdgtDescriptorGet(WDGT_T wdgt);
	static nXD::I2& iWdgtSizeA(WDGT_T _wdgt);

private xd_data:
	KeyListener* m_key_lsnr;
	PointerListener* m_pointer_lsnr;
};

}//ns

