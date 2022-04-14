#include "../include/Memento.h"

void Memento::save(const State &state) {

    if (state.truck == NOT_PROVIDED && state.max_prof == NOT_PROVIDED) {
        ofstream fs(dir_path + "/TomorrowOrders.txt", ios::out | ios::trunc);
        for (auto e: state.orders)
            fs << e << endl;
        return;
    }

    filesystem::create_directory(dir_path);
    ofstream fs(dir_path + "/t_" + to_string(state.truck) + ".txt", ios::out | ios::trunc);

    fs << "Truck_id: " << state.truck << "\nTotal Reward: " << state.max_prof << "€\n";
    fs << "=================================\n";
    fs << "  OrderId\t\t\tReward" << endl;
    fs << "=================================\n";

    unsigned total_reward = 0, count = 0;
    for (auto e: state.orders) {
        fs << setfill(' ') << setw(6) << e.id << "\t\t\t" << setw(8) << e.reward << "€" << endl;

        total_reward += e.reward;
        count++;
    }

    fs << "=================================\n";
    fs << "N_Orders: " << count << "\t" << "T_Reward: " << total_reward << "€";

    fs.close();
}

State Memento::loadDayBefore() {

    State state{};
    struct tm dayBefore = now;
    datePlusDays(&dayBefore, -1);

    string last_day_dir_path = "../report/" + to_string(dayBefore.tm_year + 1900)
                               + to_string(dayBefore.tm_mon + 1) + to_string(dayBefore.tm_mday);

    ifstream ifs(last_day_dir_path + "/TomorrowOrders.txt");

    if (!ifs.is_open())
        return state;

    Order order{};
    string aux;
    while (getline(ifs, aux)) {
        stringstream ss(aux);
        ss >> order;
        state.orders.push_back(order);
    }
    ifs.close();

    return state;
}
