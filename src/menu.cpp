#include "../include/menu.h"


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

char askChar() {
    char c;
    cout << ">> ";
    cin >> c;
    cin.clear();
    cin.ignore(1000, '\n');
    return c;
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

    int day;
    cout << "\nInput day (1-30) >> ";
    if (!(cin >> day)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return {};
    }

    if (day < 1 || day > 30) {
        cin.clear();
        cin.ignore(1000, '\n');
        return {};
    }

    if (day < 10) {
        file_paths.first = "../data/dates/2022040" + to_string(day) + "/c.txt";
        file_paths.second = "../data/dates/2022040" + to_string(day) + "/e.txt";
    } else {
        file_paths.first = "../data/dates/202204" + to_string(day) + "/c.txt";
        file_paths.second = "../data/dates/202204" + to_string(day) + "/e.txt";
    }

    cin.clear();
    cin.ignore(1000, '\n');
    return file_paths;
}


void Menu::scenario1(const pair<string, string> &files) {

    vector<Truck> trucks = read_trucks(files.first);
    vector<Order> orders = read_orders(files.second);

    cout << "\nOptimizing number of trucks used:\n\n";
    cout << "1) Rapid Knapsack:\tGreedy choice of best Trucks and Knapsack for order's combinations per truck\n";
    cout << "2) Slow Brute Force:\tGreedy choice of best Trucks and brute force order's combinations per truck\n";
    cout << "3) Slow Backtracking:\tCalculates the best scenario possible using backtracking (very slow)\n";

    char c = askChar();

    if (c == '1')
        OptimizeNumberOfDeliveries::greedyTrucksAndKnapsack(trucks, orders);
    else if (c == '2')
        OptimizeNumberOfDeliveries::greedyTrucksAndBruteForce(trucks, orders);
    else if (c == '3')
        OptimizeNumberOfDeliveries::backtracking(trucks, orders);
    else {
        cout << endl << "That is not a valid option!" << endl;
        getchar();
        return;
    }
    getchar();
}

void Menu::scenario2(const pair<string, string> &files) {

    vector<Truck> trucks = read_trucks(files.first);
    vector<Order> orders = read_orders(files.second);

    cout << "\nTrucks are chosen in a greedy way\n";
    cout << "File reports will be created\n\n";
    cout << "1) Rapid & Sub-Optimal: Greedy Trucks Fractional Knapsack\n\n";
    cout << "2) Slow & Optimal (more space): Greedy Trucks Linear Knapsack\n\n";
    cout << "3) Slower & Optimal (less space): Greedy Trucks Linear Knapsack (divide & conquer)\n\n";

    char c = askChar();

    if (c == '1')
        OptimizeProfit::greedyTrucksAndFractionalKnapsack(trucks, orders);
    else if (c == '2') {
        if (orders.size() >= 4500 || trucks.size() >= 1200)
            cout << "For a large number of Orders/Trucks try option 3\n";
        else
            OptimizeProfit::greedyTrucksAndLinearKnapsack(trucks, orders);
    } else if (c == '3')
        OptimizeProfit::greedyTrucksAndOptimizedSpaceOfLK(trucks, orders);
    else {
        cout << endl << "That is not a valid option!" << endl;
        getchar();
        return;
    }
    getchar();
}

void Menu::scenario3(const string &file) {

    vector<Order> orders = read_orders(file);

    cout << "\n1) Rapid: Optimal Task Sorting (N*Log N)\n";
    cout << "2) Slow: Optimal Task Sorting (N^2)\n";
    cout << "3) Slower:  Task Brute Force\n\n";

    char c = askChar();

    if (c == '1')
        express_scheduling(orders);
    else if (c == '2')
        express_scheduling_bubble(orders);
    else if (c == '3')
        express_scheduling_brute(orders);
    else {
        cout << "\nThat is not a valid option!\n";
        getchar();
        return;
    }
    getchar();
}
