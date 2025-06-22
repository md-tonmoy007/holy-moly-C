#ifndef Node_h
#define Node_h



enum DataType {
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    Bool,
    STRING
};


struct Node{

    void *data;
    int data_type; 
    int size;
    struct Node* next;
};

struct Node* node_Constructor(void* data, int data_type, int size);
void node_Destructor(struct Node* node);

#endif