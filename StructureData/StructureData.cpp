#include <iostream>
#include <algorithm>
#include <locale>
#include <string>

using namespace std;


struct Participant

{
	unsigned short number;

	unsigned short score;

	string name;

	string surname;

	string patronymic;

	string city;

	unsigned short age;

	string nameComand;

	bool result; // Либо победа - 1, либо поражение - 0, ничиьи нет

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
	cout << "Номер: " << p.number << "; " << "Счёт: " << p.score << "; Имя: " << p.name << "; " << "Фамилия: " << p.surname << "; " << "Отчество: " << p.patronymic << "; " << "Город: " << p.city << "; " << "Возраст: " << p.age << "; " << "Команда: " << p.nameComand << "; " << "Победа: " << p.result << endl;
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

struct Node {
	Participant data;
	Node* next;
};

void inputData(Node*& head, Participant participant)
{
	Node* newNode = new Node;
	int val1 = participant.number;
	int val2 = participant.score;
	newNode->data = participant;
	newNode->next = nullptr;
	if (head == nullptr || val1 < head->data.number || (val1 == head->data.number && val2 < head->data.score))
	{
		newNode->next = head;
		head = newNode;
	}
	else
	{
		Node* current = head;
		while (current->next != nullptr && (val1 > current->next->data.number || (val1 == current->next->data.number && val2 > current->next->data.score)))
		{
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

void BrListFromFirst(Node* head)
{
	while (head != nullptr)
	{
		Participant el = head->data;
		cout << "Номер: " << el.number << "; " << "Счёт: " << el.score << "; " << "Имя: " << el.name << "; " << "Фамилия: " << el.surname << "; " << "Отчество: " << el.patronymic << "; " << "Город: " << el.city << "; " << "Возраст: " << el.age << "; " << "Команда: " << el.nameComand << "; " << "Победа: " << el.result << endl;
		head = head->next;
	}
}

void BrListFromEnd(Node* head)
{
	if (head != nullptr)
	{
		Participant el = head->data;
		BrListFromEnd(head->next);
		cout << "Номер: " << el.number << "; " << "Счёт: " << el.score << "; " << "Имя: " << el.name << "; " << "Фамилия: " << el.surname << "; " << "Отчество: " << el.patronymic << "; " << "Город: " << el.city << "; " << "Возраст: " << el.age << "; " << "Команда: " << el.nameComand << "; " << "Победа: " << el.result << endl;
	}
}

void Search(Node*& head, int EV)
{
	Node* current = head; 
	bool isFound = false;
	while (current != nullptr)
	{
		if (current->data.number == EV)
		{
			Participant el = current->data;
			cout << "Номер: " << el.number << "; " << "Счёт: " << el.score << "; " << "Имя: " << el.name << "; " << "Фамилия: " << el.surname << "; " << "Отчество: " << el.patronymic << "; " << "Город: " << el.city << "; " << "Возраст: " << el.age << "; " << "Команда: " << el.nameComand << "; " << "Победа: " << el.result << endl;
			isFound = true;
		}
		current = current->next;
	}
	if (!isFound)
	{
		cout << "Элемент с таким номером отсутствует" << endl;
	}
}

void Delete(Node*& head, int EV)
{
	Node* H = head;
	Node* C = nullptr;
	bool isFind = false;

	while (H != nullptr)
	{
		H = head;
		while ((H != nullptr) && (H->data.number != EV))
		{
			C = H;
			H = H->next;
		}
		if (H != nullptr)
		{
			Participant el = H->data;
			if (H == head)
			{
				head = H->next;
			}
			else
			{
				if (H->next == nullptr)
				{
					C->next = nullptr;
				}
				else
				{
					C->next = H->next;
				}
			}
			cout << "Найден элемент c номером " << EV << ": " << endl;
			cout << "Номер: " << el.number << "; " << "Счёт: " << el.score << "; " << "Имя: " << el.name << "; " << "Фамилия: " << el.surname << "; " << "Отчество: " << el.patronymic << "; " << "Город: " << el.city << "; " << "Возраст: " << el.age << "; " << "Команда: " << el.nameComand << "; " << "Победа: " << el.result << endl;
			isFind = true;
			cout << "Элемент был удалён" << endl;
			delete H;
		}
	}
	if (!isFind)
	{
		cout << "Элемент с таким номером отсутствует" << endl;
	}
}

int main()
{
	system("chcp 1251 >> null");
	int variantFirst = 0;
	int variantSecond = 0;
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
	int indexForChange;
	int indexForDelete;
	int countParticipants;
	int numberSearch;
	int numberDelete;
	int scoreSearch;
	string trashAnswer;
	string message = "";
	bool arrayIsCreated = false;
	Node* head = nullptr;
	while (variantFirst != 4)
	{
		cout << "Выбирите этап:\n"
			<< "1. Сортировка и поиск данных в массивах с использованием индексов-массивов\n"
			<< "2. Сортировка и поиск данных в массивах с использованием бинарного дерева\n"
			<< "3. Создание линейных списков с сортировкой элементов\n"
			<< "4. Завершить работу\n";
		variantFirst = correctNumber(1, 4);
		switch (variantFirst)
		{
		case 1:
			while (variantSecond != 12)
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
				variantSecond = correctNumber(1, 12);
				switch (variantSecond)
				{
				case 1:
					system("cls");
					cout << "Введите количество элементов массива" << endl;
					size = correctNumber(1, 100);
					countParticipants = size;
					participants = new Participant[size];
					for (int i = 0; i < size; i++)
					{
						cout << endl;
						cout << "Введите номер участника" << endl;;
						number = correctNumber(1, 1000);
						cout << "Введите счёт участника" << endl;;
						score = correctNumber(1, 350);
						cout << "Введите имя участника: ";
						cin >> name;
						cout << "Введите фамилию участника: ";
						cin >> surname;
						cout << "Введите отчество участника: ";
						cin >> patronymic;
						cout << "Введите город участника: ";
						cin >> city;
						cout << "Введите возраст участника" << endl;
						age = correctNumber(1, 100);
						cout << "Введите имя команды участника: ";
						cin >> nameComand;
						if (score > 200) {
							result = true;
						}
						else {
							result = false;
						}
						participants[i] = { number,score, name, surname, patronymic, city, age, nameComand, result };
					};
					arrayIndexationBasic = indexation(participants, countParticipants);
					arrayIndexationNumberUp = indexation(participants, countParticipants, "number", "up");
					arrayIndexationScoreUp = indexation(participants, countParticipants, "score", "up");
					arrayIndexationNumberDown = indexation(participants, countParticipants, "number", "down");
					arrayIndexationScoreDown = indexation(participants, countParticipants, "score", "down");
					message = "Создан массив из введённых элементов. Мы можете увидеть его, выбрав соответствующую команду";
					arrayIsCreated = true;
					break;
				case 2:
					system("cls");
					participants = new Participant[5];
					countParticipants = 5;
					participants[0] = { 3, 200, "Дмитрий", "Кондратиев", "Алексеевич", "Пермь", 20, "Авангард", true };
					participants[1] = { 2, 250, "Егор", "Чертанов", "Владимирович", "Саранск", 30, "Пламя", true };
					participants[2] = { 4, 150, "Тимофей", "Ломов", "Константинович", "Хабаровск", 23, "Вымпел", false };
					participants[3] = { 1, 100, "Анатолий", "Леснов", "Евгеньевич", "Хабаровск", 24, "Вымпел", false };
					participants[4] = { 5, 199, "Иван", "Дулин", "Александрович", "Красноярск", 20, "Молот", false };
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
						cout << "Введите номер искомого элемента" << endl;
						numberSearch = correctNumber(1, 1000);
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
						scoreSearch = correctNumber(1, 350);
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
						indexForChange = binarySearch(arrayIndexationNumberUp, countParticipants, numberChange);
						cout << "Введите номер участника" << endl;;
						number = correctNumber(1, 1000);
						cout << "Введите счёт участника" << endl;;
						score = correctNumber(1, 350);
						cout << "Введите имя участника: ";
						cin >> name;
						cout << "Введите фамилию участника: ";
						cin >> surname;
						cout << "Введите отчество участника: ";
						cin >> patronymic;
						cout << "Введите город участника: ";
						cin >> city;
						cout << "Введите возраст участника" << endl;
						age = correctNumber(1, 100);
						cout << "Введите имя команды участника: ";
						cin >> nameComand;
						if (score > 200)
						{
							result = true;
						}
						else
						{
							result = false;
						}
						participants[indexForChange] = { number, score, name, surname, patronymic, city, age, nameComand, result };
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
						indexForDelete = binarySearch(arrayIndexationNumberUp, countParticipants, numberDelete);
						participants[indexForDelete].number = NULL;
						participants[indexForDelete].name = "NULL";
						participants[indexForDelete].surname = "NULL";
						participants[indexForDelete].patronymic = "NULL";
						participants[indexForDelete].city = "NULL";
						participants[indexForDelete].age = NULL;
						participants[indexForDelete].nameComand = "NULL";
						participants[indexForDelete].result = false;
						participants[indexForDelete].score = NULL;
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
					break;
				}
			}
			break;
		case 2:
			system("cls");
			break;
		case 3:
			system("cls");
			while (variantSecond != 8)
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
					<< "3. Вывести изначальный массив в порядке ввода\n"
					<< "4. Вывести массив, отсортированный по возрастанию\n"
					<< "5. Вывести массив, отсортированный по убыванию\n"
					<< "6. Найти участника с заданным номером\n"
					<< "7. Удалить информацию об участнике\n"
					<< "8. Завершить работу\n";
				variantSecond = correctNumber(1, 8);
				switch (variantSecond)
				{
				case 1:
					system("cls");
					cout << "Введите количество элементов массива" << endl;
					size = correctNumber(1, 100);
					countParticipants = size;
					participants = new Participant[size];
					for (int i = 0; i < size; i++)
					{
						cout << endl;
						cout << "Введите номер участника" << endl;;
						number = correctNumber(1, 1000);
						cout << "Введите счёт участника" << endl;;
						score = correctNumber(1, 350);
						cout << "Введите имя участника: ";
						cin >> name;
						cout << "Введите фамилию участника: ";
						cin >> surname;
						cout << "Введите отчество участника: ";
						cin >> patronymic;
						cout << "Введите город участника: ";
						cin >> city;
						cout << "Введите возраст участника" << endl;
						age = correctNumber(1, 100);
						cout << "Введите имя команды участника: ";
						cin >> nameComand;
						if (score > 200) {
							result = true;
						}
						else {
							result = false;
						}
						participants[i] = { number,score, name, surname, patronymic, city, age, nameComand, result };
					};
					message = "Создан массив из введённых элементов. Мы можете увидеть его, выбрав соответствующую команду";
					arrayIsCreated = true;
					for (int i = 0; i < countParticipants; i++)
					{
						inputData(head, participants[i]);
					}
					break;
				case 2:
					system("cls");
					participants = new Participant[5];
					countParticipants = 5;
					participants[0] = { 1, 200, "Дмитрий", "Кондратиев", "Алексеевич", "Пермь", 20, "Авангард", true };
					participants[1] = { 1, 250, "Егор", "Чертанов", "Владимирович", "Саранск", 30, "Пламя", true };
					participants[2] = { 4, 150, "Тимофей", "Ломов", "Константинович", "Хабаровск", 23, "Вымпел", false };
					participants[3] = { 1, 100, "Анатолий", "Леснов", "Евгеньевич", "Хабаровск", 24, "Вымпел", false };
					participants[4] = { 5, 199, "Иван", "Дулин", "Александрович", "Красноярск", 20, "Молот", false };
					message = "Создан массив заданный по умолчанию. Мы можете увидеть его, выбрав соответствующую команду";
					arrayIsCreated = true;
					for (int i = 0; i < countParticipants; i++)
					{
						inputData(head, participants[i]);
					}
					break;
				case 3:
					if (arrayIsCreated)
					{
						system("cls");
						for (int i = 0; i < countParticipants; i++)
						{
							writeParticipant(participants, i);
						};
						cout << "\n" << "Введите что нибудь, чтобы вернуться в меню: ";
						cin >> trashAnswer;
					}
					else
					{
						message = "Вы ещё не создали массив";
					}
					break;
				case 4:
					if (arrayIsCreated)
					{
						system("cls");
						BrListFromFirst(head);
						cout << "\n" << "Введите что нибудь, чтобы вернуться в меню: ";
						cin >> trashAnswer;
					}
					else
					{
						message = "Вы ещё не создали массив";
					}
					break;
				case 5:
					if (arrayIsCreated)
					{
						system("cls");
						BrListFromEnd(head);
						cout << "\n" << "Введите что нибудь, чтобы вернуться в меню: ";
						cin >> trashAnswer;
					}
					else
					{
						message = "Вы ещё не создали массив";
					}
					break;
				case 6:
					if (arrayIsCreated)
					{
						system("cls");
						cout << "Введите номер искомого элемента" << endl;
						numberSearch = correctNumber(1, 1000);
						Search(head, numberSearch);
						cout << "\n" << "Введите что нибудь, чтобы вернуться в меню: ";
						cin >> trashAnswer;
					}
					else
					{
						message = "Вы ещё не создали массив";
					}
					break;
				case 7:
					if (arrayIsCreated)
					{
						system("cls");
						cout << "Введите номер искомого элемента" << endl;
						numberDelete = correctNumber(1, 1000);
						Delete(head, numberDelete);
						cout << "\n" << "Введите что нибудь, чтобы вернуться в меню: ";
						cin >> trashAnswer;
						message = "Один из элементов был удалён. Мы можете увидеть новый массив, выбрав соответствующую команду";
					}
					else
					{
						message = "Вы ещё не создали массив";
					}
					break;
				case 8:
					system("cls");
					cout << "Завершаем работу" << endl;
					break;
				}
			}
			break;
		case 4:
			system("cls");
			cout << "Завершаем работу" << endl;
			break;
		}
	}
}