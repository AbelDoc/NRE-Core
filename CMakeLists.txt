cmake_minimum_required(VERSION 3.15)
project(NRE_Utility)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wno-virtual-move-assign -Wall -Wextra -Wfatal-errors -Wfloat-equal -Wstrict-overflow -Wshadow -Wconversion -Wunreachable-code -Wuninitialized -Winit-self -Werror -fstrict-overflow -O3 -std=c++17")

include_directories(C:/Users/abell/Documents/GitHub/NRE-Tester/src)
include_directories(C:/Users/abell/Documents/GitHub/NRE-Memory/src)

include_directories(src)
include_directories(src/Exception)
include_directories(src/Header)
include_directories(src/Utility)
include_directories(src/Utility/Array)
include_directories(src/Utility/ForwardList)
include_directories(src/Utility/HashTable)
include_directories(src/Utility/Id)
include_directories(src/Utility/Observable)
include_directories(src/Utility/Observer)
include_directories(src/Utility/Pair)
include_directories(src/Utility/Singleton)
include_directories(src/Utility/String)
include_directories(src/Utility/UnorderedMap)
include_directories(src/Utility/Vector)

set(COMPILE_LIST
        src/Exception/NRE_IException.hpp
        src/Header/NRE_Exception.hpp
        src/Header/NRE_Utility.hpp
        src/Utility/Array/NRE_Array.hpp
        src/Utility/ForwardList/NRE_ForwardList.hpp
        src/Utility/DetaiL/HashTable/NRE_HashTable.hpp
        src/Utility/Id/NRE_Id.hpp
        src/Utility/Observable/NRE_Observable.hpp
        src/Utility/Observer/NRE_Observer.hpp
        src/Utility/Pair/NRE_Pair.hpp
        src/Utility/Singleton/NRE_Singleton.hpp
        src/Utility/String/NRE_String.hpp
        src/Utility/UnorderedMap/NRE_UnorderedMap.hpp
        src/Utility/Interfaces/NRE_StaticInterface.hpp
        src/Utility/Interfaces/Uncopyable/NRE_Uncopyable.hpp
        src/Utility/Interfaces/Stringable/NRE_Stringable.hpp
        src/Utility/Vector/NRE_Vector.hpp)

set(EXEC_LIST
        ${COMPILE_LIST}
        src/NRE_Main.cpp)

set(TEST_LIST
        test/NRE_Main.cpp)

add_executable(NRE_Utility ${EXEC_LIST})
add_executable(NRE_Utility_Test ${TEST_LIST})

target_link_libraries(NRE_Utility_Test "C:/lib/NRE/libNRE-Tester.a")
