#include "core/random.hpp"

Random& Random::get() {
    static Random instance;
    return instance;
}

Random::Random() {
    std::random_device rd;
    gen.seed(rd());
}

template<typename T>
typename std::enable_if<
    std::disjunction<
        std::is_floating_point<T>,
        std::is_same<T, bool>
    >::value,
    T
>::type
Random::next() {
    if constexpr (std::is_same_v<T, bool>) {
        std::bernoulli_distribution d(0.5);
        return d(gen);
    } else {
        std::uniform_real_distribution<T> d(0.0, 1.0);
        return d(gen);
    }
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
Random::next(T max) {
    if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> d(0.0, max);
        return d(gen);
    } else {
        std::uniform_int_distribution<T> d(0, max);
        return d(gen);
    }
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
Random::next(T min, T max) {
    if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> d(min, max);
        return d(gen);
    } else {
        std::uniform_int_distribution<T> d(min, max);
        return d(gen);
    }
}

template<typename T>
typename std::enable_if<std::is_same<T, bool>::value, T>::type
Random::next(double probability) {
    std::bernoulli_distribution d(probability);
    return d(gen);
}

template<typename T>
typename std::enable_if<std::is_same<T, bool>::value, T>::type
Random::next(float probability) {
    std::bernoulli_distribution d(probability);
    return d(gen);
}

// Explicit template instantiations
template float Random::next<float>();
template double Random::next<double>();
template bool Random::next<bool>();

template int Random::next<int>(int);
template float Random::next<float>(float);
template double Random::next<double>(double);

template int Random::next<int>(int, int);
template float Random::next<float>(float, float);
template double Random::next<double>(double, double);

template bool Random::next<bool>(double);
template bool Random::next<bool>(float);

