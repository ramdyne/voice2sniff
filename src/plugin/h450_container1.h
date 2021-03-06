/* 
 * h450_container1.h
 *
 * Sources for saving the ID's for Ethereal protocol items
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
// h450_container1.h
//
// Code automatically generated by asnparse.
//

#ifndef H450_INTEGER_CONTAINER_1_H
#define  H450_INTEGER_CONTAINER_1_H

class H450_1_Integer_Container
{
  public:
    H450_1_Integer_Container();

    int ett_h450_ROS_choice;
    int hf_h450_Code_local;
    int hf_h450_Code_global;
    int hf_h450_EntityType_endpoint;
    int hf_h450_EntityType_anyEntity;
    int hf_h450_InterpretationApdu_discardAnyUnrecognizedInvokePdu;
    int hf_h450_InterpretationApdu_clearCallIfAnyInvokePduNotRecognized;
    int hf_h450_InterpretationApdu_rejectAnyUnrecognizedInvokePdu;
    int ett_h450_ServiceApdus_choice;
    int hf_h450_PresentedAddressScreened_presentationRestricted;
    int hf_h450_PresentedAddressScreened_numberNotAvailableDueToInterworking;
    int ett_h450_PresentedAddressScreened_choice;
    int hf_h450_PresentedAddressUnscreened_presentationRestricted;
    int hf_h450_PresentedAddressUnscreened_numberNotAvailableDueToInterworking;
    int ett_h450_PresentedAddressUnscreened_choice;
    int hf_h450_PresentedNumberScreened_presentationRestricted;
    int hf_h450_PresentedNumberScreened_numberNotAvailableDueToInterworking;
    int ett_h450_PresentedNumberScreened_choice;
    int hf_h450_PresentedNumberUnscreened_presentationRestricted;
    int hf_h450_PresentedNumberUnscreened_numberNotAvailableDueToInterworking;
    int ett_h450_PresentedNumberUnscreened_choice;
    int hf_h450_PartySubaddress_nsapSubaddress;
    int ett_h450_PartySubaddress_choice;
    int hf_h450_ScreeningIndicator_enum;
    int ett_h450_ScreeningIndicator;
    int hf_h450_GeneralErrorList_enum;
    int ett_h450_GeneralErrorList;
    int ett_h450_Extension_extensionId;
    int hf_h450_Extension_extensionArgument;
    int hf_h450_OperationName_enum;
    int ett_h450_OperationName;
    int ett_h450_MixedExtension_choice;
    int ett_h450_CcArg_choice;
    int hf_h450_CallCompletionErrors_enum;
    int ett_h450_CallCompletionErrors;
    int hf_h450_Name_nameNotAvailable;
    int ett_h450_Name_choice;
    int hf_h450_NamePresentationAllowed_simpleName;
    int hf_h450_NamePresentationAllowed_extendedName;
    int hf_h450_NamePresentationRestricted_simpleName;
    int hf_h450_NamePresentationRestricted_extendedName;
    int hf_h450_NamePresentationRestricted_restrictedNull;
    int ett_h450_DummyRes;
    int ett_h450_MWIInterrogateRes;
    int hf_h450_MsgCentreId_integer;
    int hf_h450_MsgCentreId_numericString;
    int ett_h450_MsgCentreId_choice;
    int hf_h450_MessageWaitingIndicationErrors_enum;
    int ett_h450_MessageWaitingIndicationErrors;
    int hf_h450_BasicService_enum;
    int ett_h450_BasicService;
    int hf_h450_ParkCondition_enum;
    int ett_h450_ParkCondition;
    int hf_h450_CallType_enum;
    int ett_h450_CallType;
    int hf_h450_CallPickupErrors_enum;
    int ett_h450_CallPickupErrors;
    int hf_h450_DiversionReason_enum;
    int ett_h450_DiversionReason;
    int ett_h450_IntResultList;
    int hf_h450_Procedure_enum;
    int ett_h450_Procedure;
    int hf_h450_SubscriptionOption_enum;
    int ett_h450_SubscriptionOption;
    int hf_h450_CallDiversionErrors_enum;
    int ett_h450_CallDiversionErrors;
    int ett_h450_DummyArg_choice;
    int hf_h450_EndDesignation_enum;
    int ett_h450_EndDesignation;
    int hf_h450_CallStatus_enum;
    int ett_h450_CallStatus;
    int ett_h450_ExtensionSeq;
    int hf_h450_CallTransferOperation_enum;
    int ett_h450_CallTransferOperation;
    int hf_h450_CallTransferErrors_enum;
    int ett_h450_CallTransferErrors;
    int hf_h450_CIStatusInformation_callIntrusionImpending;
    int hf_h450_CIStatusInformation_callIntruded;
    int hf_h450_CIStatusInformation_callIsolated;
    int hf_h450_CIStatusInformation_callForceReleased;
    int hf_h450_CIStatusInformation_callIntrusionComplete;
    int hf_h450_CIStatusInformation_callIntrusionEnd;
    int hf_h450_CallIntrusionErrors_enum;
    int ett_h450_CallIntrusionErrors;
    int ett_h450_ReturnResult_result_opcode;
    int hf_h450_ReturnResult_result_result;
    int hf_h450_Reject_problem_general;
    int hf_h450_Reject_problem_invoke;
    int hf_h450_Reject_problem_returnResult;
    int hf_h450_Reject_problem_returnError;
    int ett_h450_ArrayOf_ROS;
    int ett_h450_ArrayOf_AliasAddress;
    int ett_h450_ArrayOf_MixedExtension;
    int ett_h450_IntResult_extension_choice;
    int ett_h450_CTInitiateArg_argumentExtension_choice;
    int ett_h450_CTSetupArg_argumentExtension_choice;
    int ett_h450_CTIdentifyRes_resultExtension_choice;
    int ett_h450_CTUpdateArg_argumentExtension_choice;
    int ett_h450_SubaddressTransferArg_argumentExtension_choice;
    int ett_h450_CTCompleteArg_argumentExtension_choice;
    int ett_h450_CTActiveArg_argumentExtension_choice;
    int hf_h450_Invoke_invokeId;
    int hf_h450_Invoke_linkedId;
    int ett_h450_Invoke_opcode;
    int hf_h450_Invoke_argument;
    int ett_h450_Invoke_argument;
    int hf_h450_ReturnResult_invokeId;
    int ett_h450_ReturnResult_result;
    int hf_h450_ReturnError_invokeId;
    int ett_h450_ReturnError_errorCode;
    int hf_h450_ReturnError_parameter;
    int hf_h450_Reject_invokeId;
    int ett_h450_Reject_problem;
    int ett_h450_NetworkFacilityExtension_sourceEntity;
    int ett_h450_NetworkFacilityExtension_sourceEntityAddress;
    int ett_h450_NetworkFacilityExtension_destinationEntity;
    int ett_h450_NetworkFacilityExtension_destinationEntityAddress;
    int ett_h450_AddressScreened_partyNumber;
    int ett_h450_AddressScreened_screeningIndicator;
    int ett_h450_AddressScreened_partySubaddress;
    int ett_h450_NumberScreened_partyNumber;
    int ett_h450_NumberScreened_screeningIndicator;
    int ett_h450_Address_partyNumber;
    int ett_h450_Address_partySubaddress;
    int ett_h450_EndpointAddress_destinationAddress;
    int ett_h450_EndpointAddress_remoteExtensionAddress;
    int hf_h450_UserSpecifiedSubaddress_subaddressInformation;
    int hf_h450_UserSpecifiedSubaddress_oddCountIndicator;
    int ett_h450_HoldNotificArg_extensionArg;
    int ett_h450_RetrieveNotificArg_extensionArg;
    int ett_h450_RemoteHoldArg_extensionArg;
    int ett_h450_RemoteHoldRes_extensionRes;
    int ett_h450_RemoteRetrieveArg_extensionArg;
    int ett_h450_RemoteRetrieveRes_extensionRes;
    int ett_h450_CcRequestArg_numberA;
    int ett_h450_CcRequestArg_numberB;
    int ett_h450_CcRequestArg_ccIdentifier;
    int ett_h450_CcRequestArg_service;
    int hf_h450_CcRequestArg_can_retain_service;
    int hf_h450_CcRequestArg_retain_sig_connection;
    int ett_h450_CcRequestArg_extension;
    int hf_h450_CcRequestRes_retain_service;
    int ett_h450_CcRequestRes_extension;
    int ett_h450_CcShortArg_ccIdentifier;
    int ett_h450_CcShortArg_extension;
    int ett_h450_CcLongArg_numberA;
    int ett_h450_CcLongArg_numberB;
    int ett_h450_CcLongArg_ccIdentifier;
    int ett_h450_CcLongArg_service;
    int ett_h450_CcLongArg_extension;
    int ett_h450_MWIActivateArg_servedUserNr;
    int ett_h450_MWIActivateArg_basicService;
    int ett_h450_MWIActivateArg_msgCentreId;
    int hf_h450_MWIActivateArg_nbOfMessages;
    int ett_h450_MWIActivateArg_originatingNr;
    int hf_h450_MWIActivateArg_timestamp;
    int hf_h450_MWIActivateArg_priority;
    int ett_h450_MWIActivateArg_extensionArg;
    int ett_h450_MWIDeactivateArg_servedUserNr;
    int ett_h450_MWIDeactivateArg_basicService;
    int ett_h450_MWIDeactivateArg_msgCentreId;
    int hf_h450_MWIDeactivateArg_callbackReq;
    int ett_h450_MWIDeactivateArg_extensionArg;
    int ett_h450_MWIInterrogateArg_servedUserNr;
    int ett_h450_MWIInterrogateArg_basicService;
    int ett_h450_MWIInterrogateArg_msgCentreId;
    int hf_h450_MWIInterrogateArg_callbackReq;
    int ett_h450_MWIInterrogateArg_extensionArg;
    int ett_h450_MWIInterrogateResElt_basicService;
    int ett_h450_MWIInterrogateResElt_msgCentreId;
    int hf_h450_MWIInterrogateResElt_nbOfMessages;
    int ett_h450_MWIInterrogateResElt_originatingNr;
    int hf_h450_MWIInterrogateResElt_timestamp;
    int hf_h450_MWIInterrogateResElt_priority;
    int ett_h450_MWIInterrogateResElt_extensionArg;
    int ett_h450_CoReqOptArg_extension;
    int ett_h450_RUAlertOptArg_extension;
    int ett_h450_CfbOvrOptArg_extension;
    int ett_h450_CpRequestArg_parkingNumber;
    int ett_h450_CpRequestArg_parkedNumber;
    int ett_h450_CpRequestArg_parkedToNumber;
    int hf_h450_CpRequestArg_parkedToPosition;
    int ett_h450_CpRequestArg_extensionArg;
    int ett_h450_CpRequestRes_parkedToNumber;
    int hf_h450_CpRequestRes_parkedToPosition;
    int ett_h450_CpRequestRes_parkCondition;
    int ett_h450_CpRequestRes_extensionRes;
    int ett_h450_CpSetupArg_parkingNumber;
    int ett_h450_CpSetupArg_parkedNumber;
    int ett_h450_CpSetupArg_parkedToNumber;
    int hf_h450_CpSetupArg_parkedToPosition;
    int ett_h450_CpSetupArg_extensionArg;
    int ett_h450_CpSetupRes_parkedToNumber;
    int hf_h450_CpSetupRes_parkedToPosition;
    int ett_h450_CpSetupRes_parkCondition;
    int ett_h450_CpSetupRes_extensionRes;
    int ett_h450_GroupIndicationOnArg_callPickupId;
    int ett_h450_GroupIndicationOnArg_groupMemberUserNr;
    int ett_h450_GroupIndicationOnArg_retrieveCallType;
    int ett_h450_GroupIndicationOnArg_partyToRetrieve;
    int ett_h450_GroupIndicationOnArg_retrieveAddress;
    int hf_h450_GroupIndicationOnArg_parkPosition;
    int ett_h450_GroupIndicationOnArg_extensionArg;
    int ett_h450_GroupIndicationOnRes_extensionRes;
    int ett_h450_GroupIndicationOffArg_callPickupId;
    int ett_h450_GroupIndicationOffArg_groupMemberUserNr;
    int ett_h450_GroupIndicationOffArg_extensionArg;
    int ett_h450_GroupIndicationOffRes_extensionRes;
    int ett_h450_PickrequArg_picking_upNumber;
    int ett_h450_PickrequArg_callPickupId;
    int ett_h450_PickrequArg_partyToRetrieve;
    int ett_h450_PickrequArg_retrieveAddress;
    int hf_h450_PickrequArg_parkPosition;
    int ett_h450_PickrequArg_extensionArg;
    int ett_h450_PickrequRes_callPickupId;
    int ett_h450_PickrequRes_extensionRes;
    int ett_h450_PickupArg_callPickupId;
    int ett_h450_PickupArg_picking_upNumber;
    int ett_h450_PickupArg_extensionArg;
    int ett_h450_PickupRes_extensionRes;
    int ett_h450_PickExeArg_callPickupId;
    int ett_h450_PickExeArg_picking_upNumber;
    int ett_h450_PickExeArg_partyToRetrieve;
    int ett_h450_PickExeArg_extensionArg;
    int ett_h450_PickExeRes_extensionRes;
    int ett_h450_CpNotifyArg_parkingNumber;
    int ett_h450_CpNotifyArg_extensionArg;
    int ett_h450_CpickupNotifyArg_picking_upNumber;
    int ett_h450_CpickupNotifyArg_extensionArg;
    int ett_h450_IntResult_servedUserNr;
    int ett_h450_IntResult_basicService;
    int ett_h450_IntResult_procedure;
    int ett_h450_IntResult_divertedToAddress;
    int hf_h450_IntResult_remoteEnabled;
    int ett_h450_IntResult_extension;
    int hf_h450_CTInitiateArg_callIdentity;
    int ett_h450_CTInitiateArg_reroutingNumber;
    int ett_h450_CTInitiateArg_argumentExtension;
    int hf_h450_CTSetupArg_callIdentity;
    int ett_h450_CTSetupArg_transferringNumber;
    int ett_h450_CTSetupArg_argumentExtension;
    int hf_h450_CTIdentifyRes_callIdentity;
    int ett_h450_CTIdentifyRes_reroutingNumber;
    int ett_h450_CTIdentifyRes_resultExtension;
    int ett_h450_CTUpdateArg_redirectionNumber;
    int hf_h450_CTUpdateArg_redirectionInfo;
    int hf_h450_CTUpdateArg_basicCallInfoElements;
    int ett_h450_CTUpdateArg_argumentExtension;
    int ett_h450_SubaddressTransferArg_redirectionSubaddress;
    int ett_h450_SubaddressTransferArg_argumentExtension;
    int ett_h450_CTCompleteArg_endDesignation;
    int ett_h450_CTCompleteArg_redirectionNumber;
    int hf_h450_CTCompleteArg_basicCallInfoElements;
    int hf_h450_CTCompleteArg_redirectionInfo;
    int ett_h450_CTCompleteArg_callStatus;
    int ett_h450_CTCompleteArg_argumentExtension;
    int ett_h450_CTActiveArg_connectedAddress;
    int hf_h450_CTActiveArg_basicCallInfoElements;
    int hf_h450_CTActiveArg_connectedInfo;
    int ett_h450_CTActiveArg_argumentExtension;
    int hf_h450_CIRequestArg_ciCapabilityLevel;
    int ett_h450_CIRequestArg_argumentExtension;
    int ett_h450_CIRequestRes_ciStatusInformation;
    int ett_h450_CIRequestRes_resultExtension;
    int ett_h450_CIGetCIPLOptArg_argumentExtension;
    int hf_h450_CIGetCIPLRes_ciProtectionLevel;
    int hf_h450_CIGetCIPLRes_silentMonitoringPermitted;
    int ett_h450_CIGetCIPLRes_resultExtension;
    int ett_h450_CIIsOptArg_argumentExtension;
    int ett_h450_CIIsOptRes_resultExtension;
    int hf_h450_CIFrcRelArg_ciCapabilityLevel;
    int ett_h450_CIFrcRelArg_argumentExtension;
    int ett_h450_CIFrcRelOptRes_resultExtension;
    int ett_h450_CIWobOptArg_argumentExtension;
    int ett_h450_CIWobOptRes_resultExtension;
    int hf_h450_CISilentArg_ciCapabilityLevel;
    int ett_h450_CISilentArg_specificCall;
    int ett_h450_CISilentArg_argumentExtension;
    int ett_h450_CISilentOptRes_resultExtension;
    int ett_h450_CINotificationArg_ciStatusInformation;
    int ett_h450_CINotificationArg_argumentExtension;
    int hf_h450_CallWaitingArg_nbOfAddWaitingCalls;
    int ett_h450_CallWaitingArg_extensionArg;
    int ett_h450_SupplementaryService_networkFacilityExtension;
    int ett_h450_SupplementaryService_interpretationApdu;
    int ett_h450_SupplementaryService_serviceApdu;
  private:
};

#endif

// End of h450_container1.h