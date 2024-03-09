#pragma once
//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: logging tools.
//============================================================================//
#include "xd.h"
#include <iostream>

#define mSPASED(text)		" "<<text<<" "
#define mBRACED(text)		" <"<<text<<"> "
#define mDBRACED(text)		" <<"<<text<<">> "
#define mSBRACED(text)		" ["<<text<<"] "
#define mRBRACED(text)		" ("<<text<<") "
#define mQBRACED(text)		'\"'<< text << '\"'
#define mLINE				" line: ["<<__LINE__<<"] "
#define mFUNC				" function: ["<<__FUNCTION__<<"] "
#define mPFUNC				" pfunction: ["<<__PRETTY_FUNCTION__<<"] "

#define mLOG(text)			std::cout<<text
#define mNOTE(text)			mLOG(">>>"<<text<<'\n')

#define mDEV(text)			mNOTE(text<<mLINE)
#define mDEV_VAR(text)		mDEV(#text<<" = "<<text)
#define mDEV_TRACE(text)	mDEV(text<<mPFUNC<<mLINE)
#define mDEV_FUNC(text)		mDEV(mFUNC)
#define mDEV_PFUNC(text)	mDEV(mPFUNC)

#define mERROR(text)\
	{mBREAK_ERR(); mNOTE(mBRACED("!Error:")<<text<<mBRACED(mLINE));} mPASS

#define mERRORF(text)		mERROR(mFUNC<<mQBRACED(text))
#define mERRORP(text)		mERROR(mPFUNC<<mQBRACED(text))
#define mFAIL(text)			{mERRORP(text); return X_X;}

#define mFAIL_SEARCH(text) \
	mERRORF("search failed: "<<text)

#define mFORBIDDEN_OPERATON() \
	{mERRORP("This operation is forbidden"); exit(0);}

#define mWARNING(text)		//mNOTE("!Warn "<<text<<mLINE)
#define mWARNINGF(text)		mNOTE("!Warning: "<<text<<mPFUNC<<mLINE)
#define mFUNC_IMPL_ERR()	mWARNINGF("This function doesn't completed")
#define mSNIPLET()			if(false)
#define mTODO(text)

