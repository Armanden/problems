#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void generate_a(char *buf, int max_len) {
	int pos = 0;
	buf[pos++] = '2';
	buf[pos++] = '.';
	int n = 3;
	while (pos < max_len - 1) {
		pos += snprintf(buf + pos, max_len - pos, "%d", n);
		n++;
	}
	buf[max_len - 1] = '\0';
}

void generate_b(char *buf, int max_len) {
	int pos = 0;
	buf[pos++] = '3';
	buf[pos++] = '.';
	int n = 6;
	while (pos < max_len - 1) {
		pos += snprintf(buf + pos, max_len - pos, "%d", n);
		n += 3;
	}
	buf[max_len - 1] = '\0';
}

int main(void) {
	char a_str[100], b_str[100];
	generate_a(a_str, 100);
	generate_b(b_str, 100);
	printf("a = %s\n", a_str);
	printf("b = %s\n", b_str);
	double a = atof(a_str);
	double b = atof(b_str);
	printf("a * b = %.15f\n", a * b);
	return 0;
}
