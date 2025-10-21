#include <array>
#include <iostream>
#include <print>

using max_uint_t = __uint128_t;
using array_2x2_t = std::array<std::array<max_uint_t, 2>, 2>;

static constexpr auto M = array_2x2_t{{
	{1, 1},
	{1, 0}
}};

// Probably needless in the future when uint128_t is supported
std::ostream& operator<<(std::ostream& stream, __uint128_t value) {
	auto buffer = std::array<char, 39>(); // log2(2^128) = 38.53
	auto bufferP = buffer.end();
	do {
		bufferP--;
		*bufferP = "0123456789"[value % 10];
		value /= 10;
	} while (value != 0);
	stream.write(bufferP, buffer.end() - bufferP);
	return stream;
}

// Optimized recursive multiplication.
constexpr array_2x2_t multiply(const array_2x2_t& f, const array_2x2_t& m) {
	return {{
		{f[0][0] * m[0][0] + f[0][1] * m[1][0], f[0][0] * m[0][1] + f[0][1] * m[1][1]},
		{f[1][0] * m[0][0] + f[1][1] * m[1][0], f[1][0] * m[0][1] + f[1][1] * m[1][1]}
	}};
}

constexpr array_2x2_t power(const array_2x2_t& f, int n) {
	if (n < 2) {
		return f;
	}
	auto result = power(f, n / 2);
	result = multiply(result, result);
	if (n % 2 != 0) {
		result = multiply(result, M);
	}
	return result;
}

constexpr max_uint_t fibonacci(int n) {
	return (n != 0) ? power(M, n - 1)[0][0] : 0;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
        std::println(std::cerr, "Usage: fibonacci++ N");
        std::println(std::cerr, "   Calculate a fibonacci number, using {} bit integers", 8 * sizeof(max_uint_t));
		return 1;
	}
	auto n = std::atoi(argv[1]);
	std::println("{}\t{}", n, fibonacci(n));
	return 0;
}
