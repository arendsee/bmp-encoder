// WriteBMP.h
// Zebulun Arendsee
// COSC 1030, Asignment #9, fall 2010
// December 3, 2010

#ifndef WRITEBMP_H
#define WRITEBMP_H

#include "BMP.h"
#include <fstream>
using std::ofstream;

class WriteBMP
{
public:
	WriteBMP( char outfilename[], BMP& in );
	~WriteBMP(){ out.write(buffer, size);
				 out.close(); }
	void set_value(int index, int value);
private:
	ofstream out;
	void copy_BMP(BMP& in);
	int size;
	char * buffer;
};

WriteBMP::WriteBMP( char outfilename[], BMP& in ){
	out.open(outfilename);
	copy_BMP(in);
}

void WriteBMP::copy_BMP(BMP& in){
	size = in.get_filesize();
	buffer = new char [size];	
	for(int i = 0; i < size; i++){
		buffer[i] = in.get_char(i);
	}
}

void WriteBMP::set_value(int i, int val){
	if(i >= 0 && i < size){
		buffer[i] = val;
	}
}

#endif
