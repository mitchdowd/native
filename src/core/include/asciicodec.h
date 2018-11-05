#ifndef _NATIVE_ASCII_CODEC_H_
#define _NATIVE_ASCII_CODEC_H_ 1

// Module Dependencies
#include "stringcodec.h"

namespace native
{
	/**
		AsciiCodec is the StringCodec that performs conversions between Strings
		and 7-bit, ASCII characters.
	 */
	class AsciiCodec : public StringCodec
	{
	public:
		/**
			Creates an AsciiCodec. It generally makes more sense to use StringCodec::byName()
			to save re-creating and managing another instance of Latin1Codec.
		 */
		AsciiCodec() : StringCodec(L"ASCII") {}

		/**
			Encodes the text using the ASCII codec.
			\param buffer The location to store the encoded bytes.
			\param size Size of the buffer. Returns number of bytes encoded.
			\param text The text to encode.
			\param length Number of character to encode. Returns number of characters encoded.
		 */
		void encode(byte_t* buffer, size_t& size, const wchar_t* text, size_t& length) override;

		/**
			Decodes the ASCII data into text.
			\param buffer Location to store decoded characters.
			\param size Size of the buffer. Returns number of characters decoded.
			\param data The data to decode.
			\param bytes Number of bytes to decode. Returns bytes deocded.
			 */
		void decode(wchar_t* buffer, size_t& size, const byte_t* data, size_t& bytes) override;

		/**
			Returns the required number of bytes to represent the given string in
			the ASCII codec.
			\param text The string to measure.
			\param length The number of characters to measure.
			\return The number of bytes required.
		 */
		size_t getLength(const wchar_t* text, size_t length) override;

		/**
			Writes the ASCII byte order mark to the buffer. This is a three
			byte mark.
			\param buffer The buffer to write to.
			\param size The size of the buffer.
			\return The number of bytes written (will be 3 for UTF-8).
		 */
		size_t encodeByteOrderMark(byte_t* buffer, size_t size) override;
	};
}

#endif // _NATIVE_ASCII_CODEC_H_
