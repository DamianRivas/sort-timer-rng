#pragma once

#include <random>

namespace simple_rng
{
    int generate_random_int()
    {
        static std::default_random_engine e{}; // reproducible
        static std::uniform_int_distribution<int> d{ 0, 10'000 };
        return d(e); // obtains a random variate
    }
}