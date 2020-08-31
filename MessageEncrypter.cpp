#include <iostream>
#include <fstream>
#include <string>

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

std::string encryptChar(char ch)
{
    return "0065";
}

std::string encrypt(std::string message)
{
    std::string encryptedMessage = "";

    for (int i = 0; i < message.length(); i++)
    {
        char ch = message[i];
        encryptedMessage += encryptChar(ch);
    }

    return encryptedMessage;
}

char decryptChar(std::string str)
{
    return stoi(str);
}

std::string decrypt(std::string message)
{
    std::string decryptedMessage = "";

    for (int i = 0; i < message.length(); i += 4)
    {
        std::string str = message.substr(i, 4);
        decryptedMessage += decryptChar(str);
    }

    return decryptedMessage;
}

void readMessage()
{
    std::string line;
    std::ifstream file("message.txt");

    if (file.is_open())
    {
        while (getline(file, line))
        {
            std::cout << decrypt(line) << "\n";
        }
        file.close();
    }
    else
    {
        std::cout << "No message.txt file found.\n";
    }
}

void writeMessage()
{
    std::string input;
    std::cout << "Please enter message to write to file:\n";
    std::getline(std::cin, input);

    std::ofstream file("message.txt");
    file << encrypt(input);
    file.close();

    std::cout << "Message successfully written to file.\n";
}

void processCommands()
{
    std::string input;
    bool running = true;

    while (running)
    {
        std::cout << "> ";
        std::getline(std::cin, input);

        switch (toCommand(input))
        {
            case Invalid:
                std::cout << "Invalid command. Enter \"help\" for a list of commands.\n";
                break;
            case Quit:
                running = false;
                break;
            case Help:
                std::cout << "Commands:\nquit, help, read, write\n";
                break;
            case Read:
                readMessage();
                break;
            case Write:
                writeMessage();
                break;
        }
    }
}

int main()
{
    promptUser();
    processCommands();
}
