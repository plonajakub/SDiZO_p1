#include "ConsoleMenu.h"


ConsoleMenu::ConsoleMenu() : nextFreeMenuOperation(0) {
    table = new Table;
    dll = new DoublyLinkedList;
    heap = new Heap;
    rbt = new RedBlackTree;
    prepareMenuOperations();
}

ConsoleMenu::~ConsoleMenu() {
    delete table;
    delete dll;
    delete heap;
    delete rbt;
}

void ConsoleMenu::addMenuOperation(const ConsoleMenu::MenuOperation &menuOperation) {
    if (nextFreeMenuOperation == MAX_OPERATIONS_QUANTITY) {
        throw std::out_of_range("ConsoleMenu operation's limit reached");
    }
    menuOperations[nextFreeMenuOperation] = menuOperation;
    ++nextFreeMenuOperation;
}

void ConsoleMenu::start(const std::string &menuCode) {
    int menuControlVariable;
    ProgramState ps = ProgramState::RUNNING;
    while (ps == ProgramState::RUNNING) {
        cout << std::string(70, '#') << endl << endl;
        cout << this->getMenuOperation(menuCode).menuItem.operationName << ":" << endl;
        printMenuOptions(menuCode);
        menuControlVariable = getMenuControlVariable(menuCode);
        ps = chooseMenuOperation(menuCode, menuControlVariable);
    }
}

void ConsoleMenu::printMenuOptions(const std::string &menuCode) {
    MenuItem &menuItem = this->getMenuOperation(menuCode).menuItem;
    MenuItem::allMenuOptions menuOptions = menuItem.getMenuOptions();
    for (int i = 0; i < menuItem.getMenuOptionsSize(); ++i) {
        cout << menuOptions[i].ID << ". " << menuOptions[i].description << endl;
    }
    if (menuCode.empty()) {
        cout << "0. Exit" << endl;
    }
    if (!menuCode.empty()) {
        cout << "0. Return" << endl;
    }
}

ConsoleMenu::MenuOperation &ConsoleMenu::getMenuOperation(const std::string &operationID) {
    for (auto &operation : menuOperations) {
        if (operation.ID == operationID) {
            return operation;
        }
    }
    throw std::invalid_argument("No such MenuOperation");
}

int ConsoleMenu::getMenuControlVariable(const std::string &menuCode) {
    MenuOperation menuOperation = this->getMenuOperation(menuCode);
    int menuControlVariable = -1;
    Operation status = Operation::FAILURE;
    cout << endl << "Choose operation:";
    while (status == Operation::FAILURE) {
        try {
            cin >> menuControlVariable;
            if (menuControlVariable < 0 || menuControlVariable > menuOperation.menuItem.getMenuOptionsSize()) {
                cout << "Wrong operation's ID. Try again: ";
                continue;
            }
            status = Operation::SUCCESS;
        } catch (const std::ios_base::failure &e) {
            cout << "Wrong input. Try again: ";
            cin.ignore(std::numeric_limits<std::streamsize>::max());
            continue;
        }
    }
    return menuControlVariable;
}

ConsoleMenu::ProgramState ConsoleMenu::chooseMenuOperation(const std::string &menuCode, int menuControlVariable) {
    if (menuControlVariable == 0 && !menuCode.empty()) {
        cout << "--- RETURN ---" << endl;
        return ProgramState::RETURN;
    }
    if (menuControlVariable == 0 && menuCode.empty()) {
        cout << "--- EXIT ---" << endl;
        return ProgramState::EXIT;
    }
    std::string operationCode = menuCode + std::to_string(menuControlVariable);

    if (this->getMenuOperation(operationCode).menuItem.operationType == MenuItem::OperationType::SUBMENU) {
        this->start(operationCode);
        /////////////////////////////////////////////////////////////////
        //// Table - operations
        /////////////////////////////////////////////////////////////////
    } else if (operationCode == "11") {
        cout << endl;
        try {
            Table inputData = this->loadDataFromFile("build_table.txt");
            for (int i = 0; i < inputData.getSize(); ++i) {
                table->insertAtEnd(inputData[i]);
            }
            cout << "Data successfully loaded into the table!" << endl;
            cout << "Table after load: " << *table << endl;
        } catch (const std::ios_base::failure &e) {
            cout << "Table not affected" << endl;
        }
    } else if (operationCode == "12") {
        int index;
        cout << "Enter an index for the value to be removed:";
        cin >> index;
        cout << endl;
        try {
            table->remove(index);
        } catch (const std::out_of_range &e) {
            cout << "Error: " << e.what() << endl;
        }
        cout << "Table after removal: " << *table << endl;
    } else if (operationCode == "13") {
        int index, value;
        cout << "Enter an index for a new value:";
        cin >> index;
        cout << "Enter the new value:";
        cin >> value;
        cout << endl;
        try {
            table->insert(index, value);
        } catch (const std::out_of_range &e) {
            cout << "Error: " << e.what() << endl;
        }
        cout << "Table after insertion: " << *table << endl;
    } else if (operationCode == "14") {
        int value;
        cout << "Enter value to be searched for in the table:";
        cin >> value;
        cout << endl;
        int index = table->search(value);
        if (index != Table::VALUE_NOT_FOUND) {
            cout << "Entered value is in the table" << endl;
        } else {
            cout << "Entered value is not in the table" << endl;
        }
    } else if (operationCode == "15") {
        cout << endl;
        cout << "Table: " << *table << endl;
        /////////////////////////////////////////////////////////////////
        //// List - operations
        /////////////////////////////////////////////////////////////////
    } else if (operationCode == "21") {
        cout << endl;
        try {
            Table inputData = this->loadDataFromFile("build_list.txt");
            for (int i = 0; i < inputData.getSize(); ++i) {
                dll->insertAtEnd(inputData[i]);
            }
            cout << "Data successfully loaded into the list!" << endl;
            cout << "List after load: " << *dll << endl;
        } catch (const std::ios_base::failure &e) {
            cout << "List not affected" << endl;
        }
    } else if (operationCode == "22") {
        int value;
        cout << "Enter a value to be removed:";
        cin >> value;
        cout << endl;
        try {
            dll->removeByValue(value);
        } catch (const std::out_of_range &e) {
            cout << "No such value in the list!" << endl;
        }
        cout << "List after removal: " << *dll << endl;
    } else if (operationCode == "23") {
        int searchValue, insertValue;
        cout << "Enter a base value:";
        cin >> searchValue;
        cout << "Enter a new value:";
        cin >> insertValue;
        cout << endl;
        dll->insertAfterValue(searchValue, insertValue);
        cout << "List after insertion: " << *dll << endl;
    } else if (operationCode == "24") {
        int value;
        cout << "Enter value to be searched for in the list:";
        cin >> value;
        cout << endl;
        int index = dll->search(value);
        if (index != DoublyLinkedList::VALUE_NOT_FOUND) {
            cout << "Entered value is in the list" << endl;
        } else {
            cout << "Entered value is not in the list" << endl;
        }
    } else if (operationCode == "25") {
        cout << endl;
        cout << "List: " << *dll << endl;
        /////////////////////////////////////////////////////////////////
        //// Heap - operations
        /////////////////////////////////////////////////////////////////
    } else if (operationCode == "31") {
        cout << endl;
        try {
            Table inputData = this->loadDataFromFile("build_heap.txt");
            for (int i = 0; i < inputData.getSize(); ++i) {
                heap->insert(inputData[i]);
            }
            cout << "Data successfully loaded into the heap!" << endl;
            cout << "Heap after load: " << endl << *heap << endl;
        } catch (const std::ios_base::failure &e) {
            cout << "Heap not affected" << endl;
        }
    } else if (operationCode == "32") {
        int key;
        cout << "Enter a key to be removed:";
        cin >> key;
        cout << endl;
        try {
            heap->remove(key);
        } catch (const std::invalid_argument &e) {
            cout << "No such key in the heap!" << endl;
        }
        cout << "Heap after removal: " << endl << *heap << endl;
    } else if (operationCode == "33") {
        int key;
        cout << "Enter a new key:";
        cin >> key;
        cout << endl;
        heap->insert(key);
        cout << "Heap after insertion: " << endl << *heap << endl;
    } else if (operationCode == "34") {
        int key;
        cout << "Enter a key to be searched for in the heap:";
        cin >> key;
        cout << endl;
        int index = heap->search(key);
        if (index != Heap::KEY_NOT_FOUND) {
            cout << "Entered key is in the heap" << endl;
        } else {
            cout << "Entered key is not in the heap" << endl;
        }
    } else if (operationCode == "35") {
        cout << endl;
        cout << "Heap: " << endl << *heap << endl;
        /////////////////////////////////////////////////////////////////
        //// Red-Black Tree - operations
        /////////////////////////////////////////////////////////////////
    } else if (operationCode == "41") {
        cout << endl;
        try {
            Table inputData = this->loadDataFromFile("build_rbt.txt");
            for (int i = 0; i < inputData.getSize(); ++i) {
                rbt->insert(inputData[i]);
            }
            cout << "Data successfully loaded into the tree!" << endl;
            cout << "Tree after load: " << endl << *rbt << endl;
        } catch (const std::ios_base::failure &e) {
            cout << "Tree not affected" << endl;
        }
    } else if (operationCode == "42") {
        int key;
        cout << "Enter a key to be removed:";
        cin >> key;
        cout << endl;
        try {
            rbt->remove(key);
        } catch (const std::invalid_argument &e) {
            cout << "No such key in the tree!" << endl;
        }
        cout << "Tree after removal: " << endl << *rbt << endl;
    } else if (operationCode == "43") {
        int key;
        cout << "Enter a new key:";
        cin >> key;
        cout << endl;
        rbt->insert(key);
        cout << "Tree after insertion: " << endl << *rbt << endl;
    } else if (operationCode == "44") {
        int key;
        cout << "Enter a key to be searched for in the tree:";
        cin >> key;
        cout << endl;
        auto *node = rbt->search(key);
        if (node != nullptr) {
            cout << "Entered key is in the tree" << endl;
        } else {
            cout << "Entered key is not in the tree" << endl;
        }
    } else if (operationCode == "45") {
        cout << endl;
        cout << "Tree: " << endl << *rbt << endl;
    }
    return ProgramState::RUNNING;
}

void ConsoleMenu::prepareMenuOperations() {
    MenuOperation menuOperation;
    MenuItem menuItem;
    MenuItem::MenuOption menuOption;

    ////////////////////////////////////////////////////////////////////
    // Main menu
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "";
    menuItem = MenuItem(MenuItem::OperationType::SUBMENU, "Main menu");

    menuOption.ID = "1";
    menuOption.description = "Table";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "2";
    menuOption.description = "List";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "3";
    menuOption.description = "Heap";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "4";
    menuOption.description = "Red-Black Tree";
    menuItem.addMenuOption(menuOption);

    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    ////////////////////////////////////////////////////////////////////
    // Table
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "1";
    menuItem = MenuItem(MenuItem::OperationType::SUBMENU, "Table");

    menuOption.ID = "1";
    menuOption.description = "Build from file";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "2";
    menuOption.description = "Remove element";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "3";
    menuOption.description = "Insert element";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "4";
    menuOption.description = "Find element";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "5";
    menuOption.description = "Show structure";
    menuItem.addMenuOption(menuOption);

    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);


    ////////////////////////////////////////////////////////////////////
    // Table - operations
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "11";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Build from file");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "12";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Remove element");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "13";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Insert element");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "14";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Find element");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "15";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Show structure");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    ////////////////////////////////////////////////////////////////////
    // List
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "2";
    menuItem = MenuItem(MenuItem::OperationType::SUBMENU, "List");

    menuOption.ID = "1";
    menuOption.description = "Build from file";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "2";
    menuOption.description = "Remove element";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "3";
    menuOption.description = "Insert element";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "4";
    menuOption.description = "Find element";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "5";
    menuOption.description = "Show structure";
    menuItem.addMenuOption(menuOption);

    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);


    ////////////////////////////////////////////////////////////////////
    // List - operations
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "21";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Build from file");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "22";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Remove element");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "23";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Insert element");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "24";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Find element");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "25";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Show structure");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    ////////////////////////////////////////////////////////////////////
    // Heap
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "3";
    menuItem = MenuItem(MenuItem::OperationType::SUBMENU, "Heap");

    menuOption.ID = "1";
    menuOption.description = "Build from file";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "2";
    menuOption.description = "Remove element";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "3";
    menuOption.description = "Insert element";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "4";
    menuOption.description = "Find element";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "5";
    menuOption.description = "Show structure";
    menuItem.addMenuOption(menuOption);

    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);


    ////////////////////////////////////////////////////////////////////
    // Heap - operations
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "31";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Build from file");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "32";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Remove element");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "33";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Insert element");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "34";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Find element");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "35";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Show structure");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    ////////////////////////////////////////////////////////////////////
    // Red-Black Tree
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "4";
    menuItem = MenuItem(MenuItem::OperationType::SUBMENU, "Red-Black Tree");

    menuOption.ID = "1";
    menuOption.description = "Build from file";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "2";
    menuOption.description = "Remove element";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "3";
    menuOption.description = "Insert element";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "4";
    menuOption.description = "Find element";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "5";
    menuOption.description = "Show structure";
    menuItem.addMenuOption(menuOption);

    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);


    ////////////////////////////////////////////////////////////////////
    // Red-Black Tree - operations
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "41";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Build from file");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "42";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Remove element");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "43";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Insert element");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "44";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Find element");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "45";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Show structure");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);
}

Table ConsoleMenu::loadDataFromFile(const std::string &filename) {
    Table data;
    std::ifstream file("../build_values/" + filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " not opened" << endl;
        throw std::ios_base::failure("File " + filename + " not opened");
    }
    int dataQuantity;
    file >> dataQuantity;

    int nextValue;
    for (int i = 0; i < dataQuantity; ++i) {
        file >> nextValue;
        data.insertAtEnd(nextValue);
    }
    file.close();
    return data;
}
