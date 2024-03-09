#include "../xd.h"
#include "../xd_log.h"
#include "../xd_lang.h"

int main()
{
	si4 signed_32 = -1;
	ui4 unsigned_32 = 1;
	si8 signed_64 = -1;
	ui8 unsigned_64 = 1;
	fl4 float_32 = 1.f;
	fl8 float_64 = 1.;
	szt size = sizeof(szt);
	ptr pointer = &size;
	bln boolean = true;
	ui1 byte = 'a';
	str string = "string";
	x_result operation_result = nXD::A_A;

	// Following operations do nothing, but avoid warnings with unused variables.
	mIGNOREP(signed_32 || signed_64 || unsigned_32 || unsigned_64 || size || pointer);
	mIGNOREP(boolean || byte || string || operation_result);
	mIGNOREP( float_32 > 0|| float_64 > 0);

	mLOG("Testint mLOG\n"); // Testint mLOG
	mNOTE("Testing mNOTE"); // >>>Testing mNOTE
	mERROR("Testing mERROR"); // >>> <!Error:> Testing mERROR < line: [27] >
	mERRORF("Testing mERROR"); // >>> <!Error:>  function: [main] "Testing mERROR" < line: [28] >
	mERRORP("Testing mERROR"); // >>> <!Error:>  pfunction: [int main()] "Testing mERROR" < line: [29] >

	mNOTE("!"<<mSPASED("Testing mSPASED")<<"!"); // >>>! Testing mSPASED !
	mNOTE(mBRACED("Testing mBRACED")); // >>> <Testing mBRACED>
	mNOTE(mDBRACED("Testing mDBRACED")); // >>> <<Testing mDBRACED>>
	mNOTE(mRBRACED("Testing mRBRACED")); // >>> (Testing mRBRACED)
	mNOTE(mSBRACED("Testing mSBRACED")); // >>> [Testing mSBRACED]
	mNOTE(mQBRACED("Testing mQBRACED")); // >>>"Testing mQBRACED"

	mNOTE("Printing:"<<mSPASED(mLINE)<<mSPASED(mFUNC)<<mSPASED(mPFUNC));
	// >>>Printing:  line: [38]    function: [main]    pfunction: [int main()]

	return nXD::fgIncrement(-1);
}
