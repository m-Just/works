#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEED 0  // change SEED after every use

int encrypt(int text, int buff);
int getKey(int* buff);

int main(int* argv, char* argc[]) {
	FILE* plain = fopen(argc[1], "r");
	FILE* ciper = fopen(argc[2], "w");
	FILE* pskey = fopen(argc[3], "w");
	
	srand(SEED);
	char ch, chtr; 
	int key = 0;
	while ((ch = fgetc(plain))!= EOF) {
		getKey(&key);
		fprintf(pskey, "%d ", key);
		chtr = (char)encrypt((int)ch, key); 
		fprintf(ciper, "%c", chtr);
	}
	return 0;
}

int encrypt(int text, int key) {
	return text ^ key;
	return 0;
}

int getKey(int* buff) {
	*buff = (int) (rand() + 0.5);	
	return 0;
}
