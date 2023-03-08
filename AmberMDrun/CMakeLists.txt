set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "-static-libstdc++ -static-libgcc")
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(FATAL_ERROR  "Windows is not supported")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(FATAL_ERROR  "Mac OS X is not supported")
ELSE ()
    MESSAGE(FATAL_ERROR "${CMAKE_SYSTEM_NAME} is not supported")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
include_directories(include)
include_directories(extern)
add_subdirectory(extern/pybind11)
aux_source_directory(src SOURCE)
#add_library(ambermd SHARED ${SOURCE})
add_library(ambermd STATIC ${SOURCE})
add_executable(amberMd
        main.cpp
        )
target_link_libraries(amberMd PRIVATE ambermd)
pybind11_add_module(_pyamber
        pyamber.cpp
        )
target_link_libraries(_pyamber PUBLIC ambermd)
install(
  TARGETS _pyamber ambermd
  LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/AmberMDrun
  )
