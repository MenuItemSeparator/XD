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
        //X_Call(fBeginFrameX(), "Primary render frame start error");

        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        eRenderCommand initializeCommand = eRenderCommand::RendererCreate;
        X_Call(commandBuffer.fWriteX<eRenderCommand>(initializeCommand), "Can't write renderer initialize command");

        //X_Call(fEndFrameX(), "Primary render frame end error");
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

        eRenderCommand destroyVBOCommand = eRenderCommand::DestroyVBO;
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

        {
            XD_LockScope{m_resourcesMutex};

            _handle = m_indexBufferHandleMap.fCreateHandle();
            mXD_ASSERT(m_indexBufferHandleMap.fIsValid(_handle));
        }

        eRenderCommand createIBOCommand = eRenderCommand::CreateIBO;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        X_Call(commandBuffer.fWriteX<eRenderCommand>(createIBOCommand), "Can't write down create ibo command to command buffer");
        X_Call(commandBuffer.fWriteX<IndexBufferObjectHandle>(_handle), "Can't write down ibo handle to command buffer");
        X_Call(commandBuffer.fWriteX<Memory>(*_data), "Can't write down ibo data to command buffer");

        mLOG("Created IBO with handle " << _handle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fBindIndexBufferObjectX(IndexBufferObjectHandle _ibHandle)
    {
        mXD_ASSERT(fIsMainThread());

        eRenderCommand bindIBOCommand = eRenderCommand::BindIBO;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        X_Call(commandBuffer.fWriteX<eRenderCommand>(bindIBOCommand), "Can't write down bind ibo command to command buffer");
        X_Call(commandBuffer.fWriteX<IndexBufferObjectHandle>(_ibHandle), "Can't write down ibo handle to command buffer");

        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyIndexBufferX(IndexBufferObjectHandle _ibHandle)
    {
        mXD_ASSERT(fIsMainThread());
        
        eRenderCommand destroyIBOCommand = eRenderCommand::DestroyIBO;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        X_Call(commandBuffer.fWriteX<eRenderCommand>(destroyIBOCommand), "Can't write down destroy ibo command to command buffer");
        X_Call(commandBuffer.fWriteX<IndexBufferObjectHandle>(_ibHandle), "Can't write down ibo handle to command buffer");

        //Handle will be deleted in render thread

        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateVertexBufferLayoutX(VertexBufferLayoutHandle& _resultHandle, std::vector<eShaderDataType>& _elements)
    {
        mXD_ASSERT(fIsMainThread());

        {
            XD_LockScope{m_resourcesMutex};

            _resultHandle = m_layoutHandleMap.fCreateHandle();
            mXD_ASSERT(m_layoutHandleMap.fIsValid(_resultHandle));
        }

        eRenderCommand createLayoutCommand = eRenderCommand::CreateLayout;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        Memory elementsData{};
        elementsData.m_byteSize = _elements.size() * sizeof(eShaderDataType);
        elementsData.m_data = _elements.data();

        X_Call(commandBuffer.fWriteX<eRenderCommand>(createLayoutCommand), "Can't write down create layout command to command buffer");
        X_Call(commandBuffer.fWriteX<VertexBufferLayoutHandle>(_resultHandle), "Can't write down layout handle to command buffer");
        X_Call(commandBuffer.fWriteX<Memory>(elementsData), "Can't write down layout data to command buffer");

        mLOG("Created VB layout with handle " << _resultHandle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle)
    {
        mXD_ASSERT(fIsMainThread());
    
        eRenderCommand destroyLayoutCommand = eRenderCommand::DestroyLayout;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        X_Call(commandBuffer.fWriteX<eRenderCommand>(destroyLayoutCommand), "Can't write down destroy layout command to command buffer");
        X_Call(commandBuffer.fWriteX<VertexBufferLayoutHandle>(_layoutHandle), "Can't write down  layout handle to command buffer");

        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateShaderX(ShaderHandle& _resultHandle, const std::string &_filePath)
    {
        mXD_ASSERT(fIsMainThread());

        {
            XD_LockScope resScope{ m_resourcesMutex };
            _resultHandle = m_shaderHandleMap.fCreateHandle();
            mXD_ASSERT(m_shaderHandleMap.fIsValid(_resultHandle));
        }

        eRenderCommand createShaderCommand = eRenderCommand::CreateShader;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        X_Call(commandBuffer.fWriteX<eRenderCommand>(createShaderCommand), "Can't write down create shader command to command buffer");
        X_Call(commandBuffer.fWriteX<ShaderHandle>(_resultHandle), "Can't write down shader handle to command buffer");
        X_Call(commandBuffer.fWriteX<std::string>(const_cast<std::string&>(_filePath)), "Can't write down shader file path to command buffer");
       
        mLOG("Created shader with handle " << _resultHandle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyShaderX(ShaderHandle _shaderHandle)
    {
        mXD_ASSERT(fIsMainThread());

        eRenderCommand destroyShaderCommand = eRenderCommand::DestroyShader;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        X_Call(commandBuffer.fWriteX<eRenderCommand>(destroyShaderCommand), "Can't write down destroy Shader command to command buffer");
        X_Call(commandBuffer.fWriteX<ShaderHandle>(_shaderHandle), "Can't write down Shader handle to command buffer");

        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateShaderProgramX(ShaderProgramHandle& _resultHandle, ShaderHandle _vsHandle, ShaderHandle _fsHandle)
    {
        mXD_ASSERT(fIsMainThread());

        {
            XD_LockScope resScope{ m_resourcesMutex };

            _resultHandle = m_shaderProgramHandleMap.fCreateHandle();
            mXD_ASSERT(m_shaderProgramHandleMap.fIsValid(_resultHandle));
        }

        eRenderCommand createShaderProgramCommand = eRenderCommand::CreateShaderProgram;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        X_Call(commandBuffer.fWriteX<eRenderCommand>(createShaderProgramCommand), "Can't write down create shader program command to command buffer");
        X_Call(commandBuffer.fWriteX<ShaderProgramHandle>(_resultHandle), "Can't write down shader program handle to command buffer");
        X_Call(commandBuffer.fWriteX<ShaderHandle>(_vsHandle), "Can't write down vs shader handle to command buffer");
        X_Call(commandBuffer.fWriteX<ShaderHandle>(_fsHandle), "Can't write down fs shader handle to command buffer");

        mLOG("Created shader program with handle " << _resultHandle);
        return A_A;
    }

    X 
    XD_GraphicsSystem::fBindShaderProgramX(ShaderProgramHandle _programHandle)
    {
        mXD_ASSERT(fIsMainThread());

        eRenderCommand bindProgramCommand = eRenderCommand::BindShaderProgram;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        X_Call(commandBuffer.fWriteX<eRenderCommand>(bindProgramCommand), "Can't write down bind shader program command to command buffer");
        X_Call(commandBuffer.fWriteX<ShaderProgramHandle>(_programHandle), "Can't write down shader program handle to command buffer");

        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyShaderProgramX(ShaderProgramHandle _programHandle)
    {
        mXD_ASSERT(fIsMainThread());

        eRenderCommand destroyShaderProgramCommand = eRenderCommand::DestroyShaderProgram;
        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        X_Call(commandBuffer.fWriteX<eRenderCommand>(destroyShaderProgramCommand), "Can't write down destroy shader program command to command buffer");
        X_Call(commandBuffer.fWriteX<ShaderProgramHandle>(_programHandle), "Can't write down shader program handle to command buffer");

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

        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();

        eRenderCommand renderPrimitiveCommand = eRenderCommand::RenderPrimitive;
        X_Call(commandBuffer.fWriteX<eRenderCommand>(renderPrimitiveCommand), "Can't write render primitive command");

        return A_A;
    }

    X 
    XD_GraphicsSystem::fStageFrameX()
    {
        mXD_ASSERT(fIsMainThread());

        XD_CommandBuffer& commandBuffer = m_constructingFrame->fGetCommandBuffer();
        commandBuffer.fFinishWrite_Internal();

        while(!m_readyForSwapFrames) {};
        X_Call(fSwapFramesX(), "Error while swapping constructing and render frames");
        m_readyForSwapFrames = false;

        XD_CommandBuffer& newCommandBuffer = m_constructingFrame->fGetCommandBuffer();
        newCommandBuffer.fReset();
        
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
                }

                mLOG("Destroyed VBO with handle " << vboHandle);
            }
                break;
            case eRenderCommand::CreateIBO:
            {
                IndexBufferObjectHandle iboHandle{};
                Memory data{};

                X_Call(renderCommands.fReadX<IndexBufferObjectHandle>(iboHandle), "Can't read ibo handle while creating ibo");
                X_Call(renderCommands.fReadX<Memory>(data), "Can't read ibo data while creating ibo");
                X_Call(m_renderer->fvCreateIBOX(iboHandle, &data), "Can't create index buffer");

            }
                break;
            case eRenderCommand::BindIBO:
            {
                IndexBufferObjectHandle iboHandle{};

                X_Call(renderCommands.fReadX<IndexBufferObjectHandle>(iboHandle), "Can't read ibo handle while binding ibo");
                X_Call(m_renderer->fvBindIBOX(iboHandle), "Can't bind ibo");
            }
                break;
            case eRenderCommand::DestroyIBO:
            {
                IndexBufferObjectHandle iboHandle{};

                X_Call(renderCommands.fReadX<IndexBufferObjectHandle>(iboHandle), "Can't read ibo handle while destroying ibo");
                X_Call(m_renderer->fvDestroyIBOX(iboHandle), "Can't destroy index buffer data");

                {
                    XD_LockScope resScope{ m_resourcesMutex };
                    X_Call(m_indexBufferHandleMap.fFreeHandleX(iboHandle), "Can't free index buffer handle");
                }

                mLOG("Destroyed IBO with handle " << iboHandle);
            }
                break;
            case eRenderCommand::CreateLayout:
            {
                VertexBufferLayoutHandle layoutHandle{};
                Memory data{};

                X_Call(renderCommands.fReadX<VertexBufferLayoutHandle>(layoutHandle), "Can't read layout handle while creating layout");
                X_Call(renderCommands.fReadX<Memory>(data), "Can't read layout data while creating layout");
                X_Call(m_renderer->fvCreateVertexBufferLayoutX(layoutHandle, &data), "Can't create vertex buffer layout");
            }
                break;
            case eRenderCommand::DestroyLayout:
            {
                VertexBufferLayoutHandle layoutHandle{};

                X_Call(renderCommands.fReadX<VertexBufferLayoutHandle>(layoutHandle), "Can't read layout handle while destroying layout");
                X_Call(m_renderer->fvDestroyVertexBufferLayoutX(layoutHandle), "Can't destroy vertex buffer layout object");

                {
                    XD_LockScope resScope{ m_resourcesMutex };
                    X_Call(m_layoutHandleMap.fFreeHandleX(layoutHandle), "Can't free vertex buffer layout handle");
                }

                mLOG("Destroyed VB layout with handle " << layoutHandle);
            }
                break;
            case eRenderCommand::CreateShader:
            {
                ShaderHandle shaderHandle{};
                std::string filePath{};

                X_Call(renderCommands.fReadX<ShaderHandle>(shaderHandle), "Can't read shader handle while creating shader");
                X_Call(renderCommands.fReadX<std::string>(filePath), "Can't read shader file path while creating shader");
                X_Call(m_renderer->fvCreateShaderX(shaderHandle, filePath), "Can't create shader data");
            }
                break;
            case eRenderCommand::DestroyShader:
            {
                ShaderHandle shaderHandle{};

                X_Call(renderCommands.fReadX<ShaderHandle>(shaderHandle), "Can't read shader handle while destroying shader");
                X_Call(m_renderer->fvDestroyShaderX(shaderHandle), "Can't destroy shader");

                {
                    XD_LockScope resScope{ m_resourcesMutex };
                    X_Call(m_shaderHandleMap.fFreeHandleX(shaderHandle), "Can't free shader handle");
                }

                mLOG("Destroyed shader with handle " << shaderHandle);
            }
                break;
            case eRenderCommand::CreateShaderProgram:
            {
                ShaderProgramHandle programHandle{};
                ShaderHandle vsShaderHandle{};
                ShaderHandle fsShaderHandle{};

                X_Call(renderCommands.fReadX<ShaderProgramHandle>(programHandle), "Can't read shader program handle while creating shader program");
                X_Call(renderCommands.fReadX<ShaderHandle>(vsShaderHandle), "Can't read vs shader handle while creating shader program");
                X_Call(renderCommands.fReadX<ShaderHandle>(fsShaderHandle), "Can't read fs shader handle while creating shader program");
                X_Call(m_renderer->fvCreateShaderProgramX(programHandle, vsShaderHandle, fsShaderHandle), "Can't create shader program data");
            }
                break;
            case eRenderCommand::BindShaderProgram:
            {
                ShaderProgramHandle programHandle{};

                X_Call(renderCommands.fReadX<ShaderProgramHandle>(programHandle), "Can't read shader program handle while binding shader program");
                X_Call(m_renderer->fvBindShaderProgram(programHandle), "Can't bind shader program");
            }
                break;
            case eRenderCommand::DestroyShaderProgram:
            {
                ShaderProgramHandle programHandle{};
                X_Call(renderCommands.fReadX<ShaderProgramHandle>(programHandle), "Can't read shader program handle while destroying shader program");
                X_Call(m_renderer->fvDestroyShaderProgramX(programHandle), "Can't destroy shader program");

                {
                    XD_LockScope resScope{ m_resourcesMutex };
                    X_Call(m_shaderProgramHandleMap.fFreeHandleX(programHandle), "Can't free shader program handle");
                }       

                mLOG("Destroyed shader program with handle " << programHandle);
            }
                break;
            case eRenderCommand::RenderPrimitive:
            {
                X_Call(m_renderer->fvRenderX(), "Error while rendering primitive");
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
        }

        //RenderFrame

        fBeginFrameX_RenderThread().fCheck();
        
        //ExecuteCommands
        fExecuteCommonCommandsX_RenderThread().fCheck();

        fEndFrameX_RenderThread().fCheck();

        return eRenderThreadState::Render;
    }
}
