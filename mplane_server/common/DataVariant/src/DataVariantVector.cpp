/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantVector.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DataVariant/DataVariantVector.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantVector::isVectorComplete(const DataVariant& dv, std::string& error) {
  error = "";

  std::vector<std::pair<std::string, DataVariant>> list(dv.getList());
  for (auto pair : list) {
    if (!pair.second.isSet()) {
      error = "Value " + pair.first + " is unset";
      return false;
    }
  }

  return true;
}

//=============================================================================================================
// FROM DataVariant TO vector
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::vector<Frequency>
DataVariantVector::toFrequencyVector(
    const DataVariant& dv, std::string& error) {
  if (!isVectorComplete(dv, error))
    return std::vector<Frequency>();

  std::vector<Frequency> frequencyList;
  std::vector<std::pair<std::string, DataVariant>> list(dv.getList());
  for (auto pair : list) {
    Frequency freq(
        pair.second.toFloat(), Frequency::str2unit(pair.second.getUnits()));
    frequencyList.push_back(freq);
  }

  return frequencyList;
}
std::vector<Frequency>
DataVariantVector::toFrequencyVector(
    const DataVariant* dv, std::string& error) {
  return toFrequencyVector(*dv, error);
}

//-------------------------------------------------------------------------------------------------------------
std::vector<Power>
DataVariantVector::toPowerVector(const DataVariant& dv, std::string& error) {
  if (!isVectorComplete(dv, error))
    return std::vector<Power>();

  std::vector<Power> powerList;
  std::vector<std::pair<std::string, DataVariant>> list(dv.getList());
  for (auto pair : list) {
    Power power(pair.second.toFloat(), Power::str2unit(pair.second.getUnits()));
    powerList.push_back(power);
  }

  return powerList;
}
std::vector<Power>
DataVariantVector::toPowerVector(const DataVariant* dv, std::string& error) {
  return toPowerVector(*dv, error);
}

//-------------------------------------------------------------------------------------------------------------
std::vector<int>
DataVariantVector::toIntVector(const DataVariant& dv, std::string& error) {
  if (!isVectorComplete(dv, error))
    return std::vector<int>();

  std::vector<int> intList;
  std::vector<std::pair<std::string, DataVariant>> list(dv.getList());
  for (auto pair : list) {
    intList.push_back(pair.second.toInt());
  }

  return intList;
}
std::vector<int>
DataVariantVector::toIntVector(const DataVariant* dv, std::string& error) {
  return toIntVector(*dv, error);
}

//-------------------------------------------------------------------------------------------------------------
std::vector<float>
DataVariantVector::toFloatVector(const DataVariant& dv, std::string& error) {
  if (!isVectorComplete(dv, error))
    return std::vector<float>();

  std::vector<float> floatList;
  std::vector<std::pair<std::string, DataVariant>> list(dv.getList());
  for (auto pair : list) {
    floatList.push_back(pair.second.toFloat());
  }

  return floatList;
}
std::vector<float>
DataVariantVector::toFloatVector(const DataVariant* dv, std::string& error) {
  return toFloatVector(*dv, error);
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::complex<float>>
DataVariantVector::toComplexVector(const DataVariant& dv, std::string& error) {
  if (!isVectorComplete(dv, error))
    return std::vector<std::complex<float>>();

  std::vector<std::complex<float>> complexList;
  std::vector<std::pair<std::string, DataVariant>> list(dv.getList());
  for (auto pair : list) {
    complexList.push_back(pair.second.toComplex());
  }

  return complexList;
}
std::vector<std::complex<float>>
DataVariantVector::toComplexVector(const DataVariant* dv, std::string& error) {
  return toComplexVector(*dv, error);
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string>
DataVariantVector::toStringVector(const DataVariant& dv, std::string& error) {
  if (!isVectorComplete(dv, error))
    return std::vector<std::string>();

  std::vector<std::string> stringList;
  std::vector<std::pair<std::string, DataVariant>> list(dv.getList());
  for (auto pair : list) {
    stringList.push_back(pair.second.toString());
  }

  return stringList;
}
std::vector<std::string>
DataVariantVector::toStringVector(const DataVariant* dv, std::string& error) {
  return toStringVector(*dv, error);
}

//-------------------------------------------------------------------------------------------------------------
std::vector<bool>
DataVariantVector::toBoolVector(const DataVariant& dv, std::string& error) {
  if (!isVectorComplete(dv, error))
    return std::vector<bool>();

  std::vector<bool> boolList;
  std::vector<std::pair<std::string, DataVariant>> list(dv.getList());
  for (auto pair : list) {
    boolList.push_back(pair.second.toBool());
  }

  return boolList;
}
std::vector<bool>
DataVariantVector::toBoolVector(const DataVariant* dv, std::string& error) {
  return toBoolVector(*dv, error);
}

//-------------------------------------------------------------------------------------------------------------
std::vector<unsigned>
DataVariantVector::toUnsignedVector(const DataVariant& dv, std::string& error) {
  if (!isVectorComplete(dv, error))
    return std::vector<unsigned>();

  std::vector<unsigned> unsignedList;
  std::vector<std::pair<std::string, DataVariant>> list(dv.getList());
  for (auto pair : list) {
    unsignedList.push_back(static_cast<unsigned>(pair.second.toInt()));
  }

  return unsignedList;
}
std::vector<unsigned>
DataVariantVector::toUnsignedVector(const DataVariant* dv, std::string& error) {
  return toUnsignedVector(*dv, error);
}

//=============================================================================================================
// FROM DataVariant TO vector
//=============================================================================================================
namespace {

template <typename T>
bool
fromTypeVector(const std::vector<T>& vec, DataVariant& dv, std::string& error) {
  unsigned idx(0);
  for (auto val : vec) {
    dv.set(idx++, val);
  }
  return true;
}

template <>
bool
fromTypeVector(
    const std::vector<unsigned>& vec, DataVariant& dv, std::string& error) {
  unsigned idx(0);
  for (auto val : vec) {
    dv.set(idx++, static_cast<int>(val));
  }
  return true;
}

template <>
bool
fromTypeVector(
    const std::vector<Frequency>& vec, DataVariant& dv, std::string& error) {
  unsigned idx(0);
  for (auto val : vec) {
    dv.set(idx++, static_cast<float>(val.getDbl(Frequency::Hz)));
  }
  return true;
}

template <>
bool
fromTypeVector(
    const std::vector<Power>& vec, DataVariant& dv, std::string& error) {
  unsigned idx(0);
  for (auto val : vec) {
    dv.set(idx++, static_cast<float>(val.get()));
  }
  return true;
}

}; // namespace

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantVector::fromIntVector(
    const std::vector<int>& vec, DataVariant& dv, std::string& error) {
  return fromTypeVector(vec, dv, error);
}
bool
DataVariantVector::fromIntVector(
    const std::vector<int>& vec, DataVariant* dv, std::string& error) {
  return fromTypeVector(vec, *dv, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantVector::fromFloatVector(
    const std::vector<float>& vec, DataVariant& dv, std::string& error) {
  return fromTypeVector(vec, dv, error);
}
bool
DataVariantVector::fromFloatVector(
    const std::vector<float>& vec, DataVariant* dv, std::string& error) {
  return fromTypeVector(vec, *dv, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantVector::fromComplexVector(
    const std::vector<std::complex<float>>& vec,
    DataVariant& dv,
    std::string& error) {
  return fromTypeVector(vec, dv, error);
}
bool
DataVariantVector::fromComplexVector(
    const std::vector<std::complex<float>>& vec,
    DataVariant* dv,
    std::string& error) {
  return fromTypeVector(vec, *dv, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantVector::fromStringVector(
    const std::vector<std::string>& vec, DataVariant& dv, std::string& error) {
  return fromTypeVector(vec, dv, error);
}
bool
DataVariantVector::fromStringVector(
    const std::vector<std::string>& vec, DataVariant* dv, std::string& error) {
  return fromTypeVector(vec, *dv, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantVector::fromBoolVector(
    const std::vector<bool>& vec, DataVariant& dv, std::string& error) {
  return fromTypeVector(vec, dv, error);
}
bool
DataVariantVector::fromBoolVector(
    const std::vector<bool>& vec, DataVariant* dv, std::string& error) {
  return fromTypeVector(vec, *dv, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantVector::fromUnsignedVector(
    const std::vector<unsigned>& vec, DataVariant& dv, std::string& error) {
  return fromTypeVector(vec, dv, error);
}
bool
DataVariantVector::fromUnsignedVector(
    const std::vector<unsigned>& vec, DataVariant* dv, std::string& error) {
  return fromTypeVector(vec, *dv, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantVector::fromFrequencyVector(
    const std::vector<Frequency>& vec, DataVariant& dv, std::string& error) {
  return fromTypeVector(vec, dv, error);
}
bool
DataVariantVector::fromFrequencyVector(
    const std::vector<Frequency>& vec, DataVariant* dv, std::string& error) {
  return fromTypeVector(vec, *dv, error);
}

//-------------------------------------------------------------------------------------------------------------
bool
DataVariantVector::fromPowerVector(
    const std::vector<Power>& vec, DataVariant& dv, std::string& error) {
  return fromTypeVector(vec, dv, error);
}
bool
DataVariantVector::fromPowerVector(
    const std::vector<Power>& vec, DataVariant* dv, std::string& error) {
  return fromTypeVector(vec, *dv, error);
}
