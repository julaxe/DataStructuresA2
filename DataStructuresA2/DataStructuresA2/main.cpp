#include <iostream>
#include "PriorityQueueLinkedList.h"

int main()
{
	std::cout << "Priority Queue Test: " << std::endl << std::endl;
	PriorityQueueLinkedList<std::string> PriorityQueue;
	PriorityQueue.Push("Escobar",2);
	PriorityQueue.Push("Echeverri", 3);
	PriorityQueue.Push("Julian", 1);
	PriorityQueue.Push("Lucas",3);
	PriorityQueue.Push("Krespi",3);
	PriorityQueue.Push("Michael",3);
	PriorityQueue.Push("Cho",3);
	PriorityQueue.Push("Myeong",5);
	PriorityQueue.Push("Jin",4);
	

	while(PriorityQueue.GetSize() != 0)
	{
		std::cout<< PriorityQueue.Front()->getData() << ", " << PriorityQueue.Front()->getPriority() << std::endl;
		PriorityQueue.Pop();
	}
	
	
}