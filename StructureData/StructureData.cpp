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
			if ((left <= number) & (number <= right)) 
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

int** indexation(Participant participants[], string index, string upOrDown)
{
	int size = sizeof(participants);
	int** array = new int* [size];
	size = size / 2;
	for (int i = 0; i < size; ++i) {
		array[i] = new int[2];
	}
	int indexs[sizeof(participants)];
	int counter = 0;
	for (int i = 0; i < size; i++)
	{
		int min = 1111111111;
		int max = -1111111111;
		int indexMin;
		int indexMax;
		if (upOrDown == "up") 
		{
			for (int i = 0; i < size; i++)
			{
				if (index == "number")
				{
					if ((participants[i].number < min) && !(find(begin(indexs), end(indexs), i) != end(indexs)))
					{
						min = participants[i].number;
						indexMin = i;
					}
				}
				else if (index == "score")
				{
					if ((participants[i].score < min) && !(find(begin(indexs), end(indexs), i) != end(indexs)))
					{
						min = participants[i].score;
						indexMin = i;
					}
				}
			}
			array[counter][0] = min;
			array[counter][1] = indexMin;
			indexs[counter] = indexMin;
			counter++;
		}
		else if (upOrDown == "down")
		{
			for (int i = 0; i < size; i++)
			{
				if (index == "number")
				{
					if ((participants[i].number > max) && !(find(begin(indexs), end(indexs), i) != end(indexs)))
					{
						max = participants[i].number;
						indexMax = i;
					}
				}
				else if (index == "score")
				{
					if ((participants[i].score > max) && !(find(begin(indexs), end(indexs), i) != end(indexs)))
					{
						max = participants[i].score;
						indexMax = i;
					}
				}
			}
			array[counter][0] = max;
			array[counter][1] = indexMax;
			indexs[counter] = indexMax;
			counter++;
		}
	}
	return array;
};

int** indexation(Participant participants[])
{
	int size = sizeof(participants);
	int** array = new int* [size];
	size = size / 2;
	for (int i = 0; i < size; ++i) {
		array[i] = new int[2];
	}
	int counter = 0;
	for (int i = 0; i < size; i++)
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

void write(Participant participants[], int** arrayIndexation)
{
	for (int i = 0; i < sizeof(participants) / 2; i++) 
	{
		int index = arrayIndexation[i][1];
		writeParticipant(participants, index);
	}
}

int binarySearch(int** array, int size, int key, string upOrDown) 
{
	int low = 0;
	int high = size - 1;
	if (upOrDown == "up") 
	{
		while (low <= high) {
			int mid = (low + high) / 2;
			if (array[mid][0] == key) {
				return array[mid][1];
			}
			else if (array[mid][0] > key) {
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
	}
	else if (upOrDown == "down")
	{
		while (low <= high) {
			int mid = (low + high) / 2;
			if (array[mid][0] == key) {
				return array[mid][1];
			}
			else if (array[mid][0] < key) {
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
	}
	return -1;
}


int binarySearchRecursive(int** array, int size, int key, int low, int high, string upOrDown) 
{
	if (upOrDown == "up") 
	{
		if (low > high) {
			return -1;
		}
		int mid = (low + high) / 2;
		if (array[mid][0] == key) {
			return array[mid][1];
		}
		else if (array[mid][0] > key) {
			return binarySearchRecursive(array, size, key, low, mid - 1, upOrDown);
		}
		else {
			return binarySearchRecursive(array, size, key, mid + 1, high, upOrDown);
		}
	}
	else if (upOrDown == "down") 
	{
		if (low > high) {
			return -1;
		}
		int mid = (low + high) / 2;
		if (array[mid][0] == key) {
			return array[mid][1];
		}
		else if (array[mid][0] < key) {
			return binarySearchRecursive(array, size, key, low, mid - 1, upOrDown);
		}
		else {
			return binarySearchRecursive(array, size, key, mid + 1, high, upOrDown);
		}
	}
}



int main()
{
	locale::global(locale("ru_RU.UTF-8"));
	setlocale(LC_ALL, "Russian");
	//int variant = 0;
	//int size;
	//Participant* participants = nullptr;
	//int** arrayIndexationBasic = nullptr;
	//unsigned short number;
	//string name;
	//string surname;
	//string patronymic;
	//string city;
	//unsigned short age;
	//string nameComand;
	//bool result;
	//unsigned short score;
	//while (variant != 12)
	//{
	//	//system("cls");
	//	cout << "Выбирите, что необходимо сделать:\n"
	//		<< "1. Создать новый массив вручную\n"
	//		<< "2. Создать новый уже готовый тестоый массив\n"
	//		<< "3. Вывести существующий неотсортированный массив\n"
	//		<< "4. Вывести массив, отсортированный по номеру участника в порядке возрастания\n"
	//		<< "5. Вывести массив, отсортированный по номеру участника в порядке убывания\n"
	//		<< "6. Вывести массив, отсортированный по счёту участника в порядке возрастания\n"
	//		<< "7. Вывести массив, отсортированный по счёту участника в порядке убывания\n"
	//		<< "8. Найти участника с заданным номером\n"
	//		<< "9. Найти участника с заданным счётом\n"
	//		<< "10. Изменить информацию об участнике\n"
	//		<< "11. Удалить информацию об участнике\n"
	//		<< "12. Завершить работу\n";
	//	variant = correctNumber(1, 12);
	//	switch (variant)
	//	{
	//	case 1:
	//		system("cls");
	//		cout << "Введите количество элементов массива: ";
	//		cin >> size;
	//		participants = new Participant[size];
	//		for (int i = 0; i < size; i++)
	//		{
	//			cout << "Введите номер участника: ";
	//			cin >> number;
	//			cout << "Введите имя участника: ";
	//			cin >> name;
	//			cout << "Введите фамилию участника: ";
	//			cin >> surname;
	//			cout << "Введите отчество участника: ";
	//			cin >> patronymic;
	//			cout << "Введите город участника: ";
	//			cin >> city;
	//			cout << "Введите возраст участника: ";
	//			cin >> age;
	//			cout << "Введите имя команды участника: ";
	//			cin >> nameComand;
	//			cout << "Введите счёт участника: ";
	//			cin >> score;
	//			if (score > 200) {
	//				result = true;
	//			}
	//			else {
	//				result = false;
	//			}
	//			participants[i] = { number, name, surname, patronymic, city, age, nameComand, result, score};
	//			};
	//		int** arrayIndexationBasic = indexation(participants);
	//		break;
	//	case 2:
	//		/*Participant participants[4] = {{3, "Дмитрий", "Кондратиев", "Алексеевич", "Пермь", 20, "Авангард", true, 200},
	//								{2, "Егор", "Чертанов", "Владимирович", "Саранск", 30, "Пламя", true, 250}, 
	//								{4, "Тимофей", "Ломов", "Константинович", "Хабаровск", 23, "Вымпел", false, 150},
	//								{1, "Анатолий", "Леснов", "Евгеньевич", "Хабаровск", 24, "Вымпел", false, 100} };*/
	//		break;
	//	case 3:
	//		cout << "Изначальные неотсортированные данные" << endl;
	//		write(participants, arrayIndexationBasic);
	//		break;
	//	default:
	//		cout << "Wrong option!\n";
	//		break;
	//	}
	//}
	int countParticipants = 4;
	Participant participants[4] = {{3, "Дмитрий", "Кондратиев", "Алексеевич", "Пермь", 20, "Авангард", true, 200},
									{2, "Егор", "Чертанов", "Владимирович", "Саранск", 30, "Пламя", true, 250}, 
									{4, "Тимофей", "Ломов", "Константинович", "Хабаровск", 23, "Вымпел", false, 150},
									{1, "Анатолий", "Леснов", "Евгеньевич", "Хабаровск", 24, "Вымпел", false, 100} };
	int** arrayIndexationBasic = indexation(participants);
	int** arrayIndexationNumber = indexation(participants, "number", "up");
	//for (int i = 0; i < 4; i++)
	//{
	//	cout << "[ " << arrayIndexationNumber[i][0] << "; " << arrayIndexationNumber[i][1] << " ]" << endl;
	//}
	int** arrayIndexationScore = indexation(participants, "score", "down");
	//for (int i = 0; i < 4; i++)
	//{
	//	cout << "[ " << arrayIndexationScore[i][0] << "; " << arrayIndexationScore[i][1] << " ]" << endl;
	//}
	cout << "Изначальные неотсортированные данные" << endl;
	write(participants, arrayIndexationBasic);
	cout << "Данные отсортированные по номеру в порядке возрастания" << endl;
	write(participants, arrayIndexationNumber);
	cout << "Данные отсортированные по счёту в порядке убывания" << endl;
	write(participants, arrayIndexationScore);
	int numberSearch;
	cout <<"Введите номер искомого элемента: ";
	cin >> numberSearch;
	int indexFirst = binarySearch(arrayIndexationNumber, sizeof(arrayIndexationNumber) / 2, numberSearch, "up");
	if (indexFirst == -1)
	{
		cout << "Элемента с таким номером нет" << endl;
	}
	else
	{
		writeParticipant(participants, indexFirst);
	};
	int scoreSearch;
	cout << "Введите счёт искомого элемента: ";
	cin >> scoreSearch;
	int indexSecond = binarySearchRecursive(arrayIndexationScore, sizeof(arrayIndexationScore) / 2, scoreSearch, 0, sizeof(arrayIndexationScore) - 1, "down");
	if (indexSecond == -1)
	{
		cout << "Элемента с таким счётом нет" << endl;
	}
	else
	{
		writeParticipant(participants, indexSecond);
	};
	int numberChange;
	cout << "Если вы не хотите менять аргумент элемента, то просто нажмите enter" << endl;
	cout << "Введите номер элемента, который вы хотите изменить: ";
	cin >> numberChange;
	int indexForChange;
	for (int i = 0; i < countParticipants; i++) 
	{
		if (participants[i].number == numberChange) {
			indexForChange = i;
		}
	}
	unsigned short number;
	string name;
	string surname;
	string patronymic;
	string city;
	unsigned short age;
	string nameComand;
	bool result;
	unsigned short score;
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
	arrayIndexationBasic = indexation(participants);
	arrayIndexationNumber = indexation(participants, "number", "up");
	arrayIndexationScore = indexation(participants, "score", "down");
	cout << "Изменённые неотсортированные данные" << endl;
	write(participants, arrayIndexationBasic);
	cout << "Данные отсортированные по номеру в порядке возрастания" << endl;
	write(participants, arrayIndexationNumber);
	cout << "Данные отсортированные по счёту в порядке убывания" << endl;
	write(participants, arrayIndexationScore);
	int numberDelete;
	cout << "Введите номер элемента, который вы хотите удалить: ";
	cin >> numberDelete;
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
	arrayIndexationBasic = indexation(participants);
	arrayIndexationNumber = indexation(participants, "number", "up");
	arrayIndexationScore = indexation(participants, "score", "down");
	cout << "Изменённые неотсортированные данные" << endl;
	write(participants, arrayIndexationBasic);
	cout << "Данные отсортированные по номеру в порядке возрастания" << endl;
	write(participants, arrayIndexationNumber);
	cout << "Данные отсортированные по счёту в порядке убывания" << endl;
	write(participants, arrayIndexationScore);
	/*int size;
	cout << "Введите количество элементов массива: ";
	cin >> size;
	Participant* participants = new Participant[size];
	unsigned short number;
	string name;
	string surname;
	string patronymic;
	string city;
	unsigned short age;
	string nameComand;
	bool result;
	unsigned short score;*/
	/*for (int i = 0; i < size; i++) 
	{
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
		participants[i] = { number, name, surname, patronymic, city, age, nameComand, result, score};
	}*/
}