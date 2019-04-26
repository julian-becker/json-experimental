cmake_minimum_required(VERSION 3.13)
project(json_test LANGUAGES CXX)

find_package(Catch2 REQUIRED)
find_package(json REQUIRED)

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/test1.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    json::json
    Catch2::Catch2
)

add_test(
  NAME    ${PROJECT_NAME}
  COMMAND $<TARGET_FILE:${PROJECT_NAME}>
)
