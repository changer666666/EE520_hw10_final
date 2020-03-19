#ifndef __FOLLOW_VIRUS_AGENT__H
#define __FOLLOW_VIRUS_AGENT__H 

#include "enviro.h"
#include "styles.h"
#include <math.h>

using namespace enviro;

//Following virus: the virus following leader
class FollowVirusController : public Process, public AgentInterface {

    public:
    FollowVirusController() : Process(), AgentInterface(), hit(false) {}

    void init() {
        //if collide by bullet, follow virus disappear
        notice_collisions_with("Bullet", [&](Event &e) {
            Agent& bullet = find_agent(e.value()["id"]);
            vx = bullet.velocity().x;
            vy = bullet.velocity().y;
            ignore_collisions_with("Bullet");
            hit = true;
        }); 
        //if collide with leader, virus follow and attach leader      
        notice_collisions_with("Leader", [&](Event &e) {
            Agent& leader = find_agent(e.value()["id"]);
            attach_to(leader);
        });  
        //if collide with follow virus, follow this follow virus
        notice_collisions_with("FollowVirus", [&](Event &e) {
            Agent& follow_virus = find_agent(e.value()["id"]);
            attach_to(follow_virus);
        });
    }

    void start() {}
    //collide by bullet, virus pop and disappear
    void pop() {
        for ( double theta=0; theta < 2 * M_PI; theta += M_PI / 4) {
            Agent& frag = add_agent("VirusFragment", x(), y(), theta, VIRUS_FRAGMENT_STYLE);
            frag.omni_apply_force(
                50*cos(theta+M_PI/8) + vx, 
                50*sin(theta+M_PI/8) + vy
            );
        }  
        remove_agent(id());
    }    
    //when follow virus collide by bullet, it should pop
    void update() {        
        if ( hit ) {
            pop();
        } 
    }

    void stop() {}

    const int fmax = 100.0;
    bool hit;
    double vx, vy; 
};

class FollowVirus : public Agent {
    public:
    FollowVirus(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    FollowVirusController c;
};

DECLARE_INTERFACE(FollowVirus)

#endif
