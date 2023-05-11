/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfCryptoTypes.cpp
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
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleIetfCryptoTypes.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleIetfCryptoTypes_NS;

// Add user code here
// %%->

// <-%%

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
// Grouping:    public-key-grouping
// Description: A public key.
//
//              The 'algorithm' and 'public-key' nodes are not
//              mandatory because they MAY be defined in <operational>.
//              Implementations SHOULD assert that these values are
//              either configured or that they exist in <operational>.
// -----------------------------------------------------------------------------
GrpPublicKeyGrouping::GrpPublicKeyGrouping(uint32_t id)
	: YangGroup("public-key-grouping", id)
{
}

GrpPublicKeyGrouping::~GrpPublicKeyGrouping()
{
}

YangResult_E GrpPublicKeyGrouping::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /public-key-grouping/algorithm
	// Description: Identifies the key's algorithm.  More specifically,
	//              this leaf specifies how the 'public-key' binary leaf
	//              is encoded.
	// Type:        ???IDENT
	// Units:
	// -----------------------------------------------------------------------------
	LeafAlgorithm algorithmInst(ITEM_ALGORITHM);
	addLeaf(algorithmInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /public-key-grouping/public-key
	// Description: A binary that contains the value of the public key.  The
	//              interpretation of the content is defined by the key
	//              algorithm.  For example, a DSA key is an integer, an RSA
	//              key is represented as RSAPublicKey as defined in
	//              RFC 8017, and an Elliptic Curve Cryptography (ECC) key
	//              is represented using the 'publicKey' described in
	//              RFC 5915.
	// Type:        ???BINARY
	// Units:
	// -----------------------------------------------------------------------------
	LeafPublicKey publicKeyInst(ITEM_PUBLIC_KEY);
	addLeaf(publicKeyInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /public-key-grouping/algorithm
// Description: Identifies the key's algorithm.  More specifically,
//              this leaf specifies how the 'public-key' binary leaf
//              is encoded.
// -----------------------------------------------------------------------------
GrpPublicKeyGrouping::LeafAlgorithm::LeafAlgorithm(uint32_t id)
	: YangLeaf("algorithm", id)
{
}

GrpPublicKeyGrouping::LeafAlgorithm::~LeafAlgorithm()
{
}

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
GrpPublicKeyGrouping::LeafPublicKey::LeafPublicKey(uint32_t id)
	: YangLeaf("public-key", id)
{
}

GrpPublicKeyGrouping::LeafPublicKey::~LeafPublicKey()
{
}



// -----------------------------------------------------------------------------
// Grouping:    asymmetric-key-pair-grouping
// Description: A private/public key pair.
//              The 'algorithm', 'public-key', and 'private-key'  nodes are
//              not mandatory because they MAY be defined in <operational>.
//              Implementations SHOULD assert that these values are either
//              configured or that they exist in <operational>.
// -----------------------------------------------------------------------------
GrpAsymmetricKeyPairGrouping::GrpAsymmetricKeyPairGrouping(uint32_t id)
	: YangGroup("asymmetric-key-pair-grouping", id)
{
}

GrpAsymmetricKeyPairGrouping::~GrpAsymmetricKeyPairGrouping()
{
}

YangResult_E GrpAsymmetricKeyPairGrouping::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /asymmetric-key-pair-grouping/private-key
	// Description: A binary that contains the value of the private key.  The
	//              interpretation of the content is defined by the key
	//              algorithm.  For example, a DSA key is an integer, an RSA
	//              key is represented as RSAPrivateKey as defined in
	//              RFC 8017, and an Elliptic Curve Cryptography (ECC) key
	//              is represented as ECPrivateKey as defined in RFC 5915.
	// Type:        ???UNION
	// Units:
	// -----------------------------------------------------------------------------
	LeafPrivateKey privateKeyInst(ITEM_PRIVATE_KEY);
	addLeaf(privateKeyInst);

	// -----------------------------------------------------------------------------
	// Uses:        /asymmetric-key-pair-grouping/public-key-grouping
	// Description:
	// -----------------------------------------------------------------------------
	GrpPublicKeyGrouping publicKeyGroupingInst(ITEM_PUBLIC_KEY_GROUPING);
	publicKeyGroupingInst.initialise();
	addGroup(publicKeyGroupingInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /asymmetric-key-pair-grouping/private-key
// Description: A binary that contains the value of the private key.  The
//              interpretation of the content is defined by the key
//              algorithm.  For example, a DSA key is an integer, an RSA
//              key is represented as RSAPrivateKey as defined in
//              RFC 8017, and an Elliptic Curve Cryptography (ECC) key
//              is represented as ECPrivateKey as defined in RFC 5915.
// -----------------------------------------------------------------------------
GrpAsymmetricKeyPairGrouping::LeafPrivateKey::LeafPrivateKey(uint32_t id)
	: YangLeaf("private-key", id)
{
}

GrpAsymmetricKeyPairGrouping::LeafPrivateKey::~LeafPrivateKey()
{
}



// -----------------------------------------------------------------------------
// Grouping:    trust-anchor-cert-grouping
// Description: A trust anchor certificate, and a notification for when
//              it is about to (or already has) expire.
// -----------------------------------------------------------------------------
GrpTrustAnchorCertGrouping::GrpTrustAnchorCertGrouping(uint32_t id)
	: YangGroup("trust-anchor-cert-grouping", id)
{
}

GrpTrustAnchorCertGrouping::~GrpTrustAnchorCertGrouping()
{
}

YangResult_E GrpTrustAnchorCertGrouping::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /trust-anchor-cert-grouping/cert
	// Description: The binary certificate data for this certificate.
	// Type:        ???BINARY
	// Units:
	// -----------------------------------------------------------------------------
	LeafCert certInst(ITEM_CERT);
	addLeaf(certInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /trust-anchor-cert-grouping/cert
// Description: The binary certificate data for this certificate.
// -----------------------------------------------------------------------------
GrpTrustAnchorCertGrouping::LeafCert::LeafCert(uint32_t id)
	: YangLeaf("cert", id)
{
}

GrpTrustAnchorCertGrouping::LeafCert::~LeafCert()
{
}



// -----------------------------------------------------------------------------
// Grouping:    trust-anchor-certs-grouping
// Description: A list of trust anchor certificates, and a notification
//              for when one is about to (or already has) expire.
// -----------------------------------------------------------------------------
GrpTrustAnchorCertsGrouping::GrpTrustAnchorCertsGrouping(uint32_t id)
	: YangGroup("trust-anchor-certs-grouping", id)
{
}

GrpTrustAnchorCertsGrouping::~GrpTrustAnchorCertsGrouping()
{
}

YangResult_E GrpTrustAnchorCertsGrouping::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /trust-anchor-certs-grouping/cert
	// Description: The binary certificate data for this certificate.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstCert certInst(ITEM_CERT);
	certInst.initialise();
	addList(certInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        cert
// Description: The binary certificate data for this certificate.
// -----------------------------------------------------------------------------
GrpTrustAnchorCertsGrouping::LstCert::LstCert(uint32_t id)
	: YangList("cert", id)
{
}

GrpTrustAnchorCertsGrouping::LstCert::~LstCert()
{
}

YangResult_E GrpTrustAnchorCertsGrouping::LstCert::initialise(void)
{


	return YangResult_E::OK;
}





// -----------------------------------------------------------------------------
// Grouping:    end-entity-cert-grouping
// Description: An end entity certificate, and a notification for when
//              it is about to (or already has) expire.
// -----------------------------------------------------------------------------
GrpEndEntityCertGrouping::GrpEndEntityCertGrouping(uint32_t id)
	: YangGroup("end-entity-cert-grouping", id)
{
}

GrpEndEntityCertGrouping::~GrpEndEntityCertGrouping()
{
}

YangResult_E GrpEndEntityCertGrouping::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /end-entity-cert-grouping/cert
	// Description: The binary certificate data for this certificate.
	// Type:        ???BINARY
	// Units:
	// -----------------------------------------------------------------------------
	LeafCert certInst(ITEM_CERT);
	addLeaf(certInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /end-entity-cert-grouping/cert
// Description: The binary certificate data for this certificate.
// -----------------------------------------------------------------------------
GrpEndEntityCertGrouping::LeafCert::LeafCert(uint32_t id)
	: YangLeaf("cert", id)
{
}

GrpEndEntityCertGrouping::LeafCert::~LeafCert()
{
}



// -----------------------------------------------------------------------------
// Grouping:    end-entity-certs-grouping
// Description: A list of end entity certificates, and a notification for
//              when one is about to (or already has) expire.
// -----------------------------------------------------------------------------
GrpEndEntityCertsGrouping::GrpEndEntityCertsGrouping(uint32_t id)
	: YangGroup("end-entity-certs-grouping", id)
{
}

GrpEndEntityCertsGrouping::~GrpEndEntityCertsGrouping()
{
}

YangResult_E GrpEndEntityCertsGrouping::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /end-entity-certs-grouping/cert
	// Description: The binary certificate data for this certificate.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstCert certInst(ITEM_CERT);
	certInst.initialise();
	addList(certInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        cert
// Description: The binary certificate data for this certificate.
// -----------------------------------------------------------------------------
GrpEndEntityCertsGrouping::LstCert::LstCert(uint32_t id)
	: YangList("cert", id)
{
}

GrpEndEntityCertsGrouping::LstCert::~LstCert()
{
}

YangResult_E GrpEndEntityCertsGrouping::LstCert::initialise(void)
{


	return YangResult_E::OK;
}





// -----------------------------------------------------------------------------
// Grouping:    asymmetric-key-pair-with-cert-grouping
// Description: A private/public key pair and an associated certificate.
// -----------------------------------------------------------------------------
GrpAsymmetricKeyPairWithCertGrouping::GrpAsymmetricKeyPairWithCertGrouping(uint32_t id)
	: YangGroup("asymmetric-key-pair-with-cert-grouping", id)
{
}

GrpAsymmetricKeyPairWithCertGrouping::~GrpAsymmetricKeyPairWithCertGrouping()
{
}

YangResult_E GrpAsymmetricKeyPairWithCertGrouping::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /asymmetric-key-pair-with-cert-grouping/asymmetric-key-pair-grouping
	// Description:
	// -----------------------------------------------------------------------------
	GrpAsymmetricKeyPairGrouping asymmetricKeyPairGroupingInst(ITEM_ASYMMETRIC_KEY_PAIR_GROUPING);
	asymmetricKeyPairGroupingInst.initialise();
	addGroup(asymmetricKeyPairGroupingInst);

	// -----------------------------------------------------------------------------
	// Uses:        /asymmetric-key-pair-with-cert-grouping/end-entity-cert-grouping
	// Description:
	// -----------------------------------------------------------------------------
	GrpEndEntityCertGrouping endEntityCertGroupingInst(ITEM_END_ENTITY_CERT_GROUPING);
	endEntityCertGroupingInst.initialise();
	addGroup(endEntityCertGroupingInst);



	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// Grouping:    asymmetric-key-pair-with-certs-grouping
// Description: A private/public key pair and associated certificates.
// -----------------------------------------------------------------------------
GrpAsymmetricKeyPairWithCertsGrouping::GrpAsymmetricKeyPairWithCertsGrouping(uint32_t id)
	: YangGroup("asymmetric-key-pair-with-certs-grouping", id)
{
}

GrpAsymmetricKeyPairWithCertsGrouping::~GrpAsymmetricKeyPairWithCertsGrouping()
{
}

YangResult_E GrpAsymmetricKeyPairWithCertsGrouping::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Container:   /asymmetric-key-pair-with-certs-grouping/certificates
	// Description: Certificates associated with this asymmetric key.
	//              More than one certificate supports, for instance,
	//              a TPM-protected asymmetric key that has both IDevID
	//              and LDevID certificates associated.
	// -----------------------------------------------------------------------------
	CntCertificates certificatesInst(ITEM_CERTIFICATES);
	certificatesInst.initialise();
	addContainer(certificatesInst);

	// -----------------------------------------------------------------------------
	// Uses:        /asymmetric-key-pair-with-certs-grouping/asymmetric-key-pair-grouping
	// Description:
	// -----------------------------------------------------------------------------
	GrpAsymmetricKeyPairGrouping asymmetricKeyPairGroupingInst(ITEM_ASYMMETRIC_KEY_PAIR_GROUPING);
	asymmetricKeyPairGroupingInst.initialise();
	addGroup(asymmetricKeyPairGroupingInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   certificates
// Description: Certificates associated with this asymmetric key.
//              More than one certificate supports, for instance,
//              a TPM-protected asymmetric key that has both IDevID
//              and LDevID certificates associated.
// -----------------------------------------------------------------------------
GrpAsymmetricKeyPairWithCertsGrouping::CntCertificates::CntCertificates(uint32_t id)
	: YangContainer("certificates", id)
{
}

GrpAsymmetricKeyPairWithCertsGrouping::CntCertificates::~CntCertificates()
{
}

YangResult_E GrpAsymmetricKeyPairWithCertsGrouping::CntCertificates::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /asymmetric-key-pair-with-certs-grouping/certificates/certificate
	// Description: A certificate for this asymmetric key.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstCertificate certificateInst(ITEM_CERTIFICATE);
	certificateInst.initialise();
	addList(certificateInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        certificate
// Description: A certificate for this asymmetric key.
// -----------------------------------------------------------------------------
GrpAsymmetricKeyPairWithCertsGrouping::CntCertificates::LstCertificate::LstCertificate(uint32_t id)
	: YangList("certificate", id)
{
}

GrpAsymmetricKeyPairWithCertsGrouping::CntCertificates::LstCertificate::~LstCertificate()
{
}

YangResult_E GrpAsymmetricKeyPairWithCertsGrouping::CntCertificates::LstCertificate::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /asymmetric-key-pair-with-certs-grouping/certificates/certificate/name
	// Description: An arbitrary name for the certificate.  If the name
	//              matches the name of a certificate that exists
	//              independently in <operational> (i.e., an IDevID),
	//              then the 'cert' node MUST NOT be configured.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Uses:        /asymmetric-key-pair-with-certs-grouping/certificates/certificate/end-entity-cert-grouping
	// Description:
	// -----------------------------------------------------------------------------
	GrpEndEntityCertGrouping endEntityCertGroupingInst(ITEM_END_ENTITY_CERT_GROUPING);
	endEntityCertGroupingInst.initialise();
	addGroup(endEntityCertGroupingInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /asymmetric-key-pair-with-certs-grouping/certificates/certificate/name
// Description: An arbitrary name for the certificate.  If the name
//              matches the name of a certificate that exists
//              independently in <operational> (i.e., an IDevID),
//              then the 'cert' node MUST NOT be configured.
// -----------------------------------------------------------------------------
GrpAsymmetricKeyPairWithCertsGrouping::CntCertificates::LstCertificate::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

GrpAsymmetricKeyPairWithCertsGrouping::CntCertificates::LstCertificate::LeafName::~LeafName()
{
}









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
ModuleIetfCryptoTypes::ModuleIetfCryptoTypes(uint32_t id)
	: YangModule ("ietf-crypto-types",
	              "ietf-crypto-types.yang",
	              "ct",
	              "urn:ietf:params:xml:ns:yang:ietf-crypto-types",
	              id)
// Add user code here
// %%->

// <-%%
{

	// Add user code here
	// %%->

	// <-%%
}

ModuleIetfCryptoTypes::~ModuleIetfCryptoTypes()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleIetfCryptoTypes::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleIetfCryptoTypes>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleIetfCryptoTypes::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
