cmake_minimum_required(VERSION 3.10)

project(2048_core_game_test C)

add_subdirectory(unity unity)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ")

set(INCLUDE_DIRS
	../src/
	../include/
)

set(TEST_INCLUDE_DIRS
	.
	fakes
)

set(SRCS
	../src/core_2048.c
)

set(TEST_SRCS
	test_main.c
	test_runner.c
	test_2048_core.c
	test_helpers.c
	fakes/platform_port.c
)

set(GLOBAL_DEFINES
	-UNITY_FLOAT_VERBOSE
)

include_directories(${INCLUDE_DIRS} ${TEST_INCLUDE_DIRS})
add_definitions(${GLOBAL_DEFINES})

link_libraries(unity)
add_executable(${PROJECT_NAME} ${SRCS} ${TEST_SRCS})
