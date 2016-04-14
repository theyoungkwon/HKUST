// ------------------------------------------------------------
//
// ICE3003-43 Computer Architecture (Spring 2014)
// 
// Instructor: Prof. Jae W. Lee (jaewlee@skku.edu)
//
// Authors: Chung Ha Sung   (sch8906@gmail.com) 
//          Yunkeuk Kim     (giocafe87@gmail.com)
//
// Description:
//
// Please refer to Lab #1 description slides available at the
// course website on iCampus.
//
// Copyright (C) 2014 SungKyunKwan University 
// 
// -----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

int fib (int);

void main () {

	int input, result;
	FILE *fp;

	// file open
	fp = fopen("hw1-1_input.txt", "r");

	// file open error check
	if (fp == NULL) {
		printf("There is no input file\n");
		exit(-1);
	}
	
	// read input
	fscanf(fp, "%d", &input);

	// file close
	fclose(fp);

	// get result from fib
	result = fib(input);	
	
	// print result
	printf("Result of Fibonacci: %d\n", result);

}

int fib (int input) {

	if (input == 0)
		return 0;
	else if (input == 1)
		return 1;
	else
		return fib(input-1) + fib(input-2);

}
