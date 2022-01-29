#ifndef SALAMANDER_MT19937RNG_H
#define SALAMANDER_MT19937RNG_H

#include <random>
#include "Services.h"

class Mt19937Rng : public RngService {
public:
    Mt19937Rng() = default;
    std::uint32_t random_int() override {
        return generator();
    }

    std::uint32_t int_between(std::uint32_t x, std::uint32_t y) override {
        return std::uniform_int_distribution<std::uint32_t>(x, y)(generator);
    }

private:
    std::mt19937 generator{std::random_device{}()};
};

#endif //SALAMANDER_MT19937RNG_H
