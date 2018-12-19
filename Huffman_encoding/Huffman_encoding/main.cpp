#include <iostream>
#include "Huffman_Encoding.h"
#include "Huffman_Decoding.h"
///////////////// " ��ǲ ������ ���̿� �ʺ� �����ּ���.!"///////////////////
#define HEIGHT 256
#define WIDTH 256
//////////////////////////////////////////////////////////////////////////////
// ���������� ��� �ؾ��Ѵ�. => �ٵ� ���������� �ص� �����̴� ���� �׳� �� Ȯ���� ����
string table[255];

int main() {
	std::list<TreeNode*> List; // �� ����Ʈ�� ��带 �ְ� ������ Ʈ�� ����
	HuffmanTree  HT; // Ʈ�� ������ ���� Ʈ�� ��ü
	EncodeInfo info; // ���ڵ� ������ �����ϴ� ����ü
	BYTE**arr2D = MemAlloc2D<BYTE>(HEIGHT, WIDTH, 0);

	// "�ҽ��ڵ尡 �ִ� ��ġ�� ���� ������ �־�� �մϴ�!!"
	FileRead("lena256.raw", arr2D, HEIGHT, WIDTH);
	//////////>>>>>>>>>>>>>>>>>>>> Encoding Part <<<<<<<<<<<<<<<<<<<<<<////////
	cout << " =>>>> ���ڵ� ���� !" << endl;
	
	MakeHistgramList(arr2D, List, HEIGHT, WIDTH);


	MakeHuffmanTree(HT, List); // ������ Ʈ���� �����. �̰� ������� ��Ʈ�� ����
				               // ���ڵ� ���� ����ü�� �־��ش�.

	MakeCompresstoTxt(arr2D, List, HEIGHT, WIDTH, info); //������ �ؽ�Ʈ ������ �����.
	///////////////////////////////////////////////////////////////////////////
	
	cout << "���ڵ� �Ϸ� Huff_Code.txt ���Ͽ� ���ڵ��Ǿ����ϴ�.! \n" << endl;

	//////////>>>>>>>>>>>>>>>>>>>> Decoding Part <<<<<<<<<<<<<<<<<<<<<<<<///////
	cout << " =>>>> ���ڵ� ���� !" << endl;
	cout << " =>>>> �ȼ��� ������ ���� �ټ� ���� �ɸ� �� �ֽ��ϴ�. !" << endl;

	Huffman_Decoding(HEIGHT, WIDTH, info);

	cout << " =>>>> ���ڵ� �Ϸ� ouput.raw ���Ͽ� ���ڵ� �Ǿ����ϴ�. !\n" << endl;

	MemFree2D<BYTE>(arr2D, HEIGHT);

}