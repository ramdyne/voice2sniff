/* 
 * h225_container0.cxx
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
// h225_container0.cpp
//
// Code automatically generated by asnparse.
//

#include "h225_container0.h"

H225_0_Integer_Container::H225_0_Integer_Container()
{
  hf_proto_H225 = -1; // Protocol itself
  ett_proto_H225 = -1; // Protocol itself
  hf_h225_ReleaseCompleteReason_noBandwidth = -1;
  hf_h225_ReleaseCompleteReason_gatekeeperResources = -1;
  hf_h225_ReleaseCompleteReason_unreachableDestination = -1;
  hf_h225_ReleaseCompleteReason_destinationRejection = -1;
  hf_h225_ReleaseCompleteReason_invalidRevision = -1;
  hf_h225_ReleaseCompleteReason_noPermission = -1;
  hf_h225_ReleaseCompleteReason_unreachableGatekeeper = -1;
  hf_h225_ReleaseCompleteReason_gatewayResources = -1;
  hf_h225_ReleaseCompleteReason_badFormatAddress = -1;
  hf_h225_ReleaseCompleteReason_adaptiveBusy = -1;
  hf_h225_ReleaseCompleteReason_inConf = -1;
  hf_h225_ReleaseCompleteReason_undefinedReason = -1;
  hf_h225_ReleaseCompleteReason_facilityCallDeflection = -1;
  hf_h225_ReleaseCompleteReason_securityDenied = -1;
  hf_h225_ReleaseCompleteReason_calledPartyNotRegistered = -1;
  hf_h225_ReleaseCompleteReason_callerNotRegistered = -1;
  hf_h225_ReleaseCompleteReason_newConnectionNeeded = -1;
  hf_h225_ReleaseCompleteReason_replaceWithConferenceInvite = -1;
  ett_h225_ReleaseCompleteReason_choice = -1;
  hf_h225_ScnConnectionType_unknown = -1;
  hf_h225_ScnConnectionType_bChannel = -1;
  hf_h225_ScnConnectionType_hybrid2x64 = -1;
  hf_h225_ScnConnectionType_hybrid384 = -1;
  hf_h225_ScnConnectionType_hybrid1536 = -1;
  hf_h225_ScnConnectionType_hybrid1920 = -1;
  hf_h225_ScnConnectionType_multirate = -1;
  hf_h225_ScnConnectionAggregation_auto = -1;
  hf_h225_ScnConnectionAggregation_none = -1;
  hf_h225_ScnConnectionAggregation_h221 = -1;
  hf_h225_ScnConnectionAggregation_bonded_mode1 = -1;
  hf_h225_ScnConnectionAggregation_bonded_mode2 = -1;
  hf_h225_ScnConnectionAggregation_bonded_mode3 = -1;
  hf_h225_PresentationIndicator_presentationAllowed = -1;
  hf_h225_PresentationIndicator_presentationRestricted = -1;
  hf_h225_PresentationIndicator_addressNotAvailable = -1;
  hf_h225_FacilityReason_routeCallToGatekeeper = -1;
  hf_h225_FacilityReason_callForwarded = -1;
  hf_h225_FacilityReason_routeCallToMC = -1;
  hf_h225_FacilityReason_undefinedReason = -1;
  hf_h225_FacilityReason_conferenceListChoice = -1;
  hf_h225_FacilityReason_startH245 = -1;
  hf_h225_FacilityReason_noH245 = -1;
  hf_h225_TransportAddress_netBios = -1;
  hf_h225_TransportAddress_nsap = -1;
  ett_h225_TransportAddress_choice = -1;
  ett_h225_SupportedProtocols_choice = -1;
  hf_h225_H221NonStandard_t35CountryCode = -1;
  hf_h225_H221NonStandard_t35Extension = -1;
  hf_h225_H221NonStandard_manufacturerCode = -1;
  hf_h225_NonStandardIdentifier_object = -1;
  ett_h225_NonStandardIdentifier_choice = -1;
  hf_h225_AliasAddress_e164 = -1;
  hf_h225_AliasAddress_h323_ID = -1;
  hf_h225_AliasAddress_url_ID = -1;
  hf_h225_AliasAddress_email_ID = -1;
  ett_h225_AliasAddress_choice = -1;
  hf_h225_PartyNumber_dataPartyNumber = -1;
  hf_h225_PartyNumber_telexPartyNumber = -1;
  hf_h225_PartyNumber_nationalStandardPartyNumber = -1;
  ett_h225_PartyNumber_choice = -1;
  hf_h225_PublicTypeOfNumber_unknown = -1;
  hf_h225_PublicTypeOfNumber_internationalNumber = -1;
  hf_h225_PublicTypeOfNumber_nationalNumber = -1;
  hf_h225_PublicTypeOfNumber_networkSpecificNumber = -1;
  hf_h225_PublicTypeOfNumber_subscriberNumber = -1;
  hf_h225_PublicTypeOfNumber_abbreviatedNumber = -1;
  hf_h225_PrivateTypeOfNumber_unknown = -1;
  hf_h225_PrivateTypeOfNumber_level2RegionalNumber = -1;
  hf_h225_PrivateTypeOfNumber_level1RegionalNumber = -1;
  hf_h225_PrivateTypeOfNumber_pISNSpecificNumber = -1;
  hf_h225_PrivateTypeOfNumber_localNumber = -1;
  hf_h225_PrivateTypeOfNumber_abbreviatedNumber = -1;
  hf_h225_UseSpecifiedTransport_tcp = -1;
  hf_h225_UseSpecifiedTransport_annexE = -1;
  hf_h225_SecurityServiceMode_none = -1;
  hf_h225_SecurityServiceMode_default = -1;
  ett_h225_SecurityServiceMode_choice = -1;
  hf_h225_H245Security_noSecurity = -1;
  ett_h225_H245Security_choice = -1;
  hf_h225_Q954Details_conferenceCalling = -1;
  hf_h225_Q954Details_threePartyService = -1;
  hf_h225_CallIdentifier_guid = -1;
  hf_h225_EncryptIntAlg_isoAlgorithm = -1;
  ett_h225_EncryptIntAlg_choice = -1;
  hf_h225_NonIsoIntegrityMechanism_hMAC_MD5 = -1;
  hf_h225_NonIsoIntegrityMechanism_hMAC_iso10118_3 = -1;
  ett_h225_NonIsoIntegrityMechanism_choice = -1;
  hf_h225_IntegrityMechanism_digSig = -1;
  hf_h225_IntegrityMechanism_iso9797 = -1;
  ett_h225_IntegrityMechanism_choice = -1;
  hf_h225_ICV_algorithmOID = -1;
  hf_h225_ICV_icv = -1;
  ett_h225_CryptoH323Token_choice = -1;
  ett_h225_RasMessage_choice = -1;
  hf_h225_GatekeeperRejectReason_resourceUnavailable = -1;
  hf_h225_GatekeeperRejectReason_terminalExcluded = -1;
  hf_h225_GatekeeperRejectReason_invalidRevision = -1;
  hf_h225_GatekeeperRejectReason_undefinedReason = -1;
  hf_h225_GatekeeperRejectReason_securityDenial = -1;
  hf_h225_RegistrationRejectReason_discoveryRequired = -1;
  hf_h225_RegistrationRejectReason_invalidRevision = -1;
  hf_h225_RegistrationRejectReason_invalidCallSignalAddress = -1;
  hf_h225_RegistrationRejectReason_invalidRASAddress = -1;
  hf_h225_RegistrationRejectReason_invalidTerminalType = -1;
  hf_h225_RegistrationRejectReason_undefinedReason = -1;
  hf_h225_RegistrationRejectReason_transportNotSupported = -1;
  hf_h225_RegistrationRejectReason_transportQOSNotSupported = -1;
  hf_h225_RegistrationRejectReason_resourceUnavailable = -1;
  hf_h225_RegistrationRejectReason_invalidAlias = -1;
  hf_h225_RegistrationRejectReason_securityDenial = -1;
  hf_h225_RegistrationRejectReason_fullRegistrationRequired = -1;
  ett_h225_RegistrationRejectReason_choice = -1;
  hf_h225_UnregRequestReason_reregistrationRequired = -1;
  hf_h225_UnregRequestReason_ttlExpired = -1;
  hf_h225_UnregRequestReason_securityDenial = -1;
  hf_h225_UnregRequestReason_undefinedReason = -1;
  hf_h225_UnregRejectReason_notCurrentlyRegistered = -1;
  hf_h225_UnregRejectReason_callInProgress = -1;
  hf_h225_UnregRejectReason_undefinedReason = -1;
  hf_h225_UnregRejectReason_permissionDenied = -1;
  hf_h225_UnregRejectReason_securityDenial = -1;
  hf_h225_CallType_pointToPoint = -1;
  hf_h225_CallType_oneToN = -1;
  hf_h225_CallType_nToOne = -1;
  hf_h225_CallType_nToN = -1;
  hf_h225_CallModel_direct = -1;
  hf_h225_CallModel_gatekeeperRouted = -1;
  hf_h225_TransportQOS_endpointControlled = -1;
  hf_h225_TransportQOS_gatekeeperControlled = -1;
  hf_h225_TransportQOS_noControl = -1;
  hf_h225_UUIEsRequested_setup = -1;
  hf_h225_UUIEsRequested_callProceeding = -1;
  hf_h225_UUIEsRequested_connect = -1;
  hf_h225_UUIEsRequested_alerting = -1;
  hf_h225_UUIEsRequested_information = -1;
  hf_h225_UUIEsRequested_releaseComplete = -1;
  hf_h225_UUIEsRequested_facility = -1;
  hf_h225_UUIEsRequested_progress = -1;
  hf_h225_UUIEsRequested_empty = -1;
  hf_h225_AdmissionRejectReason_calledPartyNotRegistered = -1;
  hf_h225_AdmissionRejectReason_invalidPermission = -1;
  hf_h225_AdmissionRejectReason_requestDenied = -1;
  hf_h225_AdmissionRejectReason_undefinedReason = -1;
  hf_h225_AdmissionRejectReason_callerNotRegistered = -1;
  hf_h225_AdmissionRejectReason_routeCallToGatekeeper = -1;
  hf_h225_AdmissionRejectReason_invalidEndpointIdentifier = -1;
  hf_h225_AdmissionRejectReason_resourceUnavailable = -1;
  hf_h225_AdmissionRejectReason_securityDenial = -1;
  hf_h225_AdmissionRejectReason_qosControlNotSupported = -1;
  hf_h225_AdmissionRejectReason_incompleteAddress = -1;
  hf_h225_AdmissionRejectReason_aliasesInconsistent = -1;
  ett_h225_AdmissionRejectReason_choice = -1;
  hf_h225_BandRejectReason_notBound = -1;
  hf_h225_BandRejectReason_invalidConferenceID = -1;
  hf_h225_BandRejectReason_invalidPermission = -1;
  hf_h225_BandRejectReason_insufficientResources = -1;
  hf_h225_BandRejectReason_invalidRevision = -1;
  hf_h225_BandRejectReason_undefinedReason = -1;
  hf_h225_BandRejectReason_securityDenial = -1;
  hf_h225_LocationRejectReason_notRegistered = -1;
  hf_h225_LocationRejectReason_invalidPermission = -1;
  hf_h225_LocationRejectReason_requestDenied = -1;
  hf_h225_LocationRejectReason_undefinedReason = -1;
  hf_h225_LocationRejectReason_securityDenial = -1;
  hf_h225_LocationRejectReason_aliasesInconsistent = -1;
  ett_h225_LocationRejectReason_choice = -1;
  hf_h225_DisengageReason_forcedDrop = -1;
  hf_h225_DisengageReason_normalDrop = -1;
  hf_h225_DisengageReason_undefinedReason = -1;
  hf_h225_DisengageRejectReason_notRegistered = -1;
  hf_h225_DisengageRejectReason_requestToDropOther = -1;
  hf_h225_DisengageRejectReason_securityDenial = -1;
  ett_h225_TransportChannelInfo_sendAddress = -1;
  ett_h225_TransportChannelInfo_recvAddress = -1;
  hf_h225_InfoRequestNakReason_notRegistered = -1;
  hf_h225_InfoRequestNakReason_securityDenial = -1;
  hf_h225_InfoRequestNakReason_undefinedReason = -1;
  hf_h225_H323_UserInformation_user_data_protocol_discriminator = -1;
  hf_h225_H323_UserInformation_user_data_user_information = -1;
  hf_h225_H323_UU_PDU_h323_message_body_empty = -1;
  ett_h225_H323_UU_PDU_h323_message_body_choice = -1;
  hf_h225_ArrayOf_PASN_OctetString_array = -1;
  ett_h225_ArrayOf_NonStandardParameter = -1;
  ett_h225_ArrayOf_ClearToken = -1;
  ett_h225_ArrayOf_CryptoH323Token = -1;
  ett_h225_ArrayOf_AliasAddress = -1;
  hf_h225_Connect_UUIE_language_array = -1;
  hf_h225_ArrayOf_CallReferenceValue_array = -1;
  hf_h225_Setup_UUIE_conferenceGoal_create = -1;
  hf_h225_Setup_UUIE_conferenceGoal_join = -1;
  hf_h225_Setup_UUIE_conferenceGoal_invite = -1;
  hf_h225_Setup_UUIE_conferenceGoal_capability_negotiation = -1;
  hf_h225_Setup_UUIE_conferenceGoal_callIndependentSupplementaryService = -1;
  ett_h225_ArrayOf_H245Security = -1;
  ett_h225_Setup_UUIE_connectionParameters_connectionType = -1;
  hf_h225_Setup_UUIE_connectionParameters_numberOfScnConnections = -1;
  ett_h225_Setup_UUIE_connectionParameters_connectionAggregation = -1;
  hf_h225_Setup_UUIE_language_array = -1;
  ett_h225_ArrayOf_ConferenceList = -1;
  hf_h225_TransportAddress_ipAddress_ip = -1;
  hf_h225_TransportAddress_ipAddress_port = -1;
  hf_h225_TransportAddress_ipxAddress_node = -1;
  hf_h225_TransportAddress_ipxAddress_netnum = -1;
  hf_h225_TransportAddress_ipxAddress_port = -1;
  hf_h225_TransportAddress_ip6Address_ip = -1;
  hf_h225_TransportAddress_ip6Address_port = -1;
  ett_h225_ArrayOf_SupportedProtocols = -1;
  ett_h225_ArrayOf_DataRate = -1;
  ett_h225_ArrayOf_SupportedPrefix = -1;
  ett_h225_ArrayOf_TransportAddress = -1;
  ett_h225_ArrayOf_AlternateGK = -1;
  ett_h225_CryptoH323Token_cryptoEPPwdHash_alias = -1;
  ett_h225_CryptoH323Token_cryptoEPPwdHash_timeStamp = -1;
  ett_h225_CryptoH323Token_cryptoEPPwdHash_token = -1;
  hf_h225_CryptoH323Token_cryptoGKPwdHash_gatekeeperId = -1;
  ett_h225_CryptoH323Token_cryptoGKPwdHash_timeStamp = -1;
  ett_h225_CryptoH323Token_cryptoGKPwdHash_token = -1;
  ett_h225_ArrayOf_Endpoint = -1;
  ett_h225_ArrayOf_AuthenticationMechanism = -1;
  hf_h225_ArrayOf_PASN_ObjectId_array = -1;
  ett_h225_ArrayOf_IntegrityMechanism = -1;
  hf_h225_AdmissionConfirm_language_array = -1;
  ett_h225_ArrayOf_PartyNumber = -1;
  ett_h225_InfoRequestResponse_perCallInfo = -1;
  hf_h225_RTPSession_associatedSessionIds_array = -1;
  hf_h225_TransportAddress_ipSourceRoute_route_array = -1;
  hf_h225_TransportAddress_ipSourceRoute_routing_strict = -1;
  hf_h225_TransportAddress_ipSourceRoute_routing_loose = -1;
  ett_h225_ArrayOf_RTPSession = -1;
  ett_h225_ArrayOf_TransportChannelInfo = -1;
  hf_h225_ArrayOf_ConferenceIdentifier_array = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_pdu = -1;
  hf_h225_Information_UUIE_protocolIdentifier = -1;
  ett_h225_Information_UUIE_callIdentifier = -1;
  ett_h225_Information_UUIE_tokens = -1;
  ett_h225_Information_UUIE_cryptoTokens = -1;
  ett_h225_Information_UUIE_fastStart = -1;
  hf_h225_Information_UUIE_fastConnectRefused = -1;
  hf_h225_ReleaseComplete_UUIE_protocolIdentifier = -1;
  ett_h225_ReleaseComplete_UUIE_reason = -1;
  ett_h225_ReleaseComplete_UUIE_callIdentifier = -1;
  ett_h225_ReleaseComplete_UUIE_tokens = -1;
  ett_h225_ReleaseComplete_UUIE_cryptoTokens = -1;
  ett_h225_ReleaseComplete_UUIE_busyAddress = -1;
  ett_h225_ReleaseComplete_UUIE_presentationIndicator = -1;
  hf_h225_ReleaseComplete_UUIE_screeningIndicator = -1;
  hf_h225_Facility_UUIE_protocolIdentifier = -1;
  ett_h225_Facility_UUIE_alternativeAddress = -1;
  ett_h225_Facility_UUIE_alternativeAliasAddress = -1;
  hf_h225_Facility_UUIE_conferenceID = -1;
  ett_h225_Facility_UUIE_reason = -1;
  ett_h225_Facility_UUIE_callIdentifier = -1;
  ett_h225_Facility_UUIE_destExtraCallInfo = -1;
  ett_h225_Facility_UUIE_remoteExtensionAddress = -1;
  ett_h225_Facility_UUIE_tokens = -1;
  ett_h225_Facility_UUIE_cryptoTokens = -1;
  ett_h225_Facility_UUIE_conferences = -1;
  ett_h225_Facility_UUIE_h245Address = -1;
  ett_h225_Facility_UUIE_fastStart = -1;
  hf_h225_Facility_UUIE_multipleCalls = -1;
  hf_h225_Facility_UUIE_maintainConnection = -1;
  hf_h225_Facility_UUIE_fastConnectRefused = -1;
  hf_h225_CallLinkage_globalCallId = -1;
  hf_h225_CallLinkage_threadId = -1;
  ett_h225_VendorIdentifier_vendor = -1;
  hf_h225_VendorIdentifier_productId = -1;
  hf_h225_VendorIdentifier_versionId = -1;
  ett_h225_NonStandardParameter_nonStandardIdentifier = -1;
  hf_h225_NonStandardParameter_data = -1;
  ett_h225_PublicPartyNumber_publicTypeOfNumber = -1;
  hf_h225_PublicPartyNumber_publicNumberDigits = -1;
  ett_h225_PrivatePartyNumber_privateTypeOfNumber = -1;
  hf_h225_PrivatePartyNumber_privateNumberDigits = -1;
  ett_h225_AlternateTransportAddresses_annexE = -1;
  ett_h225_AlternateGK_rasAddress = -1;
  hf_h225_AlternateGK_gatekeeperIdentifier = -1;
  hf_h225_AlternateGK_needToRegister = -1;
  hf_h225_AlternateGK_priority = -1;
  ett_h225_AltGKInfo_alternateGatekeeper = -1;
  hf_h225_AltGKInfo_altGKisPermanent = -1;
  ett_h225_SecurityCapabilities_nonStandard = -1;
  ett_h225_SecurityCapabilities_encryption = -1;
  ett_h225_SecurityCapabilities_authenticaton = -1;
  ett_h225_SecurityCapabilities_integrity = -1;
  hf_h225_QseriesOptions_q932Full = -1;
  hf_h225_QseriesOptions_q951Full = -1;
  hf_h225_QseriesOptions_q952Full = -1;
  hf_h225_QseriesOptions_q953Full = -1;
  hf_h225_QseriesOptions_q955Full = -1;
  hf_h225_QseriesOptions_q956Full = -1;
  hf_h225_QseriesOptions_q957Full = -1;
  ett_h225_QseriesOptions_q954Info = -1;
  ett_h225_DataRate_nonStandardData = -1;
  hf_h225_DataRate_channelRate = -1;
  hf_h225_DataRate_channelMultiplier = -1;
  ett_h225_SupportedPrefix_nonStandardData = -1;
  ett_h225_SupportedPrefix_prefix = -1;
  hf_h225_GatekeeperConfirm_requestSeqNum = -1;
  hf_h225_GatekeeperConfirm_protocolIdentifier = -1;
  ett_h225_GatekeeperConfirm_nonStandardData = -1;
  hf_h225_GatekeeperConfirm_gatekeeperIdentifier = -1;
  ett_h225_GatekeeperConfirm_rasAddress = -1;
  ett_h225_GatekeeperConfirm_alternateGatekeeper = -1;
  ett_h225_GatekeeperConfirm_authenticationMode = -1;
  ett_h225_GatekeeperConfirm_tokens = -1;
  ett_h225_GatekeeperConfirm_cryptoTokens = -1;
  hf_h225_GatekeeperConfirm_algorithmOID = -1;
  ett_h225_GatekeeperConfirm_integrity = -1;
  ett_h225_GatekeeperConfirm_integrityCheckValue = -1;
  hf_h225_GatekeeperReject_requestSeqNum = -1;
  hf_h225_GatekeeperReject_protocolIdentifier = -1;
  ett_h225_GatekeeperReject_nonStandardData = -1;
  hf_h225_GatekeeperReject_gatekeeperIdentifier = -1;
  ett_h225_GatekeeperReject_rejectReason = -1;
  ett_h225_GatekeeperReject_altGKInfo = -1;
  ett_h225_GatekeeperReject_tokens = -1;
  ett_h225_GatekeeperReject_cryptoTokens = -1;
  ett_h225_GatekeeperReject_integrityCheckValue = -1;
  hf_h225_RegistrationReject_requestSeqNum = -1;
  hf_h225_RegistrationReject_protocolIdentifier = -1;
  ett_h225_RegistrationReject_nonStandardData = -1;
  ett_h225_RegistrationReject_rejectReason = -1;
  hf_h225_RegistrationReject_gatekeeperIdentifier = -1;
  ett_h225_RegistrationReject_altGKInfo = -1;
  ett_h225_RegistrationReject_tokens = -1;
  ett_h225_RegistrationReject_cryptoTokens = -1;
  ett_h225_RegistrationReject_integrityCheckValue = -1;
  hf_h225_UnregistrationRequest_requestSeqNum = -1;
  ett_h225_UnregistrationRequest_callSignalAddress = -1;
  ett_h225_UnregistrationRequest_endpointAlias = -1;
  ett_h225_UnregistrationRequest_nonStandardData = -1;
  hf_h225_UnregistrationRequest_endpointIdentifier = -1;
  ett_h225_UnregistrationRequest_alternateEndpoints = -1;
  hf_h225_UnregistrationRequest_gatekeeperIdentifier = -1;
  ett_h225_UnregistrationRequest_tokens = -1;
  ett_h225_UnregistrationRequest_cryptoTokens = -1;
  ett_h225_UnregistrationRequest_integrityCheckValue = -1;
  ett_h225_UnregistrationRequest_reason = -1;
  hf_h225_UnregistrationConfirm_requestSeqNum = -1;
  ett_h225_UnregistrationConfirm_nonStandardData = -1;
  ett_h225_UnregistrationConfirm_tokens = -1;
  ett_h225_UnregistrationConfirm_cryptoTokens = -1;
  ett_h225_UnregistrationConfirm_integrityCheckValue = -1;
  hf_h225_UnregistrationReject_requestSeqNum = -1;
  ett_h225_UnregistrationReject_rejectReason = -1;
  ett_h225_UnregistrationReject_nonStandardData = -1;
  ett_h225_UnregistrationReject_altGKInfo = -1;
  ett_h225_UnregistrationReject_tokens = -1;
  ett_h225_UnregistrationReject_cryptoTokens = -1;
  ett_h225_UnregistrationReject_integrityCheckValue = -1;
  hf_h225_AdmissionRequest_requestSeqNum = -1;
  ett_h225_AdmissionRequest_callType = -1;
  ett_h225_AdmissionRequest_callModel = -1;
  hf_h225_AdmissionRequest_endpointIdentifier = -1;
  ett_h225_AdmissionRequest_destinationInfo = -1;
  ett_h225_AdmissionRequest_destCallSignalAddress = -1;
  ett_h225_AdmissionRequest_destExtraCallInfo = -1;
  ett_h225_AdmissionRequest_srcInfo = -1;
  ett_h225_AdmissionRequest_srcCallSignalAddress = -1;
  hf_h225_AdmissionRequest_bandWidth = -1;
  hf_h225_AdmissionRequest_callReferenceValue = -1;
  ett_h225_AdmissionRequest_nonStandardData = -1;
  ett_h225_AdmissionRequest_callServices = -1;
  hf_h225_AdmissionRequest_conferenceID = -1;
  hf_h225_AdmissionRequest_activeMC = -1;
  hf_h225_AdmissionRequest_answerCall = -1;
  hf_h225_AdmissionRequest_canMapAlias = -1;
  ett_h225_AdmissionRequest_callIdentifier = -1;
  ett_h225_AdmissionRequest_srcAlternatives = -1;
  ett_h225_AdmissionRequest_destAlternatives = -1;
  hf_h225_AdmissionRequest_gatekeeperIdentifier = -1;
  ett_h225_AdmissionRequest_tokens = -1;
  ett_h225_AdmissionRequest_cryptoTokens = -1;
  ett_h225_AdmissionRequest_integrityCheckValue = -1;
  ett_h225_AdmissionRequest_transportQOS = -1;
  hf_h225_AdmissionRequest_willSupplyUUIEs = -1;
  ett_h225_AdmissionRequest_callLinkage = -1;
  hf_h225_AdmissionReject_requestSeqNum = -1;
  ett_h225_AdmissionReject_rejectReason = -1;
  ett_h225_AdmissionReject_nonStandardData = -1;
  ett_h225_AdmissionReject_altGKInfo = -1;
  ett_h225_AdmissionReject_tokens = -1;
  ett_h225_AdmissionReject_cryptoTokens = -1;
  ett_h225_AdmissionReject_callSignalAddress = -1;
  ett_h225_AdmissionReject_integrityCheckValue = -1;
  hf_h225_BandwidthRequest_requestSeqNum = -1;
  hf_h225_BandwidthRequest_endpointIdentifier = -1;
  hf_h225_BandwidthRequest_conferenceID = -1;
  hf_h225_BandwidthRequest_callReferenceValue = -1;
  ett_h225_BandwidthRequest_callType = -1;
  hf_h225_BandwidthRequest_bandWidth = -1;
  ett_h225_BandwidthRequest_nonStandardData = -1;
  ett_h225_BandwidthRequest_callIdentifier = -1;
  hf_h225_BandwidthRequest_gatekeeperIdentifier = -1;
  ett_h225_BandwidthRequest_tokens = -1;
  ett_h225_BandwidthRequest_cryptoTokens = -1;
  ett_h225_BandwidthRequest_integrityCheckValue = -1;
  hf_h225_BandwidthRequest_answeredCall = -1;
  ett_h225_BandwidthRequest_callLinkage = -1;
  hf_h225_BandwidthConfirm_requestSeqNum = -1;
}

// End of h225_container0.cpp
