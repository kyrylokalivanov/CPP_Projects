#include "wymierna.h"
#include <iostream>

using namespace obliczenia;

void test_constructors() {
    std::cout << "Test konstruktorów:\n";
    wymierna w1(3, 4); // 3/4
    std::cout << "w1 = " << w1 << ", licz = " << w1.get_licz() << ", mian = " << w1.get_mian() << "\n";
    wymierna w2(5); // 5/1
    std::cout << "w2 = " << w2 << ", licz = " << w2.get_licz() << ", mian = " << w2.get_mian() << "\n";
    wymierna w3; // 0/1
    std::cout << "w3 = " << w3 << ", licz = " << w3.get_licz() << ", mian = " << w3.get_mian() << "\n";

    try {
        wymierna w4(1, 0); // Powinno rzucić dzielenie_przez_zero
    } catch (const dzielenie_przez_zero& e) {
        std::cout << "Złapano wyjątek: " << e.what() << "\n";
    }
}

void test_arithmetic() {
    std::cout << "\nTest operacji arytmetycznych:\n";
    wymierna w1(1, 2); // 1/2
    wymierna w2(1, 3); // 1/3
    std::cout << w1 << " + " << w2 << " = " << (w1 + w2) << "\n";
    std::cout << w1 << " - " << w2 << " = " << (w1 - w2) << "\n";
    std::cout << w1 << " * " << w2 << " = " << (w1 * w2) << "\n";
    std::cout << w1 << " / " << w2 << " = " << (w1 / w2) << "\n";

    w1 += w2;
    std::cout << "w1 += w2: " << w1 << "\n";

    try {
        wymierna w3 = w1 / wymierna(0, 1); // Dzielenie przez 0
    } catch (const dzielenie_przez_zero& e) {
        std::cout << "Złapano wyjątek: " << e.what() << "\n";
    }
}

void test_unary() {
    std::cout << "\nTest operacji unarnych:\n";
    wymierna w1(3, 4); // 3/4
    std::cout << "-(" << w1 << ") = " << (-w1) << "\n";
    std::cout << "!(" << w1 << ") = " << (!w1) << "\n";

    try {
        wymierna w2(0, 1);
        wymierna w3 = !w2; // Odwrotność zera
    } catch (const dzielenie_przez_zero& e) {
        std::cout << "Złapano wyjątek: " << e.what() << "\n";
    }
}

void test_casting() {
    std::cout << "\nTest rzutowań:\n";
    wymierna w1(7, 2); // 3.5
    std::cout << w1 << " jako double: " << static_cast<double>(w1) << "\n";
    std::cout << w1 << " jako int: " << static_cast<int>(w1) << "\n";
}

void test_copy() {
    std::cout << "\nTest kopiowania:\n";
    wymierna w1(5, 6);
    wymierna w2(w1); // Konstruktor kopiujący
    std::cout << "Kopia w1: " << w2 << "\n";
    wymierna w3;
    w3 = w1; // Przypisanie kopiujące
    std::cout << "Przypisanie w1: " << w3 << "\n";
}

void test_periodic() {
    std::cout << "\nTest zapisu okresowego:\n";
    wymierna w1(2359348, 99900); // Powinno być 23.6(1709)
    wymierna w2 (234243, 566);
    wymierna w4 (666666, 23);
    std::cout << w1 << "\n" << w2 << "\n" << w4 << "\n";
}

int main() {
    test_constructors();
    test_arithmetic();
    test_unary();
    test_casting();
    test_copy();
    test_periodic();
    return 0;
}
