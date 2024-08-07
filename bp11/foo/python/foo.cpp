#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "pybind11_abseil/absl_casters.h"
#include "pybind11_abseil/status_casters.h"
#include "pybind11_protobuf/native_proto_caster.h"

#include "bp11/foo/foo.hpp"

namespace py = pybind11;

//PYBIND11_MAKE_OPAQUE(std::vector<std::string>);
//PYBIND11_MAKE_OPAQUE(std::vector<std::vector<std::string>>);
//PYBIND11_MAKE_OPAQUE(std::vector<std::pair<int, int>>);
//PYBIND11_MAKE_OPAQUE(std::vector<std::vector<std::pair<int, int>>>);

PYBIND11_MODULE(pyfoo, m) {
    //pybind11::google::ImportStatusModule();
    m.doc() = "pyfoo module"; // optional module docstring

    // Absl function
    m.def("absl_function", &::bp11::foo::abslFunction, "A function that return am absl::Status.");
    // absl::Time/Duration bindings.
    m.def("make_duration", &::bp11::foo::MakeDuration, py::arg("secs"));
    m.def("make_infinite_duration", &::bp11::foo::MakeInfiniteDuration);
    m.def("is_infinite_duration", &::bp11::foo::IsInfiniteDuration);
    m.def("check_duration", &::bp11::foo::CheckDuration, py::arg("duration"), py::arg("secs"));
    m.def("make_time", &::bp11::foo::MakeTime, py::arg("secs"));
    m.def("check_datetime", &::bp11::foo::CheckDatetime, py::arg("datetime"), py::arg("secs"));
    // absl::status bindings.
    m.def("return_status", &::bp11::foo::ReturnStatus, py::arg("code"), py::arg("text") = "");

    // Proto function
    m.def("proto_function", &::bp11::foo::protoFunction, "A function that return a proto.");

    // Free function
    m.def("free_function", py::overload_cast<int>(&::bp11::foo::freeFunction), "A free function taking an int.");
    m.def("free_function", py::overload_cast<int64_t>(&::bp11::foo::freeFunction), "A free function taking an int64.");

    // Vector of String
    m.def("string_vector_output", &::bp11::foo::stringVectorOutput, "A function that return a vector of string.");
    m.def("string_vector_input", &::bp11::foo::stringVectorInput, "A function that use a vector of string.");
    m.def("string_vector_ref_input", &::bp11::foo::stringVectorInput, "A function that use a vector of string const ref.");

    // Vector of Vector of String
    m.def("string_jagged_array_output", &::bp11::foo::stringJaggedArrayOutput, "A function that return a jagged array of string.");
    m.def("string_jagged_array_input", &::bp11::foo::stringJaggedArrayInput, "A function that use a jagged array of string.");
    m.def("string_jagged_array_ref_input", &::bp11::foo::stringJaggedArrayRefInput, "A function that use a jagged array of string const ref.");

    // Vector of Pair
    m.def("pair_vector_output", &::bp11::foo::pairVectorOutput, "A function that return a vector of pair.");
    m.def("pair_vector_input", &::bp11::foo::pairVectorInput, "A function that use a vector of pair.");
    m.def("pair_vector_ref_input", &::bp11::foo::pairVectorRefInput, "A function that use a vector of pair const ref.");

    // Vector of Vector of Pair
    m.def("pair_jagged_array_output", &::bp11::foo::pairJaggedArrayOutput, "A function that return a jagged array of pair.");
    m.def("pair_jagged_array_input", &::bp11::foo::pairJaggedArrayInput, "A function that use a jagged array of pair.");
    m.def("pair_jagged_array_ref_input", &::bp11::foo::pairJaggedArrayRefInput, "A function that use a jagged array of pair const ref.");

    // Class Foo
    py::class_<::bp11::foo::Foo>(m, "Foo")
      .def_static("static_function", py::overload_cast<int>(&::bp11::foo::Foo::staticFunction))
      .def_static("static_function", py::overload_cast<int64_t>(&::bp11::foo::Foo::staticFunction))
      .def(py::init<>())
      .def_property("int", &::bp11::foo::Foo::getInt, &::bp11::foo::Foo::setInt, py::return_value_policy::copy)
      .def_property("int64", &::bp11::foo::Foo::getInt64, &::bp11::foo::Foo::setInt64, py::return_value_policy::copy)
      .def("__str__", &::bp11::foo::Foo::operator());
}
