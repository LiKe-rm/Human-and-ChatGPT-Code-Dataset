#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <picojson.h>
#include <QApplication>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QMessageBox>

struct Client {
    std::string name;
    double loan_amount;
    double annual_interest_rate;
    int loan_period_years;
};

double calculate_monthly_payment(double loan_amount, double annual_interest_rate, int loan_period_years) {
    double monthly_interest_rate = annual_interest_rate / 12 / 100;
    int total_months = loan_period_years * 12;
    double temp = pow(1 + monthly_interest_rate, total_months);
    return loan_amount * monthly_interest_rate * temp / (temp - 1);
}

void show_messagebox(const std::string& message) {
    QApplication app(argc, argv);
    QMessageBox msg_box;
    msg_box.setWindowTitle("Loan Calculator");
    msg_box.setText(QString::fromStdString(message));
    msg_box.exec();
}

int main(int argc, char *argv[]) {
    std::ifstream file("db.json");
    if (!file.is_open()) {
        show_messagebox("Error: Could not open 'db.json'");
        return 1;
    }

    std::string json_str((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());
    file.close();

    picojson::value json_value;
    std::string parse_error = picojson::parse(json_value, json_str);
    if (!parse_error.empty()) {
        show_messagebox("Error: Could not parse 'db.json': " + parse_error);
        return 1;
    }

    std::vector<Client> clients;
    for (const auto& client_value : json_value.get<picojson::array>()) {
        const picojson::object& client_obj = client_value.get<picojson::object>();
        Client client;
        client.name = client_obj.at("name").get<std::string>();
        client.loan_amount = client_obj.at("loan_amount").get<double>();
        client.annual_interest_rate = client_obj.at("annual_interest_rate").get<double>();
        client.loan_period_years = static_cast<int>(client_obj.at("loan_period_years").get<double>());
        clients.push_back(client);
    }

    std::cout << "Client Name\tMonthly Payment\tLoan Period (Years)" << std::endl;
    for (const auto& client : clients) {
        double monthly_payment = calculate_monthly_payment(client.loan_amount, client.annual_interest_rate, client.loan_period_years);
        std::cout << client.name << "\t" << monthly_payment << "\t" << client.loan_period_years << std::endl;
    }

    return 0;
}
