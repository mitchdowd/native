#ifndef _NATIVE_LATIN_1_CODEC_H_
#define _NATIVE_LATIN_1_CODEC_H_ 1

// Module Dependencies
#include "stringcodec.h"

namespace native
{
	/**
		Latin1Codec is the StringCodec that performs conversions between Strings
		and 8-bit, Latin-1 ANSI characters.
	 */
	class Latin1Codec : public StringCodec
	{
	public:
		/**
			Creates a Latin1Codec. It generally makes more sense to use StringCodec::byName()
			to save re-creating and managing another instance of Latin1Codec.
		 */
		Latin1Codec() : StringCodec(L"Latin-1") {}

		/**
			Encodes the text using the Latin-1 codec.
			\param buffer The location to store the encoded bytes.
			\param size Size of the buffer. Returns number of bytes encoded.
			\param text The text to encode.
			\param length Number of character to encode. Returns number of characters encoded.
		 */
		void encode(byte_t* buffer, size_t& size, const wchar_t* text, size_t& length) override;

		/**
			Decodes the Latin-1 data into text.
			\param buffer Location to store decoded characters.
			\param size Size of the buffer. Returns number of characters decoded.
			\param data The data to decode.
			\param bytes Number of bytes to decode. Returns bytes deocded.
		 */
		void decode(wchar_t* buffer, size_t& size, const byte_t* data, size_t& bytes) override;

		/**
			Returns the required number of bytes to represent the given string in
			the Latin-1 codec.
			\param text The string to measure.
			\param length The number of characters to measure.
			\return The number of bytes required.
		 */
		size_t length(const wchar_t* text, size_t length) override;

		/**
			Writes the Latin-1 byte order mark to the buffer. This is a three
			byte mark.
			\param buffer The buffer to write to.
			\param size The size of the buffer.
			\return The number of bytes written (will be 3 for UTF-8).
		 */
		size_t encodeByteOrderMark(byte_t* buffer, size_t size) override;
	};
}

#endif // _NATIVE_LATIN_1_CODEC_H_
