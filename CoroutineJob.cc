#include <iostream>
#include <coroutine>

struct Job {
	
	struct promise_type;
	using handle_type = std::coroutine<promise_type>;

	handle_type coro;

	Job(handle_type h) : coro(h) {}
	~Job() {
		if (coro) coro.destroy();
	}

	void start() {
		coro.resume;
	}

	struct promise_type {
		
		auto get_return_type() {
			return Job{handle_type::from_promise(*this)};
		}

		auto initial_suspend() {
			std::cout << " Starting job" << '\n';
			return std::suspend_always{}
		}

		auto final_suspend() {
			std::cout << " Performin job " << '\n';
		}

		void return_void() {}
		void unhandled_exception() {}


	};

}

Job prepareJob() {
	co_await std::suspend_never();
}

int main() {
	
	std::cout << " Before Job "" << '\n';
	auto job = prepareJob();
	job.start();
	std::cout << "After JOb " << '\n';

}













