cmake_minimum_required(VERSION 3.10)

# Project name and version
project(BuilderFacade VERSION 1.0 LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Source files
set(SOURCES
    Facets.cpp
    Person.cpp
    PersonBuilder.cpp
)

# Header files (for IDEs like Visual Studio, Xcode)
set(HEADERS
    Person.h
    PersonBuilder.h
    PersonAddressBuilder.h
    PersonJobBuilder.h
)

# Create executable
add_executable(builder_facade ${SOURCES} ${HEADERS})

# Set output directory
set_target_properties(builder_facade PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Print build information
message(STATUS "Building Builder Facade Pattern Example")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
