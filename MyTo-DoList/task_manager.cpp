#include "task_manager.h"
#include <iostream>
#include <fstream>

//Метод поиска индекса задачи по ее номеру
int TaskManager::findTaskIndex(int taskId) const
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

//Метод, который отмечает выполнение задачи
void TaskManager::markComplete(int taskId)
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

	this->printAllTasks();

	return;
}

//Метод добавляющий задачу
void TaskManager::addTask(const string& title)
{
	//Проверяем, написал ли пользователь задачу перед вводом
	if (title.empty())
	{
		cout << "Задача не была написана.\n";
		return;
	}
	//Создаем объект newTask, в который положим информацию о новой задаче
	Task newTask;
	newTask.id = nextId++;		//Номер задачи
	newTask.title = title;		//Заголовок задачи
	newTask.completed = false;	//Статус выполнения

	tasks.push_back(newTask);	//Добавление новой задачи в конец списка

	cout << "Задача добавлена (ID: " << newTask.id << ")\n";

	return;
}

//Метод выводящий весь список задач
void TaskManager::printAllTasks() const
{
	//Проверяем, есть ли уже задачи
	if (tasks.empty())
	{
		cout << "Список задач пуст.\n";
		return;
	}

	//Вывод всех задач на экран
	cout << "\n=== Список задач ===\n";
	for (const auto& task : tasks)
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
}

//Метод удаляющий задачу
void TaskManager::removeTask(int taskId)
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

	this->printAllTasks();

	return;
}

//Метод, который позволяет редактировать выбранную задачу
void TaskManager::editTask(const int taskId)
{
	int taskIndex = findTaskIndex(taskId);

	cout << "Задачу номер " << taskId << " можно изменить.\n";

	cout << tasks[taskIndex].title;
}

//Метод сохраняющий список задач
void TaskManager::saveList(const string nameFile)
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
void TaskManager::loadList(const string nameFile)
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