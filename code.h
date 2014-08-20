#ifndef _CODE_H
#define _CODE_H

#include <iostream>
#include <fstream>
//#include <stdlib.h>
#include <string>

using namespace std;

#define MAX_CODE_LENGTH 12
#define DEFAULT_BLOCK_SIZE 18
#define DEFAULT_BORDER 20
#define DEFAULT_FILE_NAME "output.svg"

#define BLACK 0
#define RED 1
#define GREEN 2
#define BLUE 3

class Code
{

public:
	Code();
	Code( int _block_size );
	~Code();
	int createCode( char *_code );
	int createCode( char *_code, char *_filename);
	int createCode( char *_code, char *_color, char *_filename);
	int createCode( char *_code, char *_color, char *_color, char *_filename);

private:
	int X1[10];
	int Y1[10];
	int W1[10];
	int H1[10];
	int X2[10];
	int Y2[10];
	int W2[10];
	int H2[10];

	int BT[10];
	int DT[10];

	int LX[12];
	int LY[12];

	int TC[12];

	int block_size;
	int padding;
	int tag_border;
	int code_length;
	char* border_color;
	char* tag_color;
	char* anchor_color;
	char* anchor_bg_color;
	ofstream ofs;

	void initData();
	int transCode( int location );
	bool verifyValue( char *value );
	bool isDigit( char value );
	void doBlock( int location );
	void doBlock( int digit, int location );
	void printBlock( int x, int y, int w, int h );
	void printBlock( int x, int y, int w, int h, char *color );
	bool initDoc( char* code, char *filename);
	void closeDoc();
	bool hasMultiple( int digit );
	/* char* getColor(int color); */
};


#endif /* ! _CODE_H */
