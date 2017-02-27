// Module Dependencies
#include "../include/utf8codec.h"

namespace native
{
	static const uint32_t offsets[6] = {
		0x00000000UL, 0x00003080UL, 0x000E2080UL,
		0x03C82080UL, 0xFA082080UL, 0x82082080UL
	};

	static const char trailingBytes[256] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
	};

	void Utf8Codec::encode(byte_t* buffer, size_t& size, const wchar_t* text, size_t& length)
	{
		size_t b = 0, c = 0;
		uint32_t ch;
		byte_t defaultChar = '?';

		// Encode one character at a time.
		while (c < length)
		{
			ch = text[c];

#ifdef NATIVE_PLATFORM_WIN32

			// Check for a two-segment character.
			if (ch >= wchar_t(0xD800) && ch <= wchar_t(0xDBFF)) {
				if (c + 1 >= length)
					break;

				// Create a single, 32-bit character.
				ch = (ch - wchar_t(0xD800)) << 10;
				ch += text[c++] - wchar_t(0xDC00 + 0x10000);
			}

#endif // NATIVE_PLATFORM_WIN32

			if (ch < 0x80) {
				if (b >= size)
					break;

				// One byte character.
				buffer[b++] = byte_t(ch);
			}
			else if (ch < 0x800) {
				if (b + 1 >= size)
					break;

				// Two byte character.
				buffer[b++] = byte_t(ch >> 6) | 0xC0;
				buffer[b++] = (ch & 0x3F) | 0x80;
			}
			else if (ch < 0x10000) {
				if (b + 2 >= size)
					break;

				// Three byte character.
				buffer[b++] = byte_t(ch >> 12) | 0xE0;
				buffer[b++] = ((ch >> 6) & 0x3F) | 0x80;
				buffer[b++] = (ch & 0x3F) | 0x80;
			}
			else if (ch < 0x110000) {
				if (b + 3 >= size)
					break;

				// Four byte character.
				buffer[b++] = byte_t(ch >> 18) | 0xF0;
				buffer[b++] = ((ch >> 12) & 0x3F) | 0x80;
				buffer[b++] = ((ch >> 6) & 0x3F) | 0x80;
				buffer[b++] = (ch & 0x3F) | 0x80;
			}
			else {
				if (defaultChar == '\0')
					break;

				// Invalid character.
				buffer[b++] = defaultChar;
			}

			c++;
		}

		// Report the results.
		size = b;
		length = c;
	}

	void Utf8Codec::decode(wchar_t* buffer, size_t& size, const byte_t* data, size_t& bytes)
	{
		size_t b = 0, c = 0;
		uint32_t ch;
		wchar_t defaultChar = L'?';
		int extra;

		while (c < size)
		{
			extra = trailingBytes[data[b]];

			// Check we have enough data and space.
			if (b + extra >= bytes || (extra > 2 && c + 1 >= size))
				break;

			// Decode into a single, 32-bit character.
			ch = 0;
			switch (extra)
			{
			case 5: ch += data[b++]; ch <<= 6;
			case 4: ch += data[b++]; ch <<= 6;
			case 3: ch += data[b++]; ch <<= 6;
			case 2: ch += data[b++]; ch <<= 6;
			case 1: ch += data[b++]; ch <<= 6;
			case 0: ch += data[b++];
			}
			ch -= offsets[extra];

			// Check for invalid Unicode values (UTF-16 surrogates, out of range characters).
			if (ch >= uint32_t(0x0010FFFF) || (ch >= wchar_t(0xD800) && ch <= wchar_t(0xDFFF))) {
				if (defaultChar == L'\0')
					break;

				ch = defaultChar;
			}

#ifdef NATIVE_PLATFORM_WIN32

			// Check for multi-byte UTF-16 character.
			if (ch > wchar_t(0xFFFF)) {
				ch -= uint32_t(0x10000);

				// Add the first of the two-segment character.
				buffer[c++] = wchar_t(0xD800 + (ch >> 10));
				ch = wchar_t(0xDC00) + (ch & 0x03FF);
			}

#endif // NATIVE_PLATFORM_WIN32

			// Write the next character.
			buffer[c++] = wchar_t(ch);
		}

		// Report the results.
		size = c;
		bytes = b;
	}

	size_t Utf8Codec::length(const wchar_t* text, size_t length)
	{
		size_t b = 0, c = 0;
		uint32_t ch;

		while (c < length)
		{
			ch = text[c];

#ifdef NATIVE_PLATFORM_WIN32

			// Check for a two-segment character.
			if (ch >= wchar_t(0xD800) && ch <= wchar_t(0xDBFF)) {
				if (c + 1 >= length)
					break;

				c++;
			}

#endif // NATIVE_PLATFORM_WIN32

			if (ch < 0x80)
				b++;
			else if (ch < 0x800)
				b += 2;
			else if (ch < 0x10000)
				b += 3;
			else if (ch < 0x110000)
				b += 4;
			else
				b++;

			c++;
		}

		// Return the number of bytes required.
		return b;
	}

	size_t Utf8Codec::encodeByteOrderMark(byte_t* buffer, size_t size)
	{
		if (size < 3)
			throw CodecException();

		// Set the byte order mark.
		buffer[0] = 0xEF;
		buffer[1] = 0xBB;
		buffer[2] = 0xBF;
		return 3;
	}
}
