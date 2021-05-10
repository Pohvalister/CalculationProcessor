#ifndef CONCURRENTLIST_H
#define CONCURRENTLIST_H

#include <QAtomicPointer>

//Data structure, used for asynchronous access to data
template<typename TVal>
class ConcurrentStack
{
private:

    struct Node{
        Node(TVal v, Node* n)
            : val(v)
            , next(n)
        {}

        const TVal val;
        Node* next;
    };


    QAtomicPointer<Node> head;

public:
    ConcurrentStack()
        : head(nullptr)
    {}
    //Push an item onto the top of stack
    void push(TVal value){
        Node* to_insert = new Node(value, head);
        while(!head.testAndSetOrdered(to_insert->next, to_insert))
            to_insert->next = head;
    }

    //Remove and item from the top of stack if exist; writes in <not_empty> whether item existed
    TVal pop(bool & not_empty){
        Node* to_erase;
        do{
            to_erase = head;
            if (to_erase == nullptr){
                not_empty = false;
                return 0;
            }
        } while (!head.testAndSetOrdered(to_erase, to_erase->next));

        TVal pop_val= to_erase->val;
        not_empty = true;
        delete to_erase;
        return pop_val;
    }
};

#endif // CONCURRENTLIST_H
