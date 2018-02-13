// Module Dependencies
#include "../include/asciicodec.h"
#include "../include/latin1codec.h"
#include "../include/singleton.h"
#include "../include/stringcodec.h"
#include "../include/utf8codec.h"

namespace native
{
	StringCodec::StringCodec(const String& name) : _name(name)
	{
	}

	size_t StringCodec::encodeByteOrderMark(byte_t*, size_t)
	{
		return 0;
	}

	String StringCodec::getName() const
	{
		return _name;
	}

	void StringCodec::registerByName(StringCodec* codec)
	{
		CodecRegistry& registry = Singleton<CodecRegistry>::get();

		if (codec == nullptr)
			throw InvalidArgumentException();

		if (!registry.containsKey(codec->getName()))
		{
			registry.add(codec->getName(), codec);
		}
	}

	StringCodec* StringCodec::byName(const String& name)
	{
		CodecRegistry& registry = Singleton<CodecRegistry>::get();
		return registry[name];
	}

	StringCodec::CodecRegistry::CodecRegistry()
	{
		AsciiCodec*  ascii = new AsciiCodec();
		Latin1Codec* latin1 = new Latin1Codec();
		StringCodec* utf8 = new Utf8Codec();

		add(ascii->getName(), ascii);
		add(latin1->getName(), latin1);
		add(utf8->getName(), utf8);
	}
}
