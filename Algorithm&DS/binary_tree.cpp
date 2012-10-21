﻿/*
author:justinzhang
email:uestczhangchao@gmail.com
time:2012-8-20 15:52:27
des.:using non recursive method to traverse binary tree

rev: 2012-10-21 11:27:26 
    	Added:
	 1. layered_order;
	 2. predored_nonrecursive
	 3. inodre_nonrecursive
	 4. postorder_nonrecursive
*/
#include <iostream>
#include <deque>
#include <stack>
using namespace std;

template<typename T> class btree
{
public:
	T data;
	btree *lchild, *rchild;
};

/*	create binary tree, with one parameter.
	the binary tree is inputed through pre order,
	1
   2 3, is input as 1 2 -1 -1 3 -1 -1,(-1 represent nil node);
*/
btree<double> * create_btr(btree<double> **root)
{
	double data ;
	cin>>data;
	/* -1.0 represent the nil node */
	if(data == -1.0) 
	{
		*root=NULL;
	}
	else
	{
		*root = new btree<double>();
		(*root)->data = data;
		(*root)->lchild = create_btr(&(*root)->lchild);
		(*root)->rchild = create_btr(&(*root)->rchild);		
	}
	return *root;
}

/*create binary tree without parameter!*/
btree<double>* create_btr()
{
	double data;
	cin >> data;
	if(data == -1)
		return NULL; //return nill node
	else
	{
		btree<double> *T = new btree<double>;
		T->data = data;
		T->lchild = create_btr();
		T->rchild = create_btr();
		return T;
	}
}

void preorder(btree<double> *r)
{
	if(r==NULL)
		return;
	cout << r->data << " ";
	preorder(r->lchild);
	preorder(r->rchild);
}

void inorder(btree<double> *r)
{
	if(NULL==r)
		return;
	inorder(r->lchild);
	cout << r->data<< " ";
	inorder(r->rchild);
}
void postorder(btree<double> *r)
{
	if(NULL==r)
		return ;
	postorder(r->lchild);
	postorder(r->rchild);
	cout << r->data<<" ";
}

template<class T> void layered_order(btree<T> *r)
{
	if(NULL==r)
	{
		return;
	}
	btree<T>* node = NULL;
	deque<btree<T>* > Q;
	Q.push_back(r);
	while(!Q.empty())
	{
		node = Q.front();
		cout << node->data << " ";
		if(node->lchild != NULL)
			Q.push_back(node->lchild);
		if(node->rchild != NULL)
			Q.push_back(node->rchild);
		Q.pop_front();
	}
	cout << endl;
}

template<class T> void preorder_nonrecursive(btree<T> *r)
{
	if(NULL == r)
		return ;
	btree<T>* node = r;
	deque<btree<T> *> stack;

	while(!stack.empty() || node!=NULL)
	{
		while(node)
		{
			cout << node->data << " ";
			stack.push_back(node);
			node = node->lchild;
		}
		node = stack.back();
		stack.pop_back();
		node = node->rchild;
	}
	cout << endl;
}



template<class T> void inodre_nonrecursive(btree<T> * root)
{
	if(NULL == root)
		return;
	btree<T> * node = NULL;
	deque<btree<T> *> stack;
	node = root;
	while(!stack.empty() || node!=NULL)
	{
		while(node)
		{
			stack.push_back(node);
			node = node->lchild;
		}
		node = stack.back();
		stack.pop_back();
		cout << node->data <<" ";
		node = node->rchild;
	}
	cout << endl;

}

template<class T> void postorder_nonrecursive(btree<T> *r)
{
	if(r==NULL)
		return ;
	deque<btree<T> *> stack;
	deque<int> stack_flag;
	int flag = 0;
	btree<T> * node = r;
	stack.push_back(r);
	stack_flag.push_back(1);

	while(!stack.empty())
	{
		while(node && node->lchild)
		{
			stack.push_back(node->lchild);
			stack_flag.push_back(1);
			node = node->lchild;
		}

		node = stack.back();
		flag = stack_flag.back();
		stack.pop_back();
		stack_flag.pop_back();

		if(flag == 1)
		{
			stack.push_back(node);
			stack_flag.push_back(2);
			node = node->rchild;
			if(node)
			{
				stack.push_back(node);
				stack_flag.push_back(1);
			}
		}
		else
		{
			cout << node->data <<" ";
			node = NULL;
		}
	}
	cout << endl;
}

/*----To reconstruct a binary tree from the inorder and preorder;2012-10-21 16:48:54-----*/
template<class T> void rebuild_pre_in(T preorder[], size_t i, size_t j, T inorder[], size_t k, size_t h, btree<T> **root)
{
	/*
	if the size of preorder and inorder is not equal,or the size of order is zero,
	there must be errors, so returns
	*/
	if((j-i) != (h-k) || (j-i+1)==0)
		return;
	size_t m = k;
	while(preorder[i] != inorder[m])
	{
		m++;
	}
	*root = new btree<T>();
	(*root)->data = preorder[i];

	if(m==k)
		(*root)->lchild = NULL;
	else 
		rebuild_pre_in(preorder,i+1,i+m-k,inorder,k,m-1,&(*root)->lchild);
	if(m == h)
		(*root)->rchild = NULL;
	else
		rebuild_pre_in(preorder,i+m-k+1,j,inorder,m+1,h,&(*root)->rchild);
}

template<class T> void rebulid_post_in(T postorder[], size_t i, size_t j, T inorder[], size_t k, size_t h, btree<T> **root)
{

}

int main()
{
	/*
	test binary tree:1 2 4 8 -1 -1 9 -1 -1 5 -1 -1 3 6 -1 -1 7 -1 -1
					you can see the binary tree from layered_order easily~~
	*/
	btree<double> *root = NULL;
	create_btr(&root);
	//btree<double> *T = create_btr();
	cout << "preoredr:" << endl;
	preorder(root); cout << endl;
	cout << "inorder:" << endl;
	inorder(root);	cout << endl;
	cout << "postorder:"<< endl;
	postorder(root); cout << endl;
	//inorder(T);

	cout << "layered order:" << endl;
	layered_order<double>(root);


	cout << "preorder_nonrecursive:" << endl;
	preorder_nonrecursive<double>(root);

	cout << "inorder_nonrecursive:" << endl;
	inodre_nonrecursive<double>(root);

	cout << "postorder_nonrecursive:" << endl;
	postorder_nonrecursive<double>(root);

	cout << "reconstruct binary tree from preorder and inorder!" << endl;
	char pre[] = "abcdefghi";
	char inorder[] = "bcaedghfi";
	char post[] = "cbhgifeda";
	btree<char> * recovery_tree = NULL;
	rebuild_pre_in(pre,0,8,inorder,0,8,&recovery_tree);
	postorder_nonrecursive<char>(recovery_tree);

	return 0;
}