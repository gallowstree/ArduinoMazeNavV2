#ifndef MAZENAV_HASHMAPNODE_H
#define MAZENAV_HASHMAPNODE_H
template <typename V>
class HashNode {
public:
    HashNode(const char* key, V value) :
            key(key), value(value), next(nullptr) {
    }

    const char* getKey() const {
        return key;
    }

    V getValue() const {
        return value;
    }

    void setValue(V value) {
        this->value = value;
    }

    HashNode *getNext() const {
        return next;
    }

    void setNext(HashNode *next) {
        this->next = next;
    }

private:
    const char* key;
    V value;
    HashNode* next;
};

#endif