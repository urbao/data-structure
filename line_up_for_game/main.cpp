// hw1-3: analyze different time of line up status for a game
// environment: Clion 2021.3.2
// C++ type: C++ 11
// gcc type: gcc version 8.1.0
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// class for a player
class Player {
public:
    // default constructor
    Player() {
        this->player_num = -1;
        this->arrive_hour = -1;
        this->coin = -1;
        this->second_time = false;
    }

    Player(int player_num, int arrive_hour, int coin, bool second_time) {
        this->player_num = player_num;
        this->arrive_hour = arrive_hour;
        this->coin = coin;
        this->second_time = second_time;
    }

// player personal info
    int player_num;
    int arrive_hour;
    int coin;
    bool second_time;
};

// create player list
vector<Player> create_player_list() {
    // create player
    vector<Player> player_list;
    for (int i = 0; i <= 4; i++) {
        Player p(i, 0, 0, false);
        player_list.push_back(p);
    }
    return player_list;
}

// get integer function for coin counts & arrive hours (foolproof)
int get_integer_input(const string& info) {
    cout << info;
    string input;
    getline(cin, input);
    for (int i = 0; i < input.size(); i++) { // NOLINT(modernize-loop-convert)
        if (isdigit(input[i]));
        else {
            cout << "Error >> invalid input\n";
            return -1;
        }
    }
    return stoi(input);
}

// get player info & store it with vector
vector<int> get_player_info(const string& title, const string& info) {
    vector<int> result;
    cout << title << endl;
    for (int i = 0; i <= 4; i++) {
        int input = -1;
        while (input == -1) {
            input = get_integer_input(info + to_string(i) + " :");
        }
        result.push_back(input);
    }
    return result;
}

// assign each player info to its class
void assign_data_to_player_list(vector<int> arrived_hour, vector<int> coin, vector<Player>& player_list) {
    for (int i = 0; i < 5; i++) {
        player_list[i].arrive_hour = arrived_hour[i];
        player_list[i].coin = coin[i];
    }
}

// push function (from rear)
void push(Player*& line_queue, Player& push_player) {
    for (int i = 0; i < 5; i++) {
        if (line_queue[i].player_num == -1) {
            line_queue[i].player_num = push_player.player_num;
            line_queue[i].arrive_hour = push_player.arrive_hour;
            line_queue[i].coin = push_player.coin;
            line_queue[i].second_time = push_player.second_time;
            return;
        } else;
    }
}

// pop function (from begin)
void pop(Player*& line_queue) {
    // move all player info before an index & reset the last one
    for (int i = 0; i < 5; i++) {
        if (i == 4) {
            line_queue[i].player_num = -1;
            line_queue[i].coin = -1;
            line_queue[i].arrive_hour = -1;
            line_queue[i].second_time = false;
        } else line_queue[i] = line_queue[i + 1];
    }
}

// function to output nicely
void beautiful_output(const int current_hour, Player current_player) {
    cout << "hour: " << current_hour;
    if (current_hour == 0)cout << "    ";
    for (int i = 0; i < 4 - int(log10(current_hour)); i++) {
        cout << " ";
    }
    if (current_player.player_num == -1)cout << " player: X" << endl;
    else cout << " player: " << current_player.player_num << endl;
}

// get the total count of the game should be played(which is total of coin counts)
int get_total_counts(vector<Player> player_list) {
    int result = 0;
    for (int i = 0; i < player_list.size(); i++) { // NOLINT(modernize-loop-convert)
        result += player_list[i].coin;
    }
    return result;
}

// check if no one wait in line
bool no_one_wait_in_line(Player*& line_queue) {
    for (int i = 0; i < 5; i++) {
        if (line_queue[i].player_num != -1)return false;
    }
    return true;
}

// create a vector contains all player which waiting in line from smallest to biggest
void find_who_arrive_and_arrange_to_queue(vector<Player>& player_list, const int current_hour, Player*& line_queue) {
    // run all player, check if arrive hours match
    for (int i = 0; i < 5; i++) {
        if (player_list[i].arrive_hour == current_hour && player_list[i].coin != 0)push(line_queue, player_list[i]);
    }
}

// find a player address in player_list with given player_num
void current_player_address_in_player_list(const int player_num, vector<Player>& player_list, Player*& current_player) {
    for (int i = 0; i < 5; i++) {
        if (player_list[i].player_num == player_num) {
            current_player = &player_list[i];
            return;
        }
    }
}

// serve player for playing game
void serve_player(Player*& line_queue, int current_hour, vector<Player>& player_list) {
    beautiful_output(current_hour, line_queue[0]);
    Player* current_player = nullptr;
    current_player_address_in_player_list(line_queue[0].player_num, player_list, current_player);
    if (current_player->second_time && current_player->coin > 1) {
        pop(line_queue);
        current_player->second_time = false;
        current_player->arrive_hour = current_hour + 1;
    } else if (current_player->coin == 1) {
        pop(line_queue);
        current_player->arrive_hour = -1;
    } else {
        current_player->second_time = true;
    }
    current_player->coin -= 1;
}

// start analyze & show result
void analyze_and_show_result(Player*& line_queue, vector<Player>& player_list) {
    int count = 1, current_hour = 0;
    int total_count = get_total_counts(player_list);
    cout << "=======Line Up Result=======\n";
    while (count <= total_count) {
        find_who_arrive_and_arrange_to_queue(player_list, current_hour, line_queue);
        if (no_one_wait_in_line(line_queue))beautiful_output(current_hour, Player(-1, -1, -1, false));
        else {
            serve_player(line_queue, current_hour, player_list);
            count++;
        }
        current_hour++;
    }
    cout<<"\nThe line up is over !!\n";
    cout << "===========================\n";
}


int main() {

    // build player vector
    vector<Player> player_list = create_player_list();

    // get player info & assign them to player info
    vector<int> player_arrive_hour = get_player_info("=====Player Arrived Hour=====", "Player ");
    vector<int> player_own_coin = get_player_info("======Player Owned Coin======", "Player ");
    assign_data_to_player_list(player_arrive_hour, player_own_coin, player_list);

    //start analyze result
    auto* line_queue = new Player[5];
    analyze_and_show_result(line_queue, player_list);

    // deallocate memory
    line_queue = nullptr;
    delete[] line_queue;

    system("pause");
    return 0;
}
