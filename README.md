Projects: Virus Cluster Shooting Game
===
Week 10: The final ENVIRO project of EE520 course

Combination of hw10 task 3 and virus demo


Project Goal
===
Making a Virus Cluster Shooting Game

- ***Leader does circular movement and attach virus to become following red virus cluster.***
- ***Virus can infect cell. Infected cell will pops and populate more virus.***
- ***Player can manipulate car and shoot virus using bullet.***


Key Challenges
===

1. How to make virus following leader 

> In `virus.h`
> 
> Listened collision event of leader in `init()` function:
> 
> When colliding, virus attach to leader, set bool `follow` to be true and cancel listening collision of leader.
> ```c++
> //watch collision with leader, if leader collide, virus attach to leader   
> notice_collisions_with("Leader", [&](Event &e) {
>     Agent& leader = find_agent(e.value()["id"]);
>     attach_to(leader);
>     follow = true;
>     ignore_collisions_with("Leader");
> }); 
> ```

> Changed style of virus in `update()` function:
> 
> define `tem_style` json. 
> ```c++
> json tem_style() {
>     return {{"fill", "orange" }, 
>             {"stroke", "red"}, 
>             {"strokeWidth", "10px"},
>             {"strokeOpacity", "0.25"}
>            };
> }      
> ```
> 
> if `follow` is true, set virus style to be `tem_style`. 
> 
> ```c++
> set_style(tem_style());
> if (count-- <= 0) {
>     Agent& follow_virus = add_agent("FollowVirus", x(), y(), 0, FOLLOW_VIRUS_STYLE);
>     remove_agent(id());
> }
> ```

2. How to make virus following other followed virus
> Added `FollowVirus` repersenting following virus of leader.
> 
> Listened collision event of bullet/leader/follow virus in `init()` function:
> ```c++
> //if collide by bullet, follow virus disappear
> notice_collisions_with("Bullet", [&](Event &e) {
>     Agent& bullet = find_agent(e.value()["id"]);
>     vx = bullet.velocity().x;
>	  vy = bullet.velocity().y;
>	  ignore_collisions_with("Bullet");
>	  hit = true;
> }); 
> 
> //if collide with leader, virus follow and attach leader      
> notice_collisions_with("Leader", [&](Event &e) {
>	  Agent& leader = find_agent(e.value()["id"]);
>	  attach_to(leader);
> });  
> 
> //if collide with follow virus, follow this follow virus
> notice_collisions_with("FollowVirus", [&](Event &e) {
> 	  Agent& follow_virus = find_agent(e.value()["id"]);
>	  attach_to(follow_virus);
> });
> ```


Install and Run ENVIRO
===

To start a Docker container with ENVIRO pre-loaded into it, do:

```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:alpha bash
esm start
```

Make the project and start the enviro sever as follows.
```bash
make
enviro
```

Then navigate to `http://localhost` you should see this game. 

You can press `Ctrl-C` to stop the enviro server. 


Run Project
===
How to play this game:

- ***Leader automatically does circular movement and attach virus.***
- ***Virus randomly move around to infect cell or attach leader.***
- ***Player can manipulate car by A/ W/ S/ D on keyboard. Shooting bullet by pressing Space to hit virus.***


Reference
===
Github Repo:

[ENVIRO] (https://github.com/klavinslab/enviro) 

[EE520-W20] (https://github.com/klavins/EEP520-W20)


That's it!
===
Thank you for your patience~

<img src="https://media0.giphy.com/media/l0MYyDa8S9ghzNebm/source.gif">
