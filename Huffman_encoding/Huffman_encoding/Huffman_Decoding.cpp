#include "Huffman_Decoding.h"

void Huffman_Decoding(int nHeight, int nWidth, EncodeInfo info){

	unsigned int bytesize=info.bytesize;
	unsigned int totalbitsize = info.totalbitsize;
	unsigned int pvalcnt = info.pvaltbl.size();
	//pval �� range�� ���� ���̺� ����
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

	// ��ǲ ������ ������ ������� �޸� ��´�. 
	output_img = MemAlloc2D<unsigned char>(nHeight, nWidth, 0);

	FILE *out;
	fopen_s(&out, "output.raw", "wb");

	string bitstring = "";

	bool iswrite = false;

	int p = 0;

	//���̺��� �ȼ� ��.
	for (int h = 0; h < nHeight; h++)
	{
		for (int w = 0; w < nWidth; w++)
		{

			/// ��Ż �ڵ� ������ �߿� ������� ���� ���� ���� ���̺� ���� ��ġ�� ��� �� ���� �ƿ�ǲ �ȼ� ���� ����.
			for (; p < totalbitsize; p++){

				iswrite = false;

				if (totalcode[p] == 0)
					bitstring += "0";
				else
					bitstring += "1";


				for (int j = 0; j < pvalcnt; j++)
				{
					//vector ���̺� �ȿ� pval range�� �ִ�. �̰Ͱ� ���ؼ� ���� ����
					if (bitstring ==table[ (info.pvaltbl)[j] ]){ 
						// ���̺��� ���� ��Ʈ�ϳ��ϳ� �񱳸� �ϴµ� ���⼭ ���⵵�� ������ ��ƸԴ´�. �׷��� �ð��� ����...

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

