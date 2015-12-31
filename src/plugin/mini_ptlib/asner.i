
class PASN_Stream;
class PBER_Stream;
class PPER_Stream;

class PChannel {
public:
    int i;
	PChannel() { }
	~PChannel() { }
};





class PASN_Object : public PObject
{
    public: static const char * Class() { return "PASN_Object"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PObject::GetClass(ancestor-1) : PASN_Object::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_Object::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_Object::Class()) == 0 || PObject::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_Object)); } ;
  public:
    
    virtual PString GetTypeAsString() const = 0;

    int GetObjectLength() const;
    virtual int GetDataLength() const = 0;
    virtual BOOL IsPrimitive() const { return 1; }

    virtual BOOL Decode(PASN_Stream &) = 0;
    virtual void Encode(PASN_Stream &) const = 0;

    BOOL IsExtendable() const { return extendable; }
    void SetExtendable(BOOL ext = 1) { extendable = ext; }

    enum TagClass {
      UniversalTagClass,
      ApplicationTagClass,
      ContextSpecificTagClass,
      PrivateTagClass,
      DefaultTagClass
    };
    TagClass GetTagClass() const { return tagClass; }

    enum UniversalTags {
      InvalidUniversalTag,
      UniversalBoolean,
      UniversalInteger,
      UniversalBitString,
      UniversalOctetString,
      UniversalNull,
      UniversalObjectId,
      UniversalObjectDescriptor,
      UniversalExternalType,
      UniversalReal,
      UniversalEnumeration,
      UniversalEmbeddedPDV,
      UniversalSequence = 16,
      UniversalSet,
      UniversalNumericString,
      UniversalPrintableString,
      UniversalTeletexString,
      UniversalVideotexString,
      UniversalIA5String,
      UniversalUTCTime,
      UniversalGeneralisedTime,
      UniversalGraphicString,
      UniversalVisibleString,
      UniversalGeneralString,
      UniversalUniversalString,
      UniversalBMPString = 30
    };

    unsigned GetTag() const  { return tag; }
    virtual void SetTag(unsigned newTag, TagClass tagClass = DefaultTagClass);

    enum ConstraintType {
      Unconstrained,
      PartiallyConstrained,
      FixedConstraint,
      ExtendableConstraint
    };

    enum MinimumValueTag { MinimumValue = (-2147483647 - 1) };
    enum MaximumValueTag { MaximumValue = 2147483647 };
    void SetConstraints(ConstraintType type, int lower, MaximumValueTag upper);
    void SetConstraints(ConstraintType type, MinimumValueTag lower, unsigned upper);
    void SetConstraints(ConstraintType type, MinimumValueTag lower, MaximumValueTag upper);
    virtual void SetConstraints(ConstraintType type, int lower = 0, unsigned upper = 0xffffffff);
    virtual void SetCharacterSet(ConstraintType ctype, const char * charSet);
    virtual void SetCharacterSet(ConstraintType ctype, unsigned firstChar, unsigned lastChar);
		
		virtual void showEthereal( proto_tree *, tvbuff_t*, unsigned int ) const { return; }
		virtual void setContainer( PObject* ) { return; }
		virtual void preShowEthereal( void ) { return; }
		virtual PString getSummary( void ) { return "PASN_Object"; }
		void SetStartbyte( unsigned int byte );
		void SetStopbyte( unsigned int byte );
		unsigned int GetByteLength( void ) const;
		unsigned int GetStartByte( void ) const;

  protected:
    PASN_Object(unsigned tag, TagClass tagClass, BOOL extend = 0);

    
    BOOL extendable;
    
    TagClass tagClass;
    
    unsigned tag;
	private:
		unsigned int startbyte;
		unsigned int stopbyte;
};




class PASN_ConstrainedObject : public PASN_Object
{
    public: static const char * Class() { return "PASN_ConstrainedObject"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_Object::GetClass(ancestor-1) : PASN_ConstrainedObject::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_ConstrainedObject::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_ConstrainedObject::Class()) == 0 || PASN_Object::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_ConstrainedObject)); } ;
  public:
    virtual void SetConstraints(ConstraintType type, int lower = 0, unsigned upper = 0xffffffff);
    BOOL IsConstrained() const { return constraint != Unconstrained; }
    int GetLowerLimit() const { return lowerLimit; }
    unsigned GetUpperLimit() const { return upperLimit; }

    int ConstrainedLengthDecode(PPER_Stream & strm, unsigned & length);
    void ConstrainedLengthEncode(PPER_Stream & strm, unsigned length) const;

    BOOL ConstraintEncode(PPER_Stream & strm, unsigned value) const;

  protected:
    PASN_ConstrainedObject(unsigned tag, TagClass tagClass);

    ConstraintType constraint;
    int lowerLimit;
    unsigned upperLimit;
};




class PASN_Null : public PASN_Object
{
    public: static const char * Class() { return "PASN_Null"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_Object::GetClass(ancestor-1) : PASN_Null::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_Null::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_Null::Class()) == 0 || PASN_Object::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_Null)); } ;
  public:
    PASN_Null(unsigned tag = UniversalNull,
              TagClass tagClass = UniversalTagClass);

    virtual Comparison Compare(const PObject & obj) const;
    virtual PObject * Clone() const;
    virtual void PrintOn(ostream & strm) const;

    virtual PString GetTypeAsString() const;
    virtual int GetDataLength() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;
};




class PASN_Boolean : public PASN_Object
{
    public: static const char * Class() { return "PASN_Boolean"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_Object::GetClass(ancestor-1) : PASN_Boolean::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_Boolean::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_Boolean::Class()) == 0 || PASN_Object::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_Boolean)); } ;
  public:
    PASN_Boolean(BOOL val = 0,
                 unsigned tag = UniversalBoolean,
                 TagClass tagClass = UniversalTagClass);

    PASN_Boolean & operator=(BOOL v) { value = v; return *this; }
    operator BOOL() const { return value; }
    BOOL GetValue() const { return value; }
    void SetValue(BOOL v) { value = v; }

    virtual Comparison Compare(const PObject & obj) const;
    virtual PObject * Clone() const;
    virtual void PrintOn(ostream & strm) const;

    virtual PString GetTypeAsString() const;
    virtual int GetDataLength() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;

  protected:
    BOOL value;
};




class PASN_Integer : public PASN_ConstrainedObject
{
    public: static const char * Class() { return "PASN_Integer"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_ConstrainedObject::GetClass(ancestor-1) : PASN_Integer::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_Integer::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_Integer::Class()) == 0 || PASN_ConstrainedObject::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_Integer)); } ;
  public:
    PASN_Integer(unsigned tag = UniversalInteger,
                 TagClass tagClass = UniversalTagClass,
                 unsigned val = 0);

    PASN_Integer & operator=(unsigned value);
    operator unsigned() const { return value; }
    unsigned GetValue() const { return value; }
    void SetValue(unsigned v) { operator=(v); }

    virtual Comparison Compare(const PObject & obj) const;
    virtual PObject * Clone() const;
    virtual void PrintOn(ostream & strm) const;

    virtual PString GetTypeAsString() const;
    virtual int GetDataLength() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;

    BOOL DecodePER(PPER_Stream & strm);
    void EncodePER(PPER_Stream & strm) const;

  protected:
    unsigned value;
};




class PASN_Enumeration : public PASN_Object
{
    public: static const char * Class() { return "PASN_Enumeration"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_Object::GetClass(ancestor-1) : PASN_Enumeration::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_Enumeration::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_Enumeration::Class()) == 0 || PASN_Object::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_Enumeration)); } ;
  public:
    PASN_Enumeration(unsigned tag = UniversalEnumeration,
                     TagClass tagClass = UniversalTagClass,
                     unsigned nEnums = P_MAX_INDEX,
                     BOOL extendable = 0,
                     unsigned val = 0);
    PASN_Enumeration(unsigned tag,
                     TagClass tagClass,
                     unsigned nEnums,
                     BOOL extendable,
                     const PString & nameSpec,
                     unsigned val = 0);

    PASN_Enumeration & operator=(unsigned v) { value = v; return *this; }
    operator unsigned() const { return value; }
    unsigned GetValue() const { return value; }
    void SetValue(unsigned v) { value = v; }

    unsigned GetMaximum() const { return maxEnumValue; }

    virtual Comparison Compare(const PObject & obj) const;
    virtual PObject * Clone() const;
    virtual void PrintOn(ostream & strm) const;

    virtual PString GetTypeAsString() const;
    virtual int GetDataLength() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;

    BOOL DecodePER(PPER_Stream & strm);
    void EncodePER(PPER_Stream & strm) const;

		virtual char* getValue( void ) const;

  protected:
    unsigned maxEnumValue;
    unsigned value;
    POrdinalToString names;
};




class PASN_Real : public PASN_Object
{
    public: static const char * Class() { return "PASN_Real"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_Object::GetClass(ancestor-1) : PASN_Real::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_Real::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_Real::Class()) == 0 || PASN_Object::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_Real)); } ;
  public:
    PASN_Real(unsigned tag = UniversalEnumeration,
              TagClass tagClass = UniversalTagClass,
              double val = 0);

    PASN_Real & operator=(double val) { value = val; return *this; }
    operator double() const { return value; }
    double GetValue() const { return value; }
    void SetValue(double v) { value = v; }

    virtual Comparison Compare(const PObject & obj) const;
    virtual PObject * Clone() const;
    virtual void PrintOn(ostream & strm) const;

    virtual PString GetTypeAsString() const;
    virtual int GetDataLength() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;

  protected:
    double value;
};




class PASN_ObjectId : public PASN_Object
{
    public: static const char * Class() { return "PASN_ObjectId"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_Object::GetClass(ancestor-1) : PASN_ObjectId::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_ObjectId::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_ObjectId::Class()) == 0 || PASN_Object::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_ObjectId)); } ;
  public:
    PASN_ObjectId(unsigned tag = UniversalObjectId,
                  TagClass tagClass = UniversalTagClass);

    PASN_ObjectId(const PASN_ObjectId & other);
    PASN_ObjectId & operator=(const PASN_ObjectId & other);

    PASN_ObjectId & operator=(const char * dotstr);
    PASN_ObjectId & operator=(const PString & dotstr);
    void SetValue(const PString & dotstr);

    BOOL operator==(const char * dotstr) const;
    BOOL operator!=(const char * dotstr) const { return !operator==(dotstr); }
    BOOL operator==(const PASN_ObjectId & id) const { return value == id.value; }

    int GetSize() const { return value.GetSize(); }
    const PUnsignedArray & GetValue() const { return value; }
    unsigned operator[](int idx) const { return value[idx]; }

    virtual Comparison Compare(const PObject & obj) const;
    virtual PObject * Clone() const;
    virtual void PrintOn(ostream & strm) const;

    virtual PString GetTypeAsString() const;
    virtual int GetDataLength() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;

		virtual char* getValue( void ) const;

    BOOL CommonDecode(PASN_Stream & strm, unsigned dataLen);
    void CommonEncode(PBYTEArray & eObjId) const;

  protected:
    PUnsignedArray value;
};




class PASN_BitString : public PASN_ConstrainedObject
{
    public: static const char * Class() { return "PASN_BitString"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_ConstrainedObject::GetClass(ancestor-1) : PASN_BitString::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_BitString::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_BitString::Class()) == 0 || PASN_ConstrainedObject::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_BitString)); } ;
  public:
    PASN_BitString(unsigned tag = UniversalBitString,
                   TagClass tagClass = UniversalTagClass,
                   unsigned nBits = 0);

    PASN_BitString(const PASN_BitString & other);
    PASN_BitString & operator=(const PASN_BitString & other);

    void SetData(unsigned nBits, const PBYTEArray & bytes);
    void SetData(unsigned nBits, const BYTE * buf, int size);

    unsigned GetSize() const { return totalBits; }
    BOOL SetSize(unsigned nBits);

    BOOL operator[](int bit) const;
    void Set(unsigned bit);
    void Clear(unsigned bit);
    void Invert(unsigned bit);

    virtual void SetConstraints(ConstraintType type, int lower = 0, unsigned upper = 0xffffffff);

    virtual Comparison Compare(const PObject & obj) const;
    virtual PObject * Clone() const;
    virtual void PrintOn(ostream & strm) const;

    virtual PString GetTypeAsString() const;
    virtual int GetDataLength() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;

    BOOL DecodeBER(PBER_Stream & strm, unsigned len);
    void EncodeBER(PBER_Stream & strm) const;
    BOOL DecodePER(PPER_Stream & strm);
    void EncodePER(PPER_Stream & strm) const;

		


		virtual char* getValue( void ) const;

  protected:
    unsigned totalBits;
    PBYTEArray bitData;
};




class PASN_OctetString : public PASN_ConstrainedObject
{
    public: static const char * Class() { return "PASN_OctetString"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_ConstrainedObject::GetClass(ancestor-1) : PASN_OctetString::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_OctetString::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_OctetString::Class()) == 0 || PASN_ConstrainedObject::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_OctetString)); } ;
  public:
    PASN_OctetString(unsigned tag = UniversalOctetString,
                     TagClass tagClass = UniversalTagClass);

    PASN_OctetString(const PASN_OctetString & other);
    PASN_OctetString & operator=(const PASN_OctetString & other);

    PASN_OctetString & operator=(const char * str);
    PASN_OctetString & operator=(const PString & str);
    PASN_OctetString & operator=(const PBYTEArray & arr);
    void SetValue(const char * str) { operator=(str); }
    void SetValue(const PString & str) { operator=(str); }
    void SetValue(const PBYTEArray & arr) { operator=(arr); }
    void SetValue(const BYTE * data, int len);
    const PBYTEArray & GetValue() const { return value; }
    operator const PBYTEArray &() const { return value; }
    operator const BYTE *() const { return value; }
    PString AsString() const;
    BYTE operator[](int i) const { return value[i]; }
    BYTE & operator[](int i) { return value[i]; }
    BYTE * GetPointer(int sz = 0) { return value.GetPointer(sz); }
    int GetSize() const { return value.GetSize(); }
    BOOL SetSize(int newSize) { return value.SetSize(newSize); }

    virtual void SetConstraints(ConstraintType type, int lower = 0, unsigned upper = 0xffffffff);

    virtual Comparison Compare(const PObject & obj) const;
    virtual PObject * Clone() const;
    virtual void PrintOn(ostream & strm) const;

    virtual PString GetTypeAsString() const;
    virtual int GetDataLength() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;

    BOOL DecodePER(PPER_Stream & strm);
    void EncodePER(PPER_Stream & strm) const;

		


		virtual char* getValue( void ) const;

  protected:
    PBYTEArray value;
};




class PASN_ConstrainedString : public PASN_ConstrainedObject
{
    public: static const char * Class() { return "PASN_ConstrainedString"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_ConstrainedObject::GetClass(ancestor-1) : PASN_ConstrainedString::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_ConstrainedString::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_ConstrainedString::Class()) == 0 || PASN_ConstrainedObject::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_ConstrainedString)); } ;
  public:
    PASN_ConstrainedString & operator=(const char * str);
    PASN_ConstrainedString & operator=(const PString & str) { return operator=((const char *)str); }
    operator const PString &() const { return value; }
    const PString & GetValue() const { return value; }
    void SetValue(const PString & v) { operator=(v); }

    void SetCharacterSet(ConstraintType ctype, const char * charSet);
    void SetCharacterSet(ConstraintType ctype, unsigned firstChar = 0, unsigned lastChar = 255);
    void SetCharacterSet(const char * charSet, int size, ConstraintType ctype);

    virtual Comparison Compare(const PObject & obj) const;
    virtual void PrintOn(ostream & strm) const;

    virtual int GetDataLength() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;

    BOOL DecodeBER(PBER_Stream & strm, unsigned len);
    void EncodeBER(PBER_Stream & strm) const;
    BOOL DecodePER(PPER_Stream & strm);
    void EncodePER(PPER_Stream & strm) const;

		


		virtual char* getValue( void ) const;

  protected:
    PASN_ConstrainedString(const char * canonicalSet, int setSize,
                           unsigned tag, TagClass tagClass);

    PString value;
    PCharArray characterSet;
    const char * canonicalSet;
    int canonicalSetSize;
    unsigned canonicalSetBits;
    unsigned charSetUnalignedBits;
    unsigned charSetAlignedBits;
};














class PASN_NumericString : public PASN_ConstrainedString { public: static const char * Class() { return "PASN_NumericString"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_ConstrainedString::GetClass(ancestor-1) : PASN_NumericString::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_NumericString::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_NumericString::Class()) == 0 || PASN_ConstrainedString::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_NumericString)); } ; public: PASN_NumericString(unsigned tag = UniversalNumericString, TagClass tagClass = UniversalTagClass); PASN_NumericString & operator=(const char * str); PASN_NumericString & operator=(const PString & str); virtual PObject * Clone() const; virtual PString GetTypeAsString() const; };
class PASN_PrintableString : public PASN_ConstrainedString { public: static const char * Class() { return "PASN_PrintableString"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_ConstrainedString::GetClass(ancestor-1) : PASN_PrintableString::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_PrintableString::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_PrintableString::Class()) == 0 || PASN_ConstrainedString::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_PrintableString)); } ; public: PASN_PrintableString(unsigned tag = UniversalNumericString, TagClass tagClass = UniversalTagClass); PASN_PrintableString & operator=(const char * str); PASN_PrintableString & operator=(const PString & str); virtual PObject * Clone() const; virtual PString GetTypeAsString() const; };
class PASN_VisibleString : public PASN_ConstrainedString { public: static const char * Class() { return "PASN_VisibleString"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_ConstrainedString::GetClass(ancestor-1) : PASN_VisibleString::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_VisibleString::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_VisibleString::Class()) == 0 || PASN_ConstrainedString::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_VisibleString)); } ; public: PASN_VisibleString(unsigned tag = UniversalNumericString, TagClass tagClass = UniversalTagClass); PASN_VisibleString & operator=(const char * str); PASN_VisibleString & operator=(const PString & str); virtual PObject * Clone() const; virtual PString GetTypeAsString() const; };
class PASN_IA5String : public PASN_ConstrainedString { public: static const char * Class() { return "PASN_IA5String"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_ConstrainedString::GetClass(ancestor-1) : PASN_IA5String::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_IA5String::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_IA5String::Class()) == 0 || PASN_ConstrainedString::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_IA5String)); } ; public: PASN_IA5String(unsigned tag = UniversalNumericString, TagClass tagClass = UniversalTagClass); PASN_IA5String & operator=(const char * str); PASN_IA5String & operator=(const PString & str); virtual PObject * Clone() const; virtual PString GetTypeAsString() const; };
class PASN_GeneralString : public PASN_ConstrainedString { public: static const char * Class() { return "PASN_GeneralString"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_ConstrainedString::GetClass(ancestor-1) : PASN_GeneralString::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_GeneralString::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_GeneralString::Class()) == 0 || PASN_ConstrainedString::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_GeneralString)); } ; public: PASN_GeneralString(unsigned tag = UniversalNumericString, TagClass tagClass = UniversalTagClass); PASN_GeneralString & operator=(const char * str); PASN_GeneralString & operator=(const PString & str); virtual PObject * Clone() const; virtual PString GetTypeAsString() const; };




class PASN_BMPString : public PASN_ConstrainedObject
{
    public: static const char * Class() { return "PASN_BMPString"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_ConstrainedObject::GetClass(ancestor-1) : PASN_BMPString::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_BMPString::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_BMPString::Class()) == 0 || PASN_ConstrainedObject::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_BMPString)); } ;
  public:
    PASN_BMPString(unsigned tag = UniversalBMPString,
                   TagClass tagClass = UniversalTagClass);

    PASN_BMPString(const PASN_BMPString & other);
    PASN_BMPString & operator=(const PASN_BMPString & other);

    PASN_BMPString & operator=(const PString & v);
    PASN_BMPString & operator=(const PWORDArray & v);
    operator PString() const { return GetValue(); }
    PString GetValue() const;
    void SetValue(const PString & v) { operator=(v); }
    void SetValue(const PWORDArray & v) { operator=(v); }

    void SetCharacterSet(ConstraintType ctype, const char * charSet);
    void SetCharacterSet(ConstraintType ctype, const PWORDArray & charSet);
    void SetCharacterSet(ConstraintType ctype, unsigned firstChar, unsigned lastChar);

    virtual Comparison Compare(const PObject & obj) const;
    virtual PObject * Clone() const;
    virtual void PrintOn(ostream & strm) const;

    virtual PString GetTypeAsString() const;
    virtual int GetDataLength() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;

    BOOL DecodeBER(PBER_Stream & strm, unsigned len);
    void EncodeBER(PBER_Stream & strm) const;
    BOOL DecodePER(PPER_Stream & strm);
    void EncodePER(PPER_Stream & strm) const;

		


		virtual char* getValue( void ) const;

  protected:
    BOOL IsLegalCharacter(WORD ch);

    PWORDArray value;
    PWORDArray characterSet;
    WORD firstChar, lastChar;
    unsigned charSetUnalignedBits;
    unsigned charSetAlignedBits;
};


class PASN_Sequence;



class PASN_Choice : public PASN_Object
{
    public: static const char * Class() { return "PASN_Choice"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_Object::GetClass(ancestor-1) : PASN_Choice::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_Choice::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_Choice::Class()) == 0 || PASN_Object::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_Choice)); } ;
  public:
    ~PASN_Choice();

    virtual void SetTag(unsigned newTag, TagClass tagClass = DefaultTagClass);
    PString GetTagName() const;
    PASN_Object & GetObjectA() const;
    BOOL IsValid() const { return choice != 0; }



















#line 672 "src/../include/ptlib/asner.h"

    operator PASN_Null &();
    operator PASN_Boolean &();
    operator PASN_Integer &();
    operator PASN_Enumeration &();
    operator PASN_Real &();
    operator PASN_ObjectId &();
    operator PASN_BitString &();
    operator PASN_OctetString &();
    operator PASN_NumericString &();
    operator PASN_PrintableString &();
    operator PASN_VisibleString &();
    operator PASN_IA5String &();
    operator PASN_GeneralString &();
    operator PASN_BMPString &();
    operator PASN_Sequence &();

    operator const PASN_Null &() const;
    operator const PASN_Boolean &() const;
    operator const PASN_Integer &() const;
    operator const PASN_Enumeration &() const;
    operator const PASN_Real &() const;
    operator const PASN_ObjectId &() const;
    operator const PASN_BitString &() const;
    operator const PASN_OctetString &() const;
    operator const PASN_NumericString &() const;
    operator const PASN_PrintableString &() const;
    operator const PASN_VisibleString &() const;
    operator const PASN_IA5String &() const;
    operator const PASN_GeneralString &() const;
    operator const PASN_BMPString &() const;
    operator const PASN_Sequence &() const;

#line 706 "src/../include/ptlib/asner.h"

    virtual BOOL CreateObject() = 0;

    virtual Comparison Compare(const PObject & obj) const;
    virtual void PrintOn(ostream & strm) const;

    virtual PString GetTypeAsString() const;
    virtual int GetDataLength() const;
    virtual BOOL IsPrimitive() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;

    virtual BOOL DecodePER(PPER_Stream &);
    virtual void EncodePER(PPER_Stream &) const;

  protected:
    PASN_Choice(unsigned nChoices = 0xffffffff, BOOL extend = 0);
    PASN_Choice(unsigned tag, TagClass tagClass, unsigned nChoices, BOOL extend);
    PASN_Choice(unsigned tag, TagClass tagClass, unsigned nChoices, BOOL extend, const PString & nameSpec);

    PASN_Choice(const PASN_Choice & other);
    PASN_Choice & operator=(const PASN_Choice & other);

    unsigned numChoices;
    PASN_Object * choice;
    POrdinalToString names;
};


typedef PArray<PASN_Object> PASN_ObjectArray;




class PASN_Sequence : public PASN_Object
{
    public: static const char * Class() { return "PASN_Sequence"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_Object::GetClass(ancestor-1) : PASN_Sequence::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_Sequence::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_Sequence::Class()) == 0 || PASN_Object::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_Sequence)); } ;
  public:
    PASN_Sequence(unsigned tag = UniversalSequence,
                  TagClass tagClass = UniversalTagClass,
                  unsigned nOpts = 0, BOOL extend = 0, unsigned nExtend = 0);

    PASN_Sequence(const PASN_Sequence & other);
    PASN_Sequence & operator=(const PASN_Sequence & other);

    int GetSize() const { return fields.GetSize(); }
    void SetSize(int newSize);
    PASN_Object & operator[](int i) const { return fields[i]; }

    BOOL HasOptionalField(int opt) const;
    void IncludeOptionalField(int opt);

    virtual Comparison Compare(const PObject & obj) const;
    virtual PObject * Clone() const;
    virtual void PrintOn(ostream & strm) const;

    virtual PString GetTypeAsString() const;
    virtual int GetDataLength() const;
    virtual BOOL IsPrimitive() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;

    BOOL PreambleDecode(PASN_Stream & strm);
    void PreambleEncode(PASN_Stream & strm) const;
    BOOL KnownExtensionDecode(PASN_Stream & strm, int fld, PASN_Object & field);
    void KnownExtensionEncode(PASN_Stream & strm, int fld, const PASN_Object & field) const;
    BOOL UnknownExtensionsDecode(PASN_Stream & strm);
    void UnknownExtensionsEncode(PASN_Stream & strm) const;

    BOOL PreambleDecodeBER(PBER_Stream & strm);
    void PreambleEncodeBER(PBER_Stream & strm) const;
    BOOL KnownExtensionDecodeBER(PBER_Stream & strm, int fld, PASN_Object & field);
    void KnownExtensionEncodeBER(PBER_Stream & strm, int fld, const PASN_Object & field) const;
    BOOL UnknownExtensionsDecodeBER(PBER_Stream & strm);
    void UnknownExtensionsEncodeBER(PBER_Stream & strm) const;

    BOOL PreambleDecodePER(PPER_Stream & strm);
    void PreambleEncodePER(PPER_Stream & strm) const;
    BOOL KnownExtensionDecodePER(PPER_Stream & strm, int fld, PASN_Object & field);
    void KnownExtensionEncodePER(PPER_Stream & strm, int fld, const PASN_Object & field) const;
    BOOL UnknownExtensionsDecodePER(PPER_Stream & strm);
    void UnknownExtensionsEncodePER(PPER_Stream & strm) const;

  protected:
    BOOL NoExtensionsToDecode(PPER_Stream & strm);
    BOOL NoExtensionsToEncode(PPER_Stream & strm);

    PASN_ObjectArray fields;
    PASN_BitString optionMap;
    int knownExtensions;
    int totalExtensions;
    PASN_BitString extensionMap;
    int endBasicEncoding;
};




class PASN_Set : public PASN_Sequence
{
    public: static const char * Class() { return "PASN_Set"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_Sequence::GetClass(ancestor-1) : PASN_Set::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_Set::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_Set::Class()) == 0 || PASN_Sequence::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_Set)); } ;
  public:
    PASN_Set(unsigned tag = UniversalSet,
             TagClass tagClass = UniversalTagClass,
             unsigned nOpts = 0, BOOL extend = 0, unsigned nExtend = 0);

    virtual PObject * Clone() const;
    virtual PString GetTypeAsString() const;
};




class PASN_Array : public PASN_ConstrainedObject
{
    public: static const char * Class() { return "PASN_Array"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_ConstrainedObject::GetClass(ancestor-1) : PASN_Array::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_Array::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_Array::Class()) == 0 || PASN_ConstrainedObject::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_Array)); } ;
  public:
    int GetSize() const { return array.GetSize(); }
    void SetSize(int newSize);
    PASN_Object & operator[](int i) const { return array[i]; }
    void RemoveAt(int i) { array.RemoveAt(i); }
    void RemoveAll() { array.RemoveAll(); }

    virtual Comparison Compare(const PObject & obj) const;
    virtual void PrintOn(ostream & strm) const;

    virtual PString GetTypeAsString() const;
    virtual int GetDataLength() const;
    virtual BOOL IsPrimitive() const;
    virtual BOOL Decode(PASN_Stream &);
    virtual void Encode(PASN_Stream &) const;

    virtual PASN_Object * CreateObject() const = 0;

  protected:
    PASN_Array(unsigned tag = UniversalSequence,
               TagClass tagClass = UniversalTagClass);

    PASN_Array(const PASN_Array & other);
    PASN_Array & operator=(const PASN_Array & other);

    PASN_ObjectArray array;
};






class PASN_Stream : public PBYTEArray
{
    public: static const char * Class() { return "PASN_Stream"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PBYTEArray::GetClass(ancestor-1) : PASN_Stream::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PASN_Stream::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PASN_Stream::Class()) == 0 || PBYTEArray::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PASN_Stream)); } ;
  public:
    PASN_Stream();
    PASN_Stream(const PBYTEArray & bytes);
    PASN_Stream(const BYTE * buf, int size);

    void PrintOn(ostream & strm) const;

    int GetPosition() const { return byteOffset; }
    void SetPosition(int newPos);
    BOOL IsAtEnd() { return byteOffset >= GetSize(); }
    void ResetDecoder();
    void BeginEncoding();
    void CompleteEncoding();

    virtual BOOL Read(PChannel & chan) = 0;
    virtual BOOL Write(PChannel & chan) = 0;

    virtual BOOL NullDecode(PASN_Null &) = 0;
    virtual void NullEncode(const PASN_Null &) = 0;
    virtual BOOL BooleanDecode(PASN_Boolean &) = 0;
    virtual void BooleanEncode(const PASN_Boolean &) = 0;
    virtual BOOL IntegerDecode(PASN_Integer &) = 0;
    virtual void IntegerEncode(const PASN_Integer &) = 0;
    virtual BOOL EnumerationDecode(PASN_Enumeration &) = 0;
    virtual void EnumerationEncode(const PASN_Enumeration &) = 0;
    virtual BOOL RealDecode(PASN_Real &) = 0;
    virtual void RealEncode(const PASN_Real &) = 0;
    virtual BOOL ObjectIdDecode(PASN_ObjectId &) = 0;
    virtual void ObjectIdEncode(const PASN_ObjectId &) = 0;
    virtual BOOL BitStringDecode(PASN_BitString &) = 0;
    virtual void BitStringEncode(const PASN_BitString &) = 0;
    virtual BOOL OctetStringDecode(PASN_OctetString &) = 0;
    virtual void OctetStringEncode(const PASN_OctetString &) = 0;
    virtual BOOL ConstrainedStringDecode(PASN_ConstrainedString &) = 0;
    virtual void ConstrainedStringEncode(const PASN_ConstrainedString &) = 0;
    virtual BOOL BMPStringDecode(PASN_BMPString &) = 0;
    virtual void BMPStringEncode(const PASN_BMPString &) = 0;
    virtual BOOL ChoiceDecode(PASN_Choice &) = 0;
    virtual void ChoiceEncode(const PASN_Choice &) = 0;
    virtual BOOL ArrayDecode(PASN_Array &) = 0;
    virtual void ArrayEncode(const PASN_Array &) = 0;
    virtual BOOL SequencePreambleDecode(PASN_Sequence &) = 0;
    virtual void SequencePreambleEncode(const PASN_Sequence &) = 0;
    virtual BOOL SequenceKnownDecode(PASN_Sequence &, int, PASN_Object &) = 0;
    virtual void SequenceKnownEncode(const PASN_Sequence &, int, const PASN_Object &) = 0;
    virtual BOOL SequenceUnknownDecode(PASN_Sequence &) = 0;
    virtual void SequenceUnknownEncode(const PASN_Sequence &) = 0;

    BYTE ByteDecode();
    void ByteEncode(unsigned value);

    unsigned BlockDecode(BYTE * bufptr, unsigned nBytes);
    void BlockEncode(const BYTE * bufptr, int nBytes);

    void ByteAlign();

  protected:
    int byteOffset;
    unsigned bitOffset;

  private:
    void Construct();
};




class PBER_Stream : public PASN_Stream
{
    public: static const char * Class() { return "PBER_Stream"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_Stream::GetClass(ancestor-1) : PBER_Stream::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PBER_Stream::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PBER_Stream::Class()) == 0 || PASN_Stream::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PBER_Stream)); } ;
  public:
    PBER_Stream();
    PBER_Stream(const PBYTEArray & bytes);
    PBER_Stream(const BYTE * buf, int size);

    PBER_Stream & operator=(const PBYTEArray & bytes);

    virtual BOOL Read(PChannel & chan);
    virtual BOOL Write(PChannel & chan);

    virtual BOOL NullDecode(PASN_Null &);
    virtual void NullEncode(const PASN_Null &);
    virtual BOOL BooleanDecode(PASN_Boolean &);
    virtual void BooleanEncode(const PASN_Boolean &);
    virtual BOOL IntegerDecode(PASN_Integer &);
    virtual void IntegerEncode(const PASN_Integer &);
    virtual BOOL EnumerationDecode(PASN_Enumeration &);
    virtual void EnumerationEncode(const PASN_Enumeration &);
    virtual BOOL RealDecode(PASN_Real &);
    virtual void RealEncode(const PASN_Real &);
    virtual BOOL ObjectIdDecode(PASN_ObjectId &);
    virtual void ObjectIdEncode(const PASN_ObjectId &);
    virtual BOOL BitStringDecode(PASN_BitString &);
    virtual void BitStringEncode(const PASN_BitString &);
    virtual BOOL OctetStringDecode(PASN_OctetString &);
    virtual void OctetStringEncode(const PASN_OctetString &);
    virtual BOOL ConstrainedStringDecode(PASN_ConstrainedString &);
    virtual void ConstrainedStringEncode(const PASN_ConstrainedString &);
    virtual BOOL BMPStringDecode(PASN_BMPString &);
    virtual void BMPStringEncode(const PASN_BMPString &);
    virtual BOOL ChoiceDecode(PASN_Choice &);
    virtual void ChoiceEncode(const PASN_Choice &);
    virtual BOOL ArrayDecode(PASN_Array &);
    virtual void ArrayEncode(const PASN_Array &);
    virtual BOOL SequencePreambleDecode(PASN_Sequence &);
    virtual void SequencePreambleEncode(const PASN_Sequence &);
    virtual BOOL SequenceKnownDecode(PASN_Sequence &, int, PASN_Object &);
    virtual void SequenceKnownEncode(const PASN_Sequence &, int, const PASN_Object &);
    virtual BOOL SequenceUnknownDecode(PASN_Sequence &);
    virtual void SequenceUnknownEncode(const PASN_Sequence &);

    virtual PASN_Object * CreateObject(unsigned tag,
                                       PASN_Object::TagClass tagClass,
                                       BOOL primitive) const;

    BOOL HeaderDecode(unsigned & tagVal,
                      PASN_Object::TagClass & tagClass,
                      BOOL & primitive,
                      unsigned & len);
    BOOL HeaderDecode(PASN_Object & obj, unsigned & len);
    void HeaderEncode(const PASN_Object & obj);
};




class PPER_Stream : public PASN_Stream
{
    public: static const char * Class() { return "PPER_Stream"; } virtual const char * GetClass(unsigned ancestor = 0) const { return ancestor > 0 ? PASN_Stream::GetClass(ancestor-1) : PPER_Stream::Class(); } virtual BOOL IsClass(const char * clsName) const { return strcmp(clsName, PPER_Stream::Class()) == 0; } virtual BOOL IsDescendant(const char * clsName) const { return strcmp(clsName, PPER_Stream::Class()) == 0 || PASN_Stream::IsDescendant(clsName); } virtual Comparison CompareObjectMemoryDirect(const PObject & obj) const { return (Comparison)memcmp(this, &obj, sizeof(PPER_Stream)); } ;
  public:
    PPER_Stream(BOOL aligned = 1);
    PPER_Stream(const PBYTEArray & bytes, BOOL aligned = 1);
    PPER_Stream(const BYTE * buf, int size, BOOL aligned = 1);

    PPER_Stream & operator=(const PBYTEArray & bytes);

    unsigned GetBitsLeft() const;

    virtual BOOL Read(PChannel & chan);
    virtual BOOL Write(PChannel & chan);

    virtual BOOL NullDecode(PASN_Null &);
    virtual void NullEncode(const PASN_Null &);
    virtual BOOL BooleanDecode(PASN_Boolean &);
    virtual void BooleanEncode(const PASN_Boolean &);
    virtual BOOL IntegerDecode(PASN_Integer &);
    virtual void IntegerEncode(const PASN_Integer &);
    virtual BOOL EnumerationDecode(PASN_Enumeration &);
    virtual void EnumerationEncode(const PASN_Enumeration &);
    virtual BOOL RealDecode(PASN_Real &);
    virtual void RealEncode(const PASN_Real &);
    virtual BOOL ObjectIdDecode(PASN_ObjectId &);
    virtual void ObjectIdEncode(const PASN_ObjectId &);
    virtual BOOL BitStringDecode(PASN_BitString &);
    virtual void BitStringEncode(const PASN_BitString &);
    virtual BOOL OctetStringDecode(PASN_OctetString &);
    virtual void OctetStringEncode(const PASN_OctetString &);
    virtual BOOL ConstrainedStringDecode(PASN_ConstrainedString &);
    virtual void ConstrainedStringEncode(const PASN_ConstrainedString &);
    virtual BOOL BMPStringDecode(PASN_BMPString &);
    virtual void BMPStringEncode(const PASN_BMPString &);
    virtual BOOL ChoiceDecode(PASN_Choice &);
    virtual void ChoiceEncode(const PASN_Choice &);
    virtual BOOL ArrayDecode(PASN_Array &);
    virtual void ArrayEncode(const PASN_Array &);
    virtual BOOL SequencePreambleDecode(PASN_Sequence &);
    virtual void SequencePreambleEncode(const PASN_Sequence &);
    virtual BOOL SequenceKnownDecode(PASN_Sequence &, int, PASN_Object &);
    virtual void SequenceKnownEncode(const PASN_Sequence &, int, const PASN_Object &);
    virtual BOOL SequenceUnknownDecode(PASN_Sequence &);
    virtual void SequenceUnknownEncode(const PASN_Sequence &);

    BOOL IsAligned() const { return aligned; }

    BOOL SingleBitDecode();
    void SingleBitEncode(BOOL value);

    int MultiBitDecode(unsigned nBits);
    void MultiBitEncode(int value, unsigned nBits);

    unsigned SmallUnsignedDecode();
    void SmallUnsignedEncode(unsigned val);

    int LengthDecode(unsigned lower, unsigned upper, unsigned & len);
    void LengthEncode(unsigned len, unsigned lower, unsigned upper);

    int UnsignedDecode(unsigned lower, unsigned upper, unsigned & value);
    void UnsignedEncode(int value, unsigned lower, unsigned upper);

    void AnyTypeEncode(const PASN_Object * value);

  protected:
    BOOL aligned;
};


#line 1055 "src/../include/ptlib/asner.h"
#line 125 "src/asner.cxx"




static int CountBits(unsigned range)
{
  if (range == 0)
    return sizeof(unsigned)*8;

  int nBits = 0;
  while (nBits < (sizeof(unsigned)*8) && range > (unsigned)(1 << nBits))
    nBits++;
  return nBits;
}

PString InttoStr( unsigned int in ) 
{
	if (in == 0 ) return PString( "0" );

	PString result;
	int tmp;

	while ( in > 0 ) {
		tmp = in % 10;
		in = in / 10;
		result = PString( char( tmp + 48 ) ) + result;
	}
	return result;
}



PASN_Object::PASN_Object(unsigned theTag, TagClass theTagClass, BOOL extend)
{
  extendable = extend;

  tag = theTag;

  if (theTagClass != DefaultTagClass)
    tagClass = theTagClass;
  else
    tagClass = ContextSpecificTagClass;
}


void PASN_Object::SetTag(unsigned newTag, TagClass tagClass_)
{
  tag = newTag;
  if (tagClass_ != DefaultTagClass)
    tagClass = tagClass_;
}


int PASN_Object::GetObjectLength() const
{
  int len = 1;

  if (tag >= 31)
    len += (CountBits(tag)+6)/7;

  int dataLen = GetDataLength();
  if (dataLen < 128)
    len++;
  else
    len += (CountBits(dataLen)+7)/8 + 1;

  return len + dataLen;
}


void PASN_Object::SetConstraints(ConstraintType, MinimumValueTag lower, unsigned upper)
{
  SetConstraints(PartiallyConstrained, (int)lower, upper);
}


void PASN_Object::SetConstraints(ConstraintType, int lower, MaximumValueTag upper)
{
  SetConstraints(PartiallyConstrained, lower, (unsigned)upper);
}


void PASN_Object::SetConstraints(ConstraintType, MinimumValueTag lower, MaximumValueTag upper)
{
  SetConstraints(PartiallyConstrained, (int)lower, (unsigned)upper);
}


void PASN_Object::SetConstraints(ConstraintType, int, unsigned)
{
}


void PASN_Object::SetCharacterSet(ConstraintType, const char *)
{
}


void PASN_Object::SetCharacterSet(ConstraintType, unsigned, unsigned)
{
}

void PASN_Object::SetStartbyte( unsigned int byte )
{
	startbyte = byte; 
}

void PASN_Object::SetStopbyte( unsigned int byte )
{
	stopbyte = byte;
}

unsigned int PASN_Object::GetByteLength( void ) const
{
	





	unsigned int result = ( stopbyte - startbyte );
	if ( result == 0 ) result = 1;
	return result;
}

unsigned int PASN_Object::GetStartByte( void ) const
{
	return startbyte;
}




PASN_ConstrainedObject::PASN_ConstrainedObject(unsigned tag, TagClass tagClass)
  : PASN_Object(tag, tagClass)
{
  constraint = Unconstrained;
  lowerLimit = 0;
  upperLimit =  0xffffffff;
}


void PASN_ConstrainedObject::SetConstraints(ConstraintType ctype,
                                            int lower, unsigned upper)
{
  constraint = ctype;
  if (constraint == Unconstrained) {
    lower = 0;
    upper = 0xffffffff;
  }

  extendable = ctype == ExtendableConstraint;
  
if((lower >= 0 || upper < 0x7fffffff) && (lower < 0 || (unsigned)lower <= upper));else PAssertFunc("src/asner.cxx", 278, (PInvalidParameter));
  lowerLimit = lower;
  upperLimit = upper;
}


int PASN_ConstrainedObject::ConstrainedLengthDecode(PPER_Stream & strm, unsigned & length)
{
  
  
  if ((extendable && strm.SingleBitDecode()) || constraint == Unconstrained)
    return strm.LengthDecode(0, 2147483647, length);
  else
    return strm.LengthDecode(lowerLimit, upperLimit, length);
}


void PASN_ConstrainedObject::ConstrainedLengthEncode(PPER_Stream & strm, unsigned length) const
{
  if (ConstraintEncode(strm, length)) 
    strm.LengthEncode(length, 0, 2147483647);
  else
    strm.LengthEncode(length, lowerLimit, upperLimit);
}


BOOL PASN_ConstrainedObject::ConstraintEncode(PPER_Stream & strm, unsigned value) const
{
  if (!extendable)
    return constraint != FixedConstraint;

  BOOL needsExtending = value > upperLimit;

  if (!needsExtending) {
    if (lowerLimit < 0) {
      if ((int)value < lowerLimit)
        needsExtending = 1;
    }
    else {
      if (value < (unsigned)lowerLimit)
        needsExtending = 1;
    }
  }

  strm.SingleBitEncode(needsExtending);

  return needsExtending || constraint != FixedConstraint;
}




PASN_Null::PASN_Null(unsigned tag, TagClass tagClass)
  : PASN_Object(tag, tagClass)
{
}


PObject::Comparison PASN_Null::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_Null::Class()));else PAssertFunc("src/asner.cxx", 338, (PInvalidCast));
  return EqualTo;
}


PObject * PASN_Null::Clone() const
{
  if(IsClass(PASN_Null::Class()));else PAssertFunc("src/asner.cxx", 345, (PInvalidCast));
  return new PASN_Null(*this);
}


void PASN_Null::PrintOn(ostream & strm) const
{
  strm << "<<null>>";
}


PString PASN_Null::GetTypeAsString() const
{
  return "Null";
}


int PASN_Null::GetDataLength() const
{
  return 0;
}


BOOL PASN_Null::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = strm.NullDecode(*this);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_Null::Encode(PASN_Stream & strm) const
{
  strm.NullEncode(*this);
}


BOOL PBER_Stream::NullDecode(PASN_Null & value)
{
  unsigned len;
  if (!HeaderDecode(value, len))
    return 0;

  byteOffset += len;
  return 1;
}


void PBER_Stream::NullEncode(const PASN_Null & value)
{
  HeaderEncode(value);
}


BOOL PPER_Stream::NullDecode(PASN_Null &)
{
  return 1;
}


void PPER_Stream::NullEncode(const PASN_Null &)
{
}




PASN_Boolean::PASN_Boolean(BOOL val, unsigned tag, TagClass tagClass)
  : PASN_Object(tag, tagClass)
{
  value = val;
}


PObject::Comparison PASN_Boolean::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_Boolean::Class()));else PAssertFunc("src/asner.cxx", 423, (PInvalidCast));
  return value == ((const PASN_Boolean &)obj).value ? EqualTo : GreaterThan;
}


PObject * PASN_Boolean::Clone() const
{
  if(IsClass(PASN_Boolean::Class()));else PAssertFunc("src/asner.cxx", 430, (PInvalidCast));
  return new PASN_Boolean(*this);
}


void PASN_Boolean::PrintOn(ostream & strm) const
{
  if (value)
    strm << "TRUE";
  else
    strm << "FALSE";
}


PString PASN_Boolean::GetTypeAsString() const
{
  return "Boolean";
}


int PASN_Boolean::GetDataLength() const
{
  return 1;
}


BOOL PASN_Boolean::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = strm.BooleanDecode(*this);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_Boolean::Encode(PASN_Stream & strm) const
{
  strm.BooleanEncode(*this);
}


BOOL PBER_Stream::BooleanDecode(PASN_Boolean & value)
{
  unsigned len;
  if (!HeaderDecode(value, len))
    return 0;

  while (len-- > 0) {
    if (IsAtEnd())
      return 0;
    value = (BOOL)ByteDecode();
  }

  return 1;
}


void PBER_Stream::BooleanEncode(const PASN_Boolean & value)
{
  HeaderEncode(value);
  ByteEncode((BOOL)value);
}


BOOL PPER_Stream::BooleanDecode(PASN_Boolean & value)
{
  if (IsAtEnd())
    return 0;

  
  value = (BOOL)SingleBitDecode();
  return 1;
}


void PPER_Stream::BooleanEncode(const PASN_Boolean & value)
{
  
  SingleBitEncode((BOOL)value);
}




PASN_Integer::PASN_Integer(unsigned tag, TagClass tagClass, unsigned val)
  : PASN_ConstrainedObject(tag, tagClass)
{
  value = val;
}


PASN_Integer & PASN_Integer::operator=(unsigned val)
{
  if (constraint == Unconstrained)
    value = val;
  else if (lowerLimit >= 0) { 
    if (val < (unsigned)lowerLimit)
      value = lowerLimit;
    else if (val > upperLimit)
      value = upperLimit;
    else
      value = val;
  }
  else {
    int ival = (int)val;
    if (ival < lowerLimit)
      value = lowerLimit;
    else if (upperLimit < 2147483647 && ival > (int)upperLimit)
      value = upperLimit;
    else
      value = val;
  }

  return *this;
}


PObject::Comparison PASN_Integer::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_Integer::Class()));else PAssertFunc("src/asner.cxx", 550, (PInvalidCast));
  const PASN_Integer & other = (const PASN_Integer &)obj;

  if (value < other.value)
    return LessThan;

  if (value > other.value)
    return GreaterThan;

  return EqualTo;
}


PObject * PASN_Integer::Clone() const
{
  if(IsClass(PASN_Integer::Class()));else PAssertFunc("src/asner.cxx", 565, (PInvalidCast));
  return new PASN_Integer(*this);
}


void PASN_Integer::PrintOn(ostream & strm) const
{
  if (lowerLimit < 0)
    strm << (int)value;
  else
    strm << value;
}


PString PASN_Integer::GetTypeAsString() const
{
  return "Integer";
}


static int GetIntegerDataLength(int value)
{
  
  
  int shift = (sizeof(value)-1)*8-1;

  
  while (shift > 0 && ((value >> shift)&0x1ff) == (value < 0 ? 0x1ff : 0))
    shift -= 8;

  return (shift+9)/8;
}


int PASN_Integer::GetDataLength() const
{
  return GetIntegerDataLength(value);
}


BOOL PASN_Integer::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = strm.IntegerDecode(*this);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_Integer::Encode(PASN_Stream & strm) const
{
  strm.IntegerEncode(*this);
}


BOOL PBER_Stream::IntegerDecode(PASN_Integer & value)
{
  unsigned len;
  if (!HeaderDecode(value, len) || len == 0 || IsAtEnd())
    return 0;

  int accumulator = (char)ByteDecode(); 
  while (--len > 0) {
    if (IsAtEnd())
      return 0;
    accumulator = (accumulator << 8) | ByteDecode();
  }

  value = accumulator;
  return 1;
}


void PBER_Stream::IntegerEncode(const PASN_Integer & value)
{
  HeaderEncode(value);
  
  for (int count = GetIntegerDataLength(value)-1; count >= 0; count--)
    ByteEncode(value >> (count*8));
}


BOOL PPER_Stream::IntegerDecode(PASN_Integer & value)
{
  return value.DecodePER(*this);
}


void PPER_Stream::IntegerEncode(const PASN_Integer & value)
{
  value.EncodePER(*this);
}


BOOL PASN_Integer::DecodePER(PPER_Stream & strm)
{
  

  if ((extendable && strm.SingleBitDecode()) || constraint != FixedConstraint) { 
    unsigned len;
    if (strm.LengthDecode(0, 2147483647, len) != 0)
      return 0;
    value = strm.MultiBitDecode(len*8);
    return 1;
  }

  if ((unsigned)lowerLimit != upperLimit)  
    return strm.UnsignedDecode(lowerLimit, upperLimit, value) == 0; 

  value = lowerLimit;
  return 1;
}


void PASN_Integer::EncodePER(PPER_Stream & strm) const
{
  

  if (ConstraintEncode(strm, (int)value)) { 
    int nBytes;
    unsigned adjusted_value = value - lowerLimit;
    if (adjusted_value == 0)
      nBytes = 1;
    else {
      int nBits = CountBits(adjusted_value+1);
      nBytes = (nBits+7)/8;
    }
    strm.LengthEncode(nBytes, 0, 2147483647);
    strm.MultiBitEncode(adjusted_value, nBytes*8);
    return;
  }

  if ((unsigned)lowerLimit == upperLimit) 
    return;

  
  strm.UnsignedEncode(value, lowerLimit, upperLimit);
}




PASN_Enumeration::PASN_Enumeration(unsigned tag, TagClass tagClass,
                                   unsigned maxEnum, BOOL extend,
                                   unsigned val)
  : PASN_Object(tag, tagClass, extend)
{
  value = val;
  maxEnumValue = maxEnum;
}


static POrdinalToString BuildNamesDict(const PString & nameSpec)
{
  POrdinalToString names;

  PStringArray nameList = nameSpec.Tokenise(' ', 0);

  int num = 0;
  for (int i = 0; i < nameList.GetSize(); i++) {
    const PString & thisName = nameList[i];
    if (!thisName) {
      int equalPos = thisName.Find('=');
      if (equalPos != P_MAX_INDEX)
        num = (int)thisName.Mid(equalPos+1).AsInteger();
      names.SetAt(POrdinalKey(num), thisName.Left(equalPos));
      num++;
    }
  }

  return names;
}


PASN_Enumeration::PASN_Enumeration(unsigned tag, TagClass tagClass,
                                   unsigned maxEnum, BOOL extend,
                                   const PString & nameSpec,
                                   unsigned val)
  : PASN_Object(tag, tagClass, extend),
    names(BuildNamesDict(nameSpec))
{
  if(maxEnum > 0);else PAssertFunc("src/asner.cxx", 747, (PInvalidParameter));
  maxEnumValue = maxEnum;

  if(val < maxEnum);else PAssertFunc("src/asner.cxx", 750, (PInvalidParameter));
  value = val;
}


PObject::Comparison PASN_Enumeration::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_Enumeration::Class()));else PAssertFunc("src/asner.cxx", 757, (PInvalidCast));
  const PASN_Enumeration & other = (const PASN_Enumeration &)obj;

  if (value < other.value)
    return LessThan;

  if (value > other.value)
    return GreaterThan;

  return EqualTo;
}


PObject * PASN_Enumeration::Clone() const
{
  if(IsClass(PASN_Enumeration::Class()));else PAssertFunc("src/asner.cxx", 772, (PInvalidCast));
  return new PASN_Enumeration(*this);
}


void PASN_Enumeration::PrintOn(ostream & strm) const
{
  if (names.Contains(value))
    strm << names[value];
  else
    strm << '<' << value << '>';
}


PString PASN_Enumeration::GetTypeAsString() const
{
  return "Enumeration";
}


int PASN_Enumeration::GetDataLength() const
{
  return GetIntegerDataLength(value);
}


BOOL PASN_Enumeration::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = strm.EnumerationDecode(*this);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_Enumeration::Encode(PASN_Stream & strm) const
{
  strm.EnumerationEncode(*this);
}


BOOL PBER_Stream::EnumerationDecode(PASN_Enumeration & value)
{
  unsigned len;
  if (!HeaderDecode(value, len) || len == 0 || IsAtEnd())
    return 0;

  unsigned val = 0;
  while (len-- > 0) {
    if (IsAtEnd())
      return 0;
    val = (val << 8) | ByteDecode();
  }

  value = val;
  return 1;
}


void PBER_Stream::EnumerationEncode(const PASN_Enumeration & value)
{
  HeaderEncode(value);
  
  for (int count = GetIntegerDataLength(value)-1; count >= 0; count--)
    ByteEncode(value >> (count*8));
}


BOOL PPER_Stream::EnumerationDecode(PASN_Enumeration & value)
{
  return value.DecodePER(*this);
}


void PPER_Stream::EnumerationEncode(const PASN_Enumeration & value)
{
  value.EncodePER(*this);
}


BOOL PASN_Enumeration::DecodePER(PPER_Stream & strm)
{
  

  if (extendable) {  
    if (strm.SingleBitDecode())
      return strm.UnsignedDecode(0, strm.SmallUnsignedDecode()-1, value) == 0;
  }

  return strm.UnsignedDecode(0, maxEnumValue, value) == 0;  
}


void PASN_Enumeration::EncodePER(PPER_Stream & strm) const
{
  

  if (extendable) {  
    BOOL extended = value > maxEnumValue;
    strm.SingleBitEncode(extended);
    if (extended) {
      strm.SmallUnsignedEncode(1+value);
      strm.UnsignedEncode(value, 0, value);
      return;
    }
  }

  strm.UnsignedEncode(value, 0, maxEnumValue);  
}

char* PASN_Enumeration::getValue( void ) const
{
	PString result;
	
  if ( names.Contains( value ) )
    result = names[ value ];
  else
    result = value;

	char* presult = new char[ result.GetLength() + 1 ];
	for ( int j = 0; j < result.GetLength(); j++) presult[j] = result[j];
	presult[ result.GetLength() ] = '\0';
	return presult;
}



PASN_Real::PASN_Real(unsigned tag, TagClass tagClass, double val)
  : PASN_Object(tag, tagClass)
{
  value = val;
}


PObject::Comparison PASN_Real::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_Real::Class()));else PAssertFunc("src/asner.cxx", 909, (PInvalidCast));
  const PASN_Real & other = (const PASN_Real &)obj;

  if (value < other.value)
    return LessThan;

  if (value > other.value)
    return GreaterThan;

  return EqualTo;
}


PObject * PASN_Real::Clone() const
{
  if(IsClass(PASN_Real::Class()));else PAssertFunc("src/asner.cxx", 924, (PInvalidCast));
  return new PASN_Real(*this);
}


void PASN_Real::PrintOn(ostream & strm) const
{
  strm << value;
}


PString PASN_Real::GetTypeAsString() const
{
  return "Real";
}


int PASN_Real::GetDataLength() const
{
  PAssertFunc("src/asner.cxx", 943, (PUnimplementedFunction));
  return 0;
}


BOOL PASN_Real::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = strm.RealDecode(*this);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_Real::Encode(PASN_Stream & strm) const
{
  strm.RealEncode(*this);
}


BOOL PBER_Stream::RealDecode(PASN_Real & value)
{
  unsigned len;
  if (!HeaderDecode(value, len) || len == 0 || IsAtEnd())
    return 0;

  PAssertFunc("src/asner.cxx", 970, (PUnimplementedFunction));
  byteOffset += len;

  return 1;
}


void PBER_Stream::RealEncode(const PASN_Real &)
{
  PAssertFunc("src/asner.cxx", 979, (PUnimplementedFunction));
}


BOOL PPER_Stream::RealDecode(PASN_Real &)
{
  

  if (IsAtEnd())
    return 0;

  int len = MultiBitDecode(8)+1;
  PAssertFunc("src/asner.cxx", 991, (PUnimplementedFunction));
  byteOffset += len;
  return 1;
}


void PPER_Stream::RealEncode(const PASN_Real &)
{
  

  MultiBitEncode(0, 8);
  PAssertFunc("src/asner.cxx", 1002, (PUnimplementedFunction));
  MultiBitEncode(0, 8);
}




PASN_ObjectId::PASN_ObjectId(unsigned tag, TagClass tagClass)
  : PASN_Object(tag, tagClass)
{
}


PASN_ObjectId::PASN_ObjectId(const PASN_ObjectId & other)
  : PASN_Object(other),
    value(other.value, other.GetSize())
{
}


PASN_ObjectId & PASN_ObjectId::operator=(const PASN_ObjectId & other)
{
  PASN_Object::operator=(other);
  value = PUnsignedArray(other.value, other.GetSize());
  return *this;
}


PASN_ObjectId & PASN_ObjectId::operator=(const char * dotstr)
{
  SetValue(dotstr);
  return *this;
}


PASN_ObjectId & PASN_ObjectId::operator=(const PString & dotstr)
{
  SetValue(dotstr);
  return *this;
}


void PASN_ObjectId::SetValue(const PString & dotstr)
{
  PStringArray parts = dotstr.Tokenise('.');
  value.SetSize(parts.GetSize());
  for (int i = 0; i < parts.GetSize(); i++)
    value[i] = parts[i].AsUnsigned();
}


BOOL PASN_ObjectId::operator==(const char * dotstr) const
{
  PASN_ObjectId id;
  id.SetValue(dotstr);
  return *this == id;
}


PObject::Comparison PASN_ObjectId::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_ObjectId::Class()));else PAssertFunc("src/asner.cxx", 1063, (PInvalidCast));
  const PASN_ObjectId & other = (const PASN_ObjectId &)obj;
  return value.Compare(other.value);
}


PObject * PASN_ObjectId::Clone() const
{
  if(IsClass(PASN_ObjectId::Class()));else PAssertFunc("src/asner.cxx", 1071, (PInvalidCast));
  return new PASN_ObjectId(*this);
}


void PASN_ObjectId::PrintOn(ostream & strm) const
{
  for (int i = 0; i < value.GetSize(); i++) {
    strm << (unsigned)value[i];
    if (i < value.GetSize()-1)
      strm << '.';
  }
}


PString PASN_ObjectId::GetTypeAsString() const
{
  return "Object ID";
}


BOOL PASN_ObjectId::CommonDecode(PASN_Stream & strm, unsigned dataLen)
{
  value.SetSize(0);

  
  if (dataLen == 0)
    return 1;

  unsigned subId;

  
  
  int i = 1;
  while (dataLen > 0) {
    unsigned byte;
    subId = 0;
    do {    
      if (strm.IsAtEnd())
        return 0;
      byte = strm.ByteDecode();
      subId = (subId << 7) + (byte & 0x7f);
      dataLen--;
    } while ((byte & 0x80) != 0);
    value.SetAt(i++, subId);
  }

  





  subId = value[1];
  if (subId < 40) {
    value[0] = 0;
    value[1] = subId;
  }
  else if (subId < 80) {
    value[0] = 1;
    value[1] = subId-40;
  }
  else {
    value[0] = 2;
    value[1] = subId-80;
  }

  return 1;
}


void PASN_ObjectId::CommonEncode(PBYTEArray & encodecObjectId) const
{
  int length = value.GetSize();
  const unsigned * objId = value;

  if (length < 2) {
    
    encodecObjectId.SetSize(0);
    return;
  }

  unsigned subId = (objId[0] * 40) + objId[1];
  objId += 2;

  int outputPosition = 0;

  while (--length > 0) {
    if (subId < 128)
      encodecObjectId[outputPosition++] = (BYTE)subId;
    else {
      unsigned mask = 0x7F; 
      int bits = 0;

      
      unsigned testmask = 0x7F;
      int      testbits = 0;
      while (testmask != 0) {
        if (subId & testmask) {  
          mask = testmask;
	        bits = testbits;
	      }
        testmask <<= 7;
        testbits += 7;
      }

      
      while (mask != 0x7F) {
        
      	if (mask == 0x1E00000)
	        mask = 0xFE00000;

        encodecObjectId[outputPosition++] = (BYTE)(((subId & mask) >> bits) | 0x80);

        mask >>= 7;
        bits -= 7;
      }

      encodecObjectId[outputPosition++] = (BYTE)(subId & mask);
    }

    subId = *objId++;
  }
}


int PASN_ObjectId::GetDataLength() const
{
  PBYTEArray dummy;
  CommonEncode(dummy);
  return dummy.GetSize();
}


BOOL PASN_ObjectId::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = strm.ObjectIdDecode(*this);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_ObjectId::Encode(PASN_Stream & strm) const
{
  strm.ObjectIdEncode(*this);
}


BOOL PBER_Stream::ObjectIdDecode(PASN_ObjectId & value)
{
  unsigned len;
  if (!HeaderDecode(value, len))
    return 0;

  return value.CommonDecode(*this, len);
}


void PBER_Stream::ObjectIdEncode(const PASN_ObjectId & value)
{
  HeaderEncode(value);
  PBYTEArray data;
  value.CommonEncode(data);
  BlockEncode(data, data.GetSize());
}


BOOL PPER_Stream::ObjectIdDecode(PASN_ObjectId & value)
{
  

  unsigned dataLen;
  if (LengthDecode(0, 255, dataLen) < 0)
    return 0;

  ByteAlign();
  return value.CommonDecode(*this, dataLen);
}


void PPER_Stream::ObjectIdEncode(const PASN_ObjectId & value)
{
  

  PBYTEArray eObjId;
  value.CommonEncode(eObjId);
  LengthEncode(eObjId.GetSize(), 0, 255);
  BlockEncode(eObjId, eObjId.GetSize());
}

char* PASN_ObjectId::getValue( void ) const
{
	PString result;
  for (int i = 0; i < value.GetSize(); i++) {
    result += InttoStr( value[ i ] );
    if (i < value.GetSize()-1)
      result += '.';
  }
	
	char* presult = new char[ result.GetLength() + 1 ];
	for ( int j = 0; j < result.GetLength(); j++) presult[j] = result[j];
	presult[ result.GetLength() ] = '\0';
	return presult;
}




PASN_BitString::PASN_BitString(unsigned tag, TagClass tagClass, unsigned nBits)
  : PASN_ConstrainedObject(tag, tagClass),
    totalBits(nBits),
    bitData((totalBits+7)/8)
{
}


PASN_BitString::PASN_BitString(const PASN_BitString & other)
  : PASN_ConstrainedObject(other),
    bitData(other.bitData, other.bitData.GetSize())
{
  totalBits = other.totalBits;
}


PASN_BitString & PASN_BitString::operator=(const PASN_BitString & other)
{
  PASN_ConstrainedObject::operator=(other);
  totalBits = other.totalBits;
  bitData = PBYTEArray(other.bitData, other.bitData.GetSize());
  return *this;
}


void PASN_BitString::SetData(unsigned nBits, const PBYTEArray & bytes)
{
  bitData = bytes;
  totalBits = nBits;
}


void PASN_BitString::SetData(unsigned nBits, const BYTE * buf, int size)
{
  bitData = PBYTEArray(buf, size);
  totalBits = nBits;
}


BOOL PASN_BitString::SetSize(unsigned nBits)
{
  totalBits = nBits;
  return bitData.SetSize((nBits+7)/8);
}


BOOL PASN_BitString::operator[](int bit) const
{
  if ((unsigned)bit < totalBits)
    return (bitData[bit>>3] & (1 << (7 - (bit&7)))) != 0;
  return 0;
}


void PASN_BitString::Set(unsigned bit)
{
  if (bit < totalBits)
    bitData[(int)(bit>>3)] |= 1 << (7 - (bit&7));
}


void PASN_BitString::Clear(unsigned bit)
{
  if (bit < totalBits)
    bitData[(int)(bit>>3)] &= ~(1 << (7 - (bit&7)));
}


void PASN_BitString::Invert(unsigned bit)
{
  if (bit < totalBits)
    bitData[(int)(bit>>3)] ^= 1 << (7 - (bit&7));
}


void PASN_BitString::SetConstraints(ConstraintType type, int lower, unsigned upper)
{
  if(lower >= 0);else PAssertFunc("src/asner.cxx", 1358, (PInvalidParameter));
  PASN_ConstrainedObject::SetConstraints(type, lower, upper);
  if (constraint != Unconstrained) {
    if (totalBits < (unsigned)lowerLimit)
      SetSize(lowerLimit);
    else if ((unsigned)totalBits > upperLimit)
      SetSize(upperLimit);
  }
}


PObject::Comparison PASN_BitString::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_BitString::Class()));else PAssertFunc("src/asner.cxx", 1371, (PInvalidCast));
  const PASN_BitString & other = (const PASN_BitString &)obj;
  if (totalBits < other.totalBits)
    return LessThan;
  if (totalBits > other.totalBits)
    return GreaterThan;
  return bitData.Compare(other.bitData);
}


PObject * PASN_BitString::Clone() const
{
  if(IsClass(PASN_BitString::Class()));else PAssertFunc("src/asner.cxx", 1383, (PInvalidCast));
  return new PASN_BitString(*this);
}


void PASN_BitString::PrintOn(ostream & strm) const
{
  BYTE mask = 0x80;
  int offset = 0;
  for (unsigned i = 0; i < totalBits; i++) {
    strm << ((bitData[offset]&mask) != 0 ? '1' : '0');
    mask >>= 1;
    if (mask == 0) {
      mask = 0x80;
      offset++;
    }
  }
}


PString PASN_BitString::GetTypeAsString() const
{
  return "Bit String";
}


int PASN_BitString::GetDataLength() const
{
  return (totalBits+7)/8 + 1;
}


BOOL PASN_BitString::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = strm.BitStringDecode(*this);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_BitString::Encode(PASN_Stream & strm) const
{
  strm.BitStringEncode(*this);
}


BOOL PASN_BitString::DecodeBER(PBER_Stream & strm, unsigned len)
{
  totalBits = len*8 - strm.ByteDecode();
  unsigned nBytes = (totalBits+7)/8;
  return strm.BlockDecode(bitData.GetPointer(nBytes), nBytes) == nBytes;
}


void PASN_BitString::EncodeBER(PBER_Stream & strm) const
{
  if (totalBits == 0)
    strm.ByteEncode(0);
  else {
    strm.ByteEncode(8-totalBits%8);
    strm.BlockEncode(bitData, (totalBits+7)/8);
  }
}


BOOL PASN_BitString::DecodePER(PPER_Stream & strm)
{
  

  if (ConstrainedLengthDecode(strm, totalBits) < 0)
    return 0;

  SetSize(totalBits);

  if (totalBits == 0)
    return 1;   

  if (totalBits > strm.GetBitsLeft())
    return 0;

  if (totalBits > 16) {
    unsigned nBytes = (totalBits+7)/8;
    return strm.BlockDecode(bitData.GetPointer(), nBytes) == nBytes;   
  }

  if (totalBits <= 8)
    bitData[0] = (BYTE)(strm.MultiBitDecode(totalBits) << (8-totalBits));
  else {  
    bitData[0] = (BYTE)strm.MultiBitDecode(8);
    bitData[1] = (BYTE)(strm.MultiBitDecode(totalBits-8) << (16-totalBits));
  }

  return 1;
}


void PASN_BitString::EncodePER(PPER_Stream & strm) const
{
  

  ConstrainedLengthEncode(strm, totalBits);

  if (totalBits == 0)
    return;

  if (totalBits > 16)
    strm.BlockEncode(bitData, (totalBits+7)/8);   
  else if (totalBits <= 8)  
    strm.MultiBitEncode(bitData[0] >> (8 - totalBits), totalBits);
  else {
    strm.MultiBitEncode(bitData[0], 8);
    strm.MultiBitEncode(bitData[1] >> (16 - totalBits), totalBits-8);
  }
}


BOOL PBER_Stream::BitStringDecode(PASN_BitString & value)
{
  unsigned len;
  if (!HeaderDecode(value, len) || len == 0 || IsAtEnd())
    return 0;

  return value.DecodeBER(*this, len);
}


void PBER_Stream::BitStringEncode(const PASN_BitString & value)
{
  HeaderEncode(value);
  value.EncodeBER(*this);
}


BOOL PPER_Stream::BitStringDecode(PASN_BitString & value)
{
  return value.DecodePER(*this);
}


void PPER_Stream::BitStringEncode(const PASN_BitString & value)
{
  value.EncodePER(*this);
}

char* PASN_BitString::getValue( void ) const
{
	




	int nr = GetSize();
	char* pData = new char[ nr + 1 ];
	
	for( int i=0; i < nr; i++ ) {
		pData[i] = bitData[i] + 48;
	}
	if ( pData[ nr - 1 ] != '\0' ) pData[ nr ] = '\0';
	return pData;
}



PASN_OctetString::PASN_OctetString(unsigned tag, TagClass tagClass)
  : PASN_ConstrainedObject(tag, tagClass)
{
}


PASN_OctetString::PASN_OctetString(const PASN_OctetString & other)
  : PASN_ConstrainedObject(other),
    value(other.value, other.GetSize())
{
}


PASN_OctetString & PASN_OctetString::operator=(const PASN_OctetString & other)
{
  PASN_ConstrainedObject::operator=(other);
  value = PBYTEArray(other.value, other.GetSize());
  return *this;
}


PASN_OctetString & PASN_OctetString::operator=(const char * str)
{
  SetValue((const BYTE *)str, strlen(str));
  return *this;
}


PASN_OctetString & PASN_OctetString::operator=(const PString & str)
{
  SetValue((const BYTE *)(const char *)str, str.GetSize()-1);
  return *this;
}


PASN_OctetString & PASN_OctetString::operator=(const PBYTEArray & arr)
{
  int len = arr.GetSize();
  if ((unsigned)len > upperLimit || (int)len < lowerLimit)
    SetValue(arr, len);
  else
    value = arr;
  return *this;
}


void PASN_OctetString::SetValue(const BYTE * data, int len)
{
  if ((unsigned)len > upperLimit)
    len = upperLimit;
  value.SetSize((int)len < lowerLimit ? lowerLimit : len);
  memcpy(value.GetPointer(), data, len);
}


PString PASN_OctetString::AsString() const
{
  if (value.IsEmpty())
    return PString();
  return PString((const char *)(const BYTE *)value, value.GetSize());
}


void PASN_OctetString::SetConstraints(ConstraintType type, int lower, unsigned upper)
{
  if(lower >= 0);else PAssertFunc("src/asner.cxx", 1613, (PInvalidParameter));
  PASN_ConstrainedObject::SetConstraints(type, lower, upper);
  if (constraint != Unconstrained) {
    if (value.GetSize() < (int)lowerLimit)
      value.SetSize(lowerLimit);
    else if ((unsigned)value.GetSize() > upperLimit)
      value.SetSize(upperLimit);
  }
}


PObject::Comparison PASN_OctetString::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_OctetString::Class()));else PAssertFunc("src/asner.cxx", 1626, (PInvalidCast));
  const PASN_OctetString & other = (const PASN_OctetString &)obj;
  return value.Compare(other.value);
}


PObject * PASN_OctetString::Clone() const
{
  if(IsClass(PASN_OctetString::Class()));else PAssertFunc("src/asner.cxx", 1634, (PInvalidCast));
  return new PASN_OctetString(*this);
}


void PASN_OctetString::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << ' ' << value.GetSize() << " octets {\n";
  int i = 0;
  while (i < value.GetSize()) {
    strm << setw(indent) << " " << hex << setfill('0');
    int j;
    for (j = 0; j < 16; j++) {
      if (i+j < value.GetSize())
        strm << setw(2) << (unsigned)value[i+j] << ' ';
      else
        strm << "   ";
    }
    strm << "  ";
    for (j = 0; j < 16; j++) {
      if (i+j < value.GetSize()) {
        if (isprint(value[i+j]))
          strm << value[i+j];
        else
          strm << ' ';
      }
    }
    strm << dec << setfill(' ') << '\n';
    i += 16;
  }
  strm << setw(indent-1) << "}";
}


PString PASN_OctetString::GetTypeAsString() const
{
  return "Octet String";
}


int PASN_OctetString::GetDataLength() const
{
  return value.GetSize();
}


BOOL PASN_OctetString::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = strm.OctetStringDecode(*this);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_OctetString::Encode(PASN_Stream & strm) const
{
  strm.OctetStringEncode(*this);
}


BOOL PASN_OctetString::DecodePER(PPER_Stream & strm)
{
  

  unsigned nBytes;
  if (ConstrainedLengthDecode(strm, nBytes) < 0)
    return 0;

  value.SetSize(nBytes);   

  switch (nBytes) {
    case 0 :
      break;

    case 1 :  
      if (strm.IsAtEnd())
        return 0;
      value[0] = (BYTE)strm.MultiBitDecode(8);
      break;

    case 2 :  
      if (strm.IsAtEnd())
        return 0;
      value[0] = (BYTE)strm.MultiBitDecode(8);
      value[1] = (BYTE)strm.MultiBitDecode(8);
      break;

    default: 
      return strm.BlockDecode(value.GetPointer(), nBytes) == nBytes;
  }

  return 1;
}


void PASN_OctetString::EncodePER(PPER_Stream & strm) const
{
  

  int nBytes = value.GetSize();
  ConstrainedLengthEncode(strm, nBytes);

  switch (nBytes) {
    case 0 :  
      break;

    case 1 :  
      strm.MultiBitEncode(value[0], 8);
      break;

    case 2 :  
      strm.MultiBitEncode(value[0], 8);
      strm.MultiBitEncode(value[1], 8);
      break;

    default: 
      strm.BlockEncode(value, nBytes);
  }
}


BOOL PBER_Stream::OctetStringDecode(PASN_OctetString & value)
{
  unsigned len;
  if (!HeaderDecode(value, len))
    return 0;

  return BlockDecode(value.GetPointer(len), len) == len;
}


void PBER_Stream::OctetStringEncode(const PASN_OctetString & value)
{
  HeaderEncode(value);
  BlockEncode(value, value.GetSize());
}


BOOL PPER_Stream::OctetStringDecode(PASN_OctetString & value)
{
  return value.DecodePER(*this);
}


void PPER_Stream::OctetStringEncode(const PASN_OctetString & value)
{
  value.EncodePER(*this);
}

char* PASN_OctetString::getValue( void ) const
{
	




	int nr = GetSize();
	char* pData = new char[ nr + 1 ];
	
	for( int i=0; i < nr; i++ ) {
		pData[i] = value[i];
		if ( ( pData[i] == 0 ) && ( i < nr - 1) ) pData[i] = '0';
	}
	if ( pData[ nr - 1 ] != '\0' ) pData[ nr ] = '\0';
	return pData;
}



PASN_ConstrainedString::PASN_ConstrainedString(const char * canonical, int size,
                                               unsigned tag, TagClass tagClass)
  : PASN_ConstrainedObject(tag, tagClass)
{
  canonicalSet = canonical;
  canonicalSetSize = size;
  canonicalSetBits = CountBits(size);
  charSetUnalignedBits = 8;
  charSetAlignedBits = 8;
}


PASN_ConstrainedString & PASN_ConstrainedString::operator=(const char * str)
{
  value = PString();
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    int sz = characterSet.GetSize();
    if (sz == 0 || memchr(characterSet, str[i], sz) != 0)
      value += str[i];
  }
  return *this;
}


void PASN_ConstrainedString::SetCharacterSet(ConstraintType ctype, const char * set)
{
  SetCharacterSet(set, strlen(set), ctype);
}


void PASN_ConstrainedString::SetCharacterSet(ConstraintType ctype, unsigned firstChar, unsigned lastChar)
{
  char buffer[256];
  for (unsigned i = firstChar; i < lastChar; i++)
    buffer[i] = (char)i;
  SetCharacterSet(buffer, lastChar - firstChar + 1, ctype);
}


void PASN_ConstrainedString::SetCharacterSet(const char * set, int setSize, ConstraintType ctype)
{
  if (ctype == Unconstrained)
    characterSet.SetSize(0);
  else {
    characterSet.SetSize(setSize);
    int count = 0;
    for (int i = 0; i < canonicalSetSize; i++) {
      if (memchr(set, canonicalSet[i], setSize) != 0)
        characterSet[count++] = canonicalSet[i];
    }
    if(count > 0);else PAssertFunc("src/asner.cxx", 1857, (PInvalidParameter));
    characterSet.SetSize(count);
  }

  if (characterSet.IsEmpty())
    charSetUnalignedBits = 8;
  else
    charSetUnalignedBits = CountBits(characterSet.GetSize());

  charSetAlignedBits = 1;
  while (charSetUnalignedBits > charSetAlignedBits)
    charSetAlignedBits <<= 1;
}


PObject::Comparison PASN_ConstrainedString::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_ConstrainedString::Class()));else PAssertFunc("src/asner.cxx", 1874, (PInvalidCast));
  const PASN_ConstrainedString & other = (const PASN_ConstrainedString &)obj;
  return value.Compare(other.value);
}


void PASN_ConstrainedString::PrintOn(ostream & strm) const
{
  strm << value.ToLiteral();
}


int PASN_ConstrainedString::GetDataLength() const
{
  return value.GetSize()-1;
}


BOOL PASN_ConstrainedString::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = strm.ConstrainedStringDecode(*this);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_ConstrainedString::Encode(PASN_Stream & strm) const
{
  strm.ConstrainedStringEncode(*this);
}


BOOL PASN_ConstrainedString::DecodeBER(PBER_Stream & strm, unsigned len)
{
  return strm.BlockDecode((BYTE *)value.GetPointer(len+1), len) == len;
}


void PASN_ConstrainedString::EncodeBER(PBER_Stream & strm) const
{
  strm.BlockEncode(value, value.GetSize()-1);
}


BOOL PASN_ConstrainedString::DecodePER(PPER_Stream & strm)
{
  

  unsigned len;
  if (ConstrainedLengthDecode(strm, len) < 0)
    return 0;

  unsigned nBits = strm.IsAligned() ? charSetAlignedBits : charSetUnalignedBits;

  if (constraint == Unconstrained || upperLimit*nBits > 16) {
    if (nBits == 8)
      return strm.BlockDecode((BYTE *)value.GetPointer(len+1), len) == len;
    if (strm.IsAligned())
      strm.ByteAlign();
  }

  value.SetSize(len+1);

  int i;
  for (i = 0; i < (int)len; i++) {
    if (strm.IsAtEnd())
      return 0;
    if (nBits >= canonicalSetBits && canonicalSetBits > 4)
      value[i] = (char)strm.MultiBitDecode(nBits);
    else
      value[i] = characterSet[strm.MultiBitDecode(nBits)];
  }
  value[i] = '\0';

  return 1;
}


void PASN_ConstrainedString::EncodePER(PPER_Stream & strm) const
{
  

  int len = value.GetSize()-1;
  ConstrainedLengthEncode(strm, len);

  unsigned nBits = strm.IsAligned() ? charSetAlignedBits : charSetUnalignedBits;

  if (constraint == Unconstrained || upperLimit*nBits > 16) {
    if (nBits == 8) {
      strm.BlockEncode((const BYTE *)(const char *)value, len);
      return;
    }
    if (strm.IsAligned())
      strm.ByteAlign();
  }

  for (int i = 0; i < len; i++) {
    if (nBits >= canonicalSetBits && canonicalSetBits > 4)
      strm.MultiBitEncode(value[i], nBits);
    else {
      const void * ptr = memchr(characterSet, value[i], characterSet.GetSize());
      int pos = 0;
      if (ptr != 0)
        pos = ((const char *)ptr - (const char *)characterSet);
      strm.MultiBitEncode(pos, nBits);
    }
  }
}


BOOL PBER_Stream::ConstrainedStringDecode(PASN_ConstrainedString & value)
{
  unsigned len;
  if (!HeaderDecode(value, len))
    return 0;

  return value.DecodeBER(*this, len);
}


void PBER_Stream::ConstrainedStringEncode(const PASN_ConstrainedString & value)
{
  HeaderEncode(value);
  value.Encode(*this);
}


BOOL PPER_Stream::ConstrainedStringDecode(PASN_ConstrainedString & value)
{
  return value.DecodePER(*this);
}


void PPER_Stream::ConstrainedStringEncode(const PASN_ConstrainedString & value)
{
  value.EncodePER(*this);
}

char* PASN_ConstrainedString::getValue( void ) const
{
	




	char* pData = new char[ value.GetLength() + 1 ];
	strcpy(pData, (const char*) value );
	return pData;
}

















static const char NumericStringSet[] = " 0123456789"; PASN_NumericString::PASN_NumericString(unsigned tag, TagClass tagClass) : PASN_ConstrainedString(NumericStringSet, sizeof(NumericStringSet)-1, tag, tagClass) { } PASN_NumericString & PASN_NumericString::operator=(const char * str) { PASN_ConstrainedString::SetValue(str); return *this; } PASN_NumericString & PASN_NumericString::operator=(const PString & str) { PASN_ConstrainedString::SetValue(str); return *this; } PObject * PASN_NumericString::Clone() const { if(IsClass(PASN_NumericString::Class()));else PAssertFunc("src/asner.cxx", 2042, (PInvalidCast)); return new PASN_NumericString(*this); } PString PASN_NumericString::GetTypeAsString() const { return "Numeric" " String"; }


static const char PrintableStringSet[] = " '()+,-./0123456789:=?" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz"; PASN_PrintableString::PASN_PrintableString(unsigned tag, TagClass tagClass) : PASN_ConstrainedString(PrintableStringSet, sizeof(PrintableStringSet)-1, tag, tagClass) { } PASN_PrintableString & PASN_PrintableString::operator=(const char * str) { PASN_ConstrainedString::SetValue(str); return *this; } PASN_PrintableString & PASN_PrintableString::operator=(const PString & str) { PASN_ConstrainedString::SetValue(str); return *this; } PObject * PASN_PrintableString::Clone() const { if(IsClass(PASN_PrintableString::Class()));else PAssertFunc("src/asner.cxx", 2045, (PInvalidCast)); return new PASN_PrintableString(*this); } PString PASN_PrintableString::GetTypeAsString() const { return "Printable" " String"; }


static const char VisibleStringSet[] = " !\"#$%&'()*+,-./0123456789:;<=>?" "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_" "`abcdefghijklmnopqrstuvwxyz{|}~"; PASN_VisibleString::PASN_VisibleString(unsigned tag, TagClass tagClass) : PASN_ConstrainedString(VisibleStringSet, sizeof(VisibleStringSet)-1, tag, tagClass) { } PASN_VisibleString & PASN_VisibleString::operator=(const char * str) { PASN_ConstrainedString::SetValue(str); return *this; } PASN_VisibleString & PASN_VisibleString::operator=(const PString & str) { PASN_ConstrainedString::SetValue(str); return *this; } PObject * PASN_VisibleString::Clone() const { if(IsClass(PASN_VisibleString::Class()));else PAssertFunc("src/asner.cxx", 2048, (PInvalidCast)); return new PASN_VisibleString(*this); } PString PASN_VisibleString::GetTypeAsString() const { return "Visible" " String"; }






static const char IA5StringSet[] = "\000\001\002\003\004\005\006\007" "\010\011\012\013\014\015\016\017" "\020\021\022\023\024\025\026\027" "\030\031\032\033\034\035\036\037" " !\"#$%&'()*+,-./0123456789:;<=>?" "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_" "`abcdefghijklmnopqrstuvwxyz{|}~\177"; PASN_IA5String::PASN_IA5String(unsigned tag, TagClass tagClass) : PASN_ConstrainedString(IA5StringSet, sizeof(IA5StringSet)-1, tag, tagClass) { } PASN_IA5String & PASN_IA5String::operator=(const char * str) { PASN_ConstrainedString::SetValue(str); return *this; } PASN_IA5String & PASN_IA5String::operator=(const PString & str) { PASN_ConstrainedString::SetValue(str); return *this; } PObject * PASN_IA5String::Clone() const { if(IsClass(PASN_IA5String::Class()));else PAssertFunc("src/asner.cxx", 2055, (PInvalidCast)); return new PASN_IA5String(*this); } PString PASN_IA5String::GetTypeAsString() const { return "IA5" " String"; }






















static const char GeneralStringSet[] = "\000\001\002\003\004\005\006\007" "\010\011\012\013\014\015\016\017" "\020\021\022\023\024\025\026\027" "\030\031\032\033\034\035\036\037" " !\"#$%&'()*+,-./0123456789:;<=>?" "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_" "`abcdefghijklmnopqrstuvwxyz{|}~\177" "\200\201\202\203\204\205\206\207" "\210\211\212\213\214\215\216\217" "\220\221\222\223\224\225\226\227" "\230\231\232\233\234\235\236\237" "\240\241\242\243\244\245\246\247" "\250\251\252\253\254\255\256\257" "\260\261\262\263\264\265\266\267" "\270\271\272\273\274\275\276\277" "\300\301\302\303\304\305\306\307" "\310\311\312\313\314\315\316\317" "\320\321\322\323\324\325\326\327" "\330\331\332\333\334\335\336\337" "\340\341\342\343\344\345\346\347" "\350\351\352\353\354\355\356\357" "\360\361\362\363\364\365\366\367" "\370\371\372\373\374\375\376\377"; PASN_GeneralString::PASN_GeneralString(unsigned tag, TagClass tagClass) : PASN_ConstrainedString(GeneralStringSet, sizeof(GeneralStringSet)-1, tag, tagClass) { } PASN_GeneralString & PASN_GeneralString::operator=(const char * str) { PASN_ConstrainedString::SetValue(str); return *this; } PASN_GeneralString & PASN_GeneralString::operator=(const PString & str) { PASN_ConstrainedString::SetValue(str); return *this; } PObject * PASN_GeneralString::Clone() const { if(IsClass(PASN_GeneralString::Class()));else PAssertFunc("src/asner.cxx", 2078, (PInvalidCast)); return new PASN_GeneralString(*this); } PString PASN_GeneralString::GetTypeAsString() const { return "General" " String"; }




PASN_BMPString::PASN_BMPString(unsigned tag, TagClass tagClass)
  : PASN_ConstrainedObject(tag, tagClass)
{
  firstChar = 0;
  lastChar = 0xffff;
  charSetAlignedBits = 16;
  charSetUnalignedBits = 16;
}


PASN_BMPString::PASN_BMPString(const PASN_BMPString & other)
  : PASN_ConstrainedObject(other),
    value(other.value, other.value.GetSize()),
    characterSet(other.characterSet)
{
  firstChar = other.firstChar;
  lastChar = other.lastChar;
  charSetAlignedBits = other.charSetAlignedBits;
  charSetUnalignedBits = other.charSetUnalignedBits;
}


PASN_BMPString & PASN_BMPString::operator=(const PASN_BMPString & other)
{
  PASN_ConstrainedObject::operator=(other);

  value = PWORDArray(other.value, other.value.GetSize());
  characterSet = other.characterSet;
  firstChar = other.firstChar;
  lastChar = other.lastChar;
  charSetAlignedBits = other.charSetAlignedBits;
  charSetUnalignedBits = other.charSetUnalignedBits;

  return *this;
}


BOOL PASN_BMPString::IsLegalCharacter(WORD ch)
{
  if (ch < firstChar)
    return 0;

  if (ch > lastChar)
    return 0;

  if (characterSet.IsEmpty())
    return 1;

  const WORD * wptr = characterSet;
  int count = characterSet.GetSize();
  while (count-- > 0) {
    if (*wptr == ch)
      return 1;
    wptr++;
  }

  return 0;
}


PASN_BMPString & PASN_BMPString::operator=(const PString & str)
{
  int sz = str.GetLength();
  value.SetSize(sz);

  int count = 0;
  for (int i = 0; i < sz; i++) {
    WORD c = (BYTE)str[i];
    if (IsLegalCharacter(c))
      value[count++] = c;
  }

  value.SetSize(count);
  return *this;
}


PASN_BMPString & PASN_BMPString::operator=(const PWORDArray & array)
{
  int sz = array.GetSize();
  value.SetSize(sz);

  int count = 0;
  for (int i = 0; i < sz; i++) {
    WORD c = array[i];
    if (IsLegalCharacter(c))
      value[count++] = c;
  }

  value.SetSize(count);
  return *this;
}


PString PASN_BMPString::GetValue() const
{
  PString str;
  for (int i = 0; i < value.GetSize(); i++) {
    if (value[i] < 256)
      str += (char)value[i];
  }
  return str;
}


void PASN_BMPString::SetCharacterSet(ConstraintType ctype, const char * charSet)
{
  PWORDArray array(strlen(charSet));

  int count = 0;
  while (*charSet != '\0')
    array[count++] = (BYTE)*charSet++;

  SetCharacterSet(ctype, array);
}


void PASN_BMPString::SetCharacterSet(ConstraintType ctype, const PWORDArray & charSet)
{
  if (ctype == Unconstrained) {
    firstChar = 0;
    lastChar = 0xffff;
    characterSet.SetSize(0);
  }
  else {
    characterSet = charSet;

    charSetUnalignedBits = CountBits(lastChar - firstChar + 1);
    if (!charSet.IsEmpty()) {
      unsigned count = 0;
      for (int i = 0; i < charSet.GetSize(); i++) {
        if (characterSet[i] >= firstChar && characterSet[i] <= lastChar)
          count++;
      }
      count = CountBits(count);
      if (charSetUnalignedBits > count)
        charSetUnalignedBits = count;
    }

    charSetAlignedBits = 1;
    while (charSetUnalignedBits > charSetAlignedBits)
      charSetAlignedBits <<= 1;

    SetValue(value);
  }
}


void PASN_BMPString::SetCharacterSet(ConstraintType ctype, unsigned first, unsigned last)
{
  if (ctype != Unconstrained) {
    if(first < 0x10000 && last < 0x10000 && last > first);else PAssertFunc("src/asner.cxx", 2234, (PInvalidParameter));
    firstChar = (WORD)first;
    lastChar = (WORD)last;
  }
  SetCharacterSet(ctype, characterSet);
}


PObject * PASN_BMPString::Clone() const
{
  if(IsClass(PASN_BMPString::Class()));else PAssertFunc("src/asner.cxx", 2244, (PInvalidCast));
  return new PASN_BMPString(*this);
}


PObject::Comparison PASN_BMPString::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_BMPString::Class()));else PAssertFunc("src/asner.cxx", 2251, (PInvalidCast));
  const PASN_BMPString & other = (const PASN_BMPString &)obj;
  return value.Compare(other.value);
}


void PASN_BMPString::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  int sz = value.GetSize();
  strm << ' ' << sz << " characters {\n";
  int i = 0;
  while (i < sz) {
    strm << setw(indent) << " " << hex << setfill('0');
    int j;
    for (j = 0; j < 8; j++)
      if (i+j < sz)
        strm << setw(4) << value[i+j] << ' ';
      else
        strm << "     ";
    strm << "  ";
    for (j = 0; j < 8; j++) {
      if (i+j < sz) {
        WORD c = value[i+j];
        if (c < 128 && isprint(c))
          strm << (char)c;
        else
          strm << ' ';
      }
    }
    strm << dec << setfill(' ') << '\n';
    i += 8;
  }
  strm << setw(indent-1) << "}";
}


PString PASN_BMPString::GetTypeAsString() const
{
  return "BMP String";
}


int PASN_BMPString::GetDataLength() const
{
  return value.GetSize()*2;
}


BOOL PASN_BMPString::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = strm.BMPStringDecode(*this);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_BMPString::Encode(PASN_Stream & strm) const
{
  strm.BMPStringEncode(*this);
}


BOOL PASN_BMPString::DecodeBER(PBER_Stream & strm, unsigned len)
{
  value.SetSize(len/2);
  return strm.BlockDecode((BYTE *)value.GetPointer(len), len) == len;
}


void PASN_BMPString::EncodeBER(PBER_Stream & strm) const
{
  strm.BlockEncode((const BYTE *)(const WORD *)value, value.GetSize()*2);
}


BOOL PASN_BMPString::DecodePER(PPER_Stream & strm)
{
  

  unsigned len;
  if (ConstrainedLengthDecode(strm, len) < 0)
    return 0;

  value.SetSize(len);

  int nBits = strm.IsAligned() ? charSetAlignedBits : charSetUnalignedBits;

  if ((constraint == Unconstrained || upperLimit*nBits > 16) && strm.IsAligned())
    strm.ByteAlign();

  for (int i = 0; i < (int)len; i++) {
    if (strm.IsAtEnd())
      return 0;
    if (characterSet.IsEmpty())
      value[i] = (WORD)(strm.MultiBitDecode(nBits) + firstChar);
    else
      value[i] = characterSet[strm.MultiBitDecode(nBits)];
  }

  return 1;
}


void PASN_BMPString::EncodePER(PPER_Stream & strm) const
{
  

  int len = value.GetSize();
  ConstrainedLengthEncode(strm, len);

  int nBits = strm.IsAligned() ? charSetAlignedBits : charSetUnalignedBits;

  if ((constraint == Unconstrained || upperLimit*nBits > 16) && strm.IsAligned())
    strm.ByteAlign();

  for (int i = 0; i < len; i++) {
    if (characterSet.IsEmpty())
      strm.MultiBitEncode(value[i] - firstChar, nBits);
    else {
      for (int pos = 0; pos < characterSet.GetSize(); pos++) {
        if (characterSet[pos] == value[i]) {
          strm.MultiBitEncode(pos, nBits);
          break;
        }
      }
    }
  }
}


BOOL PBER_Stream::BMPStringDecode(PASN_BMPString & value)
{
  unsigned len;
  if (!HeaderDecode(value, len))
    return 0;

  return value.DecodeBER(*this, len);
}


void PBER_Stream::BMPStringEncode(const PASN_BMPString & value)
{
  HeaderEncode(value);
  value.EncodeBER(*this);
}


BOOL PPER_Stream::BMPStringDecode(PASN_BMPString & value)
{
  return value.DecodePER(*this);
}


void PPER_Stream::BMPStringEncode(const PASN_BMPString & value)
{
  value.EncodePER(*this);
}

char* PASN_BMPString::getValue( void ) const
{
	




	int nr =  value.GetSize();
	char* pData = new char[ nr + 1 ];

	int i = 0;
	int tmp = value[i];
	while (i < nr ) {
		tmp = value[i];
		if ( tmp > 0xFF00 ) {
			pData[ i ] = value[ i ] & 0xFF;
		}
		else {
			if ( tmp > 160 ) pData[i] = '#';
			else pData[ i ] = value[ i ];
		}
		i++;
	}
	if ( pData[ i - 1 ] != '\0' ) pData[ i ] = '\0';
	return pData;
}




PASN_Choice::PASN_Choice(unsigned nChoices, BOOL extend)
  : PASN_Object(0, ApplicationTagClass, extend)
{
  numChoices = nChoices;
  choice = 0;
}


PASN_Choice::PASN_Choice(unsigned tag, TagClass tagClass,
                         unsigned upper, BOOL extend)
  : PASN_Object(tag, tagClass, extend)
{
  numChoices = upper;
  choice = 0;
}


PASN_Choice::PASN_Choice(unsigned tag, TagClass tagClass,
                         unsigned upper, BOOL extend, const PString & nameSpec)
  : PASN_Object(tag, tagClass, extend),
    names(BuildNamesDict(nameSpec))
{
  numChoices = upper;
  choice = 0;
}


PASN_Choice::PASN_Choice(const PASN_Choice & other)
  : PASN_Object(other),
    names(other.names)
{
  numChoices = other.numChoices;

  if (other.choice != 0)
    choice = (PASN_Object *)other.choice->Clone();
  else
    choice = 0;
}


PASN_Choice & PASN_Choice::operator=(const PASN_Choice & other)
{
  delete choice;

  PASN_Object::operator=(other);

  numChoices = other.numChoices;
  names = other.names;

  if (other.choice != 0)
    choice = (PASN_Object *)other.choice->Clone();
  else
    choice = 0;

  return *this;
}


PASN_Choice::~PASN_Choice()
{
  delete choice;
}


void PASN_Choice::SetTag(unsigned newTag, TagClass tagClass)
{
  PASN_Object::SetTag(newTag, tagClass);

  delete choice;

  if (CreateObject())
    choice->SetTag(newTag, tagClass);
}


PString PASN_Choice::GetTagName() const
{
  if (tag == 0xffffffff)
    return "<uninitialised>";

  if (names.Contains(tag)) {
		PString tmps = names[tag];
    return tmps;
	}

  if (choice != 0 && choice->IsDescendant(PASN_Choice::Class()) &&
      choice->GetTag() == tag && choice->GetTagClass() == tagClass)
    return PString(choice->GetClass()) + "->" + ((PASN_Choice *)choice)->GetTagName();

  return psprintf("<%u>", tag);
}


PASN_Object & PASN_Choice::GetObjectA() const
{
  if(choice != 0);else PAssertFunc("src/asner.cxx", 2537, ("NULL Choice"));
  return *choice;
}













































































































#line 2650 "src/asner.cxx"


PASN_Choice::operator PASN_Null &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2654, PNullPointerReference), (choice)))->IsDescendant(PASN_Null::Class()));else PAssertFunc("src/asner.cxx", 2654, (PInvalidCast));
  return *(PASN_Null *)choice;
}


PASN_Choice::operator PASN_Boolean &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2661, PNullPointerReference), (choice)))->IsDescendant(PASN_Boolean::Class()));else PAssertFunc("src/asner.cxx", 2661, (PInvalidCast));
  return *(PASN_Boolean *)choice;
}


PASN_Choice::operator PASN_Integer &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2668, PNullPointerReference), (choice)))->IsDescendant(PASN_Integer::Class()));else PAssertFunc("src/asner.cxx", 2668, (PInvalidCast));
  return *(PASN_Integer *)choice;
}


PASN_Choice::operator PASN_Enumeration &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2675, PNullPointerReference), (choice)))->IsDescendant(PASN_Enumeration::Class()));else PAssertFunc("src/asner.cxx", 2675, (PInvalidCast));
  return *(PASN_Enumeration *)choice;
}


PASN_Choice::operator PASN_Real &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2682, PNullPointerReference), (choice)))->IsDescendant(PASN_Real::Class()));else PAssertFunc("src/asner.cxx", 2682, (PInvalidCast));
  return *(PASN_Real *)choice;
}


PASN_Choice::operator PASN_ObjectId &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2689, PNullPointerReference), (choice)))->IsDescendant(PASN_ObjectId::Class()));else PAssertFunc("src/asner.cxx", 2689, (PInvalidCast));
  return *(PASN_ObjectId *)choice;
}


PASN_Choice::operator PASN_BitString &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2696, PNullPointerReference), (choice)))->IsDescendant(PASN_BitString::Class()));else PAssertFunc("src/asner.cxx", 2696, (PInvalidCast));
  return *(PASN_BitString *)choice;
}


PASN_Choice::operator PASN_OctetString &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2703, PNullPointerReference), (choice)))->IsDescendant(PASN_OctetString::Class()));else PAssertFunc("src/asner.cxx", 2703, (PInvalidCast));
  return *(PASN_OctetString *)choice;
}


PASN_Choice::operator PASN_NumericString &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2710, PNullPointerReference), (choice)))->IsDescendant(PASN_NumericString::Class()));else PAssertFunc("src/asner.cxx", 2710, (PInvalidCast));
  return *(PASN_NumericString *)choice;
}


PASN_Choice::operator PASN_PrintableString &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2717, PNullPointerReference), (choice)))->IsDescendant(PASN_PrintableString::Class()));else PAssertFunc("src/asner.cxx", 2717, (PInvalidCast));
  return *(PASN_PrintableString *)choice;
}


PASN_Choice::operator PASN_VisibleString &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2724, PNullPointerReference), (choice)))->IsDescendant(PASN_VisibleString::Class()));else PAssertFunc("src/asner.cxx", 2724, (PInvalidCast));
  return *(PASN_VisibleString *)choice;
}


PASN_Choice::operator PASN_IA5String &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2731, PNullPointerReference), (choice)))->IsDescendant(PASN_IA5String::Class()));else PAssertFunc("src/asner.cxx", 2731, (PInvalidCast));
  return *(PASN_IA5String *)choice;
}


PASN_Choice::operator PASN_GeneralString &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2738, PNullPointerReference), (choice)))->IsDescendant(PASN_GeneralString::Class()));else PAssertFunc("src/asner.cxx", 2738, (PInvalidCast));
  return *(PASN_GeneralString *)choice;
}


PASN_Choice::operator PASN_BMPString &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2745, PNullPointerReference), (choice)))->IsDescendant(PASN_BMPString::Class()));else PAssertFunc("src/asner.cxx", 2745, (PInvalidCast));
  return *(PASN_BMPString *)choice;
}


PASN_Choice::operator PASN_Sequence &()
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2752, PNullPointerReference), (choice)))->IsDescendant(PASN_Sequence::Class()));else PAssertFunc("src/asner.cxx", 2752, (PInvalidCast));
  return *(PASN_Sequence *)choice;
}


PASN_Choice::operator const PASN_Null &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2759, PNullPointerReference), (choice)))->IsDescendant(PASN_Null::Class()));else PAssertFunc("src/asner.cxx", 2759, (PInvalidCast));
  return *(const PASN_Null *)choice;
}


PASN_Choice::operator const PASN_Boolean &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2766, PNullPointerReference), (choice)))->IsDescendant(PASN_Boolean::Class()));else PAssertFunc("src/asner.cxx", 2766, (PInvalidCast));
  return *(const PASN_Boolean *)choice;
}


PASN_Choice::operator const PASN_Integer &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2773, PNullPointerReference), (choice)))->IsDescendant(PASN_Integer::Class()));else PAssertFunc("src/asner.cxx", 2773, (PInvalidCast));
  return *(const PASN_Integer *)choice;
}


PASN_Choice::operator const PASN_Enumeration &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2780, PNullPointerReference), (choice)))->IsDescendant(PASN_Enumeration::Class()));else PAssertFunc("src/asner.cxx", 2780, (PInvalidCast));
  return *(const PASN_Enumeration *)choice;
}


PASN_Choice::operator const PASN_Real &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2787, PNullPointerReference), (choice)))->IsDescendant(PASN_Real::Class()));else PAssertFunc("src/asner.cxx", 2787, (PInvalidCast));
  return *(const PASN_Real *)choice;
}


PASN_Choice::operator const PASN_ObjectId &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2794, PNullPointerReference), (choice)))->IsDescendant(PASN_ObjectId::Class()));else PAssertFunc("src/asner.cxx", 2794, (PInvalidCast));
  return *(const PASN_ObjectId *)choice;
}


PASN_Choice::operator const PASN_BitString &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2801, PNullPointerReference), (choice)))->IsDescendant(PASN_BitString::Class()));else PAssertFunc("src/asner.cxx", 2801, (PInvalidCast));
  return *(const PASN_BitString *)choice;
}


PASN_Choice::operator const PASN_OctetString &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2808, PNullPointerReference), (choice)))->IsDescendant(PASN_OctetString::Class()));else PAssertFunc("src/asner.cxx", 2808, (PInvalidCast));
  return *(const PASN_OctetString *)choice;
}


PASN_Choice::operator const PASN_NumericString &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2815, PNullPointerReference), (choice)))->IsDescendant(PASN_NumericString::Class()));else PAssertFunc("src/asner.cxx", 2815, (PInvalidCast));
  return *(const PASN_NumericString *)choice;
}


PASN_Choice::operator const PASN_PrintableString &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2822, PNullPointerReference), (choice)))->IsDescendant(PASN_PrintableString::Class()));else PAssertFunc("src/asner.cxx", 2822, (PInvalidCast));
  return *(const PASN_PrintableString *)choice;
}


PASN_Choice::operator const PASN_VisibleString &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2829, PNullPointerReference), (choice)))->IsDescendant(PASN_VisibleString::Class()));else PAssertFunc("src/asner.cxx", 2829, (PInvalidCast));
  return *(const PASN_VisibleString *)choice;
}


PASN_Choice::operator const PASN_IA5String &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2836, PNullPointerReference), (choice)))->IsDescendant(PASN_IA5String::Class()));else PAssertFunc("src/asner.cxx", 2836, (PInvalidCast));
  return *(const PASN_IA5String *)choice;
}


PASN_Choice::operator const PASN_GeneralString &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2843, PNullPointerReference), (choice)))->IsDescendant(PASN_GeneralString::Class()));else PAssertFunc("src/asner.cxx", 2843, (PInvalidCast));
  return *(const PASN_GeneralString *)choice;
}


PASN_Choice::operator const PASN_BMPString &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2850, PNullPointerReference), (choice)))->IsDescendant(PASN_BMPString::Class()));else PAssertFunc("src/asner.cxx", 2850, (PInvalidCast));
  return *(const PASN_BMPString *)choice;
}


PASN_Choice::operator const PASN_Sequence &() const
{
  if(((&(choice)&&(choice)!=0)?(choice):(PAssertFunc("src/asner.cxx", 2857, PNullPointerReference), (choice)))->IsDescendant(PASN_Sequence::Class()));else PAssertFunc("src/asner.cxx", 2857, (PInvalidCast));
  return *(const PASN_Sequence *)choice;
}


#line 2863 "src/asner.cxx"


PObject::Comparison PASN_Choice::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_Choice::Class()));else PAssertFunc("src/asner.cxx", 2867, (PInvalidCast));
  const PASN_Choice & other = (const PASN_Choice &)obj;

  if (choice == other.choice)
    return EqualTo;

  if (choice == 0)
    return LessThan;

  if (other.choice == 0)
    return GreaterThan;

  if (tag < other.tag)
    return LessThan;

  if (tag > other.tag)
    return GreaterThan;

  return choice->Compare(*other.choice);
}


void PASN_Choice::PrintOn(ostream & strm) const
{
  strm << GetTagName();

  if (choice != 0)
    strm << ' ' << *choice;
  else
    strm << " (NULL)";
}


PString PASN_Choice::GetTypeAsString() const
{
  return "Choice";
}


int PASN_Choice::GetDataLength() const
{
  if (choice != 0)
    return choice->GetDataLength();
  return 0;
}


BOOL PASN_Choice::IsPrimitive() const
{
  if (choice != 0)
    return choice->IsPrimitive();
  return 0;
}


BOOL PASN_Choice::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = strm.ChoiceDecode(*this);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_Choice::Encode(PASN_Stream & strm) const
{
  strm.ChoiceEncode(*this);
}


BOOL PASN_Choice::DecodePER(PPER_Stream & strm)
{
  
  delete choice;

  if (strm.IsAtEnd()) {
    choice = 0;
    return 0;
  }

  BOOL ok = 1;

  if (extendable) {
    if (strm.SingleBitDecode()) {
      tag = strm.SmallUnsignedDecode() + numChoices;
      unsigned len;
      if (strm.LengthDecode(0, 2147483647, len) != 0)
        return 0;
      if (CreateObject()) {
        int nextPos = strm.GetPosition() + len;
        ok = choice->Decode(strm);
        strm.SetPosition(nextPos);
      }
      else {
        PASN_OctetString * open_type = new PASN_OctetString;
        open_type->SetConstraints(PASN_ConstrainedObject::FixedConstraint, len, len);
        open_type->Decode(strm);
        if (open_type->GetSize() > 0)
          choice = open_type;
        else {
          delete open_type;
          ok = 0;
        }
      }
      return ok;
    }
  }

  if (numChoices < 2)
    tag = 0;
  else {
    if (strm.UnsignedDecode(0, numChoices-1, tag) < 0)
      return 0;
  }

  if (CreateObject())
    ok = choice->Decode(strm);

  return ok;
}


void PASN_Choice::EncodePER(PPER_Stream & strm) const
{
  if(tag != 0xffffffff);else PAssertFunc("src/asner.cxx", 2992, (PLogicError));

  if (extendable) {
    BOOL extended = tag >= numChoices;
    strm.SingleBitEncode(extended);
    if (extended) {
      strm.SmallUnsignedEncode(tag - numChoices);
      strm.AnyTypeEncode(choice);
      return;
    }
  }

  if (numChoices > 1)
    strm.UnsignedEncode(tag, 0, numChoices-1);

  if (choice != 0)
    choice->Encode(strm);
}


BOOL PBER_Stream::ChoiceDecode(PASN_Choice & value)
{
  int savedPosition = GetPosition();

  unsigned tag;
  PASN_Object::TagClass tagClass;
  BOOL primitive;
  unsigned entryLen;
  if (!HeaderDecode(tag, tagClass, primitive, entryLen))
    return 0;

  SetPosition(savedPosition);

  value.SetTag(tag, tagClass);
  if (value.IsValid())
    return value.GetObjectA().Decode(*this);

  return 1;
}


void PBER_Stream::ChoiceEncode(const PASN_Choice & value)
{
  if (value.IsValid())
    value.GetObjectA().Encode(*this);
}


BOOL PPER_Stream::ChoiceDecode(PASN_Choice & value)
{
  return value.DecodePER(*this);
}


void PPER_Stream::ChoiceEncode(const PASN_Choice & value)
{
  value.EncodePER(*this);
}




PASN_Sequence::PASN_Sequence(unsigned tag, TagClass tagClass,
                             unsigned nOpts, BOOL extend, unsigned nExtend)
  : PASN_Object(tag, tagClass, extend)
{
  optionMap.SetConstraints(PASN_ConstrainedObject::FixedConstraint, nOpts, nOpts);
  knownExtensions = nExtend;
  totalExtensions = 0;
  endBasicEncoding = 0;
}


PASN_Sequence::PASN_Sequence(const PASN_Sequence & other)
  : PASN_Object(other),
    fields(other.fields.GetSize()),
    optionMap(other.optionMap),
    extensionMap(other.extensionMap)
{
  for (int i = 0; i < other.fields.GetSize(); i++)
    fields.SetAt(i, other.fields[i].Clone());

  knownExtensions = other.knownExtensions;
  totalExtensions = other.totalExtensions;
  endBasicEncoding = 0;
}


PASN_Sequence & PASN_Sequence::operator=(const PASN_Sequence & other)
{
  PASN_Object::operator=(other);

  fields.SetSize(other.fields.GetSize());
  for (int i = 0; i < other.fields.GetSize(); i++)
    fields.SetAt(i, other.fields[i].Clone());

  optionMap = other.optionMap;
  knownExtensions = other.knownExtensions;
  totalExtensions = other.totalExtensions;
  extensionMap = other.extensionMap;

  return *this;
}


BOOL PASN_Sequence::HasOptionalField(int opt) const
{
  if (opt < (int)optionMap.GetSize())
    return optionMap[opt];
  else
    return extensionMap[opt - optionMap.GetSize()];
}


void PASN_Sequence::IncludeOptionalField(int opt)
{
  if (opt < (int)optionMap.GetSize())
    optionMap.Set(opt);
  else {
    if(extendable);else PAssertFunc("src/asner.cxx", 3111, ("Must be extendable type"));
    opt -= optionMap.GetSize();
    if (opt >= (int)extensionMap.GetSize())
      extensionMap.SetSize(opt+1);
    extensionMap.Set(opt);
  }
}


PObject::Comparison PASN_Sequence::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_Sequence::Class()));else PAssertFunc("src/asner.cxx", 3122, (PInvalidCast));
  const PASN_Sequence & other = (const PASN_Sequence &)obj;
  return fields.Compare(other.fields);
}


PObject * PASN_Sequence::Clone() const
{
  if(IsClass(PASN_Sequence::Class()));else PAssertFunc("src/asner.cxx", 3130, (PInvalidCast));
  return new PASN_Sequence(*this);
}


void PASN_Sequence::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << "{\n";
  for (int i = 0; i < fields.GetSize(); i++) {
    strm << setw(indent+6) << "field[" << i << "] <";
    switch (fields[i].GetTagClass()) {
      case UniversalTagClass :
        strm << "Universal";
        break;
      case ApplicationTagClass :
        strm << "Application";
        break;
      case ContextSpecificTagClass :
        strm << "ContextSpecific";
        break;
      case PrivateTagClass :
        strm << "Private";
      default :
        break;
    }
    strm << '-' << fields[i].GetTag() << '-'
         << fields[i].GetTypeAsString() << "> = "
         << fields[i] << '\n';
  }
  strm << setw(indent-1) << "}";
}


PString PASN_Sequence::GetTypeAsString() const
{
  return "Sequence";
}


int PASN_Sequence::GetDataLength() const
{
  int len = 0;
  for (int i = 0; i < fields.GetSize(); i++)
    len += fields[i].GetObjectLength();
  return len;
}


BOOL PASN_Sequence::IsPrimitive() const
{
  return 0;
}


BOOL PASN_Sequence::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = PreambleDecode(strm) && UnknownExtensionsDecode(strm);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_Sequence::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);
  UnknownExtensionsEncode(strm);
}


BOOL PASN_Sequence::PreambleDecode(PASN_Stream & strm)
{
  return strm.SequencePreambleDecode(*this);
}


void PASN_Sequence::PreambleEncode(PASN_Stream & strm) const
{
  strm.SequencePreambleEncode(*this);
}


BOOL PASN_Sequence::KnownExtensionDecode(PASN_Stream & strm, int fld, PASN_Object & field)
{
  return strm.SequenceKnownDecode(*this, fld, field);
}


void PASN_Sequence::KnownExtensionEncode(PASN_Stream & strm, int fld, const PASN_Object & field) const
{
  strm.SequenceKnownEncode(*this, fld, field);
}


BOOL PASN_Sequence::UnknownExtensionsDecode(PASN_Stream & strm)
{
  return strm.SequenceUnknownDecode(*this);
}


void PASN_Sequence::UnknownExtensionsEncode(PASN_Stream & strm) const
{
  strm.SequenceUnknownEncode(*this);
}


BOOL PASN_Sequence::PreambleDecodeBER(PBER_Stream & strm)
{
  fields.RemoveAll();

  unsigned len;
  if (!strm.HeaderDecode(*this, len))
    return 0;

  endBasicEncoding = strm.GetPosition() + len;
  return !strm.IsAtEnd();
}


void PASN_Sequence::PreambleEncodeBER(PBER_Stream & strm) const
{
  strm.HeaderEncode(*this);
}


BOOL PASN_Sequence::KnownExtensionDecodeBER(PBER_Stream & strm, int, PASN_Object & field)
{
  if (strm.GetPosition() >= endBasicEncoding)
    return 0;

  return field.Decode(strm);
}


void PASN_Sequence::KnownExtensionEncodeBER(PBER_Stream & strm, int, const PASN_Object & field) const
{
  field.Encode(strm);
}


BOOL PASN_Sequence::UnknownExtensionsDecodeBER(PBER_Stream & strm)
{
  while (strm.GetPosition() < endBasicEncoding) {
    int savedPosition = strm.GetPosition();

    unsigned tag;
    PASN_Object::TagClass tagClass;
    BOOL primitive;
    unsigned entryLen;
    if (!strm.HeaderDecode(tag, tagClass, primitive, entryLen))
      return 0;

    int nextEntryPosition = strm.GetPosition() + entryLen;
    strm.SetPosition(savedPosition);

    PASN_Object * obj = strm.CreateObject(tag, tagClass, primitive);
    if (obj == 0)
      strm.SetPosition(nextEntryPosition);
    else {
      if (!obj->Decode(strm))
        return 0;

      fields.Append(obj);
    }
  }

  return 1;
}


void PASN_Sequence::UnknownExtensionsEncodeBER(PBER_Stream & strm) const
{
  for (int i = 0; i < fields.GetSize(); i++)
    fields[i].Encode(strm);
}


BOOL PASN_Sequence::PreambleDecodePER(PPER_Stream & strm)
{
  

  if (extendable) {
    if (strm.IsAtEnd())
      return 0;
    totalExtensions = strm.SingleBitDecode() ? -1 : 0;  
  }
  else
    totalExtensions = 0;
  return optionMap.Decode(strm);  
}


void PASN_Sequence::PreambleEncodePER(PPER_Stream & strm) const
{
  

  if (extendable) {
    BOOL hasExtensions = 0;
    for (unsigned i = 0; i < extensionMap.GetSize(); i++) {
      if (extensionMap[i]) {
        hasExtensions = 1;
        break;
      }
    }
    strm.SingleBitEncode(hasExtensions);  
    ((PASN_Sequence*)this)->totalExtensions = hasExtensions ? -1 : 0;
  }
  optionMap.Encode(strm);  
}


BOOL PASN_Sequence::NoExtensionsToDecode(PPER_Stream & strm)
{
  if (totalExtensions == 0)
    return 1;

  if (totalExtensions < 0) {
    totalExtensions = strm.SmallUnsignedDecode() + 1;
    extensionMap.SetConstraints(PASN_ConstrainedObject::FixedConstraint,
                                totalExtensions, totalExtensions);
    extensionMap.Decode(strm);
  }

  return 0;
}


BOOL PASN_Sequence::NoExtensionsToEncode(PPER_Stream & strm)
{
  if (totalExtensions == 0)
    return 1;

  if (totalExtensions < 0) {
    totalExtensions = extensionMap.GetSize();
    strm.SmallUnsignedEncode(totalExtensions-1);
    extensionMap.SetConstraints(PASN_ConstrainedObject::FixedConstraint,
                                totalExtensions, totalExtensions);
    extensionMap.Encode(strm);
  }

  return 0;
}


BOOL PASN_Sequence::KnownExtensionDecodePER(PPER_Stream & strm, int fld, PASN_Object & field)
{
  if (NoExtensionsToDecode(strm))
    return 1;

  if (!extensionMap[fld-optionMap.GetSize()])
    return 1;

  unsigned len;
  if (strm.LengthDecode(0, 2147483647, len) != 0)
    return 0;

  int nextExtensionPosition = strm.GetPosition() + len;
  BOOL ok = field.Decode(strm);
  strm.SetPosition(nextExtensionPosition);
  return ok;
}


void PASN_Sequence::KnownExtensionEncodePER(PPER_Stream & strm, int fld, const PASN_Object & field) const
{
  if (((PASN_Sequence*)this)->NoExtensionsToEncode(strm))
    return;

  if (!extensionMap[fld-optionMap.GetSize()])
    return;

  strm.AnyTypeEncode(&field);
}


BOOL PASN_Sequence::UnknownExtensionsDecodePER(PPER_Stream & strm)
{
  if (NoExtensionsToDecode(strm))
    return 1;

  if (totalExtensions <= knownExtensions)
    return 1;  

  int unknownCount = totalExtensions - knownExtensions;
  if (fields.GetSize() >= unknownCount)
    return 1;  

  fields.SetSize(unknownCount);

  int i;
  for (i = 0; i < fields.GetSize(); i++)
    fields.SetAt(i, new PASN_OctetString);

  for (i = knownExtensions; i < (int)extensionMap.GetSize(); i++) {
    if (extensionMap[i])
      if (!fields[i-knownExtensions].Decode(strm))
        return 0;
  }

  return 1;
}


void PASN_Sequence::UnknownExtensionsEncodePER(PPER_Stream & strm) const
{
  if (((PASN_Sequence*)this)->NoExtensionsToEncode(strm))
    return;

  int i;
  for (i = knownExtensions; i < totalExtensions; i++) {
    if (extensionMap[i])
      fields[i-knownExtensions].Encode(strm);
  }
}


BOOL PBER_Stream::SequencePreambleDecode(PASN_Sequence & seq)
{
  return seq.PreambleDecodeBER(*this);
}


void PBER_Stream::SequencePreambleEncode(const PASN_Sequence & seq)
{
  seq.PreambleEncodeBER(*this);
}


BOOL PBER_Stream::SequenceKnownDecode(PASN_Sequence & seq, int fld, PASN_Object & field)
{
  return seq.KnownExtensionDecodeBER(*this, fld, field);
}


void PBER_Stream::SequenceKnownEncode(const PASN_Sequence & seq, int fld, const PASN_Object & field)
{
  seq.KnownExtensionEncodeBER(*this, fld, field);
}


BOOL PBER_Stream::SequenceUnknownDecode(PASN_Sequence & seq)
{
  return seq.UnknownExtensionsDecodeBER(*this);
}


void PBER_Stream::SequenceUnknownEncode(const PASN_Sequence & seq)
{
  seq.UnknownExtensionsEncodeBER(*this);
}


BOOL PPER_Stream::SequencePreambleDecode(PASN_Sequence & seq)
{
  return seq.PreambleDecodePER(*this);
}


void PPER_Stream::SequencePreambleEncode(const PASN_Sequence & seq)
{
  seq.PreambleEncodePER(*this);
}


BOOL PPER_Stream::SequenceKnownDecode(PASN_Sequence & seq, int fld, PASN_Object & field)
{
  return seq.KnownExtensionDecodePER(*this, fld, field);
}


void PPER_Stream::SequenceKnownEncode(const PASN_Sequence & seq, int fld, const PASN_Object & field)
{
  seq.KnownExtensionEncodePER(*this, fld, field);
}


BOOL PPER_Stream::SequenceUnknownDecode(PASN_Sequence & seq)
{
  return seq.UnknownExtensionsDecodePER(*this);
}


void PPER_Stream::SequenceUnknownEncode(const PASN_Sequence & seq)
{
  seq.UnknownExtensionsEncodePER(*this);
}




PASN_Set::PASN_Set(unsigned tag, TagClass tagClass,
                   unsigned nOpts, BOOL extend, unsigned nExtend)
  : PASN_Sequence(tag, tagClass, nOpts, extend, nExtend)
{
}


PObject * PASN_Set::Clone() const
{
  if(IsClass(PASN_Set::Class()));else PAssertFunc("src/asner.cxx", 3531, (PInvalidCast));
  return new PASN_Set(*this);
}


PString PASN_Set::GetTypeAsString() const
{
  return "Set";
}




PASN_Array::PASN_Array(unsigned tag, TagClass tagClass)
  : PASN_ConstrainedObject(tag, tagClass)
{
}


PASN_Array::PASN_Array(const PASN_Array & other)
  : PASN_ConstrainedObject(other),
    array(other.array.GetSize())
{
  for (int i = 0; i < other.array.GetSize(); i++)
    array.SetAt(i, other.array[i].Clone());
}


PASN_Array & PASN_Array::operator=(const PASN_Array & other)
{
  PASN_ConstrainedObject::operator=(other);

  array.SetSize(other.array.GetSize());
  for (int i = 0; i < other.array.GetSize(); i++)
    array.SetAt(i, other.array[i].Clone());

  return *this;
}


void PASN_Array::SetSize(int newSize)
{
  int originalSize = array.GetSize();
  array.SetSize(newSize);
  for (int i = originalSize; i < newSize; i++)
    array.SetAt(i, CreateObject());
}


PObject::Comparison PASN_Array::Compare(const PObject & obj) const
{
  if(obj.IsDescendant(PASN_Array::Class()));else PAssertFunc("src/asner.cxx", 3582, (PInvalidCast));
  const PASN_Array & other = (const PASN_Array &)obj;
  return array.Compare(other.array);
}


void PASN_Array::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << array.GetSize() << " entries {\n";
  for (int i = 0; i < array.GetSize(); i++)
    strm << setw(indent+1) << "[" << i << "]=" << setprecision(indent) << array[i] << '\n';
  strm << setw(indent-1) << "}";
}


PString PASN_Array::GetTypeAsString() const
{
  return "Array";
}


int PASN_Array::GetDataLength() const
{
  int len = 0;
  for (int i = 0; i < array.GetSize(); i++)
    len += array[i].GetObjectLength();
  return len;
}


BOOL PASN_Array::IsPrimitive() const
{
  return 0;
}


BOOL PASN_Array::Decode(PASN_Stream & strm)
{
	int result;
	SetStartbyte( strm.GetPosition() );
  result = strm.ArrayDecode(*this);
	SetStopbyte( strm.GetPosition() );
	return result;
}


void PASN_Array::Encode(PASN_Stream & strm) const
{
  strm.ArrayEncode(*this);
}


BOOL PBER_Stream::ArrayDecode(PASN_Array & array)
{
  array.RemoveAll();

  unsigned len;
  if (!HeaderDecode(array, len))
    return 0;

  int endOffset = byteOffset + len;
  int count = 0;
  while (byteOffset < endOffset) {
    array.SetSize(count+1);
    if (!array[count].Decode(*this))
      return 0;
    count++;
  }

  byteOffset = endOffset;

  return 1;
}


void PBER_Stream::ArrayEncode(const PASN_Array & array)
{
  HeaderEncode(array);
  for (int i = 0; i < array.GetSize(); i++)
    array[i].Encode(*this);
}


BOOL PPER_Stream::ArrayDecode(PASN_Array & array)
{
  array.RemoveAll();

  unsigned size;
  if (array.ConstrainedLengthDecode(*this, size) < 0)
    return 0;

  array.SetSize(size);

  for (int i = 0; i < (int)size; i++) {
    if (!array[i].Decode(*this))
      return 0;
  }

  return 1;
}


void PPER_Stream::ArrayEncode(const PASN_Array & array)
{
  int size = array.GetSize();
  array.ConstrainedLengthEncode(*this, size);
  for (int i = 0; i < size; i++)
    array[i].Encode(*this);
}




PASN_Stream::PASN_Stream()
{
  Construct();
}


PASN_Stream::PASN_Stream(const PBYTEArray & bytes)
  : PBYTEArray(bytes)
{
  Construct();
}


PASN_Stream::PASN_Stream(const BYTE * buf, int size)
  : PBYTEArray(buf, size)
{
  Construct();
}


void PASN_Stream::Construct()
{
  byteOffset = 0;
  bitOffset = 8;
}


void PASN_Stream::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << " size=" << GetSize()
       << " pos=" << byteOffset << '.' << (8-bitOffset)
       << " {\n";
  int i = 0;
  while (i < GetSize()) {
    strm << setw(indent) << " " << hex << setfill('0');
    int j;
    for (j = 0; j < 16; j++)
      if (i+j < GetSize())
        strm << setw(2) << (unsigned)(BYTE)theArray[i+j] << ' ';
      else
        strm << "   ";
    strm << "  ";
    for (j = 0; j < 16; j++) {
      if (i+j < GetSize()) {
        if (isprint(theArray[i+j]))
          strm << theArray[i+j];
        else
          strm << ' ';
      }
    }
    strm << dec << setfill(' ') << '\n';
    i += 16;
  }
  strm << setw(indent-1) << "}";
}


void PASN_Stream::SetPosition(int newPos)
{
  if(byteOffset != P_MAX_INDEX);else PAssertFunc("src/asner.cxx", 3756, (PLogicError));

  if (newPos > GetSize())
    byteOffset = GetSize();
  else
    byteOffset = newPos;
  bitOffset = 8;
}


void PASN_Stream::ResetDecoder()
{
  byteOffset = 0;
  bitOffset = 8;
}


void PASN_Stream::BeginEncoding()
{
  bitOffset = 8;
  byteOffset = 0;
  PBYTEArray::operator=(PBYTEArray(20));
}


void PASN_Stream::CompleteEncoding()
{
  if (byteOffset != P_MAX_INDEX) {
    if (bitOffset != 8) {
      bitOffset = 8;
      byteOffset++;
    }
    SetSize(byteOffset);
    byteOffset = P_MAX_INDEX;
  }
}


BYTE PASN_Stream::ByteDecode()
{
  if (byteOffset >= GetSize())
    return 0;

  bitOffset = 8;
  return theArray[byteOffset++];
}


void PASN_Stream::ByteEncode(unsigned value)
{
  if(byteOffset != P_MAX_INDEX);else PAssertFunc("src/asner.cxx", 3806, (PLogicError));

  if (bitOffset != 8) {
    bitOffset = 8;
    byteOffset++;
  }
  if (byteOffset >= GetSize())
    SetSize(byteOffset+10);
  theArray[byteOffset++] = (BYTE)value;
}


unsigned PASN_Stream::BlockDecode(BYTE * bufptr, unsigned nBytes)
{
  ByteAlign();

  if (byteOffset+nBytes > (unsigned)GetSize())
    nBytes = GetSize() - byteOffset;

  if (nBytes == 0)
    return 0;

  memcpy(bufptr, &theArray[byteOffset], nBytes);
  byteOffset += nBytes;
  return nBytes;
}


void PASN_Stream::BlockEncode(const BYTE * bufptr, int nBytes)
{
  if(byteOffset != P_MAX_INDEX);else PAssertFunc("src/asner.cxx", 3836, (PLogicError));

  if (nBytes == 0)
    return;

  ByteAlign();
  if (byteOffset+nBytes >= GetSize())
    SetSize(byteOffset+nBytes+10);

  memcpy(theArray+byteOffset, bufptr, nBytes);
  byteOffset += nBytes;
}


void PASN_Stream::ByteAlign()
{
  if(byteOffset != P_MAX_INDEX);else PAssertFunc("src/asner.cxx", 3852, (PLogicError));

  if (bitOffset != 8) {
    bitOffset = 8;
    byteOffset++;
  }
}




PBER_Stream::PBER_Stream()
{
}


PBER_Stream::PBER_Stream(const PBYTEArray & bytes)
  : PASN_Stream(bytes)
{
}


PBER_Stream::PBER_Stream(const BYTE * buf, int size)
  : PASN_Stream(buf, size)
{
}


PBER_Stream & PBER_Stream::operator=(const PBYTEArray & bytes)
{
  PBYTEArray::operator=(bytes);
  ResetDecoder();
  return *this;
}



BOOL PBER_Stream::Read(PChannel & )
{
  return 0;






















































#line 3947 "src/asner.cxx"
}



BOOL PBER_Stream::Write(PChannel & )
{
  return 0;





#line 3960 "src/asner.cxx"
}


PASN_Object * PBER_Stream::CreateObject(unsigned tag,
                                        PASN_Object::TagClass tagClass,
                                        BOOL primitive) const
{
  if (tagClass == PASN_Object::UniversalTagClass) {
    switch (tag) {
      case PASN_Object::UniversalBoolean :
        return new PASN_Boolean();

      case PASN_Object::UniversalInteger :
        return new PASN_Integer();

      case PASN_Object::UniversalBitString :
        return new PASN_BitString();

      case PASN_Object::UniversalOctetString :
        return new PASN_OctetString();

      case PASN_Object::UniversalNull :
        return new PASN_Null();

      case PASN_Object::UniversalObjectId :
        return new PASN_ObjectId();

      case PASN_Object::UniversalReal :
        return new PASN_Real();

      case PASN_Object::UniversalEnumeration :
        return new PASN_Enumeration();

      case PASN_Object::UniversalSequence :
        return new PASN_Sequence();

      case PASN_Object::UniversalSet :
        return new PASN_Set();

      case PASN_Object::UniversalNumericString :
        return new PASN_NumericString();

      case PASN_Object::UniversalPrintableString :
        return new PASN_PrintableString();

      case PASN_Object::UniversalIA5String :
        return new PASN_IA5String();

      case PASN_Object::UniversalVisibleString :
        return new PASN_VisibleString();

      case PASN_Object::UniversalGeneralString :
        return new PASN_GeneralString();

      case PASN_Object::UniversalBMPString :
        return new PASN_BMPString();
    }
  }

  if (primitive)
    return new PASN_OctetString(tag, tagClass);
  else
    return new PASN_Sequence(tag, tagClass, 0, 0, 0);
}


BOOL PBER_Stream::HeaderDecode(unsigned & tagVal,
                               PASN_Object::TagClass & tagClass,
                               BOOL & primitive,
                               unsigned & len)
{
  BYTE ident = ByteDecode();
  tagClass = (PASN_Object::TagClass)(ident>>6);
  primitive = (ident&0x20) == 0;
  tagVal = ident&31;
  if (tagVal == 31) {
    BYTE b;
    tagVal = 0;
    do {
      if (IsAtEnd())
        return 0;

      b = ByteDecode();
      tagVal = (tagVal << 7) | (b&0x7f);
    } while ((b&0x80) != 0);
  }

  if (IsAtEnd())
    return 0;

  BYTE len_len = ByteDecode();
  if ((len_len & 0x80) == 0) {
    len = len_len;
    return 1;
  }

  len_len &= 0x7f;

  len = 0;
  while (len_len-- > 0) {
    if (IsAtEnd())
      return 0;

    len = (len << 8) | ByteDecode();
  }

  return 1;
}


BOOL PBER_Stream::HeaderDecode(PASN_Object & obj, unsigned & len)
{
  int pos = byteOffset;

  unsigned tagVal;
  PASN_Object::TagClass tagClass;
  BOOL primitive;
  if (HeaderDecode(tagVal, tagClass, primitive, len) &&
              tagVal == obj.GetTag() && tagClass == obj.GetTagClass())
    return 1;

  byteOffset = pos;
  return 0;
}


void PBER_Stream::HeaderEncode(const PASN_Object & obj)
{
  BYTE ident = (BYTE)(obj.GetTagClass() << 6);
  if (!obj.IsPrimitive())
    ident |= 0x20;
  unsigned tag = obj.GetTag();
  if (tag < 31)
    ByteEncode(ident|tag);
  else {
    ByteEncode(ident|31);
    unsigned count = (CountBits(tag)+6)/7;
    while (count-- > 1)
      ByteEncode((tag >> (count*7))&0x7f);
    ByteEncode(tag&0x7f);
  }

  int len = obj.GetDataLength();
  if (len < 128)
    ByteEncode(len);
  else {
    int count = (CountBits(len+1)+7)/8;
    ByteEncode(count|0x80);
    while (count-- > 0)
      ByteEncode(len >> (count*8));
  }
}





PPER_Stream::PPER_Stream(BOOL alignment)
{
  aligned = alignment;
}


PPER_Stream::PPER_Stream(const PBYTEArray & bytes, BOOL alignment)
  : PASN_Stream(bytes)
{
  aligned = alignment;
}


PPER_Stream::PPER_Stream(const BYTE * buf, int size, BOOL alignment)
  : PASN_Stream(buf, size)
{
  aligned = alignment;
}


PPER_Stream & PPER_Stream::operator=(const PBYTEArray & bytes)
{
  PBYTEArray::operator=(bytes);
  ResetDecoder();
  aligned = 1;
  return *this;
}


unsigned PPER_Stream::GetBitsLeft() const
{
  return (GetSize() - byteOffset)*8 - (8 - bitOffset);
}



BOOL PPER_Stream::Read(PChannel & )
{
  return 0;

















#line 4174 "src/asner.cxx"
}


BOOL PPER_Stream::Write(PChannel & )
{
  return 0;

















#line 4198 "src/asner.cxx"
}


BOOL PPER_Stream::SingleBitDecode()
{
  if ((GetSize() - byteOffset)*8 - (8 - bitOffset) == 0)
    return 0;

  bitOffset--;
  BOOL value = (theArray[byteOffset] & (1 << bitOffset)) != 0;

  if (bitOffset == 0) {
    bitOffset = 8;
    byteOffset++;
  }

  return value;
}


void PPER_Stream::SingleBitEncode(BOOL value)
{
  if(byteOffset != P_MAX_INDEX);else PAssertFunc("src/asner.cxx", 4220, (PLogicError));

  if (byteOffset >= GetSize())
    SetSize(byteOffset+10);

  bitOffset--;

  if (value)
    theArray[byteOffset] |= 1 << bitOffset;

  if (bitOffset == 0)
    ByteAlign();
}


int PPER_Stream::MultiBitDecode(unsigned nBits)
{
  if(nBits <= 32);else PAssertFunc("src/asner.cxx", 4237, (PInvalidParameter));

  unsigned bitsLeft = (GetSize() - byteOffset)*8 - (8 - bitOffset);
  if (nBits > bitsLeft)
    nBits = bitsLeft;

  if (nBits == 0)
    return 0;

  if (nBits < bitOffset) {
    bitOffset -= nBits;
    return (theArray[byteOffset] >> bitOffset) & ((1 << nBits) - 1);
  }

  int val = theArray[byteOffset] & ((1 << bitOffset) - 1);
  nBits -= bitOffset;
  bitOffset = 8;
  byteOffset++;

  while (nBits >= 8) {
    val = (val << 8) | (BYTE)theArray[byteOffset];
    byteOffset++;
    nBits -= 8;
  }

  if (nBits > 0) {
    bitOffset = 8 - nBits;
    val = (val << nBits) | ((BYTE)theArray[byteOffset] >> bitOffset);
  }

  return val;
}


void PPER_Stream::MultiBitEncode(int value, unsigned nBits)
{
  if(byteOffset != P_MAX_INDEX);else PAssertFunc("src/asner.cxx", 4273, (PLogicError));

  if (nBits == 0)
    return;

  if (byteOffset+nBits/8+1 >= (unsigned)GetSize())
    SetSize(byteOffset+10);

  
  if (nBits < sizeof(int)*8)
    value &= ((1 << nBits) - 1);

  if (nBits < bitOffset) {
    bitOffset -= nBits;
    theArray[byteOffset] |= value << bitOffset;
    return;
  }

  nBits -= bitOffset;
  theArray[byteOffset] |= (BYTE)(value >> nBits);
  bitOffset = 8;
  byteOffset++;

  while (nBits >= 8) {
    nBits -= 8;
    theArray[byteOffset] = (BYTE)(value >> nBits);
    byteOffset++;
  }

  if (nBits > 0) {
    bitOffset = 8 - nBits;
    theArray[byteOffset] |= (BYTE)((value & ((1 << nBits)-1)) << bitOffset);
  }
}


unsigned PPER_Stream::SmallUnsignedDecode()
{
  

  if (!SingleBitDecode())
    return MultiBitDecode(6);      

  unsigned len;
  if (LengthDecode(0, 2147483647, len) != 0)  
    return 0;

  ByteAlign();
  return MultiBitDecode(len*8);
}


void PPER_Stream::SmallUnsignedEncode(unsigned value)
{
  if (value < 64) {
    MultiBitEncode(value, 7);
    return;
  }

  SingleBitEncode(1);  

  int len = 4;
  if (value < 256)
    len = 1;
  else if (value < 65536)
    len = 2;
  else if (value < 0x1000000)
    len = 3;
  LengthEncode(len, 0, 2147483647);  
  ByteAlign();
  MultiBitEncode(value, len*8);
}


int PPER_Stream::UnsignedDecode(unsigned lower, unsigned upper, unsigned & value)
{
  

  if (lower == upper) { 
    value = lower;
    return 0;
  }

  if (IsAtEnd())
    return -1;

  unsigned range = (upper - lower) + 1;
  unsigned nBits = CountBits(range);

  if (aligned && (range == 0 || range > 255)) { 
    if (nBits > 16) {                           
      LengthDecode(1, (nBits+7)/8, nBits);      
      nBits *= 8;
    }
    else if (nBits > 8)    
      nBits = 16;          
    ByteAlign();           
  }

  value = MultiBitDecode(nBits) + lower;
  return 0;
}


void PPER_Stream::UnsignedEncode(int value, unsigned lower, unsigned upper)
{
  

  if (lower == upper) 
    return;

  unsigned range = (upper - lower) + 1;
  int nBits = CountBits(range);

  if (aligned && (range == 0 || range > 255)) { 
    if (nBits > 16) {                           
      int numBytes = value == 0 ? 1 : (((CountBits(value - lower + 1))+7)/8);
      LengthEncode(numBytes, 1, (nBits+7)/8);    
      nBits = numBytes*8;
    }
    else if (nBits > 8)      
      nBits = 16;            
    ByteAlign();             
  }

  MultiBitEncode(value - lower, nBits);
}


int PPER_Stream::LengthDecode(unsigned lower, unsigned upper, unsigned & len)
{
  

  if (upper != 2147483647 && !aligned) {
    if(upper - lower < 0x10000);else PAssertFunc("src/asner.cxx", 4407, (PUnimplementedFunction));  
    return lower + MultiBitDecode(CountBits(upper - lower + 1));   
  }

  if (upper < 65536)  
    return UnsignedDecode(lower, upper, len);

  
  ByteAlign();
  if (IsAtEnd())
    return -1;

  if (SingleBitDecode() == 0) {
    len = MultiBitDecode(7);   
    return 0;
  }

  if (SingleBitDecode() == 0) {
    len = MultiBitDecode(14);    
    return 0;
  }

  PAssertFunc("src/asner.cxx", 4429, (PUnimplementedFunction));  
  return 1;
}


void PPER_Stream::LengthEncode(unsigned len, unsigned lower, unsigned upper)
{
  

  if (upper != 2147483647 && !aligned) {
    if(upper - lower < 0x10000);else PAssertFunc("src/asner.cxx", 4439, (PUnimplementedFunction));  
    MultiBitEncode(len - lower, CountBits(upper - lower + 1));   
    return;
  }

  if (upper < 65536) { 
    UnsignedEncode(len, lower, upper);
    return;
  }

  ByteAlign();

  if (len < 128) {
    MultiBitEncode(len, 8);   
    return;
  }

  SingleBitEncode(1);

  if (len < 0x2000) {
    MultiBitEncode(len, 15);    
    return;
  }

  SingleBitEncode(1);
  if(len < 0x2000);else PAssertFunc("src/asner.cxx", 4464, (PUnimplementedFunction));  
}


void PPER_Stream::AnyTypeEncode(const PASN_Object * value)
{
  PPER_Stream substream;

  if (value != 0)
    value->Encode(substream);

  if (substream.GetPosition() == 0)   
    substream.SingleBitEncode(0); 

  substream.CompleteEncoding();

  int nBytes = substream.GetSize();
  LengthEncode(nBytes, 0, 2147483647);
  BlockEncode(substream.GetPointer(), nBytes);
}



