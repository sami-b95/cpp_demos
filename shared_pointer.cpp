#include <chrono>
#include <iostream>
#include <numeric>
#include <thread>

/***
	 Starts a "greedy thread" allocating both a raw pointer and a shared one. By 
	 constantly monitoring the memory occupied by the process, one can see the 
	 space allocated to the shared pointer is freed once the greedy thread 
	 terminates, while the raw space allocated to the raw one is not.
***/

#include <boost/format.hpp>

#define SIZE		10 * 1024 * 1024
#define SIZE_SHARED	30 * 1024 * 1024

void greedy_thread() {
	int *p = new int[SIZE];
	boost::shared_ptr<int> shared_p = boost::shared_ptr<int>(new int[SIZE_SHARED]);
	std::iota(p, p + SIZE, 0);
	std::iota(shared_p.get(), shared_p.get() + SIZE_SHARED, 0);
	std::cout << "greedy thread" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(20000));
}

int main() {
	std::cout << "started" << std::endl;
	std::thread t(greedy_thread);
	std::cout << "joining greedy thread" << std::endl;
	t.join();
	std::cout << "greedy thread ended" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(20000));
	std::cout << "ending" << std::endl;
	return 0;
}
