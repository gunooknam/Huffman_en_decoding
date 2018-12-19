#include <iostream>
#include "Huffman_Encoding.h"
#include "Huffman_Decoding.h"
///////////////// " 인풋 영상의 높이와 너비를 적어주세요.!"///////////////////
#define HEIGHT 256
#define WIDTH 256
//////////////////////////////////////////////////////////////////////////////
// 정수형으로 계산 해야한다. => 근데 더블형으로 해도 별차이는 없음 그냥 난 확률로 비교함
string table[255];

int main() {
	std::list<TreeNode*> List; // 이 리스트에 노드를 넣고 허프만 트리 구성
	HuffmanTree  HT; // 트리 구성을 위한 트리 객체
	EncodeInfo info; // 인코딩 정보를 저장하는 구조체
	BYTE**arr2D = MemAlloc2D<BYTE>(HEIGHT, WIDTH, 0);

	// "소스코드가 있는 위치에 레나 파일이 있어야 합니다!!"
	FileRead("lena256.raw", arr2D, HEIGHT, WIDTH);
	//////////>>>>>>>>>>>>>>>>>>>> Encoding Part <<<<<<<<<<<<<<<<<<<<<<////////
	cout << " =>>>> 인코딩 시작 !" << endl;
	
	MakeHistgramList(arr2D, List, HEIGHT, WIDTH);


	MakeHuffmanTree(HT, List); // 허프만 트리를 만든다. 이걸 리프노드 비트를 구함
				               // 인코딩 인포 구조체도 넣어준다.

	MakeCompresstoTxt(arr2D, List, HEIGHT, WIDTH, info); //압축한 텍스트 파일을 만든다.
	///////////////////////////////////////////////////////////////////////////
	
	cout << "인코딩 완료 Huff_Code.txt 파일에 인코딩되었습니다.! \n" << endl;

	//////////>>>>>>>>>>>>>>>>>>>> Decoding Part <<<<<<<<<<<<<<<<<<<<<<<<///////
	cout << " =>>>> 디코딩 시작 !" << endl;
	cout << " =>>>> 픽셀의 분포에 따라 다소 오래 걸릴 수 있습니다. !" << endl;

	Huffman_Decoding(HEIGHT, WIDTH, info);

	cout << " =>>>> 디코딩 완료 ouput.raw 파일에 디코딩 되었습니다. !\n" << endl;

	MemFree2D<BYTE>(arr2D, HEIGHT);

}