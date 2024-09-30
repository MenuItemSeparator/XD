#pragma once
#include "XD_Engine_Minimal.h"

namespace XD
{
    enum class eRenderCommand : ubyte
    {
        RendererCreate = 0,
        RendererDestroy,

        CreateVBO,
        BindVBO,
        DestroyVBO,

        CreateIBO,
        BindIBO,
        DestroyIBO,

        CreateLayout,
        DestroyLayout,

        CreateShader,
        DestroyShader,

        CreateShaderProgram,
        BindShaderProgram,
        DestroyShaderProgram,

        SetClearColor,

        End,

        COUNT
    };

    class XD_ENGINE_API XD_CommandBuffer final
    {
    public:
        XD_CommandBuffer();
        ~XD_CommandBuffer();

        XD_CommandBuffer(const XD_CommandBuffer&) = delete;
        XD_CommandBuffer& operator=(const XD_CommandBuffer&) = delete;

		void fStartWrite_Internal();
		void fFinishWrite_Internal();

        X fReadX(ubyte* _data, u8 _size);

        u8 fGetSize() const { return m_size; }

        template<typename T>
		X fReadX(T& _in)
		{
			X_Call(fReadX(reinterpret_cast<ubyte*>(&_in), sizeof(T)), "Unknown error while raw reading command buffer");
            return A_A;
		}

        X fWriteX(ubyte* _data, uint32_t _size);

		template<typename T>
		X fWriteX(T& _in)
		{
			X_Call(fWriteX(reinterpret_cast<ubyte*>(&_in), sizeof(T)), "Unknown error while raw writing in command buffer");
            return A_A;
		}

    private:
        ubyte* m_buffer;
        u8 m_pos;
        u8 m_size;
        u8 m_capacity;
    };
}