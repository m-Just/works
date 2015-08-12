#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEED 0  // change SEED after every use

int encrypt(int text, int buff);
int getKey(int* buff);

/* One Time Pad Encrypter dev (using PRNG)
 * usage:  ./otp [origin_file] [output_file] [key_file]
 * To decrypt a file, encrypt the encrypted file.
 * 
 * NOTICE: this encrypter is not safe, do not use in
 * formal encryption, because the SEED can be found
 * by brute force search.
 *
 * by m.Just 2015-08-11
 */

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

	fclose(plain);
	fclose(ciper);
	fclose(pskey);

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
