#include <iostream>
#include <vector>
#include <memory>

class Actor
{
public:
    virtual ~Actor() = default;
    virtual void jump() = 0;
    virtual void fire() = 0;
};

class Player : public Actor
{
public:
    void jump() override { std::cout<<"player jump\n"; }
    void fire() override { std::cout<<"player fire\n"; }
    void dash() {std::cout<<"player dash\n";}
};

class Monster: public Actor
{
public:
    void jump() override { std::cout<<"monster jump\n"; }
    void fire() override { std::cout<<"monster fire\n"; }
    void guard() {std::cout<<"monster guard\n";}
};

class Command
{
public:
    virtual void exec(Actor& actor) = 0;
};

class JumpCommand : public Command
{
public:
    void exec(Actor& actor) override { actor.jump(); }
};

class FireCommand : public Command
{
public:
    void exec(Actor& actor) override { actor.fire(); };
};

class DashCommand : public Command
{
public:
    void exec(Actor& actor) override
    {
        Player* p = dynamic_cast<Player*>(&actor);

        if(p)
            p->dash();
    }
};

class Invoker
{
private:
    std::vector<std::unique_ptr<Command>> stack;

public:
    void execCommand(std::unique_ptr<Command> cmd, Actor& actor)  
    {
       cmd->exec(actor); 
       stack.push_back(std::move(cmd));
    }

    void execOnly(Command& cmd, Actor& actor)
    {
        cmd.exec(actor);
    }
};


int main()
{
    std::unique_ptr<Player> p1(new Player);
    std::unique_ptr<Player> p2(new Player);
    auto m = std::make_unique<Monster>();
    std::unique_ptr<Invoker> i(new Invoker);

    std::unique_ptr<JumpCommand> pjc(new JumpCommand);
    std::unique_ptr<FireCommand> pfc(new FireCommand);
    std::unique_ptr<DashCommand> pdc(new DashCommand);
    auto mjc = std::make_unique<JumpCommand>();

    i->execOnly(*pjc,*p1);
    i->execOnly(*pjc,*p1);
    i->execOnly(*pjc,*p1);
    i->execOnly(*pjc,*p1);
    i->execOnly(*pdc,*p1);
    i->execOnly(*pdc,*p1);
    i->execOnly(*pdc,*p1);
    // i->execCommand(std::move(pjc),*p1);
    // i->execCommand(std::move(pjc),*p1);
    // i->execCommand(std::move(pfc),*p1);

    return 0;
}