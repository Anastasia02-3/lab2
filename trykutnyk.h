#ifndef TRYKUTNYK_H
#define TRYKUTNYK_H

#include <cmath>
#include <iostream> // Додаємо для потенційного виводу, якщо знадобиться

// Константа точності, доступна для всього проєкту
const double EPS = 1e-9;

struct Point {
    double x, y;
};

// Прототипи допоміжних функцій
double distance(const Point &p1, const Point &p2);

struct Triangle {
    Point A, B, C;

    // Методи обчислення площі
    double area() const;          // Основний метод
    double shoelaceArea() const;  // Метод Гаусса (шнурування)

    // Перевірка на узгодженість методів
    bool checkConsistency() const;

    // Перевірка на знаходження точки всередині
    bool contains(const Point &P) const;      // Через векторний добуток
    bool containsHeron(const Point &P) const; // Через суму площ (Герон)

    // Перевірка на межу (1 - на межі, 0 - ні)
    int onBorder(const Point &P) const;
};

// Функції, що працюють з об'єктом Triangle
double heronArea(const Triangle &t);
bool Vyrodzhenyi(const Triangle &t);

#endif