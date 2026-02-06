// MyTo-DoList.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "task_manager.h"

int main()
{
    string command;
    TaskManager myList;
    int taskId;

    cout << "Welcome to To-DoList!\n";

    while (1)
    {
        cout << "Enter command (add/print/copmlete/delete): ";
        getline(cin, command);

        if (command == "add")
        {
            string task;
            cout << "Enter task: ";
            getline(cin, task);
            myList.addTask(task);
        }
        else if (command == "print")
        {
            myList.printAllTasks();
        }
        else if (command == "complete")
        {
            cout << "Mark a task has been completed: ";
            cin >> taskId;
            myList.markComplete(taskId);
        }
        else if (command == "delete")
        {
            cout << "Enter task number that will be removed: ";
            cin >> taskId;
            myList.removeTask(taskId);
        }
        else
        {
            cout << "Incorrect command.\n";
        }

    }
}

