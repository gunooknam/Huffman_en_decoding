#include "Huffman_Encoding.h"

void HuffmanTree::StackTraverse(std::list<TreeNode*> & Li) {
	std::stack< TreeNode* > st;
	TreeNode* node = root;
	int a= 0;
	while (node) {

		if (node->getLeft() == NULL && node->getRight() == NULL&& node->getData().Hist_val != 0) {
			
			//cout << "value ��" << (unsigned int)(node->getData().val) << "prov �� :" << node->getData().prov << " " << node->getData().Hist_val  << "bit: "<< node->getData().bit<<endl;
		
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
	// parent ���� ������ ������ 
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
			cout << "value ��" << (unsigned int)(node->getData().val) << "prov" << node->getData().prov << " " << node->getData().Hist_val << endl << "Ƚ�� :" << ++a << endl;*/

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
		TreeNode* Node=new TreeNode(H); //�� ����� �޸� ������ �����Լ� ���� �� HT ��ü�� �Ҹ��ڿ��� ����
		L.push_back(Node);
	}

	L.sort(stLISTsort());
	list<TreeNode*>::iterator it;

	//double sum = 0;
	//cout << L.size() << endl;
	//int i = 0;
	//for (it = L.begin(); it != L.end(); it++) {
	////						// ������ �� unsigned char ����� ���� unsigned int �̴�.					
	//	cout << "val : " << (unsigned int)it->val << "Hist_val: " << it->Hist_val <<" prov : " << it->prov << " count: "<<i++<<endl;
	//	//sum += it->prov;
	//}
	//cout << sum << endl;
	// ������ �� �Ǿ��� �׸��� prov�� 0�� �κ��� ����������.
	//cout << L.back().prov << endl;

	for (int i = 0; i < L.size(); i++) {
		if (L.back()->getData().prov == 0)
			L.pop_back();
		else
			break;
	}

	//int i = 0;
	//for (it = L.begin(); it != L.end(); it++) {
	//						// ������ �� unsigned char ����� ���� unsigned int �̴�.					
	//	cout << "val : " << (unsigned int)(*it)->getData().val << "Hist_val: " << (*it)->getData().Hist_val <<" prov : " << (*it)->getData().prov << " count: "<<i++<<endl;
	//		//sum += it->prov;
	//}

	delete[] Hist;
}


// 2��° ���� �� �κ� �Լ��� ��ġ�� �� ��...
void MakeHuffmanTree(HuffmanTree &HT, std::list<TreeNode*> & List) {

	// ��ó�� start 
	TreeNode* obj1, *obj2;
	// �� ����Ʈ���� ��带 �־�� �Ѵ�!...
	// ��� => Hist ����ü�� �ƴϴ�. 
		while (List.size() != 1) {
			obj1 = List.back();
			List.pop_back();
			obj2 = List.back();
			List.pop_back();
			// ���⼭ �ٵ� zero�� prov�� �� ũ��. �׷��� prov�� ��
			// �ٵ� �̹� ���� �Ǿ����� ���ʿ� ����
			// zero�� left, one�� right 
			HT.Insert(obj2, obj1);
			// Start => �ΰ��� �̾Ƽ� Ʈ���� �����.
			List.push_back(HT.GetRoot());
			List.sort(stLISTsort());
		}

     //cout << HT.GetRoot()->getData().prov << endl; //==> ������ Ʈ�� ���� �Ϸ�

	 HT.GetBitString(List); 
	 // val�� ���� ��Ʈ�� ���´�. �׸��� ����Ʈ���ٰ� ��Ʈ ������ ��ϵ� �ִ� ��带 ä���. // Tree ��ȸ�� preorder ������� ��ȸ
	 
	 HT.StackTraverse(List); // �̰��� ���� ��ȸ���ε� 

	 List.sort(stLISTsort());

}

void MakeCompresstoTxt(BYTE**in, std::list<TreeNode*> & List, int nHeight, int nWidth, EncodeInfo &info) {



	// EncodeInfo ����ü�� pvaltbl���� �ɺ��� ������ �����Ѵ�.
	// �׸��� �ڵ������, ����Ʈ ������ ���� ����
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

	for (int h = 0; h < nHeight; h++) //256x256�� ����.
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


	// ��Ʈó�� ��Ʈ�� ����Ʈ ������ ó���� �ϵ��� �Ѵ�.
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

		//cout << (unsigned int)*write << endl; Ȯ�ο�
		fwrite(write, sizeof(unsigned char), 1, out);

	}
	delete [] write;
	fclose(out);
}