#include <stdio.h>

const int CAPACITY = 50;
const int BRACKET_SHIFT = 2;
const int BEFORESTART = -1;

Node::Node()
{
    root_l = root_r = right = left = NULL;
    line = NULL;
}

Node::Node(int capacity)
{
    root_r = root_l = right = left = NULL;
    line = new char(capacity);
}

Node::Node(char* new_line)
{
    root_r = root_l = right = left = NULL;
    line = new_line;
}

Node::~Node()
{
    if (right)
        delete right;
    if (left)
        delete left;
    delete line;
}

int Node::OK ()
{
    if (!this)
        {
            printf ("ERROR pointer is NULL\n");
            return 0;
        }
}


Node* Node::R_push (T new_line)
{
    assert (OK());

    Node* nd  = new Node();
    right = nd;
    nd->line = new_line;
    nd->root_r = this;
    return nd;
}

Node* Node::L_push (T question)
{
    assert (OK());

    Node* nd = new Node();
    left = nd;
    nd->line = line;
    nd->root_l = this;
    line = question;
    return nd;

}

void Node::L_push_node (Node* nd)
{
    left = nd;
    nd->root_l = this;
}

void Node::R_push_node (Node* nd)
{
    right = nd;
    nd->root_r = this;
}

void Node::PrintToFile (FILE* file)
{

    fprintf (file, "(\n");
    fprintf (file, "%s\n", line);
    if (left)
        left->PrintToFile (file);
    if (right)
        right->PrintToFile (file);
    fprintf (file,")\n");
}

void Node::ScanFromBuf (char** buffer, int* i)
{
    char* buf = *buffer;
    (*i) += BRACKET_SHIFT;
    int j = 0;
    while (buf[*i] != '\n')
    {
        line[j] = buf[(*i)];
        (*i)++;
        j++;
    }
    line [j] = '\0';
    (*i)++;

    if (buf[*i] == '(')
    {
        Node* nd_l = new Node (CAPACITY);
        nd_l->ScanFromBuf (buffer, i);
        L_push_node (nd_l);
        Node* nd_r = new Node (CAPACITY);
        nd_r->ScanFromBuf (buffer, i);
        R_push_node (nd_r);
        (*i) +=BRACKET_SHIFT;
    }
    else
    {
        left = right = NULL;
        (*i) += BRACKET_SHIFT;
    }


}

Tree::Tree ()
{
    head = NULL;
}

Tree::Tree(char* question)
{
    head = new Node(question);
}



Tree::Tree (int capacity)
{
    head = new Node (capacity);
}

void Tree::PrintToFile(FILE* file)
{
    head->PrintToFile (file);
}

int Tree::ScanFromFile (FILE* file)
{
    fseek (file, 0, SEEK_END);
    long file_size = ftell (file);
    if (file_size == 0)
    {
        return 0;
    }
    rewind (file);
    int i = BRACKET_SHIFT;

    char* buffer = (char*) calloc (file_size + 1, sizeof(char));
    fread (buffer, sizeof(char), file_size, file);


    int j = 0;
    if (buffer[0] == '(')
    {

        while (buffer[i] != '\n')
        {
            head->line[j] = buffer[i];
            i++;
            j++;
        }
        head->line [j] = '\0';
        i++;
    }
    else
        {
            head = NULL;
            return 0;
        }
    if (buffer[i] == '(')
    {
        Node* nd_l = new Node (CAPACITY);
        nd_l->ScanFromBuf (&buffer, &i);
        head->L_push_node (nd_l);
        Node* nd_r = new Node (CAPACITY);
        nd_r->ScanFromBuf (&buffer, &i);
        head->R_push_node (nd_r);
    }
    return 1;

}

Tree::~Tree()
{
    if (head)
        delete head;
}


void Tree::DotDump ()
{
    FILE* file = fopen ("graph_dump.txt", "w");
    fprintf (file, "digraph G{\n");
    Node* cur= head;
    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", cur, cur -> line);
    cur->Dumper (file);
    fprintf (file, "}");
    fclose (file);
    system ("C:\\Progtam\\bin\\dot.exe -Tpng C:\\Users\\Snax\\Desktop\\c++\\Акинатор\\graph_dump.txt -o C:\\Users\\Snax\\Desktop\\c++\\Акинатор\\dump.png");
    system ("del graph_dump.txt");
    system ("dump.png");
}


int Node::Dumper (FILE* file)
{
    if (left)
    {
        fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", left, left -> line);
        fprintf (file, "%d -> %d [color = blue]\n", this, left);
        left->Dumper (file);
    }

    if (right)
    {
        fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", right, right -> line);
        fprintf (file, "%d -> %d [color = blue]\n", this, right);
        right->Dumper (file);
    }

    return 0;
}
