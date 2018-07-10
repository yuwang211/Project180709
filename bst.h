#ifndef _BST_H__
#define _BST_H__


#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

class Bst{
	
	public:
	
		static constexpr int INF = 0x7F7F7F7F;
					
		class BstNode{
			public:
			//structure
			int key, l, r;
			//maintain
			int size;
			//domain
			int id, val, delta, min;
		};
	
		Bst(int maxSize);
		~Bst();
		
		void add(int p, int delta);
		void down(int p);
		void up(int p);
		
		int toList(int p, int tail = 0);
		int toTree(int p);
		
		BstNode& operator[](int k);
	
		int insert(int p, int key, int id, bool flag = true);
		int insert(int p, int n, bool flag = true);
		int remove(int p, int key, int id, bool flag = true);
		int merge(int p, int q);
		
		
		void change(int p, int l, int r, int delta);
		
		//linked with distributed tracking
		void linkDT(DT *d);
		
		void scanNegative(int p);
		
		void collect(int p, int key, int id);
		void assign(int p, int key, int id);
		
		void print(int p);
	
	private:
	
	
		int unused;
		BstNode *t;
		
		DT *dt;
		
		int buildTree(int &p, int size);
		
		//tools
		int min(int x, int y){return x < y ? x : y;}

	
		//forbidden
		Bst(const Bst&);
		Bst& operator = (const Bst&);
		
	
};

#include "bst.cpp"

#endif