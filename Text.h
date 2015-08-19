// Text.h
// Zebulun Arendsee
// COSC 1030, Asignment #9, fall 2010
// December 3, 2010

#ifndef TEXT_H
#define TEXT_H

#include <stdlib.h>
#include <fstream>
using std::ifstream;
#include <ios>
using std::ios;
using std::ios_base;
#include <iostream>
using std::cout;

class Text
{
public:
	Text(char filename[]);
	~Text(){ text_str.close(); }
	int get_filesize() const{ return filesize; };
	unsigned char get_char(int i);
private:
	bool text_isValid;
	bool openText(char filename[]); 
	ifstream text_str;
	int filesize;
};

Text::Text(char filename[]){
	text_isValid = false;
	if(openText(filename) == true){
		text_isValid = true;
	}
	else{
		cout << "text file '" << filename << "' could not be opened\n";
	}
}

bool Text::openText(char filename[]){
	text_str.open(filename, ios::binary);
	if(! text_str.fail()){
		// Setting file length
		text_str.seekg(0, ios::end); 
		filesize = text_str.tellg();
		text_str.seekg(0, ios::beg);
		return true;
	}
	else{
		text_str.close(); 
		return false;
	}
}

unsigned char Text::get_char(int i) {
	if(i < 0 || i >= filesize){
		cout << "ERROR: index requested does not exist\n";
		exit(1);
	}
	text_str.seekg(i);
	unsigned char tmp = text_str.get();
	return tmp;
}

#endif
