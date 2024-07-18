/**
 * @file code.cpp
 * @author Nguyen Trung Hieu (Hieu.NT234009@sis.hust.edu.vn)
 * @brief He thong quan ly trung tam tiem chung
 * @version 1.0
 * @date 2024-06-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/* Khai bao class cho Date */
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int _day = 0, int _month = 0, int _year = 0) {
        day = _day;
        month = _month;
        year = _year;
    }

    int getDay() const {
        return day;
    }
    void setDay(int _day) {
        day = _day;
    }

    int getMonth() const {
        return month;
    }
    void setMonth(int _month) {
        month = _month;
    }

    int getYear() const {
        return year;
    }
    void setYear(int _year) {
        year = _year;
    }

    bool isValid() const {
        if (year < 1) // Kiem tra nam
            return false;
        if (month < 1 || month > 12) // Kiem tra thang
            return false;
        int daysInmonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // So ngay trong thang
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) // Kiem tra nam nhuan
        {
            daysInmonth[1] = 29;
        }
        if (day < 1 || day > daysInmonth[month - 1]) // Kiem tra so ngay trong thang
            return false;
        return true;
    }

    friend ostream& operator<<(ostream& os, const Date& date) {
        os << date.year << "-" << date.month << "-" << date.day;
        return os;
    }
};

/* Khai bao class cho Vaccine */
class Vaccine {
private:
    string vacName;
    string ingredients; // thanh phan cua vac xin
    string target; // doi tuong su dung vac xin
    string guide; // huong dan su dung
    int inventory; // luong ton kho
    Date expiryDate; // han su dung

public:
    Vaccine(string _vacName = "", string _ingredients = "", string _target = "", string _guide = "", int _inventory = 0, Date _expiryDate = Date()) {
        vacName = _vacName;
        ingredients = _ingredients;
        target = _target;
        guide = _guide;
        inventory = _inventory;
        expiryDate = _expiryDate;
    }

    string getVacName() const {
        return vacName;
    }
    void setVacName(const string& _vacName) {
        vacName = _vacName;
    }

    string getIngredients() const {
        return ingredients;
    }
    void setIngredients(const string& _ingredients) {
        ingredients = _ingredients;
    }

    string getTarget() const {
        return target;
    }
    void setTarget(const string& _target) {
        target = _target;
    }

    string getGuide() const {
        return guide;
    }
    void setGuide(const string& _guide) {
        guide = _guide;
    }

    int getInventory() const {
        return inventory;
    }
    void setInventory(int _inventory) {
        inventory = _inventory;
    }

    Date getExpiryDate() const {
        return expiryDate;
    }
    void setExpiryDate(const Date& _expiryDate) {
        expiryDate = _expiryDate;
    }

    // Ham nhap thong tin vac xin
    void input() {
        cout << "Nhap ten loai vaccine: ";
        getline(cin, vacName);
        cout << "Nhap thanh phan cua vaccine: ";
        getline(cin, ingredients);
        cout << "Nhap doi tuong su dung: ";
        getline(cin, target);
        cout << "Nhap huong dan su dung: ";
        getline(cin, guide);
        while (true) {
            cout << "Nhap so luong thuoc ton kho: ";
            cin >> inventory;
            if (inventory > 0) {
                break;
            } else {
                cout << "Vui long nhap so luong thuoc hop le" << endl;
            }
        }
        while (true) {
            int year, month, day;
            cout << "Nhap han su dung (YYYY MM DD): ";
            cin >> year >> month >> day;
            expiryDate = Date(day, month, year);
            if (expiryDate.isValid()) {
                break;
            } else {
                cout << "Xin nhap ngay thang nam hop le" << endl;
            }
        }
        cin.ignore(); // Clear the newline character from the input buffer
    }

    // Ham hien thi thong tin vac xin
    void display() const {
        cout << "Ten loai vaccine: " << vacName << endl;
        cout << "Thanh phan vaccine: " << ingredients << endl;
        cout << "Doi tuong su dung: " << target << endl;
        cout << "Huong dan su dung: " << guide << endl;
        cout << "Luong ton kho: " << inventory << endl;
        cout << "Han su dung: " << expiryDate << endl;
    }
     // Ham so sanh han su dung cua vac xin
    bool operator<(const Vaccine& other) const {
        return expiryDate.getYear() < other.expiryDate.getYear() || 
               (expiryDate.getYear() == other.expiryDate.getYear() && expiryDate.getMonth() < other.expiryDate.getMonth()) || 
               (expiryDate.getYear() == other.expiryDate.getYear() && expiryDate.getMonth() == other.expiryDate.getMonth() && expiryDate.getDay() < other.expiryDate.getDay());
    }
};

// Ham tim kiem vac xin qua ten
void searchVac(const vector<Vaccine>& vaccines, const string& vacSearch) {
    bool found = false;
    for (size_t i = 0; i < vaccines.size(); i++) {
        if (vaccines[i].getVacName() == vacSearch) {
            cout << "So thu tu: " << i + 1 << endl;
            vaccines[i].display();
            found = true;
        }
    }
    if (!found) {
        cout << "Khong tim thay thong tin vac xin co ten tuong ung" << endl;
    }
}

// Ham sap xep vac xin theo so luong
void sortInven(vector<Vaccine>& vaccines) {
    sort(vaccines.begin(), vaccines.end(), [](const Vaccine& a, const Vaccine& b) {
        return a.getInventory() < b.getInventory();
    });
    for (const auto& vaccine : vaccines) {
        cout << "Vac xin: " << vaccine.getVacName() << " - So luong: " << vaccine.getInventory() << endl;
    }
}

// Ham sap xep vac xin theo han su dung
void searchExpiry(vector<Vaccine>& vaccines) {
    sort(vaccines.begin(), vaccines.end());
    for (const auto& vaccine : vaccines) {
        cout << "Vac xin: " << vaccine.getVacName() << " - Han su dung: " << vaccine.getExpiryDate() << endl;
    }
}

// Ham them vac xin moi
void addVac(vector<Vaccine>& vaccines, int newAddvac) {
    for (int i = 0; i < newAddvac; i++) {
        Vaccine newVaccine;
        cout << "Nhap thong tin cho vac xin thu " << vaccines.size() + 1 << ":" << endl;
        newVaccine.input();
        vaccines.push_back(newVaccine);
    }
}

// Ham xoa vac xin
void deleteVac(vector<Vaccine>& vaccines, int index) { // index la so thu tu của vac xin
    if (index >= 1 && index <= vaccines.size()) {
        vaccines.erase(vaccines.begin() + index - 1);
    } else {
        cout << "Chi so khong hop le" << endl;
    }
}

// Ham thay doi thong tin vac xin
void changeVac(vector<Vaccine>& vaccines, int index) {
    if (index >= 1 && index <= vaccines.size()) {
        Vaccine updateVac;
        cout << "Nhap thong tin muon cap nhat thanh:" << endl;
        updateVac.input();
        vaccines[index - 1] = updateVac;
    } else {
        cout << "Chi so khong hop le" << endl;
    }
}

int main() {
    int numofVac;
    cout << "Nhap so luong loai vaccine: ";
    cin >> numofVac;
    cin.ignore();

    vector<Vaccine> vaccines(numofVac);
    for (int i = 0; i < numofVac; i++) {
        cout << "Nhap thong tin loai vaccine thu " << i + 1 << ":" << endl;
        vaccines[i].input();
    }

    int choice;
    char continueInput;
    string vacSearch;
    int newAddvac, index;

    do {
        cout << "\n1. Tim kiem vac xin qua ten (Nhap ban phim so 1)"
             << "\n2. Sap xep vac xin theo so luong ton kho (Nhap ban phim so 2)"
             << "\n3. Sap xep vac xin theo han su dung (Nhap ban phim so 3)"
             << "\n4. Nhap thong tin them vac xin moi (Nhap ban phim so 4)"
             << "\n5. Xoa 1 vac xin (Nhap ban phim so 5)"
             << "\n6. Thay doi thong tin vac xin (Nhap ban phim so 6)"
             << "\nNhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Nhap ten vac xin can tim: ";
                getline(cin, vacSearch);
                searchVac(vaccines, vacSearch);
                break;
            case 2:
                sortInven(vaccines);
                break;
            case 3:
                searchExpiry(vaccines);
                break;
            case 4:
                cout << "Nhap so luong loai vac xin moi can them: ";
                cin >> newAddvac;
                cin.ignore();
                addVac(vaccines, newAddvac);
                break;
            case 5:
                cout << "Nhap so thu tu vac xin can xoa: ";
                cin >> index;
                deleteVac(vaccines, index);
                break;
            case 6:
                cout << "Nhap so thu tu vac xin can thay doi thong tin: ";
                cin >> index;
                changeVac(vaccines, index);
                break;
            default:
                cout << "Lua chon khong hop le, vui long thu lai." << endl;
        }

        cout << "\nBan co muon tiep tuc khong? (Y/N): ";
        cin >> continueInput;
        cin.ignore();

    } while (continueInput == 'y' || continueInput == 'Y');

    return 0;
}
