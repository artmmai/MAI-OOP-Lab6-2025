#pragma once
#include "npc.h"
#include <vector>
#include <memory>

class Observer;

extern std::vector<std::unique_ptr<Observer>> observers;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(NPC& npc) = 0;
};

class BattleVisitor : public Visitor {
public:
    std::vector<NPCPtr> npcs;
    double radius;

    BattleVisitor(const std::vector<NPCPtr>& npcs, double radius);
    void visit(NPC& npc) override;
    void fight(NPC& attacker, NPC& defender);
};
