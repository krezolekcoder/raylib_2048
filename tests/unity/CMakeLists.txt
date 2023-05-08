cmake_minimum_required(VERSION 3.10)

add_library(unity STATIC
	core/unity.c
	fixture/unity_fixture.c
)
set(UNITY_DEFINES
	-DUNITY_FLOAT_VERBOSE
)
add_definitions(${UNITY_DEFINES})
target_compile_options(unity PRIVATE "-Wall")
