#include "XD_WindowsOpenGLRenderer.h"

namespace XD
{
    static i4 gPixelFormatAttribs[] = 
    {
        WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
        WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,         32,
        WGL_DEPTH_BITS_ARB,         24,
        WGL_STENCIL_BITS_ARB,       8,
        0
    };

    static i4 gGLAttribList[] = 
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };

    static GLenum 
    fShaderDataTypeToOpenGLType(eShaderDataType type)
	{
		switch (type)
		{
		case eShaderDataType::Float:        return GL_FLOAT;
		case eShaderDataType::Float2:       return GL_FLOAT;
		case eShaderDataType::Float3:       return GL_FLOAT;
		case eShaderDataType::Float4:       return GL_FLOAT;
		case eShaderDataType::Matrix3f:     return GL_FLOAT;
		case eShaderDataType::Matrix4f:     return GL_FLOAT;
		case eShaderDataType::Integer:      return GL_INT;
		case eShaderDataType::Integer2:     return GL_INT;
		case eShaderDataType::Integer3:     return GL_INT;
		case eShaderDataType::Integer4:     return GL_INT;
		case eShaderDataType::Bool:         return GL_BOOL;
        case eShaderDataType::None:
        default:
            break;
		}

		mXD_ASSERTM(false, "Unknown ShaderDataType!");
		return 0;
	}

    static X
    fCheckShaderErrorsX(GLuint _id)
	{
		i4 result{};
		char infoLog[1024];
        OpenGLCheck(gGLGetShaderiv(_id, GL_COMPILE_STATUS, &result));
        if (!result)
        {
            OpenGLCheck(gGLGetShaderInfoLog(_id, 1024, nullptr, infoLog));
            mLOG("ERROR: Compile-time error: " << (const char*)infoLog);
            return X_X;
        }
		return A_A;
	}

    X
    XD_OpenGLVertexBufferObject::fCreateX(Memory *_data, VertexBufferLayoutHandle _referenceHandle)
    {
        mXD_ASSERT(_data);
        m_size = _data->m_byteSize;
        m_layout = _referenceHandle;

        OpenGLCheck(gGLGenBuffersProc(1, &m_id), "Can't gen vb buffer");
        mXD_ASSERT(m_id);
        OpenGLCheck(gGLBindBufferProc(GL_ARRAY_BUFFER, m_id), "Can't bind vb buffer");
        OpenGLCheck(gGLBufferDataProc(GL_ARRAY_BUFFER, m_size, _data->m_data, _data->m_data ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW), "Error when buffer data to vb");
        OpenGLCheck(gGLBindBufferProc(GL_ARRAY_BUFFER, 0), "Can't unbind vb buffer");
        return A_A;
    }

    X
    XD_OpenGLVertexBufferObject::fUpdateX(u8 _offset, Memory *_data)
    {
        mXD_ASSERT(m_id);
        mXD_ASSERT(_data);

        OpenGLCheck(gGLBindBufferProc(GL_ARRAY_BUFFER, m_id), "Can't bind vb buffer");
        OpenGLCheck(gGLBufferSubDataProc(GL_ARRAY_BUFFER, _offset, _data->m_byteSize, _data->m_data), "Error when buffer subdata to vb");
        OpenGLCheck(gGLBindBufferProc(GL_ARRAY_BUFFER, 0), "Can't unbind vb buffer");

        return A_A;
    }

    X
    XD_OpenGLVertexBufferObject::fDestroyX()
    {
        OpenGLCheck(gGLBindBufferProc(GL_ARRAY_BUFFER, 0), "Can't unbind vb buffer");
        OpenGLCheck(gGLDeleteBuffersProc(1, &m_id), "Can't delete vb buffer");

        return A_A;
    }

    X XD_OpenGLVertexBufferObject::fBindX()
    {
        OpenGLCheck(gGLBindBufferProc(GL_ARRAY_BUFFER, m_id), "Can't bind vb buffer");
        return A_A;
    }

    X XD_OpenGLVertexBufferObject::fUnbindX()
    {
        OpenGLCheck(gGLBindBufferProc(GL_ARRAY_BUFFER, 0), "Can't unbind vb buffer");
        return A_A;
    }

    X
    XD_OpenGLVertexArrayObject::fCreateX(VertexBufferObjectHandle _vboHandle, XD_OpenGLVertexBufferObject* _vboObject, XD_BufferLayout* _vboLayout)
    {
        OpenGLCheck(gGLGenVertexArraysProc(1, &m_id), "Can't gen vao");
        mXD_ASSERT(m_id);
        X_Call(fAddVBOX(_vboHandle, _vboObject, _vboLayout), "Error while adding vbo to vao");
        return A_A;
    }

    X 
    XD_OpenGLVertexArrayObject::fAddVBOX(VertexBufferObjectHandle _vboHandle, XD_OpenGLVertexBufferObject* _vboObject, XD_BufferLayout* _vboLayout)
    {
        mXD_ASSERT(_vboObject);
        mXD_ASSERT(_vboLayout);

        OpenGLCheck(gGLBindVertexArrayProc(m_id), "Can't bind vao");
        OpenGLCheck(_vboObject->fBindX(), "Can't bind vbo");

		for (tLayoutIter it = _vboLayout->fBegin(); it != _vboLayout->fEnd(); ++it)
		{
			switch (it->fGetType())
			{
			case eShaderDataType::Float:
			case eShaderDataType::Float2:
			case eShaderDataType::Float3:
			case eShaderDataType::Float4:
			case eShaderDataType::Integer:
			case eShaderDataType::Integer2:
			case eShaderDataType::Integer3:
			case eShaderDataType::Integer4:
			case eShaderDataType::Bool:
			{
				OpenGLCheck(gGLEnableVertexAttribArrayProc(m_layoutIndex), "");
				OpenGLCheck(gGLVertexAttribPointerProc(m_layoutIndex,
					XD_LayoutElement::fGetComponentCount(it->fGetType()),
					fShaderDataTypeToOpenGLType(it->fGetType()),
					GL_FALSE,
					_vboLayout->fGetStride(),
					(const void*)it->fGetOffset()), "Error when vao attrib pointer");
				++m_layoutIndex;
				break;
			}
			case eShaderDataType::Matrix3f:
			case eShaderDataType::Matrix4f:
			{
				u8 count = XD_LayoutElement::fGetComponentCount(it->fGetType());
				for (u8 i = 0; i < count; ++i)
				{
					OpenGLCheck(gGLEnableVertexAttribArrayProc(m_layoutIndex), "Can't enable vertex attrib");
					OpenGLCheck(gGLVertexAttribPointerProc(m_layoutIndex, 
						count,
						fShaderDataTypeToOpenGLType(it->fGetType()),
						GL_FALSE,
						_vboLayout->fGetStride(),
						(const void*)(it->fGetOffset() + sizeof(float) * count * i)), "Error when vao attrib pointer");
					OpenGLCheck(gGLVertexAttribDivisorProc(m_layoutIndex, 1), "Error when vao attrib divisor");
					++m_layoutIndex;
				}
				break;
			}
			default:
				mXD_ASSERTM(false, "Unknown ShaderDataType!");
			}
		}

        X_Call(_vboObject->fUnbindX(), "Can't unbind vbo");
        OpenGLCheck(gGLBindVertexArrayProc(0), "Can't unbind vao");

		m_vbos.push_back(_vboHandle);

        return A_A;
    }

    X
    XD_OpenGLVertexArrayObject::fDestroyX()
    {
        mXD_ASSERT(m_id);
        OpenGLCheck(gGLBindVertexArrayProc(0), "Can't unbind vao");
        OpenGLCheck(gGLDeleteVertexArraysProc(1, &m_id), "Can't delete vao");
        return A_A;
    }

    X
    XD_OpenGLShader::fCreateX(const std::string& _filepath)
    {
        std::filesystem::path path{_filepath};
        if(!std::filesystem::exists(path)) return X_X;

        X_Call(fFindShaderTypeX(path), "Can't recognize shader type");

		std::ifstream fStream{path};

		mXD_ASSERT(!fStream.fail());

        std::stringstream sStream{};
        sStream << fStream.rdbuf();
        fStream.close();
        std::string shaderSourceText{sStream.str()};
        const GLchar* rawStr = shaderSourceText.c_str();

        m_id = gGLCreateShaderProc(m_type);
        mXD_ASSERT(m_id);
        X_Call(fCheckOpenGLErrorX(__FILE__, __LINE__), "Can't create shader");
        OpenGLCheck(gGLShaderSourceProc(m_id, 1, &rawStr, NULL), "");
        OpenGLCheck(gGLCompileShaderProc(m_id));
        X_Call(fCheckShaderErrorsX(m_id), "Occured some internal errors during shader creation");

        return A_A;
    }

    X
    XD_OpenGLShader::fDestroyX()
    {
        if (!m_id) return X_X;

        OpenGLCheck(gGLDeleteShaderProc(m_id), "Can't delete shader");
        m_id = 0;

        return A_A;
    }

    X
    XD_OpenGLShader::fFindShaderTypeX(const std::filesystem::path& _filepath)
    {
        std::string fileExtension = _filepath.extension().u8string();
        if(fileExtension == ".vs")
        {
            m_type = GL_VERTEX_SHADER;
            return A_A;
        }
        else if(fileExtension == ".fs")
        {
            m_type = GL_FRAGMENT_SHADER;
            return A_A;
        }

        mLOG("Unknown shader file extension " << fileExtension);
        return X_X;
    }

    XD_OpenGLContext::XD_OpenGLContext() : 
        m_hwnd(NULL),
        m_context(NULL)
    {
    }

    XD_OpenGLContext::~XD_OpenGLContext()
    {
        fDestroyX().fCheck();
    }

    X 
    XD_OpenGLContext::fCreateX(HWND _hwnd, const int *_attribList)
    {
        if(!_hwnd) return X_X;

        m_hwnd = _hwnd;
        m_hdc = GetDC(m_hwnd);
        m_context = gWGLCreateContextAttribsARBProc(m_hdc, NULL, _attribList);

        return m_context ? A_A : X_X;
    }

    X 
    XD_OpenGLContext::fDestroyX()
    {
        HGLRC currentContext = wglGetCurrentContext();
        if(currentContext == m_context)
        {
            X_Call(fUnbindX(), "Error while unbinding gl context");
        }

        wglDeleteContext(m_context);
        return A_A;
    }

    X 
    XD_OpenGLContext::fBindX()
    {
        if(!m_hwnd) return X_X;
        
        wglMakeCurrent(m_hdc, m_context);
        
        return A_A;
    }

    X 
    XD_OpenGLContext::fUnbindX()
    {
        if(!m_hwnd) return X_X;

        wglMakeCurrent(m_hdc, m_context);

        return A_A;
    }

    X 
    XD_OpenGLContext::fSwapBuffersX()
    {
        return SwapBuffers(m_hdc) ? A_A : X_X;
    }

    XD_OpenGLRenderer::XD_OpenGLRenderer() :
        m_context(nullptr),
        m_openGLDll(),
        m_pfd()
    {
    }

    X 
    XD_OpenGLRenderer::fvInitializeX(void* _hwnd)
    {
        HWND hwnd = reinterpret_cast<HWND>(_hwnd);

        X_Call(m_openGLDll.fLoadLibraryX("opengl32.dll"), "Error while loading openGL lib");
        X_Call(fExtractInitialProcsFromDummyContextX(), "Error while loading OpenGL initial proc ptrs");
        X_Call(fCreateValidPixelFormatX(hwnd), "Error while creating valid pixel format");
        X_Call(fLoadOpenGLExtensionProcPtrX(m_openGLDll), "Error while loading initial gl proc ptrs");

        mLOG("OpenGL renderer initialized successfully");
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fExtractInitialProcsFromDummyContextX()
    {
        WNDCLASSEX wc{};
        MSG msg{};
        HMODULE hInstance = GetModuleHandle(NULL);

        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = CS_OWNDC;
        wc.lpfnWndProc   = DefWindowProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = "Dummy_WGL";
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

        if(!RegisterClassEx(&wc))
        {
            mLOG("Dummy window class registration failed!");
            MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
            return X_X;
        }

        HWND dummyHwnd = CreateWindowEx
            (
                WS_EX_CLIENTEDGE,
                wc.lpszClassName,
                "Dummy openGL window",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                640,
                360,
                NULL,
                NULL,
                hInstance,
                this
                );

        if(dummyHwnd == NULL)
        {
            mLOG("Window Creation Failed!");
            MessageBoxA(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
            return X::fFail();
        }

        PIXELFORMATDESCRIPTOR dummyPFD = {
            .nSize = sizeof(dummyPFD),
            .nVersion = 1,
            .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            .iPixelType = PFD_TYPE_RGBA,
            .cColorBits = 32,
            .cAlphaBits = 8,
            .cDepthBits = 24,
            .cStencilBits = 8,
            .iLayerType = PFD_MAIN_PLANE,
        };

        HDC dummyDC = GetDC(dummyHwnd);
        i4 pixelFormat = ChoosePixelFormat(dummyDC, &dummyPFD);

        if(!pixelFormat)
        {
            mXD_ASSERTM(false, "Failed to find a suitable pixel format")
            return 0;
        }

        if(!SetPixelFormat(dummyDC, pixelFormat, &dummyPFD))
        {
            mXD_ASSERTM(false, "Failed to set pixel format")
            return 0;
        }

        HGLRC dummyContext = wglCreateContext(dummyDC);

        if (!dummyContext) 
        {
            mXD_ASSERTM(false, "Failed to create a dummy OpenGL rendering context.");
            return X_X;
        }

        if (!wglMakeCurrent(dummyDC, dummyContext)) 
        {
            mXD_ASSERTM(false, "Failed to activate dummy OpenGL rendering context.");
            return X_X;
        }

        X_Call(fLoadOpenGLInitialProcPtrX(), "Error while loading initial openGL proc ptrs");

        wglMakeCurrent(dummyDC, NULL);
        wglDeleteContext(dummyContext);
        ReleaseDC(dummyHwnd, dummyDC);
        DeleteDC(dummyDC);
        DestroyWindow(dummyHwnd);
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fCreateValidPixelFormatX(HWND _hwnd)
    {
        i4 pixelFormat = 0;
        u4 numFormats = 0;

        HDC hdc = GetDC(_hwnd);
        gWGLChoosePixelFormatARBProc(hdc, gPixelFormatAttribs, NULL, 1, &pixelFormat, &numFormats);

        if(!numFormats)
        {
            mXD_ASSERTM(false, "Failed to choose opengl pixel format");
            return X_X;
        }

        DescribePixelFormat(hdc, pixelFormat, sizeof(m_pfd), &m_pfd);

        if(!pixelFormat)
        {
            mXD_ASSERTM(false, "Failed to find a suitable pixel format")
            return 0;
        }

        if(!SetPixelFormat(hdc, pixelFormat, &m_pfd))
        {
            mXD_ASSERTM(false, "Failed to set pixel format")
            return 0;
        }

        m_context = std::make_shared<XD_OpenGLContext>();
        X_Call(m_context->fCreateX(_hwnd, gGLAttribList), "Can't create opengl context wrapper");
        X_Call(m_context->fBindX(), "Can't bind open gl context");

        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvShutdownX()
    {
        X_Call(m_openGLDll.fUnloadLibraryX(), "Can't unload open gl library");
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvBeginFrameX()
    {
        OpenGLCheck(gSetClearColorProc(1.0f, 0.6f, 0.2f, 1.0f), "Can't set new clear color");
        OpenGLCheck(gClearProc(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT), "Can't clear viewport");
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvEndFrameX()
    {
        X_Call(m_context->fSwapBuffersX(), "Error while swapping buffers");
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvCreateVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle, const std::vector<eShaderDataType>& _elements)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvDestroyVertexBufferLayoutX(VertexBufferLayoutHandle _layoutHandle)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvCreateIBOX(IndexBufferHandle _iboHandle, Memory* _data)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvDestroyIBOX(IndexBufferHandle _iboHandle)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvCreateVBOX(VertexBufferObjectHandle _vboHandle, Memory* _data, VertexBufferLayoutHandle _layoutHandle)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvDestroyVBOX(VertexBufferObjectHandle _vboHandle)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvCreateVAOX(VertexArrayObjectHandle _vaoHandle, VertexBufferObjectHandle *_vboHandleArray, u8 _arraySize)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvDestroyVAOX(VertexArrayObjectHandle _vaoHandle)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvCreateShaderX(ShaderHandle _handle, const std::string& _filePath)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvDestroyShaderX(ShaderHandle _handle)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvCreateShaderProgramX(ShaderProgramHandle _programHandle, ShaderHandle _vsh, ShaderHandle _fsh)
    {
        return A_A;
    }

    X 
    XD_OpenGLRenderer::fvDestroyShaderProgramX(ShaderProgramHandle _programHandle)
    {
        return A_A;
    }

}
