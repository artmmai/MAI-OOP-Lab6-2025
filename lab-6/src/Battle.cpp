#include "../include/Battle.h"
#include "../include/Visitor.h"
#include <algorithm>

void run_battle(std::vector<NPCPtr>& npcs, double radius) {
    BattleVisitor visitor(npcs, radius);

    for (auto& npc : npcs)
        if (npc->is_alive()) npc->accept(visitor);

    npcs.erase(
        std::remove_if(npcs.begin(), npcs.end(),
                       [](const NPCPtr& p){ return !p->is_alive(); }),
        npcs.end()
    );
}
