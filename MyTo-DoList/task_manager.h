#pragma once

/*-----------------------------------------------------------------------------
			Заголовки
-----------------------------------------------------------------------------*/
#include <vector>
#include "task.h"

/*-----------------------------------------------------------------------------
			Типы
-----------------------------------------------------------------------------*/
class TaskManager
{
private:
	vector<Task> tasks;
	vector<Task> statusTasks;
	vector<Task> wordFindTasks;
	int nextId = 1;

public:
	string toLower(string message);

	int findTaskIndex(const int& taskId) const;
	Priority stringToPriority(const string& priorityStr) const;
	string priorityToString(Priority priority) const;
	Priority findPriority(string& input);

	void markComplete(const int& taskId);
	void addTask(string& title);
	void findTask(const string& word);
	void printTasks(const string& status);
	void removeTask(const int& taskId);
	void clearTask(const string& status);
	void editTask(const int& taskId);

	void saveList(const string& nameFile);
	void loadList(const string& nameFile);
};

/*-----------------------------------------------------------------------------
			Определения
-----------------------------------------------------------------------------*/
#define AUTO_SAVE_NAME_FILE "autoSave"

/*-----------------------------------------------------------------------------
			Внешние переменные
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
			Глобальные функции
-----------------------------------------------------------------------------*/