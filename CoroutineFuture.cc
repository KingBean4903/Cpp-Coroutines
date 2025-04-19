#include <coroutine>
#include <iostream>
#include <memory>

template<typename T>
struct FutureObj {

	std::shared_ptr<T> val;

	FutureObj() {}
	
	~FutureObj(){}
	
	T get() {
		return *val;
	}
	
	struct promise_type {
		std::shared_ptr<T> ptr = std::make_shared<T>();
		
		promise_type() {}
		
		FutureObj<T> get_return_object() {
			return ptr;
		}

		void return_value(T t) {
			*ptr = t;
		}

		std::suspend_never initial_suspend() {
			return {};
		}

		std::suspend_never final_suspend() noexcept { 
			return {};
		}

		void unhandled_exception() {
			std::exit(1);
		}
		
	};
};

FutureObj<int> fetchFuture() {
	co_return 1024;
}

int main() {
	
	std::cout << '\n';
	auto val = fetchFuture();
	std::cout << val.get() << '\n';

	return 0;

}
