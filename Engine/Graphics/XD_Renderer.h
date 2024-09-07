#pragma once
#include "XD_Graphics_Minimal.h"
#include "Application/XD_Window.h"
#include "Common/Platform/XD_Common_PlatformSelector.h"
#include "Application/Platform/XD_Application_PlatformSelector.h"
#include "Graphics/XD_BufferLayout.h"
#include "XD_HandleMap.h"

namespace XD
{
    const u8 VBO_MAX_COUNT = 1024;
    dXD_MAKE_HANDLE_STRUCT(VertexBufferHandle);
    using tVertexBufferHandleMap = XD_HandleMap<VertexBufferHandle, VBO_MAX_COUNT>;

    const u8 VBLAYOUT_MAX_COUNT = 32;
    dXD_MAKE_HANDLE_STRUCT(VertexBufferLayoutHandle);
    using tVertexBufferLayoutHandleMap = XD_HandleMap<VertexBufferLayoutHandle, VBLAYOUT_MAX_COUNT>;

    const u8 IBO_MAX_COUNT = 1024;
    dXD_MAKE_HANDLE_STRUCT(IndexBufferHandle);
    using tIndexBufferHandleMap = XD_HandleMap<IndexBufferHandle, IBO_MAX_COUNT>;

    const u8 SHADER_MAX_COUNT = 1024;
    dXD_MAKE_HANDLE_STRUCT(ShaderHandle);
    using tShaderHandleMap = XD_HandleMap<ShaderHandle, SHADER_MAX_COUNT>;

    const u8 SHADERPROG_MAX_COUNT = SHADER_MAX_COUNT / 512;
    dXD_MAKE_HANDLE_STRUCT(ShaderProgramHandle);
    using tShaderProgramHandleMap = XD_HandleMap<ShaderProgramHandle, SHADERPROG_MAX_COUNT>;

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

        virtual X fvCreateIBOX(IndexBufferHandle _iboHandle, Memory* _data) = 0;
        virtual X fvDestroyIBOX(IndexBufferHandle _iboHandle) = 0;

        virtual X fvCreateVBOX(VertexBufferHandle _vboHandle, Memory* _data, VertexBufferLayoutHandle _layoutHandle) = 0;
        virtual X fvDestroyVBOX(VertexBufferHandle _vboHandle) = 0;

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
