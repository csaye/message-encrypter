#include <iostream>
#include <fstream>

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
        std::cout << "No message.txt file found. \n";
    }
}

int main()
{
    writeToFile();
    readFromFile();
}
