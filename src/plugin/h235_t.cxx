/* 
 * h235_t.cxx
 *
 * Template implementation for H.235
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
// h235_t.cxx
//
// Code automatically generated by asnparse.
//

//
// SIGNED
//

template <class ToBeSigned>
H235_SIGNED<ToBeSigned>::H235_SIGNED(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 0, FALSE, 0)
{
}


#ifndef PASN_NOPRINTON
template <class ToBeSigned>
void H235_SIGNED<ToBeSigned>::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << "{\n";
  strm << setw(indent+13) << "toBeSigned = " << setprecision(indent) << m_toBeSigned << '\n';
  strm << setw(indent+15) << "algorithmOID = " << setprecision(indent) << m_algorithmOID << '\n';
  strm << setw(indent+9) << "paramS = " << setprecision(indent) << m_paramS << '\n';
  strm << setw(indent+12) << "signature = " << setprecision(indent) << m_signature << '\n';
  strm << setw(indent-1) << "}";
}
#endif


template <class ToBeSigned>
PObject::Comparison H235_SIGNED<ToBeSigned>::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsDescendant(H235_SIGNED<ToBeSigned>::Class()), PInvalidCast);
#endif
  const H235_SIGNED<ToBeSigned> & other = (const H235_SIGNED<ToBeSigned> &)obj;

  Comparison result;

  if ((result = m_toBeSigned.Compare(other.m_toBeSigned)) != EqualTo)
    return result;
  if ((result = m_algorithmOID.Compare(other.m_algorithmOID)) != EqualTo)
    return result;
  if ((result = m_paramS.Compare(other.m_paramS)) != EqualTo)
    return result;
  if ((result = m_signature.Compare(other.m_signature)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


template <class ToBeSigned>
PINDEX H235_SIGNED<ToBeSigned>::GetDataLength() const
{
  return m_toBeSigned.GetObjectLength() +
         m_algorithmOID.GetObjectLength() +
         m_paramS.GetObjectLength() +
         m_signature.GetObjectLength();
}


template <class ToBeSigned>
BOOL H235_SIGNED<ToBeSigned>::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (!m_toBeSigned.Decode(strm))
    return FALSE;
  if (!m_algorithmOID.Decode(strm))
    return FALSE;
  if (!m_paramS.Decode(strm))
    return FALSE;
  if (!m_signature.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


template <class ToBeSigned>
void H235_SIGNED<ToBeSigned>::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  m_toBeSigned.Encode(strm);
  m_algorithmOID.Encode(strm);
  m_paramS.Encode(strm);
  m_signature.Encode(strm);

  UnknownExtensionsEncode(strm);
}


template <class ToBeSigned>
PObject * H235_SIGNED<ToBeSigned>::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H235_SIGNED<ToBeSigned>::Class()), PInvalidCast);
#endif
  return new H235_SIGNED<ToBeSigned>(*this);
}


//
// ENCRYPTED
//

template <class ToBeEncrypted>
H235_ENCRYPTED<ToBeEncrypted>::H235_ENCRYPTED(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 0, FALSE, 0)
{
}


#ifndef PASN_NOPRINTON
template <class ToBeEncrypted>
void H235_ENCRYPTED<ToBeEncrypted>::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << "{\n";
  strm << setw(indent+15) << "algorithmOID = " << setprecision(indent) << m_algorithmOID << '\n';
  strm << setw(indent+9) << "paramS = " << setprecision(indent) << m_paramS << '\n';
  strm << setw(indent+16) << "encryptedData = " << setprecision(indent) << m_encryptedData << '\n';
  strm << setw(indent-1) << "}";
}
#endif


template <class ToBeEncrypted>
PObject::Comparison H235_ENCRYPTED<ToBeEncrypted>::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsDescendant(H235_ENCRYPTED<ToBeEncrypted>::Class()), PInvalidCast);
#endif
  const H235_ENCRYPTED<ToBeEncrypted> & other = (const H235_ENCRYPTED<ToBeEncrypted> &)obj;

  Comparison result;

  if ((result = m_algorithmOID.Compare(other.m_algorithmOID)) != EqualTo)
    return result;
  if ((result = m_paramS.Compare(other.m_paramS)) != EqualTo)
    return result;
  if ((result = m_encryptedData.Compare(other.m_encryptedData)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


template <class ToBeEncrypted>
PINDEX H235_ENCRYPTED<ToBeEncrypted>::GetDataLength() const
{
  return m_algorithmOID.GetObjectLength() +
         m_paramS.GetObjectLength() +
         m_encryptedData.GetObjectLength();
}


template <class ToBeEncrypted>
BOOL H235_ENCRYPTED<ToBeEncrypted>::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (!m_algorithmOID.Decode(strm))
    return FALSE;
  if (!m_paramS.Decode(strm))
    return FALSE;
  if (!m_encryptedData.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


template <class ToBeEncrypted>
void H235_ENCRYPTED<ToBeEncrypted>::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  m_algorithmOID.Encode(strm);
  m_paramS.Encode(strm);
  m_encryptedData.Encode(strm);

  UnknownExtensionsEncode(strm);
}


template <class ToBeEncrypted>
PObject * H235_ENCRYPTED<ToBeEncrypted>::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H235_ENCRYPTED<ToBeEncrypted>::Class()), PInvalidCast);
#endif
  return new H235_ENCRYPTED<ToBeEncrypted>(*this);
}


//
// HASHED
//

template <class ToBeHashed>
H235_HASHED<ToBeHashed>::H235_HASHED(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 0, FALSE, 0)
{
}


#ifndef PASN_NOPRINTON
template <class ToBeHashed>
void H235_HASHED<ToBeHashed>::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << "{\n";
  strm << setw(indent+15) << "algorithmOID = " << setprecision(indent) << m_algorithmOID << '\n';
  strm << setw(indent+9) << "paramS = " << setprecision(indent) << m_paramS << '\n';
  strm << setw(indent+7) << "hash = " << setprecision(indent) << m_hash << '\n';
  strm << setw(indent-1) << "}";
}
#endif


template <class ToBeHashed>
PObject::Comparison H235_HASHED<ToBeHashed>::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsDescendant(H235_HASHED<ToBeHashed>::Class()), PInvalidCast);
#endif
  const H235_HASHED<ToBeHashed> & other = (const H235_HASHED<ToBeHashed> &)obj;

  Comparison result;

  if ((result = m_algorithmOID.Compare(other.m_algorithmOID)) != EqualTo)
    return result;
  if ((result = m_paramS.Compare(other.m_paramS)) != EqualTo)
    return result;
  if ((result = m_hash.Compare(other.m_hash)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


template <class ToBeHashed>
PINDEX H235_HASHED<ToBeHashed>::GetDataLength() const
{
  return m_algorithmOID.GetObjectLength() +
         m_paramS.GetObjectLength() +
         m_hash.GetObjectLength();
}


template <class ToBeHashed>
BOOL H235_HASHED<ToBeHashed>::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (!m_algorithmOID.Decode(strm))
    return FALSE;
  if (!m_paramS.Decode(strm))
    return FALSE;
  if (!m_hash.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


template <class ToBeHashed>
void H235_HASHED<ToBeHashed>::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  m_algorithmOID.Encode(strm);
  m_paramS.Encode(strm);
  m_hash.Encode(strm);

  UnknownExtensionsEncode(strm);
}


template <class ToBeHashed>
PObject * H235_HASHED<ToBeHashed>::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H235_HASHED<ToBeHashed>::Class()), PInvalidCast);
#endif
  return new H235_HASHED<ToBeHashed>(*this);
}



// End of h235_t.cxx
