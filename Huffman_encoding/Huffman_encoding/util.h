#pragma once
#include <iostream>
#include <math.h>
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <bitset>
#include <vector>
#include <stack>
#include <list>

typedef unsigned char BYTE;
using namespace std;

class Histo {
public:
	unsigned char val; // 픽셀의 값
	unsigned int Hist_val; // freq의 값 부모면 0으로 넣을 것이다 왜냐면 0인 확률을 다 뺐으니까 
	double prov;
	double cnt;
	string bit; //비트 정보도 최종적으로 넣어주어야 할 것 같다.

	Histo() {
	}
	Histo(unsigned char val, unsigned int Hist_val, double prov) {
		this->val = val;
		this->Hist_val = Hist_val;
		this->prov = prov;
	}
};


inline void FileRead(const char* strFilename, BYTE**arr2D, int nHeight, int nWidth)
{
	FILE* fp_in;
	fopen_s(&fp_in, strFilename, "rb");

	for (int h = 0; h < nHeight; h++)
	{
		fread(arr2D[h], sizeof(BYTE), nWidth, fp_in);
	}

	fclose(fp_in);
}

inline void FileWrite(const char* strFilename, BYTE** arr2D, int nHeight, int nWidth)
{
	FILE* fp_out;
	fopen_s(&fp_out, strFilename, "wb");
	for (int h = 0; h < nHeight; h++)
	{
		fwrite(arr2D[h], sizeof(BYTE), nWidth, fp_out);
	}
	fclose(fp_out);
}

template<typename T> T** MemAlloc2D(int nHeight, int nWidth, int nInitVal);
template<typename T> void MemFree2D(T** arr2D, int nHeight);

template<typename T>
T** MemAlloc2D(int nHeight, int nWidth, int nInitVal)
{
	T** rtn = new T*[nHeight];
	for (int h = 0; h < nHeight; h++)
	{
		rtn[h] = new T[nWidth];
		memset(rtn[h], nInitVal, sizeof(T) * nWidth);
	}
	return rtn;
}

template<typename T>
void MemFree2D(T** arr2D, int nHeight)
{
	for (int h = 0; h < nHeight; h++)
	{
		delete[] arr2D[h];
	}
	delete[] arr2D;
}

class EncodeInfo {
public:
	unsigned int totalbitsize; // freq의 값 부모면 0으로 넣을 것이다 왜냐면 0인 확률을 다 뺐으니까 
	unsigned int bytesize;
	std::vector<unsigned char> pvaltbl; //여기에 pval range를 벡터
};

static int getbit(unsigned char x){
	return (x & 1);
}

