# NRE-Utility
NRE-Utility is simple library implementing standard container found in STL and other functionnalities.  
It doesn't meet all requirement from the STL, but the interface is similar and make some assumptions in order to have better performance.

## Features
- Header only

- STL containers implementation :
    * Array, simple fixed size (at compilation) array.
    * Vector, dynamic size array, reallocating itself when needed.
    * StaticVector, fixed size array but with vector behavior (without reallocation).
    * UnorderedMap, based on HashTable with linear probing and robin-hood hashing optimisation (not standard complient).
    * String, simple implementation (similar to Vector) for a string.
    * Stack, simple adapter for stack behavior on other container.
    * ForwardList, single-linked list implementation
    * Pair, a basic object pair
    
- Common utilitary :
    * Observer/Observable implementation.
    * Singleton, simplest singleton using CRTP pattern for no runtime overhead.
    * StaticInterface, allowing the use of static polymorphism.
    * Stringable, any object inheriting from this class will be able to be printed on stream (using StaticInterface).
    * Uncopyable, inheriting from this class make the derived object uncopyable.
    * Id, simple typedef for 32bit unsigned int, allow abstraction for other NRE-API.
    * IException, a Stringable exception interface.
    
Every containers has been tested to match/outpass STL performance and work as intended.
  