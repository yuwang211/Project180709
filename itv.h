#ifndef _ITV_H__
#define _ITV_H__


#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include "bst.h"

class Itv{
	
	public:
	
		static constexpr int INF = 0x7F7F7F7F;
					
		class ItvNode{
			public:
			//structure
			int key, l, r;
			//maintain
			int cnt, size;
			//secondary structure
			int lt, rt;
		};
	
		Itv(int maxSize);
		~Itv();
		
		void up(int p);

		ItvNode& operator[](int k);
	
		int insert(int p, int l, int r, int id);
		int remove(int p, int l, int r, int id);
		
		void change(int p, int x, int delta);
		
		
		//linked with distributed tracking
		void linkDT(DT *d);
		
		void collect(int p, int l, int r, int id);
		void assign(int p, int l, int r, int id);
		
		void print(int p, int dep = 0);
	
	private:
	
		int unused;
		
		ItvNode *t;
		
		Bst *bst;
		
		DT *dt;
		
		int insertKey(int p, int key);
		void insertItv(int p, int l, int r, int id);
		
		int removeKey(int p, int key);
		void removeItv(int p, int l, int r, int id);
		
		//tools
		int min(int x, int y){return x < y ? x : y;}
	
		//forbidden
		Itv(const Itv&);
		Itv& operator = (const Itv&);
		
	
};

#include "itv.cpp"


#endif