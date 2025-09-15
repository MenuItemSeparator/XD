cmake_minimum_required(VERSION 3.16)

project(NFE_01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(NFE_01 main.cpp
    Engine/Parser/ParserPolicySelector.h
    Engine/Core/TestableInterface.h
    Engine/Core/OldStyleExceptionFlow.h
    Engine/Core/Type.h
    Engine/Core/Debug.h
    Engine/Core/Helpers.h)

include(GNUInstallDirs)
install(TARGETS NFE_01
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
