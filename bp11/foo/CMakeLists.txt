add_library(foo)
get_cpp_proto(PROTO_HDRS PROTO_SRCS)
target_sources(foo
  PRIVATE
    foo.h foo.cc
    ${PROTO_HDRS} ${PROTO_SRCS})
target_include_directories(foo
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>)
target_compile_features(foo PUBLIC cxx_std_17)
if(MSVC AND BUILD_SHARED_LIBS)
  target_compile_definitions(foo INTERFACE "PROTO_DLL=__declspec(dllimport)")
  target_compile_definitions(foo PRIVATE "PROTO_DLL=__declspec(dllexport)")
 else()
  target_compile_definitions(foo PUBLIC "PROTO_DLL=")
endif()
if(APPLE)
  set_target_properties(foo PROPERTIES
    INSTALL_RPATH "@loader_path")
elseif(UNIX)
  set_target_properties(foo PROPERTIES
    INSTALL_RPATH "$ORIGIN")
endif()
set_target_properties(foo PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER "foo.h;${PROTO_HDRS}")
target_link_libraries(foo PUBLIC
  absl::strings
  absl::status
  absl::time
  protobuf::libprotobuf
)
add_library(${PROJECT_NAMESPACE}::foo ALIAS foo)

add_cpp_test(${CMAKE_CURRENT_SOURCE_DIR}/foo_test.cc)

# Install
install(TARGETS foo
  EXPORT ${PROJECT_NAME}Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bp11/foo)
