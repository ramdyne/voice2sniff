/* 
 * h225_container1.cxx
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
// h225_container1.cpp
//
// Code automatically generated by asnparse.
//

#include "h225_container1.h"

H225_1_Integer_Container::H225_1_Integer_Container()
{

  hf_h225_BandwidthConfirm_bandWidth = -1;
  ett_h225_BandwidthConfirm_nonStandardData = -1;
  ett_h225_BandwidthConfirm_tokens = -1;
  ett_h225_BandwidthConfirm_cryptoTokens = -1;
  ett_h225_BandwidthConfirm_integrityCheckValue = -1;
  hf_h225_BandwidthReject_requestSeqNum = -1;
  ett_h225_BandwidthReject_rejectReason = -1;
  hf_h225_BandwidthReject_allowedBandWidth = -1;
  ett_h225_BandwidthReject_nonStandardData = -1;
  ett_h225_BandwidthReject_altGKInfo = -1;
  ett_h225_BandwidthReject_tokens = -1;
  ett_h225_BandwidthReject_cryptoTokens = -1;
  ett_h225_BandwidthReject_integrityCheckValue = -1;
  hf_h225_LocationRequest_requestSeqNum = -1;
  hf_h225_LocationRequest_endpointIdentifier = -1;
  ett_h225_LocationRequest_destinationInfo = -1;
  ett_h225_LocationRequest_nonStandardData = -1;
  ett_h225_LocationRequest_replyAddress = -1;
  ett_h225_LocationRequest_sourceInfo = -1;
  hf_h225_LocationRequest_canMapAlias = -1;
  hf_h225_LocationRequest_gatekeeperIdentifier = -1;
  ett_h225_LocationRequest_tokens = -1;
  ett_h225_LocationRequest_cryptoTokens = -1;
  ett_h225_LocationRequest_integrityCheckValue = -1;
  hf_h225_LocationReject_requestSeqNum = -1;
  ett_h225_LocationReject_rejectReason = -1;
  ett_h225_LocationReject_nonStandardData = -1;
  ett_h225_LocationReject_altGKInfo = -1;
  ett_h225_LocationReject_tokens = -1;
  ett_h225_LocationReject_cryptoTokens = -1;
  ett_h225_LocationReject_integrityCheckValue = -1;
  hf_h225_DisengageRequest_requestSeqNum = -1;
  hf_h225_DisengageRequest_endpointIdentifier = -1;
  hf_h225_DisengageRequest_conferenceID = -1;
  hf_h225_DisengageRequest_callReferenceValue = -1;
  ett_h225_DisengageRequest_disengageReason = -1;
  ett_h225_DisengageRequest_nonStandardData = -1;
  ett_h225_DisengageRequest_callIdentifier = -1;
  hf_h225_DisengageRequest_gatekeeperIdentifier = -1;
  ett_h225_DisengageRequest_tokens = -1;
  ett_h225_DisengageRequest_cryptoTokens = -1;
  ett_h225_DisengageRequest_integrityCheckValue = -1;
  hf_h225_DisengageRequest_answeredCall = -1;
  ett_h225_DisengageRequest_callLinkage = -1;
  hf_h225_DisengageConfirm_requestSeqNum = -1;
  ett_h225_DisengageConfirm_nonStandardData = -1;
  ett_h225_DisengageConfirm_tokens = -1;
  ett_h225_DisengageConfirm_cryptoTokens = -1;
  ett_h225_DisengageConfirm_integrityCheckValue = -1;
  hf_h225_DisengageReject_requestSeqNum = -1;
  ett_h225_DisengageReject_rejectReason = -1;
  ett_h225_DisengageReject_nonStandardData = -1;
  ett_h225_DisengageReject_altGKInfo = -1;
  ett_h225_DisengageReject_tokens = -1;
  ett_h225_DisengageReject_cryptoTokens = -1;
  ett_h225_DisengageReject_integrityCheckValue = -1;
  hf_h225_InfoRequest_requestSeqNum = -1;
  hf_h225_InfoRequest_callReferenceValue = -1;
  ett_h225_InfoRequest_nonStandardData = -1;
  ett_h225_InfoRequest_replyAddress = -1;
  ett_h225_InfoRequest_callIdentifier = -1;
  ett_h225_InfoRequest_tokens = -1;
  ett_h225_InfoRequest_cryptoTokens = -1;
  ett_h225_InfoRequest_integrityCheckValue = -1;
  ett_h225_InfoRequest_uuiesRequested = -1;
  ett_h225_InfoRequest_callLinkage = -1;
  ett_h225_RTPSession_rtpAddress = -1;
  ett_h225_RTPSession_rtcpAddress = -1;
  hf_h225_RTPSession_cname = -1;
  hf_h225_RTPSession_ssrc = -1;
  hf_h225_RTPSession_sessionId = -1;
  ett_h225_RTPSession_associatedSessionIds = -1;
  hf_h225_InfoRequestAck_requestSeqNum = -1;
  ett_h225_InfoRequestAck_nonStandardData = -1;
  ett_h225_InfoRequestAck_tokens = -1;
  ett_h225_InfoRequestAck_cryptoTokens = -1;
  ett_h225_InfoRequestAck_integrityCheckValue = -1;
  hf_h225_InfoRequestNak_requestSeqNum = -1;
  ett_h225_InfoRequestNak_nonStandardData = -1;
  ett_h225_InfoRequestNak_nakReason = -1;
  ett_h225_InfoRequestNak_altGKInfo = -1;
  ett_h225_InfoRequestNak_tokens = -1;
  ett_h225_InfoRequestNak_cryptoTokens = -1;
  ett_h225_InfoRequestNak_integrityCheckValue = -1;
  hf_h225_NonStandardMessage_requestSeqNum = -1;
  ett_h225_NonStandardMessage_nonStandardData = -1;
  ett_h225_NonStandardMessage_tokens = -1;
  ett_h225_NonStandardMessage_cryptoTokens = -1;
  ett_h225_NonStandardMessage_integrityCheckValue = -1;
  hf_h225_UnknownMessageResponse_requestSeqNum = -1;
  ett_h225_UnknownMessageResponse_tokens = -1;
  ett_h225_UnknownMessageResponse_cryptoTokens = -1;
  ett_h225_UnknownMessageResponse_integrityCheckValue = -1;
  hf_h225_RequestInProgress_requestSeqNum = -1;
  ett_h225_RequestInProgress_nonStandardData = -1;
  ett_h225_RequestInProgress_tokens = -1;
  ett_h225_RequestInProgress_cryptoTokens = -1;
  ett_h225_RequestInProgress_integrityCheckValue = -1;
  hf_h225_RequestInProgress_delay = -1;
  hf_h225_ResourcesAvailableIndicate_requestSeqNum = -1;
  hf_h225_ResourcesAvailableIndicate_protocolIdentifier = -1;
  ett_h225_ResourcesAvailableIndicate_nonStandardData = -1;
  hf_h225_ResourcesAvailableIndicate_endpointIdentifier = -1;
  ett_h225_ResourcesAvailableIndicate_protocols = -1;
  hf_h225_ResourcesAvailableIndicate_almostOutOfResources = -1;
  ett_h225_ResourcesAvailableIndicate_tokens = -1;
  ett_h225_ResourcesAvailableIndicate_cryptoTokens = -1;
  ett_h225_ResourcesAvailableIndicate_integrityCheckValue = -1;
  hf_h225_ResourcesAvailableConfirm_requestSeqNum = -1;
  hf_h225_ResourcesAvailableConfirm_protocolIdentifier = -1;
  ett_h225_ResourcesAvailableConfirm_nonStandardData = -1;
  ett_h225_ResourcesAvailableConfirm_tokens = -1;
  ett_h225_ResourcesAvailableConfirm_cryptoTokens = -1;
  ett_h225_ResourcesAvailableConfirm_integrityCheckValue = -1;
  hf_h225_TransportAddress_ipSourceRoute_ip = -1;
  hf_h225_TransportAddress_ipSourceRoute_port = -1;
  ett_h225_TransportAddress_ipSourceRoute_route = -1;
  ett_h225_TransportAddress_ipSourceRoute_routing = -1;
  hf_h225_RegistrationConfirm_preGrantedARQ_makeCall = -1;
  hf_h225_RegistrationConfirm_preGrantedARQ_useGKCallSignalAddressToMakeCall = -1;
  hf_h225_RegistrationConfirm_preGrantedARQ_answerCall = -1;
  hf_h225_RegistrationConfirm_preGrantedARQ_useGKCallSignalAddressToAnswer = -1;
  hf_h225_RegistrationConfirm_preGrantedARQ_irrFrequencyInCall = -1;
  hf_h225_RegistrationConfirm_preGrantedARQ_totalBandwidthRestriction = -1;
  ett_h225_RegistrationConfirm_preGrantedARQ_alternateTransportAddresses = -1;
  ett_h225_RegistrationConfirm_preGrantedARQ_useSpecifiedTransport = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_nonStandardData = -1;
  hf_h225_InfoRequestResponse_perCallInfo_subtype_callReferenceValue = -1;
  hf_h225_InfoRequestResponse_perCallInfo_subtype_conferenceID = -1;
  hf_h225_InfoRequestResponse_perCallInfo_subtype_originator = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_audio = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_video = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_data = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_h245 = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_callSignaling = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_callType = -1;
  hf_h225_InfoRequestResponse_perCallInfo_subtype_bandWidth = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_callModel = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_callIdentifier = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_tokens = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_cryptoTokens = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_substituteConfIDs = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_pdu = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_callLinkage = -1;
  ett_h225_H323_UU_PDU_h323_message_body = -1;
  ett_h225_H323_UU_PDU_nonStandardData = -1;
  ett_h225_H323_UU_PDU_h4501SupplementaryService = -1;
  hf_h225_H323_UU_PDU_h245Tunneling = -1;
  ett_h225_H323_UU_PDU_h245Control = -1;
  ett_h225_H323_UU_PDU_nonStandardControl = -1;
  ett_h225_H323_UU_PDU_callLinkage = -1;
  hf_h225_ConferenceList_conferenceID = -1;
  ett_h225_ConferenceList_conferenceAlias = -1;
  ett_h225_ConferenceList_nonStandardData = -1;
  ett_h225_GatewayInfo_protocol = -1;
  ett_h225_GatewayInfo_nonStandardData = -1;
  ett_h225_H310Caps_nonStandardData = -1;
  ett_h225_H310Caps_dataRatesSupported = -1;
  ett_h225_H310Caps_supportedPrefixes = -1;
  ett_h225_H320Caps_nonStandardData = -1;
  ett_h225_H320Caps_dataRatesSupported = -1;
  ett_h225_H320Caps_supportedPrefixes = -1;
  ett_h225_H321Caps_nonStandardData = -1;
  ett_h225_H321Caps_dataRatesSupported = -1;
  ett_h225_H321Caps_supportedPrefixes = -1;
  ett_h225_H322Caps_nonStandardData = -1;
  ett_h225_H322Caps_dataRatesSupported = -1;
  ett_h225_H322Caps_supportedPrefixes = -1;
  ett_h225_H323Caps_nonStandardData = -1;
  ett_h225_H323Caps_dataRatesSupported = -1;
  ett_h225_H323Caps_supportedPrefixes = -1;
  ett_h225_H324Caps_nonStandardData = -1;
  ett_h225_H324Caps_dataRatesSupported = -1;
  ett_h225_H324Caps_supportedPrefixes = -1;
  ett_h225_VoiceCaps_nonStandardData = -1;
  ett_h225_VoiceCaps_dataRatesSupported = -1;
  ett_h225_VoiceCaps_supportedPrefixes = -1;
  ett_h225_T120OnlyCaps_nonStandardData = -1;
  ett_h225_T120OnlyCaps_dataRatesSupported = -1;
  ett_h225_T120OnlyCaps_supportedPrefixes = -1;
  ett_h225_NonStandardProtocol_nonStandardData = -1;
  ett_h225_NonStandardProtocol_dataRatesSupported = -1;
  ett_h225_NonStandardProtocol_supportedPrefixes = -1;
  ett_h225_T38FaxAnnexbOnlyCaps_nonStandardData = -1;
  ett_h225_T38FaxAnnexbOnlyCaps_dataRatesSupported = -1;
  ett_h225_T38FaxAnnexbOnlyCaps_supportedPrefixes = -1;
  ett_h225_T38FaxAnnexbOnlyCaps_t38FaxProtocol = -1;
  ett_h225_T38FaxAnnexbOnlyCaps_t38FaxProfile = -1;
  ett_h225_McuInfo_nonStandardData = -1;
  ett_h225_TerminalInfo_nonStandardData = -1;
  ett_h225_GatekeeperInfo_nonStandardData = -1;
  hf_h225_RegistrationConfirm_requestSeqNum = -1;
  hf_h225_RegistrationConfirm_protocolIdentifier = -1;
  ett_h225_RegistrationConfirm_nonStandardData = -1;
  ett_h225_RegistrationConfirm_callSignalAddress = -1;
  ett_h225_RegistrationConfirm_terminalAlias = -1;
  hf_h225_RegistrationConfirm_gatekeeperIdentifier = -1;
  hf_h225_RegistrationConfirm_endpointIdentifier = -1;
  ett_h225_RegistrationConfirm_alternateGatekeeper = -1;
  hf_h225_RegistrationConfirm_timeToLive = -1;
  ett_h225_RegistrationConfirm_tokens = -1;
  ett_h225_RegistrationConfirm_cryptoTokens = -1;
  ett_h225_RegistrationConfirm_integrityCheckValue = -1;
  hf_h225_RegistrationConfirm_willRespondToIRR = -1;
  ett_h225_RegistrationConfirm_preGrantedARQ = -1;
  hf_h225_RegistrationConfirm_maintainConnection = -1;
  ett_h225_InfoRequestResponse_perCallInfo_subtype_pdu_subtype_h323pdu = -1;
  hf_h225_InfoRequestResponse_perCallInfo_subtype_pdu_subtype_sent = -1;
  ett_h225_H323_UserInformation_h323_uu_pdu = -1;
  ett_h225_H323_UserInformation_user_data = -1;
  ett_h225_EndpointType_nonStandardData = -1;
  ett_h225_EndpointType_vendor = -1;
  ett_h225_EndpointType_gatekeeper = -1;
  ett_h225_EndpointType_gateway = -1;
  ett_h225_EndpointType_mcu = -1;
  ett_h225_EndpointType_terminal = -1;
  hf_h225_EndpointType_mc = -1;
  hf_h225_EndpointType_undefinedNode = -1;
  hf_h225_EndpointType_set = -1;
  ett_h225_Endpoint_nonStandardData = -1;
  ett_h225_Endpoint_aliasAddress = -1;
  ett_h225_Endpoint_callSignalAddress = -1;
  ett_h225_Endpoint_rasAddress = -1;
  ett_h225_Endpoint_endpointType = -1;
  ett_h225_Endpoint_tokens = -1;
  ett_h225_Endpoint_cryptoTokens = -1;
  hf_h225_Endpoint_priority = -1;
  ett_h225_Endpoint_remoteExtensionAddress = -1;
  ett_h225_Endpoint_destExtraCallInfo = -1;
  ett_h225_Endpoint_alternateTransportAddresses = -1;
  hf_h225_GatekeeperRequest_requestSeqNum = -1;
  hf_h225_GatekeeperRequest_protocolIdentifier = -1;
  ett_h225_GatekeeperRequest_nonStandardData = -1;
  ett_h225_GatekeeperRequest_rasAddress = -1;
  ett_h225_GatekeeperRequest_endpointType = -1;
  hf_h225_GatekeeperRequest_gatekeeperIdentifier = -1;
  ett_h225_GatekeeperRequest_callServices = -1;
  ett_h225_GatekeeperRequest_endpointAlias = -1;
  ett_h225_GatekeeperRequest_alternateEndpoints = -1;
  ett_h225_GatekeeperRequest_tokens = -1;
  ett_h225_GatekeeperRequest_cryptoTokens = -1;
  ett_h225_GatekeeperRequest_authenticationCapability = -1;
  ett_h225_GatekeeperRequest_algorithmOIDs = -1;
  ett_h225_GatekeeperRequest_integrity = -1;
  ett_h225_GatekeeperRequest_integrityCheckValue = -1;
  hf_h225_RegistrationRequest_requestSeqNum = -1;
  hf_h225_RegistrationRequest_protocolIdentifier = -1;
  ett_h225_RegistrationRequest_nonStandardData = -1;
  hf_h225_RegistrationRequest_discoveryComplete = -1;
  ett_h225_RegistrationRequest_callSignalAddress = -1;
  ett_h225_RegistrationRequest_rasAddress = -1;
  ett_h225_RegistrationRequest_terminalType = -1;
  ett_h225_RegistrationRequest_terminalAlias = -1;
  hf_h225_RegistrationRequest_gatekeeperIdentifier = -1;
  ett_h225_RegistrationRequest_endpointVendor = -1;
  ett_h225_RegistrationRequest_alternateEndpoints = -1;
  hf_h225_RegistrationRequest_timeToLive = -1;
  ett_h225_RegistrationRequest_tokens = -1;
  ett_h225_RegistrationRequest_cryptoTokens = -1;
  ett_h225_RegistrationRequest_integrityCheckValue = -1;
  hf_h225_RegistrationRequest_keepAlive = -1;
  hf_h225_RegistrationRequest_endpointIdentifier = -1;
  hf_h225_RegistrationRequest_willSupplyUUIEs = -1;
  hf_h225_RegistrationRequest_maintainConnection = -1;
  ett_h225_RegistrationRequest_alternateTransportAddresses = -1;
  hf_h225_AdmissionConfirm_requestSeqNum = -1;
  hf_h225_AdmissionConfirm_bandWidth = -1;
  ett_h225_AdmissionConfirm_callModel = -1;
  ett_h225_AdmissionConfirm_destCallSignalAddress = -1;
  hf_h225_AdmissionConfirm_irrFrequency = -1;
  ett_h225_AdmissionConfirm_nonStandardData = -1;
  ett_h225_AdmissionConfirm_destinationInfo = -1;
  ett_h225_AdmissionConfirm_destExtraCallInfo = -1;
  ett_h225_AdmissionConfirm_destinationType = -1;
  ett_h225_AdmissionConfirm_remoteExtensionAddress = -1;
  ett_h225_AdmissionConfirm_alternateEndpoints = -1;
  ett_h225_AdmissionConfirm_tokens = -1;
  ett_h225_AdmissionConfirm_cryptoTokens = -1;
  ett_h225_AdmissionConfirm_integrityCheckValue = -1;
  ett_h225_AdmissionConfirm_transportQOS = -1;
  hf_h225_AdmissionConfirm_willRespondToIRR = -1;
  ett_h225_AdmissionConfirm_uuiesRequested = -1;
  ett_h225_AdmissionConfirm_language = -1;
  ett_h225_AdmissionConfirm_alternateTransportAddresses = -1;
  ett_h225_AdmissionConfirm_useSpecifiedTransport = -1;
  hf_h225_LocationConfirm_requestSeqNum = -1;
  ett_h225_LocationConfirm_callSignalAddress = -1;
  ett_h225_LocationConfirm_rasAddress = -1;
  ett_h225_LocationConfirm_nonStandardData = -1;
  ett_h225_LocationConfirm_destinationInfo = -1;
  ett_h225_LocationConfirm_destExtraCallInfo = -1;
  ett_h225_LocationConfirm_destinationType = -1;
  ett_h225_LocationConfirm_remoteExtensionAddress = -1;
  ett_h225_LocationConfirm_alternateEndpoints = -1;
  ett_h225_LocationConfirm_tokens = -1;
  ett_h225_LocationConfirm_cryptoTokens = -1;
  ett_h225_LocationConfirm_integrityCheckValue = -1;
  ett_h225_LocationConfirm_alternateTransportAddresses = -1;
  ett_h225_InfoRequestResponse_nonStandardData = -1;
  hf_h225_InfoRequestResponse_requestSeqNum = -1;
  ett_h225_InfoRequestResponse_endpointType = -1;
  hf_h225_InfoRequestResponse_endpointIdentifier = -1;
  ett_h225_InfoRequestResponse_rasAddress = -1;
  ett_h225_InfoRequestResponse_callSignalAddress = -1;
  ett_h225_InfoRequestResponse_endpointAlias = -1;
  ett_h225_InfoRequestResponse_perCallInfo = -1;
  ett_h225_InfoRequestResponse_tokens = -1;
  ett_h225_InfoRequestResponse_cryptoTokens = -1;
  ett_h225_InfoRequestResponse_integrityCheckValue = -1;
  hf_h225_InfoRequestResponse_needResponse = -1;
  hf_h225_Alerting_UUIE_protocolIdentifier = -1;
  ett_h225_Alerting_UUIE_destinationInfo = -1;
  ett_h225_Alerting_UUIE_h245Address = -1;
  ett_h225_Alerting_UUIE_callIdentifier = -1;
  ett_h225_Alerting_UUIE_h245SecurityMode = -1;
  ett_h225_Alerting_UUIE_tokens = -1;
  ett_h225_Alerting_UUIE_cryptoTokens = -1;
  ett_h225_Alerting_UUIE_fastStart = -1;
  hf_h225_Alerting_UUIE_multipleCalls = -1;
  hf_h225_Alerting_UUIE_maintainConnection = -1;
  ett_h225_Alerting_UUIE_alertingAddress = -1;
  ett_h225_Alerting_UUIE_presentationIndicator = -1;
  hf_h225_Alerting_UUIE_screeningIndicator = -1;
  hf_h225_Alerting_UUIE_fastConnectRefused = -1;
  hf_h225_CallProceeding_UUIE_protocolIdentifier = -1;
  ett_h225_CallProceeding_UUIE_destinationInfo = -1;
  ett_h225_CallProceeding_UUIE_h245Address = -1;
  ett_h225_CallProceeding_UUIE_callIdentifier = -1;
  ett_h225_CallProceeding_UUIE_h245SecurityMode = -1;
  ett_h225_CallProceeding_UUIE_tokens = -1;
  ett_h225_CallProceeding_UUIE_cryptoTokens = -1;
  ett_h225_CallProceeding_UUIE_fastStart = -1;
  hf_h225_CallProceeding_UUIE_multipleCalls = -1;
  hf_h225_CallProceeding_UUIE_maintainConnection = -1;
  hf_h225_CallProceeding_UUIE_fastConnectRefused = -1;
  hf_h225_Connect_UUIE_protocolIdentifier = -1;
  ett_h225_Connect_UUIE_h245Address = -1;
  ett_h225_Connect_UUIE_destinationInfo = -1;
  hf_h225_Connect_UUIE_conferenceID = -1;
  ett_h225_Connect_UUIE_callIdentifier = -1;
  ett_h225_Connect_UUIE_h245SecurityMode = -1;
  ett_h225_Connect_UUIE_tokens = -1;
  ett_h225_Connect_UUIE_cryptoTokens = -1;
  ett_h225_Connect_UUIE_fastStart = -1;
  hf_h225_Connect_UUIE_multipleCalls = -1;
  hf_h225_Connect_UUIE_maintainConnection = -1;
  ett_h225_Connect_UUIE_language = -1;
  ett_h225_Connect_UUIE_connectedAddress = -1;
  ett_h225_Connect_UUIE_presentationIndicator = -1;
  hf_h225_Connect_UUIE_screeningIndicator = -1;
  hf_h225_Connect_UUIE_fastConnectRefused = -1;
  hf_h225_Setup_UUIE_protocolIdentifier = -1;
  ett_h225_Setup_UUIE_h245Address = -1;
  ett_h225_Setup_UUIE_sourceAddress = -1;
  ett_h225_Setup_UUIE_sourceInfo = -1;
  ett_h225_Setup_UUIE_destinationAddress = -1;
  ett_h225_Setup_UUIE_destCallSignalAddress = -1;
  ett_h225_Setup_UUIE_destExtraCallInfo = -1;
  ett_h225_Setup_UUIE_destExtraCRV = -1;
  hf_h225_Setup_UUIE_activeMC = -1;
  hf_h225_Setup_UUIE_conferenceID = -1;
  ett_h225_Setup_UUIE_conferenceGoal = -1;
  ett_h225_Setup_UUIE_callServices = -1;
  ett_h225_Setup_UUIE_callType = -1;
  ett_h225_Setup_UUIE_sourceCallSignalAddress = -1;
  ett_h225_Setup_UUIE_remoteExtensionAddress = -1;
  ett_h225_Setup_UUIE_callIdentifier = -1;
  ett_h225_Setup_UUIE_h245SecurityCapability = -1;
  ett_h225_Setup_UUIE_tokens = -1;
  ett_h225_Setup_UUIE_cryptoTokens = -1;
  ett_h225_Setup_UUIE_fastStart = -1;
  hf_h225_Setup_UUIE_mediaWaitForConnect = -1;
  hf_h225_Setup_UUIE_canOverlapSend = -1;
  hf_h225_Setup_UUIE_endpointIdentifier = -1;
  hf_h225_Setup_UUIE_multipleCalls = -1;
  hf_h225_Setup_UUIE_maintainConnection = -1;
  ett_h225_Setup_UUIE_connectionParameters = -1;
  ett_h225_Setup_UUIE_language = -1;
  ett_h225_Setup_UUIE_presentationIndicator = -1;
  hf_h225_Setup_UUIE_screeningIndicator = -1;
  hf_h225_Progress_UUIE_protocolIdentifier = -1;
  ett_h225_Progress_UUIE_destinationInfo = -1;
  ett_h225_Progress_UUIE_h245Address = -1;
  ett_h225_Progress_UUIE_callIdentifier = -1;
  ett_h225_Progress_UUIE_h245SecurityMode = -1;
  ett_h225_Progress_UUIE_tokens = -1;
  ett_h225_Progress_UUIE_cryptoTokens = -1;
  ett_h225_Progress_UUIE_fastStart = -1;
  hf_h225_Progress_UUIE_multipleCalls = -1;
  hf_h225_Progress_UUIE_maintainConnection = -1;
  hf_h225_Progress_UUIE_fastConnectRefused = -1;
};



// End of h225_container1.cpp
