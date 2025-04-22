#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <stdexcept>
#include <limits>
#include <vector>

using namespace std;

class DuplicateItemException : public runtime_error {
public:
    DuplicateItemException(const string& msg) : runtime_error(msg) {}
};

class ItemNotFoundException : public runtime_error {
public:
    ItemNotFoundException(const string& msg) : runtime_error(msg) {}
};

class StoredItem {
private:
    string id;
    string description;
    string location;

public:
    StoredItem(string id, string desc, string loc)
        : id(id), description(desc), location(loc) {}

    string getId() const { return id; }
    string getDescription() const { return description; }
    string getLocation() const { return location; }
};

class StorageManager {
private:
    unordered_map<string, shared_ptr<StoredItem>> itemById;
    map<string, shared_ptr<StoredItem>> itemByDescription;

    public:
    void addItem(const shared_ptr<StoredItem>& item) {
        // check for duplicate
        if (itemById.find(item->getId()) != itemById.end()) {
            throw DuplicateItemException("Item with ID " + item->getId() + " already exists!");
        }

        // Insert into both lsits
        itemById[item->getId()] = item;
        itemByDescription[item->getDescription()] = item;
        cout << "Adding item: " << item->getId() << " - " << item->getDescription() << endl;
    }

    shared_ptr<StoredItem> findById(const string& id) const {
        auto it = itemById.find(id);
        if (it != itemById.end()) {
            return it->second;
        }
        throw ItemNotFoundException("Item with ID " + id + " not found!");
    }

    void removeItem(const string& id) {
        // Check if the item exists
        auto it = itemById.find(id);
        if (it == itemById.end()) {
            throw ItemNotFoundException("Item with ID " + id + " not found!");
        }
        // Remove from both lists
        itemByDescription.erase(it->second->getDescription());
        itemById.erase(it);
        cout << "Removing item: " << id << endl;
    }

    void listItemsByDescription() const {
        cout << "Item List:" << endl;
        for (const auto& item : itemByDescription) {
            cout << "- "<<item.second->getDescription() << ": " << item.second->getLocation()<<": " <<item.second->getId()<< endl;
        }
    }
};

 
int InputValidation (int min, int max)// input validation for menu selection
{
    bool good_data = false;
    int check;
   // cin.ignore();
        
    do
    {
        cin >> check;
        good_data = cin.good();
        good_data = good_data && (check >= min) && (check <= max);

        if ( !cin.good() )
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // make sure to have #include <limits>
        }

        if ( !good_data)
        {
            cout<< "Invalid Input: Enter an integer between ";
            cout <<min <<"-"<< max<<". Please try again: ";
        }

    } while ( !good_data );

    cin.ignore();
    
    return check; 
}

int main() {
    StorageManager manager;
    int input;
    string description, aisle, row, location,itemNumber;
    vector<string> item1;

    // Add some items
    do{
        cout<<"-------------Main Menu-------------"<<endl;
        cout<<"1) Enter item into storage"<<endl;
        cout<<"2) Remove item from storage"<<endl;
        cout<<"3) Find an item in storage"<<endl;
        cout<<"4) List all items in storage"<<endl;
        cout<<"5) Exit"<<endl;

        cout<<"User Input: ";

        input = InputValidation (1,5);


        switch (input)
            {
            case 1:

                cout<<endl<<"Enter Item Number: ";
                cin >> itemNumber;
                itemNumber= "ITEM" + itemNumber;

                cout<<"Enter discription of item: ";
                cin.ignore();
                getline(cin,description);

                cout<<"Enter Asle Number: ";
                cin>> aisle;
             

                cout<<"Enter Shelf Number: ";
                cin>> row;

                location = "Aisle "+aisle+", Shelf "+row;


                break;
            case 2:
                cout<<endl<<"Enter item number: ";
                cin >> itemNumber;

                itemNumber="ITEM"+itemNumber;

                break;
            case 3:
                cout<<endl<<"Enter item number: ";
                cin >> itemNumber;

                itemNumber="ITEM"+itemNumber;
                break;
            case 4:
                manager.listItemsByDescription();
                break;

            }

            if (input == 1)
            {
                try
                {
                    auto item1 = make_shared<StoredItem>(itemNumber, description, location);
                    manager.addItem(item1);
                }
                    catch (const DuplicateItemException& e) {
                    cout << "Error: " << e.what() << std::endl;
                }
            }
            else if (input==2)
            {
                try 
                {
                    manager.removeItem(itemNumber);
                } 
                catch (const ItemNotFoundException& e) 
                {
                    cout << "Error: " << e.what() << endl;
                }
            }
            else if (input==3)
            {
                try
                {
                    shared_ptr<StoredItem> foundItem = manager.findById(itemNumber);
                    cout << "Found: " << foundItem->getDescription() << " at " << foundItem->getLocation() << endl;
                    cout<<endl;
                }
                catch (const ItemNotFoundException& e) 
                {
                    cout << "Error: " << e.what() << endl;
                }
            }
           


      }while(input != 5);

      cout<<endl<<"Exiting Application"<<endl;
    

    return 0;
}
