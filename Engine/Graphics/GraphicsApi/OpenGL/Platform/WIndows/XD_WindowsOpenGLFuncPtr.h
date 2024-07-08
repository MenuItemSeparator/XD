#pragma once
#include <Windows.h>
#include <wingdi.h>

namespace XD
{
    typedef PROC(tGLGetProcAddress)(LPCSTR);
    typedef HGLRC(tWGLCreateContextProcPtr)(HDC);
    typedef BOOL(tWGLDeleteContext)(HGLRC);
}