#pragma once

#include <iostream>

#ifdef _DEBUG
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

