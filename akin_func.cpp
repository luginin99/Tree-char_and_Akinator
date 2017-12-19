#include <stdio.h>

Akinator::Akinator ()
{
    root = new Tree (CAPACITY);
}


Node* Akinator::Head ()
{
    return root->head;
}
int strlen (char *  buf)
{
    if (buf == NULL)
        return 0;

    int Num_symb = 0;

    for (Num_symb=0; buf[Num_symb]!=0 ; Num_symb++);

    return Num_symb;
}

Node* Akinator::AddNewObj (Node* nd)
{
    char* answer = new char(CAPACITY);

    printf ("Даже гении совершают ошибки\nКого вы загадали?\n");

    scanf ("%s", answer);

    int i = strlen(answer);

    while ((answer[i++] = getchar())!='\n');

    answer[i-1] = '\0';

    nd->R_push  (answer);
    char* question = new char (CAPACITY);

    printf ("Чем %s отличается от %s?\n", answer, nd->line);

    i = 0;
    while ((question[i++] = getchar())!='\n');


    question[i-1] = '\0';

    nd->L_push (nd->line);
    nd->line = question;

    return nd->right;
}

void Akinator::GiveCharacteristic(Node* nd)
{
    Node* cur = nd;
    printf ("%s обладает следующими свойствами: ", cur->line);
    while (cur->root_l != 0 || cur->root_r != 0)
    {
        if (cur->root_l != 0)
        {
            printf ("не %s, ", cur->root_l->line);
            cur = cur->root_l;
        }
        if (cur->root_r != 0)
        {
            printf ("%s, ", cur->root_r->line);
            cur = cur->root_r;
        }
    }
    printf ("был загадан вами))\n");
}


void Akinator::CompareCharacteristicWith  (Node* node1, Node* node2)
{
    GiveCharacteristic (node1);
    printf ("a ");
    GiveCharacteristic (node2);
}


void Akinator::PrintToFile(FILE* file)
{
    root->PrintToFile(file);
}

int Akinator::ScanFromFile (FILE* file)
{
    return root->ScanFromFile(file);
}

void Akinator::DotDump ()
{
    root->DotDump();
}
