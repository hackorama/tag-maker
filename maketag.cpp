#include "code.h"

int
main( int argc, char* argv[] )
{
	Code *code = new Code();
	int result = 0;
	if(argc > 4) result = code->createCode( argv[1], argv[2], argv[3], argv[4]);
	else if(argc > 3) result = code->createCode( argv[1], argv[2], argv[3]);
	else if(argc > 2) result = code->createCode( argv[1], argv[2], "default.svg" );
	else if(argc > 1) result = code->createCode( argv[1], "#ff0000", "default.svg");
	else cout << argv[0] <<" 123456789901 \"#ff0000\" [\"#000000\"] code.svg" << endl ;
	delete code;
	return result;
}
