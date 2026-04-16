
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// --- Product ---
struct Product {
    string name;
    int quantity;
    double price;
    int freeItems = 0; // безкоштовні товари від акції

    Product(string n, int q, double p) {
        name = n;
        quantity = q;
        price = p;
    }
};

// --- Order ---
class Order {
private:
    vector<Product> products;
    map<string, double> priceList;

    string dateTime;
    string address;
    string paymentMethod;
    bool isPaid = false;
    bool isCheckedOut = false;

    double discount = 0.0;
    bool hasLoyaltyCard = false;

    // --- Застосувати акції з картою покупця ---
    void applyLoyaltyDeals() {
        bool hasMilk = false;
        bool hasCoffee = false;
        bool hasPizza = false;
        bool hasChicken = false;

        for (auto& p : products) {
            if (p.name == "milk" && p.quantity >= 2) hasMilk = true;
            if (p.name == "coffee" && p.quantity >= 1) hasCoffee = true;
            if (p.name == "pizza" && p.quantity >= 1) hasPizza = true;
            if (p.name == "chicken" && p.quantity >= 2) hasChicken = true;
        }

        for (auto& p : products) {
            // banana: 2+1
            cout << "=============================\n";
            if (p.name == "banana") {
                int free = p.quantity / 2;
                if (free > 0) {
                    p.freeItems = free;
                    cout << "[DEAL] banana: " << free << " free!\n";
                }
            }
            // apple: 3+1
            else if (p.name == "apple") {
                int free = p.quantity / 3;
                if (free > 0) {
                    p.freeItems = free;
                    cout << "[DEAL] apple: " << free << " free!\n";
                }
            }
            // yogurt: -15% якщо є milk >= 2
            else if (p.name == "yogurt" && hasMilk) {
                p.price *= 0.85;
                cout << "[DEAL] yogurt: -15% (bought with milk)\n";
            }
            // cookies: -20% якщо є coffee
            else if (p.name == "cookies" && hasCoffee) {
                p.price *= 0.80;
                cout << "[DEAL] cookies: -20% (bought with coffee)\n";
            }
            // rice або pasta: -10% якщо є chicken >= 2
            else if ((p.name == "rice" || p.name == "pasta") && hasChicken) {
                p.price *= 0.90;
                cout << "[DEAL] " << p.name << ": -10% (bought with chicken)\n";
            }
            cout << "=============================\n";

        }

        // pizza: cola у подарунок
        if (hasPizza) {
            bool hasCola = false;
            for (auto& p : products) {
                if (p.name == "cola") {
                    p.freeItems += 1;
                    hasCola = true;
                    cout << "[DEAL] cola: 1 free (bought with pizza)\n";
                    break;
                }
            }
            if (!hasCola) {
                Product freeCola("cola", 0, priceList["cola"]);
                freeCola.freeItems = 1;
                products.push_back(freeCola);
                cout << "[DEAL] cola added for free (bought with pizza)\n";
            }
        }
    }

public:
    Order() {
        loadPrices("products.txt");
    }

    // --- Load prices ---
    void loadPrices(string filename) {
        ifstream fin(filename);
        string name;
        double price;

        if (!fin) {
            cout << "ERROR: products.txt not found!\n";
            return;
        }

        while (fin >> name >> price) {
            priceList[name] = price;
        }

        fin.close();
    }

    // --- Loyalty card ---
    void setLoyaltyCard(bool value) {
        hasLoyaltyCard = value;
        if (value)
            cout << "Loyalty card activated! Deals are available.\n";
        else
            cout << "No loyalty card.\n";
    }

    bool getLoyaltyCard() {
        return hasLoyaltyCard;
    }

    // --- Show deals ---
    void showDeals() {
        cout << "\n=============================\n";
        cout << "      LOYALTY CARD DEALS\n";
        cout << "=============================\n";
        cout << "* banana:      buy 2 - get 1 free\n";
        cout << "* apple:       buy 3 - get 1 free\n";
        cout << "* yogurt:      -15% when bought with 2+ milk\n";
        cout << "* cookies:     -20% when bought with coffee\n";
        cout << "* pizza:       get 1 cola for free\n";
        cout << "* rice/pasta:  -10% when bought with 2+ chicken\n";
        cout << "=============================\n";
        if (!hasLoyaltyCard)
            cout << "(Activate loyalty card to use deals)\n";
    }

    // --- Time ---
    string getCurrentDateTime() {
        time_t now = time(0);
        char buf[26];
        ctime_s(buf, sizeof(buf), &now);
        return string(buf);
    }

    // --- Add product ---
    void addProduct(string name, int quantity) {
        if (priceList.find(name) == priceList.end()) {
            cout << "Product not found!\n";
            return;
        }
        products.push_back(Product(name, quantity, priceList[name]));
    }

    // --- Remove ---
    void removeProduct(string name) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->name == name) {
                products.erase(it);
                return;
            }
        }
        cout << "Product not found\n";
    }

    // --- Change quantity ---
    void changeQuantity(string name, int q) {
        for (auto& p : products) {
            if (p.name == name) {
                p.quantity = q;
                return;
            }
            
			}
        }
    

    // --- Show cart ---
    void showProducts() {
        cout << "\n--- CART ---\n";
        for (auto& p : products) {
            cout << p.name << " x" << p.quantity;
            if (p.freeItems > 0)
                cout << " (+" << p.freeItems << " free)";
            cout << " | price: " << p.price << "\n";
        }
    }

    // --- Total ---
    double getTotal() {
        double sum = 0;
        for (auto& p : products) {
            sum += p.price * p.quantity; 
        }
        return sum * (1 - discount);;
    }

    // --- Promo ---
    void applyPromoCode(string code) {
        if (code == "SALE10") {
            discount = 0.10;
            cout << "Promo applied: -10%\n";
        }
        else if (code == "SALE20") {
            discount = 0.20;
            cout << "Promo applied: -20%\n";
        }
        else {
            cout << "Invalid promo code\n";
        }
    }

    // --- Checkout ---
    void checkout(string addr, int paymentChoice) {
        address = addr;
        dateTime = getCurrentDateTime();

        if (hasLoyaltyCard) {
            cout << "\nApplying loyalty card deals...\n";
            applyLoyaltyDeals();
        }

        if (paymentChoice == 1) {
            paymentMethod = "Card";
            isPaid = true;
            cout << "Payment successful!\n";
        }
        else {
            paymentMethod = "Cash";
            isPaid = false;
            cout << "Pay on delivery.\n";
        }

        isCheckedOut = true;
    }

    // --- Animation ---
    void showProgressAnimated() {
        vector<string> steps = {
            "Order placed",
            "Processing",
            "Preparing",
            "Shipped",
            "Delivered"
        };

        for (int i = 0; i < (int)steps.size(); i++) {
            cout << "[~] " << steps[i] << "\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    // --- Receipt ---
    void printReceipt() {
        if (!isCheckedOut) {
            cout << "Please complete checkout first (option 5)!\n";
            return;
        }

        cout << "\n=============================\n";
        cout << "        ONLINE STORE\n";
        cout << "=============================\n";

        cout << "Date: " << dateTime;
        cout << "Address: " << address << "\n";
        cout << "Payment: " << paymentMethod
            << " | Status: " << (isPaid ? "PAID" : "NOT PAID") << "\n";
        cout << "Loyalty card: " << (hasLoyaltyCard ? "YES" : "NO") << "\n\n";

        for (auto& p : products) {
            int paid = p.quantity - p.freeItems;
            if (paid < 0) paid = 0;
            cout << p.name << " x" << p.quantity;
            if (p.freeItems > 0)
                cout << " (+" << p.freeItems << " free)";
            cout << " = " << p.price * p.quantity << "\n";
        }

        cout << "\n-----------------------------\n";

        if (discount > 0)
            cout << "Discount: -" << discount * 100 << "%\n";

        cout << "TOTAL: " << getTotal() << "\n";
        cout << "-----------------------------\n";
        cout << "\nEstimated delivery: 30-60 min\n";

        showProgressAnimated();

        cout << "\n=============================\n";
    }

    // --- Save ---
    void saveToFile(string filename) {
        ofstream fout(filename, ios::app);

        if (!fout) {
            cout << "ERROR: cannot open file!\n";
            return;
        }

        fout << "Date: " << dateTime;
        fout << "Address: " << address << "\n";
        fout << "Payment: " << paymentMethod
            << " | Status: " << (isPaid ? "PAID" : "NOT PAID") << "\n";
        fout << "Loyalty card: " << (hasLoyaltyCard ? "YES" : "NO") << "\n";

        for (auto& p : products) {
            int paid = p.quantity - p.freeItems;
            if (paid < 0) paid = 0;
            fout << p.name << " x" << p.quantity;
            if (p.freeItems > 0)
                fout << " (+" << p.freeItems << " free)";
            fout << " = " << p.price * p.quantity << "\n";
        }

        if (discount > 0)
            fout << "Discount: -" << discount * 100 << "%\n";

        fout << "TOTAL: " << getTotal() << "\n";
        fout << "----------------------\n";

        fout.close();
    }
};