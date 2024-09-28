#pragma once
#include "XD_Graphics_Minimal.h"
#include "XD_Renderer.h"
#include "XD_CommandBuffer.h"

namespace XD
{
    enum class eRenderThreadState
    {
        NoContext = 0,
        Render,
        Exiting,

        COUNT
    };

    class XD_ENGINE_API XD_RenderFrame final
    {
    public:
        XD_RenderFrame() = default;
    private:

    };

    class XD_ENGINE_API XD_GraphicsSystem final
    {
    public:
        XD_GraphicsSystem();
        XD_GraphicsSystem(const XD_GraphicsSystem&) = delete;
        XD_GraphicsSystem& operator=(const XD_GraphicsSystem&) = delete;
        ~XD_GraphicsSystem();

        X fInitializeX(const XD_GraphicsConfig& _config);
        X fShutdownX();

        X fCreateVertexBufferObjectX(VertexBufferObjectHandle& _resultHandle, Memory* _data, VertexBufferLayoutHandle _layout);
        X fBindVertexBufferObjectX(VertexBufferObjectHandle _vbHandle);
        X fDestroyVertexBufferObjectX(VertexBufferObjectHandle _vbHandle);

        X fCreateIndexBufferX(IndexBufferObjectHandle& _resultHandle, Memory* _data);
        X fBindIndexBufferObjectX(IndexBufferObjectHandle _ibHandle);
        X fDestroyIndexBufferX(IndexBufferObjectHandle _ibHandle);

        X fCreateVertexBufferLayoutX(VertexBufferLayoutHandle& _resultHandle, const std::vector<eShaderDataType>& _elements);
        X fDestroyVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle);

        X fCreateShaderX(ShaderHandle& _resultHandle, const std::string& _filePath);
        X fDestroyShaderX(ShaderHandle _shaderHandle);

        X fCreateShaderProgramX(ShaderProgramHandle& _resultHandle, ShaderHandle _vsHandle, ShaderHandle _fsHandle);
        X fBindShaderProgramX(ShaderProgramHandle _programHandle);
        X fDestroyShaderProgramX(ShaderProgramHandle _programHandle);

        X fSubmitPrimitiveX();
        X fRenderFrameX();
        X fSwapFramesX();

    private:
        // Game thread
        tVertexBufferObjectHandleMap m_vertexBufferHandleMap;
        tIndexBufferHandleMap m_indexBufferHandleMap;
        tVertexBufferLayoutHandleMap m_layoutHandleMap;
        tShaderHandleMap m_shaderHandleMap;
        tShaderProgramHandleMap m_shaderProgramHandleMap;

        // Shared data

        XD_RenderFrame m_frames[2];
        XD_RenderFrame* m_constructingFrame;
        XD_RenderFrame* m_renderingFrame;

        // Render thread

        tUptr<class XD_Renderer> m_renderer;
        XD_Thread m_renderThread;
        XD_Mutex m_resourcesMutex;
        std::atomic_bool m_disposed;

        static unsigned int fEntryPoint_RenderThread(void* _userData);
        eRenderThreadState fRenderFrame_RenderThread();
        eRenderThreadState fRenderFrame_Internal_RenderThread();

        X fBeginFrameX_RenderThread();
        X fRenderX_RenderThread();
        X fEndFrameX_RenderThread();
    };

}
