// Local Dependencies
#include "../include/textstream.h"

namespace native
{
	namespace io
	{
		TextStream::TextStream(IStream& stream) : _stream(&stream), _outputLength(0)
		{
			_codec = StringCodec::byName(L"UTF-8");
		}

		void TextStream::write(const String& text)
		{
			// Ensure we have space for the text.
			size_t requiredLength = _outputLength + _codec->getLength(text.toArray(), text.getLength());

			if (_output.getLength() < requiredLength)
				_output.setLength(internal::getCapacityForLength(requiredLength));

			size_t size = _output.getLength() - _outputLength;
			size_t length = text.getLength();

			_codec->encode((byte_t*) &_output[_outputLength], size, text.toArray(), length);

			_outputLength += size;
		}

		void TextStream::flush()
		{
			_stream->write(_output.toArray(), _outputLength);
			_output.clear();
		}
	}
}

