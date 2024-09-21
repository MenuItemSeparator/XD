#pragma once
#include "XD_Engine_Minimal.h"

namespace XD
{
    enum class eShaderDataType
    {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Integer,
        Integer2,
        Integer3,
        Integer4,
        Matrix3f,
        Matrix4f,
        Bool
    };

    class XD_ENGINE_API XD_LayoutElement final
    {
        friend class XD_BufferLayout;
    public:
        XD_LayoutElement() = delete;
        XD_LayoutElement(eShaderDataType _dataType);
        eShaderDataType fGetType() const { return m_dataType; }
        u8 fGetSize() const { return m_size; }
        u8 fGetOffset() const { return m_offset; }
        const char* fGetName() const { return fGetNameOfShaderData(m_dataType); }

        static u8 fGetShaderDataTypeSize(eShaderDataType _type);
        static u8 fGetComponentCount(eShaderDataType _type);
        static const char* fGetNameOfShaderData(eShaderDataType _type);
    private:
        eShaderDataType m_dataType;
        u8 m_size;
        u8 m_offset;
    };

    using tLayoutIter = std::vector<XD_LayoutElement>::const_iterator;

    class XD_ENGINE_API XD_BufferLayout final
    {
    public:
        XD_BufferLayout() = default;
        X fCreateX(const std::vector<eShaderDataType>& _elements);
        X fDestroyX();

        tLayoutIter fBegin() const { return m_elements.cbegin(); }
        tLayoutIter fEnd() const { return m_elements.cend(); }
        u8 fGetStride() const { return m_stride; }
    private:
        std::vector<XD_LayoutElement> m_elements;
        u8 m_stride;

        void fCalculateOffsetsAndStride();
    };

}
