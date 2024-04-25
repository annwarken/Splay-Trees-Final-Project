#include <iostream>
#include "SplayTree.h"

int main() {
    SplayTree mytree;

    mytree.insert(10);
    mytree.insert(5);
    mytree.insert(3);
    mytree.insert(7);

    mytree.print();

    std::cout << "Contains 3? " << mytree.contains(3) << std::endl;
    mytree.print();
    std::cout << "Contains 20? " << mytree.contains(20) << std::endl;
    mytree.print();

    mytree.insert(12);
    mytree.print();

    mytree.remove(7);
    mytree.print();

    /*mytree.insert(1);
    mytree.insert(4);
    mytree.insert(2);
    mytree.insert(6);
    mytree.insert(9);
    mytree.insert(8);
    mytree.insert(11);

    mytree.print();*/

    return 0;
}
