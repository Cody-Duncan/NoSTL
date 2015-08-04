# Z Standard Library
A standard library for use in memory conscious applications. 

This library will develop along-side other projects. May work on it specifically, but for now I will integrate types as I make them.

###Rationale:
* STL has a lot of cruft to support backwards compatibility. Want to avoid.
* Need statically allocating data structures. Avoid dynamic allocation.
* Need simple utility types like optional and bitflag.
* Need code that I understand. Standard lib code is often written with tons of macros to deal with various platforms, compilers, etc. Want code I can reuse without all the stuff.
* Need math functions and types that work without tons of template abstraction. Vector4f, not Vector4<float>

###Development Roadmap:

1. static_string stub. Simple functionality now, and utility functionality later.



###Pillars:

1. Reliability
	- Units should be as bug free as possible.
	- Units should report errors as soon as possible, and with great clarity
	
2. Clarity
	- Memory usage of a unit should be clear
		- Collection data structures should implement a static and dynamic counterpart
	- Must be written clearly enough to be reused or extended
	- Avoid tricks in Macros and Templates that make things unclear.
	
3. Performance
	- Must be peformant enough to be usable.
	- Avoid dynamic memory allocations where possible
	- Avoid virtual functions where possible.

4. API
	- All elements of the interface should be non-ambiguous
	- Ambiguous elements should be removed. Leave no "tricks".
	- API should use modern standards of coding and language capabilities

5. Future-Compliant
	- Elements of the source that use old or deprecated mechanisms should be rewritten or removed
	- Use STL as little as possible. 
		- Where STL is new, use it.
		- Where STL is old, write a new utility to replace STL functionality.

6. The Basics
	- Provide only what is needed, and no more.
	- Provide only Basic Elements of programming tools. Do not get complex.
	- Provide parts in separable chunks. Do not require inclusion of the whole to get at one piece.
