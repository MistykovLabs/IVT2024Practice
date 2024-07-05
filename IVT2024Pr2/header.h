// Version 2024.07.05

#pragma once

#include <iostream>
#include <string>
#include <random>
#include <windows.h>
#include <clocale>

using namespace std;

// Базовый класс для генерации и проверки капчи
class Captcha {
public:
    virtual string generateCaptcha() = 0;
    virtual bool verifyCaptcha(const string& input) = 0;
};

// Класс для простой текстовой капчи
class TextCaptcha : public Captcha {
private:
    string captchaText;

public:
    string generateCaptcha() override {
        captchaText = generateRandomString(5);
        return captchaText;
    }

    bool verifyCaptcha(const string& input) override {
        return input == captchaText;
    }

private:
    string generateRandomString(int length) {
        string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> distribution(0, chars.size() - 1);

        string randomString;
        for (int i = 0; i < length; ++i) {
            randomString += chars[distribution(generator)];
        }
        return randomString;
    }
};

// Базовый класс для хранения учетных данных
class Credentials {
public:
    virtual bool isValid() = 0;
};

// Класс для хранения логина и пароля
class UserCredentials : public Credentials {
private:
    string login;
    string password;

public:
    UserCredentials(const string& login, const string& password) : login(login), password(password) {}

    bool isValid() override {
        // Простая проверка: логин и пароль не пустые
        return !login.empty() && !password.empty();
    }

    const string& getLogin() const { return login; }
    const string& getPassword() const { return password; }
};

// Класс для взаимодействия с пользователем
class UserInterface {
public:
    string requestInput(const string& message) {
        cout << message;
        string input;
        cin >> input;
        return input;
    }

    void showMessage(const string& message) {
        cout << message << endl;
    }
};

// Основной класс библиотеки с функциями
class AuthenticationLibrary {
private:
    Captcha* captchaGenerator;
    UserInterface* userInterface;

public:
    AuthenticationLibrary() {
        captchaGenerator = new TextCaptcha();
        userInterface = new UserInterface();
    }

    ~AuthenticationLibrary() {
        delete captchaGenerator;
        delete userInterface;
    }

    // Регистрация пользователя
    UserCredentials* registration() {
        cout << "Окно регистрации" << endl;
        string login = userInterface->requestInput("Придумайте логин: ");
        string password = userInterface->requestInput("Придумайте пароль: ");

        UserCredentials* credentials = new UserCredentials(login, password);
        if (credentials->isValid()) {
            system("cls"); //1
            userInterface->showMessage("Регистрация прошла успешно!");
            return credentials;
        }
        else {
            system("cls"); //1
            userInterface->showMessage("Некорректные данные!");
            delete credentials;
            return nullptr;
        }
    }

    // Авторизация пользователя
    bool authorization(UserCredentials* credentials) {
        cout << "Окно авторизации" << endl;
        string login = userInterface->requestInput("Введите логин: ");
        string password = userInterface->requestInput("Введите пароль: ");

        if ((login == credentials->getLogin()) && (password == credentials->getPassword())) {
            string captcha = captchaGenerator->generateCaptcha();
            string captchaInput = userInterface->requestInput("Введите капчу (" + captcha + "): ");

            if (captchaGenerator->verifyCaptcha(captchaInput)) {
                userInterface->showMessage("Авторизация успешна!");
                return true;
            }
            else {
                userInterface->showMessage("Неверная капча!");
            }
        }
        else {
            userInterface->showMessage("Неверный логин или пароль!");
        }
        return false;
    }

    // Запрос произвольных параметров (пример)
    string requestOtherParameters() {
        return userInterface->requestInput("Введите произвольный параметр: ");
    }
};
