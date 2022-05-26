#pragma once
#include <iostream>
#include <random>
class Randomer {
	// random seed by default
	std::mt19937 gen_;
	std::uniform_real_distribution<float> dist_;  // uniform_int_distribution<float/double> for pointed number

public:
	/*  ... some convenient ctors ... */

	Randomer(float min, float max, float seed = std::random_device{}())
		: gen_{ seed }, dist_{ min, max } {
	}

	// if you want predictable numbers
	void SetSeed(float seed) {
		gen_.seed(seed);
	}

	float operator()() {
		return dist_(gen_);
	}
};
