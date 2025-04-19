#include <iostream>
using namespace std;
const int MAX = 20001;
char program[MAX];
char input[MAX];
int inputPointer = 0;
int inputLength;
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
	if (!head) {
		cout << '\n';
		return;
	}
	cout << head->value;
	printCharList(head->next);
}

CharNode* copyCharList(CharNode* head) {
	if (!head) {
		return nullptr;
	}
	return createCharNode(head->value, copyCharList(head->next));
}

void deleteCharList(CharNode* head) {
	if (!head) return;
	deleteCharList(head->next);
	delete head;
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

	printStackReversed(node->next, index + 1);

	cout << index << ": ";
	printCharList(node->list);
}

void printStack(StackNode* stackTop, int index = 0) {
	if (!stackTop) return;
	cout << index << ": ";
	printCharList(stackTop->list);
	printStack(stackTop->next, index + 1);
}

// Recursively converts a linked list of digits to an integer (handles least to most significant)
long long charListToIntHelper(CharNode* node, long long mult) {
	if (!node) return 0;
	if (!node->next && node->value == '-') return 0;

	// Prevent overflow when multiplier is too large
	if (mult > 100000000000000000LL) return 0;

	int digit = node->value - '0';
	return digit * mult + charListToIntHelper(node->next, mult * 10);
}

char getTailValue(CharNode* head) {
	return head->next ? getTailValue(head->next) : head->value;
}

int charListToInt(CharNode* head) {
	if (!head) return 0;
	int result = charListToIntHelper(head, 1);
	if (getTailValue(head) == '-') result = -result;
	return result;
}

void appendCharRecursive(CharNode*& head, char ch) {
	if (!head) {
		head = createCharNode(ch);
		return;
	}
	if (!head->next) {
		head->next = createCharNode(ch);
		return;
	}
	appendCharRecursive(head->next, ch);
}

CharNode* buildCharList(int value) {
	if (value == 0) return nullptr;
	CharNode* node = createCharNode((value % 10) + '0');
	node->next = buildCharList(value / 10);
	return node;
}

CharNode* getTail(CharNode* node) {
	if (!node || !node->next) return node;
	return getTail(node->next);
}

CharNode* intToCharList(int value) {
	if (value == 0) return createCharNode('0');
	bool isNegative = false;
	if (value < 0) {
		isNegative = true;
		value = -value;
	}
	CharNode* result = buildCharList(value);
	if (isNegative) {
		CharNode* tail = getTail(result);
		tail->next = createCharNode('-');
	}
	return result;
}

// Deletes a minus sign if it appears at the end of the number
void removeTrailingMinus(CharNode*& head) {
	if (!head) return;
	if (!head->next && head->value == '-') {
		delete head;
		head = nullptr;
		return;
	}
	if (head->next && !head->next->next && head->next->value == '-') {
		delete head->next;
		head->next = nullptr;
		return;
	}
	removeTrailingMinus(head->next);
}

int countDigits(CharNode* h) {
	if (!h) return 0;
	return (h->value == '-' ? 0 : 1) + countDigits(h->next);
}

bool charListEquals(CharNode* a, CharNode* b) {
	if (!a && !b) return true;
	if (!a || !b) return false;
	if (a->value != b->value) return false;
	return charListEquals(a->next, b->next);
}

bool charListCompare(CharNode* a, CharNode* b, int digitsA, int digitsB) {
	if (digitsA != digitsB) return false;
	if (!a && !b) return false;
	if (a->value > b->value) return true;
	if (a->value < b->value) return false;
	// equal so far → compare rest
	return charListCompare(a->next, b->next, digitsA, digitsB);
}

char goToTail(CharNode* tail) {
	if (tail->next == nullptr) return tail->value;
	return goToTail(tail->next);
}

void appendCharListRecursive(CharNode*& head, CharNode* toAppend) {
	if (!head) {
		head = toAppend;
		return;
	}
	if (!head->next) {
		head->next = toAppend;
		return;
	}
	appendCharListRecursive(head->next, toAppend);
}

CharNode* getSecondToLast(CharNode* node) {
	if (!node || !node->next || !node->next->next) return node;
	return getSecondToLast(node->next);
}

//CharNode* bigIntSub(CharNode* a, CharNode* b) {
//	int borrow = 0;
//	CharNode* head = nullptr;
//	CharNode* tail = nullptr;
//	while (a || b) {
//		int aVal = (a ? a->value - '0' : 0);
//		int bVal = (b ? b->value - '0' : 0);
//		int diff = aVal - bVal - borrow;
//		if (diff < 0) {
//			diff += 10;
//			borrow = 1;
//		}
//		else {
//			borrow = 0;
//		}
//		CharNode* newNode = createCharNode('0' + diff);
//		if (!head) {
//			head = newNode; tail = newNode;
//		}
//		else {
//			tail->next = newNode;
//			tail = newNode;
//		}
//		if (a) a = a->next;
//		if (b) b = b->next;
//	}
//	return head;
//}


// Adds two big integers
CharNode* bigIntAdd(CharNode* a, CharNode* b) {
	int carry = 0;
	CharNode* result = nullptr;
	CharNode* tail = nullptr;


	while (a || b || carry) {
		int sum = carry;

		if (a) {
			sum += a->value - '0';
			a = a->next;
		}

		if (b) {
			sum += b->value - '0';
			b = b->next;
		}

		carry = sum / 10;
		int digit = sum % 10;

		CharNode* newNode = createCharNode('0' + digit);

		// Start list or add to the end of it
		if (!result) {
			result = newNode;   // first digit
		}
		else {
			tail->next = newNode; // link to previous
		}

		tail = newNode; // update tail
	}

	return result;
}

//CharNode* bigIntAddNeg(CharNode* a, CharNode* b) {
//	removeTrailingMinus(a);
//	removeTrailingMinus(b);
//
//	CharNode* result = bigIntAdd(a, b);
//
//	CharNode* tail = getTail(result);
//	if (tail) {
//		tail->next = createCharNode('-');
//	}
//	else {
//		return createCharNode('-'); // Handle case where result is nullptr?
//	}
//
//	return result;
//}

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
	case '-': {
		if (!stackTop) break;

		CharNode* list = stackTop->list;

		if (!list) {
			stackTop->list = createCharNode('-');
			break;
		}

		if (!list->next && list->value == '-') {
			delete list;
			stackTop->list = nullptr;
			break;
		}
		
		CharNode* secondLast = getSecondToLast(list);
		if (secondLast->next && secondLast->next->value == '-') {
			delete secondLast->next;
			secondLast->next = nullptr;
		}
		else {
			CharNode* tail = getTail(stackTop->list); 
			tail->next = createCharNode('-');
		}

		break;
	}
	case ',': {
		pop(stackTop);
		break;
	}
	// Push copy of stack element at index c
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
		appendCharListRecursive(stackTop->list, A);
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

			long long int digitsA = countDigits(A);
			long long int digitsB = countDigits(B);

			bool tooBig = (digitsA > 18 || digitsB > 18);

			bool equal = false;
			if (!tooBig) {
				long long int aVal = charListToInt(A);
				long long int bVal = charListToInt(B);
				equal = (aVal == bVal);
			}
			else {
				// Use structural check
				equal = charListEquals(A, B);
			}


			CharNode* result = createCharNode(equal ? '1' : '0');
			push(stackTop, result);
			deleteCharList(A);
			deleteCharList(B);
		}
		break;
	}
	case '<': {
		if (stackTop && stackTop->next) {
			CharNode* A = pop(stackTop); // top
			CharNode* B = pop(stackTop); // below top

			int digitsA = countDigits(A);
			int digitsB = countDigits(B);

			bool tooBig = (digitsA > 18 || digitsB > 18);

			bool isBLessThanA = false;
			if (!tooBig) {
				int aVal = charListToInt(A);
				int bVal = charListToInt(B);
				isBLessThanA = (bVal < aVal);  // Correct comparison
			}
			else {
				isBLessThanA = charListCompare(A, B, digitsA, digitsB);

			}

			CharNode* result = createCharNode(isBLessThanA ? '1' : '0');
			push(stackTop, result);
			deleteCharList(A);
			deleteCharList(B);
		}
		break;
	}
	// Jump if value is not zero (any kind of non-zero)
	case '?': {
		if (stackTop) {
			CharNode* target = pop(stackTop);
			CharNode* W = pop(stackTop);

			int targetNum = charListToInt(target);
			int intW = charListToInt(W);

			bool jump = false;

			if (W != nullptr) {
				if (W->value != '0' || W->next != nullptr || intW != 0) {
					jump = true;
				}
			}

			deleteCharList(target);
			deleteCharList(W);

			if (jump) {
				interpret(targetNum, stackTop);
				return;
			}
		}
		break;
	}
	case '+': {
		CharNode* A = pop(stackTop);
		CharNode* B = pop(stackTop);

		int digitsA = countDigits(A);
		int digitsB = countDigits(B);

		bool aIsNeg = false, bIsNeg = false;

		if (goToTail(A) == '-') aIsNeg = true;
		if (goToTail(B) == '-') bIsNeg = true;

		bool tooBig = (digitsA > 18 || digitsB > 18);

		CharNode* result = nullptr;

		if (!tooBig) {
			int a = charListToInt(A);
			int b = charListToInt(B);
			result = intToCharList(a + b);
		}
		else {
			if (!aIsNeg && !bIsNeg) {
				result = bigIntAdd(A, B);
			}
			/*else if (aIsNeg && bIsNeg) {
				result = bigIntAddNeg(A, B);
			}
			else if (!aIsNeg && bIsNeg) {
				removeTrailingMinus(B);
				bool isA_LessThan_B = charListCompare(A, B, digitsA, digitsB);
				if (isA_LessThan_B) {
					result = bigIntSub(A, B); 
				}
				else {
					result = bigIntSub(B, A);
					CharNode* tail = getTail(result);
					tail->next = createCharNode('-');
				}
			}
			else if (aIsNeg && !bIsNeg) {
				removeTrailingMinus(A);
				bool isB_LessThan_A = charListCompare(B, A, digitsB, digitsA);
				if (isB_LessThan_A) {
					result = bigIntSub(A, B); 
				}
				else {
					result = bigIntSub(B, A); 
					CharNode* tail = getTail(result);
					tail->next = createCharNode('-');
				}
			}*/
		}
		push(stackTop, result);
		deleteCharList(A);
		deleteCharList(B);
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
	if (!head) return;
	deleteCharList(head->list);
	deleteStackNode(head->next);
	delete head;
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

