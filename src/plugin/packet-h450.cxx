/* 
 * packet-h450.cxx
 *
 * Sources registering the H.450 protocol with Ethereal
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

extern "C" {
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "plugins/plugin_api.h"

#include "moduleinfo.h"

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#include <string.h>
#include <ctype.h>
#include <time.h>

#include <gmodule.h>
#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
#include <epan/packet.h>
#include "packet-h450.h"

}


extern "C++"{
#  include <stdio.h>
#  include <string.h>
#  include "h450_container.h"
#  include "mini_ptlib/include/mini_ptlib.h"
#  include "h450.h"
}

static H450_Integer_Container h450Cont;

extern "C" {

void 
dissect_h450( tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree )
{
}

void
proto_reg_handoff_h450(void)
{
	dissector_handle_t h450_handle;
	h450_handle = create_dissector_handle( dissect_h450, h450Cont.h450_0.hf_proto_H450 );
}

static const value_string opcode_vals[] = {
  {  0,	"callingName - H.450.8"},
  {  1,	"alertingName - H.450.8"},
  {  2,	"connectedName - H.450.8"},
  {  3,	"busyName - H.450.8"},
  {  7,	"callTransferIdentity - H.450.2"},
  {  8,	"callTransferAbandon - H.450.2"},
  {  9,	"callTransferInitiate - H.450.2"},
  { 10,	"callTransferSetup - H.450.2"},
  { 11,	"callTransferActive - H.450.2"},
  { 12,	"callTransferComplete - H.450.2"},
  { 13,	"callTransferUpdate - H.450.2"},
  { 14,	"subAddressTransfer - H.450.2"},
  { 15,	"activateDiversionQ - H.450.3"},
  { 16,	"deactivateDiversionQ - H.450.3"},
  { 17,	"interrogateDiversionQ - H.450.3"},
  { 18,	"checkRestriction - H.450.3"},
  { 19,	"callRerouting - H.450.3"},
  { 20,	"divertingLegInformation1 - H.450.3"},
  { 21,	"divertingLegInformation2 - H.450.3"},
  { 22,	"divertingLegInformation3 - H.450.3"},
  { 23,	"cfnrDivertedLegFailed - H.450.3"},
  { 27,	"ccnrRequest - H.450.9"},
  { 28,	"ccCancel - H.450.9"},
  { 29,	"ccExecPossible - H.450.9"},
  { 31,	"ccRingout - H.450.9"},
  { 32,	"ccSuspend - H.450.9"},
  { 33,	"ccResume - H.450.9"},
  { 34,	"callOfferRequest - H.450.10"},
  { 40,	"ccbsRequest - H.450.9"},
  { 43,	"callIntrusionRequest - H.450.11"},
  { 44,	"callIntrusionGetCIPL - H.450.11"},
  { 45,	"callIntrusionIsolate - H.450.11"},
  { 46,	"callIntrusionForcedRelease - H.450.11"},
  { 47,	"callIntrusionWOBRequest - H.450.11"},
  { 49,	"cfbOverride - H.450.10"},
  { 80,	"mwiActivate - H.450.7"},
  { 81,	"mwiDeactivate - H.450.7"},
  { 82,	"mwiInterrogate - H.450.7"},
  { 84,	"cmnRequest - H.450.12"},
  { 85,	"cmnInform - H.450.12"},
  {100,	"divertingLegInformation4"},
	{101,	"holdNotific - H.450.4"},
	{102,	"retreiveNotific - H.450.4"},
	{103,	"remoteHold - H.450.4"},
	{104,	"remoteRetreive - H.450.4"},
	{105,	"callWaiting - H.450.6"},
	{106,	"cpRequest - H.450.5"},
	{107,	"cpSetup - H.450.5"},
	{108,	"groupIndicationOn - H.450.5"},
	{109,	"groupIndicationOff - H.450.5"},
	{110,	"pickrequ - H.450.5"},
	{111,	"pickup - H.450.5"},
	{112,	"pickExe - H.450.5"},
	{113,	"cpNotify - H.450.5"},
	{114,	"cpickupNotify - H.450.5"},
  {115,	"remoteUserAlerting - H.450.10"},
  {116,	"callIntrusionSilentMonitor - H.450.11"},
  {117,	"callIntrusionNotification - H.450.11"},
	{0,	NULL}
};

static const value_string error_vals[] = {
  {  31,"notActivated"},
  {1000,"temporarilyUnavailable"},
  {1007,"notAuthorized"},
  {1009,"notBusy"},
  {1010,"shortTermRejection"},
  {1011,"longTermRejection"},
  {1012,"remoteUserBusyAgain"},
  {1013,"failureToMatch"},
  {1008,"unspecified"},
  {1018,"invalidMsgCentreId"},
	{2000,"callPickupIdInvalid"},
	{2001,"callAlreadyPickedUp"},
  {2002,"undefined"},
	{0,	NULL}
};

void
proto_register_h450(void)
{

static hf_register_info hfh450[] = 
{
  {
  &h450Cont.h450_1.hf_h450_Code_local,
    {
      "local",
      "h450.Code.local",
      FT_UINT32, 
      BASE_DEC, 
      VALS(opcode_vals),
      0x0,
      "Code local",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_Code_global,
    {
      "global",
      "h450.Code.global",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Code global",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_EntityType_endpoint,
    {
      "endpoint",
      "h450.EntityType.endpoint",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "EntityType endpoint",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_EntityType_anyEntity,
    {
      "anyEntity",
      "h450.EntityType.anyEntity",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "EntityType anyEntity",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_InterpretationApdu_discardAnyUnrecognizedInvokePdu,
    {
      "discardAnyUnrecognizedInvokePdu",
      "h450.InterpretationApdu.discardAnyUnrecognizedInvokePdu",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "InterpretationApdu discardAnyUnrecognizedInvokePdu",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_InterpretationApdu_clearCallIfAnyInvokePduNotRecognized,
    {
      "clearCallIfAnyInvokePduNotRecognized",
      "h450.InterpretationApdu.clearCallIfAnyInvokePduNotRecognized",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "InterpretationApdu clearCallIfAnyInvokePduNotRecognized",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_InterpretationApdu_rejectAnyUnrecognizedInvokePdu,
    {
      "rejectAnyUnrecognizedInvokePdu",
      "h450.InterpretationApdu.rejectAnyUnrecognizedInvokePdu",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "InterpretationApdu rejectAnyUnrecognizedInvokePdu",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_PresentedAddressScreened_presentationRestricted,
    {
      "presentationRestricted",
      "h450.PresentedAddressScreened.presentationRestricted",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PresentedAddressScreened presentationRestricted",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_PresentedAddressScreened_numberNotAvailableDueToInterworking,
    {
      "numberNotAvailableDueToInterworking",
      "h450.PresentedAddressScreened.numberNotAvailableDueToInterworking",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PresentedAddressScreened numberNotAvailableDueToInterworking",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_PresentedAddressUnscreened_presentationRestricted,
    {
      "presentationRestricted",
      "h450.PresentedAddressUnscreened.presentationRestricted",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PresentedAddressUnscreened presentationRestricted",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_PresentedAddressUnscreened_numberNotAvailableDueToInterworking,
    {
      "numberNotAvailableDueToInterworking",
      "h450.PresentedAddressUnscreened.numberNotAvailableDueToInterworking",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PresentedAddressUnscreened numberNotAvailableDueToInterworking",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_PresentedNumberScreened_presentationRestricted,
    {
      "presentationRestricted",
      "h450.PresentedNumberScreened.presentationRestricted",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PresentedNumberScreened presentationRestricted",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_PresentedNumberScreened_numberNotAvailableDueToInterworking,
    {
      "numberNotAvailableDueToInterworking",
      "h450.PresentedNumberScreened.numberNotAvailableDueToInterworking",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PresentedNumberScreened numberNotAvailableDueToInterworking",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_PresentedNumberUnscreened_presentationRestricted,
    {
      "presentationRestricted",
      "h450.PresentedNumberUnscreened.presentationRestricted",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PresentedNumberUnscreened presentationRestricted",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_PresentedNumberUnscreened_numberNotAvailableDueToInterworking,
    {
      "numberNotAvailableDueToInterworking",
      "h450.PresentedNumberUnscreened.numberNotAvailableDueToInterworking",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PresentedNumberUnscreened numberNotAvailableDueToInterworking",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_PartySubaddress_nsapSubaddress,
    {
      "nsapSubaddress",
      "h450.PartySubaddress.nsapSubaddress",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PartySubaddress nsapSubaddress",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_ScreeningIndicator_enum,
    {
      "enum",
      "h450.ScreeningIndicator.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "ScreeningIndicator enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_GeneralErrorList_enum,
    {
      "enum",
      "h450.GeneralErrorList.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "GeneralErrorList enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_Extension_extensionArgument,
    {
      "extensionArgument",
      "h450.Extension.extensionArgument",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Extension extensionArgument",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_OperationName_enum,
    {
      "enum",
      "h450.OperationName.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "OperationName enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CallCompletionErrors_enum,
    {
      "enum",
      "h450.CallCompletionErrors.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CallCompletionErrors enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_Name_nameNotAvailable,
    {
      "nameNotAvailable",
      "h450.Name.nameNotAvailable",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Name nameNotAvailable",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_NamePresentationAllowed_simpleName,
    {
      "simpleName",
      "h450.NamePresentationAllowed.simpleName",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "NamePresentationAllowed simpleName",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_NamePresentationAllowed_extendedName,
    {
      "extendedName",
      "h450.NamePresentationAllowed.extendedName",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "NamePresentationAllowed extendedName",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_NamePresentationRestricted_simpleName,
    {
      "simpleName",
      "h450.NamePresentationRestricted.simpleName",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "NamePresentationRestricted simpleName",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_NamePresentationRestricted_extendedName,
    {
      "extendedName",
      "h450.NamePresentationRestricted.extendedName",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "NamePresentationRestricted extendedName",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_NamePresentationRestricted_restrictedNull,
    {
      "restrictedNull",
      "h450.NamePresentationRestricted.restrictedNull",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "NamePresentationRestricted restrictedNull",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_MsgCentreId_integer,
    {
      "integer",
      "h450.MsgCentreId.integer",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "MsgCentreId integer",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_MsgCentreId_numericString,
    {
      "numericString",
      "h450.MsgCentreId.numericString",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "MsgCentreId numericString",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_MessageWaitingIndicationErrors_enum,
    {
      "enum",
      "h450.MessageWaitingIndicationErrors.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "MessageWaitingIndicationErrors enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_BasicService_enum,
    {
      "enum",
      "h450.BasicService.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "BasicService enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_ParkCondition_enum,
    {
      "enum",
      "h450.ParkCondition.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "ParkCondition enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CallType_enum,
    {
      "enum",
      "h450.CallType.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CallType enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CallPickupErrors_enum,
    {
      "enum",
      "h450.CallPickupErrors.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CallPickupErrors enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_DiversionReason_enum,
    {
      "enum",
      "h450.DiversionReason.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "DiversionReason enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_Procedure_enum,
    {
      "enum",
      "h450.Procedure.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "Procedure enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_SubscriptionOption_enum,
    {
      "enum",
      "h450.SubscriptionOption.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "SubscriptionOption enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CallDiversionErrors_enum,
    {
      "enum",
      "h450.CallDiversionErrors.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CallDiversionErrors enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_EndDesignation_enum,
    {
      "enum",
      "h450.EndDesignation.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "EndDesignation enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CallStatus_enum,
    {
      "enum",
      "h450.CallStatus.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CallStatus enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CallTransferOperation_enum,
    {
      "enum",
      "h450.CallTransferOperation.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CallTransferOperation enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CallTransferErrors_enum,
    {
      "enum",
      "h450.CallTransferErrors.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CallTransferErrors enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CIStatusInformation_callIntrusionImpending,
    {
      "callIntrusionImpending",
      "h450.CIStatusInformation.callIntrusionImpending",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CIStatusInformation callIntrusionImpending",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CIStatusInformation_callIntruded,
    {
      "callIntruded",
      "h450.CIStatusInformation.callIntruded",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CIStatusInformation callIntruded",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CIStatusInformation_callIsolated,
    {
      "callIsolated",
      "h450.CIStatusInformation.callIsolated",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CIStatusInformation callIsolated",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CIStatusInformation_callForceReleased,
    {
      "callForceReleased",
      "h450.CIStatusInformation.callForceReleased",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CIStatusInformation callForceReleased",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CIStatusInformation_callIntrusionComplete,
    {
      "callIntrusionComplete",
      "h450.CIStatusInformation.callIntrusionComplete",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CIStatusInformation callIntrusionComplete",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CIStatusInformation_callIntrusionEnd,
    {
      "callIntrusionEnd",
      "h450.CIStatusInformation.callIntrusionEnd",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CIStatusInformation callIntrusionEnd",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CallIntrusionErrors_enum,
    {
      "enum",
      "h450.CallIntrusionErrors.enum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CallIntrusionErrors enum",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_ReturnResult_result_result,
    {
      "result",
      "h450.ReturnResult_result.result",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReturnResult_result result",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_Reject_problem_general,
    {
      "general",
      "h450.Reject_problem.general",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "Reject_problem general",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_Reject_problem_invoke,
    {
      "invoke",
      "h450.Reject_problem.invoke",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "Reject_problem invoke",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_Reject_problem_returnResult,
    {
      "returnResult",
      "h450.Reject_problem.returnResult",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "Reject_problem returnResult",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_Reject_problem_returnError,
    {
      "returnError",
      "h450.Reject_problem.returnError",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "Reject_problem returnError",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_Invoke_invokeId,
    {
      "invokeId",
      "h450.Invoke.invokeId",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "Invoke invokeId",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_Invoke_linkedId,
    {
      "linkedId",
      "h450.Invoke.linkedId",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "Invoke linkedId",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_Invoke_argument,
    {
      "argument",
      "h450.Invoke.argument",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Invoke argument",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_ReturnResult_invokeId,
    {
      "invokeId",
      "h450.ReturnResult.invokeId",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "ReturnResult invokeId",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_ReturnError_invokeId,
    {
      "invokeId",
      "h450.ReturnError.invokeId",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "ReturnError invokeId",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_ReturnError_parameter,
    {
      "parameter",
      "h450.ReturnError.parameter",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReturnError parameter",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_Reject_invokeId,
    {
      "invokeId",
      "h450.Reject.invokeId",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "Reject invokeId",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_UserSpecifiedSubaddress_subaddressInformation,
    {
      "subaddressInformation",
      "h450.UserSpecifiedSubaddress.subaddressInformation",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UserSpecifiedSubaddress subaddressInformation",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_UserSpecifiedSubaddress_oddCountIndicator,
    {
      "oddCountIndicator",
      "h450.UserSpecifiedSubaddress.oddCountIndicator",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "UserSpecifiedSubaddress oddCountIndicator",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CcRequestArg_can_retain_service,
    {
      "can_retain_service",
      "h450.CcRequestArg.can_retain_service",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "CcRequestArg can_retain_service",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CcRequestArg_retain_sig_connection,
    {
      "retain_sig_connection",
      "h450.CcRequestArg.retain_sig_connection",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "CcRequestArg retain_sig_connection",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CcRequestRes_retain_service,
    {
      "retain_service",
      "h450.CcRequestRes.retain_service",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "CcRequestRes retain_service",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_MWIActivateArg_nbOfMessages,
    {
      "nbOfMessages",
      "h450.MWIActivateArg.nbOfMessages",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "MWIActivateArg nbOfMessages",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_MWIActivateArg_timestamp,
    {
      "timestamp",
      "h450.MWIActivateArg.timestamp",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "MWIActivateArg timestamp",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_MWIActivateArg_priority,
    {
      "priority",
      "h450.MWIActivateArg.priority",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "MWIActivateArg priority",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_MWIDeactivateArg_callbackReq,
    {
      "callbackReq",
      "h450.MWIDeactivateArg.callbackReq",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "MWIDeactivateArg callbackReq",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_MWIInterrogateArg_callbackReq,
    {
      "callbackReq",
      "h450.MWIInterrogateArg.callbackReq",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "MWIInterrogateArg callbackReq",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_MWIInterrogateResElt_nbOfMessages,
    {
      "nbOfMessages",
      "h450.MWIInterrogateResElt.nbOfMessages",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "MWIInterrogateResElt nbOfMessages",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_MWIInterrogateResElt_timestamp,
    {
      "timestamp",
      "h450.MWIInterrogateResElt.timestamp",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "MWIInterrogateResElt timestamp",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_MWIInterrogateResElt_priority,
    {
      "priority",
      "h450.MWIInterrogateResElt.priority",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "MWIInterrogateResElt priority",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CpRequestArg_parkedToPosition,
    {
      "parkedToPosition",
      "h450.CpRequestArg.parkedToPosition",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CpRequestArg parkedToPosition",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CpRequestRes_parkedToPosition,
    {
      "parkedToPosition",
      "h450.CpRequestRes.parkedToPosition",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CpRequestRes parkedToPosition",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CpSetupArg_parkedToPosition,
    {
      "parkedToPosition",
      "h450.CpSetupArg.parkedToPosition",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CpSetupArg parkedToPosition",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CpSetupRes_parkedToPosition,
    {
      "parkedToPosition",
      "h450.CpSetupRes.parkedToPosition",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CpSetupRes parkedToPosition",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_GroupIndicationOnArg_parkPosition,
    {
      "parkPosition",
      "h450.GroupIndicationOnArg.parkPosition",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "GroupIndicationOnArg parkPosition",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_PickrequArg_parkPosition,
    {
      "parkPosition",
      "h450.PickrequArg.parkPosition",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "PickrequArg parkPosition",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_IntResult_remoteEnabled,
    {
      "remoteEnabled",
      "h450.IntResult.remoteEnabled",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "IntResult remoteEnabled",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CTInitiateArg_callIdentity,
    {
      "callIdentity",
      "h450.CTInitiateArg.callIdentity",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CTInitiateArg callIdentity",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CTSetupArg_callIdentity,
    {
      "callIdentity",
      "h450.CTSetupArg.callIdentity",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CTSetupArg callIdentity",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CTIdentifyRes_callIdentity,
    {
      "callIdentity",
      "h450.CTIdentifyRes.callIdentity",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CTIdentifyRes callIdentity",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CTUpdateArg_redirectionInfo,
    {
      "redirectionInfo",
      "h450.CTUpdateArg.redirectionInfo",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CTUpdateArg redirectionInfo",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CTUpdateArg_basicCallInfoElements,
    {
      "basicCallInfoElements",
      "h450.CTUpdateArg.basicCallInfoElements",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CTUpdateArg basicCallInfoElements",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CTCompleteArg_basicCallInfoElements,
    {
      "basicCallInfoElements",
      "h450.CTCompleteArg.basicCallInfoElements",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CTCompleteArg basicCallInfoElements",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CTCompleteArg_redirectionInfo,
    {
      "redirectionInfo",
      "h450.CTCompleteArg.redirectionInfo",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CTCompleteArg redirectionInfo",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CTActiveArg_basicCallInfoElements,
    {
      "basicCallInfoElements",
      "h450.CTActiveArg.basicCallInfoElements",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CTActiveArg basicCallInfoElements",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CTActiveArg_connectedInfo,
    {
      "connectedInfo",
      "h450.CTActiveArg.connectedInfo",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CTActiveArg connectedInfo",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CIRequestArg_ciCapabilityLevel,
    {
      "ciCapabilityLevel",
      "h450.CIRequestArg.ciCapabilityLevel",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CIRequestArg ciCapabilityLevel",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CIGetCIPLRes_ciProtectionLevel,
    {
      "ciProtectionLevel",
      "h450.CIGetCIPLRes.ciProtectionLevel",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CIGetCIPLRes ciProtectionLevel",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CIGetCIPLRes_silentMonitoringPermitted,
    {
      "silentMonitoringPermitted",
      "h450.CIGetCIPLRes.silentMonitoringPermitted",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CIGetCIPLRes silentMonitoringPermitted",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CIFrcRelArg_ciCapabilityLevel,
    {
      "ciCapabilityLevel",
      "h450.CIFrcRelArg.ciCapabilityLevel",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CIFrcRelArg ciCapabilityLevel",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CISilentArg_ciCapabilityLevel,
    {
      "ciCapabilityLevel",
      "h450.CISilentArg.ciCapabilityLevel",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CISilentArg ciCapabilityLevel",
    }
  },
  {
  &h450Cont.h450_1.hf_h450_CallWaitingArg_nbOfAddWaitingCalls,
    {
      "nbOfAddWaitingCalls",
      "h450.CallWaitingArg.nbOfAddWaitingCalls",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "CallWaitingArg nbOfAddWaitingCalls",
    }
  },
};


static gint *etth450[] = 
{
  &h450Cont.h450_0.ett_proto_H450, // Protocol itself 
  &h450Cont.h450_1.ett_h450_ROS_choice,
  &h450Cont.h450_1.ett_h450_ServiceApdus_choice,
  &h450Cont.h450_1.ett_h450_PresentedAddressScreened_choice,
  &h450Cont.h450_1.ett_h450_PresentedAddressUnscreened_choice,
  &h450Cont.h450_1.ett_h450_PresentedNumberScreened_choice,
  &h450Cont.h450_1.ett_h450_PresentedNumberUnscreened_choice,
  &h450Cont.h450_1.ett_h450_PartySubaddress_choice,
  &h450Cont.h450_1.ett_h450_ScreeningIndicator,
  &h450Cont.h450_1.ett_h450_GeneralErrorList,
  &h450Cont.h450_1.ett_h450_Extension_extensionId,
  &h450Cont.h450_1.ett_h450_OperationName,
  &h450Cont.h450_1.ett_h450_MixedExtension_choice,
  &h450Cont.h450_1.ett_h450_CcArg_choice,
  &h450Cont.h450_1.ett_h450_CallCompletionErrors,
  &h450Cont.h450_1.ett_h450_Name_choice,
  &h450Cont.h450_1.ett_h450_DummyRes,
  &h450Cont.h450_1.ett_h450_MWIInterrogateRes,
  &h450Cont.h450_1.ett_h450_MsgCentreId_choice,
  &h450Cont.h450_1.ett_h450_MessageWaitingIndicationErrors,
  &h450Cont.h450_1.ett_h450_BasicService,
  &h450Cont.h450_1.ett_h450_ParkCondition,
  &h450Cont.h450_1.ett_h450_CallType,
  &h450Cont.h450_1.ett_h450_CallPickupErrors,
  &h450Cont.h450_1.ett_h450_DiversionReason,
  &h450Cont.h450_1.ett_h450_IntResultList,
  &h450Cont.h450_1.ett_h450_Procedure,
  &h450Cont.h450_1.ett_h450_SubscriptionOption,
  &h450Cont.h450_1.ett_h450_CallDiversionErrors,
  &h450Cont.h450_1.ett_h450_DummyArg_choice,
  &h450Cont.h450_1.ett_h450_EndDesignation,
  &h450Cont.h450_1.ett_h450_CallStatus,
  &h450Cont.h450_1.ett_h450_ExtensionSeq,
  &h450Cont.h450_1.ett_h450_CallTransferOperation,
  &h450Cont.h450_1.ett_h450_CallTransferErrors,
  &h450Cont.h450_1.ett_h450_CallIntrusionErrors,
  &h450Cont.h450_1.ett_h450_ReturnResult_result_opcode,
  &h450Cont.h450_1.ett_h450_ArrayOf_ROS,
  &h450Cont.h450_1.ett_h450_ArrayOf_AliasAddress,
  &h450Cont.h450_1.ett_h450_ArrayOf_MixedExtension,
  &h450Cont.h450_1.ett_h450_IntResult_extension_choice,
  &h450Cont.h450_1.ett_h450_CTInitiateArg_argumentExtension_choice,
  &h450Cont.h450_1.ett_h450_CTSetupArg_argumentExtension_choice,
  &h450Cont.h450_1.ett_h450_CTIdentifyRes_resultExtension_choice,
  &h450Cont.h450_1.ett_h450_CTUpdateArg_argumentExtension_choice,
  &h450Cont.h450_1.ett_h450_SubaddressTransferArg_argumentExtension_choice,
  &h450Cont.h450_1.ett_h450_CTCompleteArg_argumentExtension_choice,
  &h450Cont.h450_1.ett_h450_CTActiveArg_argumentExtension_choice,
  &h450Cont.h450_1.ett_h450_Invoke_opcode,
  &h450Cont.h450_1.ett_h450_Invoke_argument,
  &h450Cont.h450_1.ett_h450_ReturnResult_result,
  &h450Cont.h450_1.ett_h450_ReturnError_errorCode,
  &h450Cont.h450_1.ett_h450_Reject_problem,
  &h450Cont.h450_1.ett_h450_NetworkFacilityExtension_sourceEntity,
  &h450Cont.h450_1.ett_h450_NetworkFacilityExtension_sourceEntityAddress,
  &h450Cont.h450_1.ett_h450_NetworkFacilityExtension_destinationEntity,
  &h450Cont.h450_1.ett_h450_NetworkFacilityExtension_destinationEntityAddress,
  &h450Cont.h450_1.ett_h450_AddressScreened_partyNumber,
  &h450Cont.h450_1.ett_h450_AddressScreened_screeningIndicator,
  &h450Cont.h450_1.ett_h450_AddressScreened_partySubaddress,
  &h450Cont.h450_1.ett_h450_NumberScreened_partyNumber,
  &h450Cont.h450_1.ett_h450_NumberScreened_screeningIndicator,
  &h450Cont.h450_1.ett_h450_Address_partyNumber,
  &h450Cont.h450_1.ett_h450_Address_partySubaddress,
  &h450Cont.h450_1.ett_h450_EndpointAddress_destinationAddress,
  &h450Cont.h450_1.ett_h450_EndpointAddress_remoteExtensionAddress,
  &h450Cont.h450_1.ett_h450_HoldNotificArg_extensionArg,
  &h450Cont.h450_1.ett_h450_RetrieveNotificArg_extensionArg,
  &h450Cont.h450_1.ett_h450_RemoteHoldArg_extensionArg,
  &h450Cont.h450_1.ett_h450_RemoteHoldRes_extensionRes,
  &h450Cont.h450_1.ett_h450_RemoteRetrieveArg_extensionArg,
  &h450Cont.h450_1.ett_h450_RemoteRetrieveRes_extensionRes,
  &h450Cont.h450_1.ett_h450_CcRequestArg_numberA,
  &h450Cont.h450_1.ett_h450_CcRequestArg_numberB,
  &h450Cont.h450_1.ett_h450_CcRequestArg_ccIdentifier,
  &h450Cont.h450_1.ett_h450_CcRequestArg_service,
  &h450Cont.h450_1.ett_h450_CcRequestArg_extension,
  &h450Cont.h450_1.ett_h450_CcRequestRes_extension,
  &h450Cont.h450_1.ett_h450_CcShortArg_ccIdentifier,
  &h450Cont.h450_1.ett_h450_CcShortArg_extension,
  &h450Cont.h450_1.ett_h450_CcLongArg_numberA,
  &h450Cont.h450_1.ett_h450_CcLongArg_numberB,
  &h450Cont.h450_1.ett_h450_CcLongArg_ccIdentifier,
  &h450Cont.h450_1.ett_h450_CcLongArg_service,
  &h450Cont.h450_1.ett_h450_CcLongArg_extension,
  &h450Cont.h450_1.ett_h450_MWIActivateArg_servedUserNr,
  &h450Cont.h450_1.ett_h450_MWIActivateArg_basicService,
  &h450Cont.h450_1.ett_h450_MWIActivateArg_msgCentreId,
  &h450Cont.h450_1.ett_h450_MWIActivateArg_originatingNr,
  &h450Cont.h450_1.ett_h450_MWIActivateArg_extensionArg,
  &h450Cont.h450_1.ett_h450_MWIDeactivateArg_servedUserNr,
  &h450Cont.h450_1.ett_h450_MWIDeactivateArg_basicService,
  &h450Cont.h450_1.ett_h450_MWIDeactivateArg_msgCentreId,
  &h450Cont.h450_1.ett_h450_MWIDeactivateArg_extensionArg,
  &h450Cont.h450_1.ett_h450_MWIInterrogateArg_servedUserNr,
  &h450Cont.h450_1.ett_h450_MWIInterrogateArg_basicService,
  &h450Cont.h450_1.ett_h450_MWIInterrogateArg_msgCentreId,
  &h450Cont.h450_1.ett_h450_MWIInterrogateArg_extensionArg,
  &h450Cont.h450_1.ett_h450_MWIInterrogateResElt_basicService,
  &h450Cont.h450_1.ett_h450_MWIInterrogateResElt_msgCentreId,
  &h450Cont.h450_1.ett_h450_MWIInterrogateResElt_originatingNr,
  &h450Cont.h450_1.ett_h450_MWIInterrogateResElt_extensionArg,
  &h450Cont.h450_1.ett_h450_CoReqOptArg_extension,
  &h450Cont.h450_1.ett_h450_RUAlertOptArg_extension,
  &h450Cont.h450_1.ett_h450_CfbOvrOptArg_extension,
  &h450Cont.h450_1.ett_h450_CpRequestArg_parkingNumber,
  &h450Cont.h450_1.ett_h450_CpRequestArg_parkedNumber,
  &h450Cont.h450_1.ett_h450_CpRequestArg_parkedToNumber,
  &h450Cont.h450_1.ett_h450_CpRequestArg_extensionArg,
  &h450Cont.h450_1.ett_h450_CpRequestRes_parkedToNumber,
  &h450Cont.h450_1.ett_h450_CpRequestRes_parkCondition,
  &h450Cont.h450_1.ett_h450_CpRequestRes_extensionRes,
  &h450Cont.h450_1.ett_h450_CpSetupArg_parkingNumber,
  &h450Cont.h450_1.ett_h450_CpSetupArg_parkedNumber,
  &h450Cont.h450_1.ett_h450_CpSetupArg_parkedToNumber,
  &h450Cont.h450_1.ett_h450_CpSetupArg_extensionArg,
  &h450Cont.h450_1.ett_h450_CpSetupRes_parkedToNumber,
  &h450Cont.h450_1.ett_h450_CpSetupRes_parkCondition,
  &h450Cont.h450_1.ett_h450_CpSetupRes_extensionRes,
  &h450Cont.h450_1.ett_h450_GroupIndicationOnArg_callPickupId,
  &h450Cont.h450_1.ett_h450_GroupIndicationOnArg_groupMemberUserNr,
  &h450Cont.h450_1.ett_h450_GroupIndicationOnArg_retrieveCallType,
  &h450Cont.h450_1.ett_h450_GroupIndicationOnArg_partyToRetrieve,
  &h450Cont.h450_1.ett_h450_GroupIndicationOnArg_retrieveAddress,
  &h450Cont.h450_1.ett_h450_GroupIndicationOnArg_extensionArg,
  &h450Cont.h450_1.ett_h450_GroupIndicationOnRes_extensionRes,
  &h450Cont.h450_1.ett_h450_GroupIndicationOffArg_callPickupId,
  &h450Cont.h450_1.ett_h450_GroupIndicationOffArg_groupMemberUserNr,
  &h450Cont.h450_1.ett_h450_GroupIndicationOffArg_extensionArg,
  &h450Cont.h450_1.ett_h450_GroupIndicationOffRes_extensionRes,
  &h450Cont.h450_1.ett_h450_PickrequArg_picking_upNumber,
  &h450Cont.h450_1.ett_h450_PickrequArg_callPickupId,
  &h450Cont.h450_1.ett_h450_PickrequArg_partyToRetrieve,
  &h450Cont.h450_1.ett_h450_PickrequArg_retrieveAddress,
  &h450Cont.h450_1.ett_h450_PickrequArg_extensionArg,
  &h450Cont.h450_1.ett_h450_PickrequRes_callPickupId,
  &h450Cont.h450_1.ett_h450_PickrequRes_extensionRes,
  &h450Cont.h450_1.ett_h450_PickupArg_callPickupId,
  &h450Cont.h450_1.ett_h450_PickupArg_picking_upNumber,
  &h450Cont.h450_1.ett_h450_PickupArg_extensionArg,
  &h450Cont.h450_1.ett_h450_PickupRes_extensionRes,
  &h450Cont.h450_1.ett_h450_PickExeArg_callPickupId,
  &h450Cont.h450_1.ett_h450_PickExeArg_picking_upNumber,
  &h450Cont.h450_1.ett_h450_PickExeArg_partyToRetrieve,
  &h450Cont.h450_1.ett_h450_PickExeArg_extensionArg,
  &h450Cont.h450_1.ett_h450_PickExeRes_extensionRes,
  &h450Cont.h450_1.ett_h450_CpNotifyArg_parkingNumber,
  &h450Cont.h450_1.ett_h450_CpNotifyArg_extensionArg,
  &h450Cont.h450_1.ett_h450_CpickupNotifyArg_picking_upNumber,
  &h450Cont.h450_1.ett_h450_CpickupNotifyArg_extensionArg,
  &h450Cont.h450_1.ett_h450_IntResult_servedUserNr,
  &h450Cont.h450_1.ett_h450_IntResult_basicService,
  &h450Cont.h450_1.ett_h450_IntResult_procedure,
  &h450Cont.h450_1.ett_h450_IntResult_divertedToAddress,
  &h450Cont.h450_1.ett_h450_IntResult_extension,
  &h450Cont.h450_1.ett_h450_CTInitiateArg_reroutingNumber,
  &h450Cont.h450_1.ett_h450_CTInitiateArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_CTSetupArg_transferringNumber,
  &h450Cont.h450_1.ett_h450_CTSetupArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_CTIdentifyRes_reroutingNumber,
  &h450Cont.h450_1.ett_h450_CTIdentifyRes_resultExtension,
  &h450Cont.h450_1.ett_h450_CTUpdateArg_redirectionNumber,
  &h450Cont.h450_1.ett_h450_CTUpdateArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_SubaddressTransferArg_redirectionSubaddress,
  &h450Cont.h450_1.ett_h450_SubaddressTransferArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_CTCompleteArg_endDesignation,
  &h450Cont.h450_1.ett_h450_CTCompleteArg_redirectionNumber,
  &h450Cont.h450_1.ett_h450_CTCompleteArg_callStatus,
  &h450Cont.h450_1.ett_h450_CTCompleteArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_CTActiveArg_connectedAddress,
  &h450Cont.h450_1.ett_h450_CTActiveArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_CIRequestArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_CIRequestRes_ciStatusInformation,
  &h450Cont.h450_1.ett_h450_CIRequestRes_resultExtension,
  &h450Cont.h450_1.ett_h450_CIGetCIPLOptArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_CIGetCIPLRes_resultExtension,
  &h450Cont.h450_1.ett_h450_CIIsOptArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_CIIsOptRes_resultExtension,
  &h450Cont.h450_1.ett_h450_CIFrcRelArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_CIFrcRelOptRes_resultExtension,
  &h450Cont.h450_1.ett_h450_CIWobOptArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_CIWobOptRes_resultExtension,
  &h450Cont.h450_1.ett_h450_CISilentArg_specificCall,
  &h450Cont.h450_1.ett_h450_CISilentArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_CISilentOptRes_resultExtension,
  &h450Cont.h450_1.ett_h450_CINotificationArg_ciStatusInformation,
  &h450Cont.h450_1.ett_h450_CINotificationArg_argumentExtension,
  &h450Cont.h450_1.ett_h450_CallWaitingArg_extensionArg,
  &h450Cont.h450_1.ett_h450_SupplementaryService_networkFacilityExtension,
  &h450Cont.h450_1.ett_h450_SupplementaryService_interpretationApdu,
  &h450Cont.h450_1.ett_h450_SupplementaryService_serviceApdu,
};

	h450Cont.h450_0.hf_proto_H450 = proto_register_protocol( "ITU-T Recommendation H.450", "H450", "h450" );
	proto_register_field_array( h450Cont.h450_0.hf_proto_H450, hfh450, array_length( hfh450 ) );
	proto_register_subtree_array( etth450, array_length( etth450 ) );

	setH450Container( &h450Cont );

  register_dissector( "h450", dissect_h450, h450Cont.h450_0.hf_proto_H450 );

	//h245_tpkt_pdu_handle = create_dissector_handle(dissect_h245_tpkt_pdu, h245Cont.h245_0.hf_proto_H245);


	//register_init_routine( &h245_init );
}

} // extern "C"