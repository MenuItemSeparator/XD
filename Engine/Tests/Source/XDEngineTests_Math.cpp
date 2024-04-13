#include "XDTest_Minimal.h"
#include "Common/XD_Utility.h"
#include "Common/XD_Math.h"
#include <iostream>

namespace XD
{
    Emote Test_Abs()
    {
        i4 iv1 = 3;
        i4 iv2 = -3;

        mXD_IS_FALSE(iv1 == iv2, "Two different int are equal");
        mXD_IS_TRUE(iv1 == fAbs(iv2), "Two equal float are not equal");

        return A_A;
    }

    Emote Test_IsNearlyEqual()
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

    Emote Test_CreateDefaultVector2()
    {
        Vector2f vec{};
        mXD_IS_TRUE(fIsNearlyZero(vec.m_x), "X value of vector2 is not zero by default");
        mXD_IS_TRUE(fIsNearlyZero(vec.m_y), "Y value of vector2 is not zero by default");
        return A_A;
    }

    Emote Test_EqualityVector2()
    {
        Vector2f vec1{1.567f, 12750.87f};
        Vector2f vec2{123.5211f, 1720.3f};
        mXD_IS_FALSE(vec1 == vec2, "Different vectors is equal");
        mXD_IS_TRUE(vec1 != vec2, "Different vectors is equal");
        return A_A;
    }

    Emote Test_ArithmeticVector2()
    {
        Vector2f vec1{12.0f, -10.0f};
        Vector2f vec2{2.0f, 2.0f};

        mXD_IS_TRUE((vec1 + vec2 == Vector2f{14.0f, -8.0f}), "Summarize of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 - vec2 == Vector2f{10.0f, -12.0f}), "Subtract of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 * 2.0f == Vector2f{24.0f, -20.0f}), "Multiply of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 / 2.0f == Vector2f{6.0f, -5.0f}), "Division of two vectors returned not expected values");
        return A_A;
    }

    Emote Test_NormalizeVector2()
    {
        Vector2f vec1{123.0f, 63.0f};
        mXD_IS_FALSE(fIsNearlyEqual(vec1.fMagnitude(), 1.0f), "Non 1-length vector has 1 length magnitude");
        mXD_IS_TRUE(fIsNearlyEqual(vec1.fGetNormalized().fMagnitude(), 1.0f), "1-length vector has not 1 length magnitude when normalized")
        return A_A;
    }

    Emote Test_DotVector2()
    {
        Vector2f vec1{1.2f, 3.6f};
        Vector2f vec2{12.1f, 0.6f};
        mXD_IS_TRUE(fIsNearlyEqual(vec1.fDot(vec2), 16.68f), "Dot product of vector 2 is not valid")
        return A_A;
    }

    //vec3

    Emote Test_CreateDefaultVector3()
    {
        Vector3f vec{};
        mXD_IS_TRUE(fIsNearlyZero(vec.m_x), "X value of vector3 is not zero by default");
        mXD_IS_TRUE(fIsNearlyZero(vec.m_y), "Y value of vector3 is not zero by default");
        return A_A;
    }

    Emote Test_EqualityVector3()
    {
        Vector3f vec1{1.567f, 12750.87f, 124.0f};
        Vector3f vec2{123.5211f, 1720.3f, 86547.2f};
        mXD_IS_FALSE(vec1 == vec2, "Different vectors is equal");
        mXD_IS_TRUE(vec1 != vec2, "Different vectors is equal");
        return A_A;
    }

    Emote Test_ArithmeticVector3()
    {
        Vector3f vec1{12.0f, -10.0f, 5.0f};
        Vector3f vec2{2.0f, 2.0f, 2.0f};

        mXD_IS_TRUE((vec1 + vec2 == Vector3f{14.0f, -8.0f, 7.0f}), "Summarize of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 - vec2 == Vector3f{10.0f, -12.0f, 3.0f}), "Subtract of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 * 2.0f == Vector3f{24.0f, -20.0f, 10.0f}), "Multiply of two vectors returned not expected values");
        mXD_IS_TRUE((vec1 / 2.0f == Vector3f{6.0f, -5.0f, 2.5f}), "Division of two vectors returned not expected values");
        return A_A;
    }

    Emote Test_NormalizeVector3()
    {
        Vector3f vec1{123.0f, 63.0f, -12.0f};
        mXD_IS_FALSE(fIsNearlyEqual(vec1.fMagnitude(), 1.0f), "Non 1-length vector has 1 length magnitude");
        mXD_IS_TRUE(fIsNearlyEqual(vec1.fGetNormalized().fMagnitude(), 1.0f), "1-length vector has not 1 length magnitude when normalized")
        return A_A;
    }

    Emote Test_DotVector3()
    {
        Vector3f vec1{1.2f, 3.6f, 12.3f};
        Vector3f vec2{12.1f, 0.6f, 9.1f};
        mXD_IS_TRUE(fIsNearlyEqual(vec1.fDot(vec2), 128.61f), "Dot product of vector 3 is not valid")
        return A_A;
    }
}


int main(int argc, char** argv)
{
   int returnValue = 0;
   returnValue += XD::Test_Abs();
   returnValue += XD::Test_IsNearlyEqual();
   returnValue += XD::Test_CreateDefaultVector2();
   returnValue += XD::Test_EqualityVector2();
   returnValue += XD::Test_ArithmeticVector2();
   returnValue += XD::Test_NormalizeVector2();
   returnValue += XD::Test_DotVector2();
   returnValue += XD::Test_CreateDefaultVector3();
   returnValue += XD::Test_EqualityVector3();
   returnValue += XD::Test_ArithmeticVector3();
   returnValue += XD::Test_NormalizeVector3();
   returnValue += XD::Test_DotVector3();
   return returnValue;
}
