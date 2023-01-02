// hw1-1: analyze most possible earn from a given array of stock prices of a period
// environment: Clion 2021.3.2
// C++ type: C++ 11
// gcc type: gcc version 8.1.0
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// get day count from user input
int get_day_count(const string& info) {
    cout << info;
    string day_count;
    getline(cin, day_count);
    for (int i = 0; i < day_count.size(); i++) {
        if (!isdigit(day_count[i])) {
            cout << "Error >> wrong input\n\n";
            return -1;
        } else;
    }
    return stoi(day_count);
}

// get day price from user input
vector<int> get_day_price(const string& info, int day_count) {
    cout << info;
    string price_str, day_price;
    vector<int> price_vec;
    for (int i = 0; i < day_count; i++) {
        if (i == day_count - 1)getline(cin, price_str, '\n');
        else getline(cin, price_str, ' ');
        price_vec.push_back(stoi(price_str));
    }
    return price_vec;
}

// find most profit
int find_max_profit(vector<int> price_vec) {
    vector<int> day_profit(price_vec); // store every day's biggest profit
    day_profit[0] = 0; // first day no profit
    int current_min_price = price_vec[0];
    for (int i = 1; i < price_vec.size(); i++) {
        // re_assign current min price during the past days
        current_min_price = min(current_min_price, price_vec[i]);
        // store i_th day biggest profit
        day_profit[i] = price_vec[i] - current_min_price;
    }
    // find the max value from vector of every day profit
    int max_profit = 0;
    for (int i = 0; i < day_profit.size(); i++) {
        if (day_profit[i] > max_profit)max_profit = day_profit[i];
        else;
    }
    return max_profit;
}

// print out the result of analysis
void print_result(int day_count, vector<int> price_vec, int profit) {
    cout << "\n========Stock Result========\n";
    cout << "Total day count: " << day_count << endl;
    cout << "All day price: ";
    for (int i = 0; i < price_vec.size(); i++) {
        cout << price_vec[i] << " ";
    }
    cout << endl;
    cout << "Biggest profit: " << profit;
    cout << "\n============================\n";
}


int main() {

    // foolproof wrong input
    int day_count = -1;
    while (day_count == -1) {
        day_count = get_day_count("Enter day count: ");
    }
    vector<int> price_vec = get_day_price("Enter price array: ", day_count);
    int max_profit = find_max_profit(price_vec);
    print_result(day_count, price_vec, max_profit);

    system("pause");
    return 0;
}
