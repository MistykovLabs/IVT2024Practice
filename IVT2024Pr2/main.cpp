#include "header.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    AuthenticationLibrary authLib;

    // Регистрация пользователя
    UserCredentials* user = authLib.registration();

    // Авторизация пользователя и функции доступные только при успешной авторизации
    if (user != nullptr && authLib.authorization(user)) {

        // Меню открывается после авторизации
        int choice = 0;
        do {
            cout << "\n";
            cout << "Меню: \n";
            cout << "1. Ввод произвольного параметра \n";
            cout << "2. Получение параметров системы \n";
            cout << "3. Выход \n";
            cout << "Введите свой выбор: ";
            while (!(cin >> choice)) {
                cout << "Ошибка: Введите число. \n";
                cin.clear();
                cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // ignore
                cout << "Выберите существующий пункт меню: ";
            }
            cout << "\n";

            switch (choice) 
            {
                case 1: {
                    // Установка произвольного параметра
                    string otherParam = authLib.requestOtherParameters();
                    cout << "Введите произвольный параметр: " << otherParam << endl;
                    break;
                }
                case 2: {
                    // Получение параметров системы
                    cout << std::system("systeminfo") << endl;
                    break;
                }
                case 3: {
                    // Выход из меню.
                    cout << "Выход... \n";
                    delete user;
                    break;
                }
                default:
                    cout << "Неверный выбор. \n";
                    break;
            }  
        } while (choice != 3);
    }

    return 0;
}