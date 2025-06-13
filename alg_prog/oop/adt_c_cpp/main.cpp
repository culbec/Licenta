#include "adt.h"

int main() {
    vec_struct MyStruct;
    
    int x[] = {1, 2, 3, 4, 5};
    int x_d = 5;

    MyStruct.init(x, x_d);
    MyStruct.print();
    MyStruct.squared();
    MyStruct.print();
    MyStruct.destroy();

    // declared private ===> INACCESSIBLE!!!
    // std::cout << MyStruct.e << " " << MyStruct.d << "\n";

    Vec_Class MyClass(x, x_d);
    MyClass.print();
    MyClass.squared();
    MyClass.print();

    // declared private ===> INACCESSIBLE!!!
    // std::cout << MyClass.e << " " << MyClass.d << "\n";
    
    // No need to call the destructor explicitly, it will be automatically
    // called when the function (scope) ends

    return 0;
}