include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_TESTING OFF)
set(CMAKE_Fortran_COMPILER OFF)

# ##############################################################################
# ZLIB
# ##############################################################################
if(BUILD_ZLIB)
  message(CHECK_START "Fetching ZLIB")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  set(ZLIB_BUILD_EXAMPLES OFF)
  FetchContent_Declare(
    ZLIB
    GIT_REPOSITORY "https://github.com/madler/ZLIB.git"
    GIT_TAG "v1.3.1"
    PATCH_COMMAND git apply --ignore-whitespace
    "${CMAKE_CURRENT_LIST_DIR}/../../patches/ZLIB-v1.3.1.patch")
  FetchContent_MakeAvailable(ZLIB)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# ABSEIL-CPP
# ##############################################################################
if(BUILD_absl)
  message(CHECK_START "Fetching Abseil-cpp")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  set(ABSL_ENABLE_INSTALL ON)
  set(ABSL_USE_SYSTEM_INCLUDES ON)
  set(ABSL_PROPAGATE_CXX_STD ON)
  set(ABSL_BUILD_TESTING OFF)
  FetchContent_Declare(
    absl
    GIT_REPOSITORY "https://github.com/abseil/abseil-cpp.git"
    GIT_TAG "20240722.0"
    GIT_SHALLOW TRUE
    PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/../../patches/abseil-cpp-20240722.0.patch"
  )
  FetchContent_MakeAvailable(absl)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# Protobuf
# ##############################################################################
if(BUILD_Protobuf)
  message(CHECK_START "Fetching Protobuf")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  set(protobuf_BUILD_TESTS OFF)
  set(protobuf_BUILD_SHARED_LIBS ON)
  set(protobuf_BUILD_EXPORT OFF)
  set(protobuf_MSVC_STATIC_RUNTIME OFF)
  #set(protobuf_BUILD_LIBUPB ON)
  FetchContent_Declare(
    Protobuf
    GIT_REPOSITORY "https://github.com/protocolbuffers/protobuf.git"
    GIT_TAG "v29.2"
    GIT_SHALLOW TRUE
    GIT_SUBMODULES ""
    PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/../../patches/protobuf-v29.2.patch"
  )
  FetchContent_MakeAvailable(Protobuf)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# RE2
# ##############################################################################
if(BUILD_re2)
  message(CHECK_START "Fetching re2")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  set(RE2_BUILD_TESTING OFF)
  FetchContent_Declare(
    re2
    GIT_REPOSITORY "https://github.com/google/re2.git"
    GIT_TAG "2024-04-01"
    GIT_SHALLOW TRUE
    PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/../../patches/re2-2024-04-01.patch"
  )
  FetchContent_MakeAvailable(re2)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# pybind11
# ##############################################################################
# Find Python 3
find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)


if(BUILD_pybind11)
  message(CHECK_START "Fetching pybind11")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  set(PYBIND11_FINDPYTHON ON)
  set(PYBIND11_INSTALL ON)
  set(PYBIND11_TEST OFF)
  FetchContent_Declare(
    pybind11
    GIT_REPOSITORY "https://github.com/pybind/pybind11.git"
    GIT_TAG "v2.13.1"
    GIT_SHALLOW TRUE
    PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/../../patches/pybind11.patch"
  )
  FetchContent_MakeAvailable(pybind11)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

if(BUILD_pybind11_abseil)
  message(CHECK_START "Fetching pybind11_abseil")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  FetchContent_Declare(
    pybind11_abseil
    GIT_REPOSITORY "https://github.com/pybind/pybind11_abseil.git" # 2024/01/11
    GIT_TAG "v202402.0"
    GIT_SHALLOW TRUE
    PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/../../patches/pybind11_abseil.patch"
  )
  FetchContent_MakeAvailable(pybind11_abseil)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# Pybind11 Protobuf
# ##############################################################################
if(BUILD_pybind11_protobuf)
  message(CHECK_START "Fetching pybind11_protobuf")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  FetchContent_Declare(
    pybind11_protobuf
    GIT_REPOSITORY "https://github.com/pybind/pybind11_protobuf.git"
    GIT_TAG "84653a591aea5df482dc2bde42c19efafbd53a57" # 2024/06/28
    PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/../../patches/pybind11_protobuf.patch"
    #GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(pybind11_protobuf)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

###############
##  TESTING  ##
###############
if(BUILD_googletest)
  message(CHECK_START "Fetching googletest")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    GIT_SHALLOW TRUE
    PATCH_COMMAND git apply --ignore-whitespace
    "${CMAKE_CURRENT_LIST_DIR}/../../patches/googletest-v1.15.2.patch"
    #PATCH_COMMAND git apply --ignore-whitespace ""
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  set(INSTALL_GTEST OFF)
  set(GTEST_HAS_ABSL ON)
  if(WIN32)
    set(BUILD_SHARED_LIBS OFF)
  endif()
  FetchContent_MakeAvailable(googletest)
  if(WIN32)
    set(BUILD_SHARED_LIBS ON)
  endif()

  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()
