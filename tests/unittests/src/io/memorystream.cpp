// External Dependencies
#include <test.h>
#include <io.h>

// Namespace Usage
using namespace native;
using namespace native::io;

TEST(MemoryStream_initialCapacity)
{
	MemoryStream stream(1024);

	ASSERT(stream.getCapacity() == 1024);
}

TEST(MemoryStream_write)
{
	MemoryStream stream;

	stream.write("Hello world", 11);

	ASSERT(stream.getPosition() == 11);
	ASSERT(stream.getCapacity() >= 11);
	ASSERT(stream.getLength() == 11);
}

TEST(MemoryStream_clear)
{
	MemoryStream stream(1024);

	stream.write("Hello world", 11);

	stream.clear();

	ASSERT(stream.getPosition() == 0);
	ASSERT(stream.getLength() == 0);
	ASSERT(stream.getCapacity() == 0);
}

TEST(MemoryStream_seek)
{
	MemoryStream stream;

	stream.write("Hello world", 11);
	stream.seek(0);

	ASSERT(stream.getPosition() == 0);

	stream.seek(999);

	ASSERT(stream.getPosition() == stream.getLength());
}

TEST(MemoryStream_read)
{
	MemoryStream stream;

	stream.write("Hello world", 12);
	stream.seek(0);

	char buffer[30];
	size_t result = stream.read(buffer, stream.getLength());

	ASSERT(result == stream.getLength());
	ASSERT(stream.getPosition() == stream.getLength());
	ASSERT_EQUAL(buffer, "Hello world");
}