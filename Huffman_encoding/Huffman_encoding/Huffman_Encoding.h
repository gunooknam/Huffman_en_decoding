#pragma once
#include "util.h"

using namespace std;
#define Eps  0.0000000000000001 // 저엉말 작은 수
extern string table[255];//mapping 테이블인데 이건 널리 쓰일 거같아서 걍 전역 변수 선언함

#pragma warning(disable : 4996)

class TreeNode {
private:
	Histo data;
	TreeNode  * leftChild;
	TreeNode  * rightChild;
public:
	
	TreeNode() {}
	~TreeNode() {}
	TreeNode(Histo data) {
		this->data = data;
		leftChild = NULL;
		rightChild = NULL;
	}

	//반드시 참조자로 리턴!!!!!
	Histo& getData() {
		return data; 
	}

	void SetData(Histo d_name) {
		data = d_name;
	}

	TreeNode * getLeft() {
		return leftChild;
	}

	TreeNode *getRight() {
		return rightChild;
	}

	void setLeft(TreeNode * node) {
		leftChild=node;
	}

	void setRight(TreeNode * node) {
		rightChild=node;
	}

};


class HuffmanTree
{
private:
	TreeNode *root;

public:

	HuffmanTree() {}

	~HuffmanTree() {
		//메모리 해제	
		if (root)
			postdelete(root);
	}

	void postdelete(TreeNode*Node) {
		if (Node) {
			postdelete(Node->getLeft());
			postdelete(Node->getRight());
			delete Node;
		}
	}

	TreeNode* GetRoot(){
		return root;
	}

	void setRoot(TreeNode * node) {
		root = node;
	}

	void GetBitString(std::list<TreeNode*> & Li);

	void StackTraverse(std::list<TreeNode*> & Li);

	void Insert(TreeNode *zero, TreeNode *one);
};

void MakeHistgramList(BYTE**arr2D, std::list<TreeNode*> &L, int nHeight, int nWidth);

void MakeCompresstoTxt(BYTE**in, std::list<TreeNode*> & List, int nHeight, int nWidth, EncodeInfo & info);

void MakeHuffmanTree(HuffmanTree &HT, std::list<TreeNode*> & List);

//어떤 기준으로 List를 sort할 것인가의 정의
struct stLISTsort
{
	bool operator() (TreeNode* Object1, TreeNode* Object2)
	{

		if (abs(Object1->getData().prov - Object2->getData().prov) < Eps) { // 같은 경우

			if (Object1->getData().Hist_val > Object2->getData().Hist_val)
				return true;
			else
				return false;

		}
		else if (Object1->getData().prov > Object2->getData().prov)
			return true;
		// 같은 경우가 있다. 그럴 때? 
		return false;
	}
};