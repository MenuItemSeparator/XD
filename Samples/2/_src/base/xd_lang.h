#pragma once

//============================================================================//
// This file a part of project VSGE.
// Look LISENCE.MD for more details.
// Autor: UCKUHT
// Date: 2013-05-19
// Desc: easy language for using inside simple engine.
//============================================================================//

namespace nXD {
// X-operation result.
enum XDE_RESULT{ // easy enum ansver, using for most engine operations.
    BAD = -1,
    X_X = -1, // Negative.
    O_O =  0, // Nothing.
    NOTING = 0,
    A_A =  1,  // Positive.
    OK = 1,
    CRITICAL_SUCCESS = 100500,
};

// Compare result.
enum XDE_CMP{
    // Left lesser.
	Lesser = -1,
    v_W = -1,
    // Equial.
    W_W = 0,
	Equal = 0,
    // Left higer.
    W_v = 1,
	Greater = 1,
};

// Input event.
enum XDE_INPUT{
    XDE_INPUT_NONE,
    XDE_INPUT_UP,
    XDE_INPUT_DOWN,
    XDE_INPUT_
};

// Clasic keyboard.
enum XDE_KEY{
    XDE_KEY_NONE,
    XDE_KEY_UNKNOWN,
    XDE_KEY_SPACE,
    XDE_KEY_ESC,
    XDE_KEY_LEFT,
    XDE_KEY_RIGHT,
    XDE_KEY_UP,
    XDE_KEY_DOWN,
    XDE_KEY_MOUSE_L,
    XDE_KEY_MOUSE_R,
    XDE_KEY_MOUSE_M,
    XDE_KEY_
};

// Pixel format.
enum XDE_PIXEL{
    XDE_PIXEL_NONE,
    XDE_PIXEL_r8g8b8a8,
    XDE_PIXEL_r8g8b8,
    XDE_PIXEL_
};

// Blend mode.
enum XDE_BLEND{
    XDE_BLEND_NONE,
    XDE_BLEND_ONE,
    XDE_BLEND_NORMAL,
    XDE_BLEND_ADD,
    XDE_BLEND_
};

enum XDE_SAMPLE{
	XDE_SAMPLE_NONE,
	XDE_SAMPLE_2x,
	XDE_SAMPLE_
};

// Local point(Centre).
enum XDE_LP{
    // Left.    // Mid.   // Right.
    XDE_LP_LU, XDE_LP_MU, XDE_LP_RU, // Up.
    XDE_LP_LM, XDE_LP_MM, XDE_LP_RM, // Mid.
    XDE_LP_LD, XDE_LP_MD, XDE_LP_RD, // Down.
    XDE_LP_
};

}
