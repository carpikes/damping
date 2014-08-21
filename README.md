
damping
=======

damping is a simple (and didactic) feedback systems simulator.

It allows you to watch what happens to a feedback system when you play with its input (_u_ parameter).

It works with second-order systems described by this equation:

![](http://www.sciweavers.org/tex2img.php?eq=%5Cbegin%7Bcases%7D%20%5Cdot%7Bx%7D%20%3D%20A%20%5Ccdot%20x%20%2B%20B%20%5Ccdot%20u%20%5C%5C%20y%20%3D%20C%20%5Ccdot%20x%20%2B%20d%20%5Ccdot%20u%20%5Cend%7Bcases%7D&bc=White&fc=Black&im=png&fs=12&ff=fourier&edit=0)

where 

![](http://www.sciweavers.org/tex2img.php?eq=A%20%3D%20%20%5Cbegin%7Bbmatrix%7Da_1%20%26%20a_2%20%5C%5C%20a_3%20%26%20a_4%20%5Cend%7Bbmatrix%7D%2C%20B%20%3D%20%20%5Cbegin%7Bbmatrix%7Db_1%20%5C%5C%20b_2%20%5Cend%7Bbmatrix%7D%2C%20C%20%3D%20%20%5Cbegin%7Bbmatrix%7Dc_1%20%26%20c_2%20%5Cend%7Bbmatrix%7D&bc=White&fc=Black&im=png&fs=12&ff=fourier&edit=0)


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
