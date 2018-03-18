
/*			*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
			** Programme :  AVL TREE (working)						       **
			** Programmer:  Muhammad Shafeeq				               **
			** Objective :  This program is written in C++ language and	   **
			**			    is simulation of AVL Tree,					   **
			**			    It has functionality to:					   **
			**			    Add Node									   **
			**				Delete Specific Node						   **
			**				Delete all Nodes (Destroy whole Tree)		   **
			**				etc.										   **
			*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
*/

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;
struct node		//Tree node holds data and links next node
{
	int data, h;  // " data " stores a value you enter,, " h " stores node's height (you have no need to enter height)
	node *left, *right;
};
class tree			
{
	node *root;
public:
	tree()		//constructer
	{
		root = NULL;
	}
	int max_h(node* templ, node* tempr)				//func to compare the heights of childs of a node,
	{
		int lh = -1, rh = -1;
		if (templ != NULL)
			lh = templ->h;
		if (tempr != NULL)
			rh = tempr->h;


		if (lh > rh)
			return lh;
		else
			return rh;
	}
	void r_rotate(node* &curr)				//func to rotatate the node in right side if balance factor is out with +ve sing
	{
		node* temp = curr->left;
		node* temp1 = curr;
		curr = curr->left;
		temp1->left = temp->right;
		curr->right = temp1;
		temp1 = curr->right;

		temp1->h = max_h(temp1->left, temp1->right) + 1;			//updating nodes height after rotation
		curr->h = max_h(curr->left, curr->right) + 1;


	}
	void l_rotate(node* &curr)				//func to rotate node in left side if b_factor is out with -ve sign
	{
		node* temp = curr->right;
		node* temp1 = curr;
		curr = curr->right;
		temp1->right = temp->left;
		curr->left = temp1;
		temp1 = curr->left;

		temp1->h = max_h(temp1->left, temp1->right) + 1;				//updating nodes height after left rotation
		curr->h = max_h(curr->left, curr->right) + 1;



	}
	void r_l_rotate(node* &curr)						//func to perform double rotation, if outed b_factor node has -ve sign
	{													//and his child has +ve b_factor, then right-left rotation

		r_rotate(curr->right);
		l_rotate(curr);
	}
	void l_r_rotate(node* &curr)					//vice versa to above founction
	{

		l_rotate(curr->left);
		r_rotate(curr);
	}
	
	int b_factor(node* temp)			//func to calculate b_factor of node (if -1<bf<2 then there is no need to balance, else .....)
	{
		int bf, lh = -1, rh = -1;
		if (temp->left != NULL)
			lh = temp->left->h;
		if (temp->right != NULL)
			rh = temp->right->h;

		bf = lh - rh;
		return bf;
	}
	void balancing(node* &curr)				//func to balace a node if b_factor of currentnode is out
	{

		if (b_factor(curr) > 1)				//b_factor of node is out with +ve sign (such as bf>1)
		{
			if (b_factor(curr->left) > 0)	//b_factor of under observation node's child is also +ve, (single rotation)
			{
				r_rotate(curr);
				cout << "right rotation\n";
			}
			else					//b_factor of under observation node's child is -ve, (double rotation)
			{
				cout << "left-right-rotation\n";
				l_r_rotate(curr);
			}
		}

		else if (b_factor(curr) < -1)			//b_factor of node is out with -ve sign (such as bf>1)
		{
			if (b_factor(curr->right) < 0)			//b_factor of under observation node's child is also -ve, (single rotation)
			{
				l_rotate(curr);
				cout << "left rotation\n";
			}
			else							//b_factor of under observation node's child is +ve, (double rotation)				
			
			{
				r_l_rotate(curr);
				cout << "Right-left rotation\n";
			}
		}
	}

	void Insert(int x, node* &temp)				//func to store data in node, and links next node
	{
		if (temp == NULL)
		{
			temp = new node;
			temp->data = x;
			temp->h = 0;
			temp->left = NULL;
			temp->right = NULL;

		}
		else
		{
			if (x < temp->data)
			{
				Insert(x, temp->left);
				temp->h = max_h(temp->left, temp->right) + 1;		//updating height of node after inserting a new node as its left child
				balancing(temp);		//calling func to balance the node if b_factor is outed
			}

			else if (x > temp->data)
			{
				Insert(x, temp->right);
				temp->h = max_h(temp->left, temp->right) + 1;			//updating height of node after inserting a new node as its right child
				balancing(temp);
			}
			else
			{
				cout << "Same value already have been stored, Do you want to store it again? Y or N: ";
				char ch;
				cin >> ch;
				if (ch == 'y' || ch == 'Y')
				{
					Insert(x, temp->right);
					temp->h = max_h(temp->left, temp->right) + 1;
					balancing(temp);
				}
				else
					return;
			}
			temp->h = max_h(temp->left, temp->right) + 1;			//updating height of node after insertion child going, back throughout path

		}
	}

	void input(int d)
	{
		Insert(d, root);
	}
	void preorder(node *temp)		//func to traverse tree in pre-order(first show root, then left child, then right child)
	{
		if (temp != NULL)
		{
			cout << temp->data << "\t";
			preorder(temp->left);
			preorder(temp->right);
		}
	}

	void inorder(node *temp)			//func to traverse tree in in_order (first show left child, then root, then right child)
	{
		if (temp != NULL)
		{

			inorder(temp->left);
			cout << temp->data << "\t";
			inorder(temp->right);
		}
	}

	void postorder(node *temp)			//func to traverse tree in pre-order(first left child, then right child, then root)
	{
		if (temp != NULL)
		{

			postorder(temp->left);
			postorder(temp->right);
			cout << temp->data << "\t";
		}
	}
	void show()
	{
		int ch;
		do
		{
			cout << "\t\t************Menu****************\n"
				<< "\t\t*          1. Pre-Order        *\n"
				<< "\t\t*          2. In-Order         *\n"
				<< "\t\t*          3. Post-Order       *\n"
				<< "\t\t*          4. Go back to Main  *\n"
				<< "\t\t********************************\n\n";
			cout << "\t\tyour choice: ";
			cin >> ch;
			switch (ch)
			{
			case 1:
				preorder(root);
				cout << endl;
				break;
			case 2:
				inorder(root);
				cout << endl;
				break;
			case 3:
				postorder(root);
				cout << endl;
				break;
			}
		} while (ch != 4);

	}
	void Delete_all(node * &temp)			//destroying whole tree
	{
		if (temp != NULL)
		{

			Delete_all(temp->left);
			Delete_all(temp->right);
			cout << "Deleting" << temp->data << "\t";
			delete temp;
		}
	}
	void del(node* &curr)			//deleting specific node
	{
		node* temp = NULL;
		if (curr == NULL)
			cout << "Data not found\t";
		else
		{
			if (curr->left == NULL)
			{
				temp = curr;
				curr = curr->right;

			}
			else if (curr->right == NULL)
			{
				temp = curr;
				curr = curr->left;
			}
			else
			{
				temp = curr->right;
				while (temp->left != NULL)
					temp = temp->left;
				temp->left = curr->left;
				temp = curr;
				curr = curr->right;

			}
		}
		delete temp;
	}

	void searching(int num, node* &temp)		//searching a node to delete 
	{
		if (temp == NULL)
		{
			cout << "Not Found\n";
			system("pause");
		}
		else if (num < temp->data)
			searching(num, temp->left);

		else if (num > temp->data)
			searching(num, temp->right);

		else
			del(temp);

	}
	void clear()
	{
		int d, ch;
		do
		{
			cout << "\t\t*************Menu***************\n"
				<< "\t\t*    1. Delete Specific Value  *\n"
				<< "\t\t*    2. Delete all Data        *\n"
				<< "\t\t*    3 Go back to Main         *\n"
				<< "\t\t********************************\n\n";
			cout << "\t\tyour choice: ";
			cin >> ch;
			switch (ch)
			{
			case 1:
				cout << "Enter value to delete:";
				cin >> d;

				searching(d, root);
				break;
			case 2:
				Delete_all(root);
				root = NULL;
				break;
			case 3:
				break;
			}
		} while (ch != 3);


	}
};

int main()							//main func
{
	int in, ch;
	tree obj;
	system("color 0B");

	cout << "\n                                                                   _______\n"
		<< "==================================================================|___    | \n"
		<< " _____________________________________________________________________\"\\  |\n"
		<< "|_   :                                                                | |_|\n"
		<< "===) :                          AVL TREE                              |  |\n"
		<< "|_  .:................................................................|  |\n"
		<< "===) :                             BY                                 |  |\n"
		<< "|_   :                                                                |  |\n"
		<< "===) :                      MUHAMMAD SHAFEEQ                          |  |\n"
		<< "|_   :                                                                |  |\n"
		<< "===) :                     2355-FBAS/BSSE/F13                         |  |\n"
		<< "|_   :                                                                |  |\n"
		<< "===) :                DATA STRUCTURES & ALGORITHM                     |  |\n"
		<< "|_   :                                                                |  |\n"
		<< "===) :              It is a simulation of AVL Tree                    |  |\n"
		<< "|_   :              written in C++ Language. It has                   |  |\n"
		<< "===) :              basic Functionality of AVL Tree.                  |  |\n"
		<< "|_   :                                                                |  |\n"
		<< "===) :                                                                |  |\n"
		<< "|___ :________________________________________________________________| |\"| \n"
		<< "                                                                   ____/  |\n"
		<< "==================================================================|_______|\n";
	system("pause");
	system("cls");
	system("color 0A");
	do
	{
		cout << "\n\n\n";
		cout << "    +---------------------------------------------------------------------+\n"
			<< "    | = : = : = : = : = : = : = : = : { MENU } = : = : = : = : = : = : = :|\n"
			<< "    | {>/-------------------------------------------------------------\\<} |\n"
			<< "    |: |                                                               |: |\n"
			<< "    | :|                    1. )   Enter Data                          | :|\n"
			<< "    |: |                                                               |: |\n"
			<< "    | :|                    2. )   Search Data                         | :|\n"
			<< "    |: |                                                               |: |\n"
			<< "    | :|                    3. )   Traverse Tree                       | :|\n"
			<< "    |: |                                                               |: |\n"
			<< "    | :|                    4. )   Delete Data                         | :|\n"
			<< "    |: |                                                               |: |\n"
			<< "    | :|                    5. )   Exit                                | :|\n"
			<< "    |: |                                                               |: |\n"
			<< "    | {>\\-------------------------------------------------------------/<} |\n"
			<< "    | = : = : = : = : = : = : = : = : = : = : = : = : = : = : = : = : = : |\n"
			<< "    +---------------------------------------------------------------------+\n";


		cout << "\tYour choice: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			do
			{
				cout << "Enter Value; To terminate,Enter 999: ";
				cin >> in;
				if (in != 999)
					obj.input(in);
			} while (in != 999);

			break;
		case 2:
			cout << "Enter data to search:";
			cin >> in;
			break;
		
		case 3:
			obj.show();
			break;
		case 4:
			obj.clear();
			break;
		case 5:
			system("cls");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tGOOD BYE\n";
			Sleep(2000);
			exit(1);
		}
	} while (true);

	system("pause");
	return 0;

}