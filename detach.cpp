#include <iostream>
#include <thread>
#include <chrono>

void run(int count) {
	while(count --> 0) {
		std::cout << count << "\n";
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main() {
	std::thread t1(run, 10);
	std::cout << "main before\n";

	if (t1.joinable()) {
		// the main thread would wait this thread to finish
		t1.join();
	}
	std::cout << "main after\n";
	return 0;
}