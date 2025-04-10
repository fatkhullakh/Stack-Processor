#include <iostream>
using namespace std;
const int MAX = 20001;
char program[MAX];
char input[MAX];
long long int inputPointer = 0;
long long int inputLength;
long long int programLength = 0;

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

StackNode* getStackNodeAtIndex(StackNode* stackTop, long long int index) {
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

void printStackReversed(StackNode* node, long long int index = 0) {
	if (!node) return;

	printStackReversed(node->next, index + 1);

	cout << index << ": ";
	printCharList(node->list);
}


void printStack(StackNode* stackTop, long long int index = 0) {
	if (!stackTop) return;
	cout << index << ": ";
	printCharList(stackTop->list);
	printStack(stackTop->next, index + 1);
}


long long int getLength(long long int i = 0) {
	if (program[i] == '\0') return i;
	return getLength(i + 1);
}


long long charListToIntHelper(CharNode* node, long long mult) {
	if (!node) return 0;
	if (!node->next && node->value == '-') return 0;

	// Prevent overflow when multiplier is too large
	if (mult > 100000000000000000LL) return 0;

	int digit = node->value - '0';
	return digit * mult + charListToIntHelper(node->next, mult * 10);
}


long long int charListToInt(CharNode* head) {
	if (!head) return 0;
	long long result = charListToIntHelper(head, 1);
	CharNode* temp = head;
	while (temp->next) temp = temp->next;
	if (temp->value == '-') result = -result;
	return static_cast<int>(result); 
}


void appendChar(CharNode*& head, char ch) {
	if (!head) {
		head = createCharNode(ch);
		return;
	}
	CharNode* curr = head;
	while (curr->next)
		curr = curr->next;
	curr->next = createCharNode(ch);
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
		appendChar(head, digit + '0');
		value /= 10;
	}
	if (isNegative) {
		CharNode* tail = head;
		while (tail->next) tail = tail->next;
		tail->next = createCharNode('-');
	}
	return head;
}

void removeTrailingMinus(CharNode*& head) {
	if (!head) return;

	if (!head->next && head->value == '-') {
		delete head;
		head = nullptr;
		return;
	}

	CharNode* curr = head;
	while (curr->next && curr->next->next) {
		curr = curr->next;
	}

	if (curr->next && curr->next->value == '-') {
		delete curr->next;
		curr->next = nullptr;
	}
}

void deleteSingleChar(CharNode*& head, char target) {
	if (!head) return;

	// If the first node is the one to delete
	if (head->value == target) {
		CharNode* temp = head;
		head = head->next;
		delete temp;
		return;
	}

	// Traverse to find the node before the one we want to delete
	CharNode* current = head;
	while (current->next && current->next->value != target) {
		current = current->next;
	}

	// If found, delete it
	if (current->next) {
		CharNode* temp = current->next;
		current->next = temp->next;
		delete temp;
	}
}


//bool isZeroList(CharNode* head) {
//	while (head && head->value == '0') {
//		head = head->next;
//	}
//	return head == nullptr || (head->next == nullptr && head->value == '-');
//}
//
//CharNode* trimLeadingZeros(CharNode* head) {
//	while (head && head->value == '0' && head->next) {
//		head = head->next;
//	}
//	return head;
//}
//
//bool charListEquals(CharNode* a, CharNode* b) {
//	if (isZeroList(a) && isZeroList(b)) return true;
//
//	a = trimLeadingZeros(a);
//	b = trimLeadingZeros(b);
//
//	// Compare each digit including optional trailing '-'
//	while (a && b) {
//		if (a->value != b->value)
//			return false;
//		a = a->next;
//		b = b->next;
//	}
//	return a == nullptr && b == nullptr;
//}

bool charListEquals(CharNode* a, CharNode* b) {
	CharNode* temp1 = a;
	CharNode* temp2 = b;

	int sum1 = 0, sum2 = 0;
	bool neg1 = false, neg2 = false;



	while (temp1->next) {
		sum1 += temp1->value;
		temp1 = temp1->next;

	}

	if (!a && !b) return true;             // both ended → equal
	if (!a || !b) return false;            // one ended → not equal
	if (a->value != b->value) return false; // values differ → not equal

	if (temp1->value == '-') {
		neg1 = true;
		deleteSingleChar(temp1, temp1->value);
	}
	else if (temp2->value == '-')
	{
		neg2 = true;
		deleteSingleChar(temp2, temp2->value);
	}


	return charListEquals(a->next, b->next); // keep comparing
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
		if (!stackTop) break;

		CharNode* list = stackTop->list;

		// empty list
		if (!list) {
			stackTop->list = createCharNode('-');
			break;
		}

		CharNode* curr = list;

		// only one node, and it's '-'
		if (!curr->next && curr->value == '-') {
			delete curr;
			stackTop->list = nullptr;
			break;
		}

		while (curr->next && curr->next->next) {
			curr = curr->next;
		}

		if (curr->next && curr->next->value == '-') {
			delete curr->next;
			curr->next = nullptr;
		}
		else {
			CharNode* tail = stackTop->list;
			while (tail->next) tail = tail->next;
			tail->next = createCharNode('-');
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
	case '^': {
		if (stackTop && stackTop->list) {
			removeTrailingMinus(stackTop->list);
		}
		break;
	}
	case '$': {
		if (stackTop && stackTop->list) {
			CharNode* first = stackTop->list;
			stackTop->list = first->next;
			first->next = nullptr;

			push(stackTop, first);

			/*char d = stackTop->list->value;
			push(stackTop, nullptr);
			prependChar(stackTop->list, d);
			CharNode* temp = stackTop->list;
			temp = temp->next;
			stackTop->list = temp;
			delete temp;*/
		}
		break;
	}
	case '[': {
		CharNode* temp = pop(stackTop);
		if (temp) {
			char firstChar = temp->value;
			int asciiValue = static_cast<int>(firstChar);
			push(stackTop, intToCharList(asciiValue));
			deleteCharList(temp);
		}
		break;
	}
	case ']': {
		CharNode* temp = pop(stackTop);
		if (temp) {
			int firstInt = charListToInt(temp);
			char firstChar = static_cast<char>(firstInt);
			CharNode* firstNode = createCharNode(firstChar);
			push(stackTop, firstNode);
			deleteCharList(temp);
		}
		break;
	}
	case '#': {
		CharNode* A = pop(stackTop);
		if (!stackTop) break;

		if (!stackTop->list) {
			stackTop->list = A;
			break;
		}

		CharNode* temp = stackTop->list;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = A;
		break;
	}
	case '~': {
		CharNode* ipList = intToCharList(ip);
		push(stackTop, ipList);
		break;
	}
	case '!': {
		if (stackTop) {
			if (!stackTop->list || (stackTop->list->next == nullptr && stackTop->list->value == '0')) {
				deleteCharList(stackTop->list);
				stackTop->list = createCharNode('1');
			}
			else {
				deleteCharList(stackTop->list);
				stackTop->list = createCharNode('0');
			}
		}
		break;
	}
	case '=': {
	if (stackTop && stackTop->next) {
		CharNode* A = pop(stackTop);
		CharNode* B = pop(stackTop);

		if (charListEquals(A, B)) {
			push(stackTop, createCharNode('1'));
		} else {
			push(stackTop, createCharNode('0'));
		}
		
		deleteCharList(A);
		deleteCharList(B);
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

		deleteCharList(head->list);

		delete head;
		head = next;
	}
}

int main() {

	cin.getline(program, MAX);
	cin.getline(input, MAX); 

	programLength = strlen(program);
	inputLength = strlen(input);

	StackNode* stackTop = nullptr;
	interpret(0, stackTop);

	deleteStackNode(stackTop);
	return 0;
}


