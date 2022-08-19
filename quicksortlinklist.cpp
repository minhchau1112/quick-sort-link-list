#include <cstdio>
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct List {
    Node* top;
};


void Push(List &l, int data) {
    Node* p = new Node;
    if (p == NULL) {
        cout << "Stack Overfolow" << endl;
        return;
    }
    p->data = data;
    p->next = l.top;
    l.top = p;
}

void printList(List l)
{
    for (Node* p = l.top; p; p = p->next) {
        cout << p->data << " ";
    }
    cout << endl;
}

Node* getTail(Node* cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

Node* partition(Node* l,Node* r,List &new_left,List &new_right)
{
    Node* pivot = r;
    Node* prev = NULL, * cur = l, * tail = pivot;

    while (cur != pivot) {
        if (cur->data < pivot->data) {
            if (new_left.top == NULL)
                new_left.top = cur;
            prev = cur;
            cur = cur->next;
        }
        else 
        {
            if (prev) prev->next = cur->next;
            Node* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if (new_left.top == NULL)
        new_left.top = pivot;
    new_right.top = tail;
    return pivot;
}

Node* QuickSort_Recur(Node* l,Node* r)
{
    if (l==NULL || l == r) return l;
    List new_left, new_right;
    new_left.top = NULL, new_right.top = NULL;
    Node* pivot= partition(l, r, new_left, new_right);

    if (new_left.top != pivot) {
        Node* temp = new_left.top;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = NULL;
        new_left.top = QuickSort_Recur(new_left.top, temp);
        temp = getTail(new_left.top);
        temp->next = pivot;
    }

    pivot->next = QuickSort_Recur(pivot->next, new_right.top);

    return new_left.top;
}

void quickSort(List &head)
{
    head.top = QuickSort_Recur(head.top, getTail(head.top));
    return;
}

// Driver code
int main()
{
    List head;
    head.top = NULL;
    Push(head, 20);
    Push(head, 40);
    Push(head, 35);
    Push(head, 24);
    Push(head, 2);
    Push(head, 8);
    Push(head, 19);
    Push(head, 65);
    Push(head, 22);
    Push(head, 18);
    Push(head, 11);
    Push(head, 10);
    cout << "Linked List before sorting \n";
    printList(head);
    quickSort(head);
    cout << "Linked List after sorting \n";
    printList(head);
    return 0;
}