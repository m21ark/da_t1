#include "../include/menu.h"
#include "../include/read_files.h"
#include "../include/cen3.h"

string trimStr(string str) {
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);
    return str;
}


bool emptyStream(istream &ios) {
    string bufferContent;
    getline(ios, bufferContent);
    trimStr(bufferContent);
    if (bufferContent.empty())
        return true;
    return false;
}


void Menu::start() {
    char userInput;

    while (true) {
        (void) system(CLEAR);

        cout << "========================" << endl;
        cout << "        Scenarios   " << endl;
        cout << "========================" << endl;
        cout << "  1)  Scenario 1 " << endl;
        cout << "  2)  Scenario 2 " << endl;
        cout << "  3)  Scenario 3 " << endl;
        cout << "  0)  Exit" << endl;
        cout << "========================" << endl;
        cout << " > ";

        if ((cin >> userInput)) {
            if (!emptyStream(cin)) {
                cout << "Invalid Input!\n";
                continue;
            }

            pair<string, string> files;
            switch (userInput) {
                case '0':
                    return;
                case '1':
                    files = askFiles();
                    if (!files.second.empty()) scenario1(files);
                    break;
                case '2':
                    files = askFiles();
                    if (!files.second.empty()) scenario2(files);
                    break;
                case '3':
                    files = askFiles(true);
                    if (!files.second.empty()) scenario3(files.second);
                    break;
                default:
                    cout << "Invalid Input!\n";
                    break;
            }
            continue;

        } else {
            cout << "Invalid Input!\n";
            getchar();
            continue;
        }
    }
}

pair<string, string> Menu::askFiles(bool scene3) {

    pair<string, string> file_paths;

    cout << endl;
    auto invalid = [](const string &msg) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << msg << "\n";
        getchar();
    };

    int num, id;
    if (!scene3) {
        cout << "Trucks file (num id) >> ";
        if (!(cin >> num >> id)) {
            invalid("Invalid input!");
            return {};
        }
        file_paths.first = "../data/c_" + to_string(num) + "/c_" + to_string(id) + ".txt";

        if (!file_exists(file_paths.first)) {
            invalid("Truck file not found!");
            return {};
        }
    }

    cout << "Orders file (num id) >> ";
    if (!(cin >> num >> id)) {
        invalid("Invalid input!");
        return {};
    }
    file_paths.second = "../data/e_" + to_string(num) + "/e_" + to_string(id) + ".txt";

    if (!file_exists(file_paths.second)) {
        invalid("Order file not found!");
        return {};
    }

    cin.clear();
    cin.ignore(1000, '\n');
    return file_paths;
}


void Menu::scenario1(const pair<string, string> &files) {

    vector<Truck> trucks = read_trucks(files.first);
    vector<Order> orders = read_orders(files.second);

    cout << "\n...\n"; // TODO LINK MAIN SCENE FUNC
    getchar();
}

void Menu::scenario2(const pair<string, string> &files) {

    vector<Truck> trucks = read_trucks(files.first);
    vector<Order> orders = read_orders(files.second);

    cout << "\n...\n"; // TODO LINK SCENE FUNC
    getchar();
}

void Menu::scenario3(const string &file) {

    vector<Order> orders = read_orders(file);
    express_scheduling(orders);
    //TODO store to file results...
    getchar();
}



