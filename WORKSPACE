workspace(name = "mizux_bpp11_protobuf")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

################################################################################
#
# WORKSPACE is being deprecated in favor of the new Bzlmod dependency system.
# It will be removed at some point in the future.
#
################################################################################

## `bazel_skylib`
# Needed for Abseil.
git_repository(
    name = "bazel_skylib",
    #commit = "27d429d8d036af3d010be837cc5924de1ca8d163",
    tag = "1.8.1",
    remote = "https://github.com/bazelbuild/bazel-skylib.git",
)
load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
bazel_skylib_workspace()

# Needed by rules_java
git_repository(
    name = "bazel_features",
    commit = "3f23ff44ff85416d96566bee8e407694cdb6f1f8",
    #tag = "v1.32.0",
    remote = "https://github.com/bazel-contrib/bazel_features.git",
)
load("@bazel_features//:deps.bzl", "bazel_features_deps")
bazel_features_deps()

## Bazel rules...
git_repository(
    name = "platforms",
    #commit = "05ec3a3df23fde62471f8288e344cc021dd87bab",
    tag = "1.0.0",
    remote = "https://github.com/bazelbuild/platforms.git",
)

git_repository(
    name = "rules_cc",
    tag = "0.1.4",
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


load("@bazel_features//:deps.bzl", "bazel_features_deps")
bazel_features_deps()

git_repository(
    name = "rules_proto",
    tag = "7.1.0",
    remote = "https://github.com/bazelbuild/rules_proto.git",
)

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies")
rules_proto_dependencies()

load("@rules_proto//proto:toolchains.bzl", "rules_proto_toolchains")
rules_proto_toolchains()

git_repository(
    name = "rules_python",
    #commit = "1944874f6ba507f70d8c5e70df84622e0c783254",
    #tag = "0.40.0",
    tag = "1.5.1",
    remote = "https://github.com/bazelbuild/rules_python.git",
)

# Dependencies
## ZLIB
new_git_repository(
    name = "zlib",
    build_file = "@protobuf//:third_party/zlib.BUILD",
    commit = "51b7f2abdade71cd9bb0e7a373ef2610ec6f9daf",
    #tag = "v1.3.1",
    remote = "https://github.com/madler/zlib.git",
)

## Abseil-cpp
git_repository(
    name = "abseil-cpp",
    #commit = "4447c7562e3bc702ade25105912dce503f0c4010",
    #tag = "20240722.0",
    commit = "bc257a88f7c1939f24e0379f14a3589e926c950c",
    #tag = "20250512.0",
    remote = "https://github.com/abseil/abseil-cpp.git",
)

## Re2
git_repository(
    name = "com_google_re2",
    tag = "2024-07-02",
    remote = "https://github.com/google/re2.git",
    #repo_mapping = {"@abseil-cpp": "@com_google_absl"},
)

## Protobuf
# proto_library and cc_proto_library rules implicitly
# depend on @protobuf for protoc and proto runtimes.
# This statement defines the @protobuf repo.
git_repository(
    name = "protobuf",
    #patches = ["//patches:protobuf-v29.2.patch"],
    #patch_args = ["-p1"],
    tag = "v31.1",
    remote = "https://github.com/protocolbuffers/protobuf.git",
)

# Load common dependencies.
load("@protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()

## Python
load("@rules_python//python:repositories.bzl", "py_repositories")
py_repositories()


load("@rules_python//python:repositories.bzl", "python_register_toolchains")

python_register_toolchains(
    name = "python_3_11",
    # Available versions are listed in @rules_python//python:versions.bzl.
    # We recommend using the same version your team is already standardized on.
    python_version = "3.11",
)

load("@rules_python//python:pip.bzl", "pip_parse")

pip_parse(
    name = "pypi",
    python_interpreter_target = "@python_3_11_host//:python",
    requirements_lock = "//bazel:requirements_lock_3_11.txt",
)

## `pybind11_bazel`
git_repository(
    name = "pybind11_bazel",
    commit = "2b6082a4d9d163a52299718113fa41e4b7978db5",
    #tag = "v2.13.6", # 2024/10/21
    remote = "https://github.com/pybind/pybind11_bazel.git",
)

new_git_repository(
    name = "pybind11",
    build_file = "@pybind11_bazel//:pybind11-BUILD.bazel",
    commit = "a2e59f0e7065404b44dfe92a28aca47ba1378dc4",
    #tag = "v2.13.6",
    remote = "https://github.com/pybind/pybind11.git",
)

new_git_repository(
    name = "pybind11_abseil",
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
    name = "googletest",
    commit = "52eb8108c5bdec04579160ae17225d66034bd723",
    #tag = "v1.17.0",
    remote = "https://github.com/google/googletest.git",
)
