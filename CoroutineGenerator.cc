#include <iostream>
#include <coroutine>

template<typename T>
struct Generator {
	
	struct promise_type;
	/* 
		Our coroutine handle, used by the client to pause,
		resume or destroy it
		*/
	using handle_type = std::coroutine_handle<promise_type>;
	handle_type coro;

	Generator(handle_type h) : coro(h)  {}
	~Generator() {
		if (coro) {coro.destroy(); }
	}

	Generator(const Generator& ) = delete;
	Generator& operator=(const Generator& ) = delete;

	Generator(Generator&&  oth) : coro(oth.coro) {
			oth.coro = nullptr;
	}

	Generator& operator=(Generator&&  oth) noexcept {
		coro = oth.coro;
		oth.coro = nullptr;
		return *this;
	}
	
	T getValue() {
		// using the handler to return a value
		return coro.promise().current_value;
	}

	bool next() {
		// using the handler to resume the coroutine
		coro.resume();
		return not coro.done();
	}

	struct promise_type {
	
		promise_type() = default;
		~promise_type()  = default;

		auto initial_suspend() {
			// std::suspend_always - our coroutine
			// is suspended on initialization
			return std::suspend_always {};
		}
		
		auto final_suspend() noexcept {
			return std::suspend_always {};
		}

		auto get_return_object() {
			return Generator{handle_type::from_promise(*this)};
		}

		auto return_void() {
			return std::suspend_never{};
		}
		
		// returns an awaitable that we can pause
		// and resume
		auto yield_value(const T value) {
			current_value = value;
			return std::suspend_always{};
		}

		void unhandled_exception() {
			std::exit(1);
		}
		
		T current_value;
	};
};

Generator<int> getNext(int start = 0, int step = 1)
{
	auto value = start;
	while(true) {
		// using co_yield here
		// transforms our function to a coroutine
		co_yield value;
		value += step;
	}
}

int main() {
	
	std::cout << '\n';
	std::cout << "getNext()";

	auto gen = getNext();

	for (int i = 0;  i < 10; ++i)
	{
		// resumes our object from its
		// initial suspended state
		gen.next();
		std::cout << " " << gen.getValue(); 
	}

	
	auto gen2 = getNext(100. -10);
	std::cout << "\n";
	std::cout << "getNext(100, -10)";
	for (int i = 0;  i < 20; ++i)
	{
		gen2.next();
		std::cout << "  " << gen2.getValue();
	}

	std::cout << "\n";

	return 0;
}


























