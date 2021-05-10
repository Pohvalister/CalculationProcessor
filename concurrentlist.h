#ifndef CONCURRENTLIST_H
#define CONCURRENTLIST_H

#include <QAtomicPointer>

template<typename TVal>
class ConcurrentStack
{
private:

    struct Node{
        Node(TVal v, Node* n)
            : val(v)
            , next(n)
        {}

        Node* next;
        const TVal val;
    };


    QAtomicPointer<Node> head;

public:
    ConcurrentStack()
        : head(nullptr)
    {}

    void push(TVal value){
        Node* to_insert = new Node(value, head);
        while(!head.testAndSetOrdered(to_insert->next, to_insert))
            to_insert->next = head;
    }

    TVal pop(bool & not_empty){
        Node* to_erase;
        do{
            to_erase = head;
            if (!to_erase){
                not_empty = false;
                break;
            }
        } while (!head.testAndSetOrdered(to_erase, to_erase->next));

        TVal& pop_val= to_erase->val;
        not_empty = true;
        delete to_erase;
        return pop_val;
    }
};

#endif // CONCURRENTLIST_H
