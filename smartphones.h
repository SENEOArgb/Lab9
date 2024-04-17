#pragma once

#ifndef SMARTPHONE_H
#define SMARTPHONE_H

#include <string>

using namespace std;

// Структура для хранения данных о смартфоне
struct Smartphone {
    string brand;
    string model;
    double price;
    double screen_size;

    // Конструктор для удобства создания экземпляров структуры
    Smartphone(const string& b, const string& m, double p, double s)
        : brand(b), model(m), price(p), screen_size(s) {}
};

#endif // SMARTPHONE_H