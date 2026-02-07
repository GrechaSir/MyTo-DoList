//Файл main
//Турбо ура!

#include <iostream>
#include "task_manager.h"

struct Command
{
    string name;
    string task;
    string stringId;
    bool complete;
};

int main()
{
    system("chcp 1251");
    Command cmd;
    TaskManager myList;
    string command;
    bool isName = false;

    cout << "Ты пидр, еп!\n";

    while (1)
    {
        cout << "\nВведите команду (help - список доступных команд): ";
        getline(cin, command);

        //Обработка введенной команды
        for (const auto& letter : command)
        {
            if (letter != ' ' && !isName)
            {
                cmd.name += letter;
            }
            else if (letter == ' ')
            {
                isName = true;
                continue;
            }
            
            if ((cmd.name == "add" || cmd.name == "help") && isName)
                cmd.task += letter;
            else if ((cmd.name == "complete" || cmd.name == "remove") && isName)
                cmd.stringId += letter;
        }


        //Выполнение каждой из команд
        if (cmd.name == "add")
            myList.addTask(cmd.task);
        else if (cmd.name == "complete")
            myList.markComplete(stoi(cmd.stringId));
        else if (cmd.name == "remove")
            myList.removeTask(stoi(cmd.stringId));
        else if (cmd.name == "list")
            myList.printAllTasks();
        else if (cmd.name == "help")
        {
            cout << "Список доступных команд:\n";
            cout << "add \"Заголовок задачи\" - Добавить задачу;\n";
            cout << "list - Вывести список всех задач;\n";
            cout << "complete \"Номер задачи\" - Отметить задачу как выполненную;\n";
            cout << "remove \"Номер задачи\" - Удалить задачу.\n";
        }
        else
            cout << "Некорректная команда.\n";

        //Очистка буффера
        cmd = {};
        isName = false;
    }
}

