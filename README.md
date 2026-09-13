# Online Shopping Management System

## Project Description

Online Shopping Management System is a console-based application developed using C++. The project is designed to demonstrate basic online shopping operations such as product browsing, customer registration, cart management, checkout, and order management.

The system has two main types of users: Customer and Admin. Customers can browse and search for products, add products to their cart, place orders, and view their previous orders. Admins can manage products, update stock, and manage customer orders.

## Author

**Name:** Tahasanur Karim
**Email:** [tahasanurkarim@gmail.com](mailto:tahasanurkarim@gmail.com)

## Features

### Customer

* Customer registration
* Customer login
* Browse available products
* Search products by ID
* Search products by name
* Search products by category
* Add products to cart
* Remove products from cart
* View cart
* Check product stock before adding to cart
* Checkout and place orders
* View generated invoice
* View previous orders
* View order status
* Logout

### Admin

* Admin login
* Add new products
* Delete products
* Browse products
* Update product stock
* View all orders
* Update order status

The available order statuses are:

* Pending
* Confirmed
* Delivered
* Cancelled

## Technologies Used

* C++
* Object-Oriented Programming
* STL Vector
* File Handling
* String Processing
* Console-based User Interface

The project uses standard C++ libraries such as `iostream`, `vector`, `string`, `fstream`, `sstream`, `iomanip`, `ctime`, and `limits`.

## OOP Concepts

The project uses several Object-Oriented Programming concepts.

### Classes

The main classes used in the project are:

* `User`
* `Customer`
* `Admin`
* `Product`
* `Order`
* `ShopManager`

### Inheritance

`Customer` and `Admin` inherit from the `User` class.

```text
             User
            /    \
           /      \
     Customer     Admin
```

### Encapsulation

Class data members are kept private or protected and are accessed through member functions.

### Abstraction

The `ShopManager` class handles most of the main operations of the shopping system, including products, customers, carts, and orders.

## Project Files

```text
Online-Shopping-Management-System/
|
|-- maincode.cpp
|-- products.txt
|-- customers.txt
|-- orders.txt
|-- README.md
```

### maincode.cpp

Contains the complete source code of the application.

### products.txt

Stores product information such as product ID, name, category, price, and stock.

Example:

```text
101|Mechanical Keyboard|Electronics|3200|10
102|Wireless Mouse|Electronics|1200|28
103|Gaming Headset|Accessories|2500|5
```

### customers.txt

Stores registered customer information.

The format is:

```text
CustomerID|Name|Username|Password|Address
```

### orders.txt

Stores order information including order ID, customer ID, date, status, total amount, and purchased products.

The format is:

```text
OrderID|CustomerID|Date|Status|Total|ProductID:Quantity
```

## How the System Works

When the program starts, it loads the existing product, customer, and order information from the text files.

The main menu contains three main options:

```text
[1] Shop / Browse Products
[2] Customer Portal
[3] Admin Portal
[0] Exit
```

### Customer Workflow

A customer can first register an account or log in using an existing account.

After logging in, the customer can:

1. Browse products
2. Search for products
3. Add products to the cart
4. View the cart
5. Remove products from the cart
6. Checkout
7. View previous orders

During checkout, the system calculates the subtotal and adds a fixed delivery charge of 100 BDT.

```text
Subtotal = Product Price × Quantity

Grand Total = Subtotal + 100 BDT
```

After an order is confirmed, the product stock is reduced and the order is saved in `orders.txt`.

### Admin Workflow

The admin must log in before accessing the admin dashboard.

The admin can:

1. Add products
2. Delete products
3. Browse products
4. Update stock
5. View all orders
6. Update order status

## Data Storage

This project does not use a database. Instead, it uses text files for storing data.

The three main files are:

```text
products.txt
customers.txt
orders.txt
```

The program loads the data when it starts and saves the updated information during the application execution and before exiting.

## Sample Login

A sample admin account is included in the program:

```text
Username: admin
Password: admin123
```

A sample customer account is also initialized:

```text
Username: rahim
Password: pass123
```

These accounts are provided only for testing the application.

## Requirements

To run the project, you need:

* C++ compiler
* C++11 or later
* Windows, Linux, or macOS

## Compilation

Using g++:

```bash
g++ maincode.cpp -o shopping
```

## Run

On Windows:

```bash
shopping.exe
```

On Linux/macOS:

```bash
./shopping
```

Make sure `products.txt`, `customers.txt`, and `orders.txt` are in the same directory as the executable.

## Limitations

This is a console-based educational project, so it has some limitations:

* Data is stored in text files instead of a database.
* Passwords are stored as plain text.
* There is no real online payment system.
* There is no graphical user interface.
* Product images are not supported.
* Delivery tracking is not included.

## Future Improvements

Some possible improvements are:

* Database integration
* Password encryption
* Graphical user interface
* Online payment integration
* Product reviews and ratings
* Discount and coupon system
* Delivery tracking
* Customer profile management
* Sales reports
* Better input validation

## License

This project was developed for educational purposes.

## Author

**Tahasanur Karim**
**Email:** [tahasanurkarim@gmail.com](mailto:tahasanurkarim@gmail.com)
