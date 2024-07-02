#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <bits/stdc++.h>
#include <cctype>
#include <limits>
using namespace std;

typedef class
{
    char date[15];
} Date1;

typedef class
{
    int ID;
    char Ten[50];
    Date1 birth;
    char h[20];
} inforBN;

typedef class
{
    char TenVC[20];
    int countVC;
    Date1 date;
} inforNX;

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
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // So ngay trong thang
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) // Kiem tra nam nhuan
        {
            daysInMonth[1] = 29;
        }
        if (day < 1 || day > daysInMonth[month - 1]) // Kiem tra so ngay trong thang
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

// Khai bao struct cho Ho so ca nhan
typedef struct {
    char tk[100];
    char mk[100];
    int ID;
    char name[100]; // Ho va ten
    int day, month, year; // Ngay thang nam sinh
    char sex[100]; // Gioi tinh
    char address[100]; // Dia chi
    char numPhone[100]; // So dien thoai
} caNhan;

// Khai bao struct cho Thong tin y te
typedef struct {
    char tienBenhLy[100]; // Tien su benh ly
    int tienTiemChung; // Tien su tiem chung (cac loai vac xin da tiem)
} yTe;

// Khai bao struct cho Lich su tiem chung
typedef struct {
    char nameOfVaccine[100]; // Danh sach cac loai vac xin da tiem
    int dayT, monthT, yearT; // Ngay tiem
    char phanUngSauTiem[100]; // Phan ung sau tiem
} tiemChung;

// Khai bao struct cho Ho so tiem chung
typedef struct {
    caNhan thongTin;
    yTe tT_yTe;
    tiemChung tT_tiemChung;
} HSTC;

// Ham nhap thong tin ho so ca nhan
void nhapHSCN(HSTC* hs) {
    //cout << "Nhap ten tai khoan: "; fflush(stdin); gets(hs->thongTin.tk);
    //cout << "Nhap mat khau: "; fflush(stdin); gets(hs->thongTin.mk);
    cout << "Nhap ID: "; cin >> hs->thongTin.ID;
    cout << "Nhap ho va ten: "; fflush(stdin); gets(hs->thongTin.name);
    cout << "Nhap ngay thang nam sinh: "; cin >> hs->thongTin.day >> hs->thongTin.month >> hs->thongTin.year;
    cout << "Nhap gioi tinh: "; fflush(stdin); gets(hs->thongTin.sex);
    cout << "Nhap dia chi: "; fflush(stdin); gets(hs->thongTin.address);
    cout << "Nhap so dien thoai: "; fflush(stdin); gets(hs->thongTin.numPhone);
}

// Ham nhap thong tin y te
void nhapTTyTe(HSTC* hs) {
    cout << "Nhap tien su benh ly: "; fflush(stdin); gets(hs->tT_yTe.tienBenhLy);
    cout << "Nhap tien su tiem chung: "; cin >> hs->tT_yTe.tienTiemChung;
}

// Ham nhap thong tin tiem chung
void nhapTTC(HSTC* hs) {
    cout << "Nhap ten vac xin da tiem: "; fflush(stdin); gets(hs->tT_tiemChung.nameOfVaccine);
    cout << "Nhap ngay tiem: "; cin >> hs->tT_tiemChung.dayT >> hs->tT_tiemChung.monthT >> hs->tT_tiemChung.yearT;
    cout << "Nhap phan ung sau tiem: "; fflush(stdin); gets(hs->tT_tiemChung.phanUngSauTiem);
}

// Ham hien thi ho so ca nhan
void hienThiHSCN(HSTC hs) {
    //cout << "Ten tai khoan: " << hs.thongTin.tk << endl;
    //cout << "Mat khau: " << hs.thongTin.mk << endl;
    cout << "ID: " << hs.thongTin.ID << endl;
    cout << "Ho va ten: " << hs.thongTin.name << endl;
    cout << "Ngay thang nam sinh: " << hs.thongTin.day << "/" << hs.thongTin.month << "/" << hs.thongTin.year << endl;
    cout << "Gioi tinh: " << hs.thongTin.sex << endl;
    cout << "Dia chi: " << hs.thongTin.address << endl;
    cout << "So dien thoai: " << hs.thongTin.numPhone << endl;
}

// Ham hien thi thong tin y te
void hienThiTTyTe(HSTC hs) {
    cout << "Tien su benh ly: " << hs.tT_yTe.tienBenhLy << endl;
    cout << "Tien su tiem chung: " << hs.tT_yTe.tienTiemChung << endl;
}

// Ham hien thi thong tin tiem chung
void hienThiTTC(HSTC hs) {
    cout << "Ten vac xin da tiem: " << hs.tT_tiemChung.nameOfVaccine << endl;
    cout << "Ngay tiem: " << hs.tT_tiemChung.dayT << "/" << hs.tT_tiemChung.monthT << "/" << hs.tT_tiemChung.yearT << endl;
    cout << "Phan ung sau tiem: " << hs.tT_tiemChung.phanUngSauTiem << endl;
}
string toLowerCaseAndRemoveSpaces(const string& input) {
    string output;
    for (char ch : input) {
        if (!isspace(ch)) {
            output += tolower(ch);
        }
    }
    return output;
}

int main()
{
    int option, m, p, a;
    string nameacc;
    string password;
    //inforBN *BenhNhan = NULL;
    //inforNX *Vaccine = NULL;
    int numBN = 0, numVC = 0;

    cout << "Ban la benh nhan hay nhan vien?";
    cout << "\n1. Nhan vien";
    cout << "\n2. Benh nhan";
    cout << "\n";
    cin >> a;
    cin.ignore();
    if (a==1)
    {
    TEST1:
    cout << "\nTen tai khoan: ";
    cin >> nameacc;
    cout << "Mat khau: ";
    cin >> password;
    if((nameacc=="buitrunghieu"&&password=="buitrunghieu")||(nameacc=="nguyentrunghieu"&&password=="nguyentrunghieu")||(nameacc=="trantrunghieu"&&password=="trantrunghieu")||(nameacc=="vuhoanghiep"&&password=="vuhoanghiep")){
    int numofVac;
    cout << "Nhap so luong loai vaccine: ";
    cin >> numofVac;
    cin.ignore();

    vector<Vaccine> vaccines(numofVac);
    for (int i = 0; i < numofVac; i++) {
        cout << "Nhap thong tin loai vaccine thu " << i + 1 << ":" << endl;
        vaccines[i].input();
    }
        //vector<Vaccine> vaccines;
    int choice;
    HSTC hs;
    while (true) {
        cout << "------ MENU ------" << endl;
        cout << "1. Nhap thong tin ca nhan" << endl;
        cout << "2. Nhap thong tin y te" << endl;
        cout << "3. Nhap thong tin tiem chung" << endl;
        cout << "4. Hien thi ho so ca nhan" << endl;
        cout << "5. Hien thi thong tin y te" << endl;
        cout << "6. Hien thi thong tin tiem chung" << endl;
        cout << "7. Nhap thong tin vac xin moi" << endl;
        cout << "8. Hien thi danh sach vac xin" << endl;
        cout << "9. Tim kiem vac xin theo ten" << endl;
        cout << "10. Sap xep vac xin theo so luong" << endl;
        cout << "11. Sap xep vac xin theo han su dung" << endl;
        cout << "12. Them vac xin moi" << endl;
        cout << "13. Xoa vac xin" << endl;
        cout << "14. Thay doi thong tin vac xin" << endl;
        cout << "15. Thoat" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1:
                nhapHSCN(&hs);
                break;
            case 2:
                nhapTTyTe(&hs);
                break;
            case 3:
                nhapTTC(&hs);
                break;
            case 4:
                hienThiHSCN(hs);
                break;
            case 5:
                hienThiTTyTe(hs);
                break;
            case 6:
                hienThiTTC(hs);
                break;
            case 7:
            {
                int numVac;
                cout << "Nhap so luong vac xin muon nhap: ";
                cin >> numVac;
                cin.ignore(); // Clear the newline character from the input buffer
                for (int i = 0; i < numVac; i++) {
                    Vaccine vaccine;
                    vaccine.input();
                    vaccines.push_back(vaccine);
                }
                break;
            }
            case 8:
                for (size_t i = 0; i < vaccines.size(); i++) {
                    cout << "So thu tu: " << i + 1 << endl;
                    vaccines[i].display();
                }
                break;
            case 9:
            {
                string vacSearch;
                cout << "Nhap ten vac xin can tim: ";
                cin.ignore(); // Clear the newline character from the input buffer
                getline(cin, vacSearch);
                searchVac(vaccines, vacSearch);
                break;
            }
            case 10:
                sortInven(vaccines);
                break;
            case 11:
                searchExpiry(vaccines);
                break;
            case 12:
            {
                int newAddvac;
                cout << "Nhap so luong vac xin muon them: ";
                cin >> newAddvac;
                cin.ignore(); // Clear the newline character from the input buffer
                addVac(vaccines, newAddvac);
                break;
            }
            case 13:
            {
                int delIndex;
                cout << "Nhap so thu tu vac xin muon xoa: ";
                cin >> delIndex;
                deleteVac(vaccines, delIndex);
                break;
            }
            case 14:
            {
                int updateIndex;
                cout << "Nhap so thu tu vac xin muon thay doi: ";
                cin >> updateIndex;
                changeVac(vaccines, updateIndex);
                break;
            }
            case 15:
                cout << "Thoat chuong trinh" << endl;
                exit(0);
            default:
                cout << "Lua chon khong hop le, vui long nhap lai" << endl;
        }}}}
    else if (a==2)
    {
    HSTC hs;
       string nameacc;
    string password;
        string ten,ten1;
        cout<<"Ho va ten: ";
        getline(cin,ten);
        ten1=toLowerCaseAndRemoveSpaces(ten);
        TEST2:
    {cout << "\nTen tai khoan: ";
    cin >> nameacc;
    cout << "Mat khau: ";
    cin >> password;}
    int option;
        if(nameacc==ten1&&password==ten1)
    {cout << "Nhap ID: "; cin >> hs.thongTin.ID;
    cout << "Nhap ho va ten: "; fflush(stdin); gets(hs.thongTin.name);
    cout << "Nhap ngay thang nam sinh: "; cin >> hs.thongTin.day >> hs.thongTin.month >> hs.thongTin.year;
    cout << "Nhap gioi tinh: "; fflush(stdin); gets(hs.thongTin.sex);
    cout << "Nhap dia chi: "; fflush(stdin); gets(hs.thongTin.address);
    cout << "Nhap so dien thoai: "; fflush(stdin); gets(hs.thongTin.numPhone);
    cout<<endl;

        cout << "------ MENU ------" << endl;
        cout << "\nBan muon lam gi?";
        cout << "\n1. Cap nhap thong tin"<<endl;
        cout << "2. Nhap thong tin y te" << endl;
        cout << "3. Nhap thong tin tiem chung" << endl;
        cout << "4. Hien thi ho so ca nhan" << endl;
        cout << "5. Hien thi thong tin y te" << endl;
        cout << "6. Hien thi thong tin tiem chung" << endl;
        cout << "7. Thoat"<<endl;
        cout << "Vui long nhap lua chon cua ban: "<<endl;
        cin >> option;
    switch (option) {
        case 1: {
            int ID;
            char Ten[50];
            Date birth;
            char home[20];

            cout << "\n  -Ma benh nhan: ";
            cin >> ID;
            cin.ignore(); // Clear newline character left in the input buffer

            cout << "  -Ten benh nhan: ";
            cin.getline(Ten, 50);
            cout << "  -Que quan: ";
            cin.getline(home, 20);
            cout << "\nThong tin benh nhan sau khi chinh sua:" << endl;
            cout << "  -Ma benh nhan: " << ID << endl;
            cout << "  -Ten benh nhan: " << Ten << endl;
            cout << "  -Que quan: " << home << endl;
            cout << "Chuc ban mot ngay tot lanh." << endl;
            break;
        }
        case 2:
                {nhapTTyTe(&hs);
                break;}
            case 3:
                {nhapTTC(&hs);
                break;}
            case 4:
               {
               hienThiHSCN(hs);
                break;}
            case 5:
               {
                hienThiTTyTe(hs);
                break;}
            case 6:
                {hienThiTTC(hs);
                break;}
        case 7:{
         cout<<"Chuc ban mot ngay tot lanh."<<endl;
         break;
        }
    }

        }
         else
    {
        cout << "\nTen tai khoan hoac mat khau ban vua nhap khong dung. Vui long ban nhap lai!";
        goto TEST2;
    }
    }
    return 0;
}

