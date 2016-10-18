#ifndef __SMIMP_LIST_H
#define __SMIMP_LIST_H

#include <cstdlib>

template <class T>
class ListNode
{
private:
    int id;
    T* item;

public:
    ListNode(T*,int);
    ~ListNode();
    int getId();
    T* getItem();
};

template <class T>
class List
{
private:
    ListNode<T>** elements;
    int numElements;
    int maxElements;
    void resize(int);
    
public:
    List();
    ~List();
    bool add(T*,int);
    void remove(int);
    T* get(int);
};

#endif


template <class T>
ListNode<T>::ListNode(T* it, int i)
{
    item = it;
    id = i;
}

template <class T>
ListNode<T>::~ListNode()
{
    item = NULL;
}

template <class T>
int ListNode<T>::getId()
{
    return id;
}

template <class T>
T* ListNode<T>::getItem()
{
    return item;
}

template <class T>
List<T>::List()
{
    numElements = 0;
    maxElements = 4;
    resize(maxElements);
}

template <class T>
List<T>::~List()
{
    for (int i=0; i<numElements;i++) delete elements[i];
    delete elements;
}

template <class T>
void List<T>::resize(int size)
{
    ListNode<T>** temp = new ListNode<T>*[size];
    for (int i=0;i<numElements;i++)
    {
	temp[i] = elements[i];
	elements[i] = NULL;
    }
    delete elements;
    maxElements = size;
    elements = temp;
}

template <class T>
bool List<T>::add(T* i, int id)
{
    elements[numElements++] = new ListNode<T>(i,id);
    if (numElements >= maxElements) resize(maxElements*2);
    return true;
}

template <class T>
void List<T>::remove(int id)
{
    if (numElements > 0)
    {
	bool found = false;
	for (int i=0;i<numElements;i++)
	{
	    if (!found && elements[i]->getId() == id)
	    {
		delete elements[i];
		found = true;
	    }
	    if (found) elements[i] = elements[i+1];
	}
	numElements--;
    }
}

template <class T>
T* List<T>::get(int id)
{
    for (int i=0;i<numElements;i++) if (elements[i]->getId() == id) return elements[i]->getItem();
    return NULL;
}
