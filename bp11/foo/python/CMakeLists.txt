pybind11_add_module(foo_pybind11 MODULE foo.cpp)
set_target_properties(foo_pybind11 PROPERTIES
  LIBRARY_OUTPUT_NAME "pyfoo")
# note: macOS is APPLE and also UNIX !
if(APPLE)
  set_target_properties(foo_pybind11 PROPERTIES
    SUFFIX ".so"
    INSTALL_RPATH "@loader_path;@loader_path/../../../${PYTHON_PROJECT}/.libs;@loader_path/../../../pybind11_abseil"
    )
  set_property(TARGET foo_pybind11 APPEND PROPERTY
    LINK_FLAGS "-flat_namespace -undefined suppress"
    )
elseif(UNIX)
  set_target_properties(foo_pybind11 PROPERTIES
    INSTALL_RPATH "$ORIGIN:$ORIGIN/../../../${PYTHON_PROJECT}/.libs:$ORIGIN/../../../pybind11_abseil"
    )
endif()
target_include_directories(foo_pybind11 PRIVATE
  ${protobuf_SOURCE_DIR})
target_link_libraries(foo_pybind11 PRIVATE
  ${PROJECT_NAMESPACE}::foo
  pybind11_abseil::absl_casters
  pybind11_abseil::status_casters
  pybind11_native_proto_caster
)
add_library(${PROJECT_NAMESPACE}::foo_pybind11 ALIAS foo_pybind11)

add_python_test(${CMAKE_CURRENT_SOURCE_DIR}/foo_test.py)
add_python_test(${CMAKE_CURRENT_SOURCE_DIR}/status_test.py)
