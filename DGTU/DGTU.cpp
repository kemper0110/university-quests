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

const int size = 5000;
char* mat1;
char* mat2;
char* mat3;
char* mat4;

void work(char* mat) {
	// pixel iterator
	for (int i = 0; i < size * size; i++) {
		int iter = i * 3;
		char aver = (mat[iter] * 0.256 + mat[iter + 1] * 0.563 + mat[iter + 2] * 0.126) / 3;
		mat[iter] = mat[iter + 1] = mat[iter + 2] = aver;
	}
}

int main() {
	//keybd_event(VK_NUMLOCK, 0, 0, 0);
	while (1) {
		bool click = false;
		for (int i = 0; i < 255; i++)
			if (GetAsyncKeyState(i) == -32767)
				click = true;
		if (click) {
			keybd_event(VK_CAPITAL, 0, 0, 0);
			Sleep(50);
			keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
		}
	}

	//char* mats[4] = { mat1, mat2, mat3, mat4 };
	//for (int i = 0; i < 4; i++)
	//	mats[i] = new char[size * size * 3];
	//for (int j = 0; j < 4; j++)
	//	for (int i = 0; i < size * size * 3; i++)
	//		mats[j][i] = rand() % 255;

	//auto start = std::chrono::steady_clock::now();
	///*for (int i = 0; i < 4; i++)
	//	work(mats[i]);*/

	///*std::thread th[3];
	//for (int i = 0; i < 3; i++)
	//	th[i] = std::thread(work, mats[i]);
	//work(mats[3]);
	//for (int i = 0; i < 3; i++)
	//	th[i].join();*/

	//auto stop = std::chrono::steady_clock::now();
	//int x = mats[0][0] + mats[1][0] + mats[2][0] + mats[3][0];
	//std::cout << x << std::endl;
	//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();


}