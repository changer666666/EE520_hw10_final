#ifndef __BULLET_AGENT__H
#define __BULLET_AGENT__H 

#include "enviro.h"

using namespace enviro;

//bullet : shoot virus
class BulletController : public Process, public AgentInterface {

    public:
    BulletController() : Process(), AgentInterface(), counter(0) {}

    void init() {
        //if bullet collision Cell, remove it
        notice_collisions_with("Cell", [&](Event &e) {
            remove_agent(id());
        });               
    }

    void start() {}

    void update() {
        //if bullet exists longer than 20, remove it
        if ( counter++ > 20 ) {
            remove_agent(id());
        }
     }
    void stop() {}

    double counter;

};

class Bullet : public Agent {
    public:
    Bullet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BulletController c;
};

DECLARE_INTERFACE(Bullet)

#endif