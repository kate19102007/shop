

#include "Header.h"

int main() {
    Order order;
    int choice;
	cout << "=============================\n";
	cout << "Welcome to the Online Store!\n";
    cout << "=============================\n";
    cout << "\n1. Add product\n";
    cout << "2. Remove product\n";
    cout << "3. Change quantity\n";
    cout << "4. Show cart\n";
    cout << "5. Checkout\n";
    cout << "6. Print receipt\n";
    cout << "7. Save to file\n";
	cout << "8. Show deals\n";
    cout << "0. Exit\n";
	cout << "=============================\n";
    cout << endl;
    cout << "Choice: ";

    do {
     
        
        cin >> choice;

        string name, address, promo;
        int quantity;

        switch (choice) {
        case 1:
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter quantity: ";
            cin >> quantity;
            order.addProduct(name, quantity);
            cout << "Choice: ";
            break;

        case 2:
            cout << "Enter product name: ";
            cin >> name;
            order.removeProduct(name);
            cout << "Choice: ";
            break;

        case 3:
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter new quantity: ";
            cin >> quantity;
            order.changeQuantity(name, quantity);
            
            cout << "Choice: ";
            break;

        case 4:
            order.showProducts();
            cout << "Choice: ";
            break;

        case 5: {
            cout << "Enter address: ";
            cin.ignore();
            getline(cin, address);

            cout << "Enter promo code (or 0 to skip): ";
            cin >> promo;
            if (promo != "0") {
                order.applyPromoCode(promo);
            }

            int paymentChoice;
            cout << "Payment method:\n";
            cout << "1. Card\n";
            cout << "2. Cash\n";
            cout << "Choice: ";
            cin >> paymentChoice;
            cout << "Do you have a loyalty card? "<<endl;
			cout << "1. Yes\n";
			cout << "2. No\n";
            int cardChoice;
            cin >> cardChoice;
            order.setLoyaltyCard(cardChoice == 1);

            order.checkout(address, paymentChoice);

			cout << "Choice: ";
            break;
        }

        case 6:
            order.printReceipt();
			cout << "Choice: ";
            break;

        case 7:
            order.saveToFile("orders.txt");
			cout << "Choice: ";
            break;
		case 8:
			cout << "=============================\n";
            cout << "\n--- CURRENT DEALS ---\n";
            cout << "banana: Buy 2 get 1 free\n";
            cout << "apple: Buy 3 get 1 free\n";
            cout << "yogurt: -15% if you buy milk >= 2\n";
            cout << "cookies: -20% if you buy coffee\n";
            cout << "rice or pasta: -10% if you buy chicken >= 2\n";
            cout << "pizza: Get a free cola\n";
            cout << "=============================\n";
            cout << "Choice: ";
			break;
		case 0:
			cout << "Thank you for shopping with us!\n";
        }

    } while (choice != 0);

    return 0;
}