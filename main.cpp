#define BOOST_TEST_MODULE CastTest
#include <boost/test/included/unit_test.hpp>

class Foo {
public:
	Foo(int baz) : m_baz(baz) {}
	operator int() const { return m_baz; }

private:
	int m_baz;
};

class Bar : public Foo {
public:
	Bar(int baz) : Foo(baz) {}
	operator int() const { return Foo::operator int() + 1; }
};

BOOST_AUTO_TEST_CASE(static_cast_test)
{
	const int baz = 42;

	/* If a temporary object of type new_type can be declared and initialized with expression,
	 * as by new_type Temp(expression);, which may involve implicit conversions,
	 * a call to the constructor of new_type or a call to a user-defined conversion operator,
	 * then static_cast<type>(expression) computes and returns the value of that temporary object. */
	BOOST_CHECK(static_cast<int>(static_cast<Foo>(baz)) == baz);

	/* If new_type is a pointer or reference to some class D and the type of expression
	 * is a pointer or reference to its non-virtual base B, static_cast performs a downcast.
	 * Such static_cast makes no runtime checks to ensure that the object's runtime type is actually D,
	 * and may only be used safely if this precondition is guaranteed by other means,
	 * such as when implementing static polymorphism. Safe downcast may be done with dynamic_cast. */
	BOOST_CHECK(static_cast<int>(static_cast<Foo>(Bar(baz)) == baz));
}
