#pragma once
#include <Windows.h>
#include <wingdi.h>

namespace XD
{
    typedef HGLRC WINAPI tWGLCreateContextAttribsARB(HDC hdc, HGLRC hShareContext, const int *attribList);
    typedef BOOL WINAPI tWGLChoosePixelFormatARB(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
    
    typedef HGLRC(tWGLCreateContextProcPtr)(HDC);
    typedef BOOL(tWGLDeleteContext)(HGLRC);
}