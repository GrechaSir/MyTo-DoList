#pragma once

#include <vector>
#include "task.h"

class TaskManager
{
private:
	vector<Task> tasks;
	int nextId = 1;

public:
	void addTask(const string& title);
	int findTaskIndex(int taskId) const;
	void markComplete(int taskId);
	void printAllTasks() const;
	void removeTask(int taskId);
	void editTask(const int taskId);

	void saveList(const string nameFile);
	void loadList(const string nameFile);
};