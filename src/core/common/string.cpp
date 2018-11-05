// Standard Dependencies
#include <cstdarg>
#include <cstring>
#include <cwchar>
#include <cwctype>
#include <string>

// Module Dependencies
#include "../include/exception.h"
#include "../include/math.h"
#include "../include/spinlock.h"
#include "../include/string.h"
#include "../include/stringcodec.h"

namespace native
{
	namespace internal
	{
		void raiseFormatException(const wchar_t* message)
		{
			throw FormatException();
		}
	}

	static StringCodec* utf8 = nullptr;
	static SpinLock utf8Lock;

	// Static Initializers
	const String String::empty;

	String::String(const wchar_t* text, size_t length) : _length(length)
	{
		if (_length == NULL_TERMINATED)
			_length = lengthOf(text);

		_array.setLength(internal::getCapacityForLength(_length));
		_array.set(0, text, _length);
		_array.set(_length, L'\0');
	}

	String::String(const char* data, size_t length)
	{
		if (length == NULL_TERMINATED)
			length = std::strlen(data);

		if (!utf8)
		{
			utf8Lock.lock();
			if (!utf8)
				utf8 = StringCodec::byName(L"UTF-8");
			utf8Lock.release();
		}

		// Create an array and decode into it.
		Array<wchar_t> buffer(length * 2);
		size_t size = buffer.getLength();
		utf8->decode((wchar_t*) buffer.toArray(), size, (const byte_t*) data, length);
		_length = length;

		// Null-terminate.
		buffer.set(size, 0);
		_array = buffer;
	}

	String::String(const char16_t* data, size_t length) : _length(length)
	{
		if (length == NULL_TERMINATED)
			_length = std::char_traits<char16_t>::length(data);

		_array.setLength(internal::getCapacityForLength(_length));

#ifdef NATIVE_PLATFORM_WIN32

		// On Windows, a wchar_t is the same size as a char16_t.
		_array.set(0, (const wchar_t*) data, _length);
		_array.set(_length, L'\0');

#else
        size_t c = 0, w = 0;

		while (c < _length)
		{
			uint32_t ch = data[c++];

			// Check for a two-segment UTF-16 character.
			if (ch >= wchar_t(0xD800) && ch <= wchar_t(0xDBFF)) {
				ch = (ch - wchar_t(0xD800)) << 10;
				ch += data[++c] - wchar_t(0xDC00 + 0x10000);
			}

			_array.set(w++, ch);
		}

		// Null-terminate.
		_array.set(_length = w, L'\0');

#endif // NATIVE_PLATFORM_WIN32
	}

	String::String(const char32_t* data, size_t length) : _length(length)
	{
		if (length == NULL_TERMINATED)
			_length = std::char_traits<char32_t>::length(data);

		_array.setLength(internal::getCapacityForLength(_length));

#ifdef NATIVE_PLATFORM_WIN32

		// Don't bother converting items exceeding the 16-bit barrier...
		for (size_t i = 0; i < _length; ++i)
			_array.set(i, data[i] > 0xFFFF ? L'?' : wchar_t(data[i]));

#else
        // On non-Windows platforms, a wchar_t is the same size as a char32_t.
		_array.set(0, (const wchar_t*) data, _length);
#endif

		_array.set(_length, L'\0');
	}

	String::String(wchar_t ch) : _length(1)
	{
		_array.setLength(internal::getCapacityForLength(_length));
		_array.set(0, ch);
		_array.set(_length, L'\0');
	}

	String::String(char ch) : _length(1)
	{
		_array.setLength(internal::getCapacityForLength(_length));
		_array.set(0, ch);
		_array.set(_length, L'\0');
	}

	String::String(const Array<wchar_t>& text, size_t length) : _length(length)
	{
		if (length == NULL_TERMINATED)
			_length = lengthOf(text.toArray());

		if (_length > text.getLength())
			internal::raiseArrayIndexException();

		_array = text;

		if (length != NULL_TERMINATED && _array.getLength() > 0)
			_array.set(_length, L'\0');
	}

	String::String(String&& other) noexcept : _array(std::move(other._array)), _length(other._length)
	{
		other._length = 0;
	}

	String& String::operator=(const wchar_t* other)
	{
		if (_array.toArray() != other)
		{
			_length = lengthOf(other);

			_array.setLength(internal::getCapacityForLength(_length));
			_array.set(0, other, _length);
		}

		return *this;
	}

	size_t String::lengthOf(const wchar_t* str)
	{
		return std::wcslen(str ? str : L"");
	}

	int String::compare(const wchar_t* text, size_t length) const
	{
		const wchar_t* data = toArray();

		return std::wcsncmp(data ? data : L"", text ? text : L"", length);
	}

	int String::compare(const String& str) const
	{
		return compare(str.toArray(), str.getLength());
	}

	void String::append(const wchar_t* text, size_t length)
	{
		if (length == NULL_TERMINATED)
			length = lengthOf(text);

		// Expand the Array if necessary.
		if (_array.getLength() <= getLength() + length)
			_array.setLength(internal::getCapacityForLength(getLength() + length));

		_array.set(getLength(), text, length);
		_array.set(_length += length, L'\0');
	}

	void String::append(const String& str)
	{
		append(str.toArray(), str.getLength());
	}

	String& String::operator+=(const wchar_t* text)
	{
		append(text);
		return *this;
	}

	String& String::operator+=(const String& str)
	{
		append(str);
		return *this;
	}

	String& String::operator+=(wchar_t ch)
	{
		append(ch);
		return *this;
	}

	ptrint_t String::indexOf(const wchar_t* substr, size_t startIndex) const
	{
		const wchar_t* data = toArray();
		const wchar_t* result = std::wcsstr(data + startIndex, substr);

		return result == nullptr ? -1 : result - data;
	}

	ptrint_t String::lastIndexOf(const wchar_t* substr) const
	{
		const wchar_t* data = toArray();
		size_t length = getLength();

		for (size_t i = 1; i < length; i++)
		{
			if (data[length - i] == *substr && std::wcsstr(data + (length - i), substr) != nullptr)
				return length - i;

		}

		return -1;
	}

	ptrint_t String::indexOfAny(const wchar_t* chars, size_t startIndex) const
	{
		const wchar_t* data = toArray();
		const wchar_t* result = std::wcspbrk(data + startIndex, chars);

		return result == nullptr ? -1 : result - data;
	}

	ptrint_t String::lastIndexOfAny(const wchar_t* chars) const
	{
		const wchar_t* data = toArray();
		size_t length = getLength();

		for (size_t i = 1; i < length; i++)
		{
			const wchar_t* c = chars;

			while (*c) {
				if (data[length - i] == *c++)
					return length - i;
			}
		}

		return -1;
	}

	bool String::contains(const wchar_t* substr) const
	{
		return indexOf(substr) >= 0;
	}

	bool String::startsWith(const wchar_t* substr) const
	{
		return indexOf(substr) == 0;
	}

	bool String::startsWith(wchar_t substr) const
	{
		if (getLength() == 0)
			return false;

		return _array[0] == substr;
	}

	bool String::endsWith(const String& substr) const
	{
		return lastIndexOf(substr) == int(getLength() - substr.getLength());
	}

	bool String::endsWith(wchar_t substr) const
	{
		if (getLength() == 0)
			return false;

		return _array[getLength() - 1] == substr;
	}

	String String::substring(size_t start, size_t length) const
	{
		if (start > getLength())
			internal::raiseArrayIndexException();

		length = Math::min(getLength() - start, length);

		return String(toArray() + start, length);
	}

	void String::clear()
	{
		_length = 0;
		_array.clear();
	}

	String String::toUpper() const
	{
		Array<wchar_t> str(internal::getCapacityForLength(getLength()));

		for (size_t i = 0; i < getLength(); i++)
			str.set(i, std::towupper(_array[i]));

		// Null-terminate.
		str.set(getLength(), L'\0');
		return str;
	}

	String String::replace(const wchar_t* oldPart, const wchar_t* newPart) const
	{
		size_t partLen = lengthOf(oldPart);
		const wchar_t* data = toArray();
		int64_t start = 0, next = indexOf(oldPart);

		if (next >= 0)
		{
			String result;

			do
			{
				if (next > 0)
					result.append(data + start, (size_t)(next - start));

				result.append(newPart);
				next = indexOf(oldPart, (size_t)(start = next + partLen));

			} while (next >= 0);

			result.append(data + start);

			return result;
		}

		return *this;
	}

	String String::replaceAny(const wchar_t* chars, wchar_t substitute) const
	{
		const wchar_t* data = toArray();
		int64_t start = 0, next = indexOfAny(chars);

		if (next >= 0)
		{
			String result;

			do
			{
				if (next > 0)
					result.append(data + start, (size_t)(next - start));

				result.append(substitute);
				next = indexOfAny(chars, (size_t)(start = ++next));

			} while (next >= 0);

			result.append(data + start);

			return result;
		}

		return *this;
	}

	ByteArray String::toBytes(const String& codecName) const
	{
		StringCodec* codec = StringCodec::byName(codecName);

		if (codec == nullptr)
			throw InvalidArgumentException();

		// Create an array and encode into it.
		ByteArray buffer(codec->getLength(toArray(), getLength()) + 1);
		size_t size = buffer.getLength(), length = getLength();
		codec->encode((byte_t*) buffer.toArray(), size, toArray(), length);

		// Null-terminate.
		buffer.set(size, 0);
		return buffer;
	}

	String String::fromBytes(const String& codecName, const byte_t* data, size_t bytes)
	{
		StringCodec* codec = StringCodec::byName(codecName);

		if (codec == nullptr)
			throw InvalidArgumentException();

		// Create an array and decode into it.
		Array<wchar_t> buffer(bytes * 2);
		size_t size = buffer.getLength();
		codec->decode((wchar_t*) buffer.toArray(), size, data, bytes);

		// Null-terminate.
		buffer.set(size, 0);
		return String(buffer);
	}

	ByteArray String::toUtf8() const
	{
		if (!utf8)
		{
			utf8Lock.lock();
			utf8 = StringCodec::byName(L"UTF-8");
			utf8Lock.release();
		}

		// Create an array and encode into it.
		ByteArray buffer(utf8->getLength(toArray(), getLength()) + 1);
		size_t size = buffer.getLength(), length = getLength();
		utf8->encode((byte_t*) buffer.toArray(), size, toArray(), length);

		// Null-terminate.
		buffer.set(size, 0);
		return buffer;
	}

	String String::fromUtf8(const void* data, size_t bytes)
	{
		if (!utf8)
		{
			utf8Lock.lock();
			utf8 = StringCodec::byName(L"UTF-8");
			utf8Lock.release();
		}

		if (bytes == NULL_TERMINATED)
			bytes = std::strlen(data ? (const char*) data : "");

		// Create an array and decode into it.
		Array<wchar_t> buffer(bytes * 2);
		size_t size = buffer.getLength();
		utf8->decode((wchar_t*) buffer.toArray(), size, (const byte_t*)data, bytes);

		// Null-terminate.
		buffer.set(size, 0);
		return String(buffer);
	}

	template <class TValue>
	static String fromPrintf(TValue value, const wchar_t* format, const wchar_t* type)
	{
		const Array<wchar_t> buffer(128);
		wchar_t typeBuffer[32];
		int i = 0;

		// Create the format string from the type and passed-in format.
		while (*type)
		{
			if (*type == L'*')
			{
				if (format)
					while (*format)
						typeBuffer[i++] = *format++;
			}
			else
			{
				typeBuffer[i++] = *type;
			}

			++type;
		}

		// Null-terminate the format.
		typeBuffer[i] = L'\0';

		// Let swprintf() do the magic.
		std::swprintf((wchar_t*) buffer.toArray(), buffer.getLength(), typeBuffer, value);
		return buffer;
	}

	String toString(const String& value, const wchar_t* format)
	{
#ifdef NATIVE_PLATFORM_WIN32
		return fromPrintf(value.toArray(), format, L"%*s");	// Stupid Windows is back-to-front.
#else
		return fromPrintf(value.toArray(), format, L"%*S");
#endif  // NATIVE_PLATFORM_WIN32
	}

	String toString(const wchar_t* value, const wchar_t* format)
	{
#ifdef NATIVE_PLATFORM_WIN32
		return fromPrintf(value, format, L"%*s");	// Stupid Windows is back-to-front.
#else
		return fromPrintf(value, format, L"%*S");
#endif // NATIVE_PLATFORM_WIN32
	}

	String toString(int32_t value, const wchar_t* format)
	{
		return fromPrintf(value, format, L"%*d");
	}

	String toString(int64_t value, const wchar_t* format)
	{
		return fromPrintf(value, format, L"%*lld");
	}

	String toString(uint32_t value, const wchar_t* format)
	{
		return fromPrintf(value, format, L"%*u");
	}

	String toString(uint64_t value, const wchar_t* format)
	{
		return fromPrintf(value, format, L"%*llu");
	}

	String toString(float value, const wchar_t* format)
	{
		return fromPrintf(value, format, L"%*f");
	}

	String toString(double value, const wchar_t* format)
	{
		return fromPrintf(value, format, L"%*lf");
	}
}
