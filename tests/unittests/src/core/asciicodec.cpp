// External Dependencies
#include <core.h>
#include <test.h>

// Namespace Usage
using namespace native;

TEST(AsciiCodec_encode)
{
	wchar_t str[] = L"Hello\x20AC";
	byte_t buffer[42];
	size_t size = 42;
	size_t length = 6;

	StringCodec* codec = StringCodec::byName(L"ASCII");

	codec->encode(buffer, size, str, length);

	buffer[size] = '\0';

	ASSERT_EQUAL((const char*) buffer, "Hello?");
}

TEST(AsciiCodec_decode)
{
	byte_t bytes[] = "Hello\xF0";
	wchar_t buffer[7];
	size_t size = 7;
	size_t length = 6;

	StringCodec* codec = StringCodec::byName(L"ASCII");

	codec->decode(buffer, size, bytes, length);

	buffer[size] = L'\0';

	ASSERT_EQUAL(buffer, L"Hello?");
}
