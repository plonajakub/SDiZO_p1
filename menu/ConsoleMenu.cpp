#include <limits>
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

    if (operationCode == "1") {
        this->start(operationCode);
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
    }

    return ProgramState::RUNNING;
}

void ConsoleMenu::prepareMenuOperations() {
    MenuOperation menuOperation;
    MenuItem menuItem;
    MenuItem::MenuOption menuOption;

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
