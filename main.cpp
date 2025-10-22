#include <iostream>
#include <print>
#include <gmpxx.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
        std::println(std::cerr, "Usage: fibonacci++ N");
        std::println(std::cerr, "   Calculate a fibonacci number, using big integers");
		return 1;
	}
	auto n = std::atoi(argv[1]);
	auto f = mpz_class();
	mpz_fib_ui(f.get_mpz_t(), n);
	std::println("{}\t{}", n, f.get_str());
	return 0;
}
