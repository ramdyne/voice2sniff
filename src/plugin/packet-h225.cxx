/* 
 * packet-h225.cxx
 *
 * Source for registering andf starting the decode of the H.225.0 protocols
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
#include "packet-h225.h"

#include "plugins/plugin_api_defs.h"

#ifndef __ETHEREAL_STATIC__
G_MODULE_EXPORT gchar version[] = VERSION;
#endif

#include <ipproto.h>

#include "packet-h245.h"
#include "packet-h450.h"

}

extern "C++"{
#  include <stdio.h>
#  include <string.h>
#  include "h225_container.h"
#  include "h235_container.h"
#  include "mini_ptlib/include/mini_ptlib.h"
#  include "h225.h"
#  include "h235.h"

}

static H225_Integer_Container h225Cont;
static H235_Integer_Container h235Cont;

extern "C" {

/*#include "packet-q931.h"
#include "packet-tpkt.h"
*/
void
dissect_h225_ras( tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree )
{
	PBYTEArray bytes;
	int nr_bytes_in_data = 0;
	unsigned int offset = 0;

	//CHECK_DISPLAY_AS_DATA(h225Cont.h225_0.hf_proto_H225, tvb, pinfo, tree);
	
	pinfo->current_proto = "H225 RAS";

	//while ( BYTES_ARE_IN_FRAME( offset, nr_bytes_in_data + 1 ) ) {
	while ( tvb_length_remaining( tvb, offset + ( unsigned ) nr_bytes_in_data ) > 0 ) {
		bytes[ nr_bytes_in_data ] = tvb_get_guint8( tvb, offset + nr_bytes_in_data );
		nr_bytes_in_data++;
	}

	PPER_Stream strm( bytes );
	H225_RasMessage seq;

	if ( check_col( pinfo->cinfo, COL_PROTOCOL ) )   {
		col_add_str( pinfo->cinfo, COL_PROTOCOL, "H.225.0" );
	}
	
	if ( seq.Decode( strm ) != FALSE ) {
		/* After decoding it's possible to 
		 * give the container to everyone. Choice
		 * is not initialized until after decode...
		 * This has to be done before getSummary()
		 * because we might need it...
		 */
		//seq.setContainer( &intCont );
		if ( check_col( pinfo->cinfo, COL_INFO ) ) {
			seq.preShowEthereal(); // This only needs to be done once per frame, so why not do it here?
			col_add_fstr( pinfo->cinfo, COL_INFO, "RAS: %s", (const unsigned char*) seq.getSummary() );
		}

		if ( tree ) {
			proto_tree	*h225_tree = (proto_tree*) NULL;
			proto_item	*h225_ti = (proto_item*) NULL;
			h225_ti = proto_tree_add_item( tree, h225Cont.h225_0.hf_proto_H225, tvb, offset, tvb_length_remaining( tvb, offset ), FALSE );
			h225_tree = proto_item_add_subtree( h225_ti, h225Cont.h225_0.ett_proto_H225 );
			seq.showEthereal( h225_tree, tvb, offset );
		}
	}
	else {
	  if ( check_col( pinfo->cinfo, COL_INFO ) ) {
			col_add_str( pinfo->cinfo, COL_INFO, "Failure during decode" );
		}
	}	
}

gboolean
dissect_h225_cs( tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree )
{

	//CHECK_DISPLAY_AS_DATA(h225Cont.h225_0.hf_proto_H225, tvb, pinfo, tree);
	if ( !proto_is_protocol_enabled( h225Cont.h225_0.hf_proto_H225 ) ) {
		//dissect_data( tvb, 0, pinfo, tree );
		return TRUE;
	}

	pinfo->current_proto = "H225 CS";
	
	PBYTEArray bytes;
	int nr_bytes_in_data = 0;
	unsigned int offset = 0;

	PString previous_protocol = pinfo->current_proto;

	//while ( BYTES_ARE_IN_FRAME( offset, nr_bytes_in_data + 1 ) ) {
	while ( tvb_length_remaining( tvb, offset + ( unsigned ) nr_bytes_in_data ) > 0 ) {
		bytes[ nr_bytes_in_data ] = tvb_get_guint8( tvb, offset + nr_bytes_in_data );
		nr_bytes_in_data++;
	}

	PPER_Stream strm( bytes );
	H225_H323_UserInformation seq;

	if ( seq.Decode( strm ) != FALSE ) {

		if ( check_col( pinfo->cinfo, COL_PROTOCOL ) )   {
			col_add_str( pinfo->cinfo, COL_PROTOCOL, "H.225.0" );
		}

		// After decoding it's possible to 
		// give the container to anyone. Choice
		// is not initialized until after decode...
		// This has to be done before getSummary()
		// because we might need it...
		//seq.setContainer( &intCont );
		if ( check_col( pinfo->cinfo, COL_INFO ) ) {
			seq.preShowEthereal(); // This only needs to be done once per frame, so...
			col_add_fstr( pinfo->cinfo, COL_INFO, "CS: %s", (const unsigned char*) seq.getSummary() );
		}

		if ( tree ) {
			proto_tree	*h225_tree = (proto_tree*) NULL;
			proto_item	*h225_ti = (proto_item*) NULL;
			h225_ti = proto_tree_add_item( tree, h225Cont.h225_0.hf_proto_H225, tvb, offset, tvb_length_remaining(tvb, offset ), FALSE );
			h225_tree = proto_item_add_subtree( h225_ti, h225Cont.h225_0.ett_proto_H225 );
			seq.showEthereal( h225_tree, tvb, offset );
		}
	}
	else {
		if ( check_col( pinfo->cinfo, COL_PROTOCOL ) )   {
			col_add_str( pinfo->cinfo, COL_PROTOCOL, "H.225.0" );
		}

	  if ( check_col( pinfo->cinfo, COL_INFO ) ) {
			col_add_str( pinfo->cinfo, COL_INFO, "Failure during decode" );
		}
	}	
	return TRUE;
}

gboolean
dissect_h225_heur_cs( tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree )
{
  unsigned int offset = 0;
  gboolean lv_result = FALSE;

/*	pinfo->current_proto = "H225 CS HEUR";

  switch ( tvb_get_guint8( tvb, offset ) )
  {
  case 3:
    // This is probably a TPKT message
    if ( is_tpkt( tvb, &offset ) )
    {
      // Skip the 4 TPKT bytes
      offset +=4;

      // It is TPKT, so let's check if this is a Q.931 for H.323 message
      if ( tvb_length_remaining( tvb, offset ) > 0 ) 
      {
        if ( tvb_get_guint8( tvb, offset ) == 8 )
        {
          // Check if there's a Q.931 UU-IE message, 
          // Pattern we're looking for is: 7E xx xx 05
          while ( tvb_length_remaining( tvb, offset ) > 4 )
          {
            if ( tvb_get_guint8( tvb, offset ) == 0x7E )
            {
              // The 5 is part of the UU-IE, so the length should be - 3
              if ( tvb_get_ntohs( tvb, offset + 1 ) <= tvb_length_remaining( tvb, offset ) - 3 )
              {
                if ( tvb_get_guint8( tvb, offset + 3 ) == 0x05 )
                {
                  return dissect_q931_heur( tvb, pinfo, tree );
                }
                else offset += 4;
              }
              else offset += 2;
            }
            else offset++;
          }
        }
      }
      else
      {
        //Dissect the TPKT information
        dissect_tpkt( tvb, &offset, pinfo, tree, TRUE );
      }
    }
    break;
  case 8:
    // This could be a Q.931 message, check if a User-User element is 
    // available with the H.225 signature, 

    // Pattern we're looking for is: 7E 00 xx 05
    while ( tvb_length_remaining( tvb, offset ) > 4 )
    {
      if ( tvb_get_guint8( tvb, offset ) == 0x7E )
      {
        if ( tvb_get_guint8( tvb, offset + 1 ) == 0x0 )
        {
          if ( tvb_get_guint8( tvb, offset + 3 ) == 0x05 )
          {
            return dissect_q931_heur( tvb, pinfo, tree );
          }
          else offset += 4;
        }
        else offset += 2;
      }
      else offset++;
    }

    break;
  default:
    break;
  }
*/
  return lv_result;
}

void 
dissect_h225( tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree )
{
  if( pinfo->ipproto == IP_PROTO_TCP )
  {
    // It's TCP, so dissect as Call Signalling
    dissect_h225_cs( tvb, pinfo, tree );
  }
  else
  {
    if ( pinfo->ipproto == IP_PROTO_UDP ) 
    {
      // It must be UDP, which means RAS
      dissect_h225_ras( tvb, pinfo, tree );
    }
  }
}

void
proto_register_h225(void)
{

static hf_register_info hfh225[] = 
{
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_noBandwidth,
    {
      "noBandwidth",
      "h225.ReleaseCompleteReason.noBandwidth",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason noBandwidth",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_gatekeeperResources,
    {
      "gatekeeperResources",
      "h225.ReleaseCompleteReason.gatekeeperResources",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason gatekeeperResources",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_unreachableDestination,
    {
      "unreachableDestination",
      "h225.ReleaseCompleteReason.unreachableDestination",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason unreachableDestination",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_destinationRejection,
    {
      "destinationRejection",
      "h225.ReleaseCompleteReason.destinationRejection",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason destinationRejection",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_invalidRevision,
    {
      "invalidRevision",
      "h225.ReleaseCompleteReason.invalidRevision",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason invalidRevision",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_noPermission,
    {
      "noPermission",
      "h225.ReleaseCompleteReason.noPermission",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason noPermission",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_unreachableGatekeeper,
    {
      "unreachableGatekeeper",
      "h225.ReleaseCompleteReason.unreachableGatekeeper",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason unreachableGatekeeper",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_gatewayResources,
    {
      "gatewayResources",
      "h225.ReleaseCompleteReason.gatewayResources",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason gatewayResources",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_badFormatAddress,
    {
      "badFormatAddress",
      "h225.ReleaseCompleteReason.badFormatAddress",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason badFormatAddress",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_adaptiveBusy,
    {
      "adaptiveBusy",
      "h225.ReleaseCompleteReason.adaptiveBusy",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason adaptiveBusy",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_inConf,
    {
      "inConf",
      "h225.ReleaseCompleteReason.inConf",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason inConf",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_undefinedReason,
    {
      "undefinedReason",
      "h225.ReleaseCompleteReason.undefinedReason",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason undefinedReason",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_facilityCallDeflection,
    {
      "facilityCallDeflection",
      "h225.ReleaseCompleteReason.facilityCallDeflection",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason facilityCallDeflection",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_securityDenied,
    {
      "securityDenied",
      "h225.ReleaseCompleteReason.securityDenied",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason securityDenied",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_calledPartyNotRegistered,
    {
      "calledPartyNotRegistered",
      "h225.ReleaseCompleteReason.calledPartyNotRegistered",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason calledPartyNotRegistered",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_callerNotRegistered,
    {
      "callerNotRegistered",
      "h225.ReleaseCompleteReason.callerNotRegistered",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason callerNotRegistered",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_newConnectionNeeded,
    {
      "newConnectionNeeded",
      "h225.ReleaseCompleteReason.newConnectionNeeded",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason newConnectionNeeded",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseCompleteReason_replaceWithConferenceInvite,
    {
      "replaceWithConferenceInvite",
      "h225.ReleaseCompleteReason.replaceWithConferenceInvite",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseCompleteReason replaceWithConferenceInvite",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionType_unknown,
    {
      "unknown",
      "h225.ScnConnectionType.unknown",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionType unknown",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionType_bChannel,
    {
      "bChannel",
      "h225.ScnConnectionType.bChannel",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionType bChannel",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionType_hybrid2x64,
    {
      "hybrid2x64",
      "h225.ScnConnectionType.hybrid2x64",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionType hybrid2x64",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionType_hybrid384,
    {
      "hybrid384",
      "h225.ScnConnectionType.hybrid384",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionType hybrid384",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionType_hybrid1536,
    {
      "hybrid1536",
      "h225.ScnConnectionType.hybrid1536",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionType hybrid1536",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionType_hybrid1920,
    {
      "hybrid1920",
      "h225.ScnConnectionType.hybrid1920",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionType hybrid1920",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionType_multirate,
    {
      "multirate",
      "h225.ScnConnectionType.multirate",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionType multirate",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionAggregation_auto,
    {
      "auto",
      "h225.ScnConnectionAggregation.auto",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionAggregation auto",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionAggregation_none,
    {
      "none",
      "h225.ScnConnectionAggregation.none",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionAggregation none",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionAggregation_h221,
    {
      "h221",
      "h225.ScnConnectionAggregation.h221",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionAggregation h221",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionAggregation_bonded_mode1,
    {
      "bonded_mode1",
      "h225.ScnConnectionAggregation.bonded_mode1",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionAggregation bonded_mode1",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionAggregation_bonded_mode2,
    {
      "bonded_mode2",
      "h225.ScnConnectionAggregation.bonded_mode2",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionAggregation bonded_mode2",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ScnConnectionAggregation_bonded_mode3,
    {
      "bonded_mode3",
      "h225.ScnConnectionAggregation.bonded_mode3",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ScnConnectionAggregation bonded_mode3",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PresentationIndicator_presentationAllowed,
    {
      "presentationAllowed",
      "h225.PresentationIndicator.presentationAllowed",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PresentationIndicator presentationAllowed",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PresentationIndicator_presentationRestricted,
    {
      "presentationRestricted",
      "h225.PresentationIndicator.presentationRestricted",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PresentationIndicator presentationRestricted",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PresentationIndicator_addressNotAvailable,
    {
      "addressNotAvailable",
      "h225.PresentationIndicator.addressNotAvailable",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PresentationIndicator addressNotAvailable",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_FacilityReason_routeCallToGatekeeper,
    {
      "routeCallToGatekeeper",
      "h225.FacilityReason.routeCallToGatekeeper",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "FacilityReason routeCallToGatekeeper",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_FacilityReason_callForwarded,
    {
      "callForwarded",
      "h225.FacilityReason.callForwarded",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "FacilityReason callForwarded",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_FacilityReason_routeCallToMC,
    {
      "routeCallToMC",
      "h225.FacilityReason.routeCallToMC",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "FacilityReason routeCallToMC",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_FacilityReason_undefinedReason,
    {
      "undefinedReason",
      "h225.FacilityReason.undefinedReason",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "FacilityReason undefinedReason",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_FacilityReason_conferenceListChoice,
    {
      "conferenceListChoice",
      "h225.FacilityReason.conferenceListChoice",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "FacilityReason conferenceListChoice",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_FacilityReason_startH245,
    {
      "startH245",
      "h225.FacilityReason.startH245",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "FacilityReason startH245",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_FacilityReason_noH245,
    {
      "noH245",
      "h225.FacilityReason.noH245",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "FacilityReason noH245",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportAddress_netBios,
    {
      "netBios",
      "h225.TransportAddress.netBios",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportAddress netBios",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportAddress_nsap,
    {
      "nsap",
      "h225.TransportAddress.nsap",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportAddress nsap",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_H221NonStandard_t35CountryCode,
    {
      "t35CountryCode",
      "h225.H221NonStandard.t35CountryCode",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "H221NonStandard t35CountryCode",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_H221NonStandard_t35Extension,
    {
      "t35Extension",
      "h225.H221NonStandard.t35Extension",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "H221NonStandard t35Extension",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_H221NonStandard_manufacturerCode,
    {
      "manufacturerCode",
      "h225.H221NonStandard.manufacturerCode",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "H221NonStandard manufacturerCode",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_NonStandardIdentifier_object,
    {
      "object",
      "h225.NonStandardIdentifier.object",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "NonStandardIdentifier object",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AliasAddress_e164,
    {
      "e164",
      "h225.AliasAddress.e164",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AliasAddress e164",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AliasAddress_h323_ID,
    {
      "h323_ID",
      "h225.AliasAddress.h323_ID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AliasAddress h323_ID",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AliasAddress_url_ID,
    {
      "url_ID",
      "h225.AliasAddress.url_ID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AliasAddress url_ID",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AliasAddress_email_ID,
    {
      "email_ID",
      "h225.AliasAddress.email_ID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AliasAddress email_ID",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PartyNumber_dataPartyNumber,
    {
      "dataPartyNumber",
      "h225.PartyNumber.dataPartyNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PartyNumber dataPartyNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PartyNumber_telexPartyNumber,
    {
      "telexPartyNumber",
      "h225.PartyNumber.telexPartyNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PartyNumber telexPartyNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PartyNumber_nationalStandardPartyNumber,
    {
      "nationalStandardPartyNumber",
      "h225.PartyNumber.nationalStandardPartyNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PartyNumber nationalStandardPartyNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PublicTypeOfNumber_unknown,
    {
      "unknown",
      "h225.PublicTypeOfNumber.unknown",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PublicTypeOfNumber unknown",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PublicTypeOfNumber_internationalNumber,
    {
      "internationalNumber",
      "h225.PublicTypeOfNumber.internationalNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PublicTypeOfNumber internationalNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PublicTypeOfNumber_nationalNumber,
    {
      "nationalNumber",
      "h225.PublicTypeOfNumber.nationalNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PublicTypeOfNumber nationalNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PublicTypeOfNumber_networkSpecificNumber,
    {
      "networkSpecificNumber",
      "h225.PublicTypeOfNumber.networkSpecificNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PublicTypeOfNumber networkSpecificNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PublicTypeOfNumber_subscriberNumber,
    {
      "subscriberNumber",
      "h225.PublicTypeOfNumber.subscriberNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PublicTypeOfNumber subscriberNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PublicTypeOfNumber_abbreviatedNumber,
    {
      "abbreviatedNumber",
      "h225.PublicTypeOfNumber.abbreviatedNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PublicTypeOfNumber abbreviatedNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PrivateTypeOfNumber_unknown,
    {
      "unknown",
      "h225.PrivateTypeOfNumber.unknown",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PrivateTypeOfNumber unknown",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PrivateTypeOfNumber_level2RegionalNumber,
    {
      "level2RegionalNumber",
      "h225.PrivateTypeOfNumber.level2RegionalNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PrivateTypeOfNumber level2RegionalNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PrivateTypeOfNumber_level1RegionalNumber,
    {
      "level1RegionalNumber",
      "h225.PrivateTypeOfNumber.level1RegionalNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PrivateTypeOfNumber level1RegionalNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PrivateTypeOfNumber_pISNSpecificNumber,
    {
      "pISNSpecificNumber",
      "h225.PrivateTypeOfNumber.pISNSpecificNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PrivateTypeOfNumber pISNSpecificNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PrivateTypeOfNumber_localNumber,
    {
      "localNumber",
      "h225.PrivateTypeOfNumber.localNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PrivateTypeOfNumber localNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PrivateTypeOfNumber_abbreviatedNumber,
    {
      "abbreviatedNumber",
      "h225.PrivateTypeOfNumber.abbreviatedNumber",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PrivateTypeOfNumber abbreviatedNumber",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UseSpecifiedTransport_tcp,
    {
      "tcp",
      "h225.UseSpecifiedTransport.tcp",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UseSpecifiedTransport tcp",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UseSpecifiedTransport_annexE,
    {
      "annexE",
      "h225.UseSpecifiedTransport.annexE",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UseSpecifiedTransport annexE",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_SecurityServiceMode_none,
    {
      "none",
      "h225.SecurityServiceMode.none",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "SecurityServiceMode none",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_SecurityServiceMode_default,
    {
      "default",
      "h225.SecurityServiceMode.default",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "SecurityServiceMode default",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_H245Security_noSecurity,
    {
      "noSecurity",
      "h225.H245Security.noSecurity",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "H245Security noSecurity",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Q954Details_conferenceCalling,
    {
      "conferenceCalling",
      "h225.Q954Details.conferenceCalling",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Q954Details conferenceCalling",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Q954Details_threePartyService,
    {
      "threePartyService",
      "h225.Q954Details.threePartyService",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Q954Details threePartyService",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_CallIdentifier_guid,
    {
      "guid",
      "h225.CallIdentifier.guid",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallIdentifier guid",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_EncryptIntAlg_isoAlgorithm,
    {
      "isoAlgorithm",
      "h225.EncryptIntAlg.isoAlgorithm",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "EncryptIntAlg isoAlgorithm",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_NonIsoIntegrityMechanism_hMAC_MD5,
    {
      "hMAC_MD5",
      "h225.NonIsoIntegrityMechanism.hMAC_MD5",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "NonIsoIntegrityMechanism hMAC_MD5",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_NonIsoIntegrityMechanism_hMAC_iso10118_3,
    {
      "hMAC_iso10118_3",
      "h225.NonIsoIntegrityMechanism.hMAC_iso10118_3",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "NonIsoIntegrityMechanism hMAC_iso10118_3",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_IntegrityMechanism_digSig,
    {
      "digSig",
      "h225.IntegrityMechanism.digSig",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "IntegrityMechanism digSig",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_IntegrityMechanism_iso9797,
    {
      "iso9797",
      "h225.IntegrityMechanism.iso9797",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "IntegrityMechanism iso9797",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ICV_algorithmOID,
    {
      "algorithmOID",
      "h225.ICV.algorithmOID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ICV algorithmOID",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ICV_icv,
    {
      "icv",
      "h225.ICV.icv",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ICV icv",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_GatekeeperRejectReason_resourceUnavailable,
    {
      "resourceUnavailable",
      "h225.GatekeeperRejectReason.resourceUnavailable",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "GatekeeperRejectReason resourceUnavailable",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_GatekeeperRejectReason_terminalExcluded,
    {
      "terminalExcluded",
      "h225.GatekeeperRejectReason.terminalExcluded",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "GatekeeperRejectReason terminalExcluded",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_GatekeeperRejectReason_invalidRevision,
    {
      "invalidRevision",
      "h225.GatekeeperRejectReason.invalidRevision",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "GatekeeperRejectReason invalidRevision",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_GatekeeperRejectReason_undefinedReason,
    {
      "undefinedReason",
      "h225.GatekeeperRejectReason.undefinedReason",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "GatekeeperRejectReason undefinedReason",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_GatekeeperRejectReason_securityDenial,
    {
      "securityDenial",
      "h225.GatekeeperRejectReason.securityDenial",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "GatekeeperRejectReason securityDenial",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationRejectReason_discoveryRequired,
    {
      "discoveryRequired",
      "h225.RegistrationRejectReason.discoveryRequired",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRejectReason discoveryRequired",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationRejectReason_invalidRevision,
    {
      "invalidRevision",
      "h225.RegistrationRejectReason.invalidRevision",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRejectReason invalidRevision",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationRejectReason_invalidCallSignalAddress,
    {
      "invalidCallSignalAddress",
      "h225.RegistrationRejectReason.invalidCallSignalAddress",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRejectReason invalidCallSignalAddress",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationRejectReason_invalidRASAddress,
    {
      "invalidRASAddress",
      "h225.RegistrationRejectReason.invalidRASAddress",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRejectReason invalidRASAddress",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationRejectReason_invalidTerminalType,
    {
      "invalidTerminalType",
      "h225.RegistrationRejectReason.invalidTerminalType",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRejectReason invalidTerminalType",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationRejectReason_undefinedReason,
    {
      "undefinedReason",
      "h225.RegistrationRejectReason.undefinedReason",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRejectReason undefinedReason",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationRejectReason_transportNotSupported,
    {
      "transportNotSupported",
      "h225.RegistrationRejectReason.transportNotSupported",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRejectReason transportNotSupported",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationRejectReason_transportQOSNotSupported,
    {
      "transportQOSNotSupported",
      "h225.RegistrationRejectReason.transportQOSNotSupported",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRejectReason transportQOSNotSupported",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationRejectReason_resourceUnavailable,
    {
      "resourceUnavailable",
      "h225.RegistrationRejectReason.resourceUnavailable",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRejectReason resourceUnavailable",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationRejectReason_invalidAlias,
    {
      "invalidAlias",
      "h225.RegistrationRejectReason.invalidAlias",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRejectReason invalidAlias",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationRejectReason_securityDenial,
    {
      "securityDenial",
      "h225.RegistrationRejectReason.securityDenial",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRejectReason securityDenial",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationRejectReason_fullRegistrationRequired,
    {
      "fullRegistrationRequired",
      "h225.RegistrationRejectReason.fullRegistrationRequired",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRejectReason fullRegistrationRequired",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregRequestReason_reregistrationRequired,
    {
      "reregistrationRequired",
      "h225.UnregRequestReason.reregistrationRequired",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UnregRequestReason reregistrationRequired",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregRequestReason_ttlExpired,
    {
      "ttlExpired",
      "h225.UnregRequestReason.ttlExpired",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UnregRequestReason ttlExpired",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregRequestReason_securityDenial,
    {
      "securityDenial",
      "h225.UnregRequestReason.securityDenial",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UnregRequestReason securityDenial",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregRequestReason_undefinedReason,
    {
      "undefinedReason",
      "h225.UnregRequestReason.undefinedReason",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UnregRequestReason undefinedReason",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregRejectReason_notCurrentlyRegistered,
    {
      "notCurrentlyRegistered",
      "h225.UnregRejectReason.notCurrentlyRegistered",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UnregRejectReason notCurrentlyRegistered",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregRejectReason_callInProgress,
    {
      "callInProgress",
      "h225.UnregRejectReason.callInProgress",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UnregRejectReason callInProgress",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregRejectReason_undefinedReason,
    {
      "undefinedReason",
      "h225.UnregRejectReason.undefinedReason",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UnregRejectReason undefinedReason",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregRejectReason_permissionDenied,
    {
      "permissionDenied",
      "h225.UnregRejectReason.permissionDenied",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UnregRejectReason permissionDenied",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregRejectReason_securityDenial,
    {
      "securityDenial",
      "h225.UnregRejectReason.securityDenial",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UnregRejectReason securityDenial",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_CallType_pointToPoint,
    {
      "pointToPoint",
      "h225.CallType.pointToPoint",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallType pointToPoint",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_CallType_oneToN,
    {
      "oneToN",
      "h225.CallType.oneToN",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallType oneToN",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_CallType_nToOne,
    {
      "nToOne",
      "h225.CallType.nToOne",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallType nToOne",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_CallType_nToN,
    {
      "nToN",
      "h225.CallType.nToN",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallType nToN",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_CallModel_direct,
    {
      "direct",
      "h225.CallModel.direct",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallModel direct",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_CallModel_gatekeeperRouted,
    {
      "gatekeeperRouted",
      "h225.CallModel.gatekeeperRouted",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallModel gatekeeperRouted",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportQOS_endpointControlled,
    {
      "endpointControlled",
      "h225.TransportQOS.endpointControlled",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportQOS endpointControlled",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportQOS_gatekeeperControlled,
    {
      "gatekeeperControlled",
      "h225.TransportQOS.gatekeeperControlled",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportQOS gatekeeperControlled",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportQOS_noControl,
    {
      "noControl",
      "h225.TransportQOS.noControl",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportQOS noControl",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UUIEsRequested_setup,
    {
      "setup",
      "h225.UUIEsRequested.setup",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "UUIEsRequested setup",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UUIEsRequested_callProceeding,
    {
      "callProceeding",
      "h225.UUIEsRequested.callProceeding",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "UUIEsRequested callProceeding",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UUIEsRequested_connect,
    {
      "connect",
      "h225.UUIEsRequested.connect",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "UUIEsRequested connect",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UUIEsRequested_alerting,
    {
      "alerting",
      "h225.UUIEsRequested.alerting",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "UUIEsRequested alerting",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UUIEsRequested_information,
    {
      "information",
      "h225.UUIEsRequested.information",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "UUIEsRequested information",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UUIEsRequested_releaseComplete,
    {
      "releaseComplete",
      "h225.UUIEsRequested.releaseComplete",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "UUIEsRequested releaseComplete",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UUIEsRequested_facility,
    {
      "facility",
      "h225.UUIEsRequested.facility",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "UUIEsRequested facility",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UUIEsRequested_progress,
    {
      "progress",
      "h225.UUIEsRequested.progress",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "UUIEsRequested progress",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UUIEsRequested_empty,
    {
      "empty",
      "h225.UUIEsRequested.empty",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "UUIEsRequested empty",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRejectReason_calledPartyNotRegistered,
    {
      "calledPartyNotRegistered",
      "h225.AdmissionRejectReason.calledPartyNotRegistered",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRejectReason calledPartyNotRegistered",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRejectReason_invalidPermission,
    {
      "invalidPermission",
      "h225.AdmissionRejectReason.invalidPermission",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRejectReason invalidPermission",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRejectReason_requestDenied,
    {
      "requestDenied",
      "h225.AdmissionRejectReason.requestDenied",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRejectReason requestDenied",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRejectReason_undefinedReason,
    {
      "undefinedReason",
      "h225.AdmissionRejectReason.undefinedReason",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRejectReason undefinedReason",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRejectReason_callerNotRegistered,
    {
      "callerNotRegistered",
      "h225.AdmissionRejectReason.callerNotRegistered",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRejectReason callerNotRegistered",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRejectReason_routeCallToGatekeeper,
    {
      "routeCallToGatekeeper",
      "h225.AdmissionRejectReason.routeCallToGatekeeper",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRejectReason routeCallToGatekeeper",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRejectReason_invalidEndpointIdentifier,
    {
      "invalidEndpointIdentifier",
      "h225.AdmissionRejectReason.invalidEndpointIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRejectReason invalidEndpointIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRejectReason_resourceUnavailable,
    {
      "resourceUnavailable",
      "h225.AdmissionRejectReason.resourceUnavailable",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRejectReason resourceUnavailable",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRejectReason_securityDenial,
    {
      "securityDenial",
      "h225.AdmissionRejectReason.securityDenial",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRejectReason securityDenial",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRejectReason_qosControlNotSupported,
    {
      "qosControlNotSupported",
      "h225.AdmissionRejectReason.qosControlNotSupported",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRejectReason qosControlNotSupported",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRejectReason_incompleteAddress,
    {
      "incompleteAddress",
      "h225.AdmissionRejectReason.incompleteAddress",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRejectReason incompleteAddress",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRejectReason_aliasesInconsistent,
    {
      "aliasesInconsistent",
      "h225.AdmissionRejectReason.aliasesInconsistent",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRejectReason aliasesInconsistent",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandRejectReason_notBound,
    {
      "notBound",
      "h225.BandRejectReason.notBound",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "BandRejectReason notBound",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandRejectReason_invalidConferenceID,
    {
      "invalidConferenceID",
      "h225.BandRejectReason.invalidConferenceID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "BandRejectReason invalidConferenceID",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandRejectReason_invalidPermission,
    {
      "invalidPermission",
      "h225.BandRejectReason.invalidPermission",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "BandRejectReason invalidPermission",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandRejectReason_insufficientResources,
    {
      "insufficientResources",
      "h225.BandRejectReason.insufficientResources",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "BandRejectReason insufficientResources",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandRejectReason_invalidRevision,
    {
      "invalidRevision",
      "h225.BandRejectReason.invalidRevision",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "BandRejectReason invalidRevision",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandRejectReason_undefinedReason,
    {
      "undefinedReason",
      "h225.BandRejectReason.undefinedReason",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "BandRejectReason undefinedReason",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandRejectReason_securityDenial,
    {
      "securityDenial",
      "h225.BandRejectReason.securityDenial",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "BandRejectReason securityDenial",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_LocationRejectReason_notRegistered,
    {
      "notRegistered",
      "h225.LocationRejectReason.notRegistered",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "LocationRejectReason notRegistered",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_LocationRejectReason_invalidPermission,
    {
      "invalidPermission",
      "h225.LocationRejectReason.invalidPermission",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "LocationRejectReason invalidPermission",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_LocationRejectReason_requestDenied,
    {
      "requestDenied",
      "h225.LocationRejectReason.requestDenied",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "LocationRejectReason requestDenied",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_LocationRejectReason_undefinedReason,
    {
      "undefinedReason",
      "h225.LocationRejectReason.undefinedReason",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "LocationRejectReason undefinedReason",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_LocationRejectReason_securityDenial,
    {
      "securityDenial",
      "h225.LocationRejectReason.securityDenial",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "LocationRejectReason securityDenial",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_LocationRejectReason_aliasesInconsistent,
    {
      "aliasesInconsistent",
      "h225.LocationRejectReason.aliasesInconsistent",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "LocationRejectReason aliasesInconsistent",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_DisengageReason_forcedDrop,
    {
      "forcedDrop",
      "h225.DisengageReason.forcedDrop",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "DisengageReason forcedDrop",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_DisengageReason_normalDrop,
    {
      "normalDrop",
      "h225.DisengageReason.normalDrop",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "DisengageReason normalDrop",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_DisengageReason_undefinedReason,
    {
      "undefinedReason",
      "h225.DisengageReason.undefinedReason",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "DisengageReason undefinedReason",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_DisengageRejectReason_notRegistered,
    {
      "notRegistered",
      "h225.DisengageRejectReason.notRegistered",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "DisengageRejectReason notRegistered",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_DisengageRejectReason_requestToDropOther,
    {
      "requestToDropOther",
      "h225.DisengageRejectReason.requestToDropOther",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "DisengageRejectReason requestToDropOther",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_DisengageRejectReason_securityDenial,
    {
      "securityDenial",
      "h225.DisengageRejectReason.securityDenial",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "DisengageRejectReason securityDenial",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_InfoRequestNakReason_notRegistered,
    {
      "notRegistered",
      "h225.InfoRequestNakReason.notRegistered",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "InfoRequestNakReason notRegistered",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_InfoRequestNakReason_securityDenial,
    {
      "securityDenial",
      "h225.InfoRequestNakReason.securityDenial",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "InfoRequestNakReason securityDenial",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_InfoRequestNakReason_undefinedReason,
    {
      "undefinedReason",
      "h225.InfoRequestNakReason.undefinedReason",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "InfoRequestNakReason undefinedReason",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_H323_UserInformation_user_data_protocol_discriminator,
    {
      "protocol_discriminator",
      "h225.H323_UserInformation_user_data.protocol_discriminator",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "H323-UserInformation_user-data protocol_discriminator",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_H323_UserInformation_user_data_user_information,
    {
      "user_information",
      "h225.H323_UserInformation_user_data.user_information",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "H323-UserInformation_user-data user_information",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_H323_UU_PDU_h323_message_body_empty,
    {
      "empty",
      "h225.H323_UU_PDU_h323_message_body.empty",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "H323-UU-PDU_h323-message-body empty",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ArrayOf_PASN_OctetString_array,
    {
      "array",
      "h225.ArrayOf_PASN_OctetString.array",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ArrayOf_PASN_OctetString array",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Connect_UUIE_language_array,
    {
      "array",
      "h225.Connect_UUIE_language.array",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Connect-UUIE_language array",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ArrayOf_CallReferenceValue_array,
    {
      "array",
      "h225.ArrayOf_CallReferenceValue.array",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "ArrayOf_CallReferenceValue array",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Setup_UUIE_conferenceGoal_create,
    {
      "create",
      "h225.Setup_UUIE_conferenceGoal.create",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE_conferenceGoal create",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Setup_UUIE_conferenceGoal_join,
    {
      "join",
      "h225.Setup_UUIE_conferenceGoal.join",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE_conferenceGoal join",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Setup_UUIE_conferenceGoal_invite,
    {
      "invite",
      "h225.Setup_UUIE_conferenceGoal.invite",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE_conferenceGoal invite",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Setup_UUIE_conferenceGoal_capability_negotiation,
    {
      "capability_negotiation",
      "h225.Setup_UUIE_conferenceGoal.capability_negotiation",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE_conferenceGoal capability_negotiation",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Setup_UUIE_conferenceGoal_callIndependentSupplementaryService,
    {
      "callIndependentSupplementaryService",
      "h225.Setup_UUIE_conferenceGoal.callIndependentSupplementaryService",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE_conferenceGoal callIndependentSupplementaryService",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Setup_UUIE_connectionParameters_numberOfScnConnections,
    {
      "numberOfScnConnections",
      "h225.Setup_UUIE_connectionParameters.numberOfScnConnections",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "Setup-UUIE_connectionParameters numberOfScnConnections",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Setup_UUIE_language_array,
    {
      "array",
      "h225.Setup_UUIE_language.array",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE_language array",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportAddress_ipAddress_ip,
    {
      "ip",
      "h225.TransportAddress_ipAddress.ip",
      FT_IPv4, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportAddress_ipAddress ip",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportAddress_ipAddress_port,
    {
      "port",
      "h225.TransportAddress_ipAddress.port",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "TransportAddress_ipAddress port",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportAddress_ipxAddress_node,
    {
      "node",
      "h225.TransportAddress_ipxAddress.node",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportAddress_ipxAddress node",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportAddress_ipxAddress_netnum,
    {
      "netnum",
      "h225.TransportAddress_ipxAddress.netnum",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportAddress_ipxAddress netnum",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportAddress_ipxAddress_port,
    {
      "port",
      "h225.TransportAddress_ipxAddress.port",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportAddress_ipxAddress port",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportAddress_ip6Address_ip,
    {
      "ip",
      "h225.TransportAddress_ip6Address.ip",
      FT_IPv6, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportAddress_ip6Address ip",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportAddress_ip6Address_port,
    {
      "port",
      "h225.TransportAddress_ip6Address.port",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "TransportAddress_ip6Address port",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_CryptoH323Token_cryptoGKPwdHash_gatekeeperId,
    {
      "gatekeeperId",
      "h225.CryptoH323Token_cryptoGKPwdHash.gatekeeperId",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CryptoH323Token_cryptoGKPwdHash gatekeeperId",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ArrayOf_PASN_ObjectId_array,
    {
      "array",
      "h225.ArrayOf_PASN_ObjectId.array",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ArrayOf_PASN_ObjectId array",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionConfirm_language_array,
    {
      "array",
      "h225.AdmissionConfirm_language.array",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionConfirm_language array",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RTPSession_associatedSessionIds_array,
    {
      "array",
      "h225.RTPSession_associatedSessionIds.array",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "RTPSession_associatedSessionIds array",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportAddress_ipSourceRoute_route_array,
    {
      "array",
      "h225.TransportAddress_ipSourceRoute_route.array",
      FT_IPv4, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportAddress_ipSourceRoute_route array",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportAddress_ipSourceRoute_routing_strict,
    {
      "strict",
      "h225.TransportAddress_ipSourceRoute_routing.strict",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportAddress_ipSourceRoute_routing strict",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_TransportAddress_ipSourceRoute_routing_loose,
    {
      "loose",
      "h225.TransportAddress_ipSourceRoute_routing.loose",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportAddress_ipSourceRoute_routing loose",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ArrayOf_ConferenceIdentifier_array,
    {
      "array",
      "h225.ArrayOf_ConferenceIdentifier.array",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ArrayOf_ConferenceIdentifier array",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Information_UUIE_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.Information_UUIE.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Information-UUIE protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Information_UUIE_fastConnectRefused,
    {
      "fastConnectRefused",
      "h225.Information_UUIE.fastConnectRefused",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Information-UUIE fastConnectRefused",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseComplete_UUIE_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.ReleaseComplete_UUIE.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseComplete-UUIE protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_ReleaseComplete_UUIE_screeningIndicator,
    {
      "screeningIndicator",
      "h225.ReleaseComplete_UUIE.screeningIndicator",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReleaseComplete-UUIE screeningIndicator",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Facility_UUIE_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.Facility_UUIE.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Facility-UUIE protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Facility_UUIE_conferenceID,
    {
      "conferenceID",
      "h225.Facility_UUIE.conferenceID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Facility-UUIE conferenceID",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Facility_UUIE_multipleCalls,
    {
      "multipleCalls",
      "h225.Facility_UUIE.multipleCalls",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Facility-UUIE multipleCalls",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Facility_UUIE_maintainConnection,
    {
      "maintainConnection",
      "h225.Facility_UUIE.maintainConnection",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Facility-UUIE maintainConnection",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_Facility_UUIE_fastConnectRefused,
    {
      "fastConnectRefused",
      "h225.Facility_UUIE.fastConnectRefused",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Facility-UUIE fastConnectRefused",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_CallLinkage_globalCallId,
    {
      "globalCallId",
      "h225.CallLinkage.globalCallId",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallLinkage globalCallId",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_CallLinkage_threadId,
    {
      "threadId",
      "h225.CallLinkage.threadId",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallLinkage threadId",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_VendorIdentifier_productId,
    {
      "productId",
      "h225.VendorIdentifier.productId",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "VendorIdentifier productId",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_VendorIdentifier_versionId,
    {
      "versionId",
      "h225.VendorIdentifier.versionId",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "VendorIdentifier versionId",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_NonStandardParameter_data,
    {
      "data",
      "h225.NonStandardParameter.data",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "NonStandardParameter data",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PublicPartyNumber_publicNumberDigits,
    {
      "publicNumberDigits",
      "h225.PublicPartyNumber.publicNumberDigits",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PublicPartyNumber publicNumberDigits",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_PrivatePartyNumber_privateNumberDigits,
    {
      "privateNumberDigits",
      "h225.PrivatePartyNumber.privateNumberDigits",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "PrivatePartyNumber privateNumberDigits",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AlternateGK_gatekeeperIdentifier,
    {
      "gatekeeperIdentifier",
      "h225.AlternateGK.gatekeeperIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AlternateGK gatekeeperIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AlternateGK_needToRegister,
    {
      "needToRegister",
      "h225.AlternateGK.needToRegister",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "AlternateGK needToRegister",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AlternateGK_priority,
    {
      "priority",
      "h225.AlternateGK.priority",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "AlternateGK priority",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AltGKInfo_altGKisPermanent,
    {
      "altGKisPermanent",
      "h225.AltGKInfo.altGKisPermanent",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "AltGKInfo altGKisPermanent",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_QseriesOptions_q932Full,
    {
      "q932Full",
      "h225.QseriesOptions.q932Full",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "QseriesOptions q932Full",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_QseriesOptions_q951Full,
    {
      "q951Full",
      "h225.QseriesOptions.q951Full",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "QseriesOptions q951Full",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_QseriesOptions_q952Full,
    {
      "q952Full",
      "h225.QseriesOptions.q952Full",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "QseriesOptions q952Full",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_QseriesOptions_q953Full,
    {
      "q953Full",
      "h225.QseriesOptions.q953Full",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "QseriesOptions q953Full",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_QseriesOptions_q955Full,
    {
      "q955Full",
      "h225.QseriesOptions.q955Full",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "QseriesOptions q955Full",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_QseriesOptions_q956Full,
    {
      "q956Full",
      "h225.QseriesOptions.q956Full",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "QseriesOptions q956Full",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_QseriesOptions_q957Full,
    {
      "q957Full",
      "h225.QseriesOptions.q957Full",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "QseriesOptions q957Full",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_DataRate_channelRate,
    {
      "channelRate",
      "h225.DataRate.channelRate",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "DataRate channelRate",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_DataRate_channelMultiplier,
    {
      "channelMultiplier",
      "h225.DataRate.channelMultiplier",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "DataRate channelMultiplier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_GatekeeperConfirm_requestSeqNum,
    {
      "requestSeqNum",
      "h225.GatekeeperConfirm.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "GatekeeperConfirm requestSeqNum",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_GatekeeperConfirm_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.GatekeeperConfirm.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "GatekeeperConfirm protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_GatekeeperConfirm_gatekeeperIdentifier,
    {
      "gatekeeperIdentifier",
      "h225.GatekeeperConfirm.gatekeeperIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "GatekeeperConfirm gatekeeperIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_GatekeeperConfirm_algorithmOID,
    {
      "algorithmOID",
      "h225.GatekeeperConfirm.algorithmOID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "GatekeeperConfirm algorithmOID",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_GatekeeperReject_requestSeqNum,
    {
      "requestSeqNum",
      "h225.GatekeeperReject.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "GatekeeperReject requestSeqNum",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_GatekeeperReject_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.GatekeeperReject.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "GatekeeperReject protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_GatekeeperReject_gatekeeperIdentifier,
    {
      "gatekeeperIdentifier",
      "h225.GatekeeperReject.gatekeeperIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "GatekeeperReject gatekeeperIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationReject_requestSeqNum,
    {
      "requestSeqNum",
      "h225.RegistrationReject.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "RegistrationReject requestSeqNum",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationReject_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.RegistrationReject.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationReject protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_RegistrationReject_gatekeeperIdentifier,
    {
      "gatekeeperIdentifier",
      "h225.RegistrationReject.gatekeeperIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationReject gatekeeperIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregistrationRequest_requestSeqNum,
    {
      "requestSeqNum",
      "h225.UnregistrationRequest.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "UnregistrationRequest requestSeqNum",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregistrationRequest_endpointIdentifier,
    {
      "endpointIdentifier",
      "h225.UnregistrationRequest.endpointIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UnregistrationRequest endpointIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregistrationRequest_gatekeeperIdentifier,
    {
      "gatekeeperIdentifier",
      "h225.UnregistrationRequest.gatekeeperIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "UnregistrationRequest gatekeeperIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregistrationConfirm_requestSeqNum,
    {
      "requestSeqNum",
      "h225.UnregistrationConfirm.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "UnregistrationConfirm requestSeqNum",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_UnregistrationReject_requestSeqNum,
    {
      "requestSeqNum",
      "h225.UnregistrationReject.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "UnregistrationReject requestSeqNum",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRequest_requestSeqNum,
    {
      "requestSeqNum",
      "h225.AdmissionRequest.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "AdmissionRequest requestSeqNum",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRequest_endpointIdentifier,
    {
      "endpointIdentifier",
      "h225.AdmissionRequest.endpointIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRequest endpointIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRequest_bandWidth,
    {
      "bandWidth",
      "h225.AdmissionRequest.bandWidth",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "AdmissionRequest bandWidth",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRequest_callReferenceValue,
    {
      "callReferenceValue",
      "h225.AdmissionRequest.callReferenceValue",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "AdmissionRequest callReferenceValue",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRequest_conferenceID,
    {
      "conferenceID",
      "h225.AdmissionRequest.conferenceID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRequest conferenceID",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRequest_activeMC,
    {
      "activeMC",
      "h225.AdmissionRequest.activeMC",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRequest activeMC",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRequest_answerCall,
    {
      "answerCall",
      "h225.AdmissionRequest.answerCall",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRequest answerCall",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRequest_canMapAlias,
    {
      "canMapAlias",
      "h225.AdmissionRequest.canMapAlias",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRequest canMapAlias",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRequest_gatekeeperIdentifier,
    {
      "gatekeeperIdentifier",
      "h225.AdmissionRequest.gatekeeperIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRequest gatekeeperIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionRequest_willSupplyUUIEs,
    {
      "willSupplyUUIEs",
      "h225.AdmissionRequest.willSupplyUUIEs",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionRequest willSupplyUUIEs",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_AdmissionReject_requestSeqNum,
    {
      "requestSeqNum",
      "h225.AdmissionReject.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "AdmissionReject requestSeqNum",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandwidthRequest_requestSeqNum,
    {
      "requestSeqNum",
      "h225.BandwidthRequest.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "BandwidthRequest requestSeqNum",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandwidthRequest_endpointIdentifier,
    {
      "endpointIdentifier",
      "h225.BandwidthRequest.endpointIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "BandwidthRequest endpointIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandwidthRequest_conferenceID,
    {
      "conferenceID",
      "h225.BandwidthRequest.conferenceID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "BandwidthRequest conferenceID",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandwidthRequest_callReferenceValue,
    {
      "callReferenceValue",
      "h225.BandwidthRequest.callReferenceValue",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "BandwidthRequest callReferenceValue",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandwidthRequest_bandWidth,
    {
      "bandWidth",
      "h225.BandwidthRequest.bandWidth",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "BandwidthRequest bandWidth",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandwidthRequest_gatekeeperIdentifier,
    {
      "gatekeeperIdentifier",
      "h225.BandwidthRequest.gatekeeperIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "BandwidthRequest gatekeeperIdentifier",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandwidthRequest_answeredCall,
    {
      "answeredCall",
      "h225.BandwidthRequest.answeredCall",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "BandwidthRequest answeredCall",
    }
  },
  {
  &h225Cont.h225_0.hf_h225_BandwidthConfirm_requestSeqNum,
    {
      "requestSeqNum",
      "h225.BandwidthConfirm.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "BandwidthConfirm requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_BandwidthConfirm_bandWidth,
    {
      "bandWidth",
      "h225.BandwidthConfirm.bandWidth",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "BandwidthConfirm bandWidth",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_BandwidthReject_requestSeqNum,
    {
      "requestSeqNum",
      "h225.BandwidthReject.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "BandwidthReject requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_BandwidthReject_allowedBandWidth,
    {
      "allowedBandWidth",
      "h225.BandwidthReject.allowedBandWidth",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "BandwidthReject allowedBandWidth",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_LocationRequest_requestSeqNum,
    {
      "requestSeqNum",
      "h225.LocationRequest.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "LocationRequest requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_LocationRequest_endpointIdentifier,
    {
      "endpointIdentifier",
      "h225.LocationRequest.endpointIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "LocationRequest endpointIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_LocationRequest_canMapAlias,
    {
      "canMapAlias",
      "h225.LocationRequest.canMapAlias",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "LocationRequest canMapAlias",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_LocationRequest_gatekeeperIdentifier,
    {
      "gatekeeperIdentifier",
      "h225.LocationRequest.gatekeeperIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "LocationRequest gatekeeperIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_LocationReject_requestSeqNum,
    {
      "requestSeqNum",
      "h225.LocationReject.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "LocationReject requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_DisengageRequest_requestSeqNum,
    {
      "requestSeqNum",
      "h225.DisengageRequest.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "DisengageRequest requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_DisengageRequest_endpointIdentifier,
    {
      "endpointIdentifier",
      "h225.DisengageRequest.endpointIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "DisengageRequest endpointIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_DisengageRequest_conferenceID,
    {
      "conferenceID",
      "h225.DisengageRequest.conferenceID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "DisengageRequest conferenceID",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_DisengageRequest_callReferenceValue,
    {
      "callReferenceValue",
      "h225.DisengageRequest.callReferenceValue",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "DisengageRequest callReferenceValue",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_DisengageRequest_gatekeeperIdentifier,
    {
      "gatekeeperIdentifier",
      "h225.DisengageRequest.gatekeeperIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "DisengageRequest gatekeeperIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_DisengageRequest_answeredCall,
    {
      "answeredCall",
      "h225.DisengageRequest.answeredCall",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "DisengageRequest answeredCall",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_DisengageConfirm_requestSeqNum,
    {
      "requestSeqNum",
      "h225.DisengageConfirm.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "DisengageConfirm requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_DisengageReject_requestSeqNum,
    {
      "requestSeqNum",
      "h225.DisengageReject.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "DisengageReject requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_InfoRequest_requestSeqNum,
    {
      "requestSeqNum",
      "h225.InfoRequest.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "InfoRequest requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_InfoRequest_callReferenceValue,
    {
      "callReferenceValue",
      "h225.InfoRequest.callReferenceValue",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "InfoRequest callReferenceValue",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RTPSession_cname,
    {
      "cname",
      "h225.RTPSession.cname",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RTPSession cname",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RTPSession_ssrc,
    {
      "ssrc",
      "h225.RTPSession.ssrc",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "RTPSession ssrc",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RTPSession_sessionId,
    {
      "sessionId",
      "h225.RTPSession.sessionId",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "RTPSession sessionId",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_InfoRequestAck_requestSeqNum,
    {
      "requestSeqNum",
      "h225.InfoRequestAck.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "InfoRequestAck requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_InfoRequestNak_requestSeqNum,
    {
      "requestSeqNum",
      "h225.InfoRequestNak.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "InfoRequestNak requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_NonStandardMessage_requestSeqNum,
    {
      "requestSeqNum",
      "h225.NonStandardMessage.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "NonStandardMessage requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_UnknownMessageResponse_requestSeqNum,
    {
      "requestSeqNum",
      "h225.UnknownMessageResponse.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "UnknownMessageResponse requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RequestInProgress_requestSeqNum,
    {
      "requestSeqNum",
      "h225.RequestInProgress.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "RequestInProgress requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RequestInProgress_delay,
    {
      "delay",
      "h225.RequestInProgress.delay",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "RequestInProgress delay",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_ResourcesAvailableIndicate_requestSeqNum,
    {
      "requestSeqNum",
      "h225.ResourcesAvailableIndicate.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "ResourcesAvailableIndicate requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_ResourcesAvailableIndicate_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.ResourcesAvailableIndicate.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ResourcesAvailableIndicate protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_ResourcesAvailableIndicate_endpointIdentifier,
    {
      "endpointIdentifier",
      "h225.ResourcesAvailableIndicate.endpointIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ResourcesAvailableIndicate endpointIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_ResourcesAvailableIndicate_almostOutOfResources,
    {
      "almostOutOfResources",
      "h225.ResourcesAvailableIndicate.almostOutOfResources",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "ResourcesAvailableIndicate almostOutOfResources",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_ResourcesAvailableConfirm_requestSeqNum,
    {
      "requestSeqNum",
      "h225.ResourcesAvailableConfirm.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "ResourcesAvailableConfirm requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_ResourcesAvailableConfirm_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.ResourcesAvailableConfirm.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ResourcesAvailableConfirm protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_TransportAddress_ipSourceRoute_ip,
    {
      "ip",
      "h225.TransportAddress_ipSourceRoute.ip",
      FT_IPv4, 
      BASE_NONE, 
      NULL,
      0x0,
      "TransportAddress_ipSourceRoute ip",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_TransportAddress_ipSourceRoute_port,
    {
      "port",
      "h225.TransportAddress_ipSourceRoute.port",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "TransportAddress_ipSourceRoute port",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_preGrantedARQ_makeCall,
    {
      "makeCall",
      "h225.RegistrationConfirm_preGrantedARQ.makeCall",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationConfirm_preGrantedARQ makeCall",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_preGrantedARQ_useGKCallSignalAddressToMakeCall,
    {
      "useGKCallSignalAddressToMakeCall",
      "h225.RegistrationConfirm_preGrantedARQ.useGKCallSignalAddressToMakeCall",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationConfirm_preGrantedARQ useGKCallSignalAddressToMakeCall",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_preGrantedARQ_answerCall,
    {
      "answerCall",
      "h225.RegistrationConfirm_preGrantedARQ.answerCall",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationConfirm_preGrantedARQ answerCall",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_preGrantedARQ_useGKCallSignalAddressToAnswer,
    {
      "useGKCallSignalAddressToAnswer",
      "h225.RegistrationConfirm_preGrantedARQ.useGKCallSignalAddressToAnswer",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationConfirm_preGrantedARQ useGKCallSignalAddressToAnswer",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_preGrantedARQ_irrFrequencyInCall,
    {
      "irrFrequencyInCall",
      "h225.RegistrationConfirm_preGrantedARQ.irrFrequencyInCall",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "RegistrationConfirm_preGrantedARQ irrFrequencyInCall",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_preGrantedARQ_totalBandwidthRestriction,
    {
      "totalBandwidthRestriction",
      "h225.RegistrationConfirm_preGrantedARQ.totalBandwidthRestriction",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "RegistrationConfirm_preGrantedARQ totalBandwidthRestriction",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_InfoRequestResponse_perCallInfo_subtype_callReferenceValue,
    {
      "callReferenceValue",
      "h225.InfoRequestResponse_perCallInfo_subtype.callReferenceValue",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "InfoRequestResponse_perCallInfo_subtype callReferenceValue",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_InfoRequestResponse_perCallInfo_subtype_conferenceID,
    {
      "conferenceID",
      "h225.InfoRequestResponse_perCallInfo_subtype.conferenceID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "InfoRequestResponse_perCallInfo_subtype conferenceID",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_InfoRequestResponse_perCallInfo_subtype_originator,
    {
      "originator",
      "h225.InfoRequestResponse_perCallInfo_subtype.originator",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "InfoRequestResponse_perCallInfo_subtype originator",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_InfoRequestResponse_perCallInfo_subtype_bandWidth,
    {
      "bandWidth",
      "h225.InfoRequestResponse_perCallInfo_subtype.bandWidth",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "InfoRequestResponse_perCallInfo_subtype bandWidth",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_H323_UU_PDU_h245Tunneling,
    {
      "h245Tunneling",
      "h225.H323_UU_PDU.h245Tunneling",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "H323-UU-PDU h245Tunneling",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_ConferenceList_conferenceID,
    {
      "conferenceID",
      "h225.ConferenceList.conferenceID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ConferenceList conferenceID",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_requestSeqNum,
    {
      "requestSeqNum",
      "h225.RegistrationConfirm.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "RegistrationConfirm requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.RegistrationConfirm.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationConfirm protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_gatekeeperIdentifier,
    {
      "gatekeeperIdentifier",
      "h225.RegistrationConfirm.gatekeeperIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationConfirm gatekeeperIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_endpointIdentifier,
    {
      "endpointIdentifier",
      "h225.RegistrationConfirm.endpointIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationConfirm endpointIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_timeToLive,
    {
      "timeToLive",
      "h225.RegistrationConfirm.timeToLive",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "RegistrationConfirm timeToLive",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_willRespondToIRR,
    {
      "willRespondToIRR",
      "h225.RegistrationConfirm.willRespondToIRR",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationConfirm willRespondToIRR",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationConfirm_maintainConnection,
    {
      "maintainConnection",
      "h225.RegistrationConfirm.maintainConnection",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationConfirm maintainConnection",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_InfoRequestResponse_perCallInfo_subtype_pdu_subtype_sent,
    {
      "sent",
      "h225.InfoRequestResponse_perCallInfo_subtype_pdu_subtype.sent",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "InfoRequestResponse_perCallInfo_subtype_pdu_subtype sent",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_EndpointType_mc,
    {
      "mc",
      "h225.EndpointType.mc",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "EndpointType mc",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_EndpointType_undefinedNode,
    {
      "undefinedNode",
      "h225.EndpointType.undefinedNode",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "EndpointType undefinedNode",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_EndpointType_set,
    {
      "set",
      "h225.EndpointType.set",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "EndpointType set",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Endpoint_priority,
    {
      "priority",
      "h225.Endpoint.priority",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "Endpoint priority",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_GatekeeperRequest_requestSeqNum,
    {
      "requestSeqNum",
      "h225.GatekeeperRequest.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "GatekeeperRequest requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_GatekeeperRequest_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.GatekeeperRequest.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "GatekeeperRequest protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_GatekeeperRequest_gatekeeperIdentifier,
    {
      "gatekeeperIdentifier",
      "h225.GatekeeperRequest.gatekeeperIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "GatekeeperRequest gatekeeperIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationRequest_requestSeqNum,
    {
      "requestSeqNum",
      "h225.RegistrationRequest.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "RegistrationRequest requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationRequest_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.RegistrationRequest.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRequest protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationRequest_discoveryComplete,
    {
      "discoveryComplete",
      "h225.RegistrationRequest.discoveryComplete",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRequest discoveryComplete",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationRequest_gatekeeperIdentifier,
    {
      "gatekeeperIdentifier",
      "h225.RegistrationRequest.gatekeeperIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRequest gatekeeperIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationRequest_timeToLive,
    {
      "timeToLive",
      "h225.RegistrationRequest.timeToLive",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "RegistrationRequest timeToLive",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationRequest_keepAlive,
    {
      "keepAlive",
      "h225.RegistrationRequest.keepAlive",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRequest keepAlive",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationRequest_endpointIdentifier,
    {
      "endpointIdentifier",
      "h225.RegistrationRequest.endpointIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRequest endpointIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationRequest_willSupplyUUIEs,
    {
      "willSupplyUUIEs",
      "h225.RegistrationRequest.willSupplyUUIEs",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRequest willSupplyUUIEs",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_RegistrationRequest_maintainConnection,
    {
      "maintainConnection",
      "h225.RegistrationRequest.maintainConnection",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "RegistrationRequest maintainConnection",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_AdmissionConfirm_requestSeqNum,
    {
      "requestSeqNum",
      "h225.AdmissionConfirm.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "AdmissionConfirm requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_AdmissionConfirm_bandWidth,
    {
      "bandWidth",
      "h225.AdmissionConfirm.bandWidth",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "AdmissionConfirm bandWidth",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_AdmissionConfirm_irrFrequency,
    {
      "irrFrequency",
      "h225.AdmissionConfirm.irrFrequency",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "AdmissionConfirm irrFrequency",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_AdmissionConfirm_willRespondToIRR,
    {
      "willRespondToIRR",
      "h225.AdmissionConfirm.willRespondToIRR",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "AdmissionConfirm willRespondToIRR",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_LocationConfirm_requestSeqNum,
    {
      "requestSeqNum",
      "h225.LocationConfirm.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "LocationConfirm requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_InfoRequestResponse_requestSeqNum,
    {
      "requestSeqNum",
      "h225.InfoRequestResponse.requestSeqNum",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "InfoRequestResponse requestSeqNum",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_InfoRequestResponse_endpointIdentifier,
    {
      "endpointIdentifier",
      "h225.InfoRequestResponse.endpointIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "InfoRequestResponse endpointIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_InfoRequestResponse_needResponse,
    {
      "needResponse",
      "h225.InfoRequestResponse.needResponse",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "InfoRequestResponse needResponse",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Alerting_UUIE_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.Alerting_UUIE.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Alerting-UUIE protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Alerting_UUIE_multipleCalls,
    {
      "multipleCalls",
      "h225.Alerting_UUIE.multipleCalls",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Alerting-UUIE multipleCalls",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Alerting_UUIE_maintainConnection,
    {
      "maintainConnection",
      "h225.Alerting_UUIE.maintainConnection",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Alerting-UUIE maintainConnection",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Alerting_UUIE_screeningIndicator,
    {
      "screeningIndicator",
      "h225.Alerting_UUIE.screeningIndicator",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Alerting-UUIE screeningIndicator",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Alerting_UUIE_fastConnectRefused,
    {
      "fastConnectRefused",
      "h225.Alerting_UUIE.fastConnectRefused",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Alerting-UUIE fastConnectRefused",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_CallProceeding_UUIE_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.CallProceeding_UUIE.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallProceeding-UUIE protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_CallProceeding_UUIE_multipleCalls,
    {
      "multipleCalls",
      "h225.CallProceeding_UUIE.multipleCalls",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallProceeding-UUIE multipleCalls",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_CallProceeding_UUIE_maintainConnection,
    {
      "maintainConnection",
      "h225.CallProceeding_UUIE.maintainConnection",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallProceeding-UUIE maintainConnection",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_CallProceeding_UUIE_fastConnectRefused,
    {
      "fastConnectRefused",
      "h225.CallProceeding_UUIE.fastConnectRefused",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CallProceeding-UUIE fastConnectRefused",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Connect_UUIE_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.Connect_UUIE.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Connect-UUIE protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Connect_UUIE_conferenceID,
    {
      "conferenceID",
      "h225.Connect_UUIE.conferenceID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Connect-UUIE conferenceID",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Connect_UUIE_multipleCalls,
    {
      "multipleCalls",
      "h225.Connect_UUIE.multipleCalls",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Connect-UUIE multipleCalls",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Connect_UUIE_maintainConnection,
    {
      "maintainConnection",
      "h225.Connect_UUIE.maintainConnection",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Connect-UUIE maintainConnection",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Connect_UUIE_screeningIndicator,
    {
      "screeningIndicator",
      "h225.Connect_UUIE.screeningIndicator",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Connect-UUIE screeningIndicator",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Connect_UUIE_fastConnectRefused,
    {
      "fastConnectRefused",
      "h225.Connect_UUIE.fastConnectRefused",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Connect-UUIE fastConnectRefused",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Setup_UUIE_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.Setup_UUIE.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Setup_UUIE_activeMC,
    {
      "activeMC",
      "h225.Setup_UUIE.activeMC",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE activeMC",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Setup_UUIE_conferenceID,
    {
      "conferenceID",
      "h225.Setup_UUIE.conferenceID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE conferenceID",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Setup_UUIE_mediaWaitForConnect,
    {
      "mediaWaitForConnect",
      "h225.Setup_UUIE.mediaWaitForConnect",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE mediaWaitForConnect",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Setup_UUIE_canOverlapSend,
    {
      "canOverlapSend",
      "h225.Setup_UUIE.canOverlapSend",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE canOverlapSend",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Setup_UUIE_endpointIdentifier,
    {
      "endpointIdentifier",
      "h225.Setup_UUIE.endpointIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE endpointIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Setup_UUIE_multipleCalls,
    {
      "multipleCalls",
      "h225.Setup_UUIE.multipleCalls",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE multipleCalls",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Setup_UUIE_maintainConnection,
    {
      "maintainConnection",
      "h225.Setup_UUIE.maintainConnection",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE maintainConnection",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Setup_UUIE_screeningIndicator,
    {
      "screeningIndicator",
      "h225.Setup_UUIE.screeningIndicator",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Setup-UUIE screeningIndicator",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Progress_UUIE_protocolIdentifier,
    {
      "protocolIdentifier",
      "h225.Progress_UUIE.protocolIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Progress-UUIE protocolIdentifier",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Progress_UUIE_multipleCalls,
    {
      "multipleCalls",
      "h225.Progress_UUIE.multipleCalls",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Progress-UUIE multipleCalls",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Progress_UUIE_maintainConnection,
    {
      "maintainConnection",
      "h225.Progress_UUIE.maintainConnection",
      FT_BOOLEAN, 
      BASE_NONE, 
      NULL,
      0x0,
      "Progress-UUIE maintainConnection",
    }
  },
  {
  &h225Cont.h225_1.hf_h225_Progress_UUIE_fastConnectRefused,
    {
      "fastConnectRefused",
      "h225.Progress_UUIE.fastConnectRefused",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Progress-UUIE fastConnectRefused",
    }
  },
};

static gint *etth225[] = 
{
  &h225Cont.h225_0.ett_proto_H225, // Protocol itself 
  &h225Cont.h225_0.ett_h225_ReleaseCompleteReason_choice,
  &h225Cont.h225_0.ett_h225_TransportAddress_choice,
  &h225Cont.h225_0.ett_h225_SupportedProtocols_choice,
  &h225Cont.h225_0.ett_h225_NonStandardIdentifier_choice,
  &h225Cont.h225_0.ett_h225_AliasAddress_choice,
  &h225Cont.h225_0.ett_h225_PartyNumber_choice,
  &h225Cont.h225_0.ett_h225_SecurityServiceMode_choice,
  &h225Cont.h225_0.ett_h225_H245Security_choice,
  &h225Cont.h225_0.ett_h225_EncryptIntAlg_choice,
  &h225Cont.h225_0.ett_h225_NonIsoIntegrityMechanism_choice,
  &h225Cont.h225_0.ett_h225_IntegrityMechanism_choice,
  &h225Cont.h225_0.ett_h225_CryptoH323Token_choice,
  &h225Cont.h225_0.ett_h225_RasMessage_choice,
  &h225Cont.h225_0.ett_h225_RegistrationRejectReason_choice,
  &h225Cont.h225_0.ett_h225_AdmissionRejectReason_choice,
  &h225Cont.h225_0.ett_h225_LocationRejectReason_choice,
  &h225Cont.h225_0.ett_h225_TransportChannelInfo_sendAddress,
  &h225Cont.h225_0.ett_h225_TransportChannelInfo_recvAddress,
  &h225Cont.h225_0.ett_h225_H323_UU_PDU_h323_message_body_choice,
  &h225Cont.h225_0.ett_h225_ArrayOf_NonStandardParameter,
  &h225Cont.h225_0.ett_h225_ArrayOf_ClearToken,
  &h225Cont.h225_0.ett_h225_ArrayOf_CryptoH323Token,
  &h225Cont.h225_0.ett_h225_ArrayOf_AliasAddress,
  &h225Cont.h225_0.ett_h225_ArrayOf_H245Security,
  &h225Cont.h225_0.ett_h225_Setup_UUIE_connectionParameters_connectionType,
  &h225Cont.h225_0.ett_h225_Setup_UUIE_connectionParameters_connectionAggregation,
  &h225Cont.h225_0.ett_h225_ArrayOf_ConferenceList,
  &h225Cont.h225_0.ett_h225_ArrayOf_SupportedProtocols,
  &h225Cont.h225_0.ett_h225_ArrayOf_DataRate,
  &h225Cont.h225_0.ett_h225_ArrayOf_SupportedPrefix,
  &h225Cont.h225_0.ett_h225_ArrayOf_TransportAddress,
  &h225Cont.h225_0.ett_h225_ArrayOf_AlternateGK,
  &h225Cont.h225_0.ett_h225_CryptoH323Token_cryptoEPPwdHash_alias,
  &h225Cont.h225_0.ett_h225_CryptoH323Token_cryptoEPPwdHash_timeStamp,
  &h225Cont.h225_0.ett_h225_CryptoH323Token_cryptoEPPwdHash_token,
  &h225Cont.h225_0.ett_h225_CryptoH323Token_cryptoGKPwdHash_timeStamp,
  &h225Cont.h225_0.ett_h225_CryptoH323Token_cryptoGKPwdHash_token,
  &h225Cont.h225_0.ett_h225_ArrayOf_Endpoint,
  &h225Cont.h225_0.ett_h225_ArrayOf_AuthenticationMechanism,
  &h225Cont.h225_0.ett_h225_ArrayOf_IntegrityMechanism,
  &h225Cont.h225_0.ett_h225_ArrayOf_PartyNumber,
  &h225Cont.h225_0.ett_h225_InfoRequestResponse_perCallInfo,
  &h225Cont.h225_0.ett_h225_ArrayOf_RTPSession,
  &h225Cont.h225_0.ett_h225_ArrayOf_TransportChannelInfo,
  &h225Cont.h225_0.ett_h225_InfoRequestResponse_perCallInfo_subtype_pdu,
  &h225Cont.h225_0.ett_h225_Information_UUIE_callIdentifier,
  &h225Cont.h225_0.ett_h225_Information_UUIE_tokens,
  &h225Cont.h225_0.ett_h225_Information_UUIE_cryptoTokens,
  &h225Cont.h225_0.ett_h225_Information_UUIE_fastStart,
  &h225Cont.h225_0.ett_h225_ReleaseComplete_UUIE_reason,
  &h225Cont.h225_0.ett_h225_ReleaseComplete_UUIE_callIdentifier,
  &h225Cont.h225_0.ett_h225_ReleaseComplete_UUIE_tokens,
  &h225Cont.h225_0.ett_h225_ReleaseComplete_UUIE_cryptoTokens,
  &h225Cont.h225_0.ett_h225_ReleaseComplete_UUIE_busyAddress,
  &h225Cont.h225_0.ett_h225_ReleaseComplete_UUIE_presentationIndicator,
  &h225Cont.h225_0.ett_h225_Facility_UUIE_alternativeAddress,
  &h225Cont.h225_0.ett_h225_Facility_UUIE_alternativeAliasAddress,
  &h225Cont.h225_0.ett_h225_Facility_UUIE_reason,
  &h225Cont.h225_0.ett_h225_Facility_UUIE_callIdentifier,
  &h225Cont.h225_0.ett_h225_Facility_UUIE_destExtraCallInfo,
  &h225Cont.h225_0.ett_h225_Facility_UUIE_remoteExtensionAddress,
  &h225Cont.h225_0.ett_h225_Facility_UUIE_tokens,
  &h225Cont.h225_0.ett_h225_Facility_UUIE_cryptoTokens,
  &h225Cont.h225_0.ett_h225_Facility_UUIE_conferences,
  &h225Cont.h225_0.ett_h225_Facility_UUIE_h245Address,
  &h225Cont.h225_0.ett_h225_Facility_UUIE_fastStart,
  &h225Cont.h225_0.ett_h225_VendorIdentifier_vendor,
  &h225Cont.h225_0.ett_h225_NonStandardParameter_nonStandardIdentifier,
  &h225Cont.h225_0.ett_h225_PublicPartyNumber_publicTypeOfNumber,
  &h225Cont.h225_0.ett_h225_PrivatePartyNumber_privateTypeOfNumber,
  &h225Cont.h225_0.ett_h225_AlternateTransportAddresses_annexE,
  &h225Cont.h225_0.ett_h225_AlternateGK_rasAddress,
  &h225Cont.h225_0.ett_h225_AltGKInfo_alternateGatekeeper,
  &h225Cont.h225_0.ett_h225_SecurityCapabilities_nonStandard,
  &h225Cont.h225_0.ett_h225_SecurityCapabilities_encryption,
  &h225Cont.h225_0.ett_h225_SecurityCapabilities_authenticaton,
  &h225Cont.h225_0.ett_h225_SecurityCapabilities_integrity,
  &h225Cont.h225_0.ett_h225_QseriesOptions_q954Info,
  &h225Cont.h225_0.ett_h225_DataRate_nonStandardData,
  &h225Cont.h225_0.ett_h225_SupportedPrefix_nonStandardData,
  &h225Cont.h225_0.ett_h225_SupportedPrefix_prefix,
  &h225Cont.h225_0.ett_h225_GatekeeperConfirm_nonStandardData,
  &h225Cont.h225_0.ett_h225_GatekeeperConfirm_rasAddress,
  &h225Cont.h225_0.ett_h225_GatekeeperConfirm_alternateGatekeeper,
  &h225Cont.h225_0.ett_h225_GatekeeperConfirm_authenticationMode,
  &h225Cont.h225_0.ett_h225_GatekeeperConfirm_tokens,
  &h225Cont.h225_0.ett_h225_GatekeeperConfirm_cryptoTokens,
  &h225Cont.h225_0.ett_h225_GatekeeperConfirm_integrity,
  &h225Cont.h225_0.ett_h225_GatekeeperConfirm_integrityCheckValue,
  &h225Cont.h225_0.ett_h225_GatekeeperReject_nonStandardData,
  &h225Cont.h225_0.ett_h225_GatekeeperReject_rejectReason,
  &h225Cont.h225_0.ett_h225_GatekeeperReject_altGKInfo,
  &h225Cont.h225_0.ett_h225_GatekeeperReject_tokens,
  &h225Cont.h225_0.ett_h225_GatekeeperReject_cryptoTokens,
  &h225Cont.h225_0.ett_h225_GatekeeperReject_integrityCheckValue,
  &h225Cont.h225_0.ett_h225_RegistrationReject_nonStandardData,
  &h225Cont.h225_0.ett_h225_RegistrationReject_rejectReason,
  &h225Cont.h225_0.ett_h225_RegistrationReject_altGKInfo,
  &h225Cont.h225_0.ett_h225_RegistrationReject_tokens,
  &h225Cont.h225_0.ett_h225_RegistrationReject_cryptoTokens,
  &h225Cont.h225_0.ett_h225_RegistrationReject_integrityCheckValue,
  &h225Cont.h225_0.ett_h225_UnregistrationRequest_callSignalAddress,
  &h225Cont.h225_0.ett_h225_UnregistrationRequest_endpointAlias,
  &h225Cont.h225_0.ett_h225_UnregistrationRequest_nonStandardData,
  &h225Cont.h225_0.ett_h225_UnregistrationRequest_alternateEndpoints,
  &h225Cont.h225_0.ett_h225_UnregistrationRequest_tokens,
  &h225Cont.h225_0.ett_h225_UnregistrationRequest_cryptoTokens,
  &h225Cont.h225_0.ett_h225_UnregistrationRequest_integrityCheckValue,
  &h225Cont.h225_0.ett_h225_UnregistrationRequest_reason,
  &h225Cont.h225_0.ett_h225_UnregistrationConfirm_nonStandardData,
  &h225Cont.h225_0.ett_h225_UnregistrationConfirm_tokens,
  &h225Cont.h225_0.ett_h225_UnregistrationConfirm_cryptoTokens,
  &h225Cont.h225_0.ett_h225_UnregistrationConfirm_integrityCheckValue,
  &h225Cont.h225_0.ett_h225_UnregistrationReject_rejectReason,
  &h225Cont.h225_0.ett_h225_UnregistrationReject_nonStandardData,
  &h225Cont.h225_0.ett_h225_UnregistrationReject_altGKInfo,
  &h225Cont.h225_0.ett_h225_UnregistrationReject_tokens,
  &h225Cont.h225_0.ett_h225_UnregistrationReject_cryptoTokens,
  &h225Cont.h225_0.ett_h225_UnregistrationReject_integrityCheckValue,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_callType,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_callModel,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_destinationInfo,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_destCallSignalAddress,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_destExtraCallInfo,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_srcInfo,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_srcCallSignalAddress,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_nonStandardData,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_callServices,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_callIdentifier,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_srcAlternatives,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_destAlternatives,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_tokens,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_cryptoTokens,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_integrityCheckValue,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_transportQOS,
  &h225Cont.h225_0.ett_h225_AdmissionRequest_callLinkage,
  &h225Cont.h225_0.ett_h225_AdmissionReject_rejectReason,
  &h225Cont.h225_0.ett_h225_AdmissionReject_nonStandardData,
  &h225Cont.h225_0.ett_h225_AdmissionReject_altGKInfo,
  &h225Cont.h225_0.ett_h225_AdmissionReject_tokens,
  &h225Cont.h225_0.ett_h225_AdmissionReject_cryptoTokens,
  &h225Cont.h225_0.ett_h225_AdmissionReject_callSignalAddress,
  &h225Cont.h225_0.ett_h225_AdmissionReject_integrityCheckValue,
  &h225Cont.h225_0.ett_h225_BandwidthRequest_callType,
  &h225Cont.h225_0.ett_h225_BandwidthRequest_nonStandardData,
  &h225Cont.h225_0.ett_h225_BandwidthRequest_callIdentifier,
  &h225Cont.h225_0.ett_h225_BandwidthRequest_tokens,
  &h225Cont.h225_0.ett_h225_BandwidthRequest_cryptoTokens,
  &h225Cont.h225_0.ett_h225_BandwidthRequest_integrityCheckValue,
  &h225Cont.h225_0.ett_h225_BandwidthRequest_callLinkage,
  &h225Cont.h225_1.ett_h225_BandwidthConfirm_nonStandardData,
  &h225Cont.h225_1.ett_h225_BandwidthConfirm_tokens,
  &h225Cont.h225_1.ett_h225_BandwidthConfirm_cryptoTokens,
  &h225Cont.h225_1.ett_h225_BandwidthConfirm_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_BandwidthReject_rejectReason,
  &h225Cont.h225_1.ett_h225_BandwidthReject_nonStandardData,
  &h225Cont.h225_1.ett_h225_BandwidthReject_altGKInfo,
  &h225Cont.h225_1.ett_h225_BandwidthReject_tokens,
  &h225Cont.h225_1.ett_h225_BandwidthReject_cryptoTokens,
  &h225Cont.h225_1.ett_h225_BandwidthReject_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_LocationRequest_destinationInfo,
  &h225Cont.h225_1.ett_h225_LocationRequest_nonStandardData,
  &h225Cont.h225_1.ett_h225_LocationRequest_replyAddress,
  &h225Cont.h225_1.ett_h225_LocationRequest_sourceInfo,
  &h225Cont.h225_1.ett_h225_LocationRequest_tokens,
  &h225Cont.h225_1.ett_h225_LocationRequest_cryptoTokens,
  &h225Cont.h225_1.ett_h225_LocationRequest_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_LocationReject_rejectReason,
  &h225Cont.h225_1.ett_h225_LocationReject_nonStandardData,
  &h225Cont.h225_1.ett_h225_LocationReject_altGKInfo,
  &h225Cont.h225_1.ett_h225_LocationReject_tokens,
  &h225Cont.h225_1.ett_h225_LocationReject_cryptoTokens,
  &h225Cont.h225_1.ett_h225_LocationReject_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_DisengageRequest_disengageReason,
  &h225Cont.h225_1.ett_h225_DisengageRequest_nonStandardData,
  &h225Cont.h225_1.ett_h225_DisengageRequest_callIdentifier,
  &h225Cont.h225_1.ett_h225_DisengageRequest_tokens,
  &h225Cont.h225_1.ett_h225_DisengageRequest_cryptoTokens,
  &h225Cont.h225_1.ett_h225_DisengageRequest_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_DisengageRequest_callLinkage,
  &h225Cont.h225_1.ett_h225_DisengageConfirm_nonStandardData,
  &h225Cont.h225_1.ett_h225_DisengageConfirm_tokens,
  &h225Cont.h225_1.ett_h225_DisengageConfirm_cryptoTokens,
  &h225Cont.h225_1.ett_h225_DisengageConfirm_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_DisengageReject_rejectReason,
  &h225Cont.h225_1.ett_h225_DisengageReject_nonStandardData,
  &h225Cont.h225_1.ett_h225_DisengageReject_altGKInfo,
  &h225Cont.h225_1.ett_h225_DisengageReject_tokens,
  &h225Cont.h225_1.ett_h225_DisengageReject_cryptoTokens,
  &h225Cont.h225_1.ett_h225_DisengageReject_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_InfoRequest_nonStandardData,
  &h225Cont.h225_1.ett_h225_InfoRequest_replyAddress,
  &h225Cont.h225_1.ett_h225_InfoRequest_callIdentifier,
  &h225Cont.h225_1.ett_h225_InfoRequest_tokens,
  &h225Cont.h225_1.ett_h225_InfoRequest_cryptoTokens,
  &h225Cont.h225_1.ett_h225_InfoRequest_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_InfoRequest_uuiesRequested,
  &h225Cont.h225_1.ett_h225_InfoRequest_callLinkage,
  &h225Cont.h225_1.ett_h225_RTPSession_rtpAddress,
  &h225Cont.h225_1.ett_h225_RTPSession_rtcpAddress,
  &h225Cont.h225_1.ett_h225_RTPSession_associatedSessionIds,
  &h225Cont.h225_1.ett_h225_InfoRequestAck_nonStandardData,
  &h225Cont.h225_1.ett_h225_InfoRequestAck_tokens,
  &h225Cont.h225_1.ett_h225_InfoRequestAck_cryptoTokens,
  &h225Cont.h225_1.ett_h225_InfoRequestAck_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_InfoRequestNak_nonStandardData,
  &h225Cont.h225_1.ett_h225_InfoRequestNak_nakReason,
  &h225Cont.h225_1.ett_h225_InfoRequestNak_altGKInfo,
  &h225Cont.h225_1.ett_h225_InfoRequestNak_tokens,
  &h225Cont.h225_1.ett_h225_InfoRequestNak_cryptoTokens,
  &h225Cont.h225_1.ett_h225_InfoRequestNak_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_NonStandardMessage_nonStandardData,
  &h225Cont.h225_1.ett_h225_NonStandardMessage_tokens,
  &h225Cont.h225_1.ett_h225_NonStandardMessage_cryptoTokens,
  &h225Cont.h225_1.ett_h225_NonStandardMessage_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_UnknownMessageResponse_tokens,
  &h225Cont.h225_1.ett_h225_UnknownMessageResponse_cryptoTokens,
  &h225Cont.h225_1.ett_h225_UnknownMessageResponse_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_RequestInProgress_nonStandardData,
  &h225Cont.h225_1.ett_h225_RequestInProgress_tokens,
  &h225Cont.h225_1.ett_h225_RequestInProgress_cryptoTokens,
  &h225Cont.h225_1.ett_h225_RequestInProgress_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_ResourcesAvailableIndicate_nonStandardData,
  &h225Cont.h225_1.ett_h225_ResourcesAvailableIndicate_protocols,
  &h225Cont.h225_1.ett_h225_ResourcesAvailableIndicate_tokens,
  &h225Cont.h225_1.ett_h225_ResourcesAvailableIndicate_cryptoTokens,
  &h225Cont.h225_1.ett_h225_ResourcesAvailableIndicate_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_ResourcesAvailableConfirm_nonStandardData,
  &h225Cont.h225_1.ett_h225_ResourcesAvailableConfirm_tokens,
  &h225Cont.h225_1.ett_h225_ResourcesAvailableConfirm_cryptoTokens,
  &h225Cont.h225_1.ett_h225_ResourcesAvailableConfirm_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_TransportAddress_ipSourceRoute_route,
  &h225Cont.h225_1.ett_h225_TransportAddress_ipSourceRoute_routing,
  &h225Cont.h225_1.ett_h225_RegistrationConfirm_preGrantedARQ_alternateTransportAddresses,
  &h225Cont.h225_1.ett_h225_RegistrationConfirm_preGrantedARQ_useSpecifiedTransport,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_nonStandardData,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_audio,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_video,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_data,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_h245,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_callSignaling,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_callType,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_callModel,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_callIdentifier,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_tokens,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_cryptoTokens,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_substituteConfIDs,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_pdu,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_callLinkage,
  &h225Cont.h225_1.ett_h225_H323_UU_PDU_h323_message_body,
  &h225Cont.h225_1.ett_h225_H323_UU_PDU_nonStandardData,
  &h225Cont.h225_1.ett_h225_H323_UU_PDU_h4501SupplementaryService,
  &h225Cont.h225_1.ett_h225_H323_UU_PDU_h245Control,
  &h225Cont.h225_1.ett_h225_H323_UU_PDU_nonStandardControl,
  &h225Cont.h225_1.ett_h225_H323_UU_PDU_callLinkage,
  &h225Cont.h225_1.ett_h225_ConferenceList_conferenceAlias,
  &h225Cont.h225_1.ett_h225_ConferenceList_nonStandardData,
  &h225Cont.h225_1.ett_h225_GatewayInfo_protocol,
  &h225Cont.h225_1.ett_h225_GatewayInfo_nonStandardData,
  &h225Cont.h225_1.ett_h225_H310Caps_nonStandardData,
  &h225Cont.h225_1.ett_h225_H310Caps_dataRatesSupported,
  &h225Cont.h225_1.ett_h225_H310Caps_supportedPrefixes,
  &h225Cont.h225_1.ett_h225_H320Caps_nonStandardData,
  &h225Cont.h225_1.ett_h225_H320Caps_dataRatesSupported,
  &h225Cont.h225_1.ett_h225_H320Caps_supportedPrefixes,
  &h225Cont.h225_1.ett_h225_H321Caps_nonStandardData,
  &h225Cont.h225_1.ett_h225_H321Caps_dataRatesSupported,
  &h225Cont.h225_1.ett_h225_H321Caps_supportedPrefixes,
  &h225Cont.h225_1.ett_h225_H322Caps_nonStandardData,
  &h225Cont.h225_1.ett_h225_H322Caps_dataRatesSupported,
  &h225Cont.h225_1.ett_h225_H322Caps_supportedPrefixes,
  &h225Cont.h225_1.ett_h225_H323Caps_nonStandardData,
  &h225Cont.h225_1.ett_h225_H323Caps_dataRatesSupported,
  &h225Cont.h225_1.ett_h225_H323Caps_supportedPrefixes,
  &h225Cont.h225_1.ett_h225_H324Caps_nonStandardData,
  &h225Cont.h225_1.ett_h225_H324Caps_dataRatesSupported,
  &h225Cont.h225_1.ett_h225_H324Caps_supportedPrefixes,
  &h225Cont.h225_1.ett_h225_VoiceCaps_nonStandardData,
  &h225Cont.h225_1.ett_h225_VoiceCaps_dataRatesSupported,
  &h225Cont.h225_1.ett_h225_VoiceCaps_supportedPrefixes,
  &h225Cont.h225_1.ett_h225_T120OnlyCaps_nonStandardData,
  &h225Cont.h225_1.ett_h225_T120OnlyCaps_dataRatesSupported,
  &h225Cont.h225_1.ett_h225_T120OnlyCaps_supportedPrefixes,
  &h225Cont.h225_1.ett_h225_NonStandardProtocol_nonStandardData,
  &h225Cont.h225_1.ett_h225_NonStandardProtocol_dataRatesSupported,
  &h225Cont.h225_1.ett_h225_NonStandardProtocol_supportedPrefixes,
  &h225Cont.h225_1.ett_h225_T38FaxAnnexbOnlyCaps_nonStandardData,
  &h225Cont.h225_1.ett_h225_T38FaxAnnexbOnlyCaps_dataRatesSupported,
  &h225Cont.h225_1.ett_h225_T38FaxAnnexbOnlyCaps_supportedPrefixes,
  &h225Cont.h225_1.ett_h225_T38FaxAnnexbOnlyCaps_t38FaxProtocol,
  &h225Cont.h225_1.ett_h225_T38FaxAnnexbOnlyCaps_t38FaxProfile,
  &h225Cont.h225_1.ett_h225_McuInfo_nonStandardData,
  &h225Cont.h225_1.ett_h225_TerminalInfo_nonStandardData,
  &h225Cont.h225_1.ett_h225_GatekeeperInfo_nonStandardData,
  &h225Cont.h225_1.ett_h225_RegistrationConfirm_nonStandardData,
  &h225Cont.h225_1.ett_h225_RegistrationConfirm_callSignalAddress,
  &h225Cont.h225_1.ett_h225_RegistrationConfirm_terminalAlias,
  &h225Cont.h225_1.ett_h225_RegistrationConfirm_alternateGatekeeper,
  &h225Cont.h225_1.ett_h225_RegistrationConfirm_tokens,
  &h225Cont.h225_1.ett_h225_RegistrationConfirm_cryptoTokens,
  &h225Cont.h225_1.ett_h225_RegistrationConfirm_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_RegistrationConfirm_preGrantedARQ,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo_subtype_pdu_subtype_h323pdu,
  &h225Cont.h225_1.ett_h225_H323_UserInformation_h323_uu_pdu,
  &h225Cont.h225_1.ett_h225_H323_UserInformation_user_data,
  &h225Cont.h225_1.ett_h225_EndpointType_nonStandardData,
  &h225Cont.h225_1.ett_h225_EndpointType_vendor,
  &h225Cont.h225_1.ett_h225_EndpointType_gatekeeper,
  &h225Cont.h225_1.ett_h225_EndpointType_gateway,
  &h225Cont.h225_1.ett_h225_EndpointType_mcu,
  &h225Cont.h225_1.ett_h225_EndpointType_terminal,
  &h225Cont.h225_1.ett_h225_Endpoint_nonStandardData,
  &h225Cont.h225_1.ett_h225_Endpoint_aliasAddress,
  &h225Cont.h225_1.ett_h225_Endpoint_callSignalAddress,
  &h225Cont.h225_1.ett_h225_Endpoint_rasAddress,
  &h225Cont.h225_1.ett_h225_Endpoint_endpointType,
  &h225Cont.h225_1.ett_h225_Endpoint_tokens,
  &h225Cont.h225_1.ett_h225_Endpoint_cryptoTokens,
  &h225Cont.h225_1.ett_h225_Endpoint_remoteExtensionAddress,
  &h225Cont.h225_1.ett_h225_Endpoint_destExtraCallInfo,
  &h225Cont.h225_1.ett_h225_Endpoint_alternateTransportAddresses,
  &h225Cont.h225_1.ett_h225_GatekeeperRequest_nonStandardData,
  &h225Cont.h225_1.ett_h225_GatekeeperRequest_rasAddress,
  &h225Cont.h225_1.ett_h225_GatekeeperRequest_endpointType,
  &h225Cont.h225_1.ett_h225_GatekeeperRequest_callServices,
  &h225Cont.h225_1.ett_h225_GatekeeperRequest_endpointAlias,
  &h225Cont.h225_1.ett_h225_GatekeeperRequest_alternateEndpoints,
  &h225Cont.h225_1.ett_h225_GatekeeperRequest_tokens,
  &h225Cont.h225_1.ett_h225_GatekeeperRequest_cryptoTokens,
  &h225Cont.h225_1.ett_h225_GatekeeperRequest_authenticationCapability,
  &h225Cont.h225_1.ett_h225_GatekeeperRequest_algorithmOIDs,
  &h225Cont.h225_1.ett_h225_GatekeeperRequest_integrity,
  &h225Cont.h225_1.ett_h225_GatekeeperRequest_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_RegistrationRequest_nonStandardData,
  &h225Cont.h225_1.ett_h225_RegistrationRequest_callSignalAddress,
  &h225Cont.h225_1.ett_h225_RegistrationRequest_rasAddress,
  &h225Cont.h225_1.ett_h225_RegistrationRequest_terminalType,
  &h225Cont.h225_1.ett_h225_RegistrationRequest_terminalAlias,
  &h225Cont.h225_1.ett_h225_RegistrationRequest_endpointVendor,
  &h225Cont.h225_1.ett_h225_RegistrationRequest_alternateEndpoints,
  &h225Cont.h225_1.ett_h225_RegistrationRequest_tokens,
  &h225Cont.h225_1.ett_h225_RegistrationRequest_cryptoTokens,
  &h225Cont.h225_1.ett_h225_RegistrationRequest_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_RegistrationRequest_alternateTransportAddresses,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_callModel,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_destCallSignalAddress,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_nonStandardData,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_destinationInfo,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_destExtraCallInfo,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_destinationType,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_remoteExtensionAddress,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_alternateEndpoints,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_tokens,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_cryptoTokens,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_transportQOS,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_uuiesRequested,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_language,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_alternateTransportAddresses,
  &h225Cont.h225_1.ett_h225_AdmissionConfirm_useSpecifiedTransport,
  &h225Cont.h225_1.ett_h225_LocationConfirm_callSignalAddress,
  &h225Cont.h225_1.ett_h225_LocationConfirm_rasAddress,
  &h225Cont.h225_1.ett_h225_LocationConfirm_nonStandardData,
  &h225Cont.h225_1.ett_h225_LocationConfirm_destinationInfo,
  &h225Cont.h225_1.ett_h225_LocationConfirm_destExtraCallInfo,
  &h225Cont.h225_1.ett_h225_LocationConfirm_destinationType,
  &h225Cont.h225_1.ett_h225_LocationConfirm_remoteExtensionAddress,
  &h225Cont.h225_1.ett_h225_LocationConfirm_alternateEndpoints,
  &h225Cont.h225_1.ett_h225_LocationConfirm_tokens,
  &h225Cont.h225_1.ett_h225_LocationConfirm_cryptoTokens,
  &h225Cont.h225_1.ett_h225_LocationConfirm_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_LocationConfirm_alternateTransportAddresses,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_nonStandardData,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_endpointType,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_rasAddress,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_callSignalAddress,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_endpointAlias,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_perCallInfo,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_tokens,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_cryptoTokens,
  &h225Cont.h225_1.ett_h225_InfoRequestResponse_integrityCheckValue,
  &h225Cont.h225_1.ett_h225_Alerting_UUIE_destinationInfo,
  &h225Cont.h225_1.ett_h225_Alerting_UUIE_h245Address,
  &h225Cont.h225_1.ett_h225_Alerting_UUIE_callIdentifier,
  &h225Cont.h225_1.ett_h225_Alerting_UUIE_h245SecurityMode,
  &h225Cont.h225_1.ett_h225_Alerting_UUIE_tokens,
  &h225Cont.h225_1.ett_h225_Alerting_UUIE_cryptoTokens,
  &h225Cont.h225_1.ett_h225_Alerting_UUIE_fastStart,
  &h225Cont.h225_1.ett_h225_Alerting_UUIE_alertingAddress,
  &h225Cont.h225_1.ett_h225_Alerting_UUIE_presentationIndicator,
  &h225Cont.h225_1.ett_h225_CallProceeding_UUIE_destinationInfo,
  &h225Cont.h225_1.ett_h225_CallProceeding_UUIE_h245Address,
  &h225Cont.h225_1.ett_h225_CallProceeding_UUIE_callIdentifier,
  &h225Cont.h225_1.ett_h225_CallProceeding_UUIE_h245SecurityMode,
  &h225Cont.h225_1.ett_h225_CallProceeding_UUIE_tokens,
  &h225Cont.h225_1.ett_h225_CallProceeding_UUIE_cryptoTokens,
  &h225Cont.h225_1.ett_h225_CallProceeding_UUIE_fastStart,
  &h225Cont.h225_1.ett_h225_Connect_UUIE_h245Address,
  &h225Cont.h225_1.ett_h225_Connect_UUIE_destinationInfo,
  &h225Cont.h225_1.ett_h225_Connect_UUIE_callIdentifier,
  &h225Cont.h225_1.ett_h225_Connect_UUIE_h245SecurityMode,
  &h225Cont.h225_1.ett_h225_Connect_UUIE_tokens,
  &h225Cont.h225_1.ett_h225_Connect_UUIE_cryptoTokens,
  &h225Cont.h225_1.ett_h225_Connect_UUIE_fastStart,
  &h225Cont.h225_1.ett_h225_Connect_UUIE_language,
  &h225Cont.h225_1.ett_h225_Connect_UUIE_connectedAddress,
  &h225Cont.h225_1.ett_h225_Connect_UUIE_presentationIndicator,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_h245Address,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_sourceAddress,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_sourceInfo,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_destinationAddress,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_destCallSignalAddress,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_destExtraCallInfo,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_destExtraCRV,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_conferenceGoal,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_callServices,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_callType,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_sourceCallSignalAddress,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_remoteExtensionAddress,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_callIdentifier,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_h245SecurityCapability,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_tokens,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_cryptoTokens,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_fastStart,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_connectionParameters,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_language,
  &h225Cont.h225_1.ett_h225_Setup_UUIE_presentationIndicator,
  &h225Cont.h225_1.ett_h225_Progress_UUIE_destinationInfo,
  &h225Cont.h225_1.ett_h225_Progress_UUIE_h245Address,
  &h225Cont.h225_1.ett_h225_Progress_UUIE_callIdentifier,
  &h225Cont.h225_1.ett_h225_Progress_UUIE_h245SecurityMode,
  &h225Cont.h225_1.ett_h225_Progress_UUIE_tokens,
  &h225Cont.h225_1.ett_h225_Progress_UUIE_cryptoTokens,
  &h225Cont.h225_1.ett_h225_Progress_UUIE_fastStart,
};

static hf_register_info hfh235[] = 
{
  {
  &h235Cont.h235_0.hf_h235_NonStandardParameter_nonStandardIdentifier,
    {
      "nonStandardIdentifier",
      "h235.NonStandardParameter.nonStandardIdentifier",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "NonStandardParameter nonStandardIdentifier",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_NonStandardParameter_data,
    {
      "data",
      "h235.NonStandardParameter.data",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "NonStandardParameter data",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_DHset_halfkey,
    {
      "halfkey",
      "h235.DHset.halfkey",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "DHset halfkey",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_DHset_modSize,
    {
      "modSize",
      "h235.DHset.modSize",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "DHset modSize",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_DHset_generator,
    {
      "generator",
      "h235.DHset.generator",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "DHset generator",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_TypedCertificate_type,
    {
      "type",
      "h235.TypedCertificate.type",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "TypedCertificate type",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_TypedCertificate_certificate,
    {
      "certificate",
      "h235.TypedCertificate.certificate",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "TypedCertificate certificate",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_AuthenticationMechanism_dhExch,
    {
      "dhExch",
      "h235.AuthenticationMechanism.dhExch",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AuthenticationMechanism dhExch",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_AuthenticationMechanism_pwdSymEnc,
    {
      "pwdSymEnc",
      "h235.AuthenticationMechanism.pwdSymEnc",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AuthenticationMechanism pwdSymEnc",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_AuthenticationMechanism_pwdHash,
    {
      "pwdHash",
      "h235.AuthenticationMechanism.pwdHash",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AuthenticationMechanism pwdHash",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_AuthenticationMechanism_certSign,
    {
      "certSign",
      "h235.AuthenticationMechanism.certSign",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AuthenticationMechanism certSign",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_AuthenticationMechanism_ipsec,
    {
      "ipsec",
      "h235.AuthenticationMechanism.ipsec",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AuthenticationMechanism ipsec",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_AuthenticationMechanism_tls,
    {
      "tls",
      "h235.AuthenticationMechanism.tls",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "AuthenticationMechanism tls",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_ClearToken_tokenOID,
    {
      "tokenOID",
      "h235.ClearToken.tokenOID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ClearToken tokenOID",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_ClearToken_timeStamp,
    {
      "timeStamp",
      "h235.ClearToken.timeStamp",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "ClearToken timeStamp",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_ClearToken_password,
    {
      "password",
      "h235.ClearToken.password",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ClearToken password",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_ClearToken_challenge,
    {
      "challenge",
      "h235.ClearToken.challenge",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ClearToken challenge",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_ClearToken_random,
    {
      "random",
      "h235.ClearToken.random",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "ClearToken random",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_ClearToken_generalID,
    {
      "generalID",
      "h235.ClearToken.generalID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ClearToken generalID",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_Params_ranInt,
    {
      "ranInt",
      "h235.Params.ranInt",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "Params ranInt",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_Params_iv8,
    {
      "iv8",
      "h235.Params.iv8",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "Params iv8",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_KeySyncMaterial_generalID,
    {
      "generalID",
      "h235.KeySyncMaterial.generalID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "KeySyncMaterial generalID",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_KeySyncMaterial_keyMaterial,
    {
      "keyMaterial",
      "h235.KeySyncMaterial.keyMaterial",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "KeySyncMaterial keyMaterial",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_ReturnSig_generalId,
    {
      "generalId",
      "h235.ReturnSig.generalId",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "ReturnSig generalId",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_ReturnSig_responseRandom,
    {
      "responseRandom",
      "h235.ReturnSig.responseRandom",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "ReturnSig responseRandom",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_ReturnSig_requestRandom,
    {
      "requestRandom",
      "h235.ReturnSig.requestRandom",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "ReturnSig requestRandom",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_KeySignedMaterial_generalId,
    {
      "generalId",
      "h235.KeySignedMaterial.generalId",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "KeySignedMaterial generalId",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_KeySignedMaterial_mrandom,
    {
      "mrandom",
      "h235.KeySignedMaterial.mrandom",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "KeySignedMaterial mrandom",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_KeySignedMaterial_srandom,
    {
      "srandom",
      "h235.KeySignedMaterial.srandom",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "KeySignedMaterial srandom",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_KeySignedMaterial_timeStamp,
    {
      "timeStamp",
      "h235.KeySignedMaterial.timeStamp",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "KeySignedMaterial timeStamp",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_H235CertificateSignature_responseRandom,
    {
      "responseRandom",
      "h235.H235CertificateSignature.responseRandom",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "H235CertificateSignature responseRandom",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_H235CertificateSignature_requesterRandom,
    {
      "requesterRandom",
      "h235.H235CertificateSignature.requesterRandom",
      FT_UINT32, 
      BASE_DEC, 
      NULL,
      0x0,
      "H235CertificateSignature requesterRandom",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_CryptoToken_cryptoEncryptedToken_tokenOID,
    {
      "tokenOID",
      "h235.CryptoToken_cryptoEncryptedToken.tokenOID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CryptoToken_cryptoEncryptedToken tokenOID",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_CryptoToken_cryptoSignedToken_tokenOID,
    {
      "tokenOID",
      "h235.CryptoToken_cryptoSignedToken.tokenOID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CryptoToken_cryptoSignedToken tokenOID",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_CryptoToken_cryptoHashedToken_tokenOID,
    {
      "tokenOID",
      "h235.CryptoToken_cryptoHashedToken.tokenOID",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "CryptoToken_cryptoHashedToken tokenOID",
    }
  },
  {
  &h235Cont.h235_0.hf_h235_H235Key_secureChannel,
    {
      "secureChannel",
      "h235.H235Key.secureChannel",
      FT_STRING, 
      BASE_NONE, 
      NULL,
      0x0,
      "H235Key secureChannel",
    }
  },
};

static gint *etth235[] = 
{
  &h235Cont.h235_0.ett_proto_H235, // Protocol itself 
  &h235Cont.h235_0.ett_h235_AuthenticationMechanism_choice,
  &h235Cont.h235_0.ett_h235_ClearToken_dhkey,
  &h235Cont.h235_0.ett_h235_ClearToken_certificate,
  &h235Cont.h235_0.ett_h235_ClearToken_nonStandard,
  &h235Cont.h235_0.ett_h235_ReturnSig_certificate,
  &h235Cont.h235_0.ett_h235_CryptoToken_choice,
  &h235Cont.h235_0.ett_h235_KeySignedMaterial_encrptval,
  &h235Cont.h235_0.ett_h235_H235CertificateSignature_certificate,
  &h235Cont.h235_0.ett_h235_H235CertificateSignature_signature,
  &h235Cont.h235_0.ett_h235_CryptoToken_cryptoEncryptedToken_token,
  &h235Cont.h235_0.ett_h235_CryptoToken_cryptoSignedToken_token,
  &h235Cont.h235_0.ett_h235_CryptoToken_cryptoHashedToken_hashedVals,
  &h235Cont.h235_0.ett_h235_CryptoToken_cryptoHashedToken_token,
  &h235Cont.h235_0.ett_h235_H235Key_choice,

};

	h225Cont.h225_0.hf_proto_H225 = proto_register_protocol( "ITU-T Recommendation H.225.0", "H.225.0", "h225" );
	proto_register_field_array( h225Cont.h225_0.hf_proto_H225, hfh225, array_length( hfh225 ) );
	proto_register_subtree_array( etth225, array_length( etth225 ) );
	proto_register_field_array( h235Cont.h235_0.hf_proto_H235, hfh235, array_length( hfh235 ) );
	proto_register_subtree_array( etth235, array_length( etth235 ) );

	setH225Container( &h225Cont );
	setH235Container( &h235Cont );

}

void
proto_reg_handoff_h323(void)
{
}

/* Start the functions we need for the plugin stuff */
G_MODULE_EXPORT void
plugin_reg_handoff(void){
  proto_reg_handoff_h323();
}

G_MODULE_EXPORT void
plugin_init(plugin_address_table_t *pat){
  /* initialise the table of pointers needed in Win32 DLLs */
  plugin_address_table_init(pat);
  /* register the new protocol, protocol fields, and subtrees */
  if (h225Cont.h225_0.hf_proto_H225 == -1) { /* execute protocol initialization only once */
    proto_register_h225();
    proto_register_h245();
    proto_register_h450();
  }

  dissector_handle_t h225_handle;
  h225_handle = create_dissector_handle( dissect_h225, h225Cont.h225_0.hf_proto_H225 );
  
  // Register UDP
  dissector_add( "udp.port", 1718, h225_handle );
  dissector_add( "udp.port", 1719, h225_handle );
  
  // CS is called from Q.931 (packet-q931.c/h)
  register_dissector( "h225_cs", dissect_h225, h225Cont.h225_0.hf_proto_H225 );
  proto_reg_handoff_h245();
}
/* End the functions we need for plugin stuff */

} // extern "C"
