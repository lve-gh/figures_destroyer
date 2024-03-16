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

		while (userChoice != quit) { // добавить enum
			cout << "1 - Столкновение двух объектов" << endl;
			cout << "2 - Подрыв объекта" << endl;
			cout << "3 - Выход" << endl;
			//cin >> userChoice; // добавить проверку
			userChoice = GetInt();
			if (!parametres.empty())
				parametres.clear();
			switch (userChoice)
			{
			case experience1:
				cout << "Выберите материал первого объекта:" << endl;
				ShowMaterials();
				//cin >> destiny[0];
				do {
					destiny[0] = GetInt();
					if (!(destiny[0] >= 1 && destiny[0] <= 26))
						cout << "Неверный пункт" << endl;
				} while (!(destiny[0] >= 1 && destiny[0] <= 26));
				destiny[0] = Materials(destiny[0]);
				cout << "Задайте массу первого объекта (в кг)" << endl;
				do {
					weight[0] = GetInt();
					if (weight[0] <= 0)
						cout << "Ошибка введения числа" << endl;
				} while (weight[0] <= 0);
				cout << "Задайте скорость первого объекта (в м/с)" << endl;
				do {
					speed[0] = GetInt();
					if (speed[0] < 0)
						cout << "Ошибка введения числа" << endl;
				} while (speed[0] < 0);
				cout << "Выберите материал второго объекта:" << endl;
				ShowMaterials();
				do {
					destiny[1] = GetInt();
					if (!(destiny[1] >= 1 && destiny[1] <= 26))
						cout << "Неверный пункт" << endl;
				} while (!(destiny[1] >= 1 && destiny[1] <= 26));
				destiny[1] = Materials(destiny[1]);
				cout << "Задайте массу второго объекта (в кг)" << endl;
				do {
					weight[1] = GetInt();
					if (weight[1] <= 0)
						cout << "Ошибка введения числа" << endl;
				} while (weight[1] <= 0);
				cout << "Задайте скорость второго объекта (в м/c)" << endl;
				//speed[1] = GetInt();
				do {
					speed[1] = GetInt();
					if (speed[1] < 0)
						cout << "Ошибка введения числа" << endl;
				} while (speed[1] < 0);
				cout << "Введите расстояние  объектов от центра (в м)" << endl;
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
				cout << "Выберите материал первого объекта:" << endl;
				ShowMaterials();
				//cin >> destiny[0];
				do {
					destiny[0] = GetInt();
					if (!(destiny[0] >= 1 && destiny[0] <= 26))
						cout << "Неверный пункт" << endl;
				} while (!(destiny[0] >= 1 && destiny[0] <= 26));
				destiny[0] = Materials(destiny[0]);
				cout << "Задайте массу первого объекта (в кг)" << endl;
				//cin >> weight[0];
				do {
					weight[0] = GetInt();
					if (weight[0] <= 0)
						cout << "Ошибка введения числа" << endl;
				} while (weight[0] <= 0);
				cout << "Введите троттиловый эквивалент, которому будет подвержен объект (в г)" << endl;
				//cin >> trottil;
				do {
					trottil = GetInt();
					if (trottil <= 0)
						cout << "Ошибка введения числа." << endl;
				} while (trottil <= 0);
				debris[0] = (2 * trottil * trottil) / (destiny[0] * weight[0]);
				//cout << "Нажмите любую клавишу, чтобы провести эксперимент" << endl;
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
				cout << "Режим модульного теста." << endl;
				speed[0] = 3;
				speed[1] = 3;
				weight[0] = 3;
				weight[1] = 3;
				destiny[0] = 900;
				destiny[1] = 900;
				distance = 3;
				cout << "Параметры первого объекта:" << endl;
				cout << "Плотность:" << destiny[0] << endl;
				cout << "Cкорость:" << speed[0] << endl;
				cout << "Масса:" << weight[0] << endl << endl;

				cout << "Параметры второго объекта:" << endl;
				cout << "Плотность:" << destiny[1] << endl;
				cout << "Cкорость:" << speed[1] << endl;
				cout << "Масса:" << weight[1] << endl << endl;
				debris[0] = (speed[0] + 1) * (speed[1] + 1) / (weight[0] * (destiny[0] / 10000 + 1));
				debris[1] = (speed[0] + 1) * (speed[1] + 1) / (weight[1] * (destiny[1] / 10000 + 1));
				cout << "Ожидаемые разрушения первого объекта:" << debris[0] << endl;
				cout << "Ожидаемые разрушения второго объекта:" << debris[1] << endl;
				parametres.push_back(1);
				parametres.push_back(debris[0]);
				parametres.push_back(debris[1]);
				parametres.push_back(speed[0]);
				parametres.push_back(speed[1]);
				parametres.push_back(distance);
				return parametres;
				break;
			default:
				cout << "Пункт меню не существует" << endl;
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
			//std::cout << "Введён неверный пункт" << std::endl;
			return -1;
			break;
		}
	}

	void ShowMaterials() {
		using std::cout;
		using std::endl;
		using std::cin;
		cout << "1 - Сосна" << endl;
		cout << "2 - Дуб" << endl;
		cout << "3 - Лёд" << endl;
		cout << "4 - Парафин" << endl;
		cout << "5 - Капрон" << endl;
		cout << "6 - Оргстекло" << endl;
		cout << "7 - Сахар-рафинад" << endl;
		cout << "8 - Кирпич" << endl;
		cout << "9 - Бетон" << endl;
		cout << "10 - Фарфор" << endl;
		cout << "11 - Стекло оконное" << endl;
		cout << "12 - Мрамор" << endl;
		cout << "13 - Аллюминий" << endl;
		cout << "14 - Корунд" << endl;
		cout << "15 - Чугун" << endl;
		cout << "16 - Цинк" << endl;
		cout << "17 - Олово" << endl;
		cout << "18 - Сталь" << endl;
		cout << "19 - Латунь" << endl;
		cout << "20 - Медь" << endl;
		cout << "21 - Серебро" << endl;
		cout << "22 - Свинец" << endl;
		cout << "23 - Золото" << endl;
		cout << "24 - Платина" << endl;
		cout << "25 - Иридий" << endl;
		cout << "26 - Осмий" << endl;
	}

	int GetInt() {
		int userInput;
		std::cin >> userInput;
		if (std::cin.fail()) {
			//std::cout << "Ошибка:введите число" << std::endl;
			while (std::cin.fail()) {
				std::cout << "Ошибка введения числа" << std::endl;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cin >> userInput;
			}
		}
		std::cin.ignore(INT_MAX, '\n');
		return userInput;
	}
}
