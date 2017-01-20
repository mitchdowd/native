// External Dependencies
#include <core.h>
#include <test.h>

// Namespace Usage
using namespace native;

TEST(String_defaultConstructorIsEmpty)
{
	String str;

	ASSERT(str.getLength() == 0);
	ASSERT(str.toArray() == nullptr);
}

TEST(String_literalConstructor)
{
	String a = L"Literal";

	ASSERT_EQUAL(a, L"Literal");
}

TEST(String_utf8LiteralConstructor)
{
	String a = "Literal";

	ASSERT_EQUAL(a, L"Literal");
}

TEST(String_copyConstructor)
{
	String a = L"Testing";
	String b = a;

	ASSERT_EQUAL(a, b);
}

TEST(String_moveConstructor)
{
	String a = L"Testing";
	String b = std::move(a);

	ASSERT_EQUAL(b, L"Testing");
	ASSERT(a.getLength() == 0);
	ASSERT(a.toArray() == nullptr);
}

TEST(String_singleCharacterConstructor)
{
	String a = L'X';

	ASSERT(a.getLength() == 1);
	ASSERT(a[0] == L'X');
}

TEST(String_lengthOf)
{
	ASSERT(String::lengthOf(L"Testing") == 7);
}

TEST(String_compare)
{
	String str = L"Testing";

	ASSERT(str == L"Testing");
	ASSERT(str != L"testing");
}

TEST(String_append)
{
	String str = L"Testing";

	str += L" 123";

	ASSERT_EQUAL(str, L"Testing 123");
}

TEST(String_indexOf)
{
	String str = L"Testing";

	ASSERT(str.indexOf(L"ting") == 3);
	ASSERT(str.indexOf(L"x") < 0);
}

TEST(String_lastIndexOf)
{
	String str = L"Testing Testing";

	ASSERT(str.lastIndexOf(L"Test") == 8);
}

TEST(String_indexOfAny)
{
	String str = L"Testing";

	ASSERT(str.indexOfAny(L"gni") == 4);
}

TEST(String_lastIndexOfAny)
{
	String str = L"Testing Testing";

	ASSERT(str.lastIndexOfAny(L"tse") == 11);
}

TEST(String_endsWith)
{
	String str = L"Testing";

	ASSERT(str.endsWith(L"ing"));
	ASSERT(str.endsWith(L'g'));
	ASSERT(!str.endsWith(L"x"));
}

TEST(String_subString)
{
	String str = L"Testing";

	ASSERT_EQUAL(str.substring(1, 4), L"esti");
}

TEST(String_clear)
{
	String str = L"Testing";

	str.clear();

	ASSERT(str.toArray() == nullptr);
	ASSERT(str.getLength() == 0);
}

TEST(String_toUpper)
{
	String str = L"Testing";

	ASSERT_EQUAL(str.toUpper(), L"TESTING");
	ASSERT_EQUAL(str, L"Testing");
}

TEST(String_replace)
{
	String str = L"Testing";

	ASSERT_EQUAL(str.replace(L"ing", L"ed"), L"Tested");
	ASSERT_EQUAL(str, L"Testing");
}

TEST(String_replaceAny)
{
	String str = L"Testing";

	ASSERT_EQUAL(str.replaceAny(L"ing", L'x'), L"Testxxx");
	ASSERT_EQUAL(str, L"Testing");
}

TEST(String_toUtf8)
{
	String str = L"\x20AC\x00A2";

	ASSERT_EQUAL(str.toUtf8(), "â‚¬Â\x00A2");
}

TEST(String_fromUtf8)
{
	String str = String::fromUtf8("â‚¬Â\x00A2");

	ASSERT_EQUAL(str, L"\x20AC\x00A2");
}

TEST(String_format)
{
	float pi = 3.14159265f;

	ASSERT_EQUAL(String::format(L"{0} {0:.3}", pi), L"3.141593 3.142");
	ASSERT_EQUAL(String::format(L"}{{}{1}{0}", 0, 1), L"}{}10");
	ASSERT_THROWS(String::format(L"{0:{}", pi), FormatException);
	ASSERT_EQUAL(String::format(L"({0})", String(L"Test")), L"(Test)");
}

TEST(String_fromUtf16)
{
	String str = u"\x20AC\x00A2";

	ASSERT_EQUAL(str.toUtf8(), "â‚¬Â\x00A2");
}

TEST(String_fromUtf32)
{
	String str = u"\x000020AC\x000000A2";

	ASSERT_EQUAL(str.toUtf8(), "â‚¬Â\x00A2");
}
