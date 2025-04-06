#include <iostream>
using namespace std;
const int MAX = 21;
char program[MAX];
char input[MAX];
int inputPointer = 0;
int programLength = 0;


struct CharNode {
	char value;
	CharNode* next;
};

struct StackNode {
	CharNode* list;
	StackNode* next;
};

CharNode* createCharNode(char ch, CharNode* next = nullptr) {
	CharNode* node = new CharNode;
	node->value = ch;
	node->next = next;
	return node;
}

CharNode* prependChar(CharNode* head, char ch) {
	return createCharNode(ch, head);
}

void printCharList(CharNode* head) {
	while (head) {
		cout << head->value;
		head = head->next;
	}
}

CharNode* copyCharList(CharNode* head) {
	if (!head) {
		return nullptr;
	}
	return createCharNode(head->value, copyCharList(head->next));
}

void deleteCharList(CharNode* head) {
	while (head) {
		CharNode* next = head->next;
		delete head;
		head = next;
	}
}


void push(StackNode*& stackTop, CharNode* list) {
	StackNode* newNode = new StackNode;
	newNode->list = list;
	newNode->next = stackTop;
	stackTop = newNode;
}


CharNode* pop(StackNode*& stackTop) {
	if (!stackTop) return nullptr;
	StackNode* temp = stackTop;
	CharNode* list = temp->list;

	stackTop = temp->next;
	delete temp;
	return list;
}

StackNode* getStackNodeAtIndex(StackNode* stackTop, int index) {
	if (!stackTop) return nullptr;
	if (index == 0) return stackTop;
	return getStackNodeAtIndex(stackTop->next, index - 1);
}

void swapTopTwo(StackNode*& stackTop) {
	if (!stackTop || !stackTop->next) return;
	StackNode* first = stackTop;
	StackNode* second = stackTop->next;

	first->next = second->next;
	second->next = first;
	stackTop = second;
}

void printStack(StackNode* stackTop) {
	if (!stackTop) return;

	printCharList(stackTop->list);
	printStack(stackTop->next);
}


int getLength(int i = 0) {
    if (program[i] == '\0') return i;
    return getLength(i + 1);
}

int main() {
	cin >> program;
	programLength = getLength();

	CharNode* list = nullptr; // empty list
	StackNode* stackTop = nullptr;

	for (int i = programLength - 1; i >= 0; i--) {
		list = prependChar(list, program[i]);
	}

	

	


	CharNode* list1 = nullptr;
	list1 = prependChar(list1, '3');
	list1 = prependChar(list1, '2');
	list1 = prependChar(list1, '1');

	CharNode* list2 = nullptr;
	list2 = prependChar(list2, 'C');
	list2 = prependChar(list2, 'B');
	list2 = prependChar(list2, 'A');

	CharNode* list3 = nullptr;
	list3 = prependChar(list3, '.');
	list3 = prependChar(list3, '.');
	list3 = prependChar(list3, '.');
	

	push(stackTop, list1);
	push(stackTop, list2);
	push(stackTop, list3);

	printStack(stackTop);
	cout << endl;
	swapTopTwo(stackTop);

	printStack(stackTop);



	/*CharNode* list = createCharNode('A', createCharNode('B', createCharNode('C')));
	cout << "Original list: ";
	printCharList(list);


	CharNode* listCopy = copyCharList(list);
	cout << "Copied list: ";
	printCharList(listCopy);

	list = prependChar(list, 'Z');
	cout << "After prepending Z: ";
	printCharList(list); */

	deleteCharList(list);
	deleteCharList(list1);
	deleteCharList(list2);
	deleteCharList(list3);
	return 0;
}




/*class LinkedList { //single linked list
public:
	Node* head;

	LinkedList(); // Constructor

	void insert(const char character);
	void printAll();
	void deleteList();
	~LinkedList() {
		deleteList();
	}
};

void LinkedList::deleteList() {
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
}

LinkedList::LinkedList() {
	head = nullptr;
}


void LinkedList::insert(const char character) {
	Node* newNode = new Node();
	newNode->value = character;

	if (head == nullptr) { // first node
		head = newNode;
	}
	else {
		Node* temp = head;
		while (temp->next != nullptr) { // to find the last node, by keep jumping the next pointers of the nodes
			temp = temp->next;
		}
		temp->next = newNode;
	}
}

void LinkedList::printAll() {
	Node* current = head;
	while (current != nullptr) {
		cout << current->value;
		current = current->next;
	}
}


class CharStack {
public:
	Node* top;
	CharStack() : top(nullptr) {}
	void push(char value) {
		Node* newNode = new Node();
		newNode->value = value;
		newNode->next = top;
		top = newNode;
	}

	char pop() {
		if (top == nullptr) { return '\0'; } // Indicates an empty stack
		Node* temp = top;
		char value = top->value;
		top = top->next;
		delete temp;
		return value;
	}

	char peek() {
		return top ? top->value : '\0'; // Return '\0' if stack is empty
	}

	bool isEmpty() {
		return top == nullptr;
	}

	~CharStack() {
		while (!isEmpty()) {
			pop(); // Pop should handle deletion of the top node.
		}
	}
}; 


int main() {
	char programStr[20001];
	char inputStr[20001];

	cin >> programStr;
	cin >> inputStr;
	//getline(cin, programStr);
	//getline(cin, inputStr);

	cout << programStr;
	cout << inputStr;
	return 0;
} */