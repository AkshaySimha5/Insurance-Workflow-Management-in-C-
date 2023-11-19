#include <bits/stdc++.h>
using namespace std;
ofstream outfile("output.txt",ios::app);
namespace Insurance {
    //AKSHAY
    // Exception handling for negative premium
    class NegativePremiumException : public exception {
    public:
        const char* what() const noexcept override {
            return "Premium cannot be negative.";
        }
    };
    // Exception handling for negative policy number
    class NegativePolicyNumberException : public exception {
    public:
        const char* what() const noexcept override {
            return "Policy number cannot be negative.";
        }
    };
    class Policy {
    public:
        Policy(int policyNumber, double premium) : policyNumber(policyNumber), premium(premium) {
            if (policyNumber < 0)
                throw NegativePolicyNumberException();
            if (premium < 0)
                throw NegativePremiumException();
        }
        virtual double calculateCoverage() = 0;
        virtual void displayDetails() = 0;
        int getPolicyNumber() { return policyNumber; }
        double getPremium() { return premium; }
        static int totalPolicies;

    private:
        int policyNumber;
        double premium;
    };

    int Policy::totalPolicies = 0; //initializing the static variable
    class MotorInsurance : public Policy {
    public:
        MotorInsurance(int policyNumber, double premium, string vehicleModel)
            : Policy(policyNumber, premium), vehicleModel(vehicleModel) {}

        double calculateCoverage() override {
            return getPremium() * 0.2;
        }
        void displayDetails() override {
            outfile << "Motor Insurance Policy #" << getPolicyNumber() << " Premium: Rs." << getPremium() << " Vehicle Model: " << vehicleModel << endl;
        }

    private:
        string vehicleModel;
    };
    class LifeInsurance : public Policy {
    public:
        LifeInsurance(int policyNumber, double premium, int policyTerm)
            : Policy(policyNumber, premium), policyTerm(policyTerm) {}

        double calculateCoverage() override {
            return getPremium() * policyTerm * 0.1;
        }

        void displayDetails() override {
            outfile << "Life Insurance Policy #" << getPolicyNumber() << " Premium: Rs." << getPremium() << " Policy Term: " << policyTerm << " years" << endl;
        }

    private:
        int policyTerm;
    };
    //ADITYA
    class HouseInsurance : public Policy {
    public:
        HouseInsurance(int policyNumber, double premium, string propertyType)
            : Policy(policyNumber, premium), propertyType(propertyType) {}

        double calculateCoverage() override {
            return getPremium() * 0.5;
        }

        void displayDetails() override {
            outfile << "House Insurance Policy #" << getPolicyNumber() << " Premium: Rs." << getPremium() << " Property Type: " << propertyType << endl;
        }

    private:
        string propertyType;
    };
}

// Friend function for accessing private members
double calculateTotalCoverage(const vector<Insurance::Policy*>& policies) {
    double totalCoverage = 0;
    for (const auto& policy : policies) {
        totalCoverage += policy->calculateCoverage();
    }
    return totalCoverage;
}
int getValidNonNegativeNumber() {
    int number;
    while (true) {
        cin >> number;

        if (cin.fail() || number < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid input. Please enter a valid non-negative number." << endl;
            //throw invalid_argument("Invalid input. Please enter a valid non-negative number.");
        } else {
            break;
        }
    }
    return number;
}
int getValidChoice() {
    int number;
    while (true) {
        cin >> number;

        if (cin.fail() || number < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid input. Please enter a valid non-negative number(1-6)." << endl;
            //throw invalid_argument("Invalid input. Please enter a valid non-negative number.");
        } else {
            break;
        }
    }
    return number;
}
int get_policynumber(int policyNumber){
    cout << "Policy Number: ";
    policyNumber = getValidNonNegativeNumber();
    return policyNumber;
}
int get_premium(double premium){
    cout << "Premium: ";
    premium = getValidNonNegativeNumber();
    return premium;
}
double readMotorPremiumValues(string vehicleModel){
    ifstream premiumFile("motorpremium.txt");
    string model;
    double premium;
    while (premiumFile >> model >> premium) {
        if (model == vehicleModel)  
            return premium;
    }
}
double readHousePremiumValues(string propertyType){
    ifstream premiumFile("housepremium.txt");
    string type;
    double premium;
    while (premiumFile >> type >> premium) {
        if (type == propertyType)  
            return premium;
    }
}
string toUpperCase(string str){
    string temp="";
    for(int i=0;i<str.length();i++)
        temp+=toupper(str[i]);
    return temp;
}
string getValidModel() {
    string model;
    while (true) {
        cin >> model;
        model=toUpperCase(model);
        if (model!="SUV" && model!="SEDAN" && model!="HATCHBACK" && model!="TWO-WHEELER") {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid input. Please enter a valid model." << endl;
            //throw invalid_argument("Invalid input. Please enter a valid non-negative number.");
        } else {
            break;
        }
    }
    return model;
}
string getValidType() {
    string type;
    while (true) {
        cin >> type;
        type=toUpperCase(type);
        if (type!="COMMERCIAL" && type!="PERSONAL") {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid input. Please enter a valid type." << endl;
            //throw invalid_argument("Invalid input. Please enter a valid non-negative number.");
        } else {
            break;
        }
    }
    return type;
}

//MADHUSUDHAN, CHIDANAND
int main() {
    using namespace Insurance;
    int choice;
    vector<Policy*> policies;
    do {
        try{
            cout << "\n***** Insurance Policy System Menu *****" << endl;
            cout << "1. Add Motor Insurance Policy" << endl;
            cout << "2. Add Life Insurance Policy" << endl;
            cout << "3. Add House Insurance Policy" << endl;
            cout << "4. Display All Policies" << endl;
            cout << "5. Calculate Total Coverage" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your choice (1-6): ";
            choice=getValidChoice();

            switch (choice) {
                case 1: {
                    int policyNumber;
                    double premium;
                    string vehicleModel;
                    policyNumber=get_policynumber(policyNumber);
                    cout << "Vehicle Model(SUV, SEDAN, HATCHBACK, 2-WHEELER): ";
                    vehicleModel=getValidModel();
                    premium=readMotorPremiumValues(vehicleModel);
                    policies.push_back(new MotorInsurance(policyNumber, premium, vehicleModel));
                    break;
                }

                case 2: {
                    int policyNumber;
                    double premium;
                    int policyTerm;
                    cout << "Enter Life Insurance Policy details:" << endl;
                    policyNumber=get_policynumber(policyNumber);
                    premium=get_premium(premium);
                    cout << "Policy Term (in years): ";
                    policyTerm = getValidNonNegativeNumber();
                    policies.push_back(new LifeInsurance(policyNumber, premium, policyTerm));
                    break;
                }

                case 3: {
                    int policyNumber;
                    double premium;
                    string propertyType;
                    cout << "Enter House Insurance Policy details:" << endl;
                    policyNumber=get_policynumber(policyNumber);
                    cout << "Property Type(PERSONAL, COMMERCIAL): ";
                    propertyType=getValidType();
                    premium=readHousePremiumValues(propertyType);
                    policies.push_back(new HouseInsurance(policyNumber, premium, propertyType));
                    break;
                }

                case 4:
                    cout << "Check output.txt" <<endl;
                    outfile << "\n===== Displaying All Policies =====" << endl;
                    for (const auto& policy : policies) {
                        policy->displayDetails();
                    }
                    break;

                case 5:
                    cout << "Check output.txt" <<endl;
                    outfile << "Total Coverage: Rs." << calculateTotalCoverage(policies) << endl;
                    break;

                case 6:
                    cout << "Exiting the Insurance Policy System. Goodbye!" << endl;
                    break;

                default:
                    cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            }
            }
            catch (const exception& ex) {
            cerr << "Error: " << ex.what() << endl;
        }
    } while (choice != 6);
    for (const auto& policy : policies) {
        delete policy;
    }
    outfile.close();
    return 0;
}
