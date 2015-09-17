#define BOOST_TEST_MODULE CastTest
#include <boost/test/included/unit_test.hpp>

namespace static_cast_test_1 {
class Foo {
public:
	template <typename T> explicit Foo(T &&str) : m_str(std::forward<T>(str)) {}
	const std::string &str() const { return m_str; }
private:
	std::string m_str;
};

BOOST_AUTO_TEST_CASE(static_cast_test_1)
{
	std::string magic = "42";

	/* call explicit ctor implicitly */
	//Foo foo = magic;
	Foo foo = static_cast<Foo>(magic);
	BOOST_CHECK(foo.str() == magic);
}
}

namespace static_cast_test_2 {
class Foo {
public:
	virtual ~Foo() {}
	static const int magic = 42;
};

class Bar : public Foo {
public:
	static const int magic = -1;
};

BOOST_AUTO_TEST_CASE(static_cast_test_2)
{
	Foo foo;

	/* careless downcasting without run-time check */
	//Bar &baz = foo;
	//Bar &baz = dynamic_cast<Bar &>(foo);
	Bar &bar = static_cast<Bar &>(foo);
	BOOST_CHECK(bar.magic == Bar::magic);
}
}

namespace static_cast_test_3 {
class Foo {
public:
	template <typename T> Foo(T &&str) : m_str(std::forward<T>(str)) {}
	const std::string &str() const { return m_str; }
private:
	std::string m_str;
};

BOOST_AUTO_TEST_CASE(static_cast_test_3)
{
	std::string magic = "42";
	Foo foo(magic);

	/* lvalue to xvalue */
	Foo bar = static_cast<Foo &&>(foo);
	BOOST_CHECK(foo.str() != magic);
	BOOST_CHECK(bar.str() == magic);
}
}

BOOST_AUTO_TEST_CASE(static_cast_test_4)
{
	const int magic = 42;

	/* discard the value of the expression */
	BOOST_CHECK(typeid(static_cast<void>(magic)) == typeid(void));
	BOOST_CHECK(typeid(static_cast<void>(magic)) != typeid(int));
	BOOST_CHECK(typeid(magic) == typeid(int));
}

BOOST_AUTO_TEST_CASE(static_cast_test_5)
{
	const int foo = 42;
	const int * const bar = &foo;
	const void * const baz = bar;
	const int * const qux = static_cast<const int * const>(baz);

	/* undo: inverse of the implicit conversion */
	BOOST_CHECK(*qux == foo);
}