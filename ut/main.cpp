#include <iostream>
#include "../common/head.h"
using namespace std;
void test_z_high() {
	for (int distance = 12; distance < 1332; ++distance) {
		double t = sqrt(distance * 2 / 1);
		cout<<distance / t<<endl;
	}
}

int main() {
	test_z_high();
	return 1;
}
