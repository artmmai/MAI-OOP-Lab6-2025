#pragma once
#include <string>
#include <memory>

class Visitor;

class NPC {
public:
    int x{0};
    int y{0};
    std::string name;

    NPC(int x, int y, const std::string& name) : x(x), y(y), name(name) {}
    virtual ~NPC() = default;

    virtual void accept(Visitor& visitor) = 0;
    virtual std::string type() const = 0;

    bool is_alive() const { return alive; }
    void die() { alive = false; }

private:
    bool alive = true;
};

class Squirrel : public NPC {
public:
    using NPC::NPC;
    void accept(Visitor& visitor) override;
    std::string type() const override { return "Squirrel"; }
};

class Werewolf : public NPC {
public:
    using NPC::NPC;
    void accept(Visitor& visitor) override;
    std::string type() const override { return "Werewolf"; }
};

class Druid : public NPC {
public:
    using NPC::NPC;
    void accept(Visitor& visitor) override;
    std::string type() const override { return "Druid"; }
};

using NPCPtr = std::shared_ptr<NPC>;
