#pragma once
#include "XD_Graphics_Minimal.h"
#include "Application/XD_Window.h"
#include "Common/Platform/XD_Common_PlatformSelector.h"
#include "Application/Platform/XD_Application_PlatformSelector.h"
#include "Graphics/XD_BufferLayout.h"

namespace XD
{
    dXD_MAKE_HANDLE_STRUCT(VertexBufferLayoutHandle);
    dXD_MAKE_HANDLE_STRUCT(VertexBufferObjectHandle);
    dXD_MAKE_HANDLE_STRUCT(IndexBufferObjectHandle);
    dXD_MAKE_HANDLE_STRUCT(ShaderHandle);
    dXD_MAKE_HANDLE_STRUCT(ShaderProgramHandle);


    //Пока виртуальные, потом девиртуализирую самые часто используемые функции
    class XD_ENGINE_API XD_Renderer
    {
    public:
        virtual ~XD_Renderer() = default;
        eRendererType GetRendererType() const { return m_rendererType; }

        virtual X fvInitializeX(void* _hwnd) = 0;
        virtual X fvShutdownX() = 0;

        virtual X fvCreateVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle, const std::vector<eShaderDataType>& _elements) = 0;
        virtual X fvDestroyVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle) = 0;

        virtual X fvCreateIBOX(IndexBufferObjectHandle _iboHandle, void* _data) = 0;
        virtual X fvDestroyIBOX(IndexBufferObjectHandle _iboHandle) = 0;

        virtual X fvCreateVBOX(VertexBufferObjectHandle _vboHandle, void* _data, VertexBufferLayoutHandle _layoutHandle) = 0;
        virtual X fvDestroyVBOX(VertexBufferObjectHandle _vboHandle) = 0;

        virtual X fvCreateShaderX(ShaderHandle _handle, const std::string& _filePath) = 0;
        virtual X fvDestroyShaderX(ShaderHandle _handle) = 0;

        virtual X fvCreateShaderProgramX(ShaderProgramHandle _programHandle, ShaderHandle _vsh, ShaderHandle _fsh) = 0;
        virtual X fvDestroyShaderProgramX(ShaderProgramHandle _programHandle) = 0;

        virtual X fvBeginFrameX() = 0;
        virtual X fvEndFrameX() = 0;

    protected:
        XD_Renderer() = default;

    private:
        eRendererType m_rendererType;
    };
}
