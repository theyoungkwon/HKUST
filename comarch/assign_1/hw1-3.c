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
#define MAX 4				// max number of input characters

char original_array[MAX];
char print_array[MAX];
int array_index[MAX] = {0};	// indexes for each depth
int cnt = 0;

void execute_anagram (int);
void permutation (int, int);
void print ();

void main () {

	char c;
	int size = 0;

	// read open
	FILE *fp = fopen("hw1-3_input.txt", "r");

	// file open error check
	if (fp == NULL) {
		printf("There is no input file\n");
		exit(-1);
	}

	// save array
	for (size = 0; fscanf(fp, "%c", &c) != EOF; size++) {
		// delete enter
		if (c != 10)
			original_array[size] = c;
		else
			size--;
	}

	// run anagram
	execute_anagram(size);
	
}

void execute_anagram (int size) {

	int i;

	// anagram example
	// if there are 4 characters
	// print all possible 4P1, 4P2, 4P3, 4P4
	for (i = 1; i <= size; i++)
		permutation(size, i);

}

void permutation (int n, int r) {

	int i, j;

	if (r==0) {
		// print characters if reaching last depth (first value of r)
		print();
	} else {
		for (i = 0; i < n; i++) {
			for (j = 0; j < cnt; j++) {
				// same point of character should not be print
				if (i == array_index[j])
					break;
			}

			if (j == cnt) {
				array_index[cnt] = i;

				// save character into print array
				print_array[cnt] = original_array[i];

				// increase depth before next permutation
				cnt++;

				// run next depth of permutation
				permutation(n, r-1);
				cnt--;
			}
		}
	}
}

void print () {

	int i;
	static int cnt_ = 1;

	for (i = 0; i < MAX; i++)
		printf("%c", print_array[i]);
	printf(" %d\n", cnt_++);

}
