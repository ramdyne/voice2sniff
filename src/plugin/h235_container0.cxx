/* 
 * h235_container0.cxx
 *
 * Source for saving the ID's for Ethereal protocol items
 *
 * H.323 for Ethereal
 *
 * Copyright (c) 2002 Koninklijke Philips NV
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is H.323 for Ethereal.
 *
 * The Initial Developer of the Original Code is Koninklijke Philips NV.
 *
 * All Rights Reserved.
 *
 * Contributor(s): ______________________________________.
 *
 *
 */

//
// h235_container0.cpp
//
// Code automatically generated by asnparse.
//

#include "h235_container0.h"

H235_0_Integer_Container::H235_0_Integer_Container()
{
  hf_proto_H235 = -1; // Protocol itself
  ett_proto_H235 = -1; // Protocol itself
  hf_h235_NonStandardParameter_nonStandardIdentifier = -1;
  hf_h235_NonStandardParameter_data = -1;
  hf_h235_DHset_halfkey = -1;
  hf_h235_DHset_modSize = -1;
  hf_h235_DHset_generator = -1;
  hf_h235_TypedCertificate_type = -1;
  hf_h235_TypedCertificate_certificate = -1;
  hf_h235_AuthenticationMechanism_dhExch = -1;
  hf_h235_AuthenticationMechanism_pwdSymEnc = -1;
  hf_h235_AuthenticationMechanism_pwdHash = -1;
  hf_h235_AuthenticationMechanism_certSign = -1;
  hf_h235_AuthenticationMechanism_ipsec = -1;
  hf_h235_AuthenticationMechanism_tls = -1;
  ett_h235_AuthenticationMechanism_choice = -1;
  hf_h235_ClearToken_tokenOID = -1;
  hf_h235_ClearToken_timeStamp = -1;
  hf_h235_ClearToken_password = -1;
  ett_h235_ClearToken_dhkey = -1;
  hf_h235_ClearToken_challenge = -1;
  hf_h235_ClearToken_random = -1;
  ett_h235_ClearToken_certificate = -1;
  hf_h235_ClearToken_generalID = -1;
  ett_h235_ClearToken_nonStandard = -1;
  hf_h235_Params_ranInt = -1;
  hf_h235_Params_iv8 = -1;
  hf_h235_KeySyncMaterial_generalID = -1;
  hf_h235_KeySyncMaterial_keyMaterial = -1;
  hf_h235_ReturnSig_generalId = -1;
  hf_h235_ReturnSig_responseRandom = -1;
  hf_h235_ReturnSig_requestRandom = -1;
  ett_h235_ReturnSig_certificate = -1;
  ett_h235_CryptoToken_choice = -1;
  hf_h235_KeySignedMaterial_generalId = -1;
  hf_h235_KeySignedMaterial_mrandom = -1;
  hf_h235_KeySignedMaterial_srandom = -1;
  hf_h235_KeySignedMaterial_timeStamp = -1;
  ett_h235_KeySignedMaterial_encrptval = -1;
  ett_h235_H235CertificateSignature_certificate = -1;
  hf_h235_H235CertificateSignature_responseRandom = -1;
  hf_h235_H235CertificateSignature_requesterRandom = -1;
  ett_h235_H235CertificateSignature_signature = -1;
  hf_h235_CryptoToken_cryptoEncryptedToken_tokenOID = -1;
  ett_h235_CryptoToken_cryptoEncryptedToken_token = -1;
  hf_h235_CryptoToken_cryptoSignedToken_tokenOID = -1;
  ett_h235_CryptoToken_cryptoSignedToken_token = -1;
  hf_h235_CryptoToken_cryptoHashedToken_tokenOID = -1;
  ett_h235_CryptoToken_cryptoHashedToken_hashedVals = -1;
  ett_h235_CryptoToken_cryptoHashedToken_token = -1;
  hf_h235_H235Key_secureChannel = -1;
  ett_h235_H235Key_choice = -1;
};



// End of h235_container0.cpp
