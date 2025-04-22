cmake_minimum_required(VERSION 3.25.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(clock VERSION 0.1.0 LANGUAGES C CXX)

include(GNUInstallDirs)

add_executable(clock clock.cpp)

target_include_directories(clock
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<INSTALL_INTERFACE:include>
)

include(CTest)
enable_testing()
add_subdirectory(test)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

install(TARGETS clock)
