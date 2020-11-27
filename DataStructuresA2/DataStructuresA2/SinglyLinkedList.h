#pragma once
#include <cassert>

// Class declaration
template <class T> class LinkIterator;
template <class T> class LinkedList;

// Define a node
template <class T>
class LinkNode
{
public:
	// Give access to the private member variables
	friend class LinkIterator<T>;
	friend class LinkedList<T>;
private:
	T m_data;
	LinkNode* m_next;
};

// Define our iterator
// Be used to access, manipulate and traverse our linked list
template <class T>
class LinkIterator
{
public:
	LinkIterator()
	{
		m_node = NULL;
	}
	~LinkIterator() {}
	// -------------OVERLOADED OPERATORS-------------------
	// Assignment operator (=)
	void operator=(LinkNode<T>* node)
	{
		m_node = node;
	}
	// Dereferencing operator (*)
	T& operator*()
	{
		assert(m_node != NULL);
		return m_node->m_data;
	}
	// Incremental operator (++) -- Prefix and Postfix
	void operator++()		// Prefix
	{
		assert(m_node != NULL);
		m_node = m_node->m_next;
	}
	void operator++(int)	// Postfix
	{
		assert(m_node != NULL);
		m_node = m_node->m_next;
	}
	// Comparison Operator (!= & ==)
	bool operator!=(LinkNode<T>* node)
	{
		return (m_node != node);
	}
	bool operator==(LinkNode<T>* node)
	{
		return (m_node == node);
	}
private:
	LinkNode<T>* m_node;	// Points to a node in the linked list
};

// Define the linked list itself
template <class T>
class LinkedList
{
public:
	LinkedList() : m_size(0), m_root(0), m_lastNode(0) {}
	~LinkedList()
	{
		while (m_root)
		{
			Pop();
		}
	}
	// ------------------ POSITIONING FUNCTIONS --------------------------
	LinkNode<T>* Begin()
	{
		assert(m_root != NULL);
		return m_root;
	}
	LinkNode<T>* End()
	{
		return NULL;
	}
	LinkNode<T>* Last()
	{
		return m_lastNode;
	}
	// ------------------- END POSITION FUNCTIONS ------------------------
	// ------------------- LINKED LIST OPERATIONS ------------------------
	void Push(T newData)
	{
		// Create a standalone LinkNode object
		LinkNode<T>* node = new LinkNode<T>;

		assert(node != NULL);
		node->m_data = newData;
		node->m_next = NULL;

		// Add new LinkNode to the existing LinkedList
		if (m_lastNode != NULL)	// Link list is populated. Push to the end of the list
		{
			m_lastNode->m_next = node;
			m_lastNode = node;
		}
		else  // An empty link list
		{
			m_root = node;
			m_lastNode = node;
		}

		m_size++;
	}
	void Pop()
	{
		assert(m_root != NULL);

		if (m_root->m_next == NULL)
		{
			delete m_root;
			m_root = NULL;
			m_lastNode = NULL;
		}
		else  // Linked list has 2 or more items
		{ 
			LinkNode<T>* prevNode = m_root;

			// Traverse the linked list until we reach the end
			while (prevNode->m_next != NULL && prevNode->m_next != m_lastNode)
			{
				prevNode = prevNode->m_next;
			}

			// The previous while look simply positions the pointer to the 2nd last node in the list
			delete m_lastNode;
			prevNode->m_next = NULL;
			m_lastNode = prevNode;

			prevNode = NULL;
		}

		m_size = (m_size == 0 ? m_size : m_size - 1);	// Prevent negative sizes
	}
	int GetSize()
	{
		return m_size;
	}
private:
	int m_size;					// Holds the size of the linked list
	LinkNode<T>* m_root;		// Point to the root of the linked list
	LinkNode<T>* m_lastNode;	// Point to the last node of the linked list
};