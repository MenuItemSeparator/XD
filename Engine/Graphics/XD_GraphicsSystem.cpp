#include "XD_GraphicsSystem.h"
#include "./GraphicsApi/OpenGL/Platform/XD_OpenGL_PlatformSelector.h"

namespace XD
{
    XD_RenderFrame::XD_RenderFrame() :
        m_commandBuffer()
    {
    }

    XD_GraphicsSystem::XD_GraphicsSystem() :
        m_vertexBufferHandleMap(),
        m_indexBufferHandleMap(),
        m_layoutHandleMap(),
        m_shaderHandleMap(),
        m_shaderProgramHandleMap(),
        m_frames(),
        m_constructingFrame(&m_frames[0]),
        m_renderingFrame(&m_frames[1]),
        m_renderer(),
        m_renderThread(),
        m_resourcesMutex(),
        m_readyForSwapFrames(true),
        m_renderThreadIsStopped(false),
        m_graphicsSystemsDisposed(false)
    {

    }

    XD_GraphicsSystem::~XD_GraphicsSystem()
    {
        if(!m_graphicsSystemsDisposed)
        {
            fShutdownX().fCheck();
        }
    }
    

    X XD_GraphicsSystem::fInitializeX(const XD_GraphicsConfig &_config)
    {
        mXD_ASSERT(fIsMainThread());

        m_config = _config;

        switch(m_config.m_rendererType)
        {
        case eRendererType::OpenGL:
            m_renderer = std::make_unique<XD_OpenGLRenderer>();
            break;
        default:
            mXD_ASSERTM(false, "Unknown type of renderer")
            return X_X;
        }

        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        commandBuffer.fStartWrite();
        eRenderCommand initializeCommand = eRenderCommand::RendererCreate;
        X_Call(commandBuffer.fWriteX<eRenderCommand>(initializeCommand), "Can't write renderer initialize command");
        commandBuffer.fFinishWrite();

        //One additional render call to initialize context;
        X_Call(fRenderFrameX(), "Primary render frame error");
        X_Call(m_renderThread.fLaunchX(&XD_GraphicsSystem::fEntryPoint_RenderThread, this, "Render thread"), "Can't launch render thread");
        return A_A;
    }

    X
    XD_GraphicsSystem::fShutdownX()
    {
        mXD_ASSERT(fIsMainThread());

        if(!m_renderer) return X_X;

        m_graphicsSystemsDisposed = true;
        
        while(!m_renderThreadIsStopped) {};

        X_Call(m_vertexBufferHandleMap.fClearX(), "Can't clear vbo handle map");
        X_Call(m_layoutHandleMap.fClearX(), "Can't clear layout handle map");
        X_Call(m_indexBufferHandleMap.fClearX(), "Can't clear ibo handle map");
        X_Call(m_shaderHandleMap.fClearX(), "Can't clear shader handle map");
        X_Call(m_shaderProgramHandleMap.fClearX(), "Can't clear shader program handle map");

        mLOG("Graphics system shut down successfully");

        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateVertexBufferObjectX(VertexBufferObjectHandle& _resultHandle, Memory *_data, VertexBufferLayoutHandle _layout)
    {
        mXD_ASSERT(fIsMainThread());

        _resultHandle = m_vertexBufferHandleMap.fCreateHandle();
        mXD_ASSERT(m_vertexBufferHandleMap.fIsValid(_resultHandle));

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvCreateVBOX(_resultHandle, _data, _layout), "Can't create vertex buffer");
        }

        mLOG("Created VBO with handle " << _resultHandle);
        return A_A;
    }

    X 
    XD_GraphicsSystem::fBindVertexBufferObjectX(VertexBufferObjectHandle _vbHandle)
    {
        mXD_ASSERT(fIsMainThread());

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvBindVBOX(_vbHandle), "Can't bind vbo");
        }

        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyVertexBufferObjectX(VertexBufferObjectHandle _vbHandle)
    {
        mXD_ASSERT(fIsMainThread());

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvDestroyVBOX(_vbHandle), "Can't destroy vertex buffer data");
        }

        X_Call(m_vertexBufferHandleMap.fFreeHandleX(_vbHandle), "Can't free vertex buffer handle");
        mLOG("Destroyed VBO with handle " << _vbHandle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateIndexBufferX(IndexBufferObjectHandle& _handle, Memory* _data)
    {
        mXD_ASSERT(fIsMainThread());

        _handle = m_indexBufferHandleMap.fCreateHandle();
        mXD_ASSERT(m_indexBufferHandleMap.fIsValid(_handle));

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvCreateIBOX(_handle, _data), "Can't create index buffer");
        }

        mLOG("Created IBO with handle " << _handle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fBindIndexBufferObjectX(IndexBufferObjectHandle _ibHandle)
    {
        mXD_ASSERT(fIsMainThread());

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvBindIBOX(_ibHandle), "Can't bind ibo");
        }

        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyIndexBufferX(IndexBufferObjectHandle _ibHandle)
    {
        mXD_ASSERT(fIsMainThread());

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvDestroyIBOX(_ibHandle), "Can't destroy index buffer data");
        }

        X_Call(m_indexBufferHandleMap.fFreeHandleX(_ibHandle), "Can't free index buffer handle");
        mLOG("Destroyed IBO with handle " << _ibHandle);
        return A_A;
    }

    
    X
    XD_GraphicsSystem::fCreateVertexBufferLayoutX(VertexBufferLayoutHandle& _resultHandle, const std::vector<eShaderDataType>& _elements)
    {
        mXD_ASSERT(fIsMainThread());

        _resultHandle = m_layoutHandleMap.fCreateHandle();
        mXD_ASSERT(m_layoutHandleMap.fIsValid(_resultHandle));

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvCreateVertexBufferLayoutX(_resultHandle, _elements), "Can't create vertex buffer layout");
        }

        mLOG("Created VB layout with handle " << _resultHandle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle)
    {
        mXD_ASSERT(fIsMainThread());

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvDestroyVertexBufferLayoutX(_layoutHandle), "Can't destroy vertex buffer layout object");
        }

        X_Call(m_layoutHandleMap.fFreeHandleX(_layoutHandle), "Can't free vertex buffer layout handle");
        mLOG("Destroyed VB layout with handle " << _layoutHandle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateShaderX(ShaderHandle& _resultHandle, const std::string &_filePath)
    {
        mXD_ASSERT(fIsMainThread());

        _resultHandle = m_shaderHandleMap.fCreateHandle();
        mXD_ASSERT(m_shaderHandleMap.fIsValid(_resultHandle));

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvCreateShaderX(_resultHandle, _filePath), "Can't create shader data");
        }
       
        mLOG("Created shader with handle " << _resultHandle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyShaderX(ShaderHandle _shaderHandle)
    {
        mXD_ASSERT(fIsMainThread());

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvDestroyShaderX(_shaderHandle), "Can't destroy shader");
        }

        X_Call(m_shaderHandleMap.fFreeHandleX(_shaderHandle), "Can't free shader handle");
        mLOG("Destroyed shader with handle " << _shaderHandle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateShaderProgramX(ShaderProgramHandle& _resultHandle, ShaderHandle _vsHandle, ShaderHandle _fsHandle)
    {
        mXD_ASSERT(fIsMainThread());

        _resultHandle = m_shaderProgramHandleMap.fCreateHandle();
        mXD_ASSERT(m_shaderProgramHandleMap.fIsValid(_resultHandle));

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvCreateShaderProgramX(_resultHandle, _vsHandle, _fsHandle), "Can't create shader program data");
        }

        mLOG("Created shader program with handle " << _resultHandle);
        return A_A;
    }

    X 
    XD_GraphicsSystem::fBindShaderProgramX(ShaderProgramHandle _programHandle)
    {
        mXD_ASSERT(fIsMainThread());

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvBindShaderProgram(_programHandle), "Can't bind shader program");
        }
        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyShaderProgramX(ShaderProgramHandle _programHandle)
    {
        mXD_ASSERT(fIsMainThread());

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvDestroyShaderProgramX(_programHandle), "Can't destroy shader program");
        }

        X_Call(m_shaderProgramHandleMap.fFreeHandleX(_programHandle), "Can't free shader program handle");
        mLOG("Destroyed shader program with handle " << _programHandle);
        return A_A;
    }

    X 
    XD_GraphicsSystem::fSubmitPrimitiveX()
    {
        mXD_ASSERT(fIsMainThread());

        mXD_NOT_IMPLEMENTED();

        return A_A;
    }

    X 
    XD_GraphicsSystem::fRenderFrameX()
    {
        mXD_ASSERT(fIsMainThread());

        while(!m_readyForSwapFrames) {};

        X_Call(fSwapFramesX(), "Error while swapping constructing and render frames");
        m_readyForSwapFrames = false;

        return A_A;
    }

    X 
    XD_GraphicsSystem::fSwapFramesX()
    {
        mXD_ASSERT(fIsMainThread());
        
        std::swap(m_constructingFrame, m_renderingFrame);

        return A_A;
    }

    X 
    XD_GraphicsSystem::fBeginFrameX_RenderThread()
    {
        mXD_ASSERT(!fIsMainThread());

        X_Call(m_renderer->fvBeginFrameX(), "Error while begin frame in renderer");
        return A_A;
    }

    X
    XD_GraphicsSystem::fRenderX_RenderThread()
    {
        mXD_ASSERT(!fIsMainThread());

        X_Call(m_renderer->fvRenderX(), "Can't render primitive");
        return A_A;
    }

    X 
    XD_GraphicsSystem::fEndFrameX_RenderThread()
    {
        mXD_ASSERT(!fIsMainThread());

        X_Call(m_renderer->fvEndFrameX(), "Error while end frame in renderer");
        return A_A;
    }

    X 
    XD_GraphicsSystem::fExecuteCommandsX_RenderThread()
    {
        mXD_ASSERT(!fIsMainThread());

        eRenderCommand command = eRenderCommand::End;
        XD_CommandBuffer& renderCommands = m_renderingFrame->fGetCommandBuffer();

        if(renderCommands.fGetSize() == 0) return A_A;
        
        do
        {
            X_Call(renderCommands.fReadX<eRenderCommand>(command), "Can't read next render command");

            switch (command)
            {
            case eRenderCommand::RendererCreate:
                X_Call(m_renderer->fvInitializeX(m_config.m_hwnd), "Can't initialize target renderer");
                break;
            default:
                break;
            }


        } while (command != eRenderCommand::End);
        
        renderCommands.fFinishRead();

        return A_A;
    }

    unsigned int XD_GraphicsSystem::fEntryPoint_RenderThread(void *_userData)
    {
        mXD_ASSERT(!fIsMainThread());

        mLOG("Function in render thread");
        XD_GraphicsSystem* graphicsSystem = reinterpret_cast<XD_GraphicsSystem*>(_userData);
        while (eRenderThreadState::Exiting != graphicsSystem->fRenderFrame_RenderThread()) {};
        return 0;
    }

    eRenderThreadState XD_GraphicsSystem::fRenderFrame_RenderThread()
    {
        mXD_ASSERT(!fIsMainThread());

        do
        {
            if(m_graphicsSystemsDisposed)
            {
                m_renderer->fvShutdownX().fCheck();
                m_renderThreadIsStopped = true;

                mLOG("Render thread is exiting. Renderer was terminated.");
                return eRenderThreadState::Exiting;
            }

        } while (m_readyForSwapFrames);
        

        eRenderThreadState result = fRenderFrame_Internal_RenderThread();

        m_readyForSwapFrames = true;
        return result;
    }

    eRenderThreadState XD_GraphicsSystem::fRenderFrame_Internal_RenderThread()
    {
        mXD_ASSERT(!fIsMainThread());

        //ExecuteCommands
        fExecuteCommandsX_RenderThread().fCheck();

        if(!m_renderer->fvIsInitialized())
        {
            return eRenderThreadState::NotInitialized;
        }

        //RenderFrame

        fBeginFrameX_RenderThread().fCheck();
        fEndFrameX_RenderThread().fCheck();

        return m_graphicsSystemsDisposed ? eRenderThreadState::Exiting : eRenderThreadState::Render;
    }
}
