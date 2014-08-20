#include "code.h"
#include <wand/magick-wand.h>

void test(void);
void runtest(char* code, char* image);
Code *code = NULL;

int
main( int argc, char* argv[] )
{
	test();
	return 0;
}

void
test()
{
	code = new Code();
	runtest( "123412341234", "1234-1234-1234.svg" );
	runtest( "111111111111", "1111-1111-1111.svg" );
	runtest( "000000000000", "0000-0000-0000.svg" );
	runtest( "012345678900", "0123-4567-8900.svg" );
}
void
runtest(char *value, char *image)
{
	if( code == NULL ){
		cout << "Code Engine Not Initilised !" << endl ;
		return;
	}
	if ( code->createCode( value, image ) ){
		cout << value << " - failed !" << endl ;
	}
}
