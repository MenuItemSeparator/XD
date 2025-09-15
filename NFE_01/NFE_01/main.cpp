#include <iostream>
#include "Engine/Core/OldStyleExceptionFlow.h"

using namespace std;



int main()
{
    XD::X_Test x_test;


    cout << (x_test.fnIsSuccess()? "success X test" : "failed X test") << endl;
    return 0;
}
