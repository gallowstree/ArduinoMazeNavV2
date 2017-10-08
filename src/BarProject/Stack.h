//
// Created by daniel on 20/04/17.
//

#ifndef STRUCTURES_STACK_H
#define STRUCTURES_STACK_H
#define NULL 0

template <class T>
class Stack
{
    public:

        Stack()
        {
            this->head = nullptr;
            this->tail = nullptr;
        }

        void push(T data)
        {
            Node * node = new Node;
            node->data = data;
            node-> next = nullptr;
            if(this->isEmpty())
            {
                this->head = this->tail = node;
            }
            else
            {
                this->tail->next = node;
                this->tail = node;
            }
        }

        T pop()
        {
            T data = NULL;
            if (!this->isEmpty())
            {
                Node *currentTail = nullptr;
                if (this->head == this->tail) {
                    currentTail = this->tail;
                    this->head = this->tail = nullptr;
                }
                else
                {
                    Node *node = this->head;
                    while ((node->next != this->tail) && (node->next != nullptr)) {
                        node = node->next;
                    }
                    currentTail = this->tail;
                    this->tail = node;
                    this->tail->next = nullptr;
                }
                data = currentTail->data;
                delete currentTail;
            }
            return data;
        }

        bool isEmpty()
        {
            return this->head == nullptr;
        }

        void print()
        {
            /*Node * node = this->head;
            while(node != nullptr)
            {
                printf("%c,", node->data);
                node = node->next;
            }
            printf("\n");*/
        }

        ~Stack()
        {
            while(!this->isEmpty())
            {
                this->pop();
            }

            if(this->head != nullptr)
                delete this->head;
            if(this->tail != nullptr)
                delete this->tail;
        }

    private:
        struct Node{
            Node * next;
            T data;
        };
        Node * head;
        Node * tail;
};

#endif //STRUCTURES_STACK_H
