#include "Huffman_Decoding.h"

void Huffman_Decoding(int nHeight, int nWidth, EncodeInfo info){

	unsigned int bytesize=info.bytesize;
	unsigned int totalbitsize = info.totalbitsize;
	unsigned int pvalcnt = info.pvaltbl.size();
	//pval 의 range에 따른 테이블 구현
	FILE * in;
	fopen_s(&in, "Huff_Code.txt", "rb");
	unsigned char * code = new unsigned char[bytesize];
	fread(code, sizeof(unsigned char), bytesize, in);
	vector<unsigned char> totalcode;

	unsigned char result;

	for (int i = 0; i < bytesize; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//cout << (unsigned int)code[i] << endl;
			result = getbit((code[i] >> (7 - j)));
			totalcode.push_back(result);
		}
	}

	unsigned char **output_img;

	// 인풋 영상한 동일한 사이즈로 메모리 잡는다. 
	output_img = MemAlloc2D<unsigned char>(nHeight, nWidth, 0);

	FILE *out;
	fopen_s(&out, "output.raw", "wb");

	string bitstring = "";

	bool iswrite = false;

	int p = 0;

	//테이블의 픽셀 값.
	for (int h = 0; h < nHeight; h++)
	{
		for (int w = 0; w < nWidth; w++)
		{

			/// 토탈 코드 사이즈 중에 현재까지 읽은 것이 벡터 테이블에 값과 일치할 경우 그 값을 아웃풋 픽셀 값에 쓴다.
			for (; p < totalbitsize; p++){

				iswrite = false;

				if (totalcode[p] == 0)
					bitstring += "0";
				else
					bitstring += "1";


				for (int j = 0; j < pvalcnt; j++)
				{
					//vector 테이블 안에 pval range가 있다. 이것과 비교해서 값을 복원
					if (bitstring ==table[ (info.pvaltbl)[j] ]){ 
						// 테이블의 값과 비트하나하나 비교를 하는데 여기서 복잡도를 오지게 잡아먹는다. 그래서 시간이 느림...

						output_img[h][w] = (info.pvaltbl)[j];
						//cout << (unsigned int)output_img[h][w] << endl;
						iswrite = true;
						p++;
						bitstring = "";
						break;

					}
				}
				if (iswrite)
					break;
			}

		}
	}

	for (int h = 0; h < nHeight; h++){
		fwrite(output_img[h], sizeof(unsigned char), nWidth, out);
	}

	MemFree2D<unsigned char>(output_img, nHeight);

	fclose(in);
	fclose(out);

	delete[] code;

}

