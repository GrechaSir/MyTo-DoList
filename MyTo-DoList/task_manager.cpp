/*------------------------------------------------------------------------------
		Заголовки
-------------------------------------------------------------------------------*/
#include "task_manager.h"
#include <iostream>
#include <fstream>

/*------------------------------------------------------------------------------
		Локальные определения - макросы
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
		Глобальные переменные - volatile
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
		Внешние переменные - extern
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
		Локальные переменные
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
		Локальные функции (объявления) - static
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
		Локальные функции (реализация) - static
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
		Глобальные функции
-------------------------------------------------------------------------------*/
//Меод перевода всех букв в нижний регистр
string TaskManager::toLower(string message)
{
	for (int i = 0; i < message.size(); i++)
	{
		if (message[i] > 'A' && message[i] < 'Z') message[i] += 'z' - 'Z';
		if (message[i] > 'А' && message[i] < 'Я') message[i] += 'я' - 'Я';
	}

	return message;
}

//Метод поиска индекса задачи по ее номеру
int TaskManager::findTaskIndex(const int& taskId) const
{
	if (taskId == 0)
		return -2;

	for (int i = 0; i < tasks.size(); i++)
	{
		if (tasks[i].id == taskId)
			return i;
	}

	return -1;
}

//Метод для преобразования строки в приоритет
Priority TaskManager::stringToPriority(const string& priorityStr) const 
{
	string lowerStr = priorityStr;

	if (lowerStr == "low" || lowerStr == "низкий" || lowerStr == "л") {
		return Priority::LOW;
	}
	else if (lowerStr == "middle" || lowerStr == "средний" || lowerStr == "ср" || lowerStr == "с") {
		return Priority::MEDIUM;
	}
	else if (lowerStr == "high" || lowerStr == "высокий" || lowerStr == "в") {
		return Priority::HIGH;
	}
	else if (lowerStr == "none" || lowerStr == "нет" || priorityStr.empty()) {
		return Priority::NONE;
	}

	std::cout << "Предупреждение: неизвестный приоритет \"" << priorityStr << "\". Используется приоритет по умолчанию.\n";
	return Priority::NONE;
}

//Метод для парсинга строки с приоритетом
Priority TaskManager::findPriority(string& input)
{
	Priority priority = Priority::NONE;

	// Ищем флаг приоритета
	size_t priorityFlagPos = input.find("--priority=");
	if (priorityFlagPos != string::npos) 
	{
		string priorityStr = input.substr(priorityFlagPos + 11); // 11 = длина "--priority="

		// Отделяем приоритет от остальной строки
		size_t spacePos = priorityStr.find(' ');
		if (spacePos != string::npos)
			priorityStr = priorityStr.substr(0, spacePos);

		// Преобразуем строку в enum Priority
		priority = stringToPriority(priorityStr);

		// Удаляем флаг приоритета из заголовка
		input = input.substr(0, priorityFlagPos);

		// Удаляем возможные пробелы в конце
		auto end = input.find_last_not_of(" \t\n\r");
		if (end != string::npos) 
			input = input.substr(0, end + 1);
	}

	return priority;
}

// Преобразование приоритета в строку
string TaskManager::priorityToString(Priority priority) const {
	switch (priority) 
	{
		case Priority::LOW: 
			return "низкий";
		case Priority::MEDIUM: 
			return "средний";
		case Priority::HIGH: 
			return "высокий";
		case Priority::NONE: 
			return "";
	}
	return "";
}

//Метод, который отмечает выполнение задачи
void TaskManager::markComplete(const int& taskId)
{
	int taskIndex = findTaskIndex(taskId);

	//Вараинт, если нет задачи с таким индексом
	if (taskIndex == -1)
	{
		cout << "Задачи номер " << taskId << " не существует.\n";
		return;
	}
	//Вариант, если номер задачи введен некорректно
	if (taskIndex == -2)
	{
		cout << "Некорректный номер задачи.\n";
		return;
	}

	//Вариант, если задача уже выполнена
	if (tasks[taskIndex].completed == true)
	{
		cout << "Задача номер " << taskId << " уже была выполнена.\n";
		return;
	}
	//Отмечаем задачу как выполненную
	tasks[taskIndex].completed = true;
	cout << "Задача номер " << taskId << " выполнена.\n";

	this->printTasks("all");
	this->saveList(AUTO_SAVE_NAME_FILE);

	return;
}

//Метод добавляющий задачу
void TaskManager::addTask(string& title)
{
	//Создаем объект newTask, в который положим информацию о новой задаче
	Task newTask;

	//Парсинг приоритета
	if (title.find("--priority=") != string::npos)
		newTask.priority = this->findPriority(title); //Если попадем в функцию, то title отбросит часть, указывающую на приоритет, оставив только заголовок. А приоритет будет возращен.

	//Проверяем, написал ли пользователь задачу перед вводом
	if (title.empty())
	{
		cout << "Задача не была написана.\n";
		return;
	}

	newTask.title = title;
	newTask.id = nextId++;		//Номер задачи
	newTask.completed = false;	//Статус выполнения

	tasks.push_back(newTask);	//Добавление новой задачи в конец списка

	cout << "Задача добавлена (ID: " << newTask.id << ")\n";

	this->printTasks("all");
	this->saveList(AUTO_SAVE_NAME_FILE);

	return;
}

//Метод выводящий весь список задач
void TaskManager::findTask(const string& word)
{
	string lowWord;
	string lowTask;

	wordFindTasks.clear();

	//Проверяем, есть вообще задачи
	if (tasks.empty())
	{
		cout << "Список задач пуст.\n";
		return;
	}

	//Сортируем в соответствии со статусом
	for (const auto& task : tasks)
	{
		lowWord = this->toLower(word);
		lowTask = this->toLower(task.title);
		if (lowTask.find(lowWord) != std::string::npos)
			wordFindTasks.push_back(task);
	}

	//Если структура не заполнена, значит поиск по слову не нашел подходящих задач
	if (wordFindTasks.empty())
	{
		cout << "Результаты не найдены.\n";
		return;
	}

	//МОЖНО ВЕРНУТЬ, ЧТОБЫ ПРИ СОРТИРОВКЕ ПО СЛОВУ НУМЕРАЦИЯ БЫЛА С ЕДИНИЦЫ. НО ЭТО КАК БУДТО НЕУДОБНО ДЛЯ ПОЛЬЗОВАТЕЛЯ
	////Выравниваем нумерацию при выводе задач
	//for (int i = 0; i < wordFindTasks.size(); i++)
	//{
	//	statusTasks[i].id = i + 1;
	//}

	//Вывод всех задач найденный по слову на экран
	cout << "\n=== Список задач ===\n";
	for (const auto& task : wordFindTasks)
	{
		//
		if (task.completed)
			cout << "[X] ";
		else
			cout << "[ ] ";

		cout << task.id << ". ";

		cout << task.title << endl;
	}
	cout << "==================\n";

	return;
}

//Метод выводящий весь список задач
void TaskManager::printTasks(const string& status)
{
	statusTasks.clear();

	//Проверяем, есть вообще задачи
	if (tasks.empty())
	{
		cout << "Список задач пуст.\n";
		return;
	}

	//Сортируем в соответствии со статусом
	for (const auto& task : tasks)
	{
		if (status == "all" || (status == "completed" && task.completed))
			statusTasks.push_back(task);
		else if (status == "all" || (status == "active" && !task.completed))
			statusTasks.push_back(task);
	}

	//Проверяем, есть вообще задачи
	if (statusTasks.empty() && status != "all")
	{
		if (status == "completed" || status == "active")
			cout << "Нет задач со статусом " + status + ".\n";
		else
			cout << "Некорректная команда.\n";
		return;
	}

	//Выравниваем нумерацию при выводе задач
	for (int i = 0; i < statusTasks.size(); i++)
	{
		statusTasks[i].id = i + 1;
	}

	//Вывод всех задач на экран
	cout << "\n==== Список задач ====\n";
	for (const auto& task : statusTasks)
	{
		//
		if (task.completed)
			cout << "[X] ";
		else
			cout << "[ ] ";

		cout << task.id << ". ";

		cout << task.title;
		cout << "  " << priorityToString(task.priority) << endl;
	}
	cout << "==================\n";

	return;
}

//Метод удаляющий задачу
void TaskManager::removeTask(const int& taskId)
{
	int taskIndex = findTaskIndex(taskId);

	//Проверяем, есть ли задача, которую хотим удалить
	if (taskIndex == -1)
	{
		cout << "Задача номер " << taskId << " не существует.\n";
		return;
	}

	//Вариант, если номер задачи введен некорректно
	if (taskIndex == -2)
	{
		cout << "Некорректный номер задачи.\n";
		return;
	}

	//Удаление задачи по индексу
	tasks.erase(tasks.begin() + taskIndex);
	cout << "Задача номер " << taskId << " удалена.\n";

	nextId--;

	for (int i = 0; i < tasks.size(); i++)
		tasks[i].id = i + 1;

	this->saveList(AUTO_SAVE_NAME_FILE);

	return;
}

//Метод удаляющий список или выполненный задачи списка
void TaskManager::clearTask(const string& status)
{
	//Проверяем, есть вообще задачи
	if (tasks.empty())
	{
		cout << "Список задач пуст.\n";
		return;
	}

	if (status != "completed" && status != "")
	{
		cout << "Некорректная команда.\n";
		return;
	}

	for (int i = 0; i < tasks.size(); )
	{

		if (status == "completed" && tasks[i].completed == true)
		{
			this->removeTask(i + 1);
			//tasks.erase(tasks.begin() + i);
			//nextId--;
		}
		else if (status == "")
		{
			tasks.clear();
			nextId = 1;
		}
		else
			i++;
	}

	cout << "Список очищен.\n";

	this->printTasks("all");
	this->saveList(AUTO_SAVE_NAME_FILE);

	return;
}

//Метод, который позволяет редактировать выбранную задачу
void TaskManager::editTask(const int& taskId)
{
	int taskIndex = findTaskIndex(taskId);

	cout << "Задачу номер " << taskId << " можно изменить.\n";
	getline(cin, tasks[taskIndex].title);
	cout << "Задачу номер " << taskId << " изменена.\n";

	this->printTasks("all");
	this->saveList(AUTO_SAVE_NAME_FILE);

	return;
}

//Метод сохраняющий список задач
void TaskManager::saveList(const string& nameFile)
{
	ofstream file;
	file.open(nameFile + ".txt", ios::out);

	if (file.is_open())
	{
		for (const auto& task : tasks)
		{
			if (task.completed)
				file << "[X] ";
			else
				file << "[ ] ";

			file << task.id << ". ";
			file << task.title << endl;
		}
	}

	file.close();

	cout << "Файл был записан.\n";
}

//Метод загрузки списка задач
void TaskManager::loadList(const string& nameFile)
{
	ifstream file;
	string task;
	Task loadTask;

	file.open(nameFile + ".txt", ios::in);

	if (file.is_open())
	{
		//Очистим объект, хранящий информацию о задачах
		tasks = {};
		nextId = 1;

		while (getline(file, task))
		{
			loadTask.id = nextId++;

			for (int i = 0; i < sizeof(task); i++)
			{
				if (i == 1)
				{
					if (task[i] == 'X')
						loadTask.completed = true;
					else
						loadTask.completed = false;
				}

				if (i > 3 && task[i] == ' ')
				{
					loadTask.title = task.substr(i + 1);
					break;
				}
			}

			tasks.push_back(loadTask);
			loadTask = {};
		}

		file.close();
		cout << "Файл был загружен.\n";
	}
	else
	{
		file.close();
		cout << "Файла не существует.\n";
	}
}