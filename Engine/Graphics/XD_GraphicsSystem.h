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

        X fCreateVertexBufferX(VertexBufferHandle& _resultHandle, Memory* _data, VertexBufferLayoutHandle _layout);
        X fDestroyVertexBufferX(VertexBufferHandle _vbHandle);

        X fCreateIndexBufferX(IndexBufferHandle& _resultHandle, Memory* _data);
        X fDestroyIndexBufferX(IndexBufferHandle _ibHandle);

        X fCreateVertexBufferLayoutX(VertexBufferLayoutHandle& _resultHandle, const std::vector<eShaderDataType>& _elements);
        X fDestroyVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle);

        X fCreateShaderX(ShaderHandle& _resultHandle, const std::string& _filePath);
        X fDestroyShaderX(ShaderHandle _shaderHandle);

        X fCreateShaderProgramX(ShaderProgramHandle& _resultHandle, ShaderHandle _vsHandle, ShaderHandle _fsHandle);
        X fDestroyShaderProgramX(ShaderProgramHandle _programHandle);

        X fBeginFrameX();
        X fEndFrameX();

    private:
        tUptr<class XD_Renderer> m_renderer;
        tVertexBufferHandleMap m_vertexBufferHandleMap;
        tIndexBufferHandleMap m_indexBufferHandleMap;
        tVertexBufferLayoutHandleMap m_layoutHandleMap;
        tShaderHandleMap m_shaderHandleMap;
        tShaderProgramHandleMap m_shaderProgramHandleMap;
    };

}
