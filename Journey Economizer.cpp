#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <climits>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

typedef pair<int, string> ipair;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void dijkstra(const string& src, const unordered_map<string, list<ipair>>& adj,
              unordered_map<string, int>& dist, unordered_map<string, string>& prev) {
    priority_queue<ipair, vector<ipair>, greater<ipair>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        string u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        if (dist_u > dist[u]) continue;
        if (adj.find(u) == adj.end()) continue;

        for (const auto& neighbor : adj.at(u)) {
            string v = neighbor.second;
            int cost = neighbor.first;

            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

void printPath(const string& target, const unordered_map<string, string>& prev) {
    if (prev.find(target) == prev.end() || prev.at(target) == "") {
        cout << target;
        return;
    }
    printPath(prev.at(target), prev);
    cout << " -> " << target;
}

class FinancialAdvisor {
private:
    double monthly_income;
    double income_growth_rate;
    double fixed_costs;
    double vacation_budget;
    int planning_months;
    map<string, double> variable_costs;

public:
    FinancialAdvisor(double income, double rate, double fixed, map<string, double> var_costs,
                     double budget, int months)
        : monthly_income(income), income_growth_rate(rate), fixed_costs(fixed),
          vacation_budget(budget), planning_months(months), variable_costs(var_costs) {}

    void visualizeSpending(ofstream& output) {
        output << "\n=========== Current Spending Breakdown ===========\n";
        output << "Monthly Income: $" << fixed << setprecision(2) << monthly_income << "\n";
        output << "Fixed Costs: $" << fixed << setprecision(2) << fixed_costs << "\n";
        output << "Variable Costs:\n";
        for (const auto& cost : variable_costs) {
            output << " - " << cost.first << ": $" << fixed << setprecision(2) << cost.second << "\n";
        }
        double total_spending = fixed_costs;
        for (const auto& cost : variable_costs) total_spending += cost.second;
        output << "Total Spending: $" << fixed << setprecision(2) << total_spending << "\n";
        output << "Current Savings: $" << fixed << setprecision(2) << (monthly_income - total_spending) << "\n";
    }

    void projectCashFlow(ofstream& output) {
        output << "\n=========== Projected Cash Flow ===========\n";
        output << setw(10) << "Month" << setw(20) << "Savings ($)\n";
        output << "-------------------------------------------\n";

        for (int t = 1; t <= planning_months; ++t) {
            double income = monthly_income * pow(1 + income_growth_rate, (t - 1) / 12.0);
            double total_variable_cost = 0;
            for (const auto& cost : variable_costs) total_variable_cost += cost.second;
            double monthly_savings = income - (fixed_costs + total_variable_cost);
            output << setw(10) << t << setw(20) << fixed << setprecision(2) << monthly_savings << "\n";
        }
    }

    void calculateMaximumAchievableReduction(ofstream& output) {
        vector<pair<string, double>> costs(variable_costs.begin(), variable_costs.end());
        double monthly_vacation_savings = vacation_budget / planning_months;
        double total_variable_costs = 0;
        for (const auto& cost : costs) total_variable_costs += cost.second;
        double monthly_savings = monthly_income - fixed_costs - total_variable_costs;

        output << "\n=========== Maximum Achievable Reduction ===========\n";
        output << "Vacation Goal: $" << fixed << setprecision(2) << vacation_budget << " in " << planning_months << " months.\n";
        output << "Required Monthly Savings: $" << fixed << setprecision(2) << monthly_vacation_savings << "\n";
        output << "Current Monthly Savings: $" << fixed << setprecision(2) << monthly_savings << "\n";

        if (monthly_savings >= monthly_vacation_savings) {
            output << "Congratulations! Your current savings are sufficient to meet your vacation goal.\n";
            return;
        }

        double required_reduction = monthly_vacation_savings - monthly_savings;
        output << "Additional Reduction Needed: $" << fixed << setprecision(2) << required_reduction << "\n";

        sort(costs.begin(), costs.end(), [](const auto& a, const auto& b) { return a.second > b.second; });

        double total_cost = accumulate(costs.begin(), costs.end(), 0.0,
            [](double sum, const auto& cost) { return sum + cost.second; });

        vector<pair<string, double>> selected_reductions;
        for (const auto& cost : costs) {
            double proportion = cost.second / total_cost;
            double reduction = proportion * required_reduction;
            selected_reductions.push_back({cost.first, reduction});
        }

        double max_reduction = accumulate(selected_reductions.begin(), selected_reductions.end(), 0.0,
            [](double sum, const auto& red) { return sum + red.second; });

        output << "Maximum Achievable Reduction: $" << fixed << setprecision(2) << max_reduction << "\n";

        if (max_reduction < required_reduction) {
            output << "Warning: Maximum achievable reduction is insufficient to meet your goal.\n";
            output << "Consider reducing fixed costs or increasing income.\n";
            return;
        }

        output << "The goal can be met by reducing the following costs proportionally:\n";
        for (const auto& reduction : selected_reductions) {
            double original = variable_costs[reduction.first];
            double percentage = (reduction.second / original) * 100;
            output << " - " << reduction.first << ": Reduce by $"
                   << fixed << setprecision(2) << reduction.second << " ("
                   << fixed << setprecision(1) << percentage << "% of the original cost)\n";
        }
    }

    int calculateTripCost(const string& src, const string& dst,
                          const unordered_map<string, list<ipair>>& adj,
                          ofstream& output, unordered_map<string, int>& dist,
                          unordered_map<string, string>& prev) {
        dist.clear();
        prev.clear();
        for (const auto& pair : adj) {
            dist[pair.first] = INT_MAX;
            prev[pair.first] = "";
        }

        dijkstra(src, adj, dist, prev);

        if (dist[dst] == INT_MAX) {
            output << "No path exists from " << src << " to " << dst << "\n";
            return -1;
        }

        output << "Shortest path from " << src << " to " << dst << " costs: $" << dist[dst] << "\n";
        output << "Path: ";
        printPath(dst, prev);
        output << "\n";

        return dist[dst];
    }
};

void getUserInputs(double& income, double& growth_rate, double& fixed_costs,
                   map<string, double>& variable_costs, double& vacation_budget, int& months) {
    cout << "Enter your monthly income: ";
    cin >> income;
    cout << "Enter annual income growth rate (e.g., 0.05 for 5%): ";
    cin >> growth_rate;
    cout << "Enter your fixed costs (e.g., rent, utilities): ";
    cin >> fixed_costs;

    int num_variable_costs;
    cout << "Enter the number of variable expense categories: ";
    cin >> num_variable_costs;

    variable_costs.clear();
    for (int i = 0; i < num_variable_costs; ++i) {
        string category;
        double cost;
        cout << "Enter category name: ";
        cin >> category;
        cout << "Enter monthly cost for " << category << ": ";
        cin >> cost;
        variable_costs[category] = cost;
    }

    cout << "Enter the number of months for planning: ";
    cin >> months;
}

int main() {
    unordered_map<string, list<ipair>> travel_graph = {
        {"Bangladesh", {{200, "Canada"}, {800, "Denmark"}}},
        {"Canada", {{200, "Bangladesh"}, {900, "Argentina"}, {700, "France"}, {1300, "England"}}},
        {"Denmark", {{800, "Bangladesh"}, {300, "Germany"}, {900, "Sweden"}}},
        {"Argentina", {{900, "Canada"}, {1100, "France"}}},
        {"France", {{700, "Canada"}, {1100, "Argentina"}, {500, "Spain"}, {500, "Italy"}, {200, "Germany"}}},
        {"England", {{1300, "Canada"}, {1500, "Norway"}}},
        {"Germany", {{300, "Denmark"}, {200, "France"}}},
        {"Spain", {{500, "France"}, {700, "Portugal"}}},
        {"Italy", {{500, "France"}}},
        {"Norway", {{1500, "England"}}},
        {"Sweden", {{900, "Denmark"}}},
        {"Portugal", {{700, "Spain"}}}
    };

    unordered_map<string, int> dist;
    unordered_map<string, string> prev;

    int choice;
    do {
        clearScreen();
        cout << "\n\n**************-> JOURNEY ECONOMIZER <-***************\n\n";
        cout << "1. Find cost from source to destination country\n";
        cout << "2. Find all destinations from source within budget\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            string source, destination;
            cout << "Enter the source country: ";
            cin >> source;
            cout << "Enter the destination country: ";
            cin >> destination;

            string filename = "financial_advice.txt";
            ofstream output(filename);
            if (!output.is_open()) {
                cerr << "Error: Unable to open file for saving output.\n";
                continue;
            }

            FinancialAdvisor advisor(0, 0, 0, {}, 0.0, 0);
            int trip_cost = advisor.calculateTripCost(source, destination, travel_graph, output, dist, prev);

            double vacation_budget;
            if (trip_cost == -1) {
                cout << "\nNo path exists. Enter estimated trip cost: $";
                cin >> vacation_budget;
            } else {
                vacation_budget = static_cast<double>(trip_cost);
            }

            double income, growth_rate, fixed_costs;
            map<string, double> variable_costs;
            int months;
            getUserInputs(income, growth_rate, fixed_costs, variable_costs, vacation_budget, months);

            FinancialAdvisor updated_advisor(income, growth_rate, fixed_costs, variable_costs, vacation_budget, months);
            updated_advisor.visualizeSpending(output);
            updated_advisor.projectCashFlow(output);
            updated_advisor.calculateMaximumAchievableReduction(output);
            output.close();

            cout << "\nFinancial advice saved to '" << filename << "'.\n";
        } else if (choice == 2) {
            clearScreen();
            string source;
            double budget;
            cout << "Enter the source country: ";
            cin >> source;
            cout << "Enter your budget: $";
            cin >> budget;

            dist.clear();
            prev.clear();
            for (const auto& pair : travel_graph) {
                dist[pair.first] = INT_MAX;
                prev[pair.first] = "";
            }
            dijkstra(source, travel_graph, dist, prev);

            cout << "\nDestinations within budget of $" << budget << ":\n";
            for (const auto& country : travel_graph) {
                if (dist[country.first] != INT_MAX && dist[country.first] <= budget && country.first != source) {
                    cout << " - " << country.first << ": $" << dist[country.first] << " (Path: ";
                    printPath(country.first, prev);
                    cout << ")\n";
                }
            }

            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 3);

    cout << "\n\nThank you for using Journey Economizer!\n";
    return 0;
}
