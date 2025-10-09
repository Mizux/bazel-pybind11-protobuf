workspace(name = "bazel-pybind11-protobuf")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

################################################################################
#
# WORKSPACE is being deprecated in favor of the new Bzlmod dependency system.
# It will be removed at some point in the future.
#
################################################################################

# Bazel Extensions
## Needed for Abseil.
git_repository(
    name = "bazel_skylib",
    commit = "56a2abbaf131332835ab2721a258ea3c763a7178",
    #tag = "1.8.1",
    remote = "https://github.com/bazelbuild/bazel-skylib.git",
)
load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
bazel_skylib_workspace()

git_repository(
    name = "bazel_features",
    commit = "3f23ff44ff85416d96566bee8e407694cdb6f1f8",
    #tag = "v1.32.0",
    remote = "https://github.com/bazel-contrib/bazel_features.git",
)
load("@bazel_features//:deps.bzl", "bazel_features_deps")
bazel_features_deps()

## Bazel rules.
git_repository(
    name = "platforms",
    commit = "ab99943ab6bed53cff461a3afa99fc79d31e4351",
    #tag = "1.0.0",
    remote = "https://github.com/bazelbuild/platforms.git",
)

git_repository(
    name = "rules_cc",
    commit = "cbee84ad7f583049823f3d1497aab1264cf94f26",
    #tag = "0.1.4",
    remote = "https://github.com/bazelbuild/rules_cc.git",
)

git_repository(
    name = "rules_java",
    #commit = "34d7e1bd22b31594c5de10c2d87c3dc6ab8efa74",
    #tag = "8.9.0",
    tag = "8.13.0",
    remote = "https://github.com/bazelbuild/rules_java.git",
)
load("@rules_java//java:rules_java_deps.bzl", "rules_java_dependencies")
rules_java_dependencies()

git_repository(
    name = "rules_proto",
    commit = "4904e1ca79182d5a3779ecbd23273285ccd70e5c",
    #tag = "7.1.0",
    remote = "https://github.com/bazelbuild/rules_proto.git",
    #repo_mapping = {"@protobuf": "@com_google_protobuf"},
)
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies")
rules_proto_dependencies()
load("@rules_proto//proto:toolchains.bzl", "rules_proto_toolchains")
rules_proto_toolchains()

git_repository(
    name = "rules_python",
    commit = "38f2679fcc6c23a72e4c6309b7fdecb4eafcccf0",
    #tag = "1.6.3",
    remote = "https://github.com/bazelbuild/rules_python.git",
)

load("@rules_python//python:repositories.bzl", "py_repositories")
py_repositories()

DEFAULT_PYTHON = "3.12"

load("@rules_python//python:repositories.bzl", "python_register_toolchains")
python_register_toolchains(
    name = "python",
    # Available versions are listed in @rules_python//python:versions.bzl.
    # We recommend using the same version your team is already standardized on.
    python_version = DEFAULT_PYTHON,
)
load("@rules_python//python:pip.bzl", "pip_parse")
pip_parse(
    name = "pypi",
    python_interpreter_target = "@python_host//:python",
    requirements_lock = "//bazel:requirements_lock_3_12.txt",
)

# Load the starlark macro, which will define your dependencies.
load("@pypi//:requirements.bzl", "install_deps")
# Call it to define repos for your requirements.
install_deps()

## `pybind11_bazel`
git_repository(
    name = "pybind11_bazel",
    commit = "2b6082a4d9d163a52299718113fa41e4b7978db5",
    #tag = "v2.13.6", # 2024/04/08
    #patches = ["//patches:pybind11_bazel.patch"],
    #patch_args = ["-p1"],
    remote = "https://github.com/pybind/pybind11_bazel.git",
)

## `pybind11`
# https://github.com/pybind/pybind11
new_git_repository(
    name = "pybind11",
    build_file = "@pybind11_bazel//:pybind11-BUILD.bazel",
    commit = "a2e59f0e7065404b44dfe92a28aca47ba1378dc4",
    #tag = "v2.13.6",
    remote = "https://github.com/pybind/pybind11.git",
)

new_git_repository(
    name = "pybind11_abseil",
    commit = "70f8b693b3b70573ca785ef62d9f48054f45d786",
    #tag = "v202402.0",
    patches = ["//patches:pybind11_abseil.patch"],
    patch_args = ["-p1"],
    remote = "https://github.com/pybind/pybind11_abseil.git",
    repo_mapping = {"@com_google_absl": "@abseil-cpp"},
)

new_git_repository(
    name = "pybind11_protobuf",
    commit = "84653a591aea5df482dc2bde42c19efafbd53a57", # 2024/06/28
    remote = "https://github.com/pybind/pybind11_protobuf.git",
)

# Dependencies
## ZLIB
new_git_repository(
    name = "zlib",
    build_file = "@com_google_protobuf//:third_party/zlib.BUILD",
    commit = "51b7f2abdade71cd9bb0e7a373ef2610ec6f9daf",
    #tag = "v1.3.1",
    remote = "https://github.com/madler/zlib.git",
)

## Abseil-cpp
git_repository(
    name = "abseil-cpp",
    commit = "987c57f325f7fa8472fa84e1f885f7534d391b0d",
    #tag = "20250814.0",
    remote = "https://github.com/abseil/abseil-cpp.git",
)

## Re2
git_repository(
    name = "re2",
    commit = "6dcd83d60f7944926bfd308cc13979fc53dd69ca",
    #tag = "2024-07-02",
    remote = "https://github.com/google/re2.git",
    #repo_mapping = {"@abseil-cpp": "@com_google_absl"},
)

## Protobuf
# proto_library and cc_proto_library rules implicitly
# depend on @com_google_protobuf for protoc and proto runtimes.
git_repository(
    name = "com_google_protobuf",
    commit = "74211c0dfc2777318ab53c2cd2c317a2ef9012de",
    #tag = "v31.1",
    remote = "https://github.com/protocolbuffers/protobuf.git",
)
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()

# Testing
## Googletest
git_repository(
    name = "googletest",
    commit = "52eb8108c5bdec04579160ae17225d66034bd723",
    #tag = "v1.17.0",
    remote = "https://github.com/google/googletest.git",
)
