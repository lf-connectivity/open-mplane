/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangUserAuth.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <map>

#include "YangParamUtils.h"
#include "XpathUtils.h"
#include "SysrepoUtils.h"

#include "YangUserAuth.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// convert from YANG string to libssh key type

// libssh:
//SSH_KEYTYPE_UNKNOWN=0,
//SSH_KEYTYPE_DSS=1,
//SSH_KEYTYPE_RSA,
//SSH_KEYTYPE_RSA1,
//SSH_KEYTYPE_ECDSA, /* deprecated */
//SSH_KEYTYPE_ED25519,
//SSH_KEYTYPE_DSS_CERT01,
//SSH_KEYTYPE_RSA_CERT01,
//SSH_KEYTYPE_ECDSA_P256,
//SSH_KEYTYPE_ECDSA_P384,
//SSH_KEYTYPE_ECDSA_P521,
//SSH_KEYTYPE_ECDSA_P256_CERT01,
//SSH_KEYTYPE_ECDSA_P384_CERT01,
//SSH_KEYTYPE_ECDSA_P521_CERT01,
//SSH_KEYTYPE_ED25519_CERT01,

// YANG:
//identity rsa1024 {
//    base asymmetric-key-algorithm;
//    description
//      "The RSA algorithm using a 1024-bit key.";
//    reference
//      "RFC 8017:
//         PKCS #1: RSA Cryptography Specifications Version 2.2.";
//  }
//
//  identity rsa2048 {
//    base asymmetric-key-algorithm;
//    description
//      "The RSA algorithm using a 2048-bit key.";
//    reference
//      "RFC 8017:
//         PKCS #1: RSA Cryptography Specifications Version 2.2.";
//  }
//
//  identity rsa3072 {
//    base asymmetric-key-algorithm;
//    description
//      "The RSA algorithm using a 3072-bit key.";
//    reference
//      "RFC 8017:
//         PKCS #1: RSA Cryptography Specifications Version 2.2.";
//  }
//
//  identity rsa4096 {
//    base asymmetric-key-algorithm;
//    description
//      "The RSA algorithm using a 4096-bit key.";
//    reference
//      "RFC 8017:
//         PKCS #1: RSA Cryptography Specifications Version 2.2.";
//  }
//
//  identity rsa7680 {
//    base asymmetric-key-algorithm;
//    description
//      "The RSA algorithm using a 7680-bit key.";
//    reference
//      "RFC 8017:
//         PKCS #1: RSA Cryptography Specifications Version 2.2.";
//  }
//
//  identity rsa15360 {
//    base asymmetric-key-algorithm;
//    description
//      "The RSA algorithm using a 15360-bit key.";
//    reference
//      "RFC 8017:
//         PKCS #1: RSA Cryptography Specifications Version 2.2.";
//  }
//
//  identity secp192r1 {
//    base asymmetric-key-algorithm;
//    description
//      "The ECDSA algorithm using a NIST P256 Curve.";
//    reference
//      "RFC 6090:
//         Fundamental Elliptic Curve Cryptography Algorithms.";
//  }
//  identity secp224r1 {
//    base asymmetric-key-algorithm;
//    description
//      "The ECDSA algorithm using a NIST P256 Curve.";
//    reference
//      "RFC 6090:
//         Fundamental Elliptic Curve Cryptography Algorithms.";
//  }
//
//  identity secp256r1 {
//    base asymmetric-key-algorithm;
//    description
//      "The ECDSA algorithm using a NIST P256 Curve.";
//    reference
//      "RFC 6090:
//         Fundamental Elliptic Curve Cryptography Algorithms.";
//  }
//
//  identity secp384r1 {
//    base asymmetric-key-algorithm;
//    description
//      "The ECDSA algorithm using a NIST P256 Curve.";
//    reference
//      "RFC 6090:
//         Fundamental Elliptic Curve Cryptography Algorithms.";
//  }
//
//  identity secp521r1 {
//    base asymmetric-key-algorithm;
//    description
//      "The ECDSA algorithm using a NIST P256 Curve.";
//    reference
//      "RFC 6090:
//         Fundamental Elliptic Curve Cryptography Algorithms.";
//  }

const std::map<std::string, ssh_keytypes_e> KEY_TYPES{
	{"rsa1024", 	SSH_KEYTYPE_RSA},
	{"rsa2048", 	SSH_KEYTYPE_RSA},
	{"rsa3072", 	SSH_KEYTYPE_RSA},
	{"rsa4096", 	SSH_KEYTYPE_RSA},
	{"rsa7680", 	SSH_KEYTYPE_RSA},
	{"rsa15360", 	SSH_KEYTYPE_RSA},

	{"secp192r1", 	SSH_KEYTYPE_ECDSA_P256},
	{"secp224r1", 	SSH_KEYTYPE_ECDSA_P256},
	{"secp256r1", 	SSH_KEYTYPE_ECDSA_P256},
	{"secp384r1", 	SSH_KEYTYPE_ECDSA_P256},
	{"secp521r1", 	SSH_KEYTYPE_ECDSA_P256},
} ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ssh_keytypes_e YangUserAuth::strToKeytype(const std::string &typeStr)
{
	if (KEY_TYPES.find(typeStr) == KEY_TYPES.end())
		return SSH_KEYTYPE_UNKNOWN ;

	return KEY_TYPES.at(typeStr) ;
}

//-------------------------------------------------------------------------------------------------------------
bool YangUserAuth::authParams(std::shared_ptr<YangParams> callList,
		std::string &authData, ISftpMgr::AuthenticationType &authType,
		std::vector<ISshSession::PublicKey> &serverKeys)
{
	authData.clear() ;
	authType = ISftpMgr::AUTH_NONE ;
	serverKeys.clear() ;

	std::map<std::string, std::shared_ptr<YangParam> > args(SysrepoUtils::paramsToMap(callList)) ;

	std::string error ;

//	for (auto entry : args)
//		std::cerr << "ARGS: " << entry.first << " = " << YangParamUtils::toString(entry.second, error) << std::endl ;

	if (args.find("password") != args.end())
	{
		authType = ISftpMgr::AUTH_PASSWORD ;
		authData = YangParamUtils::toString(args["password"], error) ;

		if (args.find("public-key") != args.end())
		{
			// need to look through the list of available key algorithms for any we support (only RSA at the moment!)
			std::vector<std::string> keyPaths ;
			for (unsigned i=0; i < callList->getNumParams(); ++i)
			{
				std::shared_ptr<YangParam> p(callList->getParam(i)) ;
				std::string leaf(XpathUtils::leafName(p->name())) ;
				if (leaf != "algorithm")
					continue ;

				ssh_keytypes_e type(strToKeytype(YangParamUtils::toString(p, error))) ;
				if (type == SSH_KEYTYPE_UNKNOWN)
					continue ;

				std::string pkeyPath( XpathUtils::leafPath(p->name()) + "/public-key") ;
				std::shared_ptr<YangParam> pkey(YangParamUtils::find(callList, pkeyPath)) ;
				if (!pkey)
					continue ;

				serverKeys.push_back(ISshSession::PublicKey(type, YangParamUtils::toString(pkey, error))) ;
			}
		}
	}
	else if (args.find("certificate") != args.end())
	{
		authType = ISftpMgr::AUTH_CERTIFICATE ;
		authData = YangParamUtils::toString(args["certificate"], error) ;
	}



	return true ;
}
