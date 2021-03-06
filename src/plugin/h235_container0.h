/* 
 * h235_container0.h
 *
 * Header for saving the ID's for Ethereal protocol items
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
// h235_container0.h
//
// Code automatically generated by asnparse.
//

#ifndef H235_INTEGER_CONTAINER_0_H
#define  H235_INTEGER_CONTAINER_0_H

class H235_0_Integer_Container
{
  public:
    H235_0_Integer_Container();
    int ett_proto_H235; // Protocol itself
    int hf_proto_H235;  // Protocol itself
    int hf_h235_NonStandardParameter_nonStandardIdentifier;
    int hf_h235_NonStandardParameter_data;
    int hf_h235_DHset_halfkey;
    int hf_h235_DHset_modSize;
    int hf_h235_DHset_generator;
    int hf_h235_TypedCertificate_type;
    int hf_h235_TypedCertificate_certificate;
    int hf_h235_AuthenticationMechanism_dhExch;
    int hf_h235_AuthenticationMechanism_pwdSymEnc;
    int hf_h235_AuthenticationMechanism_pwdHash;
    int hf_h235_AuthenticationMechanism_certSign;
    int hf_h235_AuthenticationMechanism_ipsec;
    int hf_h235_AuthenticationMechanism_tls;
    int ett_h235_AuthenticationMechanism_choice;
    int hf_h235_ClearToken_tokenOID;
    int hf_h235_ClearToken_timeStamp;
    int hf_h235_ClearToken_password;
    int ett_h235_ClearToken_dhkey;
    int hf_h235_ClearToken_challenge;
    int hf_h235_ClearToken_random;
    int ett_h235_ClearToken_certificate;
    int hf_h235_ClearToken_generalID;
    int ett_h235_ClearToken_nonStandard;
    int hf_h235_Params_ranInt;
    int hf_h235_Params_iv8;
    int hf_h235_KeySyncMaterial_generalID;
    int hf_h235_KeySyncMaterial_keyMaterial;
    int hf_h235_ReturnSig_generalId;
    int hf_h235_ReturnSig_responseRandom;
    int hf_h235_ReturnSig_requestRandom;
    int ett_h235_ReturnSig_certificate;
    int ett_h235_CryptoToken_choice;
    int hf_h235_KeySignedMaterial_generalId;
    int hf_h235_KeySignedMaterial_mrandom;
    int hf_h235_KeySignedMaterial_srandom;
    int hf_h235_KeySignedMaterial_timeStamp;
    int ett_h235_KeySignedMaterial_encrptval;
    int ett_h235_H235CertificateSignature_certificate;
    int hf_h235_H235CertificateSignature_responseRandom;
    int hf_h235_H235CertificateSignature_requesterRandom;
    int ett_h235_H235CertificateSignature_signature;
    int hf_h235_CryptoToken_cryptoEncryptedToken_tokenOID;
    int ett_h235_CryptoToken_cryptoEncryptedToken_token;
    int hf_h235_CryptoToken_cryptoSignedToken_tokenOID;
    int ett_h235_CryptoToken_cryptoSignedToken_token;
    int hf_h235_CryptoToken_cryptoHashedToken_tokenOID;
    int ett_h235_CryptoToken_cryptoHashedToken_hashedVals;
    int ett_h235_CryptoToken_cryptoHashedToken_token;
    int hf_h235_H235Key_secureChannel;
    int ett_h235_H235Key_choice;
  private:
};

#endif

// End of h235_container0.h
