#ifndef _RTS1DBF_H__
#define _RTS1DBF_H__

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

class RTS1DBF{
	
	public:
	
		RTS1DBF(int maxSize);
		
		~RTS1DBF();
		
		void addInterval(int l, int r, int num);
		
		void addPoint(int x, int weight);
	
	//private:
	
		class Node{
			public:
			int l, r, num;
		};
		
		int id = 0;
		Node *t;
		
		//forbidden
		RTS1DBF(const RTS1DBF&);
		RTS1DBF& operator = (const RTS1DBF&);
};

#include "rts1dbf.cpp"

#endif