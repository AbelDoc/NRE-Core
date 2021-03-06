cmake_minimum_required(VERSION 3.15)
project(NRE_Core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wno-virtual-move-assign -Wall -Wextra -Wfatal-errors -Wfloat-equal -Wstrict-overflow -Wshadow -Wconversion -Wunreachable-code -Wuninitialized -Winit-self -Werror -fstrict-overflow -std=c++20")

include_directories(C:/Users/abell/Documents/GitHub/NRE-Tester/src)

include_directories(src)
include_directories(src/Concept)
include_directories(src/Core)
include_directories(src/Core/Algorithm)
include_directories(src/Core/Array)
include_directories(src/Core/Detail)
include_directories(src/Core/ForwardList)
include_directories(src/Core/Id)
include_directories(src/Core/Interfaces)
include_directories(src/Core/Observable)
include_directories(src/Core/Observer)
include_directories(src/Core/Pair)
include_directories(src/Core/Singleton)
include_directories(src/Core/Stack)
include_directories(src/Core/StaticVector)
include_directories(src/Core/String)
include_directories(src/Core/Traits)
include_directories(src/Core/UnorderedMap)
include_directories(src/Core/Vector)
include_directories(src/Exception)
include_directories(src/Header)
include_directories(src/Memory)
include_directories(src/Memory/Allocator)
include_directories(src/Memory/Manager)

set(COMPILE_LIST
        src/Exception/NRE_IException.hpp
        src/Header/NRE_Exception.hpp
        src/Header/NRE_Core.hpp
        src/Core/Array/NRE_Array.hpp
        src/Core/ForwardList/NRE_ForwardList.hpp
        src/Core/Detail/HashTable/NRE_HashTable.hpp
        src/Core/Id/NRE_Id.hpp
        src/Core/Observable/NRE_Observable.hpp
        src/Core/Observer/NRE_Observer.hpp
        src/Core/Pair/NRE_Pair.hpp
        src/Core/Singleton/NRE_Singleton.hpp
        src/Core/String/NRE_String.hpp
        src/Core/UnorderedMap/NRE_UnorderedMap.hpp
        src/Core/Interfaces/NRE_StaticInterface.hpp
        src/Core/Interfaces/Uncopyable/NRE_Uncopyable.hpp
        src/Core/Interfaces/Stringable/NRE_Stringable.hpp
        src/Core/Vector/NRE_Vector.hpp)

set(EXEC_LIST
        ${COMPILE_LIST}
        src/NRE_Main.cpp)

set(TEST_LIST
        test/NRE_Main.cpp)

add_executable(NRE_Core ${EXEC_LIST})
add_executable(NRE_Core_Test ${TEST_LIST})

target_link_libraries(NRE_Core_Test "C:/lib/NRE/libNRE-Tester.a")
