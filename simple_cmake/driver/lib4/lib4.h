#include <stdio.h>

class A4 {
public:
    void a4Func1(int indent) {
        printf("%*s%s\n", indent * 2, "", __FUNCTION__);
    }
private:    
};