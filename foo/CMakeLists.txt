add_library(foo)

get_cpp_proto(PROTO_HDRS PROTO_SRCS)
target_sources(foo
  PRIVATE
    include/foo/foo.hpp foo.cpp
    ${PROTO_HDRS} ${PROTO_SRCS})
target_include_directories(foo
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>)
target_compile_features(foo PUBLIC cxx_std_17)
set_target_properties(foo PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER "include/foo/foo.hpp;${PROTO_HDRS}")
target_link_libraries(foo PUBLIC protobuf::libprotobuf)
add_library(${PROJECT_NAMESPACE}::foo ALIAS foo)

# Test
if(BUILD_TESTING)
  add_cpp_test(${CMAKE_CURRENT_SOURCE_DIR}/foo_test.cpp)
endif()

# Install
install(TARGETS foo
  EXPORT ${PROJECT_NAME}Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/foo)
