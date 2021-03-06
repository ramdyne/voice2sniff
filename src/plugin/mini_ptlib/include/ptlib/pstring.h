/*
 * pstring.h
 *
 * Character string class.
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
 */

#ifdef __GNUC__
#pragma interface
#endif


///////////////////////////////////////////////////////////////////////////////
// PString class

class PStringArray;

#ifdef PHAS_UNICODE
#define PSTRING_ANCESTOR_CLASS PWordArray
#else
#define PSTRING_ANCESTOR_CLASS PCharArray
#endif

/**The character string class. It supports a wealth of additional functions
   for string processing and conversion. Operators are provided so that
   strings can virtually be treated as a basic type.

   The #PSTRING_ANCESTOR_CLASS# is dependent on whether UNICODE
   support is selected. The {\bf entire library and application} must be
   compiled with or without UNICODE or undefined results will occur.
   #PSTRING_ANCESTOR_CLASS# macro is normally set to
   #PCharArray#.

   An important feature of the string class, which is not present in other
   container classes, is that when the string contents is changed, that is
   resized or elements set, the string is "dereferenced", and a duplicate
   made of its contents. That is this instance of the array is disconnected
   from all other references to the string data, if any, and a new string array
   contents created. For example consider the following:
\begin{verbatim}
          PString s1 = "String"; // New array allocated and set to "String"
          PString s2 = s1;       // s2 has pointer to same array as s1
                                 // and reference count is 2 for both
          s1[0] = 's';           // Breaks references into different strings
\end{verbatim}
   at the end s1 is "string" and s2 is "String" both with reference count of 1.

   The functions that will "break" a reference are #SetSize()#,
   #SetMinSize()#, #GetPointer()#, #SetAt()# and
   #operator[]#.

   Note that the array is a '\0' terminated string as in C strings. Thus the
   memory allocated, and the length of the string may be different values.
 */
#ifdef DOC_PLUS_PLUS
class PString : public PCharArray {
#endif
PDECLARE_CLASS(PString, PSTRING_ANCESTOR_CLASS);
  public:
  /**@name Construction */
  //@{
    /**Construct an empty string. This will have one character in it which is
       the '\0' character.
     */
    PINLINE PString();

    /**Create a new reference to the specified string. The string memory is not
       copied, only the pointer to the data.
     */
    PINLINE PString(
      const PString & str  /// String to create new reference to.
    );

    /**Create a string from the C string array. This is most commonly used with
       a literal string, eg "hello". A new memory block is allocated of a size
       sufficient to take the length of the string and its terminating
       '\0' character.

       If UNICODE is used then each char from the char pointer is mapped to a
       single UNICODE character.
     */
    PString(
      const char * cstr /// Standard '\0' terminated C string.
    );

    /**Create a string from the Unicode string array.
       A new memory block is allocated of a size sufficient to take the length
       of the string and its terminating '\0' character.
     */
    PString(
      const WORD * ustr /// Unicode null terminated string.
    );

    /**Create a string from the array. A new memory block is allocated of
       a size equal to #len# plus one which is sufficient to take
       the string and a terminating '\0' character.

       If UNICODE is used then each char from the char pointer is mapped to a
       single UNICODE character.

       Note that this function will allow a string with embedded '\0'
       characters to be created, but most of the functions here will be unable
       to access characters beyond the first '\0'. Furthermore, if the
       #MakeMinimumSize()# function is called, all data beyond that first
       #'\0'# character will be lost.
     */
    PString(
      const char * cstr,  /// Pointer to a string of characters.
      PINDEX len          /// Length of the string in bytes.
    );

    /**Create a string from the array. A new memory block is allocated of
       a size equal to #len# plus one which is sufficient to take
       the string and a terminating '\0' character.

       Note that this function will allow a string with embedded '\0'
       characters to be created, but most of the functions here will be unable
       to access characters beyond the first '\0'. Furthermore, if the
       #MakeMinimumSize()# function is called, all data beyond that first
       #'\0'# character will be lost.
     */
    PString(
      const WORD * cstr,  /// Pointer to a string of Unicode characters.
      PINDEX len          /// Length of the string in bytes.
    );

    /**Create a string from the single character. This is most commonly used
       as a type conversion constructor when a literal character, eg 'A' is
       used in a string expression. A new memory block is allocated of two
       characters to take the char and its terminating '\0' character.

       If UNICODE is used then the char is mapped to a single UNICODE
       character.
     */
    PString(
      char ch    /// Single character to initialise string.
    );

    enum ConversionType {
      Pascal,   // Data is a length byte followed by characters.
      Basic,    // Data is two length bytes followed by characters.
      Literal,  // Data is C language style string with \ escape codes.
      Signed,   // Convert a signed integer to a string.
      Unsigned, // Convert an unsigned integer to a string.
      Decimal,  // Convert a real number to a string in decimal format.
      Exponent, // Convert a real number to a string in exponent format.
      Printf,   // Formatted output, sprintf() style function.
      NumConversionTypes
    };
    /* Type of conversion to make in the conversion constructors.
     */

    /* Contruct a new string converting from the spcified data source into
       a string array.
     */
    PString(
      ConversionType type,  // Type of data source for conversion.
      const char * str,    // String to convert.
      ...                 // Extra parameters for #sprintf()# call.
    );
    PString(
      ConversionType type,  // Type of data source for conversion.
      long value,           // Integer value to convert.
      unsigned base = 10    // Number base to use for the integer conversion.
    );
    PString(
      ConversionType type,  // Type of data source for conversion.
      double value,         // Floating point value to convert.
      unsigned places       // Number of decimals in real number output.
    );

    /**Assign the string to the current object. The current instance then
       becomes another reference to the same string in the #str#
       parameter.
       
       @return
       reference to the current PString object.
     */
    PString & operator=(
      const PString & str  /// New string to assign.
    );

    /**Assign the C string to the current object. The current instance then
       becomes a unique reference to a copy of the #cstr# parameter.
       The #cstr# parameter is typically a literal string, eg:
\begin{verbatim}
          myStr = "fred";
\end{verbatim}
       @return
       reference to the current PString object.
     */
    PString & operator=(
      const char * cstr  /// C string to assign.
    );

    /**Assign the character to the current object. The current instance then
       becomes a unique reference to a copy of the character parameter. eg:
\begin{verbatim}
          myStr = 'A';
\end{verbatim}
       @return
       reference to the current PString object.
     */
    PString & operator=(
      char ch            /// Character to assign.
    );
  //@}

  /**@name Overrides from class PObject */
  //@{
    /**Make a complete duplicate of the string. Note that the data in the
       array of characters is duplicated as well and the new object is a
       unique reference to that data.
     */
    virtual PObject * Clone() const;

    /**Get the relative rank of the two strings. The system standard function,
       eg strcmp(), is used.

       @return
       comparison of the two objects, #EqualTo# for same,
       #LessThan# for #obj# logically less than the
       object and #GreaterThan# for #obj# logically
       greater than the object.
     */
    virtual Comparison Compare(
      const PObject & obj   /// Other PString to compare against.
    ) const;

    /**Output the string to the specified stream.
     */
    virtual void PrintOn(
      ostream & strm  /// I/O stream to output to.
    ) const;

    /**Input the string from the specified stream. This will read all
       characters until a end of line is reached. The end of line itself is
       {\bf not} placed in the string, however it {\bf is} removed from
       the stream.
     */
    virtual void ReadFrom(
      istream & strm  /// I/O stream to input from.
    );

    /**Calculate a hash value for use in sets and dictionaries.
    
       The hash function for strings will produce a value based on the sum of
       the first three characters of the string. This is a fairly basic
       function and make no assumptions about the string contents. A user may
       descend from PString and override the hash function if they can take
       advantage of the types of strings being used, eg if all strings start
       with the letter 'A' followed by 'B or 'C' then the current hash function
       will not perform very well.

       @return
       hash value for string.
     */
    virtual PINDEX HashFunction() const;
  //@}

  /**@name Overrides from class PContainer */
  //@{
    /**Set the size of the string. A new string may be allocated to accomodate
       the new number of characters. If the string increases in size then the
       new characters are initialised to zero. If the string is made smaller
       then the data beyond the new size is lost.

       Note that this function will break the current instance from multiple
       references to an array. A new array is allocated and the data from the
       old array copied to it.

       @return
       TRUE if the memory for the array was allocated successfully.
     */
    virtual BOOL SetSize(
      PINDEX newSize  /// New size of the array in elements.
    );

    /**Determine if the string is empty. This is semantically slightly
       different from the usual #PContainer::IsEmpty()# function. It does
       not test for #PContainer::GetSize()# equal to zero, it tests for
       #GetLength()# equal to zero.

       @return
       TRUE if no non-null characters in string.
     */
    virtual BOOL IsEmpty() const;

    /**Make this instance to be the one and only reference to the container
       contents. This implicitly does a clone of the contents of the container
       to make a unique reference. If the instance was already unique then
       the function does nothing.

       @return
       TRUE if the instance was already unique.
     */
    virtual BOOL MakeUnique();
  //@}


  /**@name Size/Length functions */
  //@{
    /**Set the actual memory block array size to the minimum required to hold
       the current string contents.
       
       Note that this function will break the current instance from multiple
       references to the string. A new string buffer is allocated and the data
       from the old string buffer copied to it.

       @return
       TRUE if new memory block successfully allocated.
     */
    BOOL MakeMinimumSize();

    /**Determine the length of the null terminated string. This is different
       from #PContainer::GetSize()# which returns the amount of memory
       allocated to the string. This is often, though no necessarily, one
       larger than the length of the string.
       
       @return
       length of the null terminated string.
     */
    PINLINE PINDEX GetLength() const;

    /**Determine if the string is NOT empty. This is semantically identical
       to executing !IsEmpty() on the string.

       @return
       TRUE if non-null characters in string.
     */
    BOOL operator!() const;
  //@}

  /**@name Concatenation operators **/
  //@{
    /**Concatenate two strings to produce a third. The original strings are
       not modified, an entirely new unique reference to a string is created.
       
       @return
       new string with concatenation of the object and parameter.
     */
    PString operator+(
      const PString & str   /// String to concatenate.
    ) const;

    /**Concatenate a C string to a PString to produce a third. The original
       string is not modified, an entirely new unique reference to a string
       is created. The #cstr# parameter is typically a literal
       string, eg:
\begin{verbatim}
          myStr = aStr + "fred";
\end{verbatim}

       @return
       new string with concatenation of the object and parameter.
     */
    PString operator+(
      const char * cstr  /// C string to concatenate.
    ) const;

    /**Concatenate a single character to a PString to produce a third. The
       original string is not modified, an entirely new unique reference to a
       string is created. The #ch# parameter is typically a
       literal, eg:
\begin{verbatim}
          myStr = aStr + '!';
\end{verbatim}

       @return
       new string with concatenation of the object and parameter.
     */
    PString operator+(
      char ch   /// Character to concatenate.
    ) const;

    /**Concatenate a PString to a C string to produce a third. The original
       string is not modified, an entirely new unique reference to a string
       is created. The #cstr# parameter is typically a literal
       string, eg:
\begin{verbatim}
          myStr = "fred" + aStr;
\end{verbatim}

       @return
       new string with concatenation of the object and parameter.
     */
    friend PString operator+(
      const char * cstr,    /// C string to be concatenated to.
      const PString & str   /// String to concatenate.
    );

    /**Concatenate a PString to a single character to produce a third. The
       original string is not modified, an entirely new unique reference to a
       string is created. The #c# parameter is typically a literal,
       eg:
\begin{verbatim}
          myStr = '!' + aStr;
\end{verbatim}

       @return
       new string with concatenation of the object and parameter.
     */
    friend PString operator+(
      char  c,              /// Character to be concatenated to.
      const PString & str   /// String to concatenate.
    );

    /**Concatenate a string to another string, modifiying that string.

       @return
       reference to string that was concatenated to.
     */
    PString & operator+=(
      const PString & str   /// String to concatenate.
    );

    /**Concatenate a C string to a PString, modifiying that string. The
       #cstr# parameter is typically a literal string, eg:
\begin{verbatim}
          myStr += "fred";
\end{verbatim}

       @return
       reference to string that was concatenated to.
     */
    PString & operator+=(
      const char * cstr  /// C string to concatenate.
    );

    /**Concatenate a single character to a PString. The #ch#
       parameter is typically a literal, eg:
\begin{verbatim}
          myStr += '!';
\end{verbatim}

       @return
       new string with concatenation of the object and parameter.
     */
    PString & operator+=(
      char ch   /// Character to concatenate.
    );


    /**Concatenate two strings to produce a third. The original strings are
       not modified, an entirely new unique reference to a string is created.
       
       @return
       new string with concatenation of the object and parameter.
     */
    PString operator&(
      const PString & str   /// String to concatenate.
    ) const;

    /**Concatenate a C string to a PString to produce a third. The original
       string is not modified, an entirely new unique reference to a string
       is created. The #cstr# parameter is typically a literal
       string, eg:
\begin{verbatim}
          myStr = aStr & "fred";
\end{verbatim}

       This function differes from operator+ in that it assures there is at
       least one space between the strings. Exactly one space is added if
       there is not a space at the end of the first or beggining of the last
       string.

       @return
       new string with concatenation of the object and parameter.
     */
    PString operator&(
      const char * cstr  /// C string to concatenate.
    ) const;

    /**Concatenate a single character to a PString to produce a third. The
       original string is not modified, an entirely new unique reference to a
       string is created. The #ch# parameter is typically a
       literal, eg:
\begin{verbatim}
          myStr = aStr & '!';
\end{verbatim}

       This function differes from operator+ in that it assures there is at
       least one space between the strings. Exactly one space is added if
       there is not a space at the end of the first or beggining of the last
       string.

       @return
       new string with concatenation of the object and parameter.
     */
    PString operator&(
      char ch   /// Character to concatenate.
    ) const;

    /**Concatenate a PString to a C string to produce a third. The original
       string is not modified, an entirely new unique reference to a string
       is created. The #cstr# parameter is typically a literal
       string, eg:
\begin{verbatim}
          myStr = "fred" & aStr;
\end{verbatim}

       This function differes from operator+ in that it assures there is at
       least one space between the strings. Exactly one space is added if
       there is not a space at the end of the first or beggining of the last
       string.

       @return
       new string with concatenation of the object and parameter.
     */
    friend PString operator&(
      const char * cstr,    /// C string to be concatenated to.
      const PString & str   /// String to concatenate.
    );

    /**Concatenate a PString to a single character to produce a third. The
       original string is not modified, an entirely new unique reference to a
       string is created. The #c# parameter is typically a literal,
       eg:
\begin{verbatim}
          myStr = '!' & aStr;
\end{verbatim}

       This function differes from #operator+# in that it assures there is at
       least one space between the strings. Exactly one space is added if
       there is not a space at the end of the first or beggining of the last
       string.

       @return
       new string with concatenation of the object and parameter.
     */
    friend PString operator&(
      char  ch,              /// Character to be concatenated to.
      const PString & str   /// String to concatenate.
    );

    /**Concatenate a string to another string, modifiying that string.

       @return
       reference to string that was concatenated to.
     */
    PString & operator&=(
      const PString & str   /// String to concatenate.
    );

    /**Concatenate a C string to a PString, modifiying that string. The
       #cstr# parameter is typically a literal string, eg:
\begin{verbatim}
          myStr &= "fred";
\end{verbatim}

       This function differes from operator+ in that it assures there is at
       least one space between the strings. Exactly one space is added if
       there is not a space at the end of the first or beggining of the last
       string.

       @return
       reference to string that was concatenated to.
     */
    PString & operator&=(
      const char * cstr  /// C string to concatenate.
    );


    /**Concatenate a character to a PString, modifiying that string. The
       #ch# parameter is typically a literal string, eg:
\begin{verbatim}
          myStr &= '!';
\end{verbatim}

       This function differes from operator+ in that it assures there is at
       least one space between the strings. Exactly one space is added if
       there is not a space at the end of the first or beggining of the last
       string.

       @return
       reference to string that was concatenated to.
     */
    PString & operator&=(
      char ch  /// Character to concatenate.
    );
  //@}


  /**@name Comparison operators */
  //@{
    /**Compare two strings using case insensitive comparison.

       @return
       TRUE if equal.
     */
    BOOL operator*=(
      const PString & str  /// PString object to compare against.
    ) const;

    /**Compare two strings using the #PObject::Compare()# function. This
       is identical to the #PObject# class function but is necessary due
       to other overloaded versions.

       @return
       TRUE if equal.
     */
    BOOL operator==(
      const PObject & str  /// PString object to compare against.
    ) const;

    /**Compare two strings using the #PObject::Compare()# function. This
       is identical to the #PObject# class function but is necessary due
       to other overloaded versions.

       @return
       TRUE if not equal.
     */
    BOOL operator!=(
      const PObject & str  /// PString object to compare against.
    ) const;

    /**Compare two strings using the #PObject::Compare()# function. This
       is identical to the #PObject# class function but is necessary due
       to other overloaded versions.

       @return
       TRUE if less than.
     */
    BOOL operator<(
      const PObject & str  /// PString object to compare against.
    ) const;

    /**Compare two strings using the #PObject::Compare()# function. This
       is identical to the #PObject# class function but is necessary due
       to other overloaded versions.

       @return
       TRUE if greater than.
     */
    BOOL operator>(
      const PObject & str  /// PString object to compare against.
    ) const;

    /**Compare two strings using the #PObject::Compare()# function. This
       is identical to the #PObject# class function but is necessary due
       to other overloaded versions.

       @return
       TRUE if less than or equal.
     */
    BOOL operator<=(
      const PObject & str  /// PString object to compare against.
    ) const;

    /**Compare two strings using the #PObject::Compare()# function. This
       is identical to the #PObject# class function but is necessary due
       to other overloaded versions.

       @return
       TRUE if greater than or equal.
     */
    BOOL operator>=(
      const PObject & str  /// PString object to compare against.
    ) const;


    /**Compare a PString to a C string using a case insensitive compare
       function. The #cstr# parameter is typically a literal string,
       eg:
\begin{verbatim}
          if (myStr == "fred")
\end{verbatim}

       @return
       TRUE if equal.
     */
    BOOL operator*=(
      const char * cstr  /// C string to compare against.
    ) const;

    /**Compare a PString to a C string using the ##Compare()##
       function. The #cstr# parameter is typically a literal string,
       eg:
\begin{verbatim}
          if (myStr == "fred")
\end{verbatim}

       @return
       TRUE if equal.
     */
    BOOL operator==(
      const char * cstr  /// C string to compare against.
    ) const;

    /**Compare a PString to a C string using the #PObject::Compare()#
       function. The #cstr# parameter is typically a literal
       string, eg:
\begin{verbatim}
          if (myStr != "fred")
\end{verbatim}

       @return
       TRUE if not equal.
     */
    BOOL operator!=(
      const char * cstr  /// C string to compare against.
    ) const;

    /**Compare a PString to a C string using the #PObject::Compare()#
       function. The #cstr# parameter is typically a literal
       string, eg:
\begin{verbatim}
          if (myStr < "fred")
\end{verbatim}

       @return
       TRUE if less than.
     */
    BOOL operator<(
      const char * cstr  /// C string to compare against.
    ) const;

    /**Compare a PString to a C string using the #PObject::Compare()#
       function. The #cstr# parameter is typically a literal
       string, eg:
\begin{verbatim}
          if (myStr > "fred")
\end{verbatim}

       @return
       TRUE if greater than.
     */
    BOOL operator>(
      const char * cstr  /// C string to compare against.
    ) const;

    /**Compare a PString to a C string using the #PObject::Compare()#
       function. The #cstr# parameter is typically a literal
       string, eg:
\begin{verbatim}
          if (myStr <= "fred")
\end{verbatim}

       @return
       TRUE if less than or equal.
     */
    BOOL operator<=(
      const char * cstr  /// C string to compare against.
    ) const;

    /**Compare a PString to a C string using the #PObject::Compare()#
       function. The #cstr# parameter is typically a literal
       string, eg:
\begin{verbatim}
          if (myStr >= "fred")
\end{verbatim}

       @return
       TRUE if greater than or equal.
     */
    BOOL operator>=(
      const char * cstr  /// C string to compare against.
    ) const;
  //@}


  /**@name Search & replace functions */
  //@{
    /** Locate the position within the string of the character. */
    PINDEX Find(
      char ch,              /// Character to search for in string.
      PINDEX offset = 0     /// Offset into string to begin search.
    ) const;

    /** Locate the position within the string of the substring. */
    PINDEX Find(
      const PString & str,  /// String to search for in string.
      PINDEX offset = 0     /// Offset into string to begin search.
    ) const;

    /* Locate the position within the string of the character or substring. The
       search will begin at the character offset provided.
       
       If #offset# is beyond the length of the string, then the
       function will always return #P_MAX_INDEX#.
       
       The matching will be for identical character or string. If a search
       ignoring case is required then the string should be converted to a
       #PCaselessString# before the search is made.

       @return
       position of character or substring in the string, or P_MAX_INDEX if the
       character or substring is not in the string.
     */
    PINDEX Find(
      const char * cstr,    /// C string to search for in string.
      PINDEX offset = 0     /// Offset into string to begin search.
    ) const;

    /** Locate the position of the last matching character. */
    PINDEX FindLast(
      char ch,                     /// Character to search for in string.
      PINDEX offset = P_MAX_INDEX  /// Offset into string to begin search.
    ) const;

    /** Locate the position of the last matching substring. */
    PINDEX FindLast(
      const PString & str,         /// String to search for in string.
      PINDEX offset = P_MAX_INDEX  /// Offset into string to begin search.
    ) const;

    /**Locate the position of the last matching substring.
       Locate the position within the string of the last matching character or
       substring. The search will begin at the character offset provided,
       moving backward through the string.

       If #offset# is beyond the length of the string, then the
       search begins at the end of the string. If #offset# is zero
       then the function always returns #P_MAX_INDEX#.

       The matching will be for identical character or string. If a search
       ignoring case is required then the string should be converted to a
       #PCaselessString# before the search is made.

       @return
       position of character or substring in the string, or P_MAX_INDEX if the
       character or substring is not in the string.
     */
    PINDEX FindLast(
      const char * cstr,           /// C string to search for in string.
      PINDEX offset = P_MAX_INDEX  /// Offset into string to begin search.
    ) const;

    /** Locate the position of one of the characters in the set. */
    PINDEX FindOneOf(
      const PString & set,  /// String of characters to search for in string.
      PINDEX offset = 0     /// Offset into string to begin search.
    ) const;

    /**Locate the position of one of the characters in the set.
       The search will begin at the character offset provided.

       If #offset# is beyond the length of the string, then the
       function will always return #P_MAX_INDEX#.
       
       The matching will be for identical character or string. If a search
       ignoring case is required then the string should be converted to a
       #PCaselessString# before the search is made.

       @return
       position of character in the string, or P_MAX_INDEX if no characters
       from the set are in the string.
     */
    PINDEX FindOneOf(
      const char * cset,    /// C string of characters to search for in string.
      PINDEX offset = 0     /// Offset into string to begin search.
    ) const;

    /**Locate the substring within the string and replace it with the specifed
       substring. The search will begin at the character offset provided.

       If #offset# is beyond the length of the string, then the
       function will do nothing.

       The matching will be for identical character or string. If a search
       ignoring case is required then the string should be converted to a
       #PCaselessString# before the search is made.
     */
    void Replace(
      const PString & target,   /// String to be replaced in string.
      const PString & subs,     /// String to do replace in string.
      BOOL all = FALSE,         /// Replace all occurrences of string.
      PINDEX offset = 0         /// Offset into string to begin search.
    );

    /**Splice the string into the current string at the specified position. The
       specified number of bytes are removed from the string.

       Note that this function will break the current instance from multiple
       references to the string. A new string buffer is allocated and the data
       from the old string buffer copied to it.
     */
    void Splice(
      const PString & str,  /// Substring to insert.
      PINDEX pos,           /// Position in string to insert the substring.
      PINDEX len = 0        /// Length of section to remove.
    );

    /**Splice the string into the current string at the specified position. The
       specified number of bytes are removed from the string.

       Note that this function will break the current instance from multiple
       references to the string. A new string buffer is allocated and the data
       from the old string buffer copied to it.
     */
    void Splice(
      const char * cstr,    /// Substring to insert.
      PINDEX pos,           /// Position in string to insert the substring.
      PINDEX len = 0        /// Length of section to remove.
    );

    /**Remove the substring from the string.

       Note that this function will break the current instance from multiple
       references to the string. A new string buffer is allocated and the data
       from the old string buffer copied to it.
     */
    void Delete(
      PINDEX start,   /// Position in string to remove.
      PINDEX len      /// Number of characters to delete.
    );
  //@}


  /**@name Sub-string functions */
  //@{
    /**Extract a portion of the string into a new string. The original string
       is not changed and a new unique reference to a string is returned.
       
       The substring is returned inclusive of the characters at the
       #start# and #end# positions.
       
       If the #end# position is greater than the length of the
       string then all characters from the #start# up to the end of
       the string are returned.

       If #start# is greater than the length of the string or
       #end# is before #start# then an empty string is
       returned.

       @return
       substring of the source string.
     */
    PString operator()(
      PINDEX start,  /// Starting position of the substring.
      PINDEX end     /// Ending position of the substring.
    ) const;

    /**Extract a portion of the string into a new string. The original string
       is not changed and a new unique reference to a string is returned.
       
       A substring from the beginning of the string for the number of
       characters specified is extracted.
       
       If #len# is greater than the length of the string then all
       characters to the end of the string are returned.

       If #len# is zero then an empty string is returned.

       @return
       substring of the source string.
     */
    PString Left(
      PINDEX len   /// Number of characters to extract.
    ) const;

    /**Extract a portion of the string into a new string. The original string
       is not changed and a new unique reference to a string is returned.

       A substring from the end of the string for the number of characters
       specified is extracted.
       
       If #len# is greater than the length of the string then all
       characters to the beginning of the string are returned.

       If #len# is zero then an empty string is returned.

       @return
       substring of the source string.
     */
    PString Right(
      PINDEX len   /// Number of characters to extract.
    ) const;

    /**Extract a portion of the string into a new string. The original string
       is not changed and a new unique reference to a string is returned.
       
       A substring from the #start# position for the number of
       characters specified is extracted.
       
       If #len# is greater than the length of the string from the
       #start# position then all characters to the end of the
       string are returned.

       If #start# is greater than the length of the string or
       #len# is zero then an empty string is returned.

       @return
       substring of the source string.
     */
    PString Mid(
      PINDEX start,             /// Starting position of the substring.
      PINDEX len = P_MAX_INDEX  /// Number of characters to extract.
    ) const;


    /**Create a string consisting of all characters from the source string
       except all spaces at the beginning of the string. The original string
       is not changed and a new unique reference to a string is returned.
       
       @return
       string with leading spaces removed.
     */
    PString LeftTrim() const;

    /**Create a string consisting of all characters from the source string
       except all spaces at the end of the string. The original string is not
       changed and a new unique reference to a string is returned.
       
       @return
       string with trailing spaces removed.
     */
    PString RightTrim() const;

    /**Create a string consisting of all characters from the source string
       except all spaces at the beginning and end of the string. The original
       string is not changed and a new unique reference to a string is
       returned.
       
       @return
       string with leading and trailing spaces removed.
     */
    PString Trim() const;


    /**Create a string consisting of all characters from the source string
       with all upper case letters converted to lower case. The original
       string is not changed and a new unique reference to a string is
       returned.
       
       @return
       string with upper case converted to lower case.
     */
    PString ToLower() const;

    /**Create a string consisting of all characters from the source string
       with all lower case letters converted to upper case. The original
       string is not changed and a new unique reference to a string is
       returned.
       
       @return
       string with lower case converted to upper case.
     */
    PString ToUpper() const;


    /** Split the string into an array of substrings. */
    PStringArray Tokenise(
      const PString & separators,
        /// A string for the set of separator characters that delimit tokens.
      BOOL onePerSeparator = TRUE
        /// Flag for if there are empty tokens between consecutive separators.
    ) const;
    /**Split the string into an array of substrings.
       Divide the string into an array of substrings delimited by characters
       from the specified set.
       
       There are two options for the tokenisation, the first is where the
       #onePerSeparator# is TRUE. This form will produce a token
       for each delimiter found in the set. Thus the string ",two,three,,five"
       would be split into 5 substrings; "", "two", "three", "" and "five".
       
       The second form where #onePerSeparator# is FALSE is used
       where consecutive delimiters do not constitute a empty token. In this
       case the string "  a list  of words  " would be split into 4 substrings;
       "a", "list", "of" and "words".

       There is an important distinction when there are delimiters at the
       beginning or end of the source string. In the first case there will be
       empty strings at the end of the array and in the second the delimiters
       are ignored.

       @return
       an array of substring for each token in the string.
     */
    PStringArray Tokenise(
      const char * cseparators,
        /// A C string for the set of separator characters that delimit tokens.
      BOOL onePerSeparator = TRUE
        /// Flag for if there are empty tokens between consecutive separators.
    ) const;

    /**Split the string into individual lines. The line delimiters may be a
       carriage return ('\r'), a line feed ('\n') or a carriage return and
       line feed pair ("\r\n"). A line feed and carriage return pair ("\n\r")
       would yield a blank line. between the characters.

       The #Tokenise()# function should not be used to split a string
       into lines as a #"\r\n"# pair consitutes a single line
       ending. The #Tokenise()# function would produce a blank line in
       between them.

       @return
       string array with a substring for each line in the string.
     */
    PStringArray Lines() const;
  //@}

  /**@name Conversion functions */
  //@{
    /**Concatenate a formatted output to the string. This is identical to the
       standard C library #sprintf()# function, but appends its
       output to the string.
       
       This function makes the assumption that there is less the 1000
       characters of formatted output. The function will assert if this occurs.

       Note that this function will break the current instance from multiple
       references to the string. A new string buffer is allocated and the data
       from the old string buffer copied to it.
       
       @return
       reference to the current string object.
     */
    PString & sprintf(
      const char * cfmt,   /// C string for output format.
      ...                  /// Extra parameters for #sprintf()# call.
    );

    /**Produce formatted output as a string. This is identical to the standard
       C library #sprintf()# function, but sends its output to a
       #PString#.

       This function makes the assumption that there is less the 1000
       characters of formatted output. The function will assert if this occurs.

       Note that this function will break the current instance from multiple
       references to the string. A new string buffer is allocated and the data
       from the old string buffer copied to it.
       
       @return
       reference to the current string object.
     */
    friend PString psprintf(
      const char * cfmt,   /// C string for output format.
      ...                  /// Extra parameters for #sprintf()# call.
    );

    /** Concatenate a formatted output to the string. */
    PString & vsprintf(
      const PString & fmt, /// String for output format.
      va_list args         /// Extra parameters for #sprintf()# call.
    );
    /**Concatenate a formatted output to the string. This is identical to the
       standard C library #vsprintf()# function, but appends its
       output to the string.

       This function makes the assumption that there is less the 1000
       characters of formatted output. The function will assert if this occurs.

       Note that this function will break the current instance from multiple
       references to the string. A new string buffer is allocated and the data
       from the old string buffer copied to it.
       
       @return
       reference to the current string object.
     */
    PString & vsprintf(
      const char * cfmt,   /// C string for output format.
      va_list args         /// Extra parameters for #sprintf()# call.
    );

    /** Produce formatted output as a string. */
    friend PString pvsprintf(
      const char * cfmt,   /// C string for output format.
      va_list args         /// Extra parameters for #sprintf()# call.
    );
    /**Produce formatted output as a string. This is identical to the standard
       C library #vsprintf()# function, but sends its output to a
       #PString#.

       This function makes the assumption that there is less the 1000
       characters of formatted output. The function will assert if this occurs.

       Note that this function will break the current instance from multiple
       references to the string. A new string buffer is allocated and the data
       from the old string buffer copied to it.
       
       @return
       reference to the current string object.
     */
    friend PString pvsprintf(
      const PString & fmt, /// String for output format.
      va_list args         /// Extra parameters for #sprintf()# call.
    );


    /**Convert the string to an integer value using the specified number base.
       All characters up to the first illegal character for the number base are
       converted. Case is not significant for bases greater than 10.

       The number base may only be from 2 to 36 and the function will assert
       if it is not in this range.

       This function uses the standard C library #strtol()# function.

       @return
       integer value for the string.
     */
    long AsInteger(
      unsigned base = 10    /// Number base to convert the string in.
    ) const;
    /**Convert the string to an integer value using the specified number base.
       All characters up to the first illegal character for the number base are
       converted. Case is not significant for bases greater than 10.

       The number base may only be from 2 to 36 and the function will assert
       if it is not in this range.

       This function uses the standard C library #strtoul()# function.

       @return
       integer value for the string.
     */
    DWORD AsUnsigned(
      unsigned base = 10    /// Number base to convert the string in.
    ) const;
    /**Convert the string to an integer value using the specified number base.
       All characters up to the first illegal character for the number base are
       converted. Case is not significant for bases greater than 10.

       The number base may only be from 2 to 36 and the function will assert
       if it is not in this range.

       This function uses the standard C library #strtoq()#
       or #strtoul()# function.

       @return
       integer value for the string.
     */
    PInt64 AsInt64(
      unsigned base = 10    /// Number base to convert the string in.
    ) const;
    /**Convert the string to an integer value using the specified number base.
       All characters up to the first illegal character for the number base are
       converted. Case is not significant for bases greater than 10.

       The number base may only be from 2 to 36 and the function will assert
       if it is not in this range.

       This function uses the standard C library #strtouq()#
       or #strtoul()# function.

       @return
       integer value for the string.
     */
    PUInt64 AsUnsigned64(
      unsigned base = 10    /// Number base to convert the string in.
    ) const;

    /**Convert the string to a floating point number. This number may be in
       decimal or exponential form. All characters up to the first illegal
       character for a floting point number are converted.

       This function uses the standard C library #strtod()#
       function.

       @return
       floating point value for the string.
     */
    double AsReal() const;
     

    /**Convert a standard null terminated string to a "pascal" style string.
       This consists of a songle byte for the length of the string and then
       the string characters following it.
       
       This function will assert if the string is greater than 255 characters
       in length.

       @return
       byte array containing the "pascal" style string.
     */
    PBYTEArray ToPascal() const;

    /**Convert the string to C literal string format. This will convert non
       printable characters to the \nnn form or for standard control characters
       such as line feed, to \n form. Any '"' characters are also escaped with
       a \ character and the entire string is enclosed in '"' characters.
       
       @return
       string converted to a C language literal form.
     */
    PString ToLiteral() const;

#ifndef PHAS_UNICODE
    /**Get the internal buffer as a pointer to unsigned characters. The
       standard "operator const char *" function is provided by the
       #PCharArray# ancestor class.

       @return
       pointer to character buffer.
     */
    operator const unsigned char *() const;
#endif
  //@}


  protected:
    virtual Comparison InternalCompare(
      PINDEX offset,      // Offset into string to compare.
      char c              // Character to compare against.
    ) const;
    virtual Comparison InternalCompare(
      PINDEX offset,      // Offset into string to compare.
      PINDEX length,      // Number of characters to compare.
      const char * cstr   // C string to compare against.
    ) const;
    /* Internal function to compare the current string value against the
       specified C string.

       @return
       relative rank of the two strings.
     */

    PString(int dummy, const PString * str);
};


//////////////////////////////////////////////////////////////////////////////

/**This class is a variation of a string that ignores case. Thus in all
   standard comparison (#==#, #<# etc) and search
   (#Find()# etc) functions the case of the characters and strings is
   ignored.
   
   The characters in the string still maintain their case. Only the comparison
   operations are affected. So printing etc will still display the string as
   entered.
 */
class PCaselessString : public PString
{
  PCLASSINFO(PCaselessString, PString);

  public:
    /**Create a new, empty, caseless string.
     */
    PCaselessString();

    /**Create a new caseless string, initialising it to the characters in the
       C string provided.
     */
    PCaselessString(
      const char * cstr   /// C string to initialise the caseless string from.
    );

    /**Create a caseless string, with a reference to the characters in the
       normal #PString# provided. A PCaselessString may also be provided
       to this constructor.
     */
    PCaselessString(
      const PString & str  /// String to initialise the caseless string from.
    );


    /**Set the current instance to reference the same string as the
       #str# parameter. */
    PCaselessString & operator=(
      const PString & str  /// String to initialise the caseless string from.
    );
    /**Set the current instance to reference the same string as the
       #str# parameter. The previous reference is decremented and
       if no more references to the string are present, the string buffer is
       released. A PCaselessString may also be provided to this operator.
     */
    PCaselessString & operator=(
      const char * cstr   /// C string to initialise the caseless string from.
    );


  // Overrides from class PObject
    /**Make a complete duplicate of the string. Note that the data in the
       array of characters is duplicated as well and the new object is a
       unique reference to that data.
     */
    virtual PObject * Clone() const;

  protected:
  // Overrides from class PString
    virtual Comparison InternalCompare(
      PINDEX offset,      // Offset into string to compare.
      char c              // Character to compare against.
    ) const;
    virtual Comparison InternalCompare(
      PINDEX offset,      // Offset into string to compare.
      PINDEX length,      // Number of characters to compare.
      const char * cstr   // C string to compare against.
    ) const;
    /* Internal function to compare the current string value against the
       specified C string.

       @return
       relative rank of the two strings or characters.
     */

    PCaselessString(int dummy, const PCaselessString * str);
};


//////////////////////////////////////////////////////////////////////////////

class PStringStream;

/**This class is a standard C++ stream class descendent for reading or writing
   streamed data to or from a #PString# class.
   
   All of the standard stream I/O operators, manipulators etc will operate on
   the PStringStream class.
 */
class PStringStream : public PString, public iostream
{
  PCLASSINFO(PStringStream, PString);

  public:
    /**Create a new, empty, string stream. Data may be output to this stream,
       but attempts to input from it will return end of file.
     */
    PStringStream();

    /**Create a new string stream and initialise it to the provided value. The
       string stream references the same string buffer as the #str#
       parameter until any output to the string stream is attempted. The
       reference is then broken and the instance of the string stream becomes
       a unique reference to a string buffer.
     */
    PStringStream(
      const PString & str   /// Initial value for string stream.
    );

    /**Create a new string stream and initialise it with the provided value.
       The stream may be read or written from. Writes will append to the end of
       the string.
     */
    PStringStream(
      const char * cstr   /// Initial value for the string stream.
    );

    /**Assign the string to the current object. The current instance then
       becomes another reference to the same string in the #str#
       parameter.
       
       This will reset the read pointer for input to the beginning of the
       string. Also, any data output to the string up until the asasignement
       will be lost.

       @return
       reference to the current PStringStream object.
     */
    PStringStream & operator=(
      const PString & str  /// New string to assign.
    );

    /**Assign the C string to the string stream. The current instance then
       becomes a unique reference to a copy of the #cstr#
       parameter. The #cstr# parameter is typically a literal
       string, eg:
\begin{verbatim}
          myStr = "fred";
\end{verbatim}

       This will reset the read pointer for input to the beginning of the
       string. Also, any data output to the string up until the asasignement
       will be lost.

       @return
       reference to the current PStringStream object.
     */
    PStringStream & operator=(
      const char * cstr  /// C string to assign.
    );


    /// Destroy the string stream, deleting the stream buffer
    virtual ~PStringStream();


  private:
    PStringStream(int, const PStringStream &) { }
    PStringStream & operator=(const PStringStream &) { return *this; }

    class Buffer : public streambuf {
      public:
        Buffer(PStringStream * str);
        Buffer(const Buffer & sbuf);
        Buffer & operator=(const Buffer & sbuf);
        virtual int overflow(int=EOF);
        virtual int underflow();
        virtual int sync();
#ifdef __MWERKS__
        virtual streampos seekoff(streamoff, ios::seekdir, ios::openmode);
#else
        virtual streampos seekoff(streamoff, ios::seek_dir, int);
#endif
        PStringStream * string;
    };
};


/**This is an array collection class of #PString# objects. It has all the
   usual functions for a collection, with the object types set to
   #PString# pointers.
   
   In addition some addition functions are added that take a const
   #PString# reference instead of a pointer as most standard collection
   functions do. This is more convenient for when string expressions are used
   as parameters to function in the collection.

   See the #PAbstractArray# and #PArray# classes and
   #PDECLARE_ARRAY# macro for more information.
*/
#ifdef DOC_PLUS_PLUS
class PStringArray : public PArray {
#endif
PDECLARE_ARRAY(PStringArray, PString);

  public:
  /**@name Construction */
  //@{
    /**Create a PStringArray from the array of C strings.
     */
    PStringArray(
      PINDEX count,                 /// Count of strings in array
      char const * const * strarr,  /// Array of C strings
      BOOL caseless = FALSE         /// New strings are to be PCaselessStrings
    );
  //@}

  /**@name New functions for class */
  //@{
    /**As for #GetValuesIndex()# but takes a PString argument so that
       literals will be automatically converted.

       @return
       Index of string in array or P_MAX_INDEX if not found.
     */
    PINDEX GetStringsIndex(
      const PString & str /// String to search for index of
    ) const;

    inline PString & operator[](
      PINDEX index  // Index position in the collection of the object.
    ) const { return PStringArray_PTemplate::operator[](index); }

    /**Retrieve a reference  to the object in the array. If there was not an
       object at that ordinal position or the index was beyond the size of the
       array then the function will create a new one.

       @return
       reference to the object at #index# position.
     */
    PString & operator[](
      PINDEX index  /// Index position in the collection of the object.
    );
  //@}
};


/**This is a list collection class of #PString# objects. It has all the
   usual functions for a collection, with the object types set to
   #PString# pointers.
   
   In addition some addition functions are added that take a const
   #PString# reference instead of a pointer as most standard collection
   functions do. This is more convenient for when string expressions are used
   as parameters to function in the collection.

   See the #PAbstractList# and #PList# classes and
   #PDECLARE_LIST# macro for more information.
 */
#ifdef DOC_PLUS_PLUS
class PStringList : public PList {
#endif
PDECLARE_LIST(PStringList, PString);
  public:
  /**@name Construction */
  //@{
    /**Create a PStringArray from the array of C strings.
     */
    PStringList(
      PINDEX count,                 /// Count of strings in array
      char const * const * strarr,  /// Array of C strings
      BOOL caseless = FALSE         /// New strings are to be PCaselessStrings
    );
  //@}

  /**@name Operations */
  //@{
    /** Append a string to the list.
     */
    PINDEX AppendString(
      const PString & str /// String to append.
    );

    /** Insert a string into the list.
     */
    PINDEX InsertString(
      const PString & before,   /// String to insert before.
      const PString & str       /// String to insert.
    );

    /** Get the index of the string with the specified value.
      A linear search of list is performed to find the string value.
     */
    PINDEX GetStringsIndex(
      const PString & str   /// String value to search for.
    ) const;
  //@}
};


/**This is a sorted list collection class of #PString# objects. It has all
   the usual functions for a collection, with the object types set to
   #PString# pointers.
   
   In addition some addition functions are added that take a const
   #PString# reference instead of a pointer as most standard collection
   functions do. This is more convenient for when string expressions are used
   as parameters to function in the collection.

   See the #PAbstractSortedList# and #PSortedList# classes and
   #PDECLARE_SORTEDLIST# macro for more information.
 */
#ifdef DOC_PLUS_PLUS
class PSortedStringList : public PSortedList {
#endif
PDECLARE_SORTED_LIST(PSortedStringList, PString);
  public:
  /**@name Construction */
  //@{
    /**Create a PStringArray from the array of C strings.
     */
    PSortedStringList(
      PINDEX count,                 /// Count of strings in array
      char const * const * strarr,  /// Array of C strings
      BOOL caseless = FALSE         /// New strings are to be PCaselessStrings
    );
  //@}

  /**@name Operations */
  //@{
    /** Add a string to the list.
        This will place the string in the correct position in the sorted list.
     */
    PINDEX AppendString(
      const PString & str /// String to append.
    );

    /** Get the index of the string with the specified value.
      A binary search of tree is performed to find the string value.
     */
    PINDEX GetStringsIndex(
      const PString & str   /// String value to search for.
    ) const;
  //@}
};


/**This is a set collection class of #PString# objects. It has all the
   usual functions for a collection, with the object types set to
   #PString# pointers.

   In addition some addition functions are added that take a const
   #PString# reference instead of a pointer as most standard collection
   functions do. This is more convenient for when string expressions are used
   as parameters to function in the collection.

   Unlike the normal sets, this will delete the PStrings removed from it. This
   complements the automatic creation of new PString objects when literals or
   expressions are used.

   See the #PAbstractSet# and #PSet# classes and #PDECLARE_SET#
   macro for more information.
 */
#ifdef DOC_PLUS_PLUS
class PStringSet : public PSet {
#endif
PDECLARE_SET(PStringSet, PString, TRUE);
  public:
  /**@name Construction */
  //@{
    /**Create a PStringArray from the array of C strings.
     */
    PStringSet(
      PINDEX count,                 /// Count of strings in array
      char const * const * strarr,  /// Array of C strings
      BOOL caseless = FALSE         /// New strings are to be PCaselessStrings
    );
  //@}

  /**@name Operations */
  //@{
    /** Include the spcified string value into the set. */
    void Include(
      const PString & key /// String value to add to set.
    );
    /** Include the spcified string value into the set. */
    PStringSet & operator+=(
      const PString & key /// String value to add to set.
    );
    /** Exclude the spcified string value from the set. */
    void Exclude(
      const PString & key /// String value to remove from set.
    );
    /** Exclude the spcified string value from the set. */
    PStringSet & operator-=(
      const PString & key /// String value to remove from set.
    );
  //@}
};


#ifdef PHAS_TEMPLATES

/**This template class maps the PAbstractDictionary to a specific key type and
   a #PString# data type. The functions in this class primarily do all the
   appropriate casting of types.

   Note that if templates are not used the #PDECLARE_STRING_DICTIONARY#
   macro will simulate the template instantiation.
 */
template <class K> class PStringDictionary : public PAbstractDictionary
{
  PCLASSINFO(PStringDictionary, PAbstractDictionary);

  public:
  /**@name Construction */
  //@{
    /**Create a new, empty, dictionary.

       Note that by default, objects placed into the dictionary will be
       deleted when removed or when all references to the dictionary are
       destroyed.
     */
    PStringDictionary()
      : PAbstractDictionary() { }
  //@}

  /**@name Overrides from class PObject */
  //@{
    /**Make a complete duplicate of the dictionary. Note that all objects in
       the array are also cloned, so this will make a complete copy of the
       dictionary.
     */
    virtual PObject * Clone() const
      { return PNEW PStringDictionary(0, this); }
  //@}

  /**@name New functions for class */
  //@{
    /**Get the string contained in the dictionary at the #key#
       position. The hash table is used to locate the data quickly via the
       hash function provided by the key.

       The last key/data pair is remembered by the class so that subseqent
       access is very fast.

       This function asserts if there is no data at the key position.

       @return
       reference to the object indexed by the key.
     */
    const PString & operator[](const K & key) const
      { return (const PString &)GetRefAt(key); }

    /**Get the string contained in the dictionary at the #key#
       position. The hash table is used to locate the data quickly via the
       hash function provided by the key.

       The last key/data pair is remembered by the class so that subseqent
       access is very fast.

       This function returns the #dflt# value if there is no data
       at the key position.

       @return
       reference to the object indexed by the key.
     */
    PString operator()(const K & key, const char * dflt = "") const
      { if (AbstractContains(key)) return (*this)[key]; return dflt; }

    /**Determine if the value of the object is contained in the hash table. The
       object values are compared, not the pointers.  So the objects in the
       collection must correctly implement the #PObject::Compare()#
       function. The hash table is used to locate the entry.

       @return
       TRUE if the object value is in the dictionary.
     */
    BOOL Contains(
      const K & key   // Key to look for in the dictionary.
      ) const { return AbstractContains(key); }

    /**Remove an object at the specified key. The returned pointer is then
       removed using the #SetAt()# function to set that key value to
       NULL. If the #AllowDeleteObjects# option is set then the
       object is also deleted.

       @return
       pointer to the object being removed, or NULL if it was deleted.
     */
    virtual PString * RemoveAt(
      const K & key   // Key for position in dictionary to get object.
    ) { PString * s = GetAt(key); AbstractSetAt(key, (PObject*) NULL); return s; }

    /**Get the object at the specified key position. If the key was not in the
       collection then NULL is returned.

       @return
       pointer to object at the specified key.
     */
    virtual PString * GetAt(
      const K & key   // Key for position in dictionary to get object.
    ) const { return (PString *)AbstractGetAt(key); }

    /**Set the data at the specified ordinal index position in the dictionary.

       The ordinal position in the dictionary is determined by the hash values
       of the keys and the order of insertion.

       @return
       TRUE if the new object could be placed into the dictionary.
     */
    virtual BOOL SetDataAt(
      PINDEX index,        // Ordinal index in the dictionary.
      const PString & str  // New string value to put into the dictionary.
    ) { return PAbstractDictionary::SetDataAt(index, PNEW PString(str)); }

    /**Add a new object to the collection. If the objects value is already in
       the dictionary then the object is overrides the previous value. If the
       AllowDeleteObjects option is set then the old object is also deleted.

       The object is placed in the an ordinal position dependent on the keys
       hash function. Subsequent searches use the has function to speed access
       to the data item.

       @return
       TRUE if the object was successfully added.
     */
    virtual BOOL SetAt(
      const K & key,       // Key for position in dictionary to add object.
      const PString & str  // New string value to put into the dictionary.
    ) { return AbstractSetAt(key, PNEW PString(str)); }

    /**Get the key in the dictionary at the ordinal index position.
    
       The ordinal position in the dictionary is determined by the hash values
       of the keys and the order of insertion.

       The last key/data pair is remembered by the class so that subseqent
       access is very fast.

       @return
       reference to key at the index position.
     */
    const K & GetKeyAt(PINDEX index) const
      { return (const K &)AbstractGetKeyAt(index); }

    /**Get the data in the dictionary at the ordinal index position.
    
       The ordinal position in the dictionary is determined by the hash values
       of the keys and the order of insertion.

       The last key/data pair is remembered by the class so that subseqent
       access is very fast.

       @return
       reference to data at the index position.
     */
    PString & GetDataAt(PINDEX index) const
      { return (PString &)AbstractGetDataAt(index); }
  //@}

  protected:
    PStringDictionary(int dummy, const PStringDictionary * c)
      : PAbstractDictionary(dummy, c) { }
};


/**Begin declaration of a dictionary of strings class.
   This macro is used to declare a descendent of PAbstractList class,
   customised for a particular key type {\bf K} and data object type
   #PString#.

   If the compilation is using templates then this macro produces a descendent
   of the #PStringDictionary# template class. If templates are not being
   used then the macro defines a set of inline functions to do all casting of
   types. The resultant classes have an identical set of functions in either
   case.

   See the #PStringDictionary# and #PAbstractDictionary# classes for
   more information.
 */
#define PDECLARE_STRING_DICTIONARY(cls, K) \
  PDECLARE_CLASS(cls, PStringDictionary<K>) \
  protected: \
    cls(int dummy, const cls * c) \
      : PStringDictionary<K>(dummy, c) { } \
  public: \
    cls() \
      : PStringDictionary<K>() { } \
    virtual PObject * Clone() const \
      { return PNEW cls(0, this); } \


/**Declare a dictionary of strings class.
   This macro is used to declare a descendent of PAbstractDictionary class,
   customised for a particular key type {\bf K} and data object type
   #PString#. This macro closes the class declaration off so no additional
   members can be added.

   If the compilation is using templates then this macro produces a typedef
   of the #PStringDictionary# template class.

   See the #PStringDictionary# class and #PDECLARE_STRING_DICTIONARY#
   macro for more information.
 */
#define PSTRING_DICTIONARY(cls, K) typedef PStringDictionary<K> cls


#else // PHAS_TEMPLATES


#define PSTRING_DICTIONARY(cls, K) \
  class cls : public PAbstractDictionary { \
  PCLASSINFO(cls, PAbstractDictionary) \
  protected: \
    inline cls(int dummy, const cls * c) \
      : PAbstractDictionary(dummy, c) { } \
  public: \
    inline cls() \
      : PAbstractDictionary() { } \
    inline virtual PObject * Clone() const \
      { return PNEW cls(0, this); } \
    inline PString & operator[](const K & key) const \
      { return (PString &)GetRefAt(key); } \
    inline PString operator()(const K & key, const char * dflt = "") const \
      { if (Contains(key)) return (PString &)GetRefAt(key); return dflt; } \
    virtual BOOL Contains(const K & key) const \
      { return AbstractContains(key); } \
    virtual PString * RemoveAt(const K & key) \
      { PString * s = GetAt(key); AbstractSetAt(key, NULL); return s; } \
    inline virtual PString * GetAt(const K & key) const \
      { return (PString *)AbstractGetAt(key); } \
    inline virtual BOOL SetDataAt(PINDEX index, const PString & str) \
      { return PAbstractDictionary::SetDataAt(index,PNEW PString(str));} \
    inline virtual BOOL SetAt(const K & key, const PString & str) \
      { return AbstractSetAt(key, PNEW PString(str)); } \
    inline const K & GetKeyAt(PINDEX index) const \
      { return (const K &)AbstractGetKeyAt(index); } \
    inline PString & GetDataAt(PINDEX index) const \
      { return (PString &)AbstractGetDataAt(index); } \
  }

#define PDECLARE_STRING_DICTIONARY(cls, K) \
  PSTRING_DICTIONARY(cls##_PTemplate, K); \
  PDECLARE_CLASS(cls, cls##_PTemplate) \
  protected: \
    cls(int dummy, const cls * c) \
      : cls##_PTemplate(dummy, c) { } \
  public: \
    cls() \
      : cls##_PTemplate() { } \
    virtual PObject * Clone() const \
      { return PNEW cls(0, this); } \

#endif // PHAS_TEMPLATES


/**This is a dictionary collection class of #PString# objects, keyed by an
   ordinal value. It has all the usual functions for a collection, with the
   object types set to #PString# pointers. The class could be considered
   like a sparse array of strings.

   In addition some addition functions are added that take a const
   #PString# reference instead of a pointer as most standard collection
   functions do. This is more convenient for when string expressions are used
   as parameters to function in the collection.

   See the #PAbstractDictionary# and #PStringDictionary# classes and
   #PDECLARE_DICTIONARY# and #PDECLARE_STRING_DICTIONARY# macros for
   more information.
 */
#ifdef DOC_PLUS_PLUS
class POrdinalToString : public PStringDictionary {
#endif
PDECLARE_STRING_DICTIONARY(POrdinalToString, POrdinalKey);
  public:
    /// Structure for static array initialiser for class.
    struct Initialiser {
      /// Ordinal key for string.
      PINDEX key;
      /// String value for ordinal.
      const char * value;
    };
    /** Initialise the ordinal dictionary of strings from the static array.
     */
    POrdinalToString(
      PINDEX count,                /// Count of strings in initialiser array
      const Initialiser * init     /// Array of Initialiser structures
    );
};

/**This is a dictionary collection class of ordinals keyed by
   #PString# objects. It has all the usual functions for a collection,
   with the object types set to #POrdinalKey# pointers.

   In addition some addition functions are added that take a const
   #POrdinalKey# reference or a simple #PINDEX# instead of a pointer
   as most standard collection functions do. This is more convenient for when
   integer expressions are used as parameters to function in the collection.

   See the #PAbstractDicionary# and #POrdinalDictionary# classes and
   #PDECLARE_ORDINAL_DICTIONARY# macro for more information.
 */
#ifdef DOC_PLUS_PLUS
class PStringToOrdinal : public POrdinalDictionary {
#endif
PDECLARE_ORDINAL_DICTIONARY(PStringToOrdinal, PString);
  public:
    /// Structure for static array initialiser for class.
    struct Initialiser {
      /// String key for ordinal.
      const char * key;
      /// Ordinal value for string.
      PINDEX value;
    };
    /** Initialise the string dictionary of ordinals from the static array.
     */
    PStringToOrdinal(
      PINDEX count,                /// Count of strings in initialiser array
      const Initialiser * init,    /// Array of Initialiser structures
      BOOL caseless = FALSE        /// New keys are to be PCaselessStrings
    );
};


/**This is a dictionary collection class of #PString# objects, keyed by
   another string. It has all the usual functions for a collection, with the
   object types set to #PString# pointers.

   In addition some addition functions are added that take a const
   #PString# reference instead of a pointer as most standard collection
   functions do. This is more convenient for when string expressions are used
   as parameters to function in the collection.

   See the #PAbstractDictionary# and #PStringDictionary# classes and
   #PDECLARE_DICTIONARY# and #PDECLARE_STRING_DICTIONARY# macros for
   more information.
 */
#ifdef DOC_PLUS_PLUS
class PStringToString : public PStringDictionary {
#endif
PDECLARE_STRING_DICTIONARY(PStringToString, PString);
  public:
    /// Structure for static array initialiser for class.
    struct Initialiser {
      /// String key for string.
      const char * key;
      /// String value for string.
      const char * value;
    };
    /** Initialise the string dictionary of strings from the static array.
     */
    PStringToString(
      PINDEX count,                /// Count of strings in initialiser array
      const Initialiser * init,    /// Array of Initialiser structures
      BOOL caselessKeys = FALSE,   /// New keys are to be PCaselessStrings
      BOOL caselessValues = FALSE  /// New values are to be PCaselessStrings
    );
};


// End Of File ///////////////////////////////////////////////////////////////
