#include "XD_Test_Minimal.h"
#include "XD_Engine_Minimal.h"
#include "Common/XD_Utility.h"

namespace XD
{
    X
    Test_Abs()
    {
        i4 iv1 = 3;
        i4 iv2 = -3;

        mXD_IS_FALSE(iv1 == iv2, "Two different int are equal");
        mXD_IS_TRUE(iv1 == fAbs(iv2), "Two equal float are not equal");

        return A_A;
    }

    X
    Test_IsNearlyEqual()
    {
        f4 fv1 = 4.0f;
        f4 fv2 = 12.0f;
        mXD_IS_FALSE(fIsNearlyEqual(fv1, fv2), "Two different float are equal");
        mXD_IS_TRUE(fIsNearlyEqual(fv1, fv1), "Two equal float are not equal");
        mXD_IS_TRUE(fIsNearlyEqual(fv2, fv2), "Two equal float are not equal");

        f8 dv1 = 2.0;
        f8 dv2 = -3.0;
        mXD_IS_FALSE(fIsNearlyEqual(dv1, dv2), "Two different double are equal");
        mXD_IS_TRUE(fIsNearlyEqual(dv1, dv1), "Two equal double are not equal");
        mXD_IS_TRUE(fIsNearlyEqual(dv2, dv2), "Two equal double are not equal");

        return A_A;
    }

    //vec2

    X
    Test_CreateDefaultVector2()
    {
        Vector2f vec{};
        mXD_IS_TRUE(fIsNearlyZero(vec.m_x), "X value of vector2 is not zero by default");
        mXD_IS_TRUE(fIsNearlyZero(vec.m_y), "Y value of vector2 is not zero by default");
        return A_A;
    }

    X
    Test_EqualityVector2()
    {
        Vector2f vec1{1.567f, 12750.87f};
        Vector2f vec2{123.5211f, 1720.3f};
        mXD_IS_FALSE(vec1 == vec2, "Different vectors is equal");
        mXD_IS_TRUE(vec1 != vec2, "Different vectors is equal");
        return A_A;
    }

    X
    Test_ArithmeticVector2()
    {
        Vector2f vec1{12.0f, -10.0f};
        Vector2f vec2{2.0f, 2.0f};

        mXD_IS_TRUE((vec1 + vec2 == Vector2f{14.0f, -8.0f}), "Summarize of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 - vec2 == Vector2f{10.0f, -12.0f}), "Subtract of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 * 2.0f == Vector2f{24.0f, -20.0f}), "Multiply of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 / 2.0f == Vector2f{6.0f, -5.0f}), "Division of two vectors returned not expected values");
        return A_A;
    }

    X
    Test_NormalizeVector2()
    {
        Vector2f vec1{123.0f, 63.0f};
        mXD_IS_FALSE(fIsNearlyEqual(vec1.fMagnitude(), 1.0f), "Non 1-length vector has 1 length magnitude");
        mXD_IS_TRUE(fIsNearlyEqual(vec1.fGetNormalized().fMagnitude(), 1.0f), "1-length vector has not 1 length magnitude when normalized")
        return A_A;
    }

    X
    Test_DotVector2()
    {
        Vector2f vec1{1.2f, 3.6f};
        Vector2f vec2{12.1f, 0.6f};
        mXD_IS_TRUE(fIsNearlyEqual(vec1.fDot(vec2), 16.68f), "Dot product of vector 2 is not valid")
        return A_A;
    }

    //vec3

    X
    Test_CreateDefaultVector3()
    {
        Vector3f vec{};
        mXD_IS_TRUE(fIsNearlyZero(vec.m_x), "X value of vector3 is not zero by default");
        mXD_IS_TRUE(fIsNearlyZero(vec.m_y), "Y value of vector3 is not zero by default");
        return A_A;
    }

    X
    Test_EqualityVector3()
    {
        Vector3f vec1{1.567f, 12750.87f, 124.0f};
        Vector3f vec2{123.5211f, 1720.3f, 86547.2f};
        mXD_IS_FALSE(vec1 == vec2, "Different vectors is equal");
        mXD_IS_TRUE(vec1 != vec2, "Different vectors is equal");
        return A_A;
    }

    X
    Test_ArithmeticVector3()
    {
        Vector3f vec1{12.0f, -10.0f, 5.0f};
        Vector3f vec2{2.0f, 2.0f, 2.0f};

        mXD_IS_TRUE((vec1 + vec2 == Vector3f{14.0f, -8.0f, 7.0f}), "Summarize of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 - vec2 == Vector3f{10.0f, -12.0f, 3.0f}), "Subtract of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 * 2.0f == Vector3f{24.0f, -20.0f, 10.0f}), "Multiply of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 / 2.0f == Vector3f{6.0f, -5.0f, 2.5f}), "Division of two vectors returned not expected values");
        return A_A;
    }

    X
    Test_NormalizeVector3()
    {
        Vector3f vec1{123.0f, 63.0f, -12.0f};
        mXD_IS_FALSE(fIsNearlyEqual(vec1.fMagnitude(), 1.0f), "Non 1-length vector has 1 length magnitude");
        mXD_IS_TRUE(fIsNearlyEqual(vec1.fGetNormalized().fMagnitude(), 1.0f), "1-length vector has not 1 length magnitude when normalized")
        return A_A;
    }

    X
    Test_DotVector3()
    {
        Vector3f vec1{1.2f, 3.6f, 12.3f};
        Vector3f vec2{12.1f, 0.6f, 9.1f};
        mXD_IS_TRUE(fIsNearlyEqual(vec1.fDot(vec2), 128.61f), "Dot product of vector 3 is not valid")
        return A_A;
    }

    //vec4

    X
    Test_CreateDefaultVector4()
    {
        Vector4f vec{};
        mXD_IS_TRUE(fIsNearlyZero(vec.m_x), "X value of vector3 is not zero by default");
        mXD_IS_TRUE(fIsNearlyZero(vec.m_y), "Y value of vector3 is not zero by default");
        return A_A;
    }

    X
    Test_EqualityVector4()
    {
        Vector4f vec1{1.567f, 12750.87f, 124.0f, 12.0f};
        Vector4f vec2{123.5211f, 1720.3f, 86547.2f, 1.0f};
        mXD_IS_FALSE(vec1 == vec2, "Different vectors is equal");
        mXD_IS_TRUE(vec1 != vec2, "Different vectors is equal");
        return A_A;
    }

    X
    Test_ArithmeticVector4()
    {
        Vector4f vec1{12.0f, -10.0f, 5.0f, 1.0f};
        Vector4f vec2{2.0f, 2.0f, 2.0f, 0.2f};

        mXD_IS_TRUE((vec1 + vec2 == Vector4f{14.0f, -8.0f, 7.0f, 1.2f}), "Summarize of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 - vec2 == Vector4f{10.0f, -12.0f, 3.0f, 0.8f}), "Subtract of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 * 2.0f == Vector4f{24.0f, -20.0f, 10.0f, 2.0f}), "Multiply of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 / 2.0f == Vector4f{6.0f, -5.0f, 2.5f, 0.5f}), "Division of two vectors returned not expected values");
        return A_A;
    }

    X
    Test_Matrix4Construction()
    {
        {
            Matrix4f matrixf{};
            mXD_IS_TRUE(
                fIsNearlyEqual(matrixf[0].m_x, 1.0f) &&
                fIsNearlyEqual(matrixf[1].m_y, 1.0f) &&
                fIsNearlyEqual(matrixf[2].m_z, 1.0f) &&
                fIsNearlyEqual(matrixf[3].m_w, 1.0f), "Matrix initialized with wrong values");
        }

        {
            Matrix4f matrixf{1.0f};
            mXD_IS_TRUE(
                    fIsNearlyEqual(matrixf[0].m_x, 1.0f) &&
                    fIsNearlyEqual(matrixf[1].m_y, 1.0f) &&
                    fIsNearlyEqual(matrixf[2].m_z, 1.0f) &&
                    fIsNearlyEqual(matrixf[3].m_w, 1.0f), "Matrix initialized with wrong values");
        }

        {
            Matrix4f matrixf{{2.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 3.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 4.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 5.0f}};
            mXD_IS_TRUE(
                    fIsNearlyEqual(matrixf[0].m_x, 2.0f) &&
                    fIsNearlyEqual(matrixf[1].m_y, 3.0f) &&
                    fIsNearlyEqual(matrixf[2].m_z, 4.0f) &&
                    fIsNearlyEqual(matrixf[3].m_w, 5.0f), "Matrix initialized with wrong values");
        }

        return A_A;
    }
}


int
main(int argc, char** argv)
{
   X_Call(XD::Test_Abs(), "Abs test failed");
   X_Call(XD::Test_IsNearlyEqual(), "IsNearly equal test failed");
   X_Call(XD::Test_CreateDefaultVector2(), "Create vec 2 test failed");
   X_Call(XD::Test_EqualityVector2(), "Vec 2 equality test failed");
   X_Call(XD::Test_ArithmeticVector2(), "Vec 2 arithmetic test failed");
   X_Call(XD::Test_NormalizeVector2(), "Vec 2 normalize test failed");
   X_Call(XD::Test_DotVector2(), "Vec 2 dot test failed");
   X_Call(XD::Test_CreateDefaultVector3(), "Vec 3 creation test failed");
   X_Call(XD::Test_EqualityVector3(), "Vec 3 equality test failed");
   X_Call(XD::Test_ArithmeticVector3(), "Vec 3 arithmetic test failed");
   X_Call(XD::Test_NormalizeVector3(), "Vec 3 normalize test failed");
   X_Call(XD::Test_DotVector3(), "Vec 3 dot test failed");
   X_Call(XD::Test_CreateDefaultVector3(), "Vec 4 creation test failed");
   X_Call(XD::Test_EqualityVector3(), "Vec 4 equality test failed");
   X_Call(XD::Test_ArithmeticVector3(), "Vec 4 arithmetic test failed");
   X_Call(XD::Test_Matrix4Construction(), "Mat4 construction test failed");
   return XD::A_A;
}
