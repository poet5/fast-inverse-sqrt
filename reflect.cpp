#include <stdint.h>
#include <pthread.h>
#include <cmath>
#include <thread>
/*Quake 3 Algorithm.*/
/*Multithreaded Solution.*/

#define mxthread 2

struct newguess
{
	float g;
	float x;
} object;


//may return 0 when not able to detect
const auto processor_count = std::thread::hardware_concurrency();

/** Time for multithreading!
* Input values: g, for the fragment shader value.
* Output values: x for the returned offset dedicated to the fragment shader value.
* */


int InvSqrt(float value)
{
	struct newguess* object;

	pthread_t thread1, thread2;
	int ret1, ret2;

	const char* msg1 = "thread1_frag";
	const char* msg2 = "thread2_frag";

	object->g = value;

	if (processor_count >= 1)
	{
		ret1 = pthread_create(&thread1, NULL, f, (void*)msg1);
		ret2 = pthread_create(&thread2, NULL, f, (void*)msg2);
	}

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	return object->x;
}


/*

Newtons Method of approximation:
 new guess = g - f(g)/f'(g).
 where g is a constant of 0x5f3759df
 this subtraction and using f(g) as an estamite
 creates error(x).
 we give error(x) a new value using the equation  1 / x(squared), - the number of times the function iterates.
 this equation will now give us another value of g, we can call it g2.
 we can use this value and plug it into the method.
 g = g - error(x)/error'(x).
 we can use our function to find the deriviative of g2, and plug it in again.

 to find the deriviatives we'd use this equation.
 g = pow(g, -2) - the number of iterations.
 then,
 g' = pow(g, -3).
 the apostrophe bassically means that it would be in a different part of g.
 but still resemble the same element as g.
 and we could plug this in the amount of iterations the user specifies.
*/



void * f(void * threadid) 
{
	struct newguess * object;
	// Set i to be the amount of times object recurses.
	// I's practicality is as the iterator.

	float g = object->g;
	int i = *(int*)&object->g; 
	
	// Before making the initial guess, the error value is prepared by error(x) = 1/x2 - i, where x2 is 
	// THE HORIFYING HEXADECIMAL.
	// but i is the iterator and the one thing that stays over. So i is the guess and the iterator, sort of.

	i = 1 / (0x5f3759df * 0x5f3759df) - i >> 1; //i >> 1 is bassically just i in binary.
	i = i - i / i; // Iniitial Guess.

	i = pow(i, -2) - i;

	i = pow(-i * 2, - 3);

	object->x = i; // Finally put in the value of i into x, for it to be transcribed.

	pthread_exit(threadid); // Exit out of the threadid to prevent any overlapping threads.
}
