#pragma once

#include <iostream>

#define D
#if defined _DEBUG || defined D
#  define DEBUG(x) do { std::cerr << x; } while (0)
#else
#  define DEBUG(x)
#endif

template <typename T>
auto operator << (std::ostream& os, const T& rhs)
// SFINAE goodness... only toString-able objects are eligible,
// that removes the possible ambighuity with std::operator<<
-> decltype(rhs.toString(), os) {
	using std::operator<<;
	return os << rhs.toString();
}

