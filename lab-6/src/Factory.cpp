#include "../include/Factory.h"
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <iomanip>

NPCPtr NPCFactory::create(const std::string& type, int x, int y, const std::string& name) {
    // проверка границ
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        return nullptr;
    }

    if (type == "Squirrel") {
        return std::make_shared<Squirrel>(x, y, name);
    }
    if (type == "Werewolf") {
        return std::make_shared<Werewolf>(x, y, name);
    }
    if (type == "Druid") {
        return std::make_shared<Druid>(x, y, name);
    }
    return nullptr;
}

std::vector<NPCPtr> NPCFactory::load(const std::string& filename) {
    std::ifstream f(filename);
    std::vector<NPCPtr> result;
    if (!f) return result;

    // пропускаем заголовок (если он есть)
    {
        std::string header;
        std::getline(f, header);
    }

    std::unordered_set<std::string> names;
    std::string type, name;
    int x, y;
    while (f >> type >> x >> y >> name) {
        if (names.find(name) != names.end()) { // пропускаем дубликаты
            continue;
        } 
        auto npc = create(type, x, y, name);
        if (npc) {
            result.push_back(npc);
            names.insert(name);
        }
    }
    return result;
}

void NPCFactory::save(const std::vector<NPCPtr>& npcs, const std::string& filename) {
    std::ofstream f(filename);
    f << std::left << std::setw(12) << "Type"
      << std::left << std::setw(5) << "X"
      << std::left << std::setw(5) << "Y"
      << "Name\n";

    for (auto& npc : npcs) {
        f << std::left << std::setw(12) << npc->type()
          << std::left << std::setw(5) << npc->x
          << std::left << std::setw(5) << npc->y
          << npc->name << "\n";
    }
}
