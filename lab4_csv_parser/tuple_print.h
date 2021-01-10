#pragma once

#include <iostream>
#include <tuple>

namespace tuplePrint {
	template<std::size_t> struct _size_t {};

	template <typename Ch, typename Tr, class Tuple, size_t Pos>
	std::basic_ostream<Ch, Tr>& printTuple(std::basic_ostream<Ch, Tr>& os, const Tuple& t, _size_t<Pos>) {
		os << std::get< std::tuple_size<Tuple>::value - Pos >(t) << ", ";
		return printTuple(os, t, _size_t<Pos - 1>());
	}

	template <typename Ch, typename Tr, class Tuple>
	std::basic_ostream<Ch, Tr>& printTuple(std::basic_ostream<Ch, Tr>& os, const Tuple& t, _size_t<1>) {
		return os << std::get<std::tuple_size<Tuple>::value - 1>(t);
	}

	template<typename Ch, typename Tr, typename... Args>
	std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
		os << '(';
		printTuple(os, t, _size_t<sizeof...(Args)>());
		return os << ')';
	}
}

template<typename Ch, typename Tr, typename... Args>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
	return tuplePrint::operator<<(os, t);
}

