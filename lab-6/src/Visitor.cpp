#include "../include/Visitor.h"
#include "../include/Observer.h"
#include <cmath>

BattleVisitor::BattleVisitor(const std::vector<NPCPtr>& npcs, double radius)
    : npcs(npcs), radius(radius) {}

void BattleVisitor::visit(NPC& npc) {
    for (auto& other : npcs) {
        if (!other->is_alive()) continue;
        if (other.get() == &npc) continue;

        double dist = std::hypot(npc.x - other->x, npc.y - other->y);
        if (dist <= radius) fight(npc, *other);
    }
}

void BattleVisitor::fight(NPC& attacker, NPC& defender) {
    std::string a = attacker.type();
    std::string d = defender.type();

    bool can_kill =
        (a == "Squirrel" && d == "Werewolf") ||
        (a == "Squirrel" && d == "Druid") ||
        (a == "Werewolf" && d == "Druid");

    if (can_kill) {
        for (auto& obs : observers)
            obs->on_kill(attacker.name, defender.name);

        defender.die();
    }
}
