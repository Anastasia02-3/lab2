#include "trykutnyk.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Triangle t;
    cout << "Введіть координати вершини A (x y): ";
    cin >> t.A.x >> t.A.y;
    cout << "Введіть координати вершини B (x y): ";
    cin >> t.B.x >> t.B.y;
    cout << "Введіть координати вершини C (x y): ";
    cin >> t.C.x >> t.C.y;

    if (Vyrodzhenyi(t)) {
        cout << "Увага: трикутник є виродженим!" << endl;
    } else {
        cout << "Площа (Герон):      " << heronArea(t) << endl;
        cout << "Площа (шнурування): " << t.shoelaceArea() << endl;
    }

    int n;
    cout << "Скільки точок перевірити? ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        Point p;
        cout << "Точка " << i << " (x y): ";
        cin >> p.x >> p.y;

        cout << "  [Векторний добуток] ";
        if (t.onBorder(p))
            cout << "Точка на межі трикутника" << endl;
        else if (t.contains(p))
            cout << "Точка належить трикутнику" << endl;
        else
            cout << "Точка не належить трикутнику" << endl;

        cout << "  [Метод Герона]      ";
        if (t.onBorder(p))
            cout << "Точка на межі трикутника" << endl;
        else if (t.containsHeron(p))
            cout << "Точка належить трикутнику" << endl;
        else
            cout << "Точка не належить трикутнику" << endl;
    }

    return 0;
}