// Module Dependencies
#include "../include/asciicodec.h"

namespace native
{
	void AsciiCodec::encode(byte_t* buffer, size_t& size, const wchar_t* text, size_t& length)
	{
		if (size < length)
			length = size;
		else
			size = length;

		// Encode character by character.
		for (size_t i = 0; i < size; ++i)
		{
			if (text[i] & 0xFF80)
				buffer[i] = '?';
			else
				buffer[i] = byte_t(text[i]);
		}
	}

	void AsciiCodec::decode(wchar_t* buffer, size_t& size, const byte_t* data, size_t& bytes)
	{
		size_t i = 0;

		if (size < bytes)
			bytes = size;
		else
			size = bytes;

		// Decode character by character.
		for (size_t i = 0; i < size; ++i)
		{
			if (data[i] & 0x80)
				buffer[i] = L'?';
			else
				buffer[i] = wchar_t(data[i]);
		}
	}

	size_t AsciiCodec::length(const wchar_t* text, size_t length)
	{
		return length;
	}

	size_t AsciiCodec::encodeByteOrderMark(byte_t* buffer, size_t size)
	{
		return 0;
	}
}
