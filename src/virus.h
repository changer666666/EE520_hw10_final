#ifndef __VIRUS_AGENT__H
#define __VIRUS_AGENT__H 

#include "enviro.h"
#include "styles.h"
#include <math.h>

using namespace enviro;

//virus, can infect cell and attach to leader
class VirusController : public Process, public AgentInterface {

    public:
    VirusController() : Process(), AgentInterface(), hit(false), follow(false), count(10) {}

    void init() {
        //watch collision with bullet, if bullet collide, virus disappears
        notice_collisions_with("Bullet", [&](Event &e) {
            Agent& bullet = find_agent(e.value()["id"]);
            vx = bullet.velocity().x;
            vy = bullet.velocity().y;
            ignore_collisions_with("Bullet");
            hit = true;
        });    
        //watch collision with leader, if leader collide, virus attach to leader   
        notice_collisions_with("Leader", [&](Event &e) {
            Agent& leader = find_agent(e.value()["id"]);
            attach_to(leader);
            follow = true;
            ignore_collisions_with("Leader");
        });   
        //watch collision with follow virus, if follow virus collide, virus attach to follow virus
        notice_collisions_with("FollowVirus", [&](Event &e) {
            Agent& follow_virus = find_agent(e.value()["id"]);
            attach_to(follow_virus);
            follow = true;
            ignore_collisions_with("FollowVirus");
        });  
    }

    void start() {}

    //virus disappear
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

    void update() {
        if ( !follow ) {
            //if virus not follow others, set random velocity 
            double d = sqrt(x()*x() + y()*y()),
                vx = -x() / ( 1 + d ),
                vy = -y() / ( 1 + d );        
            omni_apply_force(
                (rand() % fmax) - fmax/2 + 2*vx, 
                (rand() % fmax) - fmax/2 + 2*vy
            );
        } else {
            //if virus follow others, set different style.
            //when counter less or equals to 0, virus disappear, and follow virus appear
            set_style(tem_style());
            if (count-- <= 0) {
                Agent& follow_virus = add_agent("FollowVirus", x(), y(), 0, FOLLOW_VIRUS_STYLE);
                remove_agent(id());
            }
        }
        //if hit by bullet, virus will disappear
        if ( hit ) {
            pop();
        } 
    }

    void stop() {}

    const int fmax = 100.0;
    bool hit;
    bool follow;
    double vx, vy; 
    int count;
    json tem_style() {
        //the temporary style of virus when collide by leader or follow virus
        // { "fill": "orange", "stroke": "black", "strokeWidth": "10px", "strokeOpacity": "0.25" }
        return {  {"fill", "orange" }, 
                  {"stroke", "red"}, 
                  {"strokeWidth", "10px"},
                  {"strokeOpacity", "0.25"}
              };
    }        

};

class Virus : public Agent {
    public:
    Virus(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    VirusController c;
};

DECLARE_INTERFACE(Virus)

#endif
