#ifndef _DT_H__
#define _DT_H__


#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

class DT{
	
	public:
	
		static constexpr int INF = 0x7F7F7F7F;
	
		class TrackingUnit{
			
			public:
			//coordinates
			int l, r, u, d;
			//tracking
			int num, numps, s;
			
		};
	
		DT(int maxSize, int sites = 2);
		
		// to user
		
		int add(int num, int l, int r);
		
		TrackingUnit& operator[](int k);
		
		int get();
		
		
		// to structure
		
		void init(int id);
		
		int assign(int id);
		
		void report(int id, int &val);
		
		void collect(int id, int &val);
	
	
	private:
	
		int todo;
	
		int unused;
	
		TrackingUnit *t;
	
		int n;
		
		//forbidden
		DT(const DT&);
		DT& operator = (const DT&);
		
	
};

#include "dt.cpp"

#endif