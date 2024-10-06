set(XD_ENGINE_COMMON_DIRECTORY ${XD_ENGINE_ROOT_DIRECTORY}/Common)

set(XD_COMMON_SRC
Common/XD_TimerManager.cpp
Common/XD_TimeClock.cpp
Common/Allocator/XD_Allocator.cpp
Common/Allocator/XD_LinearAllocator.cpp
Common/Allocator/XD_MallocWrapper.cpp
Common/Platform/XD_Common_PlatformSelector.cpp)

set(XD_COMMON_HEADERS
    ${XD_ENGINE_COMMON_DIRECTORY}
)
