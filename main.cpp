/*
SentanceFilter.cpp -
Author: Jensen McKenzie
Module: 9
Project: Homework 9
Problem Statement: Parse through a file changing the first letter of each sentant to upppercase, and everything else to lowercase, and output the result to a file.

Algorithm/Plan:
  1. Open the input file
  2. Get each line of the input file, and store it in contents.
   2a. Loop through each character in the line.
   2b. Check to see if the current character is the first letter in the string, or the start of a sentance, if so, change it to uppercase.
   2c. If not, change the character to lowercase.
   2d. Add the changed character to the contents string.
  3. Close the input file.
  4. Open the output file.
  5. Write the string contents to the output file.
  6. Close the output file.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

struct item{
    string description, dateAdded;
    int quantity;
    double wholesaleCost, retailCost;
    item(){
        this->description = "";
        this->quantity = 0;
        this->wholesaleCost = 0;
        this->retailCost = 0;
        this->dateAdded = "";
    }
    item(string description, int quantity, double wholesaleCost, double retailCost, string dateAdded){
        this->description = description;
        this->quantity = quantity;
        this->wholesaleCost = wholesaleCost;
        this->retailCost = retailCost;
        this->dateAdded = dateAdded;
    }

    void print(){
        cout << "Description: " << description << "\nQuantity on hand: " << quantity << "\nWholesale cost: " << wholesaleCost << "\nRetail cost: " << retailCost << "\nDate added: " << dateAdded << endl;
    }
};


int main() {
    int size = 0;
    const string filename = "inventory.bin";
    ofstream output_file(filename, ios::binary | ios::out);
    ifstream input_file(filename, ios::binary | ios::in);
    if (!input_file) {
        cout << "Error locating file.";
        exit(1);
    }
    output_file.close();
    input_file.close();
    char choice = 0;
    while (true) {
        cout << "Enter a choice:";
        cin >> choice;
        switch(choice) {
            case '1': {
                cout << "Adding a new record to the file.\nEnter the item's description:";
                string description, date;
                int quantity;
                double wholesale, retail;
                cin.ignore();
                getline(cin, description);
                cout << "Enter the quantity on hand:";
                cin >> quantity;
                cout << "Enter the wholesale cost:";
                cin >> wholesale;
                cout << "Enter the retail cost:";
                cin >> retail;
                cout << "Enter the date added:";
                cin >> date;
                item l(description, quantity, wholesale, retail, date);
                size++;
                ofstream output_file(filename, ios::binary | ios::out);
                output_file.write((char *) &l, sizeof(l));
                output_file.close();
                continue;
            }
            case '2': {
                if (size == 0) {
                    cout << "Displaying a record from the file.\nThere are currently no items in the inventory."
                         << endl;
                    continue;
                }
                int choice;
                cout << "Displaying a record from the file.\nThe current file size is " << size
                     << " items.\nPlease enter a number to display:";
                cin >> choice;
                if (choice < 0 || choice > size) {
                    cout << "Incorrect choice for item, please try again." << endl;
                    continue;
                } else {
                    item master[size];
                    ifstream input_file(filename, ios::binary | ios::in);
                    input_file.read((char *) &master, sizeof(master));
                    master[choice-1].print();
                    input_file.close();
                }
                continue;
            }
            case '3':
                cout << "3";
                continue;
            case '4':
                cout << "Exiting program.";
                exit(1);
            default:
                cout << "Incorrect selection, please try again." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    }
}

