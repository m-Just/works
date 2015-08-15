/*
 * Test File Generator
 * Copyright(2015) m.Just
 */

#define VERSION "0.4"

#include "testfile_gen.h"

void itoa(int in, char* buf) {
	int i, cmp = 1;
	for (i = 0; i < 2; i++) {
		if (in <= cmp) break;
		else cmp*=10;
	}
	int cnt = 0;
	for (cmp/=10; cmp > 1; cmp/=10) {
		buf[cnt] = in / cmp + 48;
		in -= (buf[cnt]-48)*cmp;
		cnt++;
	} buf[cnt] = in + 48;
	buf[cnt+1] = '\0';
}

void autogen(FILE* out_file, int caseNum) {	
	guide();

	/* Input and exception handling */
	double* seq;
	int numOfElements, genmode;
	do { 	
		printf("Generating mode? ");
		scanf("%d", &genmode); getchar(); 
	} while ((genmode < 1 || genmode > MODE_NUM) && printf("Invaild mode.\n"));

	printf("How many elements in case#%d? ", caseNum); scanf("%d", &numOfElements); getchar();
	if (numOfElements <= 0) { printf("Element number smaller than one. Program abort.\n"); exit(1); }
	else if (genmode == 4 && numOfElements < 3) {
		do { 	printf("Require at least 3 elements to generate a valid Fibonacci sequence.\n");
		 	printf("How many elements in case#%d? ", caseNum);
			scanf("%d", &numOfElements); getchar();
		}
		while (numOfElements < 3);
	}
	
	/* Generate panel */
	seq = (double*)malloc(sizeof(double)*numOfElements);
	switch (genmode) {
		case 1: arthmtrcPro(seq, numOfElements); break;
		case 2: geomtrcPro(seq, numOfElements);  break;
		case 3: randSeq(seq, numOfElements);     break;
		case 4: fiboSeq(seq, numOfElements);     break;
		case 5: pwrFun(seq, numOfElements); 	 break;
	}
	
	/* Output */
	int i;
	static int lastmode;
	static int format;
	static char dformat;
	static char out_format[10]; 
	
	static int format_copy;
	if (format_copy > 0) {
		format_copy++;	
		goto label_seperator;	
	}

	out_format[0] = '%'; out_format[1] = '\0';

	// Possible enhancement:
	// put format & seperator option into general setting before `autogen'
	// there is no need to inquire on every case
	label_format_option:
	printf(">>>Output format:\n");
	printf("1. Integer\n");
	printf("2. Floating number\n");
	printf("3. Character (ASCII)\n");  // how to output UNICODE character??
	printf("? ");
	scanf("%d", &format); getchar();

	switch (format) {
		case 1: dformat = 'd'; break;
		case 2: dformat = 'f'; break;
		case 3: dformat = 'c'; break;
		default: printf("Invalid format!\n"); goto label_format_option;
	}

	int len;
	if (format == 2) {
		int digits; len = strlen(out_format);
		char digits_char[2]; memset(digits_char, 0, sizeof(char)*2); // at most 99?
		do {	printf("How many decimal digits for output? ");
			scanf("%d", &digits); getchar();
		} while (digits < 0 && printf("Number of digits cannot be smaller than 0.\n"));
		out_format[len] = '.'; out_format[len+1] = '\0';
		itoa(digits, digits_char);      
		if (digits > 0) strcat(out_format, digits_char);
	}

	printf("Apply this format to all the following cases? (y/n) ");
	char temp = getchar();
	if (temp == 'y' || temp == 'Y') format_copy = 1; getchar();



	static char sep;
	static int sep_copy;
	label_seperator:
	if (sep_copy > 0) goto label_print;

	printf(">>>Seperate each elements by:\n");
	printf("0. Do not seperate\n");
	printf("1. Blank\n");
	printf("2. New line\n");
	printf("3. Tab\n");
	// customize seperator ?
	printf("? ");
	sep = getchar(); getchar();
	switch (sep) {
		case '0': sep = '\0'; break;
		case '1': sep = ' ';  break;
		case '2': sep = '\n'; break;
		case '3': sep = '\t'; break;
		default: printf("Invalid option!\n"); goto label_seperator;
	}
	printf("Apply this seperator to all the following cases? (y/n) ");
	temp = getchar();
	if (temp == 'y' || temp == 'Y') sep_copy = 1; getchar();

	label_print:
	if (format <= 2) {
		if (format_copy < 2) {
			len = strlen(out_format);
			out_format[len] = dformat;
			out_format[len+1] = '\0';
		}
		for (i = 0; i < numOfElements; i++) {
			if (format == 1) fprintf(out_file, out_format, (int)(seq[i]+0.5));
			else 		 fprintf(out_file, out_format, seq[i]); 
			if (i < numOfElements-1) { 
				if ('\0' != sep) fputc(sep, out_file);
			} else 	fputc('\n', out_file);
		}	
	} else
	if (format == 3) {
		if (format_copy < 2) {
			out_format[2] = out_format[1];
			out_format[1] = dformat;	
		}
		for (i = 0; i < numOfElements; i++) {
			fprintf(out_file, out_format, (char)seq[i]); 
			if (i < numOfElements-1) { 
				if ('\0' != sep) fputc(sep, out_file);
			} else 	fputc('\n', out_file);
		}
	} 

	free(seq);
}

void guide() {
	int i;
	printf("Auto-generator %s\n", VERSION);
	for (i = 1; i <= MODE_NUM; i++) {
		printf("%d. ", i);
		switch (i) {
			case 1: printf("Arithmetic progression\n"); break;
			case 2: printf("Geometric progression\n");  break;
			case 3: printf("Random sequence\n"); 	    break;
			case 4: printf("Fibonacci sequence\n");     break;
			case 5: printf("Power function\n"); 	    break;
		}
	}
}

void arthmtrcPro(double* seq, int n) {
	double firstTerm, proNum;

	printf("First term? "); 	scanf("%lf", &firstTerm); getchar();
	printf("Progression number? "); scanf("%lf", &proNum);    getchar();

	int i; seq[0] = firstTerm;
	for (i = 1; i < n; i++) seq[i] = seq[i-1] + proNum;
}

void geomtrcPro(double* seq, int n) {
	double firstTerm, proNum;

	printf("First term? "); scanf("%lf", &firstTerm); getchar();
	do { printf("Progression number? "); scanf("%lf", &proNum); getchar(); }
	while (proNum == 0 && printf("Progression number cannot be zero!\n"));

	int i; seq[0] = firstTerm;
	for (i = 1; i < n; i++) seq[i] = seq[i-1] * proNum;
}

void randSeq(double* seq, int n) {
	double upplim, lwrlim;
	char tmp;

	do {
		printf("Lower limit? "); scanf("%lf", &lwrlim); getchar();
		printf("Upper limit? "); scanf("%lf", &upplim); getchar();
		// do { printf("How many decimal digits? "); scanf("%d", &digits); tmp = getchar(); }   // long digits exception
		// while ((tmp != '\n' || digits < 0) && printf("Number of decimal digits must be a non-negative integer\n"));
	} while ((upplim < lwrlim && printf("Upper limit cannot be smaller than lower limit!\n")) ||
		 (upplim-lwrlim >= RAND_MAX && printf("The range is too large!\n")));

	int i;
	srand((unsigned int)time(NULL));  // use current time as seed
	for (i = 0; i < n; i++) {
		double r = (double)rand() + (double)rand() / RAND_MAX;
		if (upplim == lwrlim) seq[i] = upplim;
		else seq[i] = r - (int)(r/(upplim-lwrlim))*(upplim-lwrlim) + lwrlim;  // fmod: mod of floating num
	}
}

void fiboSeq(double* seq, int n /*n>2*/) {
	printf("First term? ");  scanf("%lf", seq);   getchar();
	printf("Second term? "); scanf("%lf", seq+1); getchar();

	int i;
	for (i = 2; i < n; i++) seq[i] = seq[i-1] + seq[i-2];
}

void pwrFun(double* seq, int n) {
	printf("Base num sequence: (default: Arithmetric Progression)\n");
	arthmtrcPro(seq, n);    // base num imported from arithmetic progression
	double pwr;

	printf("Power number? "); scanf("%lf", &pwr); getchar();
	
	int i;
	for (i = 0; i < n; i++) seq[i] = pow(seq[i], pwr);
}



int main(int agrc, char* agrv[]) {
	FILE* out_file = NULL;
	if (agrc == 2) out_file = fopen(agrv[1], "a"); // agrc = total num of para + 1; agrv[0] = the address of the program itself;
	else printf("usage: tfgen <filename>\n");

	if (out_file == NULL) { printf("Cannot create file. Program abort.\n"); exit(1); }

	int numOfCases = 0;
	printf("How many test cases? "); scanf("%d", &numOfCases); getchar();
	if 	(numOfCases > 0) fprintf(out_file, "%d\n", numOfCases);
	else if (numOfCases < 0) numOfCases*=-1;   // ignore test case number
	else exit(1);

	int i;
	for (i = 1; i <= numOfCases; i++) {
		printf("Case#%d auto-generate?(y/n) ", i);
		if ('y' == getchar() & '\n' == getchar()) autogen(out_file, i);
		
		/* manual input */
		else {
			printf("The input for test case#%d: ($ for the end of input)\n", i);
			while (1) {
				char c = getchar();
				if (c == '$') { 
					if (getchar() == '$') fprintf(out_file, "%c", c);
					else { fprintf(out_file, "%c", '\n'); setbuf(stdin, NULL); break; } // end of line & clear input buffer
				} else fprintf(out_file, "%c", c);
			}
		}
	}

	if (out_file) {}


	fclose(out_file); out_file = NULL;
	return 0;
}
