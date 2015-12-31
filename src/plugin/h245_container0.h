/* 
 * h245_container0.h
 *
 * Headers for saving the ID's for Ethereal protocol items
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
// h245_container0.h
//
// Code automatically generated by asnparse.
//

#ifndef H245_INTEGER_CONTAINER_0_H
#define  H245_INTEGER_CONTAINER_0_H

class H245_0_Integer_Container
{
  public:
    H245_0_Integer_Container();
    int ett_proto_H245; // Protocol itself
    int hf_proto_H245;  // Protocol itself
    int ett_h245_MultimediaSystemControlMessage_choice;
    int ett_h245_RequestMessage_choice;
    int ett_h245_ResponseMessage_choice;
    int ett_h245_CommandMessage_choice;
    int ett_h245_IndicationMessage_choice;
    int hf_h245_NonStandardIdentifier_object;
    int ett_h245_NonStandardIdentifier_choice;
    int hf_h245_MasterSlaveDetermination_terminalType;
    int hf_h245_MasterSlaveDetermination_statusDeterminationNumber;
    int hf_h245_AlternativeCapabilitySet_array;
    int hf_h245_TerminalCapabilitySetAck_sequenceNumber;
    int hf_h245_Capability_h233EncryptionTransmitCapability;
    int hf_h245_Capability_maxPendingReplacementFor;
    int ett_h245_Capability_choice;
    int ett_h245_MultiplexCapability_choice;
    int hf_h245_H223AnnexCCapability_videoWithAL1M;
    int hf_h245_H223AnnexCCapability_videoWithAL2M;
    int hf_h245_H223AnnexCCapability_videoWithAL3M;
    int hf_h245_H223AnnexCCapability_audioWithAL1M;
    int hf_h245_H223AnnexCCapability_audioWithAL2M;
    int hf_h245_H223AnnexCCapability_audioWithAL3M;
    int hf_h245_H223AnnexCCapability_dataWithAL1M;
    int hf_h245_H223AnnexCCapability_dataWithAL2M;
    int hf_h245_H223AnnexCCapability_dataWithAL3M;
    int hf_h245_H223AnnexCCapability_alpduInterleaving;
    int hf_h245_H223AnnexCCapability_maximumAL1MPDUSize;
    int hf_h245_H223AnnexCCapability_maximumAL2MSDUSize;
    int hf_h245_H223AnnexCCapability_maximumAL3MSDUSize;
    int hf_h245_V75Capability_audioHeader;
    int hf_h245_QOSMode_guaranteedQOS;
    int hf_h245_QOSMode_controlledLoad;
    int hf_h245_ATMParameters_maxNTUSize;
    int hf_h245_ATMParameters_atmUBR;
    int hf_h245_ATMParameters_atmrtVBR;
    int hf_h245_ATMParameters_atmnrtVBR;
    int hf_h245_ATMParameters_atmABR;
    int hf_h245_ATMParameters_atmCBR;
    int hf_h245_MediaTransportType_ip_UDP;
    int hf_h245_MediaTransportType_ip_TCP;
    int hf_h245_MediaTransportType_atm_AAL5_UNIDIR;
    int hf_h245_MediaTransportType_atm_AAL5_BIDIR;
    int ett_h245_MediaChannelCapability_mediaTransport;
    int hf_h245_RedundancyEncodingMethod_rtpAudioRedundancyEncoding;
    int ett_h245_RedundancyEncodingMethod_choice;
    int ett_h245_VideoCapability_choice;
    int hf_h245_H261VideoCapability_qcifMPI;
    int hf_h245_H261VideoCapability_cifMPI;
    int hf_h245_H261VideoCapability_temporalSpatialTradeOffCapability;
    int hf_h245_H261VideoCapability_maxBitRate;
    int hf_h245_H261VideoCapability_stillImageTransmission;
    int hf_h245_H262VideoCapability_profileAndLevel_SPatML;
    int hf_h245_H262VideoCapability_profileAndLevel_MPatLL;
    int hf_h245_H262VideoCapability_profileAndLevel_MPatML;
    int hf_h245_H262VideoCapability_profileAndLevel_MPatH_14;
    int hf_h245_H262VideoCapability_profileAndLevel_MPatHL;
    int hf_h245_H262VideoCapability_profileAndLevel_SNRatLL;
    int hf_h245_H262VideoCapability_profileAndLevel_SNRatML;
    int hf_h245_H262VideoCapability_profileAndLevel_SpatialatH_14;
    int hf_h245_H262VideoCapability_profileAndLevel_HPatML;
    int hf_h245_H262VideoCapability_profileAndLevel_HPatH_14;
    int hf_h245_H262VideoCapability_profileAndLevel_HPatHL;
    int hf_h245_H262VideoCapability_videoBitRate;
    int hf_h245_H262VideoCapability_vbvBufferSize;
    int hf_h245_H262VideoCapability_samplesPerLine;
    int hf_h245_H262VideoCapability_linesPerFrame;
    int hf_h245_H262VideoCapability_framesPerSecond;
    int hf_h245_H262VideoCapability_luminanceSampleRate;
    int hf_h245_TransparencyParameters_presentationOrder;
    int hf_h245_TransparencyParameters_offset_x;
    int hf_h245_TransparencyParameters_offset_y;
    int hf_h245_TransparencyParameters_scale_x;
    int hf_h245_TransparencyParameters_scale_y;
    int hf_h245_CustomPictureClockFrequency_clockConversionCode;
    int hf_h245_CustomPictureClockFrequency_clockDivisor;
    int hf_h245_CustomPictureClockFrequency_sqcifMPI;
    int hf_h245_CustomPictureClockFrequency_qcifMPI;
    int hf_h245_CustomPictureClockFrequency_cifMPI;
    int hf_h245_CustomPictureClockFrequency_cif4MPI;
    int hf_h245_CustomPictureClockFrequency_cif16MPI;
    int hf_h245_H263ModeComboFlags_unrestrictedVector;
    int hf_h245_H263ModeComboFlags_arithmeticCoding;
    int hf_h245_H263ModeComboFlags_advancedPrediction;
    int hf_h245_H263ModeComboFlags_pbFrames;
    int hf_h245_H263ModeComboFlags_advancedIntraCodingMode;
    int hf_h245_H263ModeComboFlags_deblockingFilterMode;
    int hf_h245_H263ModeComboFlags_unlimitedMotionVectors;
    int hf_h245_H263ModeComboFlags_slicesInOrder_NonRect;
    int hf_h245_H263ModeComboFlags_slicesInOrder_Rect;
    int hf_h245_H263ModeComboFlags_slicesNoOrder_NonRect;
    int hf_h245_H263ModeComboFlags_slicesNoOrder_Rect;
    int hf_h245_H263ModeComboFlags_improvedPBFramesMode;
    int hf_h245_H263ModeComboFlags_referencePicSelect;
    int hf_h245_H263ModeComboFlags_dynamicPictureResizingByFour;
    int hf_h245_H263ModeComboFlags_dynamicPictureResizingSixteenthPel;
    int hf_h245_H263ModeComboFlags_dynamicWarpingHalfPel;
    int hf_h245_H263ModeComboFlags_dynamicWarpingSixteenthPel;
    int hf_h245_H263ModeComboFlags_reducedResolutionUpdate;
    int hf_h245_H263ModeComboFlags_independentSegmentDecoding;
    int hf_h245_H263ModeComboFlags_alternateInterVLCMode;
    int hf_h245_H263ModeComboFlags_modifiedQuantizationMode;
    int hf_h245_IS11172VideoCapability_constrainedBitstream;
    int hf_h245_IS11172VideoCapability_videoBitRate;
    int hf_h245_IS11172VideoCapability_vbvBufferSize;
    int hf_h245_IS11172VideoCapability_samplesPerLine;
    int hf_h245_IS11172VideoCapability_linesPerFrame;
    int hf_h245_IS11172VideoCapability_pictureRate;
    int hf_h245_IS11172VideoCapability_luminanceSampleRate;
    int hf_h245_AudioCapability_g711Alaw64k;
    int hf_h245_AudioCapability_g711Alaw56k;
    int hf_h245_AudioCapability_g711Ulaw64k;
    int hf_h245_AudioCapability_g711Ulaw56k;
    int hf_h245_AudioCapability_g722_64k;
    int hf_h245_AudioCapability_g722_56k;
    int hf_h245_AudioCapability_g722_48k;
    int hf_h245_AudioCapability_g728;
    int hf_h245_AudioCapability_g729;
    int hf_h245_AudioCapability_g729AnnexA;
    int hf_h245_AudioCapability_g729wAnnexB;
    int hf_h245_AudioCapability_g729AnnexAwAnnexB;
    int ett_h245_AudioCapability_choice;
    int hf_h245_IS11172AudioCapability_audioLayer1;
    int hf_h245_IS11172AudioCapability_audioLayer2;
    int hf_h245_IS11172AudioCapability_audioLayer3;
    int hf_h245_IS11172AudioCapability_audioSampling32k;
    int hf_h245_IS11172AudioCapability_audioSampling44k1;
    int hf_h245_IS11172AudioCapability_audioSampling48k;
    int hf_h245_IS11172AudioCapability_singleChannel;
    int hf_h245_IS11172AudioCapability_twoChannels;
    int hf_h245_IS11172AudioCapability_bitRate;
    int hf_h245_IS13818AudioCapability_audioLayer1;
    int hf_h245_IS13818AudioCapability_audioLayer2;
    int hf_h245_IS13818AudioCapability_audioLayer3;
    int hf_h245_IS13818AudioCapability_audioSampling16k;
    int hf_h245_IS13818AudioCapability_audioSampling22k05;
    int hf_h245_IS13818AudioCapability_audioSampling24k;
    int hf_h245_IS13818AudioCapability_audioSampling32k;
    int hf_h245_IS13818AudioCapability_audioSampling44k1;
    int hf_h245_IS13818AudioCapability_audioSampling48k;
    int hf_h245_IS13818AudioCapability_singleChannel;
    int hf_h245_IS13818AudioCapability_twoChannels;
    int hf_h245_IS13818AudioCapability_threeChannels2_1;
    int hf_h245_IS13818AudioCapability_threeChannels3_0;
    int hf_h245_IS13818AudioCapability_fourChannels2_0_2_0;
    int hf_h245_IS13818AudioCapability_fourChannels2_2;
    int hf_h245_IS13818AudioCapability_fourChannels3_1;
    int hf_h245_IS13818AudioCapability_fiveChannels3_0_2_0;
    int hf_h245_IS13818AudioCapability_fiveChannels3_2;
    int hf_h245_IS13818AudioCapability_lowFrequencyEnhancement;
    int hf_h245_IS13818AudioCapability_multilingual;
    int hf_h245_IS13818AudioCapability_bitRate;
    int hf_h245_GSMAudioCapability_audioUnitSize;
    int hf_h245_GSMAudioCapability_comfortNoise;
    int hf_h245_GSMAudioCapability_scrambled;
    int hf_h245_DataProtocolCapability_v14buffered;
    int hf_h245_DataProtocolCapability_v42lapm;
    int hf_h245_DataProtocolCapability_hdlcFrameTunnelling;
    int hf_h245_DataProtocolCapability_h310SeparateVCStack;
    int hf_h245_DataProtocolCapability_h310SingleVCStack;
    int hf_h245_DataProtocolCapability_transparent;
    int hf_h245_DataProtocolCapability_segmentationAndReassembly;
    int hf_h245_DataProtocolCapability_hdlcFrameTunnelingwSAR;
    int hf_h245_DataProtocolCapability_v120;
    int hf_h245_DataProtocolCapability_separateLANStack;
    int hf_h245_DataProtocolCapability_tcp;
    int hf_h245_DataProtocolCapability_udp;
    int ett_h245_DataProtocolCapability_choice;
    int ett_h245_CompressionType_choice;
    int hf_h245_V42bis_numberOfCodewords;
    int hf_h245_V42bis_maximumStringLength;
    int hf_h245_T84Profile_t84Unrestricted;
    int ett_h245_T84Profile_choice;
    int hf_h245_T38FaxProfile_fillBitRemoval;
    int hf_h245_T38FaxProfile_transcodingJBIG;
    int hf_h245_T38FaxProfile_transcodingMMR;
    int ett_h245_EncryptionCapability;
    int hf_h245_MediaEncryptionAlgorithm_algorithm;
    int ett_h245_MediaEncryptionAlgorithm_choice;
    int hf_h245_UserInputCapability_basicString;
    int hf_h245_UserInputCapability_iA5String;
    int hf_h245_UserInputCapability_generalString;
    int hf_h245_UserInputCapability_dtmf;
    int hf_h245_UserInputCapability_hookflash;
    int ett_h245_UserInputCapability_choice;
    int hf_h245_V75Parameters_audioHeaderPresent;
    int hf_h245_DataType_nullData;
    int ett_h245_DataType_choice;
    int hf_h245_H222LogicalChannelParameters_resourceID;
    int hf_h245_H222LogicalChannelParameters_subChannelID;
    int hf_h245_H222LogicalChannelParameters_pcr_pid;
    int hf_h245_H222LogicalChannelParameters_programDescriptors;
    int hf_h245_H222LogicalChannelParameters_streamDescriptors;
    int hf_h245_CRCLength_crc8bit;
    int hf_h245_CRCLength_crc16bit;
    int hf_h245_CRCLength_crc32bit;
    int ett_h245_RedundancyEncoding_redundancyEncodingMethod;
    int ett_h245_RedundancyEncoding_secondaryEncoding;
    int ett_h245_TransportAddress_choice;
    int hf_h245_UnicastAddress_netBios;
    int hf_h245_UnicastAddress_nsap;
    int ett_h245_UnicastAddress_choice;
    int hf_h245_MulticastAddress_nsap;
    int ett_h245_MulticastAddress_choice;
    int hf_h245_EscrowData_escrowID;
    int hf_h245_EscrowData_escrowValue;
    int hf_h245_OpenLogicalChannelConfirm_forwardLogicalChannelNumber;
    int hf_h245_CloseLogicalChannelAck_forwardLogicalChannelNumber;
    int hf_h245_RequestChannelCloseAck_forwardLogicalChannelNumber;
    int hf_h245_RequestChannelCloseRelease_forwardLogicalChannelNumber;
    int ett_h245_ModeDescription;
    int hf_h245_V76ModeParameters_suspendResumewAddress;
    int hf_h245_V76ModeParameters_suspendResumewoAddress;
    int ett_h245_VideoMode_choice;
    int hf_h245_IS11172VideoMode_constrainedBitstream;
    int hf_h245_IS11172VideoMode_videoBitRate;
    int hf_h245_IS11172VideoMode_vbvBufferSize;
    int hf_h245_IS11172VideoMode_samplesPerLine;
    int hf_h245_IS11172VideoMode_linesPerFrame;
    int hf_h245_IS11172VideoMode_pictureRate;
    int hf_h245_IS11172VideoMode_luminanceSampleRate;
    int hf_h245_AudioMode_g711Alaw64k;
    int hf_h245_AudioMode_g711Alaw56k;
    int hf_h245_AudioMode_g711Ulaw64k;
    int hf_h245_AudioMode_g711Ulaw56k;
    int hf_h245_AudioMode_g722_64k;
    int hf_h245_AudioMode_g722_56k;
    int hf_h245_AudioMode_g722_48k;
    int hf_h245_AudioMode_g728;
    int hf_h245_AudioMode_g729;
    int hf_h245_AudioMode_g729AnnexA;
    int hf_h245_AudioMode_g729wAnnexB;
    int hf_h245_AudioMode_g729AnnexAwAnnexB;
    int ett_h245_AudioMode_choice;
    int hf_h245_EncryptionMode_h233Encryption;
    int ett_h245_EncryptionMode_choice;
    int hf_h245_RoundTripDelayRequest_sequenceNumber;
    int hf_h245_RoundTripDelayResponse_sequenceNumber;
    int ett_h245_CommunicationModeResponse_choice;
    int hf_h245_ConferenceRequest_terminalListRequest;
    int hf_h245_ConferenceRequest_makeMeChair;
    int hf_h245_ConferenceRequest_cancelMakeMeChair;
    int hf_h245_ConferenceRequest_enterH243Password;
    int hf_h245_ConferenceRequest_enterH243TerminalID;
    int hf_h245_ConferenceRequest_enterH243ConferenceID;
    int hf_h245_ConferenceRequest_enterExtensionAddress;
    int hf_h245_ConferenceRequest_requestChairTokenOwner;
    int hf_h245_ConferenceRequest_broadcastMyLogicalChannel;
    int hf_h245_ConferenceRequest_requestAllTerminalIDs;
    int ett_h245_ConferenceRequest_choice;
    int ett_h245_CertSelectionCriteria;
    int hf_h245_Criteria_field;
    int hf_h245_Criteria_value;
    int hf_h245_ConferenceResponse_videoCommandReject;
    int hf_h245_ConferenceResponse_terminalDropReject;
    int ett_h245_ConferenceResponse_choice;
    int hf_h245_RemoteMCRequest_masterActivate;
    int hf_h245_RemoteMCRequest_slaveActivate;
    int hf_h245_RemoteMCRequest_deActivate;
    int hf_h245_RemoteMCResponse_accept;
    int ett_h245_RemoteMCResponse_choice;
    int ett_h245_MultilinkRequest_choice;
    int ett_h245_MultilinkResponse_choice;
    int ett_h245_MultilinkIndication_choice;
    int hf_h245_DiallingInformation_infoNotAvailable;
    int ett_h245_DiallingInformation_choice;
    int hf_h245_DiallingInformationNetworkType_n_isdn;
    int hf_h245_DiallingInformationNetworkType_gstn;
    int ett_h245_DiallingInformationNetworkType_choice;
    int hf_h245_ConnectionIdentifier_channelTag;
    int hf_h245_ConnectionIdentifier_sequenceNumber;
    int hf_h245_SendTerminalCapabilitySet_genericRequest;
    int ett_h245_SendTerminalCapabilitySet_choice;
    int hf_h245_EncryptionCommand_encryptionSE;
    int hf_h245_EncryptionCommand_encryptionIVRequest;
    int ett_h245_EncryptionCommand_choice;
    int hf_h245_EndSessionCommand_disconnect;
    int ett_h245_EndSessionCommand_choice;
    int hf_h245_ConferenceCommand_broadcastMyLogicalChannel;
    int hf_h245_ConferenceCommand_cancelBroadcastMyLogicalChannel;
    int hf_h245_ConferenceCommand_cancelMakeTerminalBroadcaster;
    int hf_h245_ConferenceCommand_cancelSendThisSource;
    int hf_h245_ConferenceCommand_dropConference;
    int ett_h245_ConferenceCommand_choice;
    int hf_h245_SubstituteConferenceIDCommand_conferenceIdentifier;
    int hf_h245_KeyProtectionMethod_secureChannel;
    int hf_h245_KeyProtectionMethod_sharedSecret;
    int hf_h245_KeyProtectionMethod_certProtectedKey;
    int ett_h245_EncryptionUpdateRequest_keyProtectionMethod;
    int ett_h245_H223MultiplexReconfiguration_choice;
    int ett_h245_FunctionNotUnderstood_choice;
    int hf_h245_ConferenceIndication_sbeNumber;
    int hf_h245_ConferenceIndication_seenByAtLeastOneOther;
    int hf_h245_ConferenceIndication_cancelSeenByAtLeastOneOther;
    int hf_h245_ConferenceIndication_seenByAll;
    int hf_h245_ConferenceIndication_cancelSeenByAll;
    int hf_h245_ConferenceIndication_requestForFloor;
    int hf_h245_ConferenceIndication_withdrawChairToken;
    int ett_h245_ConferenceIndication_choice;
    int hf_h245_H223SkewIndication_logicalChannelNumber1;
    int hf_h245_H223SkewIndication_logicalChannelNumber2;
    int hf_h245_H223SkewIndication_skew;
    int hf_h245_H2250MaximumSkewIndication_logicalChannelNumber1;
    int hf_h245_H2250MaximumSkewIndication_logicalChannelNumber2;
    int hf_h245_H2250MaximumSkewIndication_maximumSkew;
    int ett_h245_MCLocationIndication_signalAddress;
    int ett_h245_VendorIdentification_vendor;
    int hf_h245_VendorIdentification_productNumber;
    int hf_h245_VendorIdentification_versionNumber;
    int hf_h245_UserInputIndication_alphanumeric;
    int ett_h245_UserInputIndication_choice;
    int hf_h245_NonStandardIdentifier_h221NonStandard_t35CountryCode;
    int hf_h245_NonStandardIdentifier_h221NonStandard_t35Extension;
    int hf_h245_NonStandardIdentifier_h221NonStandard_manufacturerCode;
    int hf_h245_MasterSlaveDeterminationAck_decision_master;
    int hf_h245_MasterSlaveDeterminationAck_decision_slave;
    int hf_h245_MasterSlaveDeterminationReject_cause_identicalNumbers;
    int ett_h245_ArrayOf_CapabilityTableEntry;
    int ett_h245_ArrayOf_CapabilityDescriptor;
    int ett_h245_ArrayOf_AlternativeCapabilitySet;
    int hf_h245_TerminalCapabilitySetReject_cause_unspecified;
    int hf_h245_TerminalCapabilitySetReject_cause_undefinedTableEntryUsed;
    int hf_h245_TerminalCapabilitySetReject_cause_descriptorCapacityExceeded;
    int ett_h245_TerminalCapabilitySetReject_cause_choice;
    int hf_h245_Capability_h233EncryptionReceiveCapability_h233IVResponseTime;
    int ett_h245_ArrayOf_VCCapability;
    int hf_h245_VCCapability_aal1_nullClockRecovery;
    int hf_h245_VCCapability_aal1_srtsClockRecovery;
    int hf_h245_VCCapability_aal1_adaptiveClockRecovery;
    int hf_h245_VCCapability_aal1_nullErrorCorrection;
    int hf_h245_VCCapability_aal1_longInterleaver;
    int hf_h245_VCCapability_aal1_shortInterleaver;
    int hf_h245_VCCapability_aal1_errorCorrectionOnly;
    int hf_h245_VCCapability_aal1_structuredDataTransfer;
    int hf_h245_VCCapability_aal1_partiallyFilledCells;
    int hf_h245_VCCapability_aal5_forwardMaximumSDUSize;
    int hf_h245_VCCapability_aal5_backwardMaximumSDUSize;
    int hf_h245_H223Capability_h223MultiplexTableCapability_basic;
    int ett_h245_H223Capability_h223MultiplexTableCapability_choice;
    int hf_h245_H223Capability_mobileOperationTransmitCapability_modeChangeCapability;
    int hf_h245_H223Capability_mobileOperationTransmitCapability_h223AnnexA;
    int hf_h245_H223Capability_mobileOperationTransmitCapability_h223AnnexADoubleFlag;
    int hf_h245_H223Capability_mobileOperationTransmitCapability_h223AnnexB;
    int hf_h245_H223Capability_mobileOperationTransmitCapability_h223AnnexBwithHeader;
    int hf_h245_H2250Capability_mcCapability_centralizedConferenceMC;
    int hf_h245_H2250Capability_mcCapability_decentralizedConferenceMC;
    int ett_h245_ArrayOf_RedundancyEncodingCapability;
    int ett_h245_ArrayOf_RTPPayloadType;
    int ett_h245_ArrayOf_QOSCapability;
    int ett_h245_ArrayOf_MediaChannelCapability;
    int hf_h245_ArrayOf_CapabilityTableEntryNumber_array;
    int hf_h245_RTPH263VideoRedundancyEncoding_frameToThreadMapping_roundrobin;
    int ett_h245_RTPH263VideoRedundancyEncoding_frameToThreadMapping_choice;
    int hf_h245_RTPH263VideoRedundancyEncoding_containedThreads_array;
    int hf_h245_RTPH263VideoRedundancyFrameMapping_frameSequence_array;
    int ett_h245_ArrayOf_MediaDistributionCapability;
    int ett_h245_ArrayOf_DataApplicationCapability;
    int ett_h245_ArrayOf_EnhancementOptions;
    int ett_h245_ArrayOf_BEnhancementParameters;
    int ett_h245_ArrayOf_CustomPictureClockFrequency;
    int ett_h245_ArrayOf_CustomPictureFormat;
    int ett_h245_ArrayOf_H263VideoModeCombos;
    int hf_h245_RefPictureSelection_additionalPictureMemory_sqcifAdditionalPictureMemory;
    int hf_h245_RefPictureSelection_additionalPictureMemory_qcifAdditionalPictureMemory;
    int hf_h245_RefPictureSelection_additionalPictureMemory_cifAdditionalPictureMemory;
    int hf_h245_RefPictureSelection_additionalPictureMemory_cif4AdditionalPictureMemory;
    int hf_h245_RefPictureSelection_additionalPictureMemory_cif16AdditionalPictureMemory;
    int hf_h245_RefPictureSelection_additionalPictureMemory_bigCpfAdditionalPictureMemory;
    int hf_h245_RefPictureSelection_videoBackChannelSend_none;
    int hf_h245_RefPictureSelection_videoBackChannelSend_ackMessageOnly;
    int hf_h245_RefPictureSelection_videoBackChannelSend_nackMessageOnly;
    int hf_h245_RefPictureSelection_videoBackChannelSend_ackOrNackMessageOnly;
    int hf_h245_RefPictureSelection_videoBackChannelSend_ackAndNackMessage;
    int hf_h245_CustomPictureFormat_pixelAspectInformation_anyPixelAspectRatio;
    int ett_h245_CustomPictureFormat_pixelAspectInformation_choice;
    int ett_h245_ArrayOf_H263ModeComboFlags;
    int hf_h245_AudioCapability_g7231_maxAl_sduAudioFrames;
    int hf_h245_AudioCapability_g7231_silenceSuppression;
    int hf_h245_G7231AnnexCCapability_g723AnnexCAudioMode_highRateMode0;
    int hf_h245_G7231AnnexCCapability_g723AnnexCAudioMode_highRateMode1;
    int hf_h245_G7231AnnexCCapability_g723AnnexCAudioMode_lowRateMode0;
    int hf_h245_G7231AnnexCCapability_g723AnnexCAudioMode_lowRateMode1;
    int hf_h245_G7231AnnexCCapability_g723AnnexCAudioMode_sidMode0;
    int hf_h245_G7231AnnexCCapability_g723AnnexCAudioMode_sidMode1;
    int hf_h245_DataApplicationCapability_application_dsvdControl;
    int ett_h245_DataApplicationCapability_application_choice;
    int ett_h245_DataProtocolCapability_v76wCompression_choice;
    int hf_h245_T84Profile_t84Restricted_qcif;
    int hf_h245_T84Profile_t84Restricted_cif;
    int hf_h245_T84Profile_t84Restricted_ccir601Seq;
    int hf_h245_T84Profile_t84Restricted_ccir601Prog;
    int hf_h245_T84Profile_t84Restricted_hdtvSeq;
    int hf_h245_T84Profile_t84Restricted_hdtvProg;
    int hf_h245_T84Profile_t84Restricted_g3FacsMH200x100;
    int hf_h245_T84Profile_t84Restricted_g3FacsMH200x200;
    int hf_h245_T84Profile_t84Restricted_g4FacsMMR200x100;
    int hf_h245_T84Profile_t84Restricted_g4FacsMMR200x200;
    int hf_h245_T84Profile_t84Restricted_jbig200x200Seq;
    int hf_h245_T84Profile_t84Restricted_jbig200x200Prog;
    int hf_h245_T84Profile_t84Restricted_jbig300x300Seq;
    int hf_h245_T84Profile_t84Restricted_jbig300x300Prog;
    int hf_h245_T84Profile_t84Restricted_digPhotoLow;
  private:
};

#endif // end of header file


// End of h245_container0.h
