
/*
 * object.cxx
 *
 * Global object support.
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
 * $Log: object.cxx,v $
 * Revision 1.42  1999/11/01 00:17:20  robertj
 * Added override of new functions for MSVC memory check code.
 *
 * Revision 1.41  1999/08/22 13:38:39  robertj
 * Fixed termination hang up problem with memory check code under unix pthreads.
 *
 * Revision 1.40  1999/08/10 10:45:09  robertj
 * Added mutex in memory check detection code.
 *
 * Revision 1.39  1999/07/18 15:08:48  robertj
 * Fixed 64 bit compatibility
 *
 * Revision 1.38  1999/05/01 11:29:20  robertj
 * Alpha linux port changes.
 *
 * Revision 1.37  1999/03/09 10:30:17  robertj
 * Fixed ability to have PMEMORY_CHECK on/off on both debug/release versions.
 *
 * Revision 1.36  1999/02/22 10:48:14  robertj
 * Fixed delete operator prototypes for MSVC6 and GNU compatibility.
 *
 * Revision 1.35  1998/12/22 10:24:17  robertj
 * Fixed MSVC warnings caused by changes made in linux PPC support.
 *
 * Revision 1.34  1998/12/15 09:01:10  robertj
 * Fixed 8 byte alignment problem in memory leak check code for sparc.
 *
 * Revision 1.33  1998/11/30 05:33:00  robertj
 * Fixed duplicate debug stream class, ther can be only one.
 *
 * Revision 1.32  1998/11/03 03:11:53  robertj
 * Fixed memory leak question so correctly detects leaks and can be ^C'd.
 *
 * Revision 1.31  1998/11/03 00:55:31  robertj
 * Added allocation breakpoint variable.
 *
 * Revision 1.30  1998/10/15 07:48:56  robertj
 * Added hex dump to memory leak.
 * Added ability to ignore G++lib memory leaks.
 *
 * Revision 1.29  1998/10/15 01:53:35  robertj
 * GNU compatibility.
 *
 * Revision 1.28  1998/10/13 14:06:26  robertj
 * Complete rewrite of memory leak detection code.
 *
 * Revision 1.27  1998/09/23 06:22:22  robertj
 * Added open source copyright license.
 *
 * Revision 1.26  1998/05/30 13:27:02  robertj
 * Changed memory check code so global statics are not included in leak check.
 *
 * Revision 1.25  1997/07/08 13:07:07  robertj
 * DLL support.
 *
 * Revision 1.24  1997/02/09 03:45:28  robertj
 * Fixed unix/dos compatibility with include file.
 *
 * Revision 1.23  1997/02/05 11:54:12  robertj
 * Fixed problems with memory check and leak detection.
 *
 * Revision 1.22  1996/08/08 10:08:46  robertj
 * Directory structure changes for common files.
 *
 * Revision 1.21  1996/07/15 10:35:11  robertj
 * Changed memory leak dump to use static class rather than atexit for better portability.
 *
 * Revision 1.20  1996/06/17 11:35:47  robertj
 * Fixed display of memory leak info, needed flush and use of cin as getchar() does not work with services.
 *
 * Revision 1.19  1996/05/09 12:19:29  robertj
 * Fixed up 64 bit integer class for Mac platform.
 * Fixed incorrect use of memcmp/strcmp return value.
 *
 * Revision 1.18  1996/03/26 00:55:20  robertj
 * Added keypress before dumping memory leaks.
 *
 * Revision 1.17  1996/01/28 02:50:27  robertj
 * Added missing bit shift operators to 64 bit integer class.
 * Added assert into all Compare functions to assure comparison between compatible objects.
 *
 * Revision 1.16  1996/01/23 13:15:52  robertj
 * Mac Metrowerks compiler support.
 *
 * Revision 1.15  1996/01/02 12:52:02  robertj
 * Mac OS compatibility changes.
 *
 * Revision 1.14  1995/11/21 11:51:54  robertj
 * Improved streams compatibility.
 *
 * Revision 1.12  1995/04/25 11:30:34  robertj
 * Fixed Borland compiler warnings.
 * Fixed function hiding ancestors virtual.
 *
 * Revision 1.11  1995/03/12 04:59:53  robertj
 * Re-organisation of DOS/WIN16 and WIN32 platforms to maximise common code.
 * Used built-in equate for WIN32 API (_WIN32).
 *
 * Revision 1.10  1995/02/19  04:19:21  robertj
 * Added dynamically linked command processing.
 *
 * Revision 1.9  1995/01/15  04:52:02  robertj
 * Mac compatibility.
 * Added memory stats function.
 *
// Revision 1.8  1995/01/09  12:38:07  robertj
// Changed variable names around during documentation run.
// Fixed smart pointer comparison.
// Fixed serialisation stuff.
//
// Revision 1.7  1995/01/07  04:39:45  robertj
// Redesigned font enumeration code and changed font styles.
//
// Revision 1.6  1995/01/04  10:57:08  robertj
// Changed for HPUX and GNU2.6.x
//
// Revision 1.5  1995/01/03  09:39:10  robertj
// Put standard malloc style memory allocation etc into memory check system.
//
// Revision 1.4  1994/12/21  11:43:29  robertj
// Added extra memory stats.
//
// Revision 1.3  1994/12/13  11:54:54  robertj
// Added some memory usage statistics.
//
// Revision 1.2  1994/12/12  10:08:32  robertj
// Renamed PWrapper to PSmartPointer..
//
// Revision 1.1  1994/10/30  12:02:15  robertj
// Initial revision
//
 */
#ifdef __GNUC__
#pragma implementation "object.h"
#endif

#include "../include/mini_ptlib.h"
#include <ctype.h>
#ifdef _WIN32
#include <strstrea.h>
#include "../include/ptlib/vc++/debstrm.h"
#else
#include <strstream.h>
#include <signal.h>
#endif


#ifdef MINI_PTLIB

static ostream * PErrorStream = &cerr;

ostream & PGetErrorStream()
{
  return *PErrorStream;
}


void PSetErrorStream(ostream * s)
{
  PErrorStream = s != NULL ? s : &cerr;
}

#endif

void PAssertFunc(const char * file, int line, PStandardAssertMessage msg)
{
  static const char * const textmsg[PMaxStandardAssertMessage] = {
    NULL,
    "Out of memory",
    "Null pointer reference",
    "Invalid cast to non-descendant class",
    "Invalid array index",
    "Invalid array element",
    "Stack empty",
    "Unimplemented function",
    "Invalid parameter",
    "Operating System error",
    "File not open",
    "Unsupported feature",
    "Invalid or closed operating system window"
  };

  const char * theMsg;
  char msgbuf[20];
  if (msg < PMaxStandardAssertMessage)
    theMsg = textmsg[msg];
  else {
    sprintf(msgbuf, "Error code: %i", msg);
    theMsg = msgbuf;
  }
  PAssertFunc(file, line, theMsg);
}


/******************
 * POBJECT
 ******************/

const char * PObject::GetClass(unsigned) const
{
  return Class();
}


BOOL PObject::IsClass(const char * clsName) const
{
  return strcmp(clsName, Class()) == 0;
}


BOOL PObject::IsDescendant(const char * clsName) const
{
  return strcmp(clsName, Class()) == 0;
}


PObject::Comparison PObject::CompareObjectMemoryDirect(const PObject&obj) const
{
  int retval = memcmp(this, &obj, sizeof(PObject));
  if (retval < 0)
    return LessThan;
  if (retval > 0)
    return GreaterThan;
  return EqualTo;
}


PObject * PObject::Clone() const
{
  PAssertAlways(PUnimplementedFunction);
  return NULL;
}


PObject::Comparison PObject::Compare(const PObject & obj) const
{
  return (Comparison)CompareObjectMemoryDirect(obj);
}


void PObject::PrintOn(ostream & strm) const
{
  strm << GetClass();
}


void PObject::ReadFrom(istream &)
{
}


PINDEX PObject::PreSerialise(PSerialiser &)
{
  return 0;
}


void PObject::Serialise(PSerialiser &)
{
}


void PObject::UnSerialise(PUnSerialiser &)
{
}


PINDEX PObject::HashFunction() const
{
  return 0;
}


///////////////////////////////////////////////////////////////////////////////
// Serialisation support

PSerialRegistration * PSerialRegistration::creatorHashTable[
                                           PSerialRegistration::HashTableSize];

PINDEX PSerialRegistration::HashFunction(const char * className)
{
  PINDEX hash = (BYTE)className[0];
  if (className[0] != '\0') {
    hash += (BYTE)className[1];
    if (className[1] != '\0')
      hash += (BYTE)className[2];
  }
  return hash%HashTableSize;
}


PSerialRegistration::PSerialRegistration(const char * clsNam,
                                                          CreatorFunction func)
  : className(clsNam), creator(func)
{
  clash = NULL;

  PINDEX hash = HashFunction(className);
  if (creatorHashTable[hash] != NULL)
    creatorHashTable[hash]->clash = this;
  creatorHashTable[hash] = this;
}


PSerialRegistration::CreatorFunction
                           PSerialRegistration::GetCreator(const char * clsNam)
{
  PINDEX hash = HashFunction(clsNam);
  PSerialRegistration * reg = creatorHashTable[hash];
  while (reg != NULL) {
    if (strcmp(reg->className, clsNam) == 0)
      return reg->creator;
  }
  return NULL;
}


PSerialiser::PSerialiser(ostream & strm)
  : stream(strm)
{
}


PSerialiser & PSerialiser::operator<<(PObject & obj)
{
  obj.Serialise(*this);
  return *this;
}


PTextSerialiser::PTextSerialiser(ostream & strm, PObject & data)
  : PSerialiser(strm)
{
  data.Serialise(*this);
}


PSerialiser & PTextSerialiser::operator<<(char)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(unsigned char)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(signed char)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(short)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(unsigned short)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(int)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(unsigned int)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(long)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(unsigned long)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(float)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(double)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(long double)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(const char *)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(const unsigned char *)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(const signed char *)
  { return *this; }

PSerialiser & PTextSerialiser::operator<<(PObject & obj)
  { return PSerialiser::operator<<(obj); }


PBinarySerialiser::PBinarySerialiser(ostream & strm, PObject & data)
  : PSerialiser(strm)
{
  classesUsed = new PSortedStringList;
  data.PreSerialise(*this);
  stream << *classesUsed;
  data.Serialise(*this);
}


PBinarySerialiser::~PBinarySerialiser()
{
  delete classesUsed;
}


PSerialiser & PBinarySerialiser::operator<<(char)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(unsigned char)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(signed char)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(short)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(unsigned short)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(int)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(unsigned int)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(long)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(unsigned long)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(float)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(double)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(long double)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(const char *)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(const unsigned char *)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(const signed char *)
  { return *this; }

PSerialiser & PBinarySerialiser::operator<<(PObject & obj)
  { return PSerialiser::operator<<(obj); }


PUnSerialiser::PUnSerialiser(istream & strm)
  : stream(strm)
{
}


PTextUnSerialiser::PTextUnSerialiser(istream & strm)
  : PUnSerialiser(strm)
{
}


PUnSerialiser & PTextUnSerialiser::operator>>(char &)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(unsigned char &)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(signed char &)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(short &)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(unsigned short &)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(int &)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(unsigned int &)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(long &)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(unsigned long &)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(float &)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(double &)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(long double &)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(char *)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(unsigned char *)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(signed char *)
  { return *this; }

PUnSerialiser & PTextUnSerialiser::operator>>(PObject &)
  { return *this; }


PBinaryUnSerialiser::PBinaryUnSerialiser(istream & strm)
  : PUnSerialiser(strm)
{
  classesUsed = new PStringArray;
}


PBinaryUnSerialiser::~PBinaryUnSerialiser()
{
  delete classesUsed;
}


PUnSerialiser & PBinaryUnSerialiser::operator>>(char &)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(unsigned char &)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(signed char &)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(short &)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(unsigned short &)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(int &)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(unsigned int &)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(long &)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(unsigned long &)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(float &)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(double &)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(long double &)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(char *)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(unsigned char *)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(signed char *)
  { return *this; }

PUnSerialiser & PBinaryUnSerialiser::operator>>(PObject &)
  { return *this; }


///////////////////////////////////////////////////////////////////////////////
// General reference counting support

PSmartPointer::PSmartPointer(const PSmartPointer & ptr)
{
  object = ptr.object;
  if (object != NULL)
    ++object->referenceCount;
}


PSmartPointer & PSmartPointer::operator=(const PSmartPointer & ptr)
{
  if (object == ptr.object)
    return *this;

  if (object != NULL && --object->referenceCount == 0)
    delete object;

  object = ptr.object;
  if (object != NULL)
    ++object->referenceCount;

  return *this;
}


PSmartPointer::~PSmartPointer()
{
  if (object != NULL && --object->referenceCount == 0)
    delete object;
}


PObject::Comparison PSmartPointer::Compare(const PObject & obj) const
{
  PAssert(obj.IsDescendant(PSmartPointer::Class()), PInvalidCast);
  PSmartObject * other = ((const PSmartPointer &)obj).object;
  if (object == other)
    return EqualTo;
  return object < other ? LessThan : GreaterThan;
}


///////////////////////////////////////////////////////////////////////////////
// Large integer support

#ifdef P_NEEDS_INT64

void PInt64__::Add(const PInt64__ & v)
{
  unsigned long old = low;
  high += v.high;
  low += v.low;
  if (low < old)
    high++;
}


void PInt64__::Sub(const PInt64__ & v)
{
  unsigned long old = low;
  high -= v.high;
  low -= v.low;
  if (low > old)
    high--;
}


void PInt64__::Mul(const PInt64__ & v)
{
  DWORD p1 = (low&0xffff)*(v.low&0xffff);
  DWORD p2 = (low >> 16)*(v.low >> 16);
  DWORD p3 = (high&0xffff)*(v.high&0xffff);
  DWORD p4 = (high >> 16)*(v.high >> 16);
  low = p1 + (p2 << 16);
  high = (p2 >> 16) + p3 + (p4 << 16);
}


void PInt64__::Div(const PInt64__ & v)
{
  long double dividend = high;
  dividend *=  4294967296.0;
  dividend += low;
  long double divisor = high;
  divisor *=  4294967296.0;
  divisor += low;
  long double quotient = dividend/divisor;
  low = quotient;
  high = quotient/4294967296.0;
}


void PInt64__::Mod(const PInt64__ & v)
{
  PInt64__ t = *this;
  t.Div(v);
  t.Mul(t);
  Sub(t);
}


void PInt64__::ShiftLeft(int bits)
{
  if (bits >= 32) {
    high = low << (bits - 32);
    low = 0;
  }
  else {
    high <<= bits;
    high |= low >> (32 - bits);
    low <<= bits;
  }
}


void PInt64__::ShiftRight(int bits)
{
  if (bits >= 32) {
    low = high >> (bits - 32);
    high = 0;
  }
  else {
    low >>= bits;
    low |= high << (32 - bits);
    high >>= bits;
  }
}


BOOL PInt64::Lt(const PInt64 & v) const
{
  if ((long)high < (long)v.high)
    return TRUE;
  if ((long)high > (long)v.high)
    return FALSE;
  if ((long)high < 0)
    return (long)low > (long)v.low;
  return (long)low < (long)v.low;
}


BOOL PInt64::Gt(const PInt64 & v) const
{
  if ((long)high > (long)v.high)
    return TRUE;
  if ((long)high < (long)v.high)
    return FALSE;
  if ((long)high < 0)
    return (long)low < (long)v.low;
  return (long)low > (long)v.low;
}


BOOL PUInt64::Lt(const PUInt64 & v) const
{
  if (high < v.high)
    return TRUE;
  if (high > v.high)
    return FALSE;
  return low < high;
}


BOOL PUInt64::Gt(const PUInt64 & v) const
{
  if (high > v.high)
    return TRUE;
  if (high < v.high)
    return FALSE;
  return low > high;
}


static void Out64(ostream & stream, PUInt64 num)
{
  char buf[25];
  char * p = &buf[sizeof(buf)];
  *--p = '\0';

  switch (stream.flags()&ios::basefield) {
    case ios::oct :
      while (num != 0) {
        *--p = (num&7) + '0';
        num >>= 3;
      }
      break;

    case ios::hex :
      while (num != 0) {
        *--p = (num&15) + '0';
        if (*p > '9')
          *p += 7;
        num >>= 4;
      }
      break;

    default :
      while (num != 0) {
        *--p = num%10 + '0';
        num /= 10;
      }
  }

  if (*p == '\0')
    *--p = '0';

  stream << p;
}


ostream & operator<<(ostream & stream, const PInt64 & v)
{
  if (v >= 0)
    Out64(stream, v);
  else {
    int w = stream.width();
    stream.put('-');
    if (w > 0)
      stream.width(w-1);
    Out64(stream, -v);
  }

  return stream;
}


ostream & operator<<(ostream & stream, const PUInt64 & v)
{
  Out64(stream, v);
  return stream;
}


static PUInt64 Inp64(istream & stream)
{
  int base;
  switch (stream.flags()&ios::basefield) {
    case ios::oct :
      base = 8;
      break;
    case ios::hex :
      base = 16;
      break;
    default :
      base = 10;
  }

  if (isspace(stream.peek()))
    stream.get();

  PInt64 num = 0;
  while (isxdigit(stream.peek())) {
    int c = stream.get() - '0';
    if (c > 9)
      c -= 7;
    if (c > 9)
      c -= 32;
    num = num*base + c;
  }

  return num;
}


istream & operator>>(istream & stream, PInt64 & v)
{
  if (isspace(stream.peek()))
    stream.get();

  switch (stream.peek()) {
    case '-' :
      stream.ignore();
      v = -(PInt64)Inp64(stream);
      break;
    case '+' :
      stream.ignore();
    default :
      v = (PInt64)Inp64(stream);
  }

  return stream;
}


istream & operator>>(istream & stream, PUInt64 & v)
{
  v = Inp64(stream);
  return stream;
}


#endif

static PUInt64 Inp64(istream & stream)
{
  int base;
  switch (stream.flags()&ios::basefield) {
    case ios::oct :
      base = 8;
      break;
    case ios::hex :
      base = 16;
      break;
    default :
      base = 10;
  }

  if (isspace(stream.peek()))
    stream.get();

  PInt64 num = 0;
  while (isxdigit(stream.peek())) {
    int c = stream.get() - '0';
    if (c > 9)
      c -= 7;
    if (c > 9)
      c -= 32;
    num = num*base + c;
  }

  return num;
}

istream & operator>>(istream & stream, PInt64 & v)
{
  if (isspace(stream.peek()))
    stream.get();

  switch (stream.peek()) {
    case '-' :
      stream.ignore();
      v = -(PInt64)Inp64(stream);
      break;
    case '+' :
      stream.ignore();
    default :
      v = (PInt64)Inp64(stream);
  }

  return stream;
}



// End Of File ///////////////////////////////////////////////////////////////
