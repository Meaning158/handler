// handler.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <fstream>
#include "Lexer.h"
#include <iostream>
#include "TokenType.h"
#include "regex"
#include "string"
#include <sstream>
#include <vector>
int main()
{
    std::string line;
    std::ifstream file;
    Lexer a;
    file.open("FileName.txt");
    if (file.is_open())
    {
        std::cout << "file is open" << std::endl;
        while (std::getline(file, line))
        {
           a.lexAnalysis(line);
        }
    }
    else {
        std::cout << "close";
    }
    for (auto& i : a.getVector()) {
        std::cout << i.getTokenValue() << " " << i.getTokenType().getType() << std::endl;
    }
    file.close();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
