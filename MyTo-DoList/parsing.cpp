/*------------------------------------------------------------------------------
        Заголовки
-------------------------------------------------------------------------------*/
#include "parsing.h"
#include <iostream>

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
//Функция преобразования строки в приоритет
Priority stringToPriority(const string& priorityStr)
{
    string lowerStr = priorityStr;

    if (lowerStr == "low" || lowerStr == "низкий" || lowerStr == "н") {
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

//Парсинг строки с приоритетом
Priority findPriority(string& input)
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

Command parsingInputCmd(const string& command)
{
    Command cmd;
    bool isName = false;
    bool isNum = false;

    for (const auto& letter : command)
    {
        if (letter != ' ' && !isName)
            cmd.nameCommand += letter;
        else if (letter == ' ' && !isName)
        {
            isName = true;
            continue;
        }

        if ((cmd.nameCommand == "add" || cmd.nameCommand == "find" || cmd.nameCommand == "close") && isName)
            cmd.task += letter;
        else if ((cmd.nameCommand == "save" || cmd.nameCommand == "load") && isName)
            cmd.file += letter;
        else if ((cmd.nameCommand == "list" || cmd.nameCommand == "clear") && isName)
            cmd.filter += letter;
        else if ((cmd.nameCommand == "complete" || cmd.nameCommand == "remove" || cmd.nameCommand == "edit") && isName)
        {
            if (letter != ' ' && !isNum)
                cmd.stringId += letter;
            else if (letter == ' ' && !isNum)
            {
                isNum = true;
                continue;
            }
            else
                cmd.task += letter;
        }
    }

    cmd.priority = Priority::NONE;
    if (cmd.task.find("--priority=") != string::npos)
        cmd.priority = findPriority(cmd.task);

    return cmd;
}