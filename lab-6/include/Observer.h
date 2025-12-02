#pragma once
#include <string>
#include <vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void on_kill(const std::string& killer, const std::string& victim) = 0;
};

class FileObserver : public Observer {
    std::string filename;
public:
    FileObserver(const std::string& fname = "log.txt") : filename(fname) {}
    void on_kill(const std::string& killer, const std::string& victim) override;
};

class ConsoleObserver : public Observer {
public:
    void on_kill(const std::string& killer, const std::string& victim) override;
};
