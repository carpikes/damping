damping tool
=======

damping is a simple feedback systems simulator.

It allows you to watch what happens to a feedback system when you play with its input (_u_ parameter).

It works with second-order systems described by this equation:

![](http://i.imgur.com/jNywEt0.png)

where 

![](http://i.imgur.com/Rhdu74C.png)


Screenshots
-------

![Screenshot](http://i.imgur.com/BqvLK5I.png)


Configuration
-------

Using config.ini you can change these parameters:

* A,  real matrix (2x2)
* B,  real matrix (2x1)
* C,  real matrix (1x2)
* d,  real number
* x0, real matrix (1x2), initial state of the system.
* u,  real number, input 1 
* i,  real number, input 2 


Key shortcuts
-------

While the simulator is running, it listens for these keystrokes:

* r: reload config.ini
* u: set _u_ <- input 1
* i: set _u_ <- input 2
