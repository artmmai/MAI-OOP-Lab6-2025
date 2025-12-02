#pragma once
#include "npc.h"
#include <vector>
#include <string>

class NPCFactory {
public:
    static NPCPtr create(const std::string& type, int x, int y, const std::string& name);
    static std::vector<NPCPtr> load(const std::string& filename);
    static void save(const std::vector<NPCPtr>& npcs, const std::string& filename);
};

