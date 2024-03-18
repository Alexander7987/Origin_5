#include <iostream>
#include <vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void warningLoading(std::string str) = 0;
    virtual void errorLoading(std::string str) = 0;
    virtual void fatalerrorLoading(std::string str) = 0;
};


class Observer1 : public Observer{
public:
    ~Observer1() = default;

    void warningLoading(std::string str) override {
        std::cout << str;
    }

    void errorLoading(std::string str) override {}
    void fatalerrorLoading(std::string str) override {}
};


class Observer2 : public Observer {
public:
    ~Observer2() = default;

    void errorLoading(std::string str) override {
        std::cout << str;
    }

    void warningLoading(std::string str) override {}
    void fatalerrorLoading(std::string str) override {}
};


class Observer3 : public Observer {
public:
    ~Observer3() = default;

    void fatalerrorLoading(std::string str) override {
        std::cout << str;
    }

    void errorLoading(std::string str) override {}
    void warningLoading(std::string str) override {}
};


class Observed {
public:
    void AddObserver(Observer* observer) {
        observers_.push_back(observer);
    }

    void warning(const std::string& message) const
    {
        std::string str = "warning: " + message;
        for (auto observer : observers_) {
            observer->warningLoading(str);
        }
    }

    void error(const std::string& message) const
    {
        std::string str = "error: " + message;
        for (auto observer : observers_) {
            observer->errorLoading(str);
        }
    }

    void fatalError(const std::string& message) const
    {
        std::string str = "fatalerror: " + message;
        for (auto observer : observers_) {
            observer->fatalerrorLoading(str);
        }
    }

    void RemoveObserver(Observer* observer) {
        auto it = std::remove(observers_.begin(), observers_.end(), observer);
        observers_.erase(it, observers_.end());
    }

private:
    std::vector<Observer*> observers_;
};


int main()
{
    Observer1 observer1;
    Observer2 observer2;
    Observer3 observer3;

    Observed observed;

    observed.AddObserver(&observer1);
    observed.AddObserver(&observer2);
    observed.AddObserver(&observer3);
    
    observed.warning("warning");
    std::cout << std::endl;
    observed.error("error");
    std::cout << std::endl;
    observed.fatalError("fatalError");

    return 0;
}
