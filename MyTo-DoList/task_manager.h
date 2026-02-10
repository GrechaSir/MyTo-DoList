#pragma once

#include <vector>
#include "task.h"

class TaskManager
{
private:
	vector<Task> tasks;
	vector<Task> statusTasks;
	vector<Task> wordFindTasks;
	int nextId = 1;

public:
	int findTaskIndex(int taskId) const;
	string toLower(string message);

	void addTask(const string& title);
	void findTask(const string& word);
	void markComplete(int taskId);
	void printTasks(const string& status);
	void removeTask(int taskId);
	void clearTask(const string& status);
	void editTask(const int taskId);

	void saveList(const string nameFile);
	void loadList(const string nameFile);
};