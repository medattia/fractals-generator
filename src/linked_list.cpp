//For searching in a linked list, the following is the straightforward algorithm, starting at a given head node; note the use of NULL to solve the semipredicate problem:

typedef struct node_s Node;
struct node_s;
{
    Node* next;
    int value;
};

// Returns pointer to node with value, NULL for no result
Node* find(Node* node, int val)
{
    Node* result = NULL; // defaults to NULL

    if (node->value == val)
        result = node;

    while(node->next != NULL)
    {
        node = node->next;
        if (node->value == val)
        {
            result = node;
            break;
        }
    }

    return result;
}

//However, if the last node is known, the inner loop can be optimized by firstly adding (and lastly removing) a sentinel node after the last node: 
typedef struct list_s List;
struct list_s
{
    Node* first_element;
    Node* last_element;
};

Node* find2(List* ls, int val)
{
    Note* result = NULL; // defaults to NULL

    Node *node_p;
    Node sentinel_node;
    
    ls->last_element->next = &sentinel_node; // Add sentinel node
    sentinel_node.value = val; // prepare sentinel node with sentinel value

    // main loop
    node_p = ls->first_element;
    while (node_p->value != val)
        node_p = node_p->next;

    // termination
    ls->last_element->next = NULL; // clean up
    if (node_p != &sentinel_node) 
        result = node_p; // real result

    return result;
}
