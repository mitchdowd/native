#ifndef _NATIVE_STRING_H_
#define _NATIVE_STRING_H_ 1

// Module Dependencies
#include "array.h"
#include "convert.h"
#include "hash.h"

namespace native
{
	/**
		A Unicode String class.
	 */
	class String
	{
	public:
		/** 
			Used as a length value to denote a null-terminated string array. 
		 */
		static const size_t NULL_TERMINATED = size_t(-1);

		/** The empty string. */
		static const String empty;

		/** 
			Creates an empty String. 
		 */
		String() noexcept : _length(0) {}

		/**
			Copies a String.
			\param other The String to copy.
		 */
		String(const String& other) = default;

		/**
			Standard move constructor. Moves the String contents from another String.
			\param other The String to move the contents from.
		 */
		String(String&& other) noexcept;

		/**
			Creates a String containing the specified text.
			\param text The native character array.
			\param length The length of the text.
		 */
		String(const wchar_t* text, size_t length = NULL_TERMINATED);

		/**
			Creates a String from the given UTF-8 text.
			\param utf8 The UTF-8 encoded text.
			\param length The number of bytes, or NULL_TERMINATED.
		 */
		String(const char* utf8, size_t length = NULL_TERMINATED);

		/**
			Creates a String from the given UTF-16 text.
		 	\param utf16 The UTF-16 encoded text.
		 	\param length The number of bytes, or NULL_TERMINATED.
		 */
		String(const char16_t* utf16, size_t length = NULL_TERMINATED);

		/**
			Creates a String from the given UTF-32 text.
			 \param utf32 The UTF-32 encoded text.
			 \param length The number of bytes, or NULL_TERMINATED.
		 */
		String(const char32_t* utf32, size_t length = NULL_TERMINATED);

		/**
			Creates a String from a single character.
			\param ch The character.
		 */
		String(wchar_t ch);
		String(char ch);

		/**
			Creates a String from the given Array of text.
			\param text The Array of characters.
			\param length The number of characters.
		 */
		String(const Array<wchar_t>& text, size_t length = NULL_TERMINATED);

		/** Destructor. */
		~String() = default;

		/**
			Discards the previous String text and copies another String.
			\param other The String to copy.
			\return Reference to this String.
		 */
		String& operator=(const String& other) = default;

		/**
			Assigns the contents of the given text to this String.
			\param other The text to assign.
			\return Reference to this String.
		 */
		String& operator=(const wchar_t* other);

		/**
			The current length of the String.
			\return The String's length (in characters).
		 */
		size_t getLength() const noexcept { return _length; }

		/**
			Returns the length of a null-terminated character array.
			\param str The string to get the length of.
			\return The number of characters in the string (not counting the null).
		 */
		static size_t lengthOf(const wchar_t* str);

		/**
			Gets a pointer to the internal C-style string array. If it is not
			nullptr, then it will be null-terminated.
			\return The C-string data.
		 */
		const wchar_t* toArray() const noexcept { return _array.toArray(); }
		operator const wchar_t*() const noexcept { return toArray(); }

		/**
			Compares this String with the given text. A negative result means this
			String comes lexically before the compared text; positive means it comes
			after, and zero means they are equal. Comparison is case sensitive.
			\param text The text to compare with.
			\param length The length of the compared text.
			\return Result of the comparison.
		 */
		int compare(const wchar_t* text, size_t length = NULL_TERMINATED) const;

		/**
			Compares this String with the given String. A negative result means this
			String comes lexically before the other String; positive means it comes
			after, and zero means they are equal. Comparison is case sensitive.
			\param str The String to compare with.
			\return Result of the comparison.
		 */
		int compare(const String& str) const;

		/**
			Appends the given text to the end of this String.
			\param text The text to append.
			\param length The length of the text to append.
		 */
		void append(const wchar_t* text, size_t length = NULL_TERMINATED);

		/**
			Appends the given String to the end of this String.
			\param str The String to append.
		 */
		void append(const String& str);

		/**
			Appends the given character to the end of the String.
			\param ch The character to append.
		 */
		void append(wchar_t ch) { append(&ch, 1); }

		/**
			Appends the given text to the end of this String.
			\param text The text to append.
			\return This String.
		 */
		String& operator+=(const wchar_t* text);

		/**
			Appends the given String to the end of this String.
			\param str The String to append.
			\return This String.
		 */
		String& operator+=(const String& str);

		/**
			Appends the given character to the end of the String.
			\param ch The character to append.
			\return This String.
		 */
		String& operator+=(wchar_t ch);

		/**
			Gets the character at the given index.
			\param index The index of the character.
			\return The character at that index.
		 */
		wchar_t atIndex(size_t index)    const { return _array[index]; }
		wchar_t operator[](size_t index) const { return atIndex(index); }
		wchar_t operator[](int index)    const { return atIndex(index); }

		/**
			Searches the String for the first occurence of the given null-terminated
			substring of characters.
			\param substr The substring to search for.
			\param startIndex The position in the String to start searching from.
			\return The index of the start of the substring, or -1 if not found.
		 */
		ptrint_t indexOf(const wchar_t* substr, size_t startIndex = 0) const;

		/**
			Returns the last index of the given substring, searching from the end
			to the beginning of the String.
			\param substr The sub-string to search for.
			\return The index of the start of the substring, or -1 if not found.
		 */
		ptrint_t lastIndexOf(const wchar_t* substr) const;

		/**
			Searches the String for the first occurence of any of the characters
			in the given null-terminated string.
			\param chars The characters to search for.
			\param startIndex the index to start searching from.
			\return The index of the first occurence, or -1 if not found.
		 */
		ptrint_t indexOfAny(const wchar_t* chars, size_t startIndex = 0) const;

		/**
			Gets the last index of any of the specified characters.
			\param chars A null-terminated array of characters to search for.
			\return The index of the last occurence, or -1 if not found.
		 */
		ptrint_t lastIndexOfAny(const wchar_t* chars) const;

		/**
			Determines whether this String contains another given string.
			\param substr The string to search for.
			\return `true` if the supplied text is a substring, false otherwise.
		 */
		bool contains(const String& substr) const { return contains(substr.toArray()); }
		bool contains(const wchar_t* substr) const;

		/**
			Tells whether this String starts with the given substring.
			\param substr The substring to search for.
			\return `true` if the substring is equal to the start character, `false` otherwise.
		 */
		bool startsWith(const String& substr) const { return startsWith(substr.toArray()); }
		bool startsWith(wchar_t substr) const;
		bool startsWith(const wchar_t* substr) const;

		/**
			Tells whether this String ends with the given substring.
			\param substr The substring to search for.
			\return `true` if the substring is equal to the final character, `false` otherwise.
		 */
		bool endsWith(const String& substr) const;
		bool endsWith(wchar_t substr) const;
		bool endsWith(const wchar_t* substr) const { return endsWith(String(substr)); }

		/**
			Retrieves a substring of characters from this String.
			\param start The start index.
			\param length The length of the substring.
			\return The substring.
		 */
		String substring(size_t start, size_t length) const;

		/** Empties the String. */
		void clear();

		/**
			Returns a copy of the String with everything converted to upper case.
			\return An upper case copy of the String.
		 */
		String toUpper() const;

		/**
			Creates a new String with all instances of the old part replaced by the new part.
			\param oldPart The part to remove.
			\param newPart The part to insert instead.
			\return A new String.
		 */
		String replace(const wchar_t* oldPart, const wchar_t* newPart) const;

		/**
			Creates a new String where all instances of all characters supplied in the
			null-terminated array are replaced with the substitute character.
			\param chars Array of characters to replace.
			\param substitute The substitution.
			\return New String.
		 */
		String replaceAny(const wchar_t* chars, wchar_t substitute) const;

		/**
			Encodes the String using the codec registered with the given name.
			\param codecName The registered codec name.
			\return An Array of encoded bytes of text.
		 */
		ByteArray toBytes(const String& codecName) const;

		/**
			Creates a String from an array of bytes.
			\param codecName the name of the StringCodec that identifies the data.
			\param data The data to decode.
			\param bytes The number of bytes to decode.
		 */
		static String fromBytes(const String& codecName, const byte_t* data, size_t bytes);

		/**
			Convenience function to get a UTF-8 encoded byte array of this String.
			\return The String, as UTF-8 data.
		 */
		ByteArray toUtf8() const;

		/**
			Convenience function to create a String from a UTF-8 byte array.
			\param data The UTF-8 data.
			\param bytes The number of bytes in the UTF-8 string.
			\return The created String.
		 */
		static String fromUtf8(const void* data, size_t bytes = NULL_TERMINATED);

		/**
			Produces a formatted String based upon a set of input arguments,
			substituted into a format definition. The format substitutions
			are zero-based parameter indexes inside braces (e.g. {0}).
		
			Additional formatting information can be given for each paramter
			by specifying a colon, followed by a printf() style format modifier.
		
			For example:
		
			String::format(L"{0:.3}", 3.14159) gives the String "3.142".
		
			\param format Text denoting the format.
			\param args Arguments to substitute into the format.
			\return The resulting String.
		 */
		template <class... TArgs>
		static String format(const wchar_t* format, TArgs... args);

	private:
		// Instance Variables
		Array<wchar_t> _array;
		size_t        _length;
	};

	/**
		Overloadable function which converts a value to a String. The optional
		`format` parameter is extra formatting in the printf() style.
		\param value The value to convert to a String.
		\param format An optional format parameter to define how to format the value.
		\return A String equivalent of `value`.
	 */
	String toString(const String&  value, const wchar_t* format = nullptr);
	String toString(const wchar_t* value, const wchar_t* format = nullptr);
	String toString(int32_t value, const wchar_t* format = nullptr);
	String toString(int64_t value, const wchar_t* format = nullptr);
	String toString(uint32_t value, const wchar_t* format = nullptr);
	String toString(uint64_t value, const wchar_t* format = nullptr);
	String toString(float value, const wchar_t* format = nullptr);
	String toString(double value, const wchar_t* format = nullptr);

	/**
		Gets a hash code for the given String.
		\param str The String to get the hash code for.
		\return The hash code.
	 */
	inline uptrint_t hash(const String& str) { return hash(str.toArray(), str.getLength() * sizeof(wchar_t)); }

	/**
		Compares two strings for equality. Case sensitive.
		\param lhs The first string to compare.
		\param rhs The second string to compare.
		\return true if equal, false if different.
	 */
	inline bool operator==(const String& lhs, const String& rhs) { return lhs.compare(rhs) == 0; }
	inline bool operator==(const String& lhs, const wchar_t* rhs) { return lhs.compare(rhs) == 0; }
	inline bool operator==(const wchar_t* lhs, const String& rhs) { return rhs.compare(lhs) == 0; }

	/**
		Compares two strings for inequality. Case sensitive.
		\param lhs The first string to compare.
		\param rhs The second string to compare.
		\return true if different, false if equal.
	 */
	inline bool operator!=(const String& lhs, const String& rhs) { return lhs.compare(rhs) != 0; }
	inline bool operator!=(const String& lhs, const wchar_t* rhs) { return lhs.compare(rhs) != 0; }
	inline bool operator!=(const wchar_t* lhs, const String& rhs) { return rhs.compare(lhs) != 0; }

	/**
		Concatenates the supplied string values into a single String.
		\param lhs The first string value.
		\param rhs The second string value.
		\return The resulting concatenation.
	 */
	inline String operator+(const String& lhs, const String& rhs) { String str(lhs); return str += rhs; }
	inline String operator+(const wchar_t* lhs, const String& rhs) { String str(lhs); return str += rhs; }
	inline String operator+(const String& lhs, const wchar_t* rhs) { String str(lhs); return str += rhs; }

	// ---------------------------------------------------------------------- //
	//                      String::format Implementation                     //
	// ---------------------------------------------------------------------- //

	namespace internal
	{
		/** Raises a FormatException. */
		void raiseFormatException(const wchar_t* message = L"Invalid input format");

		inline String getFormattedArgument(size_t index, const wchar_t* argFormat)
		{
			raiseFormatException(L"Invalid argument index supplied.");

			// We don't ever reach here. It's to stop compiler warnings.
			return String();
		}

		/** Gets the formatted String output of the specified argument index. */
		template <class TNext, class... TArgs>
		String getFormattedArgument(size_t index, const wchar_t* argFormat, const TNext& next, TArgs... args)
		{
			if (index == 0)
				return toString(next, argFormat);

			return getFormattedArgument(index - 1, argFormat, args...);
		}
	}

	template <class... TArgs>
	String String::format(const wchar_t* format, TArgs... args)
	{
		String output, argFormat, argNumber;

		// Current state of the format parser.
		enum { Normal, ArgNumber, ArgFormat } state = Normal;

		if (!format)
			internal::raiseInvalidArgumentException();

		// Parse the format parameter.
		while (*format)
		{
			wchar_t ch = *format++;

			switch (ch)
			{
			case L'{':
				if (state == Normal) {
					if (*format == L'{')
						output += *format++;
					else
						state = ArgNumber;
				}
				else {
					internal::raiseFormatException();
				}
				break;

			case L'}':
				if (state == Normal) {
					if (*format == L'}')
						format++;

					output += ch;
				}
				else if (state == ArgNumber || state == ArgFormat) {
					// Get the formatted output of the specified argument.
					int num = Convert::toInt(argNumber);
					output += internal::getFormattedArgument(num, argFormat.toArray(), args...);

					// Back to normal processing.
					argFormat.clear();
					argNumber.clear();
					state = Normal;
				}
				else {
					internal::raiseFormatException();
				}
				break;

			case L'0': case L'1':
			case L'2': case L'3':
			case L'4': case L'5':
			case L'6': case L'7':
			case L'8': case L'9':
				if (state == Normal)
					output += ch;
				else if (state == ArgNumber)
					argNumber += ch;
				else if (state == ArgFormat)
					argFormat += ch;
				break;

			case L':':
				if (state == Normal) {
					output += ch;
				}
				else if (state == ArgNumber) {
					if (argNumber.getLength() == 0)
						internal::raiseFormatException(L"A number must be specified");

					state = ArgFormat;
				}
				else if (state == ArgFormat) {
					argFormat += ch;
				}
				break;

			default:
				if (state == Normal)
					output += ch;
				else if (state == ArgFormat)
					argFormat += ch;
				else
					internal::raiseFormatException();
				break;
			}
		}

		return output;
	}
}

#endif // _NATIVE_STRING_H_
