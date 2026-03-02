#include <vector>
#include <iostream>
#include <fstream>
#include "i.h"
struct Artifact {
    int id;
    int weight;
    int value;
};
void t2() {
    using namespace std;
    cout<<"Введите имена входного и выходного файла"<<endl;
    string inname;
    cin >> inname;
    string outname;
    cin >> outname;
    fstream input(inname);
    fstream output(outname);
    if (!input.is_open()) {
        cout << "Не удалось открыть файл " << endl;
    }
    if (!output.is_open()) {
        cout << "Не удалось открыть файл " << endl;
    }
    int n;
    input >> n;
    vector<vector<int>> board(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input >> board[i][j];
        }
    }

    vector<vector<long long>> d(n, vector<long long>(n, 0));

    d[n-1][0] = board[n-1][0];

    for (int i = n-2; i >= 0; i--) {
        d[i][0] = d[i+1][0] + board[i][0];
    }
    for (int j = 1; j < n; j++) {
        d[n-1][j] = d[n-1][j-1] + board[n-1][j];
    }

    for (int i = n-2; i >= 0; i--) {
        for (int j = 1; j < n; j++) {
            d[i][j] = board[i][j] + min(d[i+1][j], d[i][j-1]);
        }
    }
    output << d[0][n-1];
    input.close();
    output.close();
}
bool readf(const std::string& filename, std::vector<Artifact>& artifacts, int& Z) {
    using namespace std;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл " << filename << endl;
        return false;
    }
    int N;
    file >> N >> Z;
    if (N <= 0 || Z <= 0) {
        cout << "Ошибка: Некорректные данные в файле" << endl;
        return false;
    }
    artifacts.resize(N);
    for (int i = 0; i < N; i++) {
        file >> artifacts[i].weight;
        artifacts[i].id = i + 1;
    }
    for (int i = 0; i < N; i++) {
        file >> artifacts[i].value;
    }
    file.close();
    return true;
}
void solve(const std::vector<Artifact>& artifacts, int Z, std::vector<int>& selectedIds,int &totalWeight,int& totalValue) {
    using namespace std;
    int N = artifacts.size();
    vector<vector<int>> dp(N + 1, vector<int>(Z + 1, 0));
    for (int i = 1; i <= N; i++) {
        for (int w = 0; w <= Z; w++) {
            dp[i][w] = dp[i - 1][w];
            if (artifacts[i - 1].weight <= w) {
                dp[i][w] = max(dp[i][w],
                              dp[i - 1][w - artifacts[i - 1].weight] + artifacts[i - 1].value);
            }
        }
    }
    totalWeight = 0;
    totalValue = dp[N][Z];
    int remainingWeight = Z;

    for (int i = N; i > 0; i--) {
        if (dp[i][remainingWeight] != dp[i - 1][remainingWeight]) {
            selectedIds.push_back(artifacts[i - 1].id);
            remainingWeight -= artifacts[i - 1].weight;
            totalWeight += artifacts[i - 1].weight;
        }
    }

}
void printResults(const std::vector<int>& selectedIds, int totalWeight, int totalValue) {
    using namespace std;
    cout << "Выбранные артефакты (порядковые номера): ";
    for (size_t i = 0; i < selectedIds.size(); i++) {
        cout << selectedIds[i];
        if (i < selectedIds.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "Суммарный вес: " << totalWeight << " кг" << endl;
    cout << "Общая ценность: " << totalValue << endl;
}


void t1() {
    using namespace std;
    fstream file("lab8_1.txt");
    string filename;
    cout << "Введите имя файла с данными: ";
    cin >> filename;
    vector<Artifact> artifacts;
    int Z;
    vector<int> selectedIds;
    readf(filename, artifacts, Z);
    int totalWeight,totalValue;
    solve(artifacts, Z, selectedIds,totalWeight,totalValue);
    printResults(selectedIds, totalWeight, totalValue);
}
void inputData(int& K, int& N) {
    using namespace std;
    cout << "Введите основание системы счисления K (2-10): ";
    cin >> K;

    while (K < 2 || K > 10) {
        cout << "Ошибка! K должно быть от 2 до 10. Повторите ввод: ";
        cin >> K;
    }

    cout << "Введите количество разрядов N (1 < N < 20, N + K < 26): ";
    cin >> N;

    while (N <= 1 || N >= 20 || N + K >= 26) {
        cout << "Ошибка! N должно быть 1 < N < 20 и N + K < 26. Повторите ввод: ";
        cin >> N;
    }
}
double countk(int K, int N) {
    using namespace std;
    if (N <= 0 || K < 2 || K > 10) return 0;
    vector<vector<double>> dp(N + 1, vector<double>(3, 0.0));
    dp[1][0] = K - 1;
    dp[1][1] = 0;
    dp[1][2] = 0;

    for (int pos = 2; pos <= N; pos++) {

        dp[pos][0] = (dp[pos-1][0] + dp[pos-1][1] + dp[pos-1][2]) * (K - 1);

        dp[pos][1] = dp[pos-1][0];

        dp[pos][2] = dp[pos-1][1];
    }
    double result = dp[N][0] + dp[N][1] + dp[N][2];
    return result;
}
void t3() {
    using namespace std;
    int K, N;
    inputData(K, N);

    double result = countk(K, N);

    cout << setprecision(0);
    cout << "\nКоличество " << N << "-разрядных " << K << "-ичных чисел";
    cout << " без более чем двух нулей подряд: " << result << endl;
}