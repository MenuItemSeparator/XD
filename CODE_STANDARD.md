# Coding Standard for ModularProject

## 1. General Rules

### 1.1 Encoding
- **All files must be in UTF-8 format**
- No other encodings allowed

### 1.2 Formatting
- **Tab size: 4 spaces**
- **Prefer tabs over spaces** for indentation
- Maximum line length: 280 characters
- Line ending: Unix (LF)

### 1.3 Naming Conventions
- **Classes**: PascalCase (`MyClass`, `ApplicationWindow`)
- **Functions/Methods**: PascalCase (`fn_CreateWindow`, `fn_GetPosition`)
- **Variables**: PascalCase (`Var_WindowWidth`, `Var_MaxCount`)
- **Constants**: UPPER_SNAKE_CASE (`MAX_BUFFER_SIZE`)
- **Files**: PascalCase (`MyClass.h`, `Application.cpp`)

### 1.4 Class Member Prefixes
- **Instance variables**: `Var_` prefix (`Var_WindowWidth`, `Var_Title`)
- **Constant variables**: `cvar_` prefix (`CVar_MaxSize`, `CVar_DefaultTitle`)
- **Class methods**: `fn_` prefix (`fn_CreateWindow`, `fn_GetPosition`)
- **No postfix** Wrong : var_Title_ m_Title | Ok: Var_Title

### 1.5 Comments
- Use `//` for single-line comments
- Use `/* */` for multi-line comments
- Document public methods using Doxygen-style comments

## 2. File Structure

### 2.1 Header Files (.h)
```cpp
#pragma once

#include <iostream>
#include <string>

class MyClass 
{
public:
    MyClass();
    ~MyClass();

    void fn_Method();

private:
    int Var_Member;
    const int CVar_MaxValue;
};
```

### 2.2 Implementation Files (.cpp)
```cpp
#include "my_class.h"

MyClass::MyClass() 
	: Var_Member(0), CVar_MaxValue(100) 
{

}

void MyClass::fn_Method() 
{

}
```

## 3. C++ Rules

### 3.1 Language Standard
- Use C++17 or higher
- Set `CMAKE_CXX_STANDARD 17` in CMake

### 3.2 Recommendations
- Use `nullptr` instead of `NULL`
- Use `override` when overriding virtual methods
- Avoid raw pointers, use smart pointers
- Use `const` for immutable methods

### 3.3 Exceptions
- Do not use exceptions
- Do not use exceptions for flow control
- Use `noexcept` for methods that do not throw

## 4. CMake

### 4.1 Structure
- Minimum version: 3.20
- Use `add_library()` for static libraries
- Use `target_include_directories()` for include paths

### 4.2 Example
```cmake
cmake_minimum_required(VERSION 3.20)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(mylib STATIC
    mylib.cpp
)

target_include_directories(mylib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
```

## 5. Project Organization

### 5.1 Directory Structure
```
project/
├── CMakeLists.txt
└── src/
    ├── main.cpp
    ├── module1/
    │   ├── CMakeLists.txt
    │   ├── module1.h
    │   └── module1.cpp
    └── module2/
        ├── CMakeLists.txt
        ├── module2.h
        └── module2.cpp
```

### 5.2 Modularity
- Each module in a separate directory
- Own CMakeLists.txt for each module
- Minimal dependencies between modules

## 6. Testing

### 6.1 Unit Tests
- Use Google Test or similar
- Place tests in `tests/` directory
- Name tests: `test_module_name.cpp`

---

**Version**: 1.1  
**Date**: 27.04.2026