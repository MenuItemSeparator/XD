#include "XD_GraphicsSystem.h"
#include "./GraphicsApi/OpenGL/Platform/XD_OpenGL_PlatformSelector.h"

namespace XD
{
    XD_GraphicsSystem::XD_GraphicsSystem() :
        m_renderer(),
        m_vertexBufferHandleMap(),
        m_indexBufferHandleMap(),
        m_layoutHandleMap(),
        m_shaderHandleMap(),
        m_shaderProgramHandleMap(),
        m_disposed(false)
    {

    }

    XD_GraphicsSystem::~XD_GraphicsSystem()
    {
        if(!m_disposed)
        {
            fShutdownX().fCheck();
        }
    }
    

    X XD_GraphicsSystem::fInitializeX(const XD_GraphicsConfig &_config)
    {
        switch(_config.m_rendererType)
        {
        case eRendererType::OpenGL:
            m_renderer = std::make_unique<XD_OpenGLRenderer>();
            break;
        default:
            mXD_ASSERTM(false, "Unknown type of renderer")
            return X_X;
        }

        X_Call(m_renderer->fvInitializeX(_config.m_hwnd), "Can't initialize target renderer");
        return A_A;
    }

    X
    XD_GraphicsSystem::fShutdownX()
    {
        if(!m_renderer) return X_X;
        
        X_Call(m_renderer->fvShutdownX(), "Error while shutdown renderer");

        X_Call(m_vertexBufferHandleMap.fClearX(), "Can't clear vbo handle map");
        X_Call(m_layoutHandleMap.fClearX(), "Can't clear layout handle map");
        X_Call(m_indexBufferHandleMap.fClearX(), "Can't clear ibo handle map");
        X_Call(m_shaderHandleMap.fClearX(), "Can't clear shader handle map");
        X_Call(m_shaderProgramHandleMap.fClearX(), "Can't clear shader program handle map");

        m_disposed = true;
        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateVertexBufferObjectX(VertexBufferObjectHandle& _resultHandle, Memory *_data, VertexBufferLayoutHandle _layout)
    {
        _resultHandle = m_vertexBufferHandleMap.fCreateHandle();
        mXD_ASSERT(m_vertexBufferHandleMap.fIsValid(_resultHandle));

        X_Call(m_renderer->fvCreateVBOX(_resultHandle, _data, _layout), "Can't create vertex buffer");

        mLOG("Created VBO with handle " << _resultHandle);
        return A_A;
    }

    X 
    XD_GraphicsSystem::fBindVertexBufferObjectX(VertexBufferObjectHandle _vbHandle)
    {
        X_Call(m_renderer->fvBindVBOX(_vbHandle), "Can't bind vbo");
        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyVertexBufferObjectX(VertexBufferObjectHandle _vbHandle)
    {
        X_Call(m_renderer->fvDestroyVBOX(_vbHandle), "Can't destroy vertex buffer data");
        X_Call(m_vertexBufferHandleMap.fFreeHandleX(_vbHandle), "Can't free vertex buffer handle");

        mLOG("Destroyed VBO with handle " << _vbHandle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateIndexBufferX(IndexBufferObjectHandle& _handle, Memory* _data)
    {
        _handle = m_indexBufferHandleMap.fCreateHandle();
        mXD_ASSERT(m_indexBufferHandleMap.fIsValid(_handle));

        X_Call(m_renderer->fvCreateIBOX(_handle, _data), "Can't create index buffer");

        mLOG("Created IBO with handle " << _handle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fBindIndexBufferObjectX(IndexBufferObjectHandle _ibHandle)
    {
        X_Call(m_renderer->fvBindIBOX(_ibHandle), "Can't bind ibo");
        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyIndexBufferX(IndexBufferObjectHandle _ibHandle)
    {
        X_Call(m_renderer->fvDestroyIBOX(_ibHandle), "Can't destroy index buffer data");
        X_Call(m_indexBufferHandleMap.fFreeHandleX(_ibHandle), "Can't free index buffer handle");

        mLOG("Destroyed IBO with handle " << _ibHandle);
        return A_A;
    }

    
    X
    XD_GraphicsSystem::fCreateVertexBufferLayoutX(VertexBufferLayoutHandle& _resultHandle, const std::vector<eShaderDataType>& _elements)
    {
        _resultHandle = m_layoutHandleMap.fCreateHandle();
        mXD_ASSERT(m_layoutHandleMap.fIsValid(_resultHandle));

        X_Call(m_renderer->fvCreateVertexBufferLayoutX(_resultHandle, _elements), "Can't create vertex buffer layout");

        mLOG("Created VB layout with handle " << _resultHandle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle)
    {
        X_Call(m_renderer->fvDestroyVertexBufferLayoutX(_layoutHandle), "Can't destroy vertex buffer layout object");
        X_Call(m_layoutHandleMap.fFreeHandleX(_layoutHandle), "Can't free vertex buffer layout handle");

        mLOG("Destroyed VB layout with handle " << _layoutHandle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateShaderX(ShaderHandle& _resultHandle, const std::string &_filePath)
    {
        _resultHandle = m_shaderHandleMap.fCreateHandle();
        mXD_ASSERT(m_shaderHandleMap.fIsValid(_resultHandle));

        X_Call(m_renderer->fvCreateShaderX(_resultHandle, _filePath), "Can't create shader data");
       
        mLOG("Created shader with handle " << _resultHandle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyShaderX(ShaderHandle _shaderHandle)
    {
        X_Call(m_renderer->fvDestroyShaderX(_shaderHandle), "Can't destroy shader");
        X_Call(m_shaderHandleMap.fFreeHandleX(_shaderHandle), "Can't free shader handle");

        mLOG("Destroyed shader with handle " << _shaderHandle);
        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateShaderProgramX(ShaderProgramHandle& _resultHandle, ShaderHandle _vsHandle, ShaderHandle _fsHandle)
    {
        _resultHandle = m_shaderProgramHandleMap.fCreateHandle();
        mXD_ASSERT(m_shaderProgramHandleMap.fIsValid(_resultHandle));

        X_Call(m_renderer->fvCreateShaderProgramX(_resultHandle, _vsHandle, _fsHandle), "Can't create shader program data");

        mLOG("Created shader program with handle " << _resultHandle);
        return A_A;
    }

    X 
    XD_GraphicsSystem::fBindShaderProgramX(ShaderProgramHandle _programHandle)
    {
        X_Call(m_renderer->fvBindShaderProgram(_programHandle), "Can't bind shader program");
        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyShaderProgramX(ShaderProgramHandle _programHandle)
    {
        X_Call(m_renderer->fvDestroyShaderProgramX(_programHandle), "Can't destroy shader program");
        X_Call(m_shaderProgramHandleMap.fFreeHandleX(_programHandle), "Can't free shader program handle");

        mLOG("Destroyed shader program with handle " << _programHandle);
        return A_A;
    }

    X 
    XD_GraphicsSystem::fBeginFrameX()
    {
        X_Call(m_renderer->fvBeginFrameX(), "Error while begin frame in renderer");
        return A_A;
    }

    X
    XD_GraphicsSystem::fRenderX()
    {
        X_Call(m_renderer->fvRenderX(), "Can't render primitive");
        return A_A;
    }

    X 
    XD_GraphicsSystem::fEndFrameX()
    {
        X_Call(m_renderer->fvEndFrameX(), "Error while end frame in renderer");
        return A_A;
    }
}
