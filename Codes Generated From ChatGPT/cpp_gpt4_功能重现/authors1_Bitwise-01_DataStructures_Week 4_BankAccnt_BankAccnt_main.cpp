#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const int max_columns = 2;
const int last_account_number = -1;
const int first_column = 0;
const int second_column = 1;
const int max_accounts = 1000;
const int accounts_at_a_time = 10;

void write_to_file(std::string filename, const std::vector<std::vector<int>>& accounts);
void add_accounts(std::vector<std::vector<int>>& accounts, std::vector<std::vector<int>>& accounts_chunks);
int update_balance(const std::vector<std::vector<int>>& transactions, int account_number, int initial_balance);
void read_accounts_file(std::string filename, std::vector<std::vector<int>>& accounts);
void read_accounts(std::vector<std::vector<int>>& accounts, const std::vector<std::vector<int>>& transactions);
int read_transactions_file(std::string filename, std::vector<std::vector<int>>& transactions);

int main() {
    std::vector<std::vector<int>> transactions;
    std::vector<std::vector<int>> accounts(max_accounts, std::vector<int>(max_columns, 0));

    int transaction_count = read_transactions_file("transactions.txt", transactions);
    read_accounts_file("accounts.txt", accounts);
    read_accounts(accounts, transactions);

    for (int i = 0; i < max_accounts && accounts[i][first_column] != last_account_number; ++i) {
        std::cout << "Account Number: " << accounts[i][first_column] << " Balance: " << accounts[i][second_column] << std::endl;
    }

    write_to_file("updated_balances.txt", accounts);

    return 0;
}

void write_to_file(std::string filename, const std::vector<std::vector<int>>& accounts) {
    std::ofstream output_file(filename);

    for (int i = 0; i < max_accounts && accounts[i][first_column] != last_account_number; ++i) {
        output_file << accounts[i][first_column] << ' ' << accounts[i][second_column] << std::endl;
    }

    output_file.close();
}

void add_accounts(std::vector<std::vector<int>>& accounts, std::vector<std::vector<int>>& accounts_chunks) {
    for (int i = 0; i < accounts_at_a_time; ++i) {
        accounts[i] = accounts_chunks[i];
    }
}

int update_balance(const std::vector<std::vector<int>>& transactions, int account_number, int initial_balance) {
    int balance = initial_balance;

    for (const auto& transaction : transactions) {
        if (transaction[first_column] == account_number) {
            balance += transaction[second_column];
        }
    }

    return balance;
}

void read_accounts_file(std::string filename, std::vector<std::vector<int>>& accounts) {
    std::ifstream input_file(filename);
    std::vector<std::vector<int>> accounts_chunks(accounts_at_a_time, std::vector<int>(max_columns, 0));
    int account_number, balance;

    while (input_file >> account_number >> balance) {
        accounts_chunks.push_back({account_number, balance});
    }

    add_accounts(accounts, accounts_chunks);
    input_file.close();
}

void read_accounts(std::vector<std::vector<int>>& accounts, const std::vector<std::vector<int>>& transactions) {
    for (int i = 0; i < max_accounts && accounts[i][first_column] != last_account_number; ++i) {
        accounts[i][second_column] = update_balance(transactions, accounts[i][first_column], accounts[i][second_column]);
    }
}

int read_transactions_file(std::string filename, std::vector<std::vector<int>>& transactions) {
    std::ifstream input_file(filename);
    int transaction_type, account_number, transaction_amount;
    int transaction_count = 0;

    while (input_file >> transaction_type >> account_number >> transaction_amount) {
        transactions.push_back({transaction_type, account_number, transaction_amount});
        transaction_count++;
    }

    input_file.close();
    return transaction_count;
}
