#include "../include/npc.h"
#include "../include/Visitor.h"

void Squirrel::accept(Visitor& v) {
     v.visit(*this);
}

void Werewolf::accept(Visitor& v) {
    v.visit(*this);
}

void Druid::accept(Visitor& v) {
    v.visit(*this);
}
