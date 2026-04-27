cmake_minimum_required(VERSION 3.16)
project(chipi-gekko-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find chipi CLI (install via cargo install chipi-cli)
find_program(CHIPI_CLI chipi REQUIRED)

# Generate the decoder header from the chipi bindings file
set(GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generated")
set(GENERATED_HEADER "${GENERATED_DIR}/gekko.hpp")
set(CHIPI_SPEC "${CMAKE_CURRENT_SOURCE_DIR}/chipi-spec/gamecube/gekko.chipi")
set(CHIPI_BINDINGS "${CMAKE_CURRENT_SOURCE_DIR}/gekko.bindings.chipi")

file(MAKE_DIRECTORY ${GENERATED_DIR})

add_custom_command(
    OUTPUT ${GENERATED_HEADER}
    COMMAND ${CHIPI_CLI} generate ${CHIPI_BINDINGS}
    DEPENDS ${CHIPI_SPEC} ${CHIPI_BINDINGS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating Gekko decoder from chipi bindings"
)

add_custom_target(generate_decoder DEPENDS ${GENERATED_HEADER})

add_executable(demo src/main.cpp)
add_dependencies(demo generate_decoder)
target_include_directories(demo PRIVATE ${GENERATED_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src)
