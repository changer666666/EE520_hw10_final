#ifndef __VIRUS_FRAGMENT_AGENT__H
#define __VIRUS_FRAGMENT_AGENT__H 

#include "enviro.h"
#include <math.h>

using namespace enviro;

//virus fragment : the fragment of virus when it pops
class VirusFragmentController : public Process, public AgentInterface {

    public:
    VirusFragmentController() : Process(), AgentInterface() {}

    void init() {
        //set a random time of each fragment
        counter = rand() % 8;
    }
    void start() {}
    void update() {
        //when counter less or equals to zero, remove this fragment
        if ( counter-- <= 0 ) {
            remove_agent(id());
        }
    }
    void stop() {}
    int counter;
    const int fmax = 10;

};

class VirusFragment : public Agent {
    public:
    VirusFragment(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    VirusFragmentController c;
};

DECLARE_INTERFACE(VirusFragment)

#endif