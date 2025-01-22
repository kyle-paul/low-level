#include <iostream>
#include <thread>
#include <mutex>

int count = 0;
std::mutex m;

/*
Try lock function
1. std::try_lock
2. std::mutext::try_lock
3. std::shared_lock::try_lock
4. std::timed_mutex::try_lock
5. std::unique_lock::try_lock
6. std::shared_mutex::try_lock
7. std::recursive_mutex::try_lock
8. std::shared_timed_mutex::try_lock
9. std::recursive_timed_mutex::try_lock
*/

void add() {
	for (int i=0; i<10; i++) {
		if (m.try_lock()) {
			count++;
			m.unlock();
		}	
	}
}

int main() {
	std::thread t1(add);
	std::thread t2(add);

	t1.join();
	t2.join();

	std::cout << count << "\n";
}