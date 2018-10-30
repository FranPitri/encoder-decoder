#ifndef HASHMAP_H
#define HASHMAP_H

template<class K, class T>
class HashMap {
private:
    unsigned int hashFunc(K key);

    static unsigned int hashFuncDefault(K key) { return 0; };

    unsigned int (*hashFuncP)(K key);

    T **data;

    unsigned int size;

public:
    HashMap(unsigned int k);

    HashMap(unsigned int k, unsigned int (*hashFuncP)(K key));

    T get(K key);

    void put(K key, T value);

    void remove(K key);

    ~HashMap();

    bool isEmpty();

};

template<class K, class T>
HashMap<K, T>::HashMap(unsigned int k) {
    data = new T *[k];
    size = k;
    hashFuncP = this->hashFuncDefault;
    for (int i = 0; i < k; i++)
        data[i] = nullptr;
}

template<class K, class T>
HashMap<K, T>::HashMap(unsigned int k, unsigned int (*fp)(K)) {
    data = new T *[k];
    size = k;
    hashFuncP = fp;
    for (int i = 0; i < k; i++)
        data[i] = nullptr;
}

template<class K, class T>
HashMap<K, T>::~HashMap() {
    for (int i = 0; i < size; i++)
        if (data[i] != nullptr)
            delete data[i];

}

template<class K, class T>
T HashMap<K, T>::get(K key) {
    unsigned int idx = hashFunc(key);

    if (data[idx] == nullptr)
        return nullptr;

    return *data[idx];
}

template<class K, class T>
void HashMap<K, T>::put(K key, T value) {

    unsigned int idx = hashFunc(key);

    if (data[idx] != nullptr)
        throw 1;

    data[idx] = new T;
    *data[idx] = value;
}

template<class K, class T>
void HashMap<K, T>::remove(K key) {
    unsigned int idx = hashFunc(key);
    if (data[idx] == nullptr)
        throw 404;

    delete data[idx];

}

template<class K, class T>
bool HashMap<K, T>::isEmpty() {
    return false;
}

template<class K, class T>
unsigned int HashMap<K, T>::hashFunc(K key) {
    return hashFuncP(key);
}

#endif //HASHMAP_H