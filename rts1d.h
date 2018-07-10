#ifndef _RTS1D_H__
#define _RTS1D_H__

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include "dt.h"
#include "itv.h"

class RTS1D{
	
	public:
	
		RTS1D(int maxSize);
		
		~RTS1D();
		
		void addInterval(int l, int r, int num);
		
		void addPoint(int x, int weight);
	
	//private:
		
		DT *dt;
		Itv *itv;
		
		int root;
		
		
		//forbidden
		RTS1D(const RTS1D&);
		RTS1D& operator = (const RTS1D&);
};

#include "rts1d.cpp"

#endif