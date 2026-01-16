#include "api.h"

#include "lib1.h"
#include <stdio.h>

int api1(void){
	int indent = 0;
	printf("%*s%s\n", indent * 2, "", __FUNCTION__);
    lib1Func1(indent);
    return 0;
}