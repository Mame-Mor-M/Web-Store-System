/* This program will allow users to set up a web account to make purchases.Users will firstly input a username and password.
* Once logged in users will be allowed to add funds, add items to cart, purchase, refund, and thumbs up or down specific products. This program
* will have preset products to function properly on a test basis.
*/ 


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Product {
private:
    std::string name;
    float price;
    int stock;

public:
    Product(std::string name, float price, int stock) : name(name), price(price), stock(stock) {}
    
    std::string getName() const { return name; }
    float getPrice() const { return price; }
    int getStock() const { return stock; }
    void setStock(int newStock) { stock = newStock; }
};

class Store {
private:
    std::vector<Product> products;
    std::vector<Product> wishlist;
    std::vector<Product> cart;

public:
    Store() {
        products = {
            Product("4K 65\" Sony TV", 1000.99, 100),
            Product("4K 45\" Sony TV", 500.99, 150),
            Product("Pen", 1.39, 2000),
            Product("Playstation 5", 659.99, 40)
        };
    }

    void displayProducts() {
        std::cout << "\nAvailable Products:\n";
        for (size_t i = 0; i < products.size(); i++) {
            std::cout << i + 1 << ". " << products[i].getName() << " - $" << products[i].getPrice() << " (Stock: " << products[i].getStock() << ")\n";
        }
    }

    void addToWishlist(const std::string& productName) {
        for (const auto& product : products) {
            if (product.getName() == productName) {
                wishlist.push_back(product);
                std::cout << "Added to wishlist: " << productName << "\n";
                return;
            }
        }
        std::cout << "Product not found.\n";
    }

    void addToCart(const std::string& productName) {
        for (auto& product : products) {
            if (product.getName() == productName && product.getStock() > 0) {
                product.setStock(product.getStock() - 1);
                cart.push_back(product);
                std::cout << "Added to cart: " << productName << "\n";
                return;
            }
        }
        std::cout << "Product not available or out of stock.\n";
    }

    void showWishlist() {
        std::cout << "\nWishlist:\n";
        for (const auto& item : wishlist) {
            std::cout << "- " << item.getName() << " ($" << item.getPrice() << ")\n";
        }
    }

    void showCart() {
        std::cout << "\nShopping Cart:\n";
        float total = 0;
        for (const auto& item : cart) {
            std::cout << "- " << item.getName() << " ($" << item.getPrice() << ")\n";
            total += item.getPrice();
        }
        std::cout << "Total: $" << total << "\n";
    }
};

int main() {
    Store store;
    std::string choice;

    while (true) {
        std::cout << "\n1. Browse Store\n2. View Wishlist\n3. View Cart\n4. Exit\nChoice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == "1") {
            store.displayProducts();
            std::cout << "Enter product name to add (or 'back' to return): ";
            std::string productName;
            std::getline(std::cin, productName);
            if (productName == "back") continue;
            
            std::cout << "Add to (wishlist/cart): ";
            std::string target;
            std::getline(std::cin, target);
            
            if (target == "wishlist") {
                store.addToWishlist(productName);
            } else if (target == "cart") {
                store.addToCart(productName);
            } else {
                std::cout << "Invalid option.\n";
            }
        }
        else if (choice == "2") {
            store.showWishlist();
        }
        else if (choice == "3") {
            store.showCart();
        }
        else if (choice == "4") {
            std::cout << "Exiting program.\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
