#include "lib2.h"

#include "lib3.h"
#include "lib4.h"

void lib2Func1(int indent){
	printf("%*s%s\n", indent * 2, "", __FUNCTION__);
    lib3Func1(indent + 1);

    A4 a4;
    a4.a4Func1(indent + 1);
}