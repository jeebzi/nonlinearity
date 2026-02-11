/*
 * petit programme juste pour regarder la différence des instructions machine
 * en compilant avec et sans -mpopcnt
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int res;
	res = __builtin_popcount(atoi(argv[2]));
	printf("%d\n", res);
	return 0;
}
