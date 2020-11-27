#pragma once
#include <cassert>

// Class declaration
template <class T> class LinkIterator;
template <class T> class PriorityQueueLinkedList;

// Define a node
template <class T>
class LinkNode
{
public:
	// Give access to the private member variables
	friend class LinkIterator<T>;
	friend class PriorityQueueLinkedList<T>;
	T getData(){return m_data;}
	int getPriority() const {return m_priority;}
private:
	int m_priority;
	T m_data;
	LinkNode* m_next;
	LinkNode* m_previous;
};

// Define our iterator
// Be used to access, manipulate and traverse our linked list
template <class T>
class LinkIterator
{
public:
	friend class PriorityQueueLinkedList<T>; // New Addition

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
	// Decremental Operators (--) -- Prefix and Postfix
	void operator--()		// Prefix
	{
		assert(m_node != NULL);
		m_node = m_node->m_previous;
	}
	void operator--(int)	// Postfix
	{
		assert(m_node != NULL);
		m_node = m_node->m_previous;
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
	bool isValid()
	{
		return (m_node != NULL);
	}
private:
	LinkNode<T>* m_node;	// Points to a node in the linked list
};

// Define the linked list itself
template <class T>
class PriorityQueueLinkedList
{
public:
	PriorityQueueLinkedList() : m_size(0), m_root(0), m_lastNode(0) {}
	~PriorityQueueLinkedList()
	{
		while (m_root)
		{
			Pop();
		}
	}
	// ------------------ POSITIONING FUNCTIONS --------------------------
	LinkNode<T>* Front()
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
	void Push(T newData, int priority)
	{
		// Create a standalone LinkNode object
		LinkNode<T>* node = new LinkNode<T>;

		assert(node != NULL);
		node->m_data = newData;
		node->m_priority = priority;
		node->m_next = NULL;
		node->m_previous = NULL;

		//Check priority being 1 the highest priority.
		if(m_root == NULL)
		{
			m_root = node;
			m_lastNode = node;
			m_size++;
			return;
		}
		LinkNode<T>* temp = m_root;
		
		while(temp != NULL && temp->m_priority <= node->m_priority)
		{
			temp = temp->m_next;
		}
		
		if(temp == NULL)
		{
			Insert_After(m_lastNode, node);
			return;
		}
		if(temp->m_priority == node->m_priority) //when they are the same insert after
			Insert_After(temp, node);
		else
			Insert_Before(temp,node);
		
	}
	void Pop()
	{
		assert(m_root != NULL);

		// We are eventually deleting the contents of temp
		LinkNode<T>* temp = m_root;

		// Re-route my pointers
		m_root = m_root->m_next;

		if (m_root != NULL)
		{
			m_root->m_previous = NULL;
		}
		else
		{
			m_lastNode = NULL;
		}

		delete temp;
		temp = NULL;

		m_size = (m_size == 0 ? m_size : m_size - 1);
	}
	int GetSize()
	{
		return m_size;
	}
private:
	// ------------------ PRIORITY QUEUE FUNCTIONS ----------------------
	void Insert_Before(LinkNode<T>* oldNode, LinkNode<T>* newNode)
	{
		assert(oldNode != NULL);

		LinkNode<T>* node = newNode;
		assert(node != NULL);

		node->m_next = oldNode;
		node->m_previous = oldNode->m_previous;

		if (node->m_previous != NULL)
		{
			// Point the previous node to the new node
			node->m_previous->m_next = node;
		}

		oldNode->m_previous = node;

		// Check to see if the iterator was pointing to the root
		if (oldNode == m_root)
		{
			m_root = node;
		}

		m_size++;
	}
	void Insert_After(LinkNode<T>* oldNode, LinkNode<T>* newNode)
	{
		assert(oldNode != NULL);

		LinkNode<T>* node = newNode;
		assert(node != NULL);

		node->m_next = oldNode->m_next;
		node->m_previous = oldNode;

		if (node->m_next != NULL)
		{
			node->m_next->m_previous = node;
		}

		oldNode->m_next = node;

		if (oldNode == m_lastNode)
		{
			m_lastNode = node;
		}

		m_size++;
	}

private:
	int m_size;					// Holds the size of the linked list
	LinkNode<T>* m_root;		// Point to the root of the linked list
	LinkNode<T>* m_lastNode;	// Point to the last node of the linked list
};