#ifndef TFGEN_H
#define TFGEN_H


#define MODE_NUM 5

void itoa(int in, char* buf);

void autogen(FILE* out_file, int caseNum);

void guide();

void arthmtrcPro(double* seq, int n);
void geomtrcPro(double* seq, int n);
void randSeq(double* seq, int n);
void fiboSeq(double* seq, int n);
void pwrFun(double* seq, int n);

#endif
