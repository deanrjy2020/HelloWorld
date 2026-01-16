#include "lib1.h"

#include "lib2.h"
#include "lib3.h"
#include <stdio.h>

void lib1Func1(int indent){
	printf("%*s%s\n", indent * 2, "", __FUNCTION__);
    lib2Func1(indent + 1);

    lib3Func1(indent + 1);
}