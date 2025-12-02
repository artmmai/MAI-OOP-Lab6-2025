#include <gtest/gtest.h>
#include "../include/npc.h"
#include "../include/Factory.h"
#include "../include/Visitor.h"
#include "../include/Observer.h"
#include <memory>
#include <vector>
#include <fstream>

// Глобальная переменная для тестов
std::vector<std::unique_ptr<Observer>> observers;

// Вспомогательный класс для тестирования логирования
class TestObserver : public Observer {
public:
    std::vector<std::pair<std::string, std::string>> kills;

    void on_kill(const std::string& killer, const std::string& victim) override {
        kills.emplace_back(killer, victim);
    }
};

TEST(NPCFactoryTest, CreateNPCs) {
    auto s = NPCFactory::create("Squirrel", 1, 2, "S1");
    auto w = NPCFactory::create("Werewolf", 3, 4, "W1");
    auto d = NPCFactory::create("Druid", 5, 6, "D1");
    auto n = NPCFactory::create("Unknown", 0, 0, "X");

    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->type(), "Squirrel");
    EXPECT_EQ(s->x, 1);
    EXPECT_EQ(s->y, 2);
    EXPECT_EQ(s->name, "S1");

    ASSERT_NE(w, nullptr);
    EXPECT_EQ(w->type(), "Werewolf");
    EXPECT_EQ(w->x, 3);
    EXPECT_EQ(w->y, 4);
    EXPECT_EQ(w->name, "W1");

    ASSERT_NE(d, nullptr);
    EXPECT_EQ(d->type(), "Druid");
    EXPECT_EQ(d->x, 5);
    EXPECT_EQ(d->y, 6);
    EXPECT_EQ(d->name, "D1");

    EXPECT_EQ(n, nullptr);
}

TEST(NPCFactoryTest, SaveAndLoad) {
    std::vector<NPCPtr> npcs;
    npcs.push_back(NPCFactory::create("Squirrel", 1, 2, "S1"));
    npcs.push_back(NPCFactory::create("Werewolf", 3, 4, "W1"));
    npcs.push_back(NPCFactory::create("Druid", 5, 6, "D1"));

    NPCFactory::save(npcs, "test_npc.txt");
    auto loaded = NPCFactory::load("test_npc.txt");

    ASSERT_EQ(loaded.size(), 3);
    EXPECT_EQ(loaded[0]->type(), "Squirrel");
    EXPECT_EQ(loaded[1]->type(), "Werewolf");
    EXPECT_EQ(loaded[2]->type(), "Druid");
    EXPECT_EQ(loaded[0]->x, 1);
    EXPECT_EQ(loaded[1]->x, 3);
    EXPECT_EQ(loaded[2]->x, 5);
}

TEST(BattleVisitorTest, FightKillsCorrectly) {
    auto s = std::make_shared<Squirrel>(0, 0, "S1");
    auto w = std::make_shared<Werewolf>(1, 1, "W1"); // в радиусе
    auto d = std::make_shared<Druid>(50, 50, "D1");  // вне радиуса

    std::vector<NPCPtr> npcs = {s, w, d};
    observers.clear();
    auto obs = std::make_unique<TestObserver>();
    TestObserver* obsPtr = obs.get();
    observers.push_back(std::move(obs));

    BattleVisitor visitor(npcs, 5.0);
    for (auto& npc : npcs)
        npc->accept(visitor);

    EXPECT_FALSE(w->is_alive());
    EXPECT_TRUE(s->is_alive());
    EXPECT_TRUE(d->is_alive());

    ASSERT_EQ(obsPtr->kills.size(), 1);
    EXPECT_EQ(obsPtr->kills[0].first, "S1");
    EXPECT_EQ(obsPtr->kills[0].second, "W1");
}

TEST(BattleVisitorTest, NoKillOutsideRadius) {
    auto s = std::make_shared<Squirrel>(0, 0, "S1");
    auto w = std::make_shared<Werewolf>(10, 10, "W1"); // вне радиуса

    std::vector<NPCPtr> npcs = {s, w};
    observers.clear();
    BattleVisitor visitor(npcs, 5.0);
    for (auto& npc : npcs)
        npc->accept(visitor);

    EXPECT_TRUE(s->is_alive());
    EXPECT_TRUE(w->is_alive());
}

TEST(NPCDeathTest, DieMethodWorks) {
    auto s = std::make_shared<Squirrel>(0, 0, "S1");
    EXPECT_TRUE(s->is_alive());
    s->die();
    EXPECT_FALSE(s->is_alive());
}
