#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "absl/strings/string_view.h"
#include "absl/status/status.h"
#include "absl/time/time.h"
#include "bp11/foo/C.pb.h"

//! @namespace bp11 The `bp11` namespace
namespace bp11 {
//! @namespace foo The `foo` namespace
namespace foo {

//! @defgroup AbslFunction Abseil function usage.
//! @{
//! @brief Abseil function in foo namespace.
absl::Status abslFunction(absl::string_view string);

absl::Duration MakeDuration(double secs);
absl::Duration MakeInfiniteDuration();
bool IsInfiniteDuration(const absl::Duration& duration);
bool CheckDuration(const absl::Duration& duration, double secs);
absl::Time MakeTime(double secs);
bool CheckDatetime(const absl::Time& datetime, double secs);

//absl::Status ReturnStatus();
absl::Status ReturnStatus(absl::StatusCode code, absl::string_view text = "");
//! @}

//! @defgroup ProtoFunction Proto function usage.
//! @{
/*! @brief Proto function in foo namespace.
 * @param level Scope level.*/
::bp11::foo::C protoFunction(int level);
//! @}


//! @defgroup FreeFunction Free function usage.
//! @{
/*! @brief Free function in foo namespace.
 * @param level Scope level.*/
void freeFunction(int level);
/*! @brief Free function in foo namespace.
 * @param level Scope level.*/
void freeFunction(int64_t level);
//! @}

//! @defgroup StringVector Vector of String usage.
//! @{
/*! @brief Test returning a vector of string.
 * @param level Scope level.
 * @return A vector of string.*/
std::vector<std::string> stringVectorOutput(int level);
/*! @brief Test using a vector of string passed by value.
 * @param data Input data.
 * @return The size of the data vector.*/
int stringVectorInput(std::vector<std::string> data);
/*! @brief Test using a vector of string passed by const ref.
 * @param data Input data.
 * @return The size of the data vector.*/
int stringVectorRefInput(const std::vector<std::string>& data);
//! @}

//! @defgroup StringJaggedArray Vector of Vector of String usage.
//! @{
/*! @brief Test returning a jagged array of string.
 * @param level Scope level.
 * @return A jagged array of string.*/
std::vector<std::vector<std::string>> stringJaggedArrayOutput(int level);
/*! @brief Test using a jagged array of string passed by value.
 * @param data Input data.
 * @return The size of the data outer vector.*/
int stringJaggedArrayInput(std::vector<std::vector<std::string>> data);
/*! @brief Test using a jagged array of string passed by const ref.
 * @param data Input data.
 * @return The size of the data outer vector.*/
int stringJaggedArrayRefInput(const std::vector<std::vector<std::string>>& data);
//! @}

//! @defgroup PairVector Vector of Pair usage.
//! @{
/*! @brief Test returning a vector of pair.
 * @param level Scope level.
 * @return A vector of pair.*/
std::vector<std::pair<int, int>> pairVectorOutput(int level);
/*! @brief Test using a vector of pair passed by value.
 * @param data Input data.
 * @return The size of the data vector.*/
int pairVectorInput(std::vector<std::pair<int, int>> data);
/*! @brief Test using a vector of pair passed by const ref.
 * @param data Input data.
 * @return The size of the data vector.*/
int pairVectorRefInput(const std::vector<std::pair<int, int>>& data);
//! @}

//! @defgroup PairJaggedArray Jagged array of Pair<int, int> usage.
//! @{
/*! @brief Test returning a jagged array of pair.
 * @param level Scope level.
 * @return A jagged array of pair.*/
std::vector<std::vector<std::pair<int, int>>> pairJaggedArrayOutput(int level);
/*! @brief Test using a jagged array of pair passed by value.
 * @param data Input data.
 * @return The size of the data outer vector.*/
int pairJaggedArrayInput(std::vector<std::vector<std::pair<int, int>>> data);
/*! @brief Test using a jagged of pair passed by const ref.
 * @param data Input data.
 * @return The size of the data outer vector.*/
int pairJaggedArrayRefInput(const std::vector<std::vector<std::pair<int, int>>>& data);
//! @}

//! @brief Class Foo.
class Foo {
 public:
  //! @defgroup StaticMembers Static members
  //! @{

  /*! @brief Static method of Foo class.
   * @param[in] level Scope level.*/
  static void staticFunction(int level);

  /*! @brief Static method of Foo class.
   * @param[in] level Scope level.*/
  static void staticFunction(int64_t level);

  //! @}

  //! @defgroup IntegerMembers Integer members
  //! @{

  /*! @brief Method (getter) of Foo class.
   * @return A member value.*/
  int getInt() const;
  /*! @brief Method (setter) of Foo class.
   * @param[in] input A member value.*/
  void setInt(int input);

  //! @}

  //! @defgroup Int64Members Long Integer members
  //! @{

  /*! @brief Method (getter) of Foo class.
   * @return A member value.*/
  int64_t getInt64() const;
  /*! @brief Method (setter) of Foo class.
   * @param[in] input A member value.*/
  void setInt64(int64_t input);

  //! @}

  //! @brief Print object for debug.
  std::string operator()() const;

 private:
  int     _intValue   = 0;
  int64_t _int64Value = 0;
};
} // namespace foo
} // namespace bp11
