#include <stdio.h>

int main() {
	int x, res;
	res = __builtin_ctz(x);
	printf("%d\n", res);
	return 0;
}
