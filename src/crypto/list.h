#ifndef __SMIMP_LIST_H
#define __SMIMP_LIST_H

#include <cstdlib>

template <class T>
//! Nodes for the List class
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
//! General List Iterator
/*!
  Iterator iterates through array of ListNode. Order decided by order given.
*/
class Iterator
{
private:
    ListNode<T>** items;
    int loc;
    int size;
    
public:
    Iterator(int,ListNode<T>**);
    ~Iterator();

    T* next();
    bool hasNext();
};

template <class T>
//! Generic List implementation
/*! 
  Simple List implementation, does not sort elements. All searches are O(n).
*/
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

    /*!
      Appends element to the list.
    */
    bool add(T*,int);
    void remove(int);
    int size();
    bool isEmpty();
    T* get(int);
    T* getRandom();

    /*!
      Iterator iterates through array of ListNode
    */
    Iterator<T>* iterator();
};

#endif

////
//ListNode
////

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

////
//Iterator
////

template <class T>
Iterator<T>::Iterator(int c, ListNode<T>** i)
{
    loc = 0;
    size= c;
    items = i;
}

template <class T>
Iterator<T>::~Iterator()
{
}

template <class T>
T* Iterator<T>::next()
{
    if (hasNext()) return items[loc++]->getItem();

    return NULL;
}

template <class T>
bool Iterator<T>::hasNext()
{
    return loc < size;
}

////
//List
////

template <class T>
List<T>::List()
{
    numElements = 0;
    maxElements = 4;
    elements = new ListNode<T>*[maxElements];
}

template <class T>
List<T>::~List()
{
    delete[] elements;
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
    delete[] elements;
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
int List<T>::size()
{
    return numElements;
}

template <class T>
bool List<T>::isEmpty()
{
    return numElements == 0;
}

template <class T>
T* List<T>::get(int id)
{
    for (int i=0;i<numElements;i++) if (elements[i]->getId() == id) return elements[i]->getItem();
    return NULL;
}

//gets a psudo-random element from the list
template <class T>
T* List<T>::getRandom()
{
    return elements[rand()%numElements]->getItem();
}

template <class T>
Iterator<T>* List<T>::iterator()
{
    return new Iterator<T>(numElements,elements);
}
