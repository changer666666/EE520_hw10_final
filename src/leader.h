#ifndef __LEADER_AGENT__H
#define __LEADER_AGENT__H 

#include "enviro.h"
#include "styles.h"

using namespace enviro;

//leader of virus chain
class LeaderController : public Process, public AgentInterface {

    public:
    LeaderController() : Process(), AgentInterface() {}

    void init() {
    }
    void start() { }
    void update() {
        //set velocity and angle move strength
        track_velocity(8, 12);
    }
    void stop() {}
};

class Leader : public Agent {
    public:
    Leader(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    LeaderController c;
};

DECLARE_INTERFACE(Leader)

#endif