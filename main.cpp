#define BOOST_TEST_MODULE CastTest
#include <boost/test/included/unit_test.hpp>

class Foo {
public:
	template <typename T> explicit Foo(T &&str) : m_str(std::forward<T>(str)) {}
	Foo() : m_str() {}
	virtual ~Foo() {}
	const std::string &to_string() const { return m_str; }
	static const int magic = 42;
protected:
	std::string m_str;
};

class Bar : public Foo {
public:
	template <typename T> Bar(T &&str) : Foo(std::forward<T>(str)) {}
	static const int magic = 0;
};

BOOST_AUTO_TEST_CASE(static_cast_test_1)
{
	std::string magic = "42";

	/* call explicit ctor implicitly */
	//Foo foo = magic;
	Foo foo = static_cast<Foo>(magic);
	BOOST_CHECK(foo.to_string() == magic);
}

BOOST_AUTO_TEST_CASE(static_cast_test_2)
{
	Foo foo;

	/* downcasting without run-time check */
	//Bar &baz = foo;
	//Bar &baz = dynamic_cast<Bar &>(foo);
	Bar &bar = static_cast<Bar &>(foo);
	BOOST_CHECK(bar.magic == Bar::magic);
}

#if 0
BOOST_AUTO_TEST_CASE(static_cast_test_3)
{
	std::string magic = "42";
	Bar foo(magic);

	/* lvalue to xvalue */
	Bar bar = static_cast<Bar &&>(foo);
	BOOST_CHECK(foo.to_string() != magic);
	BOOST_CHECK(bar.to_string() == magic);
}
#endif

BOOST_AUTO_TEST_CASE(static_cast_test_4)
{
	const int magic = 42;

	/* discard the value of the expression */
	BOOST_CHECK((std::is_same<decltype(static_cast<void>(magic)), void>::value));
	BOOST_CHECK(typeid(static_cast<void>(magic)) == typeid(void));
	BOOST_CHECK(typeid(static_cast<void>(magic)) != typeid(int));
	BOOST_CHECK(typeid(magic) == typeid(int));
}

BOOST_AUTO_TEST_CASE(static_cast_test_5)
{
	const int foo = 42;
	const int * const bar = &foo;
	const void * const baz = bar;

	/* undo: inverse of the implicit conversion */
	//const int * const qux = baz;
	const int * const qux = static_cast<const int * const>(baz);

	BOOST_CHECK(*qux == foo);
}
