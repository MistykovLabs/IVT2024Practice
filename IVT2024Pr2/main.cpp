#include "header.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    AuthenticationLibrary authLib;

    // ����������� ������������
    UserCredentials* user = authLib.registration();

    // ����������� ������������ � ������� ��������� ������ ��� �������� �����������
    if (user != nullptr && authLib.authorization(user)) {

        // ���� ����������� ����� �����������
        int choice = 0;
        do {
            cout << "\n";
            cout << "����: \n";
            cout << "1. ���� ������������� ��������� \n";
            cout << "2. ��������� ���������� ������� \n";
            cout << "3. ����� \n";
            cout << "������� ���� �����: ";
            while (!(cin >> choice)) {
                cout << "������: ������� �����. \n";
                cin.clear();
                cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // ignore
                cout << "�������� ������������ ����� ����: ";
            }
            cout << "\n";

            switch (choice) 
            {
                case 1: {
                    // ��������� ������������� ���������
                    string otherParam = authLib.requestOtherParameters();
                    cout << "������� ������������ ��������: " << otherParam << endl;
                    break;
                }
                case 2: {
                    // ��������� ���������� �������
                    cout << std::system("systeminfo") << endl;
                    break;
                }
                case 3: {
                    // �����
                    cout << "�����... \n";
                    delete user;
                    break;
                }
                default:
                    cout << "�������� �����. \n";
                    break;
            }  
        } while (choice != 3);
    }

    return 0;
}