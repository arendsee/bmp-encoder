// main.cpp
// Zebulun Arendsee
// COSC 1030, Asignment #9, fall 2010
// December 3, 2010
// Updated August 2015

#include <iostream>
using std::cerr;
using std::endl;
#include <stdlib.h>
#include <iostream>
#include <fstream>
using std::ofstream;
#include "BMP.h"
#include "WriteBMP.h"
#include "Text.h"

void encode(BMP& in, Text& txt, WriteBMP& out);
void decode(BMP& code, char outfile[]);

unsigned char turnBitOn(unsigned char ch, int bit);
unsigned char turnBitOff(unsigned char ch, int bit);
bool getBit(unsigned char ch, int bit);

/*
Enter arguments on the command line in the following format:
	For encoding a file into a BMP:
	./exe fileToBeEncoded.txt input.bmp output.bmp
	For decoding a BMP to a file:
	./exe encodedInput.bmp output.txt
*/
int main(int argc, char* argv[]){
	// If there are 3 arguments, must be decoding operation
	if(argc == 3){
		cerr << "decoding "
             << "'" << argv[1] << "' BMP file to text file " 
			 << "'" << argv[2] << "'" << endl;
		BMP coded(argv[1]);
		decode(coded, argv[2]);
	}
	// If there are 4 arguments, must be encoding operation
	else if(argc == 4){
		cerr << "encoding "
             << "'" << argv[1] << "' file to BMP file "
			 << "'" << argv[2] << "' written to encoded file "
             << "'" << argv[3] << "'" << endl;
		Text txt(argv[1]);
		BMP in(argv[2]);
		WriteBMP out(argv[3], in);
		encode(in, txt, out);
	}
	// If neither, print usage
	else{
        cerr << "USAGE\n"
                "\tbmp-encoder text-filename bmp-filename text-output-filename\n"
                "\tbmp-encoder bmp-filename encoded-bmp-output-filename\n";
	}
}

// Decoding script
void decode(BMP& code, char outfile[]){
	ofstream out;
	out.open(outfile);
	unsigned char tmp(0);
	int off = code.get_startOffset();
	int size = code.get_filesize() - off;
	int i = 0;
	bool done = false;
	while(i < size && !done){
		if( getBit( code.get_char(off + i), 0 ) ){
			tmp = turnBitOn(tmp,(7 - i%8));
		}
		if( (i%8 == 0) && (i != 0)){
			if( (tmp <= 126 && tmp != 0) ){
				if(tmp == '$'){
					done = true;
				}
				else{
					out << tmp;
				}
			tmp = 0;
			}
		}
		i++;
	}
	out.close();
}

// Encoding script
void encode(BMP& in, Text& txt, WriteBMP& out){
	if(txt.get_filesize() > (8 * in.get_filesize())){
		cerr << "BMP file is too small to encode the text file\n";
		exit(1);
	}	
	unsigned char ch(0), temp(0);
	int bmp_index = in.get_startOffset();
	for(int i = 0; i < txt.get_filesize(); i++){
		ch = txt.get_char(i);
		for(int j = 7; j >= 0; j--){
			temp = in.get_char(bmp_index);
			temp = (getBit(ch,j)) ? turnBitOn(temp,0) : turnBitOff(temp,0);
			out.set_value(bmp_index, temp);
			bmp_index++;
		}
	}
}

// Turn a specific bit in a character on
unsigned char turnBitOn(unsigned char ch, int bit){
	return ch | (1 << bit);
}

// Turn a specific bit in a character off
unsigned char turnBitOff(unsigned char ch, int bit){
	return ch & ~(1 << bit);
}

// Get the value of a specific bit, false == 0, true == 1;
bool getBit(unsigned char ch, int bit){
	return (((ch ^ (ch & ~(1 << bit))) == 0) ? false : true); 
}
