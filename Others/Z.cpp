#include <bits/stdc++.h>

template <typename T, auto f = std::multiplies<T>()>
constexpr static T power(T a, int64_t b) {
    T res;
    if constexpr (std::is_arithmetic_v<T>) {
        res = 1;
    } else {
        res = a.identity();
    }
    while (b) {
        if (b & 1) {
            res = f(res, a);
        }
        b >>= 1;
        a = f(a, a);
    }
    return res;
}

template <typename T, T MOD>
struct ModInt {
    using prod_type = std::conditional_t<std::is_same_v<T, int>, long long, __int128>;
    T val;
    constexpr ModInt(const int64_t v = 0) : val(v % MOD) { if (val < 0) val += MOD; }
    constexpr ModInt operator+() const { return ModInt(val); }
    constexpr ModInt operator-() const { return ModInt(MOD - val); }
    constexpr ModInt inv() const {
        return power(*this, MOD - 2);
    }
    constexpr friend ModInt operator+(ModInt lhs, const ModInt rhs) { return lhs += rhs; }
    constexpr friend ModInt operator-(ModInt lhs, const ModInt rhs) { return lhs -= rhs; }
    constexpr friend ModInt operator*(ModInt lhs, const ModInt rhs) { return lhs *= rhs; }
    constexpr friend ModInt operator/(ModInt lhs, const ModInt rhs) { return lhs /= rhs; }
    constexpr ModInt &operator+=(const ModInt x) {
        if ((val += x.val) >= MOD)
            val -= MOD;
        return *this;
    }
    constexpr ModInt &operator-=(const ModInt x) {
        if ((val -= x.val) < 0)
            val += MOD;
        return *this;
    }
    constexpr ModInt &operator*=(const ModInt x) {
        val = prod_type(val) * x.val % MOD;
        return *this;
    }
    constexpr ModInt &operator/=(const ModInt x) { return *this *= x.inv(); }
    bool operator==(const ModInt b) const { return val == b.val; }
    bool operator!=(const ModInt b) const { return val != b.val; }
    friend std::istream &operator>>(std::istream &is, ModInt &x) noexcept {
        return is >> x.val;
    }
    friend std::ostream &operator<<(std::ostream &os, const ModInt x) noexcept {
        return os << x.val;
    }
    constexpr static ModInt identity() { return 1; }
    constexpr ModInt pow(int64_t p) {
        return power(*this, p);
    }
};
using ModInt1000000007 = ModInt<int, 1'000'000'007>;
using ModInt998244353 = ModInt<int, 998244353>;