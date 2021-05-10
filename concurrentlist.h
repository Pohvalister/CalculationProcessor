#ifndef CONCURRENTLIST_H
#define CONCURRENTLIST_H

#include <QAtomicPointer>
#include <iostream>

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

    void push(TVal value){
        std::cout<<"\npush:"<<value<<'\n';
        Node* to_insert = new Node(value, head);
        while(!head.testAndSetOrdered(to_insert->next, to_insert))
            to_insert->next = head;
    }

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
        std::cout<<"\npop:"<<pop_val<<'\n';
        return pop_val;
    }
};

#endif // CONCURRENTLIST_H
