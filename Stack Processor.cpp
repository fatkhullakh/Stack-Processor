#include <iostream>
using namespace std;
const int MAX = 20001;
char program[MAX];
char input[MAX];
int inputPointer = 0;
int inputLength;     // Removed global initialization—will be set in main.
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
	cout << endl;
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

void printStackReversed(StackNode* node, int index = 0) {
	if (!node) return;

	// First go deeper
	printStackReversed(node->next, index + 1);

	// Then print on the way back
	cout << index << ": ";
	printCharList(node->list);
}


void printStack(StackNode* stackTop, int index = 0) {
	if (!stackTop) return;
	cout << index << ": ";
	printCharList(stackTop->list);
	printStack(stackTop->next, index + 1);
}


int getLength(int i = 0) {
	if (program[i] == '\0') return i;
	return getLength(i + 1);
}

int charListToIntHelper(CharNode* node, int mult) {
	if (!node) return 0;

	if (!node->next && node->value == '-') return 0;

	int digit = node->value - '0';
	return digit * mult + charListToIntHelper(node->next, mult * 10);
}

int charListToInt(CharNode* head) {
	if (!head) return 0;

	int result = charListToIntHelper(head, 1);

	CharNode* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	if (temp->value == '-') result = -result;

	return result;
}

CharNode* intToCharList(int value) {
	if (value == 0)
		return createCharNode('0');

	bool isNegative = false;
	if (value < 0) {
		isNegative = true;
		value = -value;
	}

	CharNode* head = nullptr;
	while (value > 0) {
		int digit = value % 10;
		head = prependChar(head, digit + '0');
		value /= 10;
	}
	if (isNegative) {
		CharNode* tail = head;
		while (tail->next) tail = tail->next;
		tail->next = createCharNode('-');
	}
	return head;
}

void interpret(int ip, StackNode*& stackTop) {
	if (ip >= programLength) return;

	char instr = program[ip];

	switch (instr) {
	case '\'': {
		push(stackTop, nullptr);
		break;
	}
	case ':': {
		if (stackTop) {
			CharNode* copy = copyCharList(stackTop->list);
			push(stackTop, copy);
		}
		break;
	}
	case ';': {
		swapTopTwo(stackTop);
		break;
	}
	case '.': {
		if (inputPointer < inputLength) {
			char ch = input[inputPointer++];
			if (stackTop) {
				stackTop->list = prependChar(stackTop->list, ch);
			}
		}
		break;
	}
	case '>': {
		if (stackTop && stackTop->list) {
			cout << stackTop->list->value;
			pop(stackTop);
		}
		break;
	}
	case '&': {
		printStackReversed(stackTop);
		break;
	}
	case '+': {
		CharNode* aList = pop(stackTop);
		CharNode* bList = pop(stackTop);

		int a = charListToInt(aList);
		int b = charListToInt(bList);

		int result = a + b;

		CharNode* resultList = intToCharList(result);
		push(stackTop, resultList);

		deleteCharList(aList);
		deleteCharList(bList);
		break;
	}
	case '-': {
		if (stackTop && stackTop->list) {
			CharNode* temp = stackTop->list;
			while (temp->next && temp->next->next != nullptr) {
				temp = temp->next;
			}
			// Now check the last node
			if (temp->next && temp->next->value == '-') {
				delete temp->next;
				temp->next = nullptr;  // remove '-'
			}
			else {
				// append '-' at the end
				CharNode* tail = temp;
				while (tail->next) tail = tail->next;
				tail->next = createCharNode('-');
			}
		}
		break;
	}
	case ',': {
		pop(stackTop);
		break;
	}
	case '@': {
		CharNode* cList = pop(stackTop);
		int c = charListToInt(cList);
		deleteCharList(cList);

		
		StackNode* target = getStackNodeAtIndex(stackTop, c);

		if (target) {
			CharNode* ccopy = copyCharList(target->list);
			push(stackTop, ccopy);
		}
		break;
	}
	default:
		if (stackTop) {
			stackTop->list = prependChar(stackTop->list, instr);
		}
		break;
	}
	interpret(ip + 1, stackTop);
}

void deleteStackNode(StackNode* head) {
	while (head) {
		StackNode* next = head->next;
		delete head;
		head = next;
	}
}

int main() {

	cin.getline(program, MAX);
	cin.getline(input, MAX); // Safe even if input is not provided.

	programLength = strlen(program);
	inputLength = strlen(input);

	// Start with an empty stack.
	StackNode* stackTop = nullptr;
	interpret(0, stackTop);

	// Clean up remaining stack nodes.
	deleteStackNode(stackTop);

	return 0;
}