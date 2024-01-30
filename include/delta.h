#pragma once
#include <utility>

template<typename V>
struct delta {
    V x;
    V dx;
    delta(V x,  V dx) :
    x(x), dx(dx) {}

};

// Operator overloads for delta
// Multiplication
template<typename V>
delta<V> operator*(delta<V> lhs, delta<V> rhs) {
    return delta<V>(lhs.x * rhs.x, lhs.dx * rhs.x + lhs.x * rhs.dx);
}

template<typename V>
delta<V> operator*(delta<V> lhs, V rhs) {
    return delta<V>(lhs.x * rhs, lhs.dx * rhs);
}

template<typename V>
delta<V> operator*(V lhs, delta<V> rhs) {
    return delta<V>(lhs * rhs.x, lhs * rhs.dx);
}

// Summation
template<typename V>
delta<V> operator+(delta<V> lhs, delta<V> rhs) {
    return delta<V>(lhs.x + rhs.x, lhs.dx + rhs.dx);
}

template<typename V>
delta<V> operator+(delta<V> lhs, V rhs) {
    return delta<V>(lhs.x + rhs, lhs.dx);
}

template<typename V>
delta<V> operator+(V lhs, delta<V> rhs) {
    return delta<V>(lhs + rhs.x, rhs.dx);
}