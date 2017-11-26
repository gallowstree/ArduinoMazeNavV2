#ifndef MAZENAV_HASHMAP_H
#define MAZENAV_HASHMAP_H

#include "HashNode.h"

template <typename V>
class HashMap {
public:
    HashMap() { }

    ~HashMap() {
        auto current = head;
        if(current == nullptr)
            return;
            
        while ((current = head->getNext()) != nullptr) {
            delete head;
            head = current;
        }
        delete head;
    }

    V get(const char* key) {        
        if (isEmpty()) return nullptr;

        HashNode<V>* node = findNode(key);
        if (node) {
            return node->getValue();
        }

        return nullptr;
    }

    void put(const char* key, V value) {
        if (head == nullptr) {
            head = tail = new HashNode<V>(key, value);
        } else {
            HashNode<V>* node = findNode(key);
            if (node) {
                node->setValue(value);
            } else {
                tail->setNext(new HashNode<V>(key, value));
                tail = tail->getNext();
            }
        }
    }

    void remove(const char* key) {
        if (isEmpty()) return;

        auto current = head;
        auto previous = head;
        do {
            if (strCmp(current->getKey(), key) == 0) {
                previous->setNext(current->getNext());
                delete current;
            }
            auto previous = current;
        } while ((current = current->getNext()) != nullptr);
    }

    bool isEmpty() {
        return head == nullptr;
    }

private:
    HashNode<V> * head = nullptr;
    HashNode<V> * tail = nullptr;

    int strCmp(const char* s1, const char* s2) {
        while(*s1 && (*s1 == *s2)) {
            s1++;
            s2++;
        }
        return *(const unsigned char*)s1 - *(const unsigned char*)s2;
    }

    HashNode<V>* findNode(const char* key) {
        auto current = head;
        if (isEmpty()) return nullptr;
        do {
            if (strCmp(current->getKey(), key) == 0) {
                return current;
            }
        } while ((current = current->getNext()) != nullptr);
        return nullptr;
    }
};

#endif