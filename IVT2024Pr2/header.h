// Version 2024.07.05

#pragma once

#include <iostream>
#include <string>
#include <random>
#include <windows.h>
#include <clocale>

using namespace std;

// ������� ����� ��� ��������� � �������� �����
class Captcha {
public:
    virtual string generateCaptcha() = 0;
    virtual bool verifyCaptcha(const string& input) = 0;
};

// ����� ��� ������� ��������� �����
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

// ������� ����� ��� �������� ������� ������
class Credentials {
public:
    virtual bool isValid() = 0;
};

// ����� ��� �������� ������ � ������
class UserCredentials : public Credentials {
private:
    string login;
    string password;

public:
    UserCredentials(const string& login, const string& password) : login(login), password(password) {}

    bool isValid() override {
        // ������� ��������: ����� � ������ �� ������
        return !login.empty() && !password.empty();
    }

    const string& getLogin() const { return login; }
    const string& getPassword() const { return password; }
};

// ����� ��� �������������� � �������������
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

// �������� ����� ���������� � ���������
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

    // ����������� ������������
    UserCredentials* registration() {
        cout << "���� �����������" << endl;
        string login = userInterface->requestInput("���������� �����: ");
        string password = userInterface->requestInput("���������� ������: ");

        UserCredentials* credentials = new UserCredentials(login, password);
        if (credentials->isValid()) {
            system("cls"); //1
            userInterface->showMessage("����������� ������ �������!");
            return credentials;
        }
        else {
            system("cls"); //1
            userInterface->showMessage("������������ ������!");
            delete credentials;
            return nullptr;
        }
    }

    // ����������� ������������
    bool authorization(UserCredentials* credentials) {
        cout << "���� �����������" << endl;
        string login = userInterface->requestInput("������� �����: ");
        string password = userInterface->requestInput("������� ������: ");

        if ((login == credentials->getLogin()) && (password == credentials->getPassword())) {
            string captcha = captchaGenerator->generateCaptcha();
            string captchaInput = userInterface->requestInput("������� ����� (" + captcha + "): ");

            if (captchaGenerator->verifyCaptcha(captchaInput)) {
                userInterface->showMessage("����������� �������!");
                return true;
            }
            else {
                userInterface->showMessage("�������� �����!");
            }
        }
        else {
            userInterface->showMessage("�������� ����� ��� ������!");
        }
        return false;
    }

    // ������ ������������ ���������� (������)
    string requestOtherParameters() {
        return userInterface->requestInput("������� ������������ ��������: ");
    }
};
