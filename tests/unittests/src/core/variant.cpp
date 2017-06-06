// External Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;
using namespace native::test;

TEST(Variant_defaultConstructorIsNull)
{
	Variant var;

	ASSERT(var.isNull());
}

TEST(Variant_stringToInt)
{
	Variant var = "123";

	ASSERT(var.toInt() == 123);
}

TEST(Variant_intToString)
{
	Variant var = 123;

	ASSERT(var.toString() == L"123");
}

TEST(Variant_getType)
{
	Variant var = 123;

	ASSERT(var.getType() == VariantType::Int);
}

