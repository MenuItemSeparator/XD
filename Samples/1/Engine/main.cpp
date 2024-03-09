#include <iostream>
#include "App/XD_App.h"
#include "Engine/Base/XD_Code.h"
#include "Engine/Base/Log.h"

int main(int argc, char** argv)
{
	XD_App xd_app{};

	if(xd_app.fTest() == XDN::X_Result::A_A)
	{
		XDN::Log::fError("App test failed");
	}

	return 0;
}
