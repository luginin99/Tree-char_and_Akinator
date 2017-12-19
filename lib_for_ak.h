#ifndef _LIB_FOR_AK_
#define _LIB_FOR_AK_
#include "treelib_char.h"

class Akinator
{
public:
    Tree* root;

    Node* AddNewObj(Node* nd);
    void GiveCharacteristic(Node* nd);
    void CompareCharacteristicWith  (Node* node1, Node* node2);

    Node* Head ();
    void PrintToFile(FILE* file);
    int ScanFromFile (FILE* file);
    void DotDump ();

    Akinator ();
};






#include "akin_func.cpp"
#endif // _LIB_FOR_AK_
