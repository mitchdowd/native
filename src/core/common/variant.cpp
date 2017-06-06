// Standard Dependencies
#include <new>

// Module Dependencies
#include "../include/convert.h"
#include "../include/exception.h"
#include "../include/variant.h"

namespace native
{
	Variant::Variant() noexcept : _type(VariantType::Null)
	{
	}

	Variant::Variant(const Variant& other)
	{
		set(&other);
	}

	Variant::Variant(Variant&& other)
	{
		set(&other);
	}

	Variant::Variant(const String& value) : _type(VariantType::String)
	{
		new(&_string) String(value);
	}

	Variant::Variant(const wchar_t* value) : _type(VariantType::String)
	{
		new(&_string) String(value);
	}

	Variant::Variant(const char* value) : _type(VariantType::String)
	{
		new(&_string) String(value);
	}

	Variant::Variant(int value) noexcept : _type(VariantType::Int)
	{
		_int = value;
	}

	Variant::Variant(float value) noexcept : _type(VariantType::Float)
	{
		_float = value;
	}

	Variant::~Variant()
	{
		destroy(this);
	}

	Variant& Variant::operator=(const Variant& value)
	{
		if (&value != this)
		{
			// Call the destructor for the existing value.
			destroy(this);
			set(&value);
		}

		return *this;
	}

	String Variant::toString() const
	{
		switch (_type)
		{
		case VariantType::String:
			return _string;

		case VariantType::Int:
			return String::format(L"{0}", _int);

		case VariantType::Float:
			return String::format(L"{0}", _float);
		}

		throw InvalidStateException("Cannot convert current Variant to String");
	}

	int Variant::toInt() const
	{
		switch (_type)
		{
		case VariantType::String:
			return Convert::toInt(_string);

		case VariantType::Int:
			return _int;

		case VariantType::Float:
			return int(_float);
		}

		throw InvalidStateException("Cannot convert current Variant to int");
	}

	float Variant::toFloat() const
	{
		switch (_type)
		{
		case VariantType::String:
			return Convert::toFloat(_string);

		case VariantType::Int:
			return float(_int);

		case VariantType::Float:
			return _float;
		}

		throw InvalidStateException("Cannot convert current Variant to float");
	}

	void Variant::destroy(Variant* value)
	{
		switch (value->_type)
		{
		case VariantType::String:
			value->_string.~String();
			break;

			// TODO: New VariantTypes MUST go here.
		}

		value->_type = VariantType::Null;
	}

	void Variant::set(const Variant* value)
	{
		_type = value->_type;

		switch (_type)
		{
		case VariantType::String:
			new(&_string) String(value->_string);
			break;

		case VariantType::Int:
			_int = value->_int;
			break;

		case VariantType::Float:
			_float = value->_float;
			break;

			// TODO: New VariantTypes MUST go here.
		}
	}
}

