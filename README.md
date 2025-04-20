# C++ Joins the Coroutine Party: What You Need to Know About C++20 Coroutines
Having worked with Kotlin and Go, I’ve seen how coroutines were introduced early in their language specifications. In contrast, C++ is older and arguably more mature than these newer languages, which have coroutines built-in or supported through DSLs like KTX in Kotlin.

But worry not, fellow C++ die-hards — with C++20, we finally got our gate pass to the coroutines party.
## NB 
This tutorial is divided into two parts. Part 1 introduces the key terminology and foundational concepts. In Part 2, we’ll explore detailed examples to apply what we've learned.

## What are coroutines
The term coroutine was first introduced in the 1960s by Melvin Conway.

Coroutines are special functions that can pause (suspend) and later continue (resume) their execution, all while preserving their state.

In a regular function, you simply call it and wait for it to return. But with a coroutine, you have more control — you can suspend it partway through, resume it later, or even destroy it while it's suspended.

## Example: Generator function
Time for some code; 
Here is a sample generator function without
the use of coroutines.
![Generator code!](/assets/old_generator.png "Old Generator Code")


![Generator code!](/assets/old_gen_terminal.png "Old Generator Code")

From the above code we can observe that
the oldSchoolGenerator() function returns all values.
What if we wanted to generate the numbers
lazily; that is a new number on every request.
 
## A coroutine generator function
![Coroutine Generator code!](/assets/keepGen_2.png "Coroutine Generator Code")

In our above code we used co_yield which transforms our 
function to a coroutine.
More on co_yield below.

## How to become a Coroutine
C++20 introduces keywords that assist us 
in interacting with coroutines

1. co_yield - supports generator functions.
   The generator function generates a new value
   everytime you call it.
2. co_return - used by a coroutine as its return statement
3. co_await expression - makes it possible to suspend
   and resume the execution of the expression.

A function becomes a coroutine if uses
any of the above keywords.

## Restrictions
1. Coroutines cannot have return statements.
2. Functions with variadic arguments, constexpr
   consteval functions, constructors and destructors
   and the main function cannot be coroutines.

## Components of a Coroutine
In C++, a coroutine consists of 

1. promise object 
1. coroutine handle
1. coroutine frame
1. An awaitable 

### The Promise Object
Specified with the promise_type name inside
the return type of the coroutine(Wrapper type).

Here is it's interface
![Promise object !](/assets/promise_type.png "promise_type")

### The Coroutine Handle
A coroutine handle is like a remote control for a coroutine.
It doesn't own the coroutine itself, buti it lets you
start it again(resume) or stop it completely(destory).
![Coroutine handle !](/assets/coro_handle.png "Coroutine handle")

### The Coroutine frame
It stores the coroutine data on the heap.

### An Awaitable
In a coroutine’s promise object, the functions yield_value, initial_suspend, and final_suspend all return something awaitable — meaning they control when and how the coroutine pauses or resumes.

C++20 defines two basic awaitables
	1. std::suspend_always
	2. std::suspend_never

The awaitables std::suspend_always and std::suspend_never are the
basic building blocks used int functions like initial_suspend and 
final_suspend.

Theses two functions are automatically called during a coroutine's
lifecycle - initial_suspend runs at the very beginning and final_suspend
runs at the very end of the coroutine's execution.

## Putting it all together
Now that we have all the bits and pieces required to build
our coroutine, lets jump into the murky waters of C++20 
coroutines

In this section we will put together a generator toy example
function to yield values successively on each request.

### A bit of housekeeping before we proceed
The table below shows how the C++20 coroutine
keywords resume, pause and end a coroutine.
![Coroutine handle !](/assets/keywords.png "Coroutine handle")

### The Awiater
The Awaiter is part of the elements that are
part of the coroutine.
There are two ways to get an Awaiter.

1. A co_await operator is defined.
2. The Awaitable becomes the Awaiter.

## Let's build our coroutine generator

At the heart of the coroutine is the object we can
suspend, pause, resume and destroy.
How do we make an object resumable ?

Earlier we were introduced to the promise object, this
is what ewe need to mplement in our object to make it resumable.

A promise needs at least one of the member functions
1. return_value
2. return_voi
3. yield_value

These three functions return awaitables.
1. yield_value
2. initial_suspend
3. final_suspend

Remember an Awaitable is something you can wait on.
The awaitable determines if the coroutine pauses or not.
![Coroutine handle !](/assets/full_generator.png "Coroutine handle")

We override the yield_value() function in the promise_type object
which takes a value and returns an Awaitable.

Now that we have an resumable, pausable and destroyable object
it's time we now use it in our coroutine function

![Coroutine handle !](/assets/coroutine_func.png "Coroutine handle")

The code above shows our coroutine function.

And finally here is our main() function 
![Coroutine handle !](/assets/main_func_gen.png "Coroutine handle")

## Conclusion
From our generator example we have seen how we
can use coroutines.

One important thing to note is that coroutines are non-blocking
and can be used to replace threads which are expensive
quite verbose in their implementation.

### Applications of coroutines
1. Co-operative multitasking
2. Event-driven applications 

More examples on co_return and co_await are 
available on the github repository link.




