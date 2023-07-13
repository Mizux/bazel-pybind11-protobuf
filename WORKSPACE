workspace(name = "org_mizux_bazelpybind11protobuf")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

# Bazel Extensions
## Bazel Skylib rules.
git_repository(
    name = "bazel_skylib",
    tag = "1.4.1",
    remote = "https://github.com/bazelbuild/bazel-skylib.git",
)
load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
bazel_skylib_workspace()

## Bazel rules.
git_repository(
    name = "platforms",
    tag = "0.0.6",
    remote = "https://github.com/bazelbuild/platforms.git",
)

git_repository(
    name = "rules_cc",
    tag = "0.0.6",
    remote = "https://github.com/bazelbuild/rules_cc.git",
)

git_repository(
    name = "rules_proto",
    tag = "5.3.0-21.7",
    remote = "https://github.com/bazelbuild/rules_proto.git",
)

git_repository(
    name = "rules_python",
    tag = "0.23.1",
    remote = "https://github.com/bazelbuild/rules_python.git",
)

# Dependencies
## ZLIB
new_git_repository(
    name = "zlib",
    build_file = "@com_google_protobuf//:third_party/zlib.BUILD",
    tag = "v1.2.13",
    remote = "https://github.com/madler/zlib.git",
)

## Re2
git_repository(
    name = "com_google_re2",
    tag = "2023-03-01",
    remote = "https://github.com/google/re2.git",
)

## Abseil-cpp
git_repository(
    name = "com_google_absl",
    tag = "20230125.3",
    patches = ["//patches:abseil-cpp-20230125.3.patch"],
    patch_args = ["-p1"],
    remote = "https://github.com/abseil/abseil-cpp.git",
)

## Protobuf
git_repository(
    name = "com_google_protobuf",
    tag = "v23.3",
    patches = ["//patches:protobuf-v23.3.patch"],
    patch_args = ["-p1"],
    remote = "https://github.com/protocolbuffers/protobuf.git",
)
# Load common dependencies.
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()

## Python
load("@rules_python//python:repositories.bzl", "py_repositories")
py_repositories()

# Create a central external repo, @pip_deps, that contains Bazel targets for all the
# third-party packages specified in the requirements.txt file.
load("@rules_python//python:pip.bzl", "pip_parse")
pip_parse(
   name = "pip_deps",
   requirements = "//:requirements.txt",
)

load("@pip_deps//:requirements.bzl", install_pip_deps="install_deps")
install_pip_deps()

git_repository(
    name = "pybind11_bazel",
    commit = "fc56ce8a8b51e3dd941139d329b63ccfea1d304b",
    patches = ["//patches:pybind11_bazel.patch"],
    patch_args = ["-p1"],
    remote = "https://github.com/pybind/pybind11_bazel.git",
)

new_git_repository(
    name = "pybind11",
    build_file = "@pybind11_bazel//:pybind11.BUILD",
    tag = "v2.10.3",
    remote = "https://github.com/pybind/pybind11.git",
)

new_git_repository(
    name = "pybind11_protobuf",
    #build_file = "@pybind11_bazel//:pybind11.BUILD",
    #tag = "v2.10.3",
    commit = "5baa2dc9d93e3b608cde86dfa4b8c63aeab4ac78",
    remote = "https://github.com/pybind/pybind11_protobuf.git",
)

load("@pybind11_bazel//:python_configure.bzl", "python_configure")
python_configure(name = "local_config_python", python_version = "3")
bind(
    name = "python_headers",
    actual = "@local_config_python//:python_headers",
)

## Testing
git_repository(
    name = "com_google_googletest",
    tag = "v1.13.0",
    remote = "https://github.com/google/googletest.git",
)
