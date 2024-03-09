#pragma once

namespace XDN{

typedef bool bln;

class X_Result
{
	int ReturnCode = 0;
public:
	enum X_Codes
	{
		X_X = -1, // Critical error
		O_O, // Error, that can be handled.
		A_A // Good.
	};
public:
	X_Result() : ReturnCode(X_X) {}
	X_Result(int _i) : ReturnCode(_i) {}

	// Check result status is OK.
	bln fCheckResult() { return ReturnCode == A_A; }
};

}// XDN
