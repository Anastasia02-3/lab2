#include "trykutnyk.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Triangle t;
    int n;

    cout << "ВВедіть координати вершини A (x y): ";
    cin >> t.A.x >> t.A.y;
    cout << "ВВедіть  координати вершини B (x y): ";
    cin >> t.B.x >> t.B.y;
    cout << "ВВедіть  координати вершини C (x y): ";
    cin >> t.C.x >> t.C.y;

    if (Vyrodzhenyi(t)) {
        cout << "Трикутник є виродженим!" << endl;
        return 1;
    }

    cout << "Площа трикутника: " << Geron(t) << endl;

    cout << "Скільки  точок перевірити? ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        Point p;
        cout << "Точка " << i << " (x y): ";
        cin >> p.x >> p.y;

        int result = VekDobytok(t, p);
        if (result == 1)
            cout << "Точка всередині трикутника" << endl;
        else if (result == 2)
            cout << "Точка на межі трикутника" << endl;
        else
            cout << "Точка ззовні трикутника" << endl;
    }

    return 0;
}