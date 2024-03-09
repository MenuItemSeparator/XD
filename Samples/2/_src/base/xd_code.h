#pragma once
// LISENCE.txt

#include <assert.h>
#include <iostream>

#include "xd.h"
#include "xd_log.h"

// m*
#define mNONE
#define mTRACE_FUNC()	\
	mNOTE(mFUNC)
#define mBLOCK(text) mNOTE(text)
#define mCODE_BLOCK(text) xd_none
#define mCOMMENT(text)
#define mOLDFUNC(text)	\
	mWARNING(text<<mSPASED(mFUNC)<<"is out of date "<<mLINE)
// Optimization request.
#define mOPTIMFUNC(text)	\
	mWARNING(mPFUNC<<" must be optimised "<<mLINE) xd_pass
#define mISDEBUG()	\
	true
#define mISRELEASE()	\
	false
#define mRELEASEONLY()\
	if(mISRELEASE)
#define mDEBUGONLY(text)	\
	if(mISDEBUG() text)
#define mISDEVELOP	\
	true
#if mISDEBUG != 0
#define mASSERT(term, reason_text)	\
	assert(term)
#else
#define mASSERT(term, reason_text)	\
	if(!(term)){mERRORP(mBRACED(#term)<<reason_text); mXD_DEBUG_STOP(); exit(0);} xd_pass
#endif
#define mOLDBLOCK()	\
	if(false)
#define mREFACTOR_THIS(text) mNONE

// mXD*
#define mXD_RESULT(term,action)	\
	{si4 res = term;	\
	if(A_A != res){mERRORF(#term); {action;}}}

#define mXD_RESULTA(term)	\
	{si4 res = term; if(A_A != res)	\
	{mERRORP(#term); return res;}}

#define mXCALL(function)	\
	{\
		si4 result = function;\
		if(nXD::X_X == result){ mERRORP(#function);\
		return nXD::X_X; }\
	}
#define mRCALL(function, expected)\
	{\
		auto result = function;\
		if(result != expected){\
			mERRORP(mBRACED(#function)<<" return " \
						<<mBRACED(result)<<" expected "<<mBRACED(expected)) }

#define mXASSERT(x)\
		mASSERT(x == nXD::A_A, "AUTODETECT");

#define mXD_RESULT_E(term)	\
	{si4 res = term; if(X_X == res)	\
	{mERRORP(#term); return res;}}

#define mXD_CHECK(term)	\
	{if(!term){mERRORF(#term); return nXD::X_X;}} xd_pass

#define mXD_CHECK_ERR(term, text ,act)\
		if(term){mERRORP(text); act;}

#define mXD_IF(subject, term, action)	\
	if(subject == term) action;

#define mXD_ERROR(text,action)	\
	{mERRORF(text);action;}

#define mXD_FAIL(text) \
	{mERRORP(text); return nXD::X_X;}

#define mDELETE_PTR(ptr) \
	if(ptr) delete prt; ptr = 0x0;

#define mXD_CASE_TO_STR(text) \
	case text: return #text

#define mXD_MAGIC(name, text) text
#define mVAR(name, text) mXD_MAGIC(name, text)

#define mXD_WTF(text) xd_pass
#define mDEF(name, assignment, input, output)\
	info_#name(){mNOTE(mBRACED(##name) << \
		mQUOTED(assignment) \
		<< mQUOTED(input) \
		<< mQUOTED(output));}

// xd*

// I hate templates. Use one and it will corrupt all your sources
#define blood_contract		template

#ifndef override
#	define override xd_none
#endif

#define xd_heap_free // function use no heap
#define xd_override	override
#define xd_low_perf	xd_none
#define xd_deprecated xd_none
#define xd_platform_impl xd_none

// IDE
#ifdef __CDT_PARSER__
#endif
