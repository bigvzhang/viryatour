set(CMAKE_LEGACY_CYGWIN_WIN32 0) #cmake_minimum_required(VERSION 2.8.4)
cmake_minimum_required(VERSION 3.8)
project(cpptour C CXX) # project(cpptour)


message ("CurrentDir =>" $ENV{PWD})
message ("CurrentPATH =>" $ENV{PATH})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
   add_definitions(-Wno-unknown-pragmas -Wno-write-strings -Wno-terminate)
   execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_GREATER_EQUAL 11)
        message(STATUS "C++20 activated.")
        add_definitions("-std=gnu++20")
   elseif (GCC_VERSION VERSION_GREATER_EQUAL 7)
        message(STATUS "C++17 activated.")
        add_definitions("-std=gnu++17")
   elseif (GCC_VERSION VERSION_EQUAL 6.1)
        message(STATUS "C++14 activated.")
        add_definitions("-std=gnu++14")
   elseif (GCC_VERSION VERSION_EQUAL 4.7)
        message(STATUS "C++11 activated.")
        add_definitions("-std=gnu++11")
   elseif(GCC_VERSION VERSION_EQUAL 4.3)
        message(WARNING "C++0x activated. If you get any errors update to a compiler which fully supports C++11")
        add_definitions("-std=gnu++0x")
   else ()
        message(FATAL_ERROR "C++11 needed. Therefore a gcc compiler with a version higher than 4.3 is needed.")
   endif()
else()# For MSVC
	#message("MSC_VER" ${MSVC_VERSION})
    #1200      = VS  6.0
	#1300      = VS  7.0
	#1310      = VS  7.1
	#1400      = VS  8.0 (v80 toolset)
	#1500      = VS  9.0 (v90 toolset)
	#1600      = VS 10.0 (v100 toolset)
	#1700      = VS 11.0 (v110 toolset)
	#1800      = VS 12.0 (v120 toolset)
	#1900      = VS 14.0 (v140 toolset) 2015
	#1910-1919 = VS 15.0 (v141 toolset) 2017
	#1920-1929 = VS 16.0 (v142 toolset) 2019
	#1930-1939 = VS 17.0 (v143 toolset) 2022
    if(    MSVC_VERSION VERSION_GREATER_EQUAL 1930)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20 /Zc:__cplusplus")
		message("VC2022")	
    elseif(MSVC_VERSION VERSION_GREATER_EQUAL 1920)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20 /Zc:__cplusplus")
		message("VC2019")	
    elseif(MSVC_VERSION VERSION_GREATER_EQUAL 1910)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /Zc:__cplusplus")
		message("VC2017")	
    elseif(MSVC_VERSION VERSION_GREATER_EQUAL 1900)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14 /Zc:__cplusplus")
        message("VC2015")
	else()
        message(FATAL_ERROR "VC Version is too low: ${MSVC_VERSION}")
	endif()
endif()#CMAKE_COMPILER_IS_GNUCXX



message("CMAKE_CXX_COMPILER_VERSION:${CMAKE_CXX_COMPILER_VERSION}")
message("CMAKE_CXX_STANDARD:${CMAKE_CXX_STANDARD}")

SET (SRC0 ../../virya/base)
include_directories(${SRC0} ../../virya)

if (GCC_VERSION VERSION_GREATER_EQUAL 11)
    SET (TESTFILES20 tour140.cpp tour170.cpp tour200.cpp tour201.cpp)
elseif(MSVC_VERSION)
if(    MSVC_VERSION VERSION_GREATER_EQUAL 1930)
	SET (TESTFILES20 tour140.cpp tour170.cpp tour200.cpp tour201.cpp)
elseif(MSVC_VERSION VERSION_GREATER_EQUAL 1920)
	SET (TESTFILES20 tour140.cpp tour170.cpp tour200.cpp tour201.cpp)
elseif(MSVC_VERSION VERSION_GREATER_EQUAL 1910)
		SET (TESTFILES20 tour140.cpp tour170.cpp)
	elseif(MSVC_VERSION VERSION_GREATER_EQUAL 1900)
		SET (TESTFILES20 tour140.cpp)
	else()
		message(FATAL_ERROR "VC Version is too low: ${MSVC_VERSION}")
	endif()
else()
	message(FATAL_ERROR "Unsupported compiler")
endif()

add_library(test_frame STATIC
	${SRC0}/varg.cpp
	${SRC0}/vfile.cpp
	${SRC0}/vfuncentry.cpp
	${SRC0}/vioman.cpp
	${SRC0}/vstring.cpp
	${SRC0}/vsys.cpp
	${SRC0}/vtest.cpp
    ${SRC0}/vtest_main.cpp
	${SRC0}/vtestcommon.cpp
	${SRC0}/vtime.cpp
	${SRC0}/vutility.cpp
)

add_executable (cpptour
                tour001.cpp tour002.cpp tour003.cpp tour004.cpp tour005.cpp 
                tour006.cpp tour007.cpp tour008.cpp tour009.cpp
                tour071.cpp
                tour081.cpp
                tour101.cpp tour102.cpp
                tour110.cpp
                            tour202.cpp tour203.cpp tour204.cpp
                ${TESTFILES20}
)

if(CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries (cpptour test_frame iconv)
else()
	target_link_libraries (cpptour test_frame)
endif()
