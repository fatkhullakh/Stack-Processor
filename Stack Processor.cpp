/*Stack Processor
The Gedanum state has decided to conquer space. In the first stage, it plans to send a number of probes that will search for planets suitable for colonization. The probes must be intelligent and energy-efficient, so a new processor is needed to control them. The commission of Experts Technology Interstellar was commissioned to design it. After many hours of hard work and numerous flashes of genius, the Stack Translator Of Symbols, model AaD5, was created. It still requires a lot of work to start mass production, but in order not to waste time, you were commissioned to write an emulator of this processor. Thanks to it, the creation of probe control systems can begin much faster.

The processor has a program memory, an instruction pointer, and a stack. Program memory stores the program. A program is a sequence of instructions, and each instruction is one character. The instruction pointer stores the number of the instruction that will be executed next, and increments by one after each execution (for most instructions). The processor terminates when the instruction pointer points beyond the last instruction in the program. The first instruction is numbered 0.

The stack stores data for calculations. The stack elements are lists containing zero or more characters (digits, letters, and other symbols). If the list contains only digits and at most one '-' (minus) character at the end, we say that such a list contains a number. The youngest digit of the number is stored in the first position of the list, so the number -1234 is stored as a list 4321-.

It can be assumed that all programs will be correct, i.e. there will be no situations not foreseen in the instruction list.

The list of processor instructions is as follows:

'	apostrophe	put an empty list on the stack
:	colon	put a copy of the list on the top of the stack
;	semicolon	swap the places of the list on the top of the stack and the list directly below it
@	at	pop the number A off the stack, then put a copy of the list on the A-th position on the stack (0 is the top of the stack, 1 is the list directly below it etc.); program '0@ is equivalent to the instruction :
.	dot	read a character from standard input and append it to the beginning of the list on the top of the stack
>	greater than	write the first character from the list on the top of the stack to standard output and pop the list off the top of the stack
!	exclamation mark	logical negation: if the top of the stack is an empty list or a list containing a single character '0', replace it with a list containing the character '1'; otherwise replace the list on the top of the stack with a list containing the character '0'
<	less than	pop number A off the stack, pop number B off the stack, if B < A put number 1 on the stack, otherwise put number 0 on the stack
=	equal	pop number A off the stack, pop number B off the stack, if B = A put number 1 on the stack, otherwise put number 0 on the stack
~	tilde	put a number equal to the number of this instruction (the value of the instruction pointer) on the stack
?	question mark	conditional jump: pop number T off the stack pop list W off the stack if W is not empty and does not contain only the character '0' put number T into the instruction pointer and do not increment the instruction pointer;
-	minus	negation: if the last character of the top list is '-' (minus) remove it from the list; otherwise append '-' to the end of the list at the top of the stack
^	caret	absolute value: if the last character of the top list is '-' (minus) remove it from the list
$	dollar	split: detach the first character from the top list and push it onto the stack
#	hash	pop list A off the stack; append A to the end of the list at the top of the stack
+	plus	pop number A off the stack; pop number B off the stack; put number A + B on the stack
&	ampersand	print the contents of the stack to the standard output in the format:
n: list in the nth position on the stack
...
1: list in the second position on the stack
0: list on the top of the stack
the list should be presented as a sequence of consecutive characters from the list (starting with the first)
]		pop number A off the stack; put the character with the ASCII number A on the stack
[		pop list A off the stack; put the number equal to the ASCII number of the first character from list A on the stack
remaining characters	append this character to the top of the list at the top of the stack
Input
The first line of input contains the program to be executed. The second line will contain the characters that will be fed to the program's standard input. Neither the program nor the program's input will contain whitespace. The number of instructions will not exceed 20,000. The number of characters fed to the standard input will not exceed 20,000.
Output
The output should be everything that the processor would write to the standard output.
Rules and scoring
The program should not use STL (except for input and output handling) or arrays (the array can only be used to store the program and input data). Except for reading input, the for/while/do...while loop can be used at most once (recursion should be used).

The tests are divided into groups, each subsequent group extends the preceding group (you cannot include group 6 without including groups 1, 2, 3, 4 and 5).

Note: the tests are constructed in such a way that with reasonable parameters, it is enough for the stack function. If stack overflow occurs under Visual Studio, it does not mean that it will be the same on STOS (here the stack size is set to 10MB). The available stack size can be set in Visual Studio in the project options -> Linker -> System -> Stack Reserve Size (the default is 1MB).

Tests
1-3 (12.5%)
' , : ; @ & remaining characters instructions, only numbers in the int-a range will be stored on the stack


4-6 (12.5%)
' , : ; @ & remaining characters instructions

7-9 (12.5%)
additionally . > - ^ instructions

10-12 (12.5%)
additionally [ ] $ # instructions

13-16 (25%)
additionally < = ! ~ ? instructions

17-19 (25%)
additionally + instructions
Example
Input:
'123'-456&+&


Output:
1: 321
0: 654-
0: 333-

Input:
'...&$&
123

Output:
0: 321
1: 21
0: 3*/
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