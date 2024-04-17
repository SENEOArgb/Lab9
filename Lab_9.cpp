// Lab_9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "smartphones.h"
#include "BinaryTreePhons.h"

using namespace std;

int main() {

    setlocale(LC_ALL, "rus");

    BinaryTreePhons phones;

    cout << "Выполнил студент группы ИПсп-121:\n" << endl;
    cout << "Аверкин Сергей Максимович" << endl;

    cout << "" << endl;


    int choice;
    do {
        // Выводим меню
        cout << "Выберите один из следующих пунктов:\n";
        cout << "1. Добавить новый телефон\n";
        cout << "2. Удалить смартфон по критериям\n";
        cout << "3. Проверить наличие смартфона по нескольким критериям\n";
        cout << "4. Вывести список имеющихся смартфонов\n";
        cout << "5. Выйти\n";
        cout << "Ввод: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string brand, model;
            double price, screen_size;
            cout << "Введите бренд смартфона: ";
            cin >> brand;
            cout << "Введите модель смартфона: ";
            cin >> model;
            cout << "Введите цену смартфона: ";
            cin >> price;
            cout << "Введите размер диагонали экрана смартфона: ";
            cin >> screen_size;
            phones.addSmartphone(Smartphone(brand, model, price, screen_size));
            break;
        }
        case 2: {
            double screen_size, price;
            cout << "Введите размер диагонали экрана смартфона для удаления: ";
            cin >> screen_size;
            cout << "Введите цену смартфона для удаления: ";
            cin >> price;
            phones.removeSmartphone(screen_size, price);
            break;
        }
        case 3: {
            double screen_size, price;
            cout << "Введите размер диагонали экрана смартфона для проверки наличия: ";
            cin >> screen_size;
            cout << "Введите цену смартфона для проверки наличия: ";
            cin >> price;
            if (phones.containsSmartphone(screen_size, price)) {
                cout << "По данным характеристикам в списке имеются следующие смартфоны:\n" << phones.containsSmartphone(screen_size, price);
                cout << "" << endl;
            }
            else {
                cout << "По данным характеристикам не найдено ни одного смартфона в списке.\n";
                cout << " " << endl;
            }
            break;
        }
        case 4: {
            vector<Smartphone> smartphones = phones.getAllSmartphones();
            cout << "Список смартфонов:\n";
            for (const auto& phone : smartphones) {
                cout << "Бренд:" << phone.brand << "\n Модель: " << phone.model << "\n Цена: " << phone.price << "\n Размер диагонали: " << phone.screen_size << endl;
                cout << " " << endl;
            }
            break;
        }
        case 5:
            cout << "Выход...\n";
            break;
        default:
            cout << "Ошибка! Введите цифру от 1 до 5.\n";
        }
    } while (choice != 5);

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
