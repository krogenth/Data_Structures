#include "StackClass.h"

size_t main() {

	Stack stack1, stack2;
	ItemType item;

	//ensure that IsEmpty() functions properly
	if (stack1.IsEmpty())
		std::cout << "Stack1 is empty.\n\n";
	else
		std::cout << "Stack1 is not empty.\n\n";

	//write some random crap to stack1
	for (size_t i = 0; i < 4; i++) {

		item.key = i;
		stack1.Push(item);

	}

	//write some random crap to stack2
	for (size_t i = 0; i < 4; i++) {

		item.key = i * 10;
		stack2.Push(item);

	}

	//double check that IsEmpty() functions properly
	if (stack1.IsEmpty())
		std::cout << "Stack1 is empty.\n\n";
	else
		std::cout << "Stack1 is not empty.\n\n";

	//check our equivalency operator overloads
	if (stack1 == stack2)
		std::cout << "These stacks are equivalent. :)\n\n";
	else if (stack1 != stack2)
		std::cout << "These stacks are not equivalent. >:(\n\n";

	//attempt to push another item onto stack1, this will output "bad exception"
	try {

		stack1.Push(item);

	}
	catch (const std::exception &e) {

		std::cout << e.what() << "\n\n";

	}

	//Begin reading and removing items from both stacks
	while (!stack1.IsEmpty()) {

		//check if there is an item
		if (stack1.Top(item))
			std::cout << "stack1 top:\t" << item.key;
		else
			std::cout << "There was an issue retrieving the top element.\n";

		//check if there is an item
		if (stack2.Top(item))
			std::cout << "\tstack2 top:\t" << item.key << '\n';
		else
			std::cout << "There was an issue retrieving the top element.\n";

		//remove item from both stacks
		stack1.Pop();
		stack2.Pop();

	}

	//check if the stack is empty
		//it should be, otherwise we have some issues with our loop
	if (stack1.IsEmpty()) {

		//add more items to stack1
		for (size_t i = 0; i < 4; i++) {

			item.key = i;
			stack1.Push(item);

		}

	}

	//remove all items from stack1
	stack1.Clear();

	//check that stack1 is now empty
	if(stack1.IsEmpty())
		std::cout << "\nStack1 is empty.\n\n";

	//check if the stack is empty
	if (stack1.IsEmpty()) {

		//add more items to stack1
		for (size_t i = 0; i < 4; i++) {

			item.key = i;
			stack1.Push(item);

		}

	}

	//make stack2 equivalent to stack1
	stack2 = stack1;

	//check that stack2 is equivalent to stack1
	if (stack1 == stack2)
		std::cout << "These stacks are equivalent. :)\n\n";
	else if (stack1 != stack2)
		std::cout << "These stacks are not equivalent. >:(\n\n";

	//attempt to remove 5 items from both stacks
		//5th pass should use both else statements
	for (size_t i = 0; i < 5; i++) {

		if (stack1.Top(item))
			std::cout << "stack1 top:\t" << item.key;
		else
			std::cout << "There was an issue retrieving the top element.\n";

		if (stack2.Top(item))
			std::cout << "\tstack2 top:\t" << item.key << '\n';
		else
			std::cout << "There was an issue retrieving the top element.\n";

		stack1.Pop();
		stack2.Pop();

	}

	std::cout << "Press enter to continue . . .\n";

	endl(std::cout);

	std::cin.get();

}