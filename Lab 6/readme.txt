//Cody Hubbard 004843389
//CS35L week 6

The main point of this homework assignment was to identify where multithreading 
could be used to optimize some given code for a ray tracer.

After throughly reviewing the code it becoame apperent that the extensive nested for loops
which were processing each pixel was a source of mass inefficency in this program and could
be easily optimized by using multithreading.

To do this I seperated the pixel calculating algorithm from the main source of the program
and then had every thread run an appropriate fraction of the total pixels. The main problem 
I had using this mehtod is the needless duplication of many variables across the multiple threads.
To circumvent this without passing a struct of arguments to each thread I used the (poor) programming
style of making several of them global variables; violating encapsulation.

The time output by a "make ckean check" on a default main.c is as follows:

	real    0m44.977s
	user    0m44.978s
	sys     0m0.000s
	mv 1-test.ppm.tmp 1-test.ppm
	time ./srt 2-test.ppm >2-test.ppm.tmp
	./srt: Multithreading is not supported yet.

	real    0m0.002s
	user    0m0.000s
	sys     0m0.001s
	make: *** [2-test.ppm] Error 1
	
After my multithreading modifications a "make ckean check" on gives the following output:
	
	real    0m44.755s
	user    0m44.709s
	sys     0m0.001s
	time ./srt 2-test.ppm >2-test.ppm.tmp && mv 2-test.ppm.tmp 2-test.ppm

	real    0m22.545s
	user    0m44.723s
	sys     0m0.002s
	time ./srt 4-test.ppm >4-test.ppm.tmp && mv 4-test.ppm.tmp 4-test.ppm

	real    0m11.274s
	user    0m44.714s
	sys     0m0.001s
	time ./srt 8-test.ppm >8-test.ppm.tmp && mv 8-test.ppm.tmp 8-test.ppm

	real    0m5.863s
	user    0m44.744s
	sys     0m0.004s
	for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
	
As the above data shows when the multithreading is increased to 8 cores the real time 
is DRASTICALLY decreased, from 44.755s with no multithreading at all to a 5.863s with 8 core multithreading.

This is around an 87% increase in efficiency by multithreading, so I would say my implementation was quite 
successful. Also looking at the above output the similarities in user time show a necessary consistancy in
all mult-threaded and non-muilt-theraded computations.
