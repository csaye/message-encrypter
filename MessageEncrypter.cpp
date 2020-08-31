#include <iostream>
#include <fstream>

enum Command
{
    Invalid,
    Quit,
    Help,
    Read,
    Write
};

void promptUser()
{
    std::cout << "Welcome. Enter \"help\" for a list of commands.\n";
}

Command toCommand(std::string input)
{
    if (input == "quit") return ::Quit;
    if (input == "help") return ::Help;
    if (input == "read") return ::Read;
    if (input == "write") return ::Write;

    return ::Invalid;
}

void processCommands()
{
    std::string input;
    std::cin >> input;

    switch (toCommand(input))
    {
        case Invalid:
            break;
        case Quit:
            break;
        case Help:
            break;
        case Read:
            break;
        case Write:
            break;
    }
}

void writeToFile()
{
    std::ofstream file("message.txt");
    file << "hello world";
    file.close();
}

void readFromFile()
{
    std::string line;
    std::ifstream file("message.txt");

    if (file.is_open())
    {
        while (getline(file, line))
        {
            std::cout << line << "\n";
        }
        file.close();
    }
    else
    {
        std::cout << "No message.txt file found.\n";
    }
}

int main()
{
    promptUser();
    processCommands();
    // writeToFile();
    // readFromFile();
}
