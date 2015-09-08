#define BOOST_TEST_MODULE CastTest
#include <boost/test/included/unit_test.hpp>

/* If a temporary object of type new_type can be declared and initialized with expression,
 * as by new_type Temp(expression);, which may involve implicit conversions,
 * a call to the constructor of new_type or a call to a user-defined conversion operator,
 * then static_cast<type>(expression) computes and returns the value of that temporary object. */
BOOST_AUTO_TEST_CASE(static_cast_test_1)
{
	const int foo_magic = 42;
	const std::string bar_magic = "-1";

	class Foo {
	public:
		explicit Foo(int foo) : m_foo(foo) {}
		/* explicit */ Foo(const std::string &foo) : m_foo(std::stoi(foo)) {}
		operator int() const { return m_foo; }

	private:
		int m_foo;
	};

	/* The following line won't compile with the explicit ctor.
	 * At the same time the static_cast allow us to call explicit ctor implicitly. */
	/* Foo foo = bar; */
	Foo foo = static_cast<Foo>(foo_magic);
	BOOST_CHECK(foo == foo_magic);

	/* (Just for demonstration purpose) ctor will be called implicitly in the code below. */
	Foo bar = bar_magic;
	BOOST_CHECK(std::to_string(bar) == bar_magic);
}

/* If new_type is a pointer or reference to some class D and the type of expression
 * is a pointer or reference to its non-virtual base B, static_cast performs a downcast.
 * Such static_cast makes no runtime checks to ensure that the object's runtime type is actually D,
 * and may only be used safely if this precondition is guaranteed by other means,
 * such as when implementing static polymorphism. Safe downcast may be done with dynamic_cast. */
BOOST_AUTO_TEST_CASE(static_cast_test_2)
{
	/* static data members are not allowed in local classes */
	const int foo_magic = 42;
	const int bar_magic = -1;

	class Foo {
	public:
		virtual ~Foo() {}
		virtual int magic() const { return foo_magic; }
	};

	class Bar : public Foo {
	public:
		virtual int magic() const { return bar_magic; }
	};

	Foo foo;

	/* The downcast below won't compile without static_cast. */
	/* Bar &baz = foo; */
	Bar &bar = static_cast<Bar &>(foo);
	BOOST_CHECK(bar.magic() == foo_magic);

	/* At the same time dynamic_cast is smart enough not to compile the code below. */
	/* Bar &baz = dynamic_cast<Bar &>(foo); */
}
