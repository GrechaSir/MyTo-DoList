#include <iostream>
#include "task_manager.h"

struct Command
{
    string nameCommand;
    string task;
    string stringId;
    string file;
    bool complete;
};

int main()
{
    system("chcp 1251");
    Command cmd;
    TaskManager myList;
    string command;
    bool isName = false;

    cout << "Добро пожаловать в To-Do List!\n";

    while (1)
    {
        cout << "\nВведите команду (help - список доступных команд): ";
        getline(cin, command);

        //Обработка введенной команды
        for (const auto& letter : command)
        {
            if (letter != ' ' && !isName)
            {
                cmd.nameCommand += letter;
            }
            else if (letter == ' ' && !isName)
            {
                isName = true;
                continue;
            }

            if ((cmd.nameCommand == "add" || cmd.nameCommand == "help") && isName)
                cmd.task += letter;
            else if ((cmd.nameCommand == "save" || cmd.nameCommand == "load") && isName)
                cmd.file += letter;
            else if ((cmd.nameCommand == "complete" || cmd.nameCommand == "remove" || cmd.nameCommand == "edit") && isName)
                cmd.stringId += letter;
        }

        //Выполнение каждой из команд
        if (cmd.nameCommand == "add")
            myList.addTask(cmd.task);
        else if (cmd.nameCommand == "complete")
            myList.markComplete(atoll(cmd.stringId.c_str()));
        else if (cmd.nameCommand == "remove")
            myList.removeTask(atoll(cmd.stringId.c_str()));
        else if (cmd.nameCommand == "list")
            myList.printAllTasks();
        else if (cmd.nameCommand == "help")
        {
            cout << "Список доступных команд:\n";
            cout << "add \"Заголовок задачи\" - Добавить задачу;\n";
            cout << "list - Вывести список всех задач;\n";
            cout << "complete \"Номер задачи\" - Отметить задачу как выполненную;\n";
            cout << "remove \"Номер задачи\" - Удалить задачу.\n";
        }
        else if (cmd.nameCommand == "save")
            myList.saveList(cmd.file);
        else if (cmd.nameCommand == "load")
            myList.loadList(cmd.file);
        else if (cmd.nameCommand == "edit")
            myList.editTask(atoll(cmd.stringId.c_str()));
        else
            cout << "Некорректная команда.\n";

        //Очистка буффера
        cmd = {};
        isName = false;
    }
}

