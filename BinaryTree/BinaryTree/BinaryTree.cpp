

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>




using namespace std;


int main() {
	
	
	
	btree* tree = new btree();


	fstream bstF;
	bstF.open("bTree.txt",ios::in);
	if (bstF.is_open())
	{
		int line;
		while (bstF >> line) {
			cout << line << endl;
			tree->insert(line);
			tree->postorder_print();
			tree->preorder_print();
			tree->search(41);
			tree->postorder_print();
			tree->preorder_print();
			tree->findMax();


	}
		bstF.close();
	
	}

	//btree* tree = new btree();
	//tree->insert(10);

	/*btree* tree = new btree();

	tree->insert(10);
	tree->insert(6);
	tree->insert(14);
	tree->insert(5);
	tree->insert(8);
	tree->insert(11);
	tree->insert(18);

	tree->preorder_print();
	tree->inorder_print();
	tree->postorder_print();

	delete tree;*/
	

	return("pause">0);

}
/*
void readFromFile(char fileName[], int numb[], int& moreNum)
{

		ifstream take("bTree.txt");
	take >> moreNum;
	for (int i = 0; i < moreNum; i++) {
		take >> numb[i];
	}

}
*/