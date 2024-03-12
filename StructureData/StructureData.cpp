#include <iostream>
#include <algorithm>
#include <locale>
#include <string>

using namespace std;


struct Participant

{
	unsigned short number;

	string name;

	string surname;

	string patronymic;

	string city;

	unsigned short age;

	string nameComand;

	bool result; // Либо победа - 1, либо поражение - 0, ничиьи нет

	unsigned short score;

};

//Участники соревнования: 1) место 2) имя 3) фамилия 4) отчество 5) город 6) возраст 7) название команды 8) результат 9) счёт

int correctNumber(int left, int right) {
	string numberInput;
	cout << "Введите целое число от " << left << " до " << right << ": ";
	int number = 0;
	cin >> numberInput;
	while (true)
	{
		try 
		{
			number = stoi(numberInput);
			if ((left <= number) && (number <= right)) 
			{
				return number;
			}
			else 
			{
				cout << "Ошибка ввода. Вам необходимо ввести целое число от " << left << " до " << right << endl;
				cout << "Введите целое число от " << left << " до " << right << ": ";
				cin >> numberInput;
			}
		}
		catch (invalid_argument) {
			cout << "Ошибка ввода. Вам необходимо ввести целое число от " << left << " до " << right << endl;
			cout << "Введите целое число от " << left << " до " << right << ": ";
			cin >> numberInput;
		}
	}
}

int** indexation(Participant participants[], int countParticipants, string index, string upOrDown)
{
	int** array = new int* [countParticipants];
	if (index == "number")
	{
		for (int i = 0; i < countParticipants; ++i)
		{
			array[i] = new int[2];
			array[i][0] = participants[i].number;
			array[i][1] = i;
		}
	}
	else if (index == "score")
	{
		for (int i = 0; i < countParticipants; ++i)
		{
			array[i] = new int[2];
			array[i][0] = participants[i].score;
			array[i][1] = i;
		}
	}
	if (upOrDown == "up") 
	{
		for (int i = 0; i < countParticipants; i++)
		{
			bool flag = true;
			for (int j = 0; j < countParticipants - (i + 1); j++)
			{
				if (array[j][0] > array[j + 1][0])
				{
					flag = false;
					swap(array[j], array[j + 1]);
				}
			}
			if (flag)
			{
				break;
			}
		}
	}
	else if (upOrDown == "down")
	{
		for (int i = 0; i < countParticipants; i++)
		{
			bool flag = true;
			for (int j = 0; j < countParticipants - (i + 1); j++)
			{
				if (array[j][0] < array[j + 1][0])
				{
					flag = false;
					swap(array[j], array[j + 1]);
				}
			}
			if (flag)
			{
				break;
			}
		}
	}
	return array;
};

int** indexation(Participant participants[], int countParticipants)
{
	int** array = new int* [countParticipants];
	for (int i = 0; i < countParticipants; ++i) {
		array[i] = new int[2];
	}
	int counter = 0;
	for (int i = 0; i < countParticipants; i++)
	{
		array[counter][0] = participants[i].number;
		array[counter][1] = i;
		counter++;
	}
	return array;
}

void writeParticipant(Participant participants[], int index)
{
	Participant p = participants[index];
	cout << "Номер: " << p.number << "; " << "Имя: " << p.name << "; " << "Фамилия: " << p.surname << "; " << "Отчество: " << p.patronymic << "; " << "Город: " << p.city << "; " << "Возраст: " << p.age << "; " << "Команда: " << p.nameComand << "; " << "Победа: " << p.result << "; " << "Счёт: " << p.score << endl;
}

void write(Participant participants[], int** arrayIndexation, int countParticipants)
{
	int index;
	for (int i = 0; i < countParticipants; i++)
	{
		index = arrayIndexation[i][1];
		writeParticipant(participants, index);
	}
}

int binarySearch(int** array, int size, int key) 
{
	int low = 0;
	int high = size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (array[mid][0] == key) {
			return array[mid][1];
		}
		else if (array[mid][0] > key) {
			high = mid - 1;
		}
		else 
		{
			low = mid + 1;
		}
	}
	return -1;
}


int binarySearchRecursive(int** array, int size, int key, int low, int high) 
{
	if (low > high) {
		return -1;
	}
	int mid = (low + high) / 2;
	if (array[mid][0] == key) {
		return array[mid][1];
	}
	else if (array[mid][0] > key) {
		return binarySearchRecursive(array, size, key, low, mid - 1);
	}
	else {
		return binarySearchRecursive(array, size, key, mid + 1, high);
	}
}



int main()
{
	locale::global(locale("ru_RU.UTF-8"));
	setlocale(LC_ALL, "Russian");
	int variant = 0;
	int size;
	Participant* participants = nullptr;
	int** arrayIndexationBasic = nullptr;
	int** arrayIndexationNumberUp = nullptr;
	int** arrayIndexationNumberDown = nullptr;
	int** arrayIndexationScoreUp = nullptr;
	int** arrayIndexationScoreDown = nullptr;
	unsigned short number;
	string name;
	string surname;
	string patronymic;
	string city;
	unsigned short age;
	string nameComand;
	bool result;
	unsigned short score;
	int indexFirst;
	int indexSecond;
	int countParticipants;
	int numberSearch;
	int scoreSearch;
	string trashAnswer;
	string message = "";
	bool arrayIsCreated = false;
	while (variant != 12)
	{
		system("cls");
		if (message != "")
		{
			cout << message << endl;
		};
		message = "";
		cout << "Выбирите, что необходимо сделать:\n"
			<< "1. Создать новый массив вручную\n"
			<< "2. Создать новый уже готовый тестовый массив\n"
			<< "3. Вывести существующий неотсортированный массив\n"
			<< "4. Вывести массив, отсортированный по номеру участника в порядке возрастания\n"
			<< "5. Вывести массив, отсортированный по номеру участника в порядке убывания\n"
			<< "6. Вывести массив, отсортированный по счёту участника в порядке возрастания\n"
			<< "7. Вывести массив, отсортированный по счёту участника в порядке убывания\n"
			<< "8. Найти участника с заданным номером\n"
			<< "9. Найти участника с заданным счётом\n"
			<< "10. Изменить информацию об участнике\n"
			<< "11. Удалить информацию об участнике\n"
			<< "12. Завершить работу\n";
		variant = correctNumber(1, 12);
		switch (variant)
		{
		case 1:
			system("cls");
			cout << "Введите количество элементов массива: ";
			cin >> size;
			countParticipants = size;
			participants = new Participant[size];
			for (int i = 0; i < size; i++)
			{
				cout << "Введите номер участника: ";
				cin >> number;
				cout << "Введите имя участника: ";
				cin >> name;
				cout << "Введите фамилию участника: ";
				cin >> surname;
				cout << "Введите отчество участника: ";
				cin >> patronymic;
				cout << "Введите город участника: ";
				cin >> city;
				cout << "Введите возраст участника: ";
				cin >> age;
				cout << "Введите имя команды участника: ";
				cin >> nameComand;
				cout << "Введите счёт участника: ";
				cin >> score;
				if (score > 200) {
					result = true;
				}
				else {
					result = false;
				}
				participants[i] = { number, name, surname, patronymic, city, age, nameComand, result, score};
				};
			arrayIndexationBasic = indexation(participants, countParticipants);
			arrayIndexationNumberUp = indexation(participants, countParticipants, "number", "up");
			arrayIndexationScoreUp = indexation(participants, countParticipants,  "score", "up");
			arrayIndexationNumberDown = indexation(participants, countParticipants, "number", "down");
			arrayIndexationScoreDown = indexation(participants, countParticipants, "score", "down");
			message = "Создан массив из введённых элементов. Мы можете увидеть его, выбрав соответствующую команду";
			arrayIsCreated = true;
			break;
		case 2:
			system("cls");
			participants = new Participant[5];
			countParticipants = 5;
			participants[0] = { 3, "Дмитрий", "Кондратиев", "Алексеевич", "Пермь", 20, "Авангард", true, 200 };
			participants[1] = { 2, "Егор", "Чертанов", "Владимирович", "Саранск", 30, "Пламя", true, 250 };
			participants[2] = { 4, "Тимофей", "Ломов", "Константинович", "Хабаровск", 23, "Вымпел", false, 150 };
			participants[3] = { 1, "Анатолий", "Леснов", "Евгеньевич", "Хабаровск", 24, "Вымпел", false, 100 };
			participants[4] = { 5, "Иван", "Дулин", "Александрович", "Красноярск", 20, "Молот", false, 199 };
			arrayIndexationBasic = indexation(participants, countParticipants);
			arrayIndexationNumberUp = indexation(participants, countParticipants, "number", "up");
			arrayIndexationScoreUp = indexation(participants, countParticipants, "score", "up");
			arrayIndexationNumberDown = indexation(participants, countParticipants, "number", "down");
			arrayIndexationScoreDown = indexation(participants, countParticipants, "score", "down");
			message = "Создан массив заданный по умолчанию. Мы можете увидеть его, выбрав соответствующую команду";
			arrayIsCreated = true;
			break;
		case 3:
			if (arrayIsCreated)
			{
				system("cls");
				cout << "Изначальные неотсортированные данные" << endl;
				write(participants, arrayIndexationBasic, countParticipants);
				cout << "\n" << "Введите что нибудь, чтобы вернуться в меню: ";
				cin >> trashAnswer;
			}
			else
			{
				message = "Вы ещё не создали массив";
			};
			break;
		case 4:
			if (arrayIsCreated)
			{
				system("cls");
				cout << "Массив, отсортированный по номеру участника в порядке возрастания" << endl;
				write(participants, arrayIndexationNumberUp, countParticipants);
				cout << "\n" << "Введите что нибудь, чтобы вернуться в меню: ";
				cin >> trashAnswer;
			}
			else
			{
				message = "Вы ещё не создали массив";
			};
			break;
		case 5:
			if (arrayIsCreated)
			{
				system("cls");
				cout << "Массив, отсортированный по номеру участника в порядке убывания" << endl;
				write(participants, arrayIndexationNumberDown, countParticipants);
				cout << "\n" << "Введите что нибудь, чтобы вернуться в меню: ";
				cin >> trashAnswer;
			}
			else
			{
				message = "Вы ещё не создали массив";
			};
			break;
		case 6:
			if (arrayIsCreated)
			{
				system("cls");
				cout << "Массив, отсортированный по счёту участника в порядке возрастания" << endl;
				write(participants, arrayIndexationScoreUp, countParticipants);
				cout << "\n" << "Введите что нибудь, чтобы вернуться в меню: ";
				cin >> trashAnswer;
			}
			else
			{
				message = "Вы ещё не создали массив";
			};
			break;
		case 7:
			if (arrayIsCreated)
			{
				system("cls");
				cout << "Массив, отсортированный по счёту участника в порядке убывания" << endl;
				write(participants, arrayIndexationScoreDown, countParticipants);
				cout << "\n" << "Введите что нибудь, чтобы вернуться в меню: ";
				cin >> trashAnswer;
			}
			else
			{
				message = "Вы ещё не создали массив";
			};
			break;
		case 8:
			if (arrayIsCreated)
			{
				system("cls");
				cout <<"Введите номер искомого элемента" ;
				numberSearch = correctNumber(1, 65535);
				indexFirst = binarySearch(arrayIndexationNumberUp, countParticipants, numberSearch);
				if (indexFirst == -1)
				{
					cout << "Элемента с таким номером нет" << endl;
				}
				else
				{
					writeParticipant(participants, indexFirst);
				};
				cout << "\n" << "Введите что нибудь, чтобы вернуться в меню: ";
				cin >> trashAnswer;	
			}
			else
			{
				message = "Вы ещё не создали массив";
			};
			break;
		case 9:
			if (arrayIsCreated)
			{
				system("cls");
				cout << "Введите счёт искомого элемента" << endl;
				scoreSearch = correctNumber(1, 65535);
				indexSecond = binarySearchRecursive(arrayIndexationScoreUp, countParticipants, scoreSearch, 0, countParticipants - 1);
				if (indexSecond == -1)
				{
					cout << "Элемента с таким счётом нет" << endl;
				}
				else
				{
					writeParticipant(participants, indexSecond);
				};
				cout << "\n" << "Введите что нибудь, чтобы вернуться в меню: ";
				cin >> trashAnswer;
			}
			else
			{
				message = "Вы ещё не создали массив";
			};
			break;
		case 10:
			if (arrayIsCreated)
			{
				system("cls");
				int numberChange;
				cout << "Введите номер элемента, который вы хотите изменить" << endl;
				numberChange = correctNumber(1, countParticipants);
				int indexForChange;
				for (int i = 0; i < countParticipants; i++)
				{
					if (participants[i].number == numberChange)
					{
						indexForChange = i;
					}
				}
				cout << "Введите номер игрока: ";
				cin >> number;
				cout << "Введите имя игрока: ";
				cin >> name;
				cout << "Введите фамилию игрока: ";
				cin >> surname;
				cout << "Введите отчество игрока: ";
				cin >> patronymic;
				cout << "Введите город игрока: ";
				cin >> city;
				cout << "Введите возраст игрока: ";
				cin >> age;
				cout << "Введите имя команды игрока: ";
				cin >> nameComand;
				cout << "Введите счёт игрока: ";
				cin >> score;
				if (score > 200) {
					result = true;
				}
				else {
					result = false;
				}
				participants[indexForChange] = { number, name, surname, patronymic, city, age, nameComand, result, score };
				arrayIndexationBasic = indexation(participants, countParticipants);
				arrayIndexationNumberUp = indexation(participants, countParticipants, "number", "up");
				arrayIndexationScoreUp = indexation(participants, countParticipants, "score", "up");
				arrayIndexationNumberDown = indexation(participants, countParticipants, "number", "down");
				arrayIndexationScoreDown = indexation(participants, countParticipants, "score", "down");
				message = "Один из элементов массива изменился. Мы можете увидеть новый массив, выбрав соответствующую команду";
			}
			else
			{
				message = "Вы ещё не создали массив";
			};
			break;
		case 11:
			if (arrayIsCreated)
			{
				system("cls");
				int numberDelete;
				cout << "Введите номер элемента, который вы хотите удалить" << endl;
				numberDelete = correctNumber(1, countParticipants);
				int indexDelete;
				for (int i = 0; i < countParticipants; i++)
				{
					if (participants[i].number == numberDelete) {
						indexDelete = i;
					}
				}
				participants[indexDelete].number = NULL;
				participants[indexDelete].name = "NULL";
				participants[indexDelete].surname = "NULL";
				participants[indexDelete].patronymic = "NULL";
				participants[indexDelete].city = "NULL";
				participants[indexDelete].age = NULL;
				participants[indexDelete].nameComand = "NULL";
				participants[indexDelete].result = false;
				participants[indexDelete].score = NULL;
				arrayIndexationBasic = indexation(participants, countParticipants);
				arrayIndexationNumberUp = indexation(participants, countParticipants, "number", "up");
				arrayIndexationScoreUp = indexation(participants, countParticipants, "score", "up");
				arrayIndexationNumberDown = indexation(participants, countParticipants, "number", "down");
				arrayIndexationScoreDown = indexation(participants, countParticipants, "score", "down");
				message = "Один из элементов был удалён. Мы можете увидеть новый массив, выбрав соответствующую команду";
			}
			else
			{
				message = "Вы ещё не создали массив";
			};
			break;
		case 12:
			system("cls");
			cout << "Завершаем работу" << endl;
		default:
			cout << "Wrong option!\n";
			break;
		}
	}
}