#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <set>
#include <atomic>
#include <mutex>
#include <thread>
#include <omp.h>

const int size = 10000;

void work(byte* mat) {
	// pixel iterator
	for (int i = 0; i < size * size; i++) {
		int iter = i * 3;
		byte aver = (mat[iter] * 0.256 + mat[iter + 1] * 0.563 + mat[iter + 2] * 0.126) / 3;
		mat[iter] = mat[iter + 1] = mat[iter + 2] = aver;
	}
}
void work_optimized(byte* mat) {
	// pixel iterator
	for (int i = 0; i < size * size; i++) {
		int iter = i * 3;
		byte aver = ((mat[iter] >> 2) + (mat[iter + 1] >> 1) + (mat[iter + 2] >> 3) + 255) >> 2;
		mat[iter] = mat[iter + 1] = mat[iter + 2] = aver;
	}
}
inline bool
isLess(int a, int b) {
	return (a - b) >> 31;
}

void kek(int core) {
	while (1) {
		static uint64_t a = 0;
		a += std::pow(core, core + 1);
	}
}

int main() {

	const int cores = 8;
	byte** mats = new byte * [cores];
	std::thread th[cores];

	const int elem_num = size * size * 3;
	const byte b = 202;
	const byte g = 99;
	const byte r = 159;

	for (int i = 0; i < cores; i++) {
		mats[i] = new byte[elem_num];
		for (int j = 0; j < size; j++) {
			mats[i][j] = b;
			mats[i][j + 1] = g;
			mats[i][j + 2] = r;
		}
	}

	auto start = std::chrono::steady_clock::now();
	// 8 cores
	for (int i = 0; i < cores; i++)
		th[i] = std::thread(work, mats[i]);
	for (int i = 0; i < cores; i++)
		th[i].join();

	/*for (int i = 0; i < cores; i++)
		work(mats[i]);*/

	auto stop = std::chrono::steady_clock::now();
	std::cout << "time for 8 cores = " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << std::endl;

	/*while (1) {
		bool click = false;
		for (int i = 0; i < 255; i++)
			if (GetAsyncKeyState(i) == -32767)
				click = true;
		if (click) {
			keybd_event(VK_CAPITAL, 0, 0, 0);
			Sleep(50);
			keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
		}
	}*/


}