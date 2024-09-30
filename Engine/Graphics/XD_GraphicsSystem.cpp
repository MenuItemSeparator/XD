#include "XD_GraphicsSystem.h"
#include "./GraphicsApi/OpenGL/Platform/XD_OpenGL_PlatformSelector.h"

namespace XD
{
    XD_RenderFrame::XD_RenderFrame() :
        m_commandBuffer()
    {
    }

    XD_GraphicsSystem::XD_GraphicsSystem() :
        m_frames(),
        m_constructingFrame(&m_frames[0]),
        m_renderingFrame(&m_frames[1]),
        m_renderer(),
        m_renderThread(),
        m_resourcesMutex(),
        m_config(),
        m_vertexBufferHandleMap(),
        m_indexBufferHandleMap(),
        m_layoutHandleMap(),
        m_shaderHandleMap(),
        m_shaderProgramHandleMap(),
        m_readyForSwapFrames(true),
        m_renderThreadIsStopped(false),
        m_graphicsSystemIsShutdown(false)
    {

    }

    XD_GraphicsSystem::~XD_GraphicsSystem()
    {
        if(!m_graphicsSystemIsShutdown)
        {
            fShutdownX().fCheck();
        }
    }

    X 
    XD_GraphicsSystem::fInitializeX(const XD_GraphicsConfig &_config)
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

        //One additional render call to initialize context;
        X_Call(fBeginFrameX(), "Primary render frame start error");

        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        eRenderCommand initializeCommand = eRenderCommand::RendererCreate;
        X_Call(commandBuffer.fWriteX<eRenderCommand>(initializeCommand), "Can't write renderer initialize command");

        X_Call(fEndFrameX(), "Primary render frame end error");
        //One additional render call to initialize context END;

        X_Call(m_renderThread.fLaunchX(&XD_GraphicsSystem::fEntryPoint_RenderThread, this, "Render thread"), "Can't launch render thread");
        return A_A;
    }

    X
    XD_GraphicsSystem::fShutdownX()
    {
        mXD_ASSERT(fIsMainThread());

        if(!m_renderer) return X_X;

        mLOG("Graphics system termination started.")

        m_graphicsSystemIsShutdown = true;
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

        {
            XD_LockScope{m_resourcesMutex};

            _resultHandle = m_vertexBufferHandleMap.fCreateHandle();
            mXD_ASSERT(m_vertexBufferHandleMap.fIsValid(_resultHandle));
        }

        eRenderCommand createVBOCommand = eRenderCommand::CreateVBO;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        X_Call(commandBuffer.fWriteX<eRenderCommand>(createVBOCommand), "Can't write down create vbo command to command buffer");
        X_Call(commandBuffer.fWriteX<VertexBufferObjectHandle>(_resultHandle), "Can't write down vbo handle to command buffer");
        X_Call(commandBuffer.fWriteX<Memory>(*_data), "Can't write down vbo data to command buffer");
        X_Call(commandBuffer.fWriteX<VertexBufferLayoutHandle>(_layout), "Can't write down layout to command buffer");

        mLOG("Created VBO with handle " << _resultHandle);
        return A_A;
    }

    X 
    XD_GraphicsSystem::fBindVertexBufferObjectX(VertexBufferObjectHandle _vbHandle)
    {
        mXD_ASSERT(fIsMainThread());

        eRenderCommand bindVBOCommand = eRenderCommand::BindVBO;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        X_Call(commandBuffer.fWriteX<eRenderCommand>(bindVBOCommand), "Can't write down bind vbo command to command buffer");
        X_Call(commandBuffer.fWriteX<VertexBufferObjectHandle>(_vbHandle), "Can't write down vbo handle to command buffer");

        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyVertexBufferObjectX(VertexBufferObjectHandle _vbHandle)
    {
        mXD_ASSERT(fIsMainThread());

        eRenderCommand destroyVBOCommand = eRenderCommand::BindVBO;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        X_Call(commandBuffer.fWriteX<eRenderCommand>(destroyVBOCommand), "Can't write down destroy vbo command to command buffer");
        X_Call(commandBuffer.fWriteX<VertexBufferObjectHandle>(_vbHandle), "Can't write down vbo handle to command buffer");

        //Handle will be deleted in render thread

        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateIndexBufferX(IndexBufferObjectHandle& _handle, Memory* _data)
    {
        mXD_ASSERT(fIsMainThread());
        mXD_NOT_IMPLEMENTED();

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
        mXD_NOT_IMPLEMENTED();

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
        mXD_NOT_IMPLEMENTED();

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
        mXD_NOT_IMPLEMENTED();

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
        mXD_NOT_IMPLEMENTED();

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
        mXD_NOT_IMPLEMENTED();

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
        mXD_NOT_IMPLEMENTED();

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
        mXD_NOT_IMPLEMENTED();

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
        mXD_NOT_IMPLEMENTED();

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
        mXD_NOT_IMPLEMENTED();

        {
            XD_LockScope resScope{ m_resourcesMutex };
            X_Call(m_renderer->fvDestroyShaderProgramX(_programHandle), "Can't destroy shader program");
        }

        X_Call(m_shaderProgramHandleMap.fFreeHandleX(_programHandle), "Can't free shader program handle");
        mLOG("Destroyed shader program with handle " << _programHandle);
        return A_A;
    }

    X 
    XD_GraphicsSystem::fSetClearColorX(const XD_Color& _color)
    {
        mXD_ASSERT(fIsMainThread());

        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        
        XD_Color newColor{ _color };
        eRenderCommand setClearColorCommand = eRenderCommand::SetClearColor;

        X_Call(commandBuffer.fWriteX<eRenderCommand>(setClearColorCommand), "Can't write set clear color command");
        X_Call(commandBuffer.fWriteX<XD_Color>(newColor), "Can't write clear color struct");

        mLOG("Set new clear color. " << _color);
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
    XD_GraphicsSystem::fBeginFrameX()
    {
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        commandBuffer.fStartWrite_Internal();
        return A_A;
    }

    X 
    XD_GraphicsSystem::fEndFrameX()
    {
        mXD_ASSERT(fIsMainThread());

        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        commandBuffer.fFinishWrite_Internal();

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
    XD_GraphicsSystem::fTryExecuteInitializeCommandX_RenderThread()
    {
        mXD_ASSERT(!fIsMainThread());

        eRenderCommand command = eRenderCommand::End;
        XD_CommandBuffer& renderCommands = m_renderingFrame->fGetCommandBuffer();

        if(renderCommands.fGetSize() == 0) return X_X;

        X_Call(renderCommands.fReadX<eRenderCommand>(command), "Can't read next render command");
        if(command == eRenderCommand::RendererCreate)
        {
            XD_LockScope{m_resourcesMutex};
            X_Call(m_renderer->fvInitializeX(m_config.m_hwnd), "Can't initialize target renderer");
        }
        
        return A_A;
    }


    X 
    XD_GraphicsSystem::fExecuteCommonCommandsX_RenderThread()
    {
        mXD_ASSERT(!fIsMainThread());

        eRenderCommand command = eRenderCommand::End;
        XD_CommandBuffer& renderCommands = m_renderingFrame->fGetCommandBuffer();

        if(renderCommands.fGetSize() == 0) return X_X;
        
        do
        {
            X_Call(renderCommands.fReadX<eRenderCommand>(command), "Can't read next render command");

            switch (command)
            {
            case eRenderCommand::SetClearColor:
            {
                XD_Color newClearColor{};
                X_Call(renderCommands.fReadX<XD_Color>(newClearColor), "Can't read new clear color struct");
                X_Call(m_renderer->fvSetClearColorX(newClearColor), "Can't set new clear color to renderer");
            }
                break;
            case eRenderCommand::CreateVBO:
            {
                VertexBufferObjectHandle vboHandle{};
                Memory data{};
                VertexBufferLayoutHandle layoutHandle{};

                X_Call(renderCommands.fReadX<VertexBufferObjectHandle>(vboHandle), "Can't read vbo handle while creating vbo");
                X_Call(renderCommands.fReadX<Memory>(data), "Can't read vbo data while creating vbo");
                X_Call(renderCommands.fReadX<VertexBufferLayoutHandle>(layoutHandle), "Can't read layout handle while creating vbo");
                X_Call(m_renderer->fvCreateVBOX(vboHandle, &data, layoutHandle), "Can't create vertex buffer");
            }
                break;
            case eRenderCommand::BindVBO:
            {
                VertexBufferObjectHandle vboHandle{};

                X_Call(renderCommands.fReadX<VertexBufferObjectHandle>(vboHandle), "Can't read vbo handle while binding vbo");
                X_Call(m_renderer->fvBindVBOX(vboHandle), "Can't bind vbo");
            }
                break;
            case eRenderCommand::DestroyVBO:
            {
                VertexBufferObjectHandle vboHandle{};

                X_Call(renderCommands.fReadX<VertexBufferObjectHandle>(vboHandle), "Can't read vbo handle while destroying vbo");
                X_Call(m_renderer->fvDestroyVBOX(vboHandle), "Can't destroy vertex buffer data");

                {
                    XD_LockScope{m_resourcesMutex};

                    X_Call(m_vertexBufferHandleMap.fFreeHandleX(vboHandle), "Can't free vertex buffer handle");
                    mLOG("Destroyed VBO with handle " << vboHandle);
                }
            }
                break;
            default:
                break;
            }


        } while (command != eRenderCommand::End);
        
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
            if(m_graphicsSystemIsShutdown)
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

        if(!m_renderer->fvIsInitialized())
        {
            fTryExecuteInitializeCommandX_RenderThread().fCheck();
            return eRenderThreadState::NotInitialized;
        }

        //RenderFrame

        fBeginFrameX_RenderThread().fCheck();
        
        //ExecuteCommands
        fExecuteCommonCommandsX_RenderThread().fCheck();

        fEndFrameX_RenderThread().fCheck();

        return eRenderThreadState::Render;
    }
}
