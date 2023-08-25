#include <iostream>

using namespace std;

class Node {
public:
	int value;
	Node* prev;
	Node* next;

	Node(int v, Node* p, Node* n){
		this->value = v;
		prev = p;
		next = n;
	}
};

class List {
	Node* head;
	Node* tail;
public:
	List() {
		head = tail = nullptr;
	}

	Node* Find(int index) {
		if (head != nullptr) {
			Node* current = head;
			int i = 1;
			for (int i = 1; current != nullptr && i != index; current = current->next, i++);
			return current;
		}
		return nullptr;
	}

	void InsertAt(int value, int index = 1) {
		if (Find(index) != nullptr || head == nullptr) {
			Node* node = Find(index);
			Node* newNode = new Node(value, node != nullptr ? node->prev : nullptr, node);
			if (head == nullptr) {
				head = tail = newNode;
				return;
			}
			else if (index == 1) {
				node->prev = newNode;
				head = newNode;
				return;
			}
			node->prev->next = newNode;
			node->prev = newNode;
		}
		else {
			tail->next = new Node(value, tail, nullptr);
			tail = tail->next;
		}
	}

	void DeleteAt(int index) {
		if (index <= 0)return;
		if (head != nullptr) {
			Node* node = Find(index);
			if (node == nullptr)node = tail;
			if (head == tail) {
				delete head;
				head = tail = nullptr;
				return;
			}
			node->prev != nullptr ? node->prev->next = node->next : nullptr;
			node->next != nullptr ? node->next->prev = node->prev : nullptr;
			if (node == head) {
				head = head->next;
			}
			else if (node == tail) {
				tail = tail->prev;
			}
			delete node;
		}
	}

	void RemoveDublicates() {
		Node* current = head;
		for (int i = 1, pos; current != nullptr; current = current->next, i++) {
			pos = Contains(current->value, i);
			while (pos > 0) {
				DeleteAt(pos);
				pos = Contains(current->value, pos - 1);
			}
		}
	}

	void Reverse() {
		swap(head, tail);
		Node* current = head;
		while (current != nullptr) {
			swap(current->next, current->prev);
			current = current->next;
		}
	}

	void PrintList()const {
		Node* current = head;
		while (current != nullptr) {
			cout << current->value << "   ";
			current = current->next;
		}cout << endl << endl;
	}

	void PrintReverse() {
		Node* current = tail;
		while (current != nullptr) {
			cout << current->value << "   ";
			current = current->prev;
		}cout << endl << endl;
	}

	int GetSize()const {
		int i = 0;
		Node* current = head;
		while (current != nullptr) {
			i++;
			current = current->next;
		}
		return i;
	}

	bool Contains(int value) {
		Node* current = head;
		while (current != nullptr) {
			if(current->value == value)return true;
			current = current->next;
		}
		return false;
	}

	int Contains(int value, int start) {
		Node* current = Find(start  + 1);
		for (int i = start + 1; current != nullptr; current = current->next ,i++) {
			if (current->value == value)return i;
		}
		return -999999;
	}

	int CountOccurrences(int value) {
		Node* current = head;
		int counter = 0;
		while (current != nullptr) {
			if (current->value == value)counter++;
			current = current->next;
		}
		return counter;
	}

	int GetFirst() {
		return head != nullptr ? head->value : -99999;
	}

	int GetLast() {
		return tail != nullptr ? tail->value : -99999;
	}

	int GetAt(int index) {
		Node* current = head;
		for (int i = 1; current != nullptr && i != index; current = current->next, i++);
		return current != nullptr ? current->value : -99999;
	}

	~List() {
	while (head != nullptr) {
		Node* temp = head;
		head = head->next;
		delete temp;
		}
	}
};

void main() {
	List list;
	list.InsertAt(1);
	list.InsertAt(2, 2);
	list.InsertAt(3, 3);
	list.InsertAt(4, 1);
	list.InsertAt(5, 5);
	list.PrintList();
	list.DeleteAt(3);
	list.DeleteAt(1);
	list.DeleteAt(2);
	list.PrintList();
	list.Reverse();
	list.PrintList();
	list.InsertAt(2, 2);
	list.InsertAt(3, 4);
	list.PrintList();
	cout << "Size of list : " << list.GetSize() << endl;
	cout << "List contains 5 : " << boolalpha << list.Contains(5) << endl;
	cout << "Reversed list :\n";
	list.PrintReverse();
	list.InsertAt(2);
	list.InsertAt(3, 2);
	list.InsertAt(2, 4);
	list.InsertAt(1);
	list.InsertAt(5, 5);
	list.PrintList();
	list.RemoveDublicates();
	list.PrintList();
	list.InsertAt(2, 4);
	list.InsertAt(1);
	list.InsertAt(5, 5);
	list.PrintList();
	cout << "Number of occurrences of number 5 is : " << list.CountOccurrences(5) << endl;
	cout << "First item in list is : " << list.GetFirst() << endl;
	cout << "Last item in list is : " << list.GetLast() << endl;
	cout << "Item number 3 is : " << list.GetAt(3) << endl;
}