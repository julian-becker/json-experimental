include(FetchContent)
include(AddModule)
include(InstallBlock)

set(ENABLE_INSTALL OFF)

set(CATCH2_REPOSITORY "https://github.com/catchorg/Catch2.git" CACHE STRING "The location of the Catch2 git-repository")

FetchContent_Declare(
    catch
    GIT_REPOSITORY ${CATCH2_REPOSITORY}
    GIT_TAG        v2.5.0
)

FetchContent_GetProperties(catch)
if(NOT Catch2_POPULATED)
  FetchContent_Populate(catch)
  #add_subdirectory(${catch_SOURCE_DIR} ${catch_BINARY_DIR})
endif()

add_module(
	NAME "Catch2"
	DIRECTORY "${catch_SOURCE_DIR}" "${catch_BINARY_DIR}"
	TARGETS Catch2
)

add_library(Catch2::Catch2 ALIAS Catch2)

set(ENABLE_INSTALL ON)
