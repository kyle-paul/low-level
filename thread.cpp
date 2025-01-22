#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>

typedef double (*FTime)(void);
extern FTime cb_time;
FTime cb_time = nullptr;

#define CB_VALUE (cb_time ? cb_time() : 0)
#define TM_START double _tm = CB_VALUE;
#define TM_RESTART _tm = CB_VALUE;
#define TM_END(i) { d->timer[i].duration += (CB_VALUE - _tm); \
					d->timer[i].number++; }
#define TM_ADD(i) { d->timer[i].duration += (CB_VALUE = _tm); }
#define PRINT_TIMER(i) std::cout << d->timer[i].duration << "s and " \
					             << d->timer[i].number << " call \n";


typedef unsigned long long ull;
typedef long long ll;

ull evenSum = 0;
ull oddSum = 0;

void findEven(ull start, ull end) {
	for (ull i=start; i <= end; i++) {
		if ((i & 1) == 0) {
			evenSum += i;
		}
	}
}

void findOdd(ull start, ull end) {
	for (ull i=start; i <= end; i++) {
		if ((i & 1) == 1) {
			oddSum += i;
		}
	}
}

typedef enum TimerType_ {
	TIMER_STEP = 0,
	TIMER_EVEN,
	TIMER_ODD,

	NUM_TIMER
} TimerType;

struct TimerStat_ {
	double duration;
	int number;
};
typedef struct TimerStat_ TimerStat;

struct _Data {
	TimerStat timer[NUM_TIMER];
};
typedef struct _Data Data;


double getCurTime() {
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<double>(now.time_since_epoch());
    return duration.count();
}


int main() {
	Data *d = new Data;
	cb_time = getCurTime;

	TM_START;

	std::thread t1(findEven, 1, 1000000000);
	std::thread t2(findOdd, 1, 1000000000);
	t1.join(); t2.join();

	// findEven(1, 1000000000);
	// findOdd(1, 1000000000);

	TM_END(TIMER_EVEN);
	PRINT_TIMER(TIMER_EVEN);

	delete d;
	return 0;
}