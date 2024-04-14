#include "XDEngine_Minimal.h"
#include "XDTest_Minimal.h"
#include "Graphics/XD_BufferLayout.h"

namespace XD
{
    X
    Test_LayoutElementStatics()
    {
        mXD_IS_TRUE(XD_LayoutElement::fGetComponentCount(eShaderDataType::Float) == 1, "Float component count invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetComponentCount(eShaderDataType::Float2) == 2, "Float2 component count invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetComponentCount(eShaderDataType::Float3) == 3, "Float3 component count invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetComponentCount(eShaderDataType::Float4) == 4, "Float4 component count invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetComponentCount(eShaderDataType::Integer) == 1, "Int component count invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetComponentCount(eShaderDataType::Integer2) == 2, "Int2 component count invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetComponentCount(eShaderDataType::Integer3) == 3, "Int3 component count invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetComponentCount(eShaderDataType::Integer4) == 4, "Int4 component count invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetComponentCount(eShaderDataType::Matrix3f) == 3, "Mat3 component count invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetComponentCount(eShaderDataType::Matrix4f) == 4, "Mat4 component count invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetComponentCount(eShaderDataType::Bool) == 1, "Bool component count invalid");

        mXD_IS_TRUE(XD_LayoutElement::fGetShaderDataTypeSize(eShaderDataType::Float) == sizeof(f4), "Float data type size invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetShaderDataTypeSize(eShaderDataType::Float2) == sizeof(f4) * 2, "Float2 data type size invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetShaderDataTypeSize(eShaderDataType::Float3) == sizeof(f4) * 3, "Float3 data type size invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetShaderDataTypeSize(eShaderDataType::Float4) == sizeof(f4) * 4, "Float4 data type size invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetShaderDataTypeSize(eShaderDataType::Integer) == sizeof(i4) * 1, "Int data type size invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetShaderDataTypeSize(eShaderDataType::Integer2) == sizeof(i4) * 2, "Int2 data type size invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetShaderDataTypeSize(eShaderDataType::Integer3) == sizeof(i4) * 3, "Int3 data type size invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetShaderDataTypeSize(eShaderDataType::Integer4) == sizeof(i4) * 4, "Int4 data type sizet invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetShaderDataTypeSize(eShaderDataType::Matrix3f) == sizeof(f4) * 9, "Mat3 data type size invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetShaderDataTypeSize(eShaderDataType::Matrix4f) == sizeof(f4) * 16, "Mat4 data type size invalid");
        mXD_IS_TRUE(XD_LayoutElement::fGetShaderDataTypeSize(eShaderDataType::Bool) == sizeof(bl), "Bool data type size invalid");

        return A_A;
    }

    X
    Test_BufferLayoutConstruction()
    {
        std::vector<eShaderDataType> layout
        {
            eShaderDataType::Float3,
            eShaderDataType::Float2,
            eShaderDataType::Float3,
            eShaderDataType::Matrix4f,
            eShaderDataType::Bool
        };

        XD_BufferLayout layoutBuffer{layout};
        tLayoutIter end = layoutBuffer.fEnd();
        u8 counter = 0;
        u8 offset = 0;

        for(tLayoutIter it = layoutBuffer.fBegin(); it != end; ++it, ++counter)
        {
            mXD_IS_TRUE(it->fGetName() == XD_LayoutElement::fGetNameOfShaderData(layout[counter]), "Invalid name of layout buffer element");
            mXD_IS_TRUE(it->fGetSize() == XD_LayoutElement::fGetShaderDataTypeSize(layout[counter]), "Invalid size of layout buffer element");
            mXD_IS_TRUE(it->fGetOffset() == offset, "Invalid offset of layout buffer element");
            mXD_IS_TRUE(it->fGetType() == layout[counter], "Invalid offset of layout buffer element");

            offset += it->fGetSize();
        }

        mXD_IS_TRUE(layoutBuffer.fGetStride() == offset, "Invalid layout buffer stride calculation");
        return A_A;
    }
}


int
main(int argc, const char** argv)
{
    X_Call(XD::Test_LayoutElementStatics(), "Layout element statics test failed");
    X_Call(XD::Test_BufferLayoutConstruction(), "Buffer layout construction test failed");
    return 0;
}
