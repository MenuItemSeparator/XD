#pragma once
#include "XD_WindowsOpenGLFuncPtr.h"
#include "Graphics/XD_Renderer.h"
#include "Common/Platform/XD_Common_PlatformSelector.h"
#include "Graphics/XD_BufferLayout.h"
#include "Graphics/GraphicsApi/OpenGL/XD_GLCheck.h"

namespace XD
{
    class XD_ENGINE_API XD_OpenGLVertexBuffer final
    {
    public:
        X fCreateX(Memory* _data, VertexBufferLayoutHandle _referenceHandle);
        X fUpdateX(u8 _offset, Memory* _data);
        X fDestroy();
    private:
        GLuint m_id;
        VertexBufferLayoutHandle m_layout;
        u8 m_size;
    };

    class XD_ENGINE_API XD_OpenGLContext final
    {
    public:
        XD_OpenGLContext();
        ~XD_OpenGLContext();

        X fCreateX(HWND _hwnd, const int *_attribList);
        X fDestroyX();

        X fBindX();
        X fUnbindX();

        X fSwapBuffersX();

    private:
        HWND m_hwnd;
        HDC m_hdc;
        HGLRC m_context;
    };

    class XD_ENGINE_API XD_OpenGLRenderer : public XD_Renderer
    {
    public:
        XD_OpenGLRenderer();
        
        virtual X fvInitializeX(void* _hwnd) override;
        virtual X fvShutdownX() override;

        virtual X fvBeginFrameX() override;
        virtual X fvEndFrameX() override;

        virtual X fvCreateVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle, const std::vector<eShaderDataType>& _elements) override;
        virtual X fvDestroyVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle) override;

        virtual X fvCreateIBOX(IndexBufferHandle _iboHandle, Memory* _data) override;
        virtual X fvDestroyIBOX(IndexBufferHandle _iboHandle) override;

        virtual X fvCreateVBOX(VertexBufferHandle _vboHandle, Memory* _data, VertexBufferLayoutHandle _layoutHandle) override;
        virtual X fvDestroyVBOX(VertexBufferHandle _vboHandle) override;
        
        virtual X fvCreateShaderX(ShaderHandle _handle, const std::string& _filePath) override;
        virtual X fvDestroyShaderX(ShaderHandle _handle) override;

        virtual X fvCreateShaderProgramX(ShaderProgramHandle _programHandle, ShaderHandle _vsh, ShaderHandle _fsh) override;
        virtual X fvDestroyShaderProgramX(ShaderProgramHandle _programHandle) override;

    private:
        tSptr<XD_OpenGLContext> m_context;
        XD_Library m_openGLDll;
        PIXELFORMATDESCRIPTOR m_pfd;

        X fExtractInitialProcsFromDummyContextX();
        X fCreateValidPixelFormatX(HWND _hwnd);
    };
}