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

std::string getEncryptor(char ch)
{
    int firstEncryptor = ((ch % 19) + 7) * 3;
    int secondEncryptor = ((ch % 13) + 2) * 7;

    return std::to_string(firstEncryptor) + std::to_string(secondEncryptor);
}

std::string encryptChar(char ch, std::string encryptor)
{
    int firstEncryptor = stoi(encryptor.substr(0, 2));
    int secondEncryptor = stoi(encryptor.substr(2, 4));

    int encryptedNum = ch;

    encryptedNum *= firstEncryptor;
    encryptedNum -= secondEncryptor;

    std::string encryptedString = std::to_string(encryptedNum);

    for (int i = encryptedString.length(); i < 4; i++)
    {
        encryptedString = "0" + encryptedString;
    }

    return encryptedString;
}

std::string encrypt(std::string message)
{
    std::string encryptor = getEncryptor(message[0]);
    std::string encryptedMessage = encryptor;

    for (int i = 0; i < message.length(); i++)
    {
        char ch = message[i];
        encryptedMessage += encryptChar(ch, encryptor);
    }

    return encryptedMessage;
}

char decryptChar(std::string str, std::string encryptor)
{
    int firstEncryptor = stoi(encryptor.substr(0, 2));
    int secondEncryptor = stoi(encryptor.substr(2, 4));

    int decryptedNum = stoi(str);

    decryptedNum += secondEncryptor;
    decryptedNum /= firstEncryptor;

    return decryptedNum;
}

std::string decrypt(std::string message)
{
    std::string decryptedMessage = "";
    std::string decryptor = message.substr(0, 4);

    for (int i = 4; i < message.length(); i += 4)
    {
        std::string str = message.substr(i, 4);
        decryptedMessage += decryptChar(str, decryptor);
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
        std::cout << "No message.txt file found. Write to file to automatically create it.\n";
    }
}

bool isInvalidString(std::string str)
{
    if (str.length() < 1) return true;

    for (int i = 0; i < str.length(); i++)
    {
        char ch = str[i];
        if (ch < 32 || ch > 127) return true;
    }

    return false;
}

void writeMessage()
{
    std::string input;
    std::cout << "Please enter message to write to file:\n";
    std::getline(std::cin, input);
    while (isInvalidString(input))
    {
        std::cout << "Invalid input. Please try again:\n";
        std::getline(std::cin, input);
    }

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
                std::cout << "Commands:\nread, write, quit, help\n";
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
