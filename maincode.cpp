
/*
    ONLINE SHOPPING MANAGEMENT SYSTEM
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <limits>

using namespace std;

// ===================== ASCII COLOR UI =====================
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

int LINE_WIDTH = 70;

// ===================== UI FUNCTIONS =====================

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printLine()
{
    cout << CYAN << string(LINE_WIDTH, '=') << RESET << '\n';
}

void printHeader(string title)
{
    printLine();

    int space = (LINE_WIDTH - (int)title.size()) / 2;
    if (space < 0) space = 0;

    cout << CYAN;
    for (int i = 0; i < space; i++)
        cout << ' ';

    cout << title << RESET << '\n';

    printLine();
}

void successMsg(string msg)
{
    cout << GREEN << "[SUCCESS] " << msg << RESET << '\n';
}

void errorMsg(string msg)
{
    cout << RED << "[ERROR] " << msg << RESET << '\n';
}

void warningMsg(string msg)
{
    cout << YELLOW << "[WARNING] " << msg << RESET << '\n';
}

void infoMsg(string msg)
{
    cout << BLUE << "[INFO] " << msg << RESET << '\n';
}

void pauseScreen()
{
    cout << YELLOW << "\nPress ENTER to continue..." << RESET;
    string dummy;
    getline(cin, dummy);
}

string toLowerStr(string s)
{
    for (size_t i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    ostringstream oss;
    if (ltm)
    {
        oss << setfill('0') << setw(2) << ltm->tm_mday << "-"
            << setfill('0') << setw(2) << (1 + ltm->tm_mon) << "-"
            << (1900 + ltm->tm_year);
    }
    else
    {
        oss << "01-01-2026";
    }
    return oss.str();
}

int readInt(string prompt)
{
    int val;
    while (true)
    {
        cout << YELLOW << prompt << RESET;
        if (cin >> val)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        errorMsg("Invalid integer input! Try again.");
    }
}

double readDouble(string prompt)
{
    double val;
    while (true)
    {
        cout << YELLOW << prompt << RESET;
        if (cin >> val)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        errorMsg("Invalid numeric input! Try again.");
    }
}

string readLineTrim(string prompt)
{
    cout << YELLOW << prompt << RESET;
    string input;
    getline(cin, input);
    return input;
}

// ===================== MENUS & BANNERS =====================

void shopBanner()
{
    cout << GREEN;
    cout << R"(
                     ____  _   _  ___  ____
                    / ___|| | | |/ _ \|  _ \
                    \___ \| |_| | | | | |_) |
                     ___) |  _  | |_| |  __/
                    |____/|_| |_|\___/|_|
)";
    cout << RESET;
}

void mainMenuUI()
{
    shopBanner();
    printHeader("ONLINE SHOPPING SYSTEM");

    cout << GREEN;
    cout << " [1] Shop / Browse Products\n";
    cout << " [2] Customer Portal\n";
    cout << " [3] Admin Portal\n";
    cout << " [0] Exit\n";
    cout << RESET;

    printLine();
}

void customerMenuUI()
{
    printHeader("CUSTOMER PORTAL");

    cout << GREEN
         << " [1] Browse Products\n"
         << " [2] Search Products\n"
         << " [3] View Cart\n"
         << " [4] Add To Cart\n"
         << " [5] Remove From Cart\n"
         << " [6] Checkout\n"
         << " [7] My Orders\n"
         << " [0] Logout\n"
         << RESET;

    printLine();
}

void adminMenuUI()
{
    printHeader("ADMIN DASHBOARD");

    cout << MAGENTA
         << " [1] Add Product\n"
         << " [2] Delete Product\n"
         << " [3] Browse Products\n"
         << " [4] Update Stock\n"
         << " [5] View All Orders\n"
         << " [6] Update Order Status\n"
         << " [0] Logout\n"
         << RESET;

    printLine();
}

void printTableHeader()
{
    cout << CYAN
         << left
         << setw(8)  << "ID"
         << setw(25) << "Product"
         << setw(18) << "Category"
         << setw(12) << "Price"
         << setw(8)  << "Stock"
         << RESET << '\n';

    printLine();
}

void invoiceHeader()
{
    cout << GREEN;
    cout << "\n";
    printLine();
    cout << "                 INVOICE RECEIPT\n";
    printLine();
    cout << RESET;
}

// ===================== CLASSES =====================

class User
{
protected:
    int id;
    string name;
    string username;
    string password;

public:
    User(int id_ = 0, string name_ = "", string username_ = "", string password_ = "")
    {
        id = id_;
        name = name_;
        username = username_;
        password = password_;
    }

    void displayInfo()
    {
        cout << WHITE
             << "ID       : " << id << "\n"
             << "Name     : " << name << "\n"
             << "Username : " << username << "\n"
             << RESET;
    }

    int getId() { return id; }
    string getName() { return name; }
    string getUsername() { return username; }
    string getPassword() { return password; }
    bool checkPassword(string p) { return password == p; }
};

class Customer : public User
{
private:
    string address;

public:
    Customer() : User() { address = "N/A"; }
    Customer(int id_, string name_, string username_, string password_, string address_ = "N/A")
        : User(id_, name_, username_, password_)
    {
        address = address_;
    }

    string getAddress() { return address; }

    void displayInfo()
    {
        infoMsg("CUSTOMER PROFILE");
        User::displayInfo();
        cout << WHITE << "Address  : " << address << RESET << "\n";
    }
};

class Admin : public User
{
public:
    Admin() : User() {}
    Admin(int id_, string name_, string username_, string password_)
        : User(id_, name_, username_, password_) {}

    void displayInfo()
    {
        infoMsg("ADMIN PROFILE");
        User::displayInfo();
    }
};

class Product
{
private:
    int productId;
    string name;
    string category;
    double price;
    int stock;

public:
    Product()
    {
        productId = 0;
        name = "";
        category = "";
        price = 0;
        stock = 0;
    }

    Product(int id_, string name_, string category_, double price_, int stock_)
    {
        productId = id_;
        name = name_;
        category = category_;
        price = price_;
        stock = stock_;
    }

    int getId() { return productId; }
    string getName() { return name; }
    string getCategory() { return category; }
    double getPrice() { return price; }
    int getStock() { return stock; }

    void setStock(int s) { stock = s; }

    void reduceStock(int qty)
    {
        if (qty <= stock) stock -= qty;
    }

    void displayRow()
    {
        string displayName = name;
        if (displayName.length() > 24) displayName = displayName.substr(0, 21) + "...";

        cout << WHITE
             << left
             << setw(8)  << productId
             << setw(25) << displayName
             << setw(18) << category
             << setw(12) << fixed << setprecision(2) << price
             << setw(8)  << stock
             << RESET
             << '\n';
    }
};

struct CartItem
{
    int productId;
    int quantity;
    CartItem(int pid = 0, int qty = 0)
    {
        productId = pid;
        quantity = qty;
    }
};

class Order
{
private:
    int orderId;
    int customerId;
    vector<CartItem> items;
    double totalAmount;
    string orderDate;
    string status;

public:
    Order()
    {
        orderId = 0;
        customerId = 0;
        totalAmount = 0;
        status = "Pending";
    }

    Order(int orderId_, int customerId_, vector<CartItem> items_, double totalAmount_, string orderDate_, string status_ = "Pending")
    {
        orderId = orderId_;
        customerId = customerId_;
        items = items_;
        totalAmount = totalAmount_;
        orderDate = orderDate_;
        status = status_;
    }

    int getOrderId() { return orderId; }
    int getCustomerId() { return customerId; }
    vector<CartItem> getItems() { return items; }
    double getTotalAmount() { return totalAmount; }
    string getDate() { return orderDate; }
    string getStatus() { return status; }
    void setStatus(string s) { status = s; }
};

// ===================== SHOP MANAGER =====================
class ShopManager
{
private:
    vector<Product> products;
    vector<Customer> customers;
    vector<Admin> admins;
    vector<Order> orders;

    vector<CartItem> currentCart;
    int loggedInCustomerId;

    int nextProductId;
    int nextCustomerId;
    int nextOrderId;

    int findProductIndex(int id)
    {
        for (size_t i = 0; i < products.size(); i++)
        {
            if (products[i].getId() == id) return i;
        }
        return -1;
    }

    int findCustomerIndex(string uname)
    {
        for (size_t i = 0; i < customers.size(); i++)
        {
            if (customers[i].getUsername() == uname) return i;
        }
        return -1;
    }

public:
    ShopManager()
    {
        loggedInCustomerId = -1;
        nextProductId = 101;
        nextCustomerId = 1;
        nextOrderId = 1001;
    }

    // ============ FILE I/O ============
    void loadProducts()
    {
        ifstream file("products.txt");
        if (!file.is_open()) return;
        string line;
        while (getline(file, line))
        {
            if (line.empty()) continue;
            stringstream ss(line);
            string idStr, name, category, priceStr, stockStr;
            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, category, '|');
            getline(ss, priceStr, '|');
            getline(ss, stockStr, '|');

            int id = stoi(idStr);
            double price = stod(priceStr);
            int stock = stoi(stockStr);

            products.push_back(Product(id, name, category, price, stock));
            if (id >= nextProductId) nextProductId = id + 1;
        }
        file.close();
    }

    void saveProducts()
    {
        ofstream file("products.txt");
        for (size_t i = 0; i < products.size(); i++)
        {
            file << products[i].getId() << "|" << products[i].getName() << "|"
                 << products[i].getCategory() << "|" << products[i].getPrice() << "|"
                 << products[i].getStock() << "\n";
        }
        file.close();
    }

    void loadCustomers()
    {
        ifstream file("customers.txt");
        if (!file.is_open()) return;
        string line;
        while (getline(file, line))
        {
            if (line.empty()) continue;
            stringstream ss(line);
            string idStr, name, username, password, address;
            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, username, '|');
            getline(ss, password, '|');
            getline(ss, address, '|');

            int id = stoi(idStr);
            customers.push_back(Customer(id, name, username, password, address));
            if (id >= nextCustomerId) nextCustomerId = id + 1;
        }
        file.close();
    }

    void saveCustomers()
    {
        ofstream file("customers.txt");
        for (size_t i = 0; i < customers.size(); i++)
        {
            file << customers[i].getId() << "|" << customers[i].getName() << "|"
                 << customers[i].getUsername() << "|" << customers[i].getPassword() << "|"
                 << customers[i].getAddress() << "\n";
        }
        file.close();
    }

    void loadOrders()
    {
        ifstream file("orders.txt");
        if (!file.is_open()) return;
        string line;
        while (getline(file, line))
        {
            if (line.empty()) continue;
            stringstream ss(line);
            string idStr, custStr, date, status, totalStr, itemsStr;
            getline(ss, idStr, '|');
            getline(ss, custStr, '|');
            getline(ss, date, '|');
            getline(ss, status, '|');
            getline(ss, totalStr, '|');
            getline(ss, itemsStr, '|');

            int id = stoi(idStr);
            int custId = stoi(custStr);
            double total = stod(totalStr);

            vector<CartItem> items;
            stringstream itemStream(itemsStr);
            string pair;
            while (getline(itemStream, pair, ','))
            {
                if (pair.empty()) continue;
                size_t colon = pair.find(':');
                if (colon != string::npos)
                {
                    int pid = stoi(pair.substr(0, colon));
                    int qty = stoi(pair.substr(colon + 1));
                    items.push_back(CartItem(pid, qty));
                }
            }
            orders.push_back(Order(id, custId, items, total, date, status));
            if (id >= nextOrderId) nextOrderId = id + 1;
        }
        file.close();
    }

    void saveOrders()
    {
        ofstream file("orders.txt");
        for (size_t i = 0; i < orders.size(); i++)
        {
            file << orders[i].getOrderId() << "|" << orders[i].getCustomerId() << "|"
                 << orders[i].getDate() << "|" << orders[i].getStatus() << "|"
                 << orders[i].getTotalAmount() << "|";

            vector<CartItem> items = orders[i].getItems();
            for (size_t j = 0; j < items.size(); ++j)
            {
                file << items[j].productId << ":" << items[j].quantity;
                if (j + 1 < items.size()) file << ",";
            }
            file << "\n";
        }
        file.close();
    }

    void initializeSampleData()
    {
        if (products.empty())
        {
            products.push_back(Product(101, "Mechanical Keyboard", "Electronics", 3200.00, 15));
            products.push_back(Product(102, "Wireless Mouse", "Electronics", 1200.00, 28));
            products.push_back(Product(103, "Gaming Headset", "Accessories", 2500.00, 7));
            products.push_back(Product(104, "USB-C Hub", "Electronics", 1800.00, 20));
            products.push_back(Product(105, "Cotton T-Shirt", "Fashion", 650.00, 40));
            nextProductId = 106;
        }
        if (customers.empty())
        {
            customers.push_back(Customer(1, "Rahim Uddin", "rahim", "pass123", "Dhaka, BD"));
            nextCustomerId = 2;
        }
        if (admins.empty())
        {
            admins.push_back(Admin(1, "System Admin", "admin", "admin123"));
        }
    }

    void loadData()
    {
        loadProducts();
        loadCustomers();
        loadOrders();
        initializeSampleData();
    }

    void saveData()
    {
        saveProducts();
        saveCustomers();
        saveOrders();
    }

    // ============ PRODUCT FEATURES ============
    void listProducts(vector<Product> list)
    {
        if (list.empty())
        {
            warningMsg("No products available.");
            return;
        }
        printTableHeader();
        for (size_t i = 0; i < list.size(); i++)
        {
            list[i].displayRow();
        }
        printLine();
    }

    void browseProducts()
    {
        clearScreen();
        printHeader("SHOP / BROWSE PRODUCTS");
        listProducts(products);
        pauseScreen();
    }

    void searchProducts()
    {
        clearScreen();
        printHeader("SEARCH PRODUCTS");
        cout << GREEN
             << " [1] By ID\n"
             << " [2] By Name\n"
             << " [3] By Category\n"
             << " [0] Back\n"
             << RESET;
        printLine();

        int choice = readInt("Enter choice: ");

        vector<Product> result;
        if (choice == 1)
        {
            int id = readInt("Enter Product ID: ");
            for (size_t i = 0; i < products.size(); i++)
            {
                if (products[i].getId() == id)
                {
                    result.push_back(products[i]);
                    break;
                }
            }
        }
        else if (choice == 2)
        {
            string name = toLowerStr(readLineTrim("Enter Product Name: "));
            for (size_t i = 0; i < products.size(); i++)
            {
                if (toLowerStr(products[i].getName()).find(name) != string::npos)
                    result.push_back(products[i]);
            }
        }
        else if (choice == 3)
        {
            string cat = toLowerStr(readLineTrim("Enter Category: "));
            for (size_t i = 0; i < products.size(); i++)
            {
                if (toLowerStr(products[i].getCategory()).find(cat) != string::npos)
                    result.push_back(products[i]);
            }
        }
        else return;

        cout << "\n";
        infoMsg("Search Results:");
        listProducts(result);
        pauseScreen();
    }

    // ============ CUSTOMER FEATURES ============
    void registerCustomer()
    {
        clearScreen();
        printHeader("CUSTOMER REGISTRATION");
        string name = readLineTrim("Full Name       : ");
        string username = readLineTrim("Choose Username : ");

        if (findCustomerIndex(username) != -1)
        {
            errorMsg("Username already exists!");
            pauseScreen();
            return;
        }

        string password = readLineTrim("Choose Password : ");
        string address = readLineTrim("Address         : ");

        customers.push_back(Customer(nextCustomerId++, name, username, password, address));
        saveCustomers();
        successMsg("Registration successful!");
        pauseScreen();
    }

    void loginCustomer()
    {
        clearScreen();
        shopBanner();
        printHeader("CUSTOMER LOGIN");
        string username = readLineTrim("Username : ");
        string password = readLineTrim("Password : ");

        int idx = findCustomerIndex(username);
        if (idx == -1 || !customers[idx].checkPassword(password))
        {
            errorMsg("Invalid credentials!");
            pauseScreen();
            return;
        }

        loggedInCustomerId = customers[idx].getId();
        currentCart.clear();
        successMsg("Welcome, " + customers[idx].getName() + "!");
        pauseScreen();
        customerSessionMenu();
    }

    // ============ CART & CHECKOUT ============
    void addToCart()
    {
        clearScreen();
        printHeader("ADD TO CART");
        listProducts(products);

        int id = readInt("Enter Product ID: ");
        int pIndex = findProductIndex(id);
        if (pIndex == -1)
        {
            errorMsg("Product not found!");
            pauseScreen();
            return;
        }

        int qty = readInt("Enter Quantity: ");
        if (qty <= 0)
        {
            errorMsg("Quantity must be positive!");
            pauseScreen();
            return;
        }

        int currentQtyInCart = 0;
        for (size_t i = 0; i < currentCart.size(); i++)
        {
            if (currentCart[i].productId == id)
            {
                currentQtyInCart += currentCart[i].quantity;
            }
        }

        if (qty + currentQtyInCart > products[pIndex].getStock())
        {
            errorMsg("Not enough stock!");
            pauseScreen();
            return;
        }

        bool found = false;
        for (size_t i = 0; i < currentCart.size(); i++)
        {
            if (currentCart[i].productId == id)
            {
                currentCart[i].quantity += qty;
                found = true;
                break;
            }
        }
        if (!found) currentCart.push_back(CartItem(id, qty));
        successMsg("Added to cart!");
        pauseScreen();
    }

    void removeFromCart()
    {
        clearScreen();
        printHeader("REMOVE FROM CART");
        if (currentCart.empty())
        {
            warningMsg("Your cart is empty.");
            pauseScreen();
            return;
        }

        int id = readInt("Enter Product ID to remove: ");
        bool removed = false;
        for (size_t i = 0; i < currentCart.size(); i++)
        {
            if (currentCart[i].productId == id)
            {
                currentCart.erase(currentCart.begin() + i);
                removed = true;
                break;
            }
        }

        if (removed)
        {
            successMsg("Item removed from cart!");
        }
        else
        {
            errorMsg("Item not found in cart!");
        }
        pauseScreen();
    }

    void viewCart()
    {
        clearScreen();
        printHeader("MY CART");
        if (currentCart.empty())
        {
            warningMsg("Your cart is empty.");
            pauseScreen();
            return;
        }

        cout << CYAN << left << setw(28) << "Product" << setw(12) << "Quantity"
             << setw(15) << "Unit Price" << "Total" << RESET << "\n";
        printLine();

        double total = 0;
        for (size_t i = 0; i < currentCart.size(); i++)
        {
            int pIndex = findProductIndex(currentCart[i].productId);

            if (pIndex != -1)
            {
                double lineTotal = products[pIndex].getPrice() * currentCart[i].quantity;
                total += lineTotal;
                string pName = products[pIndex].getName();
                if (pName.length() > 27) pName = pName.substr(0, 24) + "...";

                cout << WHITE << left << setw(28) << pName
                     << setw(12) << currentCart[i].quantity
                     << setw(15) << products[pIndex].getPrice() << lineTotal << RESET << "\n";
            }
        }
        printLine();
        cout << GREEN << "Subtotal: " << total << " BDT" << RESET << "\n";
        pauseScreen();
    }

    void printInvoice(Order ord)
    {
        invoiceHeader();
        cout << WHITE
             << "Order ID   : " << ord.getOrderId() << "\n"
             << "Date       : " << ord.getDate() << "\n"
             << "Status     : " << ord.getStatus() << "\n"
             << RESET;
        printLine();
        cout << CYAN << left << setw(25) << "Product" << setw(10) << "Qty" << "Total (BDT)" << RESET << "\n";
        printLine();

        vector<CartItem> items = ord.getItems();
        for (size_t i = 0; i < items.size(); i++)
        {
            string pName = "Unknown Product";
            double price = 0.0;
            int pIndex = findProductIndex(items[i].productId);
            if (pIndex != -1)
            {
                pName = products[pIndex].getName();
                if (pName.length() > 24) pName = pName.substr(0, 21) + "...";
                price = products[pIndex].getPrice();
            }
            cout << WHITE << left << setw(25) << pName
                 << setw(10) << items[i].quantity
                 << (price * items[i].quantity) << RESET << "\n";
        }
        printLine();
        cout << GREEN << "Grand Total: " << ord.getTotalAmount() << " BDT" << RESET << "\n";
        printLine();
    }

    void checkout()
    {
        clearScreen();
        printHeader("CHECKOUT");
        if (currentCart.empty())
        {
            warningMsg("Cart is empty!");
            pauseScreen();
            return;
        }

        double subtotal = 0;
        for (size_t i = 0; i < currentCart.size(); i++)
        {
            int pIndex = findProductIndex(currentCart[i].productId);
            if (pIndex != -1) subtotal += products[pIndex].getPrice() * currentCart[i].quantity;
        }

        double grandTotal = subtotal + 100.0;
        cout << WHITE
             << "Subtotal       : " << subtotal << " BDT\n"
             << "Delivery Charge: 100.00 BDT\n"
             << "Grand Total    : " << grandTotal << " BDT\n\n"
             << RESET;

        cout << GREEN << " [1] Confirm Order & Pay\n" << RESET
             << RED   << " [0] Cancel\n" << RESET;
        printLine();

        int choice = readInt("Enter choice: ");
        if (choice == 1)
        {
            for (size_t i = 0; i < currentCart.size(); i++)
            {
                int pIndex = findProductIndex(currentCart[i].productId);
                if (pIndex != -1) products[pIndex].reduceStock(currentCart[i].quantity);
            }
            saveProducts();

            Order newOrder(nextOrderId++, loggedInCustomerId, currentCart, grandTotal, getCurrentDate(), "Confirmed");
            orders.push_back(newOrder);
            saveOrders();

            currentCart.clear();
            successMsg("Order placed successfully!");
            printInvoice(newOrder);
        }
        else
        {
            infoMsg("Checkout cancelled.");
        }
        pauseScreen();
    }

    void viewMyOrders()
    {
        clearScreen();
        printHeader("MY ORDERS");
        cout << CYAN << left << setw(12) << "Order ID" << setw(15) << "Date"
             << setw(14) << "Amount" << "Status" << RESET << "\n";
        printLine();

        bool hasOrders = false;
        for (size_t i = 0; i < orders.size(); i++)
        {
            if (orders[i].getCustomerId() == loggedInCustomerId)
            {
                hasOrders = true;
                cout << WHITE << left << setw(12) << orders[i].getOrderId()
                     << setw(15) << orders[i].getDate()
                     << setw(14) << orders[i].getTotalAmount()
                     << orders[i].getStatus() << RESET << "\n";
            }
        }
        if (!hasOrders) warningMsg("No orders found.");
        pauseScreen();
    }

    // ============ ADMIN FEATURES ============
    bool loginAdmin()
    {
        clearScreen();
        shopBanner();
        printHeader("ADMIN LOGIN");
        string username = readLineTrim("Username : ");
        string password = readLineTrim("Password : ");

        for (size_t i = 0; i < admins.size(); i++)
        {
            if (admins[i].getUsername() == username && admins[i].checkPassword(password))
            {
                successMsg("Admin logged in!");
                pauseScreen();
                return true;
            }
        }
        errorMsg("Invalid admin credentials!");
        pauseScreen();
        return false;
    }

    void addProduct()
    {
        clearScreen();
        printHeader("ADD PRODUCT");
        string name = readLineTrim("Product Name : ");
        string cat = readLineTrim("Category     : ");
        double price = readDouble("Price        : ");
        int stock = readInt("Stock        : ");

        if (price < 0 || stock < 0)
        {
            errorMsg("Price and stock cannot be negative!");
            pauseScreen();
            return;
        }

        products.push_back(Product(nextProductId++, name, cat, price, stock));
        saveProducts();
        successMsg("Product added!");
        pauseScreen();
    }

    void deleteProduct()
    {
        clearScreen();
        printHeader("DELETE PRODUCT");
        listProducts(products);

        int id = readInt("Enter Product ID to delete: ");
        bool deleted = false;
        for (size_t i = 0; i < products.size(); i++)
        {
            if (products[i].getId() == id)
            {
                products.erase(products.begin() + i);
                deleted = true;
                break;
            }
        }

        if (deleted)
        {
            saveProducts();
            successMsg("Product deleted!");
        }
        else
        {
            errorMsg("Product not found!");
        }
        pauseScreen();
    }

    void updateStock()
    {
        clearScreen();
        printHeader("UPDATE STOCK");
        listProducts(products);

        int id = readInt("Enter Product ID: ");
        int pIndex = findProductIndex(id);
        if (pIndex == -1)
        {
            errorMsg("Product not found!");
            pauseScreen();
            return;
        }

        int stock = readInt("Enter New Stock: ");
        if (stock < 0)
        {
            errorMsg("Stock cannot be negative!");
            pauseScreen();
            return;
        }

        products[pIndex].setStock(stock);
        saveProducts();
        successMsg("Stock updated!");
        pauseScreen();
    }

    void viewAllOrders()
    {
        clearScreen();
        printHeader("ALL ORDERS");
        cout << CYAN << left << setw(10) << "Order ID" << setw(12) << "Customer ID"
             << setw(15) << "Date" << setw(12) << "Amount" << "Status" << RESET << "\n";
        printLine();

        for (size_t i = 0; i < orders.size(); i++)
        {
            cout << WHITE << left << setw(10) << orders[i].getOrderId()
                 << setw(12) << orders[i].getCustomerId()
                 << setw(15) << orders[i].getDate()
                 << setw(12) << orders[i].getTotalAmount()
                 << orders[i].getStatus() << RESET << "\n";
        }
        pauseScreen();
    }

    void updateOrderStatus()
    {
        clearScreen();
        printHeader("UPDATE ORDER STATUS");
        int id = readInt("Enter Order ID: ");
        int targetIndex = -1;

        for (size_t i = 0; i < orders.size(); i++)
        {
            if (orders[i].getOrderId() == id)
            {
                targetIndex = (int)i;
                break;
            }
        }

        if (targetIndex == -1)
        {
            errorMsg("Order not found!");
            pauseScreen();
            return;
        }

        cout << MAGENTA
             << " [1] Pending\n"
             << " [2] Confirmed\n"
             << " [3] Delivered\n"
             << " [4] Cancelled\n"
             << RESET;
        printLine();

        int choice = readInt("Select Status: ");
        if (choice == 1) orders[targetIndex].setStatus("Pending");
        else if (choice == 2) orders[targetIndex].setStatus("Confirmed");
        else if (choice == 3) orders[targetIndex].setStatus("Delivered");
        else if (choice == 4) orders[targetIndex].setStatus("Cancelled");
        else
        {
            errorMsg("Invalid choice!");
            pauseScreen();
            return;
        }

        saveOrders();
        successMsg("Status updated!");
        pauseScreen();
    }

    // ============ MENUS ============
    void customerSessionMenu()
    {
        int choice;
        do
        {
            clearScreen();
            customerMenuUI();
            choice = readInt("Enter choice: ");

            switch (choice)
            {
                case 1: browseProducts(); break;
                case 2: searchProducts(); break;
                case 3: viewCart(); break;
                case 4: addToCart(); break;
                case 5: removeFromCart(); break;
                case 6: checkout(); break;
                case 7: viewMyOrders(); break;
                case 0: loggedInCustomerId = -1; infoMsg("Logged out."); break;
                default: errorMsg("Invalid choice!"); pauseScreen(); break;
            }
        } while (choice != 0);
    }

    void customerPortalMenu()
    {
        int choice;
        do
        {
            clearScreen();
            printHeader("CUSTOMER ACCESS");
            cout << GREEN
                 << " [1] Register\n"
                 << " [2] Login\n"
                 << " [0] Back\n"
                 << RESET;
            printLine();

            choice = readInt("Enter choice: ");

            switch (choice)
            {
                case 1: registerCustomer(); break;
                case 2: loginCustomer(); break;
                case 0: break;
                default: errorMsg("Invalid choice!"); pauseScreen(); break;
            }
        } while (choice != 0 && loggedInCustomerId == -1);
    }

    void adminPortalMenu()
    {
        if (!loginAdmin()) return;

        int choice;
        do
        {
            clearScreen();
            adminMenuUI();
            choice = readInt("Enter choice: ");

            switch (choice)
            {
                case 1: addProduct(); break;
                case 2: deleteProduct(); break;
                case 3: browseProducts(); break;
                case 4: updateStock(); break;
                case 5: viewAllOrders(); break;
                case 6: updateOrderStatus(); break;
                case 0: infoMsg("Admin logged out."); break;
                default: errorMsg("Invalid choice!"); pauseScreen(); break;
            }
        } while (choice != 0);
    }

    void run()
    {
        int choice;
        do
        {
            clearScreen();
            mainMenuUI();
            choice = readInt("Enter choice: ");

            switch (choice)
            {
                case 1: browseProducts(); break;
                case 2: customerPortalMenu(); break;
                case 3: adminPortalMenu(); break;
                case 0: infoMsg("Exiting application..."); break;
                default: errorMsg("Invalid choice!"); pauseScreen(); break;
            }
        } while (choice != 0);
    }
};

int main()
{
    ShopManager shopManager;
    shopManager.loadData();
    shopManager.run();
    shopManager.saveData();
    return 0;
}
