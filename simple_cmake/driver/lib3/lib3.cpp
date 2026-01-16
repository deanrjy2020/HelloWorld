#include "lib3.h"

#include <stdio.h>

void lib3Func1(int indent){
	printf("%*s%s\n", indent * 2, "", __FUNCTION__);
}