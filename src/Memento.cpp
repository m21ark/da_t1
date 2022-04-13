#include "../include/Memento.h"

void Memento::save(State state) {
    using namespace std;

    if (state.truck == NOT_PROVIDED && state.max_prof == NOT_PROVIDED) {
        ofstream fstream1(dir_path + "/TomorrowOrders.txt", ios::out | ios::trunc);
        for (auto e: state.orders) {
            fstream1 << e.id << " " << e.reward << " €" << endl;
        }
        return;
    }

    std::filesystem::create_directory(dir_path);
    ofstream fstream1(dir_path + "/t_" + to_string(state.truck) + ".txt", ios::out | ios::trunc);
    fstream1 << "Truck: " << state.truck << " Total Reward: " << state.max_prof << endl;
    fstream1 << "OrderId reward" << endl;
    for (auto e: state.orders) {
        fstream1 << e.id << " " << e.reward << " €" << endl;
    }

    fstream1.close();
}
