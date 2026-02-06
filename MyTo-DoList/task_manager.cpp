#include "task_manager.h"
#include <iostream>

int TaskManager::findTaskIndex(int taskId) const
{
	for (int i = 0; i < tasks.size(); i++)
	{
		if (tasks[i].id == taskId)
			return i;
	}

	if (taskId == 0)
		return 0;

	return -1;
}

void TaskManager::markComplete(int taskId)
{
	int taskIndex = findTaskIndex(taskId);

	if (taskIndex == 0)
	{
		cout << "Task number is incorrect.\n";
		return;
	}

	//Вараинт, если нет задачи с таким индексом
	if (taskIndex == -1)
	{
		cout << "Task with that number is empty.\n";
		return;
	}
	//Вариант, если задача уже выполнена
	if (tasks[taskIndex].completed == true)
	{
		cout << "That task has been copmleted before.\n";
		return;
	}
	//Отмечаем задачу как выполненную
	tasks[taskIndex].completed = true;
	cout << "Task number " << taskId << " completed.\n";
	return;
}

void TaskManager::addTask(const string& title)
{
	//Проверяем, написал ли пользователь задачу перед вводом
	if (title.empty())
	{
		cout << "Task is empty.\n";
		return;
	}
	//Создаем объект newTask, в который положим информацию о новой задаче
	Task newTask;
	newTask.id = nextId++;		//Номер задачи
	newTask.title = title;		//Задача
	newTask.completed = false;	//Статус выполнения

	tasks.push_back(newTask);	//Добавляем новую задачу в список всех задач

	cout << "Task added (ID: " << newTask.id << ")\n";

	return;
}

void TaskManager::printAllTasks() const
{
	//Проверяем, есть ли уже задачи
	if (tasks.empty())
	{
		cout << "List is empty.\n";
		return;
	}

	//Вывод всех задач на экран
	cout << "\n=== Tasks list ===\n";
	for (const auto& task : tasks)
	{
		//
		if (task.completed)
			cout << "[*] ";
		else
			cout << "[ ] ";
		
		cout << task.id << ".";

		cout << task.title << endl;
	}
	cout << "==================\n";
}

void TaskManager::removeTask(int taskId)
{
	int taskIndex = findTaskIndex(taskId);

	//Проверяем, есть ли задача, которую хотим удалить
	if (taskIndex == -1)
	{
		cout << "Task with that number is empty.\n";
		return;
	}

	//Удаляем задачу
	tasks.erase(tasks.begin() + taskIndex);
	cout << "Task number " << taskId << " has been removed.\n";

	nextId--;

	for (int i = 0; i < tasks.size(); i++)
		tasks[i].id = i + 1;

	return;
}
