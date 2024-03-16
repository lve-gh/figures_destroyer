#include "SimpleEngineCore/Interface.hpp"

namespace SimpleEngine {
	std::vector<GLfloat> Interface() {
		using std::cout;
		using std::endl;
		using std::cin;
		using std::sort;

		int destiny[2];
		int weight[2];
		int speed[2];
		int debris[2];
		int distance = 1;
		int userChoice = 0;
		int trottil = 0;
		std::vector<GLfloat> parametres;

		while (userChoice != quit) { // �������� enum
			cout << "1 - ������������ ���� ��������" << endl;
			cout << "2 - ������ �������" << endl;
			cout << "3 - �����" << endl;
			//cin >> userChoice; // �������� ��������
			userChoice = GetInt();
			if (!parametres.empty())
				parametres.clear();
			switch (userChoice)
			{
			case experience1:
				cout << "�������� �������� ������� �������:" << endl;
				ShowMaterials();
				//cin >> destiny[0];
				do {
					destiny[0] = GetInt();
					if (!(destiny[0] >= 1 && destiny[0] <= 26))
						cout << "�������� �����" << endl;
				} while (!(destiny[0] >= 1 && destiny[0] <= 26));
				destiny[0] = Materials(destiny[0]);
				cout << "������� ����� ������� ������� (� ��)" << endl;
				do {
					weight[0] = GetInt();
					if (weight[0] <= 0)
						cout << "������ �������� �����" << endl;
				} while (weight[0] <= 0);
				cout << "������� �������� ������� ������� (� �/�)" << endl;
				do {
					speed[0] = GetInt();
					if (speed[0] < 0)
						cout << "������ �������� �����" << endl;
				} while (speed[0] < 0);
				cout << "�������� �������� ������� �������:" << endl;
				ShowMaterials();
				do {
					destiny[1] = GetInt();
					if (!(destiny[1] >= 1 && destiny[1] <= 26))
						cout << "�������� �����" << endl;
				} while (!(destiny[1] >= 1 && destiny[1] <= 26));
				destiny[1] = Materials(destiny[1]);
				cout << "������� ����� ������� ������� (� ��)" << endl;
				do {
					weight[1] = GetInt();
					if (weight[1] <= 0)
						cout << "������ �������� �����" << endl;
				} while (weight[1] <= 0);
				cout << "������� �������� ������� ������� (� �/c)" << endl;
				//speed[1] = GetInt();
				do {
					speed[1] = GetInt();
					if (speed[1] < 0)
						cout << "������ �������� �����" << endl;
				} while (speed[1] < 0);
				cout << "������� ����������  �������� �� ������ (� �)" << endl;
				//cin >> distance;
				distance = GetInt();
				debris[0] = (speed[0] + 1) * (speed[1] + 1) / (weight[0] * (destiny[0] / 10000 + 1));
				debris[1] = (speed[0] + 1) * (speed[1] + 1) / (weight[1] * (destiny[1] / 10000 + 1));
				userChoice = 0;
				parametres.push_back(1);
				parametres.push_back(debris[0]);
				parametres.push_back(debris[1]);
				parametres.push_back(speed[0]);
				parametres.push_back(speed[1]);
				parametres.push_back(distance);
				//cout << "*" << debris[0] << "}" << debris[1] << endl;
				return parametres;
				break;
			case experience2:
				cout << "�������� �������� ������� �������:" << endl;
				ShowMaterials();
				//cin >> destiny[0];
				do {
					destiny[0] = GetInt();
					if (!(destiny[0] >= 1 && destiny[0] <= 26))
						cout << "�������� �����" << endl;
				} while (!(destiny[0] >= 1 && destiny[0] <= 26));
				destiny[0] = Materials(destiny[0]);
				cout << "������� ����� ������� ������� (� ��)" << endl;
				//cin >> weight[0];
				do {
					weight[0] = GetInt();
					if (weight[0] <= 0)
						cout << "������ �������� �����" << endl;
				} while (weight[0] <= 0);
				cout << "������� ����������� ����������, �������� ����� ��������� ������ (� �)" << endl;
				//cin >> trottil;
				do {
					trottil = GetInt();
					if (trottil <= 0)
						cout << "������ �������� �����." << endl;
				} while (trottil <= 0);
				debris[0] = (2 * trottil * trottil) / (destiny[0] * weight[0]);
				//cout << "������� ����� �������, ����� �������� �����������" << endl;
				userChoice = 0;
				//return 2;
				parametres.push_back(2);
				parametres.push_back(debris[0]);
				parametres.push_back(destiny[0]);
				parametres.push_back(weight[0]);
				parametres.push_back(trottil);
				return parametres;
				break;
			case quit:
				parametres.push_back(0);
				return parametres;
			case 100:
				cout << "����� ���������� �����." << endl;
				speed[0] = 3;
				speed[1] = 3;
				weight[0] = 3;
				weight[1] = 3;
				destiny[0] = 900;
				destiny[1] = 900;
				distance = 3;
				cout << "��������� ������� �������:" << endl;
				cout << "���������:" << destiny[0] << endl;
				cout << "C�������:" << speed[0] << endl;
				cout << "�����:" << weight[0] << endl << endl;

				cout << "��������� ������� �������:" << endl;
				cout << "���������:" << destiny[1] << endl;
				cout << "C�������:" << speed[1] << endl;
				cout << "�����:" << weight[1] << endl << endl;
				debris[0] = (speed[0] + 1) * (speed[1] + 1) / (weight[0] * (destiny[0] / 10000 + 1));
				debris[1] = (speed[0] + 1) * (speed[1] + 1) / (weight[1] * (destiny[1] / 10000 + 1));
				cout << "��������� ���������� ������� �������:" << debris[0] << endl;
				cout << "��������� ���������� ������� �������:" << debris[1] << endl;
				parametres.push_back(1);
				parametres.push_back(debris[0]);
				parametres.push_back(debris[1]);
				parametres.push_back(speed[0]);
				parametres.push_back(speed[1]);
				parametres.push_back(distance);
				return parametres;
				break;
			default:
				cout << "����� ���� �� ����������" << endl;
				userChoice = 0;
				continue;
			}
		}
	}

	int Materials(int number) {
		switch (number)
		{
		case 1:
			return 400;
			break;
		case 2:
			return 700;
			break;
		case 3:
			return 900;
			break;
		case 4:
			return 900;
			break;
		case 5:
			return 1100;
			break;
		case 6:
			return 1200;
			break;
		case 7:
			return 1600;
			break;
		case 8:
			return 1800;
			break;
		case 9:
			return 1800;
			break;
		case 10:
			return 2300;
			break;
		case 11:
			return 2500;
			break;
		case 12:
			return 2700;
			break;
		case 13:
			return 2700;
			break;
		case 14:
			return 4000;
			break;
		case 15:
			return 7000;
			break;
		case 16:
			return 7100;
			break;
		case 17:
			return 7300;
			break;
		case 18:
			return 7800;
			break;
		case 19:
			return 8500;
			break;
		case 20:
			return 8900;
			break;
		case 21:
			return 10500;
			break;
		case 22:
			return 11300;
			break;
		case 23:
			return 19300;
			break;
		case 24:
			return 21500;
			break;
		case 25:
			return 22400;
			break;
		case 26:
			return 22600;
			break;
		default:
			//std::cout << "����� �������� �����" << std::endl;
			return -1;
			break;
		}
	}

	void ShowMaterials() {
		using std::cout;
		using std::endl;
		using std::cin;
		cout << "1 - �����" << endl;
		cout << "2 - ���" << endl;
		cout << "3 - ˸�" << endl;
		cout << "4 - �������" << endl;
		cout << "5 - ������" << endl;
		cout << "6 - ���������" << endl;
		cout << "7 - �����-�������" << endl;
		cout << "8 - ������" << endl;
		cout << "9 - �����" << endl;
		cout << "10 - ������" << endl;
		cout << "11 - ������ �������" << endl;
		cout << "12 - ������" << endl;
		cout << "13 - ���������" << endl;
		cout << "14 - ������" << endl;
		cout << "15 - �����" << endl;
		cout << "16 - ����" << endl;
		cout << "17 - �����" << endl;
		cout << "18 - �����" << endl;
		cout << "19 - ������" << endl;
		cout << "20 - ����" << endl;
		cout << "21 - �������" << endl;
		cout << "22 - ������" << endl;
		cout << "23 - ������" << endl;
		cout << "24 - �������" << endl;
		cout << "25 - ������" << endl;
		cout << "26 - �����" << endl;
	}

	int GetInt() {
		int userInput;
		std::cin >> userInput;
		if (std::cin.fail()) {
			//std::cout << "������:������� �����" << std::endl;
			while (std::cin.fail()) {
				std::cout << "������ �������� �����" << std::endl;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cin >> userInput;
			}
		}
		std::cin.ignore(INT_MAX, '\n');
		return userInput;
	}
}
