#include <iostream>
#include <coroutine>

template<typename T>
struct Generator {
	
	struct promise_type;
	using handle_type = std::coroutine_handle<promise_type>;
	handle_type coro;

	Generator(handle_type h) coro(h)  {}
	~Generator() {
		if (coro) {
			coro.destroy()
		}
	}

	Generator(Generator& const) = delete;
	Generator& operator=(Generator& const) = delete;

	Generator(Generator&& const oth) : coro(oth.coro) {
			oth.coro = nullptr;
	}

	Generator& operator=(Generator&& const oth) noexcept {
		coro = oth.coro;
		oth.coro = nullptr;
		return *this;
	}
	
	T getValue() {
		return coro.promise().current_value;
	}

	bool next() {
		coro.resume();
		return not coro.done();
	}

	struct promise_type {
	
		promise_type() = default;
		~promise_type()  = default;

		auto initial_suspend() {
			return std::suspend_always {};
		}
		
		auto final_suspend() {
			return std::suspend_always {};
		}

		auto get_return_object() {
			return Generator{handle_type::from_promise(*this)};
		}

		auto return_void() {
			return std::suspend_never{};
		}
		
		auto yield_value(const T value) {
			current_value = value;
			return std::suspend_always;
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


























