#ifndef _SFL_OBJECT_POOL_H_
#define _SFL_OBJECT_POOL_H_

namespace edog
{

template<class T>
class ObjectPool
{
    struct Node
    {
        ~Node(void)
        {
            next = (Node *)-1;
        }

        char obj[sizeof(T)];
        Node *next;
    };

    Node *_head;

public:
    ObjectPool(void)
    {
        _head = NULL;
    }

    ~ObjectPool(void)
    {
        while (_head != NULL)
        {
            Node *next = _head->next;
            delete _head;
            _head = next;
        }
    }

    T *alloc(void)
    {
        Node *node = alloc_node();
        return new(node->obj)T();
    }

    template<class P>
    T *alloc(P &p)
    {
        Node *node = alloc_node();
        return new(node->obj)T(p);
    }

    void free(T *obj)
    {
        obj->~T();
        Node *node = reinterpret_cast<Node *>(obj);
        node->next = _head;
        _head = node;
    }

private:
    Node *alloc_node(void)
    {
        Node *node = NULL;
        if (_head == NULL)
        {
            node = new Node();
        }
        else
        {
            node = _head;
            _head = _head->next;
        }

        return node;
    }
};

}

#endif /* _SFL_OBJECT_POOL_H_ */
