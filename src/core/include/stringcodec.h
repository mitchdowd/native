#ifndef _NATIVE_STRING_CODEC_H_
#define _NATIVE_STRING_CODEC_H_ 1

// Module Dependencies
#include "exception.h"
#include "map.h"
#include "string.h"

namespace native
{
	/**
		StringCodec is the base class of all codecs used to convert between
		String and byte data.
	 */
	class StringCodec
	{
	public:
		/**
			Creates a StringCodec with the given name.
			\param name The name of the codec.
		 */
		StringCodec(const String& name);

		/**
			Encodes the text using the current codec.
			\param buffer The location to store the encoded bytes.
			\param size Size of the buffer. Returns number of bytes encoded.
			\param text The text to encode.
			\param length Number of character to encode. Returns number of characters encoded.
		 */
		virtual void encode(byte_t* buffer, size_t& size, const wchar_t* text, size_t& length) = 0;

		/**
			Decodes the byte data into text.
			\param buffer Location to store decoded characters.
			\param size Size of the buffer. Returns number of characters decoded.
			\param data The data to decode.
			\param bytes Number of bytes to decode. Returns bytes deocded.
		 */
		virtual void decode(wchar_t* buffer, size_t& size, const byte_t* data, size_t& bytes) = 0;

		/**
			Returns the required number of bytes to represent the given string in
			the current codec.
			\param text The string to measure.
			\param length The number of characters to measure.
			\return The number of bytes required.
		 */
		virtual size_t length(const wchar_t* text, size_t length) = 0;

		/**
			Writes the encoded byte order mark (BOM) for this codec to the buffer.
			\param buffer The buffer to write it to.
			\param size The size of the buffer.
			\return The number of bytes added to the buffer.
		 */
		virtual size_t encodeByteOrderMark(byte_t* buffer, size_t size);

		/**
			Retrieves the name of this StringCodec.
			\return The codec's name.
		 */
		String getName() const;

		/**
			Registers the given StringCodec subclass so it can be accessed
			by name. The Codec will then belong to the global Scope.
			\param codec The StringCodec to register.
		 */
		static void registerByName(StringCodec* codec);

		/**
			Retrieves a registered StringCodec by its name.
			\param name The name of the StringCodec.
			\return The StringCodec with that name.
		 */
		static StringCodec* byName(const String& name);

	private:
		/** Used to maintain a registry of Codecs by name. */
		class CodecRegistry : public Map<String, StringCodec*>
		{
		public:
			/** Registers basic StringCodecs. */
			CodecRegistry();
		};

		// Instance Variables
		String _name;
	};

	/**
		Thrown when there is an error to do with a coder/decoder.
	 */
	class CodecException : public Exception
	{
	};
}

#endif // _NATIVE_STRING_CODEC_H_
