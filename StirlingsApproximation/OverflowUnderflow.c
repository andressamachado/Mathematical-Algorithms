/*$begin show - bytes*/ 
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#include<math.h>

int main() { 
	int i; 
	float n, x;     
	n = 1.0; 
	
	for (i = 0; i <= 127; i++) {
		n = n * 2.0;          
		x = 1.0 / n;             
		printf("%d %e %E\n", i, x, n); } 
	return 0; 
}