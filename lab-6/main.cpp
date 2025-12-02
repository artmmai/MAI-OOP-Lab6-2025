#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream> 
#include <iomanip>

#include "include/npc.h"
#include "include/Factory.h"
#include "include/Visitor.h"
#include "include/Observer.h"

extern std::vector<std::unique_ptr<Observer>> observers;

int main() {
    std::srand(std::time(nullptr));

    std::vector<NPCPtr> npcs;

    // === Генерация ===
    std::cout << "Generating...\n";

    for (size_t i = 0; i < 100; ++i) {
        int type = std::rand() % 3; // 0 squirrel, 1 werewolf, 2 druid
        int x = std::rand() % 501;
        int y = std::rand() % 501;

        std::string t =
            (type == 0 ? "Squirrel" :
             type == 1 ? "Werewolf" : "Druid");

        std::string name = t + std::to_string(i);

        npcs.push_back(NPCFactory::create(t, x, y, name));
    }

    // === Сохранение ===
    std::cout << "Saving...\n";
    NPCFactory::save(npcs, "../npc.txt");

    // === Загрузка ===
    std::cout << "Loading...\n";
    npcs = NPCFactory::load("../npc.txt");

    // === Добавляем наблюдателей ===

    // Очищаем старый лог, чтобы он начинался с заголовка
    {
        std::ofstream clear("../log.txt", std::ios::trunc);
    }

    observers.clear();
    observers.emplace_back(std::make_unique<FileObserver>("../log.txt"));
    observers.emplace_back(std::make_unique<ConsoleObserver>());

    // === Бои ===  
    std::cout << "Fighting...\n";

    for (int radius = 20; radius <= 100; radius += 10) {
        BattleVisitor visitor(npcs, radius);

        for (auto &npc : npcs)
            if (npc->is_alive())
                npc->accept(visitor);

        // Удаляем мертвых
        size_t before = npcs.size();
        npcs.erase(
            std::remove_if(npcs.begin(), npcs.end(),
                           [](const NPCPtr &n) { return !n->is_alive(); }), npcs.end());
        size_t killed = before - npcs.size();

        std::cout << "Fight stats ----------\n"
                  << "radius: " << radius << "\n"
                  << "killed: " << killed << "\n\n";
    }

    // === Выжившие ===
    std::cout << "Survivors:\n";
    std::cout << "Type        Name          Coordinates\n";
    for (auto &npc : npcs)
        std::cout << std::left
                << std::setw(12) << npc->type()
                << std::setw(14) << npc->name
                << "(" << npc->x << "," << npc->y << ")"
                << "\n";
    return 0;
}
