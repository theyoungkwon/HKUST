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
#define MAX 11	// maximum heap size+1

int heap[MAX];
int insert_heap (int, int);
void swap (int *, int *);
void print_heap (int);

void main () {

	int input, curr = 1;
	FILE *fp;

	// file open
	fp = fopen("hw1-2_input.txt", "r");

	// file open error check
	if (fp == NULL) {
		printf("There is no input file\n");
		exit(-1);
	}

	// insert input into heap
	while (fscanf(fp, "%d", &input) != EOF) {
		insert_heap(curr, input);
		curr ++;
	}

	// file close
	fclose(fp);

	// print heap
	print_heap(curr);

}

// root of heap is 1 in arr index.
int insert_heap (int curr, int input) {

	int i = curr;

	// just put input in the last index
	heap[curr] = input;

	// compare to upper value
	while ((i != 1) && (heap[i] > heap[i/2])) {
		swap(&heap[i], &heap[i/2]);
		i = i/2;
	}

}

void swap (int *a, int *b) {

    int t = *a;
    *a = *b;
    *b = t;

}

void print_heap (int curr) {

	int i, level = 0;
	int print_cnt = 0, level_num = 1;

	for (i = 1; i < curr; i++) {
		if (print_cnt == level_num) {
			level ++;
			level_num *= 2;
			print_cnt = 0;
			printf("\n---------------\n");
		}
		printf(" %d ", heap[i]);
		print_cnt ++;
	}
	printf("\n");

}
