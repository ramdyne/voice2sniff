/* 
 * packet-h225.h
 *
 * Header for regsitering the H.225 protocol
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


void dissect_h225_ras( tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree );
gboolean dissect_h225_cs( tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree );
void proto_register_h225( void );
