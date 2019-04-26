cmake_minimum_required(VERSION 3.13)
project(json_test LANGUAGES CXX)

find_package(Catch2 REQUIRED)
find_package(json REQUIRED)

macro(add_test_catch TEST_NAME)
	cmake_parse_arguments(ADD_TEST "" "" "SOURCES" ${ARGN})

	message("Adding test ${PROJECT_NAME}.${TEST_NAME}")
	add_executable(${PROJECT_NAME}.${TEST_NAME}
		src/main.cpp
		${ADD_TEST_SOURCES}
	)

	target_compile_features(${PROJECT_NAME}.${TEST_NAME} PRIVATE cxx_std_17)

	target_link_libraries(${PROJECT_NAME}.${TEST_NAME}
	  PRIVATE
		json::json
		Catch2::Catch2
	)

	add_test(
	  NAME    ${PROJECT_NAME}.${TEST_NAME}
	  COMMAND $<TARGET_FILE:${PROJECT_NAME}.${TEST_NAME}>
	)
  unset(TEST_NAME)
  unset(ADD_TEST_SOURCES)
endmacro()

file(GLOB TEST_SOURCES src/*.test.cpp)

foreach(_TEST_SOURCE ${TEST_SOURCES})
	get_filename_component(_TEST_NAME ${_TEST_SOURCE} NAME_WE)
	add_test_catch(${_TEST_NAME} SOURCES ${_TEST_SOURCE})
	unset(_TEST_NAME)
	unset(_TEST_SOURCE)
endforeach(_TEST_SOURCE)
