/* This program will allow users to set up a web account to make purchases.Users will firstly input a username and password.
* Once logged in users will be allowed to add funds, add items to cart, purchase, refund, and thumbs up or down specific products. This program
* will have preset products to function properly on a test basis.
*/ 


#include <iostream>
#include <string>



class Products { // Format of any product sold by the store
private:
	std::string itemName;
	float itemPrice;
	int itemStock;

public:
	Products() {
		this->itemName = "";
		this->itemPrice = 0;
		this->itemStock = 0;
	}
	Products(std::string name, float price, int stock) {
		this->itemName = name;
		this->itemPrice = price;
		this->itemStock = stock;
	}

	std::string getItemName() const {
		return itemName;
	}

	float getItemPrice() const {
		return itemPrice;
	}

	
	int getItemStock() const {
		return itemStock;
	}

	void setItemStock(int stock) {
		this->itemStock = stock;
	}

};
bool browsing;
std::string prodName;
std::string prodTarget;
const int maxWishListCapacity = 100;
const int maxCartCapacity = 50;
Products wishlist[maxWishListCapacity];
Products cart[maxCartCapacity];

Products productArray[] = { // Purchaseable Items
		Products("4K 65\"\ Sony TV", 1000.99, 100),
		Products("4K 45\"\ Sony TV", 500.99, 150),
		Products("Pen", 1.39, 2000),
		Products("Playstation 5", 659.99, 40)

};


void AddWishlist(Products productArray[], const std::string prodName, int arraySize) {
	bool isProduct = false;
	for (int i = 0; i < maxWishListCapacity; i++) {
		if (wishlist[i].getItemName() == "") { // Check if the current index is empty
			for (int j = 0; j < arraySize / sizeof(productArray[0]); j++) { // Divide total size of array bit size of a single element to get the # of elements in the array. sizeof operator gives you bit size

				if (prodName == productArray[j].getItemName()) { // Look for the product matching the user's inputted name
					isProduct = true;
					wishlist[i] = productArray[j]; // Add the product to the users wishlist
				}
			}

			break;
		}

	}
	if (!isProduct) {
		std::cout << "\n---| " << prodName << " |---is not sold at this store...\n\n";
		return;
	}
	else {
		std::cout << "\n---| " << prodName << " |--- was added to your wishlist...\n\n";
	}
}

void AddToCart(Products productArray[], const std::string prodName, int arraySize) {
	bool isProduct = false;
	for (int i = 0; i < maxCartCapacity; i++) {
		if (cart[i].getItemName() == "") { // Check if the current index is empty
			for (int j = 0; j < arraySize / sizeof(productArray[0]); j++) { // Divide total size of array bit size of a single element to get the # of elements in the array. sizeof operator gives you bit size

				if (prodName == productArray[j].getItemName()) { // Look for the product matching the user's inputted name
					isProduct = true;
					productArray[j].setItemStock(productArray[j].getItemStock() - 1); // Reduce stock when adding item to cart
					
					cart[i] = productArray[j]; // Add the product to the users cart
				}
			}

			break;
		}

	}
	if (!isProduct) {
		std::cout << "\n---| " << prodName << " |---is not sold at this store...\n\n";
		return;
	}
	else {
		std::cout << "\n---| " << prodName << " |--- was added to your wishlist...\n\n";
	}
}
bool Quit() {
	char currentMenu;
	std::cout << "Are you sure you would like to return to the home screen?[Y/N]: ";
	std::cin >> currentMenu;

	if (currentMenu == 'Y' || currentMenu == 'y') {
		browsing = false;
		return true;
	}
	else if (currentMenu != 'N' && currentMenu != 'n') {
		std::cout << "Please enter 'Y' or 'N'...\n";
		Quit();
		
	}
	
	else {
		return false;
	}
	
}
void CheckWishlist(Products wishlist[], int arraySize) {
	std::cout << "\n----- Items in wishlist -----\n";
	for (int i = 0; i < arraySize / sizeof(wishlist[0]); i++) {
		if (wishlist[i].getItemName() != "") {
			std::cout << wishlist[i].getItemName() << " ---- $" << wishlist[i].getItemPrice() << "\n";
		}
		else {
			break;
		}
	}
	std::cout << "-----------------------------\n\n";
	return;
}

void CheckCart(Products cart[], int arraySize) {
	std::cout << "\n----- Items in cart -----\n";
	float totalCost = 0;
	for (int i = 0; i < arraySize / sizeof(cart[0]); i++) {
		if (cart[i].getItemName() != "") {
			std::cout << cart[i].getItemName() << " ---- $" << cart[i].getItemPrice() << "\n";
		}
		else {
			break;
		}
		totalCost += cart[i].getItemPrice();
		
	}
	std::cout << "Total cost: $" << totalCost << "\n";
	std::cout << "-------------------------\n\n";
	return;
}

void Browse(bool browsing) {
	

	while (browsing == true) {
		

		for (int i = 0; i < sizeof(productArray) / sizeof(productArray[0]); i++) { // Divide total size of array bit size of a single element to get the # of elements in the array. sizeof operator gives you bit size

			std::cout << i + 1 << ". " << productArray[i].getItemName() << " ---- $" << productArray[i].getItemPrice() << " ---- Quantity: " << productArray[i].getItemStock() << "\n";

		}
		
		std::cout << "Enter the name of the product you would like to buy: ";

		std::cin.ignore(); // Used to clear input buffer

		std::getline(std::cin, prodName); // Get user input for desired product

		if (prodName == "quit") {
			if (Quit() == true) {
				std::cout << "QUITTING...\n";
				return;
			}
			else{
				//Browse(browsing);
				continue;
			}
			
		}
		
		
		
		std::cout << "Would you like to add this to your cart or your wishlist?: ";

		std::cin >> prodTarget;

		
		if (prodTarget == "quit") {
			if (Quit() == true) {
				std::cout << "QUITTING...\n";
				return;
				
			}
			else {
				//Browse(browsing);
				continue;
			}
		}

		if (prodTarget == "wishlist") {
			AddWishlist(productArray, prodName, sizeof(productArray));
		}

		else if (prodTarget == "cart") {
			AddToCart(productArray, prodName, sizeof(productArray));
		}

		else {
			std::cout << "Invalid Entry...\n";
			continue;
		}


	}

	return;
}




int main()
{
	bool programRunning = true;
	while (programRunning) {
		std::string userActivity;

		std::cout << "1. Browse store\n2. Cart\n3. Wishlist\n4. Exit\n[Case Sensitive]\n";

		std::cout << "What would you like to do?: ";

		//std::getline(std::cin, userActivity);
		std::cin >> userActivity;

		if (userActivity == "Browse" || userActivity == "store") {

			browsing = true;
			Browse(browsing);
		}

		else if (userActivity == "Wishlist") {
			CheckWishlist(wishlist, sizeof(wishlist));
		}

		else if (userActivity == "Cart") {
			CheckCart(cart, sizeof(cart));
		}
	}
	
	return 0;
}

	











// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
