#include "../include/Observer.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void FileObserver::on_kill(const std::string& killer, const std::string& victim) {
    bool empty = false;
    
    // проверяем, пустой ли файл (если его нет = пустой)
    std::ifstream in(filename);
    if (!in) {
        // файла нет или не открылся
        empty = true;
    } else {
        if (in.peek() == std::ifstream::traits_type::eof()) {
            empty = true;
        }
    }

    std::ofstream f(filename, std::ios::app);

    // если пустой — пишем заголовок
    if (empty) {
        f << std::left << std::setw(12) << "Killer"
          << std::left << std::setw(12) << "Victim" << "\n";
    }

    f << std::left << std::setw(12) << killer
      << std::left << std::setw(12) << victim << "\n";
}

void ConsoleObserver::on_kill(const std::string& killer, const std::string& victim) {
    std::cout << killer << " killed " << victim << "\n";
}
