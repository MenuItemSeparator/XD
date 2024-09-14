#pragma once
#include "XD_Graphics_Minimal.h"
#include "XD_Renderer.h"

namespace XD
{
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

        X fCreateVertexArrayObjectX(VertexArrayObjectHandle& _vaoHandle, VertexBufferObjectHandle* _vboHandleArray, u8 _arraySize);
        X fBindVertexArrayObjectX(VertexArrayObjectHandle _vaoHandle);
        X fDestroyVertexArrayObjectX(VertexArrayObjectHandle _vaoHandle);

        X fCreateShaderX(ShaderHandle& _resultHandle, const std::string& _filePath);
        X fDestroyShaderX(ShaderHandle _shaderHandle);

        X fCreateShaderProgramX(ShaderProgramHandle& _resultHandle, ShaderHandle _vsHandle, ShaderHandle _fsHandle);
        X fBindShaderProgramX(ShaderProgramHandle _programHandle);
        X fDestroyShaderProgramX(ShaderProgramHandle _programHandle);

        X fBeginFrameX();
        X fRenderX();
        X fEndFrameX();

    private:
        tUptr<class XD_Renderer> m_renderer;
        tVertexBufferObjectHandleMap m_vertexBufferHandleMap;
        tIndexBufferHandleMap m_indexBufferHandleMap;
        tVertexBufferArrayHandleMap m_vertexBufferArrayHandleMap;
        tVertexBufferLayoutHandleMap m_layoutHandleMap;
        tShaderHandleMap m_shaderHandleMap;
        tShaderProgramHandleMap m_shaderProgramHandleMap;

        bl m_disposed;
    };

}
