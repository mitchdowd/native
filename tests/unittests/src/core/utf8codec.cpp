// External Dependencies
#include <core.h>
#include <test.h>

// Namespace Usage
using namespace native;

TEST(Utf8Codec_encode)
{
	wchar_t str[] = L"\x20AC\x00A2";
	byte_t buffer[sizeof(str) * 6];
	size_t size = sizeof(buffer);
	size_t length = sizeof(str);

	StringCodec* codec = StringCodec::byName(L"UTF-8");

	codec->encode(buffer, size, str, length);

	buffer[size] = '\0';

	ASSERT_EQUAL((const char*) buffer, "â‚¬Â\x00A2");
}

TEST(Utf8Codec_decode)
{
	byte_t bytes[] = "â‚¬Â\x00A2";
	wchar_t buffer[sizeof(bytes)];
	size_t size = sizeof(buffer);
	size_t length = sizeof(bytes);

	StringCodec* codec = StringCodec::byName(L"UTF-8");

	codec->decode(buffer, size, bytes, length);

	buffer[size] = L'\0';

	ASSERT_EQUAL(buffer, L"\x20AC\x00A2");
}
