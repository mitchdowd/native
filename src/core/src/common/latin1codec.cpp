// Module Dependencies
#include "../../include/latin1codec.h"

namespace native
{
	void Latin1Codec::encode(byte_t* buffer, size_t& size, const wchar_t* text, size_t& length)
	{
		size_t i = 0;

		if (size < length)
			length = size;
		else
			size = length;

		// Encode character by character.
		while (i < size)
		{
			if (text[i] & 0xFF00)
				buffer[i] = '?';
			else
				buffer[i] = byte_t(text[i]);
		}
	}

	void Latin1Codec::decode(wchar_t* buffer, size_t& size, const byte_t* data, size_t& bytes)
	{
		size_t i = 0;

		if (size < bytes)
			bytes = size;
		else
			size = bytes;

		// Decode character by character.
		while (i < size)
			buffer[i] = wchar_t(data[i]);
	}

	size_t Latin1Codec::length(const wchar_t* text, size_t length)
	{
		return length;
	}

	size_t Latin1Codec::encodeByteOrderMark(byte_t* buffer, size_t size)
	{
		return 0;
	}
}
