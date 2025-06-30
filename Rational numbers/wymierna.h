#ifndef WYMIERNA_H
#define WYMIERNA_H

#include <iostream>
#include <stdexcept>

namespace obliczenia {

class wyjatek_wymierny : public std::logic_error {
public:
    explicit wyjatek_wymierny(const std::string& msg) : std::logic_error(msg) {}
};

class przekroczenie_zakresu : public wyjatek_wymierny {
public:
    przekroczenie_zakresu() : wyjatek_wymierny("Przekroczenie zakresu liczby wymiernej") {}
};

class dzielenie_przez_zero : public wyjatek_wymierny {
public:
    dzielenie_przez_zero() : wyjatek_wymierny("Dzielenie przez zero") {}
};

class wymierna {
private:
    int licz; // Licznik
    int mian; // Mianownik
    void normalize();
    static int gcd(int a, int b);

public:
    // Konstruktory
    wymierna(int licz, int mian);
    wymierna(); // 0/1
    explicit wymierna(int liczba);

    int get_licz() const noexcept { return licz; }
    int get_mian() const noexcept { return mian; }

    friend wymierna operator+(const wymierna& w1, const wymierna& w2);
    friend wymierna operator-(const wymierna& w1, const wymierna& w2);
    friend wymierna operator*(const wymierna& w1, const wymierna& w2);
    friend wymierna operator/(const wymierna& w1, const wymierna& w2);

    wymierna& operator+=(const wymierna& w);
    wymierna& operator-=(const wymierna& w);
    wymierna& operator*=(const wymierna& w);
    wymierna& operator/=(const wymierna& w);

    wymierna operator-() const;
    wymierna operator!() const;

    explicit operator double() const noexcept;
    explicit operator int() const noexcept;

    friend std::ostream& operator<<(std::ostream& wy, const wymierna& w);
};

}

#endif
