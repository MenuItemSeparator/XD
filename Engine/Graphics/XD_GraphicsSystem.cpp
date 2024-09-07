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
        m_shaderProgramHandleMap()
    {

    }

    XD_GraphicsSystem::~XD_GraphicsSystem()
    {
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
        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateVertexBufferX(VertexBufferHandle& _resultHandle, Memory *_data, VertexBufferLayoutHandle _layout)
    {
        _resultHandle = m_vertexBufferHandleMap.fCreateHandle();
        mXD_ASSERT(m_vertexBufferHandleMap.fIsValid(_resultHandle));

        X_Call(m_renderer->fvCreateVBOX(_resultHandle, _data, _layout), "Can't create vertex buffer");

        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyVertexBufferX(VertexBufferHandle _vbHandle)
    {
        X_Call(m_renderer->fvDestroyVBOX(_vbHandle), "Can't destroy vertex buffer data");
        X_Call(m_vertexBufferHandleMap.fFreeHandleX(_vbHandle), "Can't free vertex buffer handle");
        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateIndexBufferX(IndexBufferHandle& _handle, Memory* _data)
    {
        _handle = m_indexBufferHandleMap.fCreateHandle();
        mXD_ASSERT(m_indexBufferHandleMap.fIsValid(_handle));

        X_Call(m_renderer->fvCreateIBOX(_handle, _data), "Can't create index buffer");

        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyIndexBufferX(IndexBufferHandle _ibHandle)
    {
        X_Call(m_renderer->fvDestroyIBOX(_ibHandle), "Can't destroy index buffer data");
        X_Call(m_indexBufferHandleMap.fFreeHandleX(_ibHandle), "Can't free index buffer handle");
        return A_A;
    }

    
    X
    XD_GraphicsSystem::fCreateVertexBufferLayoutX(VertexBufferLayoutHandle& _resultHandle, const std::vector<eShaderDataType>& _elements)
    {
        _resultHandle = m_layoutHandleMap.fCreateHandle();
        mXD_ASSERT(m_layoutHandleMap.fIsValid(_resultHandle));

        X_Call(m_renderer->fvCreateVertexBufferLayoutX(_resultHandle, _elements), "Can't create vertex buffer layout");

        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle)
    {
        X_Call(m_renderer->fvDestroyVertexBufferLayoutX(_layoutHandle), "Can't destroy vertex buffer layout object");
        X_Call(m_layoutHandleMap.fFreeHandleX(_layoutHandle), "Can't free vertex buffer layout handle");

        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateShaderX(ShaderHandle& _resultHandle, const std::string &_filePath)
    {
        _resultHandle = m_shaderHandleMap.fCreateHandle();
        mXD_ASSERT(m_shaderHandleMap.fIsValid(_resultHandle));

        X_Call(m_renderer->fvCreateShaderX(_resultHandle, _filePath), "Can't create shader data");

        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyShaderX(ShaderHandle _shaderHandle)
    {
        X_Call(m_renderer->fvDestroyShaderX(_shaderHandle), "Can't destroy shader");
        X_Call(m_shaderHandleMap.fFreeHandleX(_shaderHandle), "Can't free shader handle");

        return A_A;
    }

    X
    XD_GraphicsSystem::fCreateShaderProgramX(ShaderProgramHandle& _resultHandle, ShaderHandle _vsHandle, ShaderHandle _fsHandle)
    {
        _resultHandle = m_shaderProgramHandleMap.fCreateHandle();
        mXD_ASSERT(m_shaderProgramHandleMap.fIsValid(_resultHandle));

        X_Call(m_renderer->fvCreateShaderProgramX(_resultHandle, _vsHandle, _fsHandle), "Can't create shader program data");

        return A_A;
    }

    X
    XD_GraphicsSystem::fDestroyShaderProgramX(ShaderProgramHandle _programHandle)
    {
        X_Call(m_renderer->fvDestroyShaderProgramX(_programHandle), "Can't destroy shader program");
        X_Call(m_shaderProgramHandleMap.fFreeHandleX(_programHandle), "Can't free shader program handle");

        return A_A;
    }

    X 
    XD_GraphicsSystem::fBeginFrameX()
    {
        X_Call(m_renderer->fvBeginFrameX(), "Error while begin frame in renderer");
        return A_A;
    }

    X 
    XD_GraphicsSystem::fEndFrameX()
    {
        X_Call(m_renderer->fvEndFrameX(), "Error while end frame in renderer");
        return A_A;
    }
}
