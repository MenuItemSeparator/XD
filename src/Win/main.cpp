#include "Solution.h"

#include <vector>

int main()
{
    std::vector<void*> t;
    nXD::Solution app;
    if (app.fn_Init() != 1)
        return -1;
    if (app.fn_Run() != 1)
        return -1; 
    return 1;
}
