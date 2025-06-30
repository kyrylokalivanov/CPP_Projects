#include "wymierna.h"
#include <cmath>
#include <limits>
#include <sstream>
#include <vector>

namespace obliczenia {

int wymierna::gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a ? a : 1;
} // metoda euklidesa

void wymierna::normalize() {
    if (mian == 0) throw dzielenie_przez_zero();
    if (mian < 0) {
        licz = -licz;
        mian = -mian;
    }
    int d = gcd(licz, mian);
    licz /= d;
    mian /= d;
}

wymierna::wymierna(int licz, int mian) : licz(licz), mian(mian) {
    if (mian == 0) throw dzielenie_przez_zero();
    normalize();
}

wymierna::wymierna() : licz(0), mian(1) {}

wymierna::wymierna(int liczba) : licz(liczba), mian(1) {}

wymierna operator+(const wymierna& w1, const wymierna& w2) {
    long long new_licz = static_cast<long long>(w1.licz) * w2.mian + static_cast<long long>(w2.licz) * w1.mian;
    long long new_mian = static_cast<long long>(w1.mian) * w2.mian;
    if (new_licz > std::numeric_limits<int>::max() || new_licz < std::numeric_limits<int>::min() ||
        new_mian > std::numeric_limits<int>::max() || new_mian < std::numeric_limits<int>::min()) {
        throw przekroczenie_zakresu();
    }
    return wymierna(static_cast<int>(new_licz), static_cast<int>(new_mian));
}

wymierna operator-(const wymierna& w1, const wymierna& w2) {
    long long new_licz = static_cast<long long>(w1.licz) * w2.mian - static_cast<long long>(w2.licz) * w1.mian;
    long long new_mian = static_cast<long long>(w1.mian) * w2.mian;
    if (new_licz > std::numeric_limits<int>::max() || new_licz < std::numeric_limits<int>::min() ||
        new_mian > std::numeric_limits<int>::max() || new_mian < std::numeric_limits<int>::min()) {
        throw przekroczenie_zakresu();
    }
    return wymierna(static_cast<int>(new_licz), static_cast<int>(new_mian));
}

wymierna operator*(const wymierna& w1, const wymierna& w2) {
    long long new_licz = static_cast<long long>(w1.licz) * w2.licz;
    long long new_mian = static_cast<long long>(w1.mian) * w2.mian;
    if (new_licz > std::numeric_limits<int>::max() || new_licz < std::numeric_limits<int>::min() ||
        new_mian > std::numeric_limits<int>::max() || new_mian < std::numeric_limits<int>::min()) {
        throw przekroczenie_zakresu();
    }
    return wymierna(static_cast<int>(new_licz), static_cast<int>(new_mian));
}

wymierna operator/(const wymierna& w1, const wymierna& w2) {
    if (w2.licz == 0) throw dzielenie_przez_zero();
    long long new_licz = static_cast<long long>(w1.licz) * w2.mian;
    long long new_mian = static_cast<long long>(w1.mian) * w2.licz;
    if (new_licz > std::numeric_limits<int>::max() || new_licz < std::numeric_limits<int>::min() ||
        new_mian > std::numeric_limits<int>::max() || new_mian < std::numeric_limits<int>::min()) {
        throw przekroczenie_zakresu();
    }
    return wymierna(static_cast<int>(new_licz), static_cast<int>(new_mian));
}

wymierna& wymierna::operator+=(const wymierna& w) {
    *this = *this + w;
    return *this;
}

wymierna& wymierna::operator-=(const wymierna& w) {
    *this = *this - w;
    return *this;
}

wymierna& wymierna::operator*=(const wymierna& w) {
    *this = *this * w;
    return *this;
}

wymierna& wymierna::operator/=(const wymierna& w) {
    *this = *this / w;
    return *this;
}

wymierna wymierna::operator-() const {
    return wymierna(-licz, mian);
}

wymierna wymierna::operator!() const {
    if (licz == 0) throw dzielenie_przez_zero();
    return wymierna(mian, licz);
}

wymierna::operator double() const noexcept {
    return static_cast<double>(licz) / mian;
}

wymierna::operator int() const noexcept {
    return static_cast<int>(std::round(static_cast<double>(licz) / mian));
}

std::ostream& operator<<(std::ostream& wy, const wymierna& w) {
    double val = static_cast<double>(w.licz) / w.mian;
    int whole = static_cast<int>(val);
    double frac = std::abs(val - whole);
    std::stringstream ss;
    ss << whole << ".";
    std::string decimal;
    int period_start = -1;
    std::vector<int> remainders;
    int remainder = static_cast<int>(frac * w.mian);
    for (int i = 0; i < 100000 && remainder != 0; ++i) {
        remainder *= 10;
        int digit = remainder / w.mian;
        decimal += std::to_string(digit);
        remainder %= w.mian;
        for (size_t j = 0; j < remainders.size(); ++j) {
            if (remainders[j] == remainder) {
                period_start = j;
                break;
            }
        }
        if (period_start != -1) break;
        remainders.push_back(remainder);
    }
    if (period_start == -1) {
        ss << decimal;
    } else {
        ss << decimal.substr(0, period_start) << "(" << decimal.substr(period_start) << ")";
    }
    wy << ss.str();
    return wy;
}

}
