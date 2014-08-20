#include "code.h"

Code::Code()
{
	Code( DEFAULT_BLOCK_SIZE );
}

Code::Code( int _block_size )
{
	border_color = new char(128);
	tag_color = new char(128);
	anchor_color = new char(128);
	anchor_bg_color = new char(128);

	border_color = "#ff0000";
	tag_color = "#000000";
	anchor_color = "#000000";
	anchor_bg_color = "#ffffff";

	block_size = _block_size;
}

Code::~Code()
{
	delete border_color;
	delete tag_color;
	delete anchor_color;
	delete anchor_bg_color;
}

int
Code::createCode( char *code  )
{
	border_color = "#000000";
	tag_color = "#000000";
	return createCode( code, DEFAULT_FILE_NAME );
}

int
Code::createCode( char *code, char *_color, char *filename )
{
	border_color = _color;
	//tag_color = "#000000";
	return createCode(code, filename);
}

int
Code::createCode( char *code, char *_bordercolor, char*_tagcolor, char *filename )
{
	border_color = _bordercolor;
	tag_color = _tagcolor;
	return createCode(code, filename);
}

int
Code::createCode( char *code, char *filename )
{
	initData();
	if( ! verifyValue(code) )  { return 1; }
	if( ! initDoc(code, filename) ) { return 1; }

	int len = ( strlen(code) < MAX_CODE_LENGTH ) ? strlen(code) : MAX_CODE_LENGTH;

	char tmp[1]; 
	for(int i=0; i< MAX_CODE_LENGTH; i++){
		// cout << "i = " << i << " char = " << code[i] << endl ;
		if( i < len ){
			tmp[0] = code[i];
			doBlock(atoi(tmp), i);
		}else{
			doBlock(i);
		}
	}
	closeDoc();
	return 0;
}

void
Code::initData()
{

	block_size = DEFAULT_BLOCK_SIZE;
	tag_border = DEFAULT_BORDER;
	padding = block_size / 2;

	X1[0] = 0; X1[1] = 0; X1[2] = 0; X1[3] = 0; X1[4] = 0; X1[5] = 1; X1[6] = 0; X1[7] = 1; X1[8] = 0; X1[9] = 0;
	Y1[0] = 1; Y1[1] = 0; Y1[2] = 0; Y1[3] = 1; Y1[4] = 0, Y1[5] = 0; Y1[6] = 0; Y1[7] = 0; Y1[8] = 0; Y1[9] = 0;
	W1[0] = 2; W1[1] = 2; W1[2] = 2; W1[3] = 2; W1[4] = 1; W1[5] = 1; W1[6] = 1; W1[7] = 1; W1[8] = 2; W1[9] = 1;
	H1[0] = 1; H1[1] = 1; H1[2] = 1; H1[3] = 1; H1[4] = 2; H1[5] = 2; H1[6] = 1; H1[7] = 1; H1[8] = 1; H1[9] = 1;

	X2[0] = 1; X2[1] = 0; X2[2] = 0; X2[3] = 0; X2[4] = 0; X2[5] = 0; X2[6] = 1; X2[7] = 0; X2[8] = 1; X2[9] = 0;
	Y2[0] = 0; Y2[1] = 1; Y2[2] = 0; Y2[3] = 0; Y2[4] = 0; Y2[5] = 0; Y2[6] = 1; Y2[7] = 1; Y2[8] = 1; Y2[9] = 1;
	W2[0] = 1; W2[1] = 1; W2[2] = 0; W2[3] = 0; W2[4] = 0; W2[5] = 0, W2[6] = 1; W2[7] = 1; W2[8] = 1; W2[9] = 2;
	H2[0] = 1; H2[1] = 1; H2[2] = 0; H2[3] = 0; H2[4] = 0; H2[5] = 0; H2[6] = 1; H2[7] = 1; H2[8] = 1; H2[9] = 1;

	BT[0] = 0; BT[1] = 0; BT[2] = 1; BT[3] = 1; BT[4] = 2; BT[5] = 2; BT[6] = 3; BT[7] = 3; BT[8] = 0; BT[9] = 0;
	DT[0] = 0; DT[1] = 0; DT[2] = 1; DT[3] = 2; DT[4] = 1; DT[5] = 2; DT[6] = 3; DT[7] = 3; DT[8] = 0; DT[9] = 0;

	LX[0]  = 2; LY[0]  = 0;
	LX[1]  = 3; LY[1]  = 0;
	LX[2]  = 2; LY[2]  = 1;
	LX[3]  = 3; LY[3]  = 1;

	LX[4]  = 0; LY[4]  = 2;
	LX[5]  = 1; LY[5]  = 2;
	LX[6]  = 0; LY[6]  = 3;
	LX[7]  = 1; LY[7]  = 3;

	LX[8]  = 2; LY[8]  = 2;
	LX[9]  = 3; LY[9]  = 2;
	LX[10] = 2; LY[10] = 3;
	LX[11] = 3; LY[11] = 3;

	TC[0] = 0;
	TC[1] = 4;
	TC[2] = 8;
	TC[3] = 1;
	TC[4] = 5;
	TC[5] = 9;
	TC[6] = 2;
	TC[7] = 6;
	TC[8] = 10;
	TC[9] = 3;
	TC[10] = 7;
	TC[11] = 11;

}

bool
Code::verifyValue( char *value )
{
	for(int i=0; i < strlen(value); i++){
		if( ! isdigit(value[i]) ) return false;
	}
	return true;
}

bool
Code::isDigit( char value )
{
	return true;
}

int
Code::transCode( int location )
{
	return TC[location];
}

/* special for blank block */
void
Code::doBlock( int _location )
{
	int location = transCode(_location);

	int w = 2 * block_size;
	int h = 2 * block_size;
	int x = ( LX[location] * (2*block_size) );
	int y = ( LY[location] * (2*block_size) );
	x += padding * LX[location];
	y += padding * LY[location];
	printBlock( x, y, w, h );
}

void
Code::doBlock( int digit, int _location )
{
	int location = transCode(_location);

	// cout << block_size << endl ;
	// cout << endl <<  "printing block for " << digit << " at " << location << endl;

	int w = W1[digit] * block_size;
	int h = H1[digit] * block_size;
	int x = ( LX[location] * (2*block_size) ) + ( X1[digit] * block_size ) ;
	int y = ( LY[location] * (2*block_size) ) + ( Y1[digit] * block_size ) ;
	int offset = block_size / 2; //marker for 2,3 and 4.5
	x += padding * LX[location];
	y += padding * LY[location];
        if( BT[digit] == 3 ){ //6,7 (diagonal)
		w += offset/4;
		h += offset/4;
	}
	printBlock( x, y, w, h );

	if( hasMultiple(digit) ) {
		w = W2[digit] * block_size;
		h = H2[digit] * block_size;
		x = ( LX[location] * (2*block_size) ) + ( X2[digit] * block_size ) ;
		y = ( LY[location] * (2*block_size) ) + ( Y2[digit] * block_size ) ;
		x += padding * LX[location];
		y += padding * LY[location];
        	if( BT[digit] == 3 ){ //6,7 (diagonal)
			w += offset/4;
			h += offset/4;
		}
		printBlock( x, y, w, h );
	}
	//add the extra marker middle tag 
	if( BT[digit] == 1 ){    //2,3 (vertical) 
	  if( DT[digit] == 1 ){
		x += block_size - (offset/2);
		w = offset;
		h = block_size * 2;
		printBlock( x, y, w, h );
	  } else if( DT[digit] == 2 ){ 	     
		x += block_size - (offset/2);
		y -= block_size;
		w = offset;
		h = block_size * 2;
		printBlock( x, y, w, h );
	  }
	}else if( BT[digit] == 2 ){ //4,5 (horizonatl)
	  if( DT[digit] == 1 ){
		y +=  block_size - (offset/2);
		h = offset;
		w = block_size*2;
		printBlock( x, y, w, h );
	  } else if( DT[digit] == 2 ){ 	     
		y += block_size - (offset/2);
		x -= block_size;
		h = offset;
		w = block_size*2;
		printBlock( x, y, w, h );
	  }
	}
}

void
Code::printBlock( int x, int y, int w, int h )
{
	printBlock( x, y, w, h , tag_color );
}

void
Code::printBlock( int x, int y, int w, int h , char *color )
{
	ofs << endl << "\t<rect";
	ofs << endl << "\tstyle=\"" << "fill:" << color << ";fill-opacity:1.0" << "\"" ;
	ofs << endl << "\twidth=\"" << w << "\"" ;
	ofs << endl << "\theight=\"" << h << "\"" ;
	ofs << endl << "\tx=\"" << x  << "\"" ;
	ofs << endl << "\ty=\"" << y  << "\"" ;
	ofs << " />" << endl;

}

bool
Code::hasMultiple( int digit )
{
	if( X2[digit] > 0 ) return true;
	if( Y2[digit] > 0 ) return true;
	if( W2[digit] > 0 ) return true;
	if( H2[digit] > 0 ) return true;
	return false;
}

bool
Code::initDoc(char *code, char *filename)
{
	int border = block_size / 2;
	int textoffset = 30;

	int edge =  8 * block_size + border + (3*padding) ;
	int bounds = (8 * block_size) + (2*border) + (3*padding);
	int tag_width  = bounds + (2*tag_border) ;
	int tag_height = bounds + textoffset + (2*tag_border) ;
	

	ofs.open ( filename , ofstream::out );
	if( ! ofs.good() ){
                ofs.close();
		// cout << "Failed to Open " << filename << " at initDoc !" << endl ;
                return false;
        }
	ofs << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl ;
	ofs << "<!-- www.hackorma.com kishan@hackorama.com -->" << endl ;
	ofs << "<svg width=\"" << tag_width <<"\" height=\"" << tag_height  << "\">" << endl ;
	ofs << endl ;
	ofs << "<g transform=\"translate(" << tag_border << "," << tag_border << ")\">" << endl ;
	ofs << endl ;
	printBlock( 0, 0, (block_size * 4) + padding, (block_size * 4) + padding, anchor_color );
	//printBlock( block_size, block_size, block_size * 2, block_size * 2, "#ff0000" );
	int anchor_pad = padding + (padding/2);
	printBlock( anchor_pad, anchor_pad, (block_size * 4) - block_size , (block_size * 4) - block_size , anchor_bg_color );
	printBlock( edge , 0, border, bounds, border_color );
	printBlock( 0, edge , bounds , border, border_color );
	ofs << endl ;

	/*
	ofs << "<text  transform=\"scale(2,1)\" x=\"0\" y=\"" << edge + textoffset << "\">";
	ofs << code << "VERSION NUVO B13" ;
	ofs << code ;
	ofs << "</text>" ;
	*/

	ofs << "<text  transform=\"scale(1.8,1.5)\" x=\"0\" y=\"140\">" ; 
	ofs << code[0] << code[3] << code[6] << code[9] << "</text>" << endl;

	ofs << "<text  transform=\"scale(1.8,1.5)\" x=\"38\" y=\"140\">" ; 
	ofs << code[1] << code[4] << code[7] << code[10] << "</text>" << endl;

	ofs << "<text  transform=\"scale(1.8,1.5)\" x=\"75\" y=\"140\">" ; 
	ofs << code[2] << code[5] << code[8] << code[11] << "</text>" << endl;
	ofs << "<text  transform=\"scale(0.67,1)\" x=\"0\" y=\"224\">" ;
	ofs << "SCAN WITH PHONE CAM &amp; GO TO MYTAGO.COM</text>" << endl ;


	return true;
}

/* 
char*
Code::getColor(int color )
{
	switch(color){
		case RED: { return "#ff0000"; break; }
		case GREEN: { return "#00ff00"; break; }
		case BLUE: { return "#0000ff"; break; }
		default: { break; }
	}
	return "#000000";
}
*/

void
Code::closeDoc( )
{
	if( ofs.is_open() ) {
		ofs << "</g>" << endl ;
		ofs << "</svg>" << endl ;
                ofs.close();
	}
}

