#include "XD_BufferLayout.h"

namespace XD
{

    XD_LayoutElement::XD_LayoutElement(eShaderDataType _dataType) :
        m_dataType(_dataType),
        m_size(fGetShaderDataTypeSize(_dataType)),
        m_offset(0)
    {}

    u8
    XD_LayoutElement::fGetShaderDataTypeSize(eShaderDataType _type)
    {
        switch (_type)
        {
            case eShaderDataType::Float:        return sizeof(f4);
            case eShaderDataType::Float2:       return sizeof(f4) * 2;
            case eShaderDataType::Float3:       return sizeof(f4) * 3;
            case eShaderDataType::Float4:       return sizeof(f4) * 4;
            case eShaderDataType::Matrix3f:     return sizeof(f4) * 9;
            case eShaderDataType::Matrix4f:     return sizeof(f4) * 16;
            case eShaderDataType::Integer:      return sizeof(i4);
            case eShaderDataType::Integer2:     return sizeof(i4) * 2;
            case eShaderDataType::Integer3:     return sizeof(i4) * 3;
            case eShaderDataType::Integer4:     return sizeof(i4) * 4;
            case eShaderDataType::Bool:         return sizeof(bl);
            case eShaderDataType::None:         mXD_ASSERTM(false, "Unknown ShaderDataType!"); return 0;
        }
    }

    u8
    XD_LayoutElement::fGetComponentCount(eShaderDataType _type)
    {
        switch (_type)
        {
            case eShaderDataType::Float:       return 1;
            case eShaderDataType::Float2:      return 2;
            case eShaderDataType::Float3:      return 3;
            case eShaderDataType::Float4:      return 4;
            case eShaderDataType::Matrix3f:    return 3;
            case eShaderDataType::Matrix4f:    return 4;
            case eShaderDataType::Integer:     return 1;
            case eShaderDataType::Integer2:    return 2;
            case eShaderDataType::Integer3:    return 3;
            case eShaderDataType::Integer4:    return 4;
            case eShaderDataType::Bool:        return 1;
            case eShaderDataType::None:        mXD_ASSERTM(false, "Unknown ShaderDataType!"); return 0;
        }
    }

    const char*
    XD_LayoutElement::fGetNameOfShaderData(eShaderDataType _type)
    {
        switch (_type)
        {
            case eShaderDataType::Float:        return "Float";
            case eShaderDataType::Float2:       return "Float2";
            case eShaderDataType::Float3:       return "Float3";
            case eShaderDataType::Float4:       return "Float4";
            case eShaderDataType::Matrix3f:     return "Matrix3f";
            case eShaderDataType::Matrix4f:     return "Matrix4f";
            case eShaderDataType::Integer:      return "Integer";
            case eShaderDataType::Integer2:     return "Integer2";
            case eShaderDataType::Integer3:     return "Integer3";
            case eShaderDataType::Integer4:     return "Integer4";
            case eShaderDataType::Bool:         return "Boolean";
            case eShaderDataType::None:         mXD_ASSERTM(false, "Unknown ShaderDataType!"); return "None";
        }
    }

    XD_BufferLayout::XD_BufferLayout(const std::vector<eShaderDataType>& _elements) :
        m_elements(),
        m_stride()
    {
        m_elements.reserve(_elements.size());
        for(u8 i = 0; i < _elements.size(); ++i)
        {
            m_elements.push_back({_elements[i]});
        }
        fCalculateOffsetsAndStride();
    }

    void
    XD_BufferLayout::fCalculateOffsetsAndStride()
    {
        u8 offset = 0;
        m_stride = 0;

        for(u8 i = 0; i < m_elements.size(); ++i)
        {
            m_elements[i].m_offset = offset;
            offset += m_elements[i].m_size;
            m_stride += m_elements[i].m_size;
        }
    }

}
