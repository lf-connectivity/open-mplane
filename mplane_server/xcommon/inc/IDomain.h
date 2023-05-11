/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDomain.h
 * \brief
 *
 *
 */

#ifndef INC_IDOMAIN_H_
#define INC_IDOMAIN_H_

#include <string>

namespace Mplane {

/*!
 * \class  IDomain
 * \brief
 * \details
 *
 */
class IDomain {
 public:
  enum SignalDomain {
    NULL_DOMAIN,
    TIME_DOMAIN,
    FREQ_DOMAIN,
  };

  /**
   * Convert domain to string
   */
  static std::string domainStr(SignalDomain domain);
};

} // namespace Mplane

#endif /* INC_IDOMAIN_H_ */
