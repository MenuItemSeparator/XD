#include "XD_CommandBuffer.h"

namespace XD
{
    static u8 COMMAND_BUFFER_STATIC_SIZE = 1024;

    XD_CommandBuffer::XD_CommandBuffer() :
        m_buffer(nullptr),
        m_pos(0),
        m_size(0),
        m_capacity(COMMAND_BUFFER_STATIC_SIZE)
    {
        m_buffer = reinterpret_cast<ubyte*>(malloc(COMMAND_BUFFER_STATIC_SIZE));
        fFinishWrite_Internal();
    }

    XD_CommandBuffer::~XD_CommandBuffer()
    {
    }

    void
    XD_CommandBuffer::fReset()
    {
        m_pos = 0;
        m_size = 0;
    }

    void
    XD_CommandBuffer::fFinishWrite_Internal()
    {
        ubyte cmd = static_cast<ubyte>(eRenderCommand::End);
        fWriteX<ubyte>(cmd).fCheck();
        m_size = m_pos;
        m_pos = 0;

        mXD_ASSERT(m_size < m_capacity);
    }

    X 
    XD_CommandBuffer::fReadX(ubyte* _data, u8 _size)
    {
        memcpy(_data, &m_buffer[m_pos], _size);
        m_pos += _size;
        return A_A;
    }

    X 
    XD_CommandBuffer::fWriteX(ubyte* _data, uint32_t _size)
    {
        //mXD_ASSERTM(m_size == 0, "Called without fStart/fEnd calls. Size: " << m_size);

        if (m_pos + _size > m_capacity)
        {
            mXD_ASSERTM(false, "Command buffer overflow.")
            return X_X;
            //Resize?
        }

        memcpy(&m_buffer[m_pos], _data, _size);
        m_pos += _size;
        return A_A;
    }
}