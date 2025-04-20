#C++ Is late to<F5> the Coroutine party
Having worked on Kotlin and Go, coroutines were
early addons to their language specifications,
but we can argue that C++ is older and wiser
than the younger new languages who have coroutines
baked into their spec or in some form of DSL like
ktx for Kotlin.
But, worry not C++ die hard,  C++20 got us a gate pass to the 
coroutines party.

##What are coroutines
The term coroutine was coined back in the 60s by
Melvin Conway.

Coroutines are functions that can suspend and resume
their execution while keeping their state.

In a normal function call you only call a function
and return from it but in a coroutine you can 
suspend and resume it and destroy a suspended 
coroutine.

##Example: Generator function
Time for some code; 
Here is a sample generator function without
the use of coroutines.
![Generator code!](/assets/old_generator.png "Old Generator Code")




From the above code we can observe that
the generator() function returns all values.
What if we wanted to generate the numbers
lazily; that is a new number on every request.

##Appyling Coroutines to Generator

fROM THE 




##How to become a Coroutine
C++20 introduces keywords that assist us 
in interacting with coroutines
1. co_yield 
2. co_await
3. co_return

A function becomes a coroutine if uses
the above keywords.

Future<int> fetchFuture() {
	co_retun 40;
}

##Components of a Coroutine
In C++, a coroutine consists of 

1. promise object 
1. coroutine handle
1. coroutine frame
1. An awaitable 

###The Promise Object
Specified with the promise_type inside
the return type of the coroutine.

###The Coroutine Handle

###The Coroutine frame

###An Awaitable

















