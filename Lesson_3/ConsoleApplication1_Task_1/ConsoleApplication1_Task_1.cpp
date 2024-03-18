#include <iostream>
#include <fstream>
#include <string>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message_) = 0;
};


class LogCommand1 : public LogCommand
{
public:
    void print(const std::string& message_) override
    {
        std::cout << message_;
    }
};

class LogCommand2 : public LogCommand
{
public:
    LogCommand2(std::ofstream& f) : f(f) {}

    void print(const std::string& message_) override
    {
            f << message_;
    }

private:
    std::ofstream& f;
};


void print(LogCommand* command, std::string message_)
{
    command->print(message_);
}

int main()
{
    std::ofstream f("");
    LogCommand1 command1;
    LogCommand2 command2(f);
    print(&command1, "Hello World");
    return 0;
}

