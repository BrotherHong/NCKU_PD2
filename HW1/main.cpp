#include<iostream>
using namespace std;

int main(int argc, char **argv) {
	int n = atoi(argv[1]);
	
	int mx = 0;

	for (int i = 0;i <= n;i++) {
		printf("(%d,%d)\n", i, n-i);
		mx = max(mx, i*(n-i));
	}

	printf("%d", mx);
	return 0;
}
