// BMP.h
// Zebulun Arendsee
// COSC 1030, Asignment #9, fall 2010
// December 3, 2010

#ifndef BMP_H
#define BMP_H

#include <stdlib.h>
#include <math.h>
#include <fstream>
using std::ifstream;
#include <ios>
using std::ios;
using std::ios_base;
#include <iostream>
using std::cout;
using std::endl;

class BMP
{
public:
	BMP(char filename[]);
	~BMP(){ bmp_str.close(); };
	unsigned char get_char(int i);
	bool get_BMP_isValid() const{ return BMP_isValid; }
	int get_filesize() const{ return filesize; }
	int get_startOffset() const{ return startOffset; }
private:
	int filesize;
	int startOffset;
	bool BMP_isValid;
	bool isBMP(ifstream& bmp);
	bool openBMP(ifstream& bmp, char filename[]);
	ifstream bmp_str;
};

BMP::BMP(char filename[]){
	BMP_isValid = false;
	if(openBMP(bmp_str, filename) == true){
		if(isBMP(bmp_str) == true){
			BMP_isValid = true;
			filesize = 0;
			startOffset = 0;
			// Get file size (bytes 2-5 of file)
			bmp_str.seekg(2);
			int multiplier = 1;
			for(int i = 0; i < 4; i++){
				filesize += bmp_str.get() * multiplier;
				multiplier *= 256;
			}
			// Get bitmap start offset
			bmp_str.seekg(10);
			multiplier = 1;
			for(int i = 0; i < 4; i++){
				startOffset += bmp_str.get() * multiplier;
				multiplier *= 256;
			}
		}
		else{
			cout << "ERROR: file is not a BMP file" << endl;
			BMP_isValid = false;
		}
	}
	else{
		cout << "ERROR: file '" << filename << "' could not be opened " << endl;
		BMP_isValid = false;
	}
}

bool BMP::openBMP(ifstream& str, char filename[]){
	str.open(filename, ios::binary | ios::in);
	return (str.fail() ? false : true);
}

bool BMP::isBMP(ifstream& str){
	str.seekg(0);
	char tmp1 = str.get();
	char tmp2 = str.get();
	return (tmp1 == 'B' && tmp2 == 'M') ? true : false;
}

unsigned char BMP::get_char(int i){
if(i < 0 || i >= filesize){
		cout << "ERROR: index requested does not exist" << endl;
		exit(1);
    }   
    bmp_str.seekg(i);
    unsigned char tmp = bmp_str.get();
    return tmp;
}

#endif
