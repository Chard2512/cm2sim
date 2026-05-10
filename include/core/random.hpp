#ifndef _CM2_RANDOM_HPP_
#define _CM2_RANDOM_HPP_
#include <random>
#include <type_traits>

class Random {
private:
    std::mt19937 gen;
    
    Random();
    
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;
    
    ~Random() = default;

public:
    static Random& get();

    template<typename T>
    typename std::enable_if<
        std::disjunction<
            std::is_floating_point<T>,
            std::is_same<T, bool>
        >::value,
        T
    >::type
    next();

    template<typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    next(T max);

    template<typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    next(T min, T max);

    template<typename T>
    typename std::enable_if<std::is_same<T, bool>::value, T>::type
    next(double probability);

    template<typename T>
    typename std::enable_if<std::is_same<T, bool>::value, T>::type
    next(float probability);
};

#endif