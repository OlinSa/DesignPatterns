# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "
    FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
    ")
endif()

cmake_minimum_required (VERSION 2.8)
project(DesignPattern)

set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")
set(CMAKE_VERBOSE_MAKEFILE on)

ADD_DEFINITIONS("-Wall -g -DDEBUG")

add_executable(factory factory.cc)
add_executable(abstract_factory abstract_factory.cc)
add_executable(single_object single_object.cc)
add_executable(builder builder.cc)
add_executable(proto_type proto_type.cc)
add_executable(adaptor adaptor.cc)
add_executable(bridge bridge.cc)
add_executable(filter filter.cc)
add_executable(composite composite.cc)
add_executable(decorator decorator.cc)
add_executable(facade facade.cc)
add_executable(flyweight flyweight.cc)
add_executable(proxy proxy.cc)
add_executable(chain chain.cc)
add_executable(command command.cc)
add_executable(interpreter interpreter.cc)
add_executable(interator interator.cc)
add_executable(mediator mediator.cc)
add_executable(memento memento.cc)
add_executable(observer observer.cc)
add_executable(state state.cc)
add_executable(strategy strategy.cc)
add_executable(template template.cc)
add_executable(visitor visitor.cc)