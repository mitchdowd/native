// External Dependencies
#include <test.h>
#include <io.h>

// Namespace Usage
using namespace native;
using namespace native::io;

TEST(TextStream_writeUtf8)
{
	MemoryStream stream(1024);
	TextStream textStream(stream);

	textStream.write(L"\x20AC\x00A2");
	textStream.flush();

	ByteArray buffer = stream.getBuffer();
	buffer.set(textStream.getOutputLength(), '\0');

	ASSERT_EQUAL((const char*) buffer, "â‚¬Â\x00A2");
}

