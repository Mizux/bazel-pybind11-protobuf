workspace(name = "org_mizux_bazelpybind11protobuf")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

# Bazel Extensions
## Bazel Skylib rules.
git_repository(
    name = "bazel_skylib",
    tag = "1.7.1",
    remote = "https://github.com/bazelbuild/bazel-skylib.git",
)
load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
bazel_skylib_workspace()

## Bazel rules.
git_repository(
    name = "platforms",
    tag = "0.0.10",
    remote = "https://github.com/bazelbuild/platforms.git",
)

git_repository(
    name = "rules_cc",
    tag = "0.0.9",
    remote = "https://github.com/bazelbuild/rules_cc.git",
)

git_repository(
    name = "rules_proto",
    tag = "5.3.0-21.7",
    remote = "https://github.com/bazelbuild/rules_proto.git",
)

git_repository(
    name = "rules_python",
    tag = "0.34.0",
    remote = "https://github.com/bazelbuild/rules_python.git",
)

# Dependencies
## ZLIB
new_git_repository(
    name = "zlib",
    build_file = "@com_google_protobuf//:third_party/zlib.BUILD",
    tag = "v1.3.1",
    remote = "https://github.com/madler/zlib.git",
)

## Abseil-cpp
git_repository(
    name = "com_google_absl",
    tag = "20240116.2",
    patches = ["//patches:abseil-cpp-20240116.2.patch"],
    patch_args = ["-p1"],
    remote = "https://github.com/abseil/abseil-cpp.git",
)

## Re2
git_repository(
    name = "com_google_re2",
    tag = "2024-04-01",
    remote = "https://github.com/google/re2.git",
    repo_mapping = {"@abseil-cpp": "@com_google_absl"},
)

## Protobuf
# proto_library and cc_proto_library rules implicitly
# depend on @com_google_protobuf for protoc and proto runtimes.
# This statement defines the @com_google_protobuf repo.
git_repository(
    name = "com_google_protobuf",
    patches = ["//patches:protobuf-v27.2.patch"],
    patch_args = ["-p1"],
    tag = "v27.2",
    remote = "https://github.com/protocolbuffers/protobuf.git",
)
# Load common dependencies.
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()

## Python
load("@rules_python//python:repositories.bzl", "py_repositories")
py_repositories()

load("@rules_python//python:repositories.bzl", "python_register_multi_toolchains")
DEFAULT_PYTHON = "3.11"
python_register_multi_toolchains(
    name = "python",
    default_version = DEFAULT_PYTHON,
    python_versions = [
      "3.12",
      "3.11",
      "3.10",
      "3.9",
      "3.8"
    ],
    ignore_root_user_error=True,
)

# Create a central external repo, @pip_deps, that contains Bazel targets for all the
# third-party packages specified in the requirements.txt file.
load("@rules_python//python:pip.bzl", "pip_parse")
pip_parse(
   name = "pip_deps",
   requirements_lock = "//:requirements.txt",
)

load("@pip_deps//:requirements.bzl", install_pip_deps="install_deps")
install_pip_deps()

# Protobuf
#load("@com_google_protobuf//bazel:system_python.bzl", "system_python")
#system_python(
#    name = "system_python",
#    minimum_python_version = "3.8",
#)

## `pybind11_bazel`
git_repository(
    name = "pybind11_bazel",
    tag = "v2.12.0", # 2024/04/08
    patches = ["//patches:pybind11_bazel.patch"],
    patch_args = ["-p1"],
    remote = "https://github.com/pybind/pybind11_bazel.git",
)

new_git_repository(
    name = "pybind11",
    build_file = "@pybind11_bazel//:pybind11-BUILD.bazel",
    tag = "v2.13.1",
    remote = "https://github.com/pybind/pybind11.git",
)

new_git_repository(
    name = "org_pybind11_abseil",
    tag = "v202402.0",
    patches = ["//patches:pybind11_abseil.patch"],
    patch_args = ["-p1"],
    remote = "https://github.com/pybind/pybind11_abseil.git",
)

new_git_repository(
    name = "pybind11_protobuf",
    commit = "84653a591aea5df482dc2bde42c19efafbd53a57", # 2024/06/28
    remote = "https://github.com/pybind/pybind11_protobuf.git",
)

## Testing
git_repository(
    name = "com_google_googletest",
    tag = "v1.14.0",
    remote = "https://github.com/google/googletest.git",
)
