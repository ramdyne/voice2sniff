/*
 * ptlib.h
 *
 * Umbrella include for all non-GUI classes.
 *
 * Portable Windows Library
 *
 * Copyright (c) 1993-1998 Equivalence Pty. Ltd.
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
 * The Original Code is Portable Windows Library.
 *
 * The Initial Developer of the Original Code is Equivalence Pty. Ltd.
 *
 * Portions are Copyright (C) 1993 Free Software Foundation, Inc.
 * All Rights Reserved.
 *
 * Contributor(s): ______________________________________.
 *
 * $Log: ptlib.h,v $
 * Revision 1.1  2000/01/06 20:38:11  dliu
 * place under cvs
 *
 * Revision 1.21  1999/08/17 03:46:40  robertj
 * Fixed usage of inlines in optimised version.
 *
 * Revision 1.20  1999/06/17 13:38:11  robertj
 * Fixed race condition on indirect channel close, mutex needed in PIndirectChannel.
 *
 * Revision 1.19  1999/06/13 13:54:07  robertj
 * Added PConsoleChannel class for access to stdin/stdout/stderr.
 *
 * Revision 1.18  1998/11/30 22:08:56  robertj
 * Fixed backslash in #include
 *
 * Revision 1.17  1998/11/30 02:50:43  robertj
 * New directory structure
 *
 * Revision 1.16  1998/10/31 12:46:57  robertj
 * Renamed file for having general thread synchronisation objects.
 *
 * Revision 1.15  1998/09/23 06:19:52  robertj
 * Added open source copyright license.
 *
 * Revision 1.14  1998/05/30 13:25:00  robertj
 * Added PSyncPointAck class.
 *
 * Revision 1.13  1998/03/20 03:16:10  robertj
 * Added special classes for specific sepahores, PMutex and PSyncPoint.
 *
 * Revision 1.12  1996/09/14 13:09:16  robertj
 * Major upgrade:
 *   rearranged sockets to help support IPX.
 *   added indirect channel class and moved all protocols to descend from it,
 *   separating the protocol from the low level byte transport.
 *
 * Revision 1.11  1996/08/08 10:08:40  robertj
 * Directory structure changes for common files.
 *
 * Revision 1.10  1996/05/23 09:57:24  robertj
 * Changed process.h to pprocess.h to avoid name conflict.
 *
 * Revision 1.9  1995/07/31 12:06:21  robertj
 * Added semaphore class.
 *
 * Revision 1.8  1995/03/12 04:44:56  robertj
 * Added dynamic link libraries.
 *
 * Revision 1.7  1994/09/25  10:43:57  robertj
 * Added pipe channel.
 *
 * Revision 1.6  1994/08/23  11:32:52  robertj
 * Oops
 *
 * Revision 1.5  1994/08/22  00:46:48  robertj
 * Added pragma fro GNU C++ compiler.
 *
 * Revision 1.4  1994/07/25  03:36:03  robertj
 * Added sockets to common, normalising to same comment standard.
 *
 * Revision 1.3  1994/07/21  12:17:41  robertj
 * Sockets.
 *
 * Revision 1.2  1994/06/25  12:27:39  robertj
 * *** empty log message ***
 *
 * Revision 1.1  1994/04/01  14:38:42  robertj
 * Initial revision
 *
 */

#ifndef _PTLIB_H
#define _PTLIB_H

#ifdef __GNUC__
#pragma interface
#endif

#include <limits.h>
#include "ptlib/contain.h"
//#include "ptlib/ptime.h"
//#include <ptlib/channel.h>
//#include <ptlib/filepath.h>
//#include <ptlib/file.h>
//#include <ptlib/textfile.h>

#include "ptlib/args.h"

//#if P_USE_INLINES
//#include <ptlib/ptlib.inl>
//#include <ptlib/osutil.inl>
//#endif

#endif // _PTLIB_H


// End Of File ///////////////////////////////////////////////////////////////
