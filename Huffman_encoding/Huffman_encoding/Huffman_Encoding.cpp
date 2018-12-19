#include "Huffman_Encoding.h"

void HuffmanTree::StackTraverse(std::list<TreeNode*> & Li) {
	std::stack< TreeNode* > st;
	TreeNode* node = root;
	int a= 0;
	while (node) {

		if (node->getLeft() == NULL && node->getRight() == NULL&& node->getData().Hist_val != 0) {
			
			//cout << "value 값" << (unsigned int)(node->getData().val) << "prov 값 :" << node->getData().prov << " " << node->getData().Hist_val  << "bit: "<< node->getData().bit<<endl;
		
			table[node->getData().val] = node->getData().bit;
		}

		//Li.push_back(node);
		if (node->getRight())
			st.push(node->getRight());
		if (node->getLeft())
			st.push(node->getLeft());
		if (st.empty()) break;
		node = st.top();
		st.pop();
	}
}

void HuffmanTree::Insert(TreeNode *zero, TreeNode *one) {
	Histo H;
	// parent 노드는 무조건 생성됨 
	H.prov = zero->getData().prov + one->getData().prov;
	H.Hist_val = 0;
	H.val = 0;
	TreeNode * pNode = new TreeNode(H);

	pNode->setLeft(zero);
	pNode->setRight(one);
	setRoot(pNode);
}

void HuffmanTree::GetBitString(std::list<TreeNode*> & Li) {

	std::stack< TreeNode* > st;
	TreeNode* node = root;
	//int a = 0;
	while (node) {
		/*if (node->getData().Hist_val != 0)
			cout << "value 값" << (unsigned int)(node->getData().val) << "prov" << node->getData().prov << " " << node->getData().Hist_val << endl << "횟수 :" << ++a << endl;*/

		Li.push_back(node);

		if (node->getRight()) {
			node->getRight()->getData().bit = node->getData().bit + "1";
			
			st.push(node->getRight());
		}
		if (node->getLeft()) {
			node->getLeft()->getData().bit = node->getData().bit + "0";
			
			st.push(node->getLeft());
		}
		if (st.empty()) break;
		node = st.top();
		st.pop();
	}

}



void MakeHistgramList(BYTE**arr2D, std::list<TreeNode*> &L, int nHeight, int nWidth) {

	
	int * Hist = new int[256];
	memset(Hist, 0, sizeof(int) * 256);
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			Hist[arr2D[h][w]]++;
		}
	}

	for (int i = 0; i < 256; i++) {
		Histo H;
		H.Hist_val = Hist[i];
		H.prov = (double)Hist[i] / (nHeight*nWidth);
		H.val = i;
		TreeNode* Node=new TreeNode(H); //이 노드의 메모리 해제는 메인함수 끝날 때 HT 객체의 소멸자에서 진행
		L.push_back(Node);
	}

	L.sort(stLISTsort());
	list<TreeNode*>::iterator it;

	//double sum = 0;
	//cout << L.size() << endl;
	//int i = 0;
	//for (it = L.begin(); it != L.end(); it++) {
	////						// 저장할 떈 unsigned char 출력할 떄는 unsigned int 이다.					
	//	cout << "val : " << (unsigned int)it->val << "Hist_val: " << it->Hist_val <<" prov : " << it->prov << " count: "<<i++<<endl;
	//	//sum += it->prov;
	//}
	//cout << sum << endl;
	// 정렬이 잘 되었음 그리고 prov가 0인 부분을 지워뻐리자.
	//cout << L.back().prov << endl;

	for (int i = 0; i < L.size(); i++) {
		if (L.back()->getData().prov == 0)
			L.pop_back();
		else
			break;
	}

	//int i = 0;
	//for (it = L.begin(); it != L.end(); it++) {
	//						// 저장할 떈 unsigned char 출력할 떄는 unsigned int 이다.					
	//	cout << "val : " << (unsigned int)(*it)->getData().val << "Hist_val: " << (*it)->getData().Hist_val <<" prov : " << (*it)->getData().prov << " count: "<<i++<<endl;
	//		//sum += it->prov;
	//}

	delete[] Hist;
}


// 2번째 도전 이 부분 함수만 고치면 될 듯...
void MakeHuffmanTree(HuffmanTree &HT, std::list<TreeNode*> & List) {

	// 맨처음 start 
	TreeNode* obj1, *obj2;
	// 음 리스트에는 노드를 넣어야 한다!...
	// 결론 => Hist 구조체가 아니다. 
		while (List.size() != 1) {
			obj1 = List.back();
			List.pop_back();
			obj2 = List.back();
			List.pop_back();
			// 여기서 근데 zero가 prov가 더 크다. 그래서 prov를 비교
			// 근데 이미 정렬 되었으니 할필요 없음
			// zero는 left, one은 right 
			HT.Insert(obj2, obj1);
			// Start => 두개를 뽑아서 트리를 만든다.
			List.push_back(HT.GetRoot());
			List.sort(stLISTsort());
		}

     //cout << HT.GetRoot()->getData().prov << endl; //==> 허프만 트리 구성 완료

	 HT.GetBitString(List); 
	 // val에 따른 비트를 얻어온다. 그리고 리스트에다가 비트 정보가 기록된 있는 노드를 채운다. // Tree 순회는 preorder 방식으로 순회
	 
	 HT.StackTraverse(List); // 이것은 단지 순회용인데 

	 List.sort(stLISTsort());

}

void MakeCompresstoTxt(BYTE**in, std::list<TreeNode*> & List, int nHeight, int nWidth, EncodeInfo &info) {



	// EncodeInfo 구조체의 pvaltbl에는 심볼의 종류를 저장한다.
	// 그리고 코드사이즈, 바이트 사이즈 등을 저장
	int Pvaluecount = 0;
	list<TreeNode*>::iterator it;
	unsigned char i = 0;
	for (it = List.begin(); it != List.end(); it++) {
		if ((*it)->getData().Hist_val != 0) { 
			info.pvaltbl.push_back((*it)->getData().val);
		}
		i++;
	}

	FILE *out;
	fopen_s(&out, "Huff_Code.txt", "wb");

	vector<unsigned char> totalbit;

	for (int h = 0; h < nHeight; h++) //256x256번 돈다.
	{
		for (int w = 0; w < nWidth; w++)
		{
			for (int i = 0; i < table[in[h][w]].length(); i++)
			{
				totalbit.push_back( table[in[h][w]][i] );
			}
		}
	}

	size_t totalcodesize = totalbit.size();

	unsigned char * write = new unsigned char[totalcodesize];

	memset(write, 0, totalcodesize);

	info.totalbitsize = totalcodesize;

	info.bytesize = (totalcodesize % 8)== 0 ? (totalcodesize / 8): (totalcodesize / 8) + 1;


	// 비트처리 비트를 바이트 단위로 처리를 하도록 한다.
	for (int i = 0; i < totalcodesize;) {

		unsigned char item = 0;
		if (i == 0) {
			for (int j = 0; j < 8; j++)
			{
				if (j == 0)
				{
					*write = getbit(totalbit[i]);
				}

				else
				{
					item = getbit(totalbit[i]);

					*write = (*write << 1) | item;
				}
				i++;
			}
		}
		else
		{
			for (int j = 0; j < 8; j++)
			{
				item = getbit(totalbit[i]);
				*write = *write << 1 | item;
				i++;
				//cout << i << endl;
				if (i == totalcodesize)
				{
					if (i % 8 == 0){
						break;
					}
					else
					{
						*write = *write << (info.bytesize * 8 - totalcodesize);
						break;
					}
				}
			}
		}

		//cout << (unsigned int)*write << endl; 확인용
		fwrite(write, sizeof(unsigned char), 1, out);

	}
	delete [] write;
	fclose(out);
}