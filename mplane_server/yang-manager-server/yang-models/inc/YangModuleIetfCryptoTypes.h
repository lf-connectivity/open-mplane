#ifndef _MODULE_IETF_CRYPTO_TYPES_H_
#define _MODULE_IETF_CRYPTO_TYPES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfCryptoTypes.h
 * \brief     Module IetfCryptoTypes interface
 *
 *
 * \details   This file defines the YANG module ietf-crypto-types interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-crypto-types"
 *            YANG Filename:    "ietf-crypto-types.yang"
 *            Module Prefix:    "ct"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:ietf-crypto-types"
 *
 * Add user description here
 *
 * %%->

 * <-%%
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

// -----------------------------------------------------------------------------
// Common
// -----------------------------------------------------------------------------

#include "YangModule.h"

// -----------------------------------------------------------------------------
// External Modules
// -----------------------------------------------------------------------------

// Module:   ietf-yang-types
// Revision:
// Notes:
#include "YangModuleIetfYangTypes.h"

// Module:   ietf-netconf-acm
// Revision:
// Notes:
#include "YangModuleIetfNetconfAcm.h"


namespace Mplane {

namespace ModuleIetfCryptoTypes_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************


// *****************************************************************************
// Features
// *****************************************************************************

// *****************************************************************************
// Leafs
// *****************************************************************************

// *****************************************************************************
// References
// *****************************************************************************

// *****************************************************************************
// Containers
// *****************************************************************************

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /public-key-grouping
// Description: A public key.
//
//              The 'algorithm' and 'public-key' nodes are not
//              mandatory because they MAY be defined in <operational>.
//              Implementations SHOULD assert that these values are
//              either configured or that they exist in <operational>.
// -----------------------------------------------------------------------------
class GrpPublicKeyGrouping : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ALGORITHM, // LeafAlgorithm
   ITEM_PUBLIC_KEY, // LeafPublicKey
 };

 GrpPublicKeyGrouping(uint32_t id);
 ~GrpPublicKeyGrouping();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /public-key-grouping/algorithm
 // Description: Identifies the key's algorithm.  More specifically,
 //              this leaf specifies how the 'public-key' binary leaf
 //              is encoded.
 // -----------------------------------------------------------------------------
 class LeafAlgorithm : public YangLeaf {
  public:
   LeafAlgorithm(uint32_t id);
   ~LeafAlgorithm();

 }; // LeafAlgorithm

 // -----------------------------------------------------------------------------
 // Leaf:        /public-key-grouping/public-key
 // Description: A binary that contains the value of the public key.  The
 //              interpretation of the content is defined by the key
 //              algorithm.  For example, a DSA key is an integer, an RSA
 //              key is represented as RSAPublicKey as defined in
 //              RFC 8017, and an Elliptic Curve Cryptography (ECC) key
 //              is represented using the 'publicKey' described in
 //              RFC 5915.
 // -----------------------------------------------------------------------------
 class LeafPublicKey : public YangLeaf {
  public:
   LeafPublicKey(uint32_t id);
   ~LeafPublicKey();

 }; // LeafPublicKey

}; // GrpPublicKeyGrouping

// -----------------------------------------------------------------------------
// Grouping:    /asymmetric-key-pair-grouping
// Description: A private/public key pair.
//              The 'algorithm', 'public-key', and 'private-key'  nodes are
//              not mandatory because they MAY be defined in <operational>.
//              Implementations SHOULD assert that these values are either
//              configured or that they exist in <operational>.
// -----------------------------------------------------------------------------
class GrpAsymmetricKeyPairGrouping : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_PRIVATE_KEY, // LeafPrivateKey
   ITEM_PUBLIC_KEY_GROUPING, // Use GrpPublicKeyGrouping
 };

 GrpAsymmetricKeyPairGrouping(uint32_t id);
 ~GrpAsymmetricKeyPairGrouping();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /asymmetric-key-pair-grouping/private-key
 // Description: A binary that contains the value of the private key.  The
 //              interpretation of the content is defined by the key
 //              algorithm.  For example, a DSA key is an integer, an RSA
 //              key is represented as RSAPrivateKey as defined in
 //              RFC 8017, and an Elliptic Curve Cryptography (ECC) key
 //              is represented as ECPrivateKey as defined in RFC 5915.
 // -----------------------------------------------------------------------------
 class LeafPrivateKey : public YangLeaf {
  public:
   LeafPrivateKey(uint32_t id);
   ~LeafPrivateKey();

 }; // LeafPrivateKey

}; // GrpAsymmetricKeyPairGrouping

// -----------------------------------------------------------------------------
// Grouping:    /trust-anchor-cert-grouping
// Description: A trust anchor certificate, and a notification for when
//              it is about to (or already has) expire.
// -----------------------------------------------------------------------------
class GrpTrustAnchorCertGrouping : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_CERT, // LeafCert
   ITEM_CERTIFICATE_EXPIRATION, // NotifCertificateExpiration
 };

 GrpTrustAnchorCertGrouping(uint32_t id);
 ~GrpTrustAnchorCertGrouping();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /trust-anchor-cert-grouping/cert
 // Description: The binary certificate data for this certificate.
 // -----------------------------------------------------------------------------
 class LeafCert : public YangLeaf {
  public:
   LeafCert(uint32_t id);
   ~LeafCert();

 }; // LeafCert

 // -----------------------------------------------------------------------------
 // Notification:/trust-anchor-cert-grouping/certificate-expiration
 // Description: A notification indicating that the configured certificate
 //              is either about to expire or has already expired.  When to
 //              send notifications is an implementation specific decision,
 //              but it is RECOMMENDED that a notification be sent once a
 //              month for 3 months, then once a week for four weeks, and
 //              then once a day thereafter until the issue is resolved.
 // -----------------------------------------------------------------------------
 class NotifCertificateExpiration : public YangNotif {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_EXPIRATION_DATE, // LeafExpirationDate
   };

   NotifCertificateExpiration(uint32_t id);
   ~NotifCertificateExpiration();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf: /trust-anchor-cert-grouping/certificate-expiration/expiration-date
   // Description: Identifies the expiration date on the certificate.
   // -----------------------------------------------------------------------------
   class LeafExpirationDate : public YangLeaf {
    public:
     LeafExpirationDate(uint32_t id);
     ~LeafExpirationDate();

   }; // LeafExpirationDate

 }; // NotifCertificateExpiration

}; // GrpTrustAnchorCertGrouping

// -----------------------------------------------------------------------------
// Grouping:    /trust-anchor-certs-grouping
// Description: A list of trust anchor certificates, and a notification
//              for when one is about to (or already has) expire.
// -----------------------------------------------------------------------------
class GrpTrustAnchorCertsGrouping : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_CERT, // LstCert
   ITEM_CERTIFICATE_EXPIRATION, // NotifCertificateExpiration
 };

 GrpTrustAnchorCertsGrouping(uint32_t id);
 ~GrpTrustAnchorCertsGrouping();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // List:        /trust-anchor-certs-grouping/cert
 // Description: The binary certificate data for this certificate.
 // -----------------------------------------------------------------------------
 class LstCert : public YangList {
  public:
   // Item IDs
   enum : uint32_t {};

   LstCert(uint32_t id);
   ~LstCert();

   YangResult_E initialise(void);

 }; // LstCert

 // -----------------------------------------------------------------------------
 // Notification:/trust-anchor-certs-grouping/certificate-expiration
 // Description: A notification indicating that the configured certificate
 //              is either about to expire or has already expired.  When to
 //              send notifications is an implementation specific decision,
 //              but it is RECOMMENDED that a notification be sent once a
 //              month for 3 months, then once a week for four weeks, and
 //              then once a day thereafter until the issue is resolved.
 // -----------------------------------------------------------------------------
 class NotifCertificateExpiration : public YangNotif {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_EXPIRATION_DATE, // LeafExpirationDate
   };

   NotifCertificateExpiration(uint32_t id);
   ~NotifCertificateExpiration();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf: /trust-anchor-certs-grouping/certificate-expiration/expiration-date
   // Description: Identifies the expiration date on the certificate.
   // -----------------------------------------------------------------------------
   class LeafExpirationDate : public YangLeaf {
    public:
     LeafExpirationDate(uint32_t id);
     ~LeafExpirationDate();

   }; // LeafExpirationDate

 }; // NotifCertificateExpiration

}; // GrpTrustAnchorCertsGrouping

// -----------------------------------------------------------------------------
// Grouping:    /end-entity-cert-grouping
// Description: An end entity certificate, and a notification for when
//              it is about to (or already has) expire.
// -----------------------------------------------------------------------------
class GrpEndEntityCertGrouping : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_CERT, // LeafCert
   ITEM_CERTIFICATE_EXPIRATION, // NotifCertificateExpiration
 };

 GrpEndEntityCertGrouping(uint32_t id);
 ~GrpEndEntityCertGrouping();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /end-entity-cert-grouping/cert
 // Description: The binary certificate data for this certificate.
 // -----------------------------------------------------------------------------
 class LeafCert : public YangLeaf {
  public:
   LeafCert(uint32_t id);
   ~LeafCert();

 }; // LeafCert

 // -----------------------------------------------------------------------------
 // Notification:/end-entity-cert-grouping/certificate-expiration
 // Description: A notification indicating that the configured certificate
 //              is either about to expire or has already expired.  When to
 //              send notifications is an implementation specific decision,
 //              but it is RECOMMENDED that a notification be sent once a
 //              month for 3 months, then once a week for four weeks, and
 //              then once a day thereafter until the issue is resolved.
 // -----------------------------------------------------------------------------
 class NotifCertificateExpiration : public YangNotif {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_EXPIRATION_DATE, // LeafExpirationDate
   };

   NotifCertificateExpiration(uint32_t id);
   ~NotifCertificateExpiration();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf: /end-entity-cert-grouping/certificate-expiration/expiration-date
   // Description: Identifies the expiration date on the certificate.
   // -----------------------------------------------------------------------------
   class LeafExpirationDate : public YangLeaf {
    public:
     LeafExpirationDate(uint32_t id);
     ~LeafExpirationDate();

   }; // LeafExpirationDate

 }; // NotifCertificateExpiration

}; // GrpEndEntityCertGrouping

// -----------------------------------------------------------------------------
// Grouping:    /end-entity-certs-grouping
// Description: A list of end entity certificates, and a notification for
//              when one is about to (or already has) expire.
// -----------------------------------------------------------------------------
class GrpEndEntityCertsGrouping : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_CERT, // LstCert
   ITEM_CERTIFICATE_EXPIRATION, // NotifCertificateExpiration
 };

 GrpEndEntityCertsGrouping(uint32_t id);
 ~GrpEndEntityCertsGrouping();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // List:        /end-entity-certs-grouping/cert
 // Description: The binary certificate data for this certificate.
 // -----------------------------------------------------------------------------
 class LstCert : public YangList {
  public:
   // Item IDs
   enum : uint32_t {};

   LstCert(uint32_t id);
   ~LstCert();

   YangResult_E initialise(void);

 }; // LstCert

 // -----------------------------------------------------------------------------
 // Notification:/end-entity-certs-grouping/certificate-expiration
 // Description: A notification indicating that the configured certificate
 //              is either about to expire or has already expired.  When to
 //              send notifications is an implementation specific decision,
 //              but it is RECOMMENDED that a notification be sent once a
 //              month for 3 months, then once a week for four weeks, and
 //              then once a day thereafter until the issue is resolved.
 // -----------------------------------------------------------------------------
 class NotifCertificateExpiration : public YangNotif {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_EXPIRATION_DATE, // LeafExpirationDate
   };

   NotifCertificateExpiration(uint32_t id);
   ~NotifCertificateExpiration();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf: /end-entity-certs-grouping/certificate-expiration/expiration-date
   // Description: Identifies the expiration date on the certificate.
   // -----------------------------------------------------------------------------
   class LeafExpirationDate : public YangLeaf {
    public:
     LeafExpirationDate(uint32_t id);
     ~LeafExpirationDate();

   }; // LeafExpirationDate

 }; // NotifCertificateExpiration

}; // GrpEndEntityCertsGrouping

// -----------------------------------------------------------------------------
// Grouping:    /asymmetric-key-pair-with-cert-grouping
// Description: A private/public key pair and an associated certificate.
// -----------------------------------------------------------------------------
class GrpAsymmetricKeyPairWithCertGrouping : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ASYMMETRIC_KEY_PAIR_GROUPING, // Use GrpAsymmetricKeyPairGrouping
   ITEM_END_ENTITY_CERT_GROUPING, // Use GrpEndEntityCertGrouping
 };

 GrpAsymmetricKeyPairWithCertGrouping(uint32_t id);
 ~GrpAsymmetricKeyPairWithCertGrouping();

 YangResult_E initialise(void);

}; // GrpAsymmetricKeyPairWithCertGrouping

// -----------------------------------------------------------------------------
// Grouping:    /asymmetric-key-pair-with-certs-grouping
// Description: A private/public key pair and associated certificates.
// -----------------------------------------------------------------------------
class GrpAsymmetricKeyPairWithCertsGrouping : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_CERTIFICATES, // CntCertificates
   ITEM_ASYMMETRIC_KEY_PAIR_GROUPING, // Use GrpAsymmetricKeyPairGrouping
 };

 GrpAsymmetricKeyPairWithCertsGrouping(uint32_t id);
 ~GrpAsymmetricKeyPairWithCertsGrouping();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Container:   /asymmetric-key-pair-with-certs-grouping/certificates
 // Description: Certificates associated with this asymmetric key.
 //              More than one certificate supports, for instance,
 //              a TPM-protected asymmetric key that has both IDevID
 //              and LDevID certificates associated.
 // -----------------------------------------------------------------------------
 class CntCertificates : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_CERTIFICATE, // LstCertificate
   };

   CntCertificates(uint32_t id);
   ~CntCertificates();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // List: /asymmetric-key-pair-with-certs-grouping/certificates/certificate
   // Description: A certificate for this asymmetric key.
   // -----------------------------------------------------------------------------
   class LstCertificate : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_NAME, // LeafName
       ITEM_END_ENTITY_CERT_GROUPING, // Use GrpEndEntityCertGrouping
     };

     LstCertificate(uint32_t id);
     ~LstCertificate();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /asymmetric-key-pair-with-certs-grouping/certificates/certificate/name
     // Description: An arbitrary name for the certificate.  If the name
     //              matches the name of a certificate that exists
     //              independently in <operational> (i.e., an IDevID),
     //              then the 'cert' node MUST NOT be configured.
     // -----------------------------------------------------------------------------
     class LeafName : public YangLeaf {
      public:
       LeafName(uint32_t id);
       ~LeafName();

     }; // LeafName

   }; // LstCertificate

 }; // CntCertificates

}; // GrpAsymmetricKeyPairWithCertsGrouping


// *****************************************************************************
// Lists
// *****************************************************************************

// *****************************************************************************
// Choices
// *****************************************************************************

// *****************************************************************************
// Notifications
// *****************************************************************************

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      ietf-crypto-types
// Description: This module defines common YANG types for cryptographic
//              applications.
//
//              Copyright (c) 2019 IETF Trust and the persons identified
//              as authors of the code. All rights reserved.
//
//              Redistribution and use in source and binary forms, with
//              or without modification, is permitted pursuant to, and
//              subject to the license terms contained in, the Simplified
//              BSD License set forth in Section 4.c of the IETF Trust's
//              Legal Provisions Relating to IETF Documents
//              (https://trustee.ietf.org/license-info).
//
//              This version of this YANG module is part of RFC XXXX
//              (https://www.rfc-editor.org/info/rfcXXXX); see the RFC
//              itself for full legal notices.;
//
//              The key words 'MUST', 'MUST NOT', 'REQUIRED', 'SHALL',
//              'SHALL NOT', 'SHOULD', 'SHOULD NOT', 'RECOMMENDED',
//              'NOT RECOMMENDED', 'MAY', and 'OPTIONAL' in this document
//              are to be interpreted as described in BCP 14 (RFC 2119)
//              (RFC 8174) when, and only when, they appear in all
//              capitals, as shown here.
// -----------------------------------------------------------------------------
class ModuleIetfCryptoTypes : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {};

 ModuleIetfCryptoTypes(uint32_t id);
 ~ModuleIetfCryptoTypes();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleIetfCryptoTypes_NS */

} /* namespace Mplane */

#endif /* _MODULE_IETF_CRYPTO_TYPES_H_ */
