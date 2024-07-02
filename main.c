#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>
typedef struct
{
    char date[15];
} Date1;

typedef struct
{
    int ID;
    char Ten[50];
    Date1 birth;
    char h[20];
} inforBN;

typedef struct
{
    char TenVC[20];
    int countVC;
    Date1 date;
} inforNX;
typedef struct {
    int day;
    int month;
    int year;
} Date;

/* Hàm kiểm tra ngày tháng năm hợp lệ */
int isValidDate(const Date *date) {
    if (date->year < 1) // Kiểm tra năm
        return 0;
    if (date->month < 1 || date->month > 12) // Kiểm tra tháng
        return 0;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Số ngày trong tháng
    if ((date->year % 4 == 0 && date->year % 100 != 0) || (date->year % 400 == 0)) // Kiểm tra năm nhuận
        daysInMonth[1] = 29;
    if (date->day < 1 || date->day > daysInMonth[date->month - 1]) // Kiểm tra số ngày trong tháng
        return 0;
    return 1;
}

/* Hàm hiển thị ngày tháng năm */
void displayDate(const Date *date) {
    printf("%d-%d-%d", date->year, date->month, date->day);
}

/* Khai báo struct cho Vaccine */
typedef struct {
    char vacName[100];
    char ingredients[100]; // thành phần của vaccine
    char target[100]; // đối tượng sử dụng vaccine
    char guide[100]; // hướng dẫn sử dụng
    int inventory; // lượng tồn kho
    Date expiryDate; // hạn sử dụng
} Vaccine;

/* Hàm nhập thông tin vaccine */
void inputVaccine(Vaccine *vaccine) {
    printf("Nhap ten loai vaccine: ");
    fflush(stdin);
    gets(vaccine->vacName);
    printf("Nhap thanh phan cua vaccine: ");
    fflush(stdin);
    gets(vaccine->ingredients);
    printf("Nhap doi tuong su dung: ");
    fflush(stdin);
    gets(vaccine->target);
    printf("Nhap huong dan su dung: ");
    fflush(stdin);
    gets(vaccine->guide);
    while (1) {
        printf("Nhap so luong ton kho: ");
        scanf("%d", &vaccine->inventory);
        if (vaccine->inventory > 0) {
            break;
        } else {
            printf("Vui long nhap so luong ton kho hop le\n");
        }
    }
    while (1) {
        int year, month, day;
        printf("Nhap han su dung (YYYY MM DD): ");
        scanf("%d %d %d", &year, &month, &day);
        vaccine->expiryDate.day = day;
        vaccine->expiryDate.month = month;
        vaccine->expiryDate.year = year;
        if (isValidDate(&vaccine->expiryDate)) {
            break;
        } else {
            printf("Xin nhap ngay thang nam hop le\n");
        }
    }
    getchar(); // Xóa ký tự '\n' còn lại trong buffer đầu vào
}

/* Hàm hiển thị thông tin vaccine */
void displayVaccine(const Vaccine *vaccine) {
    printf("Ten loai vaccine: %s\n", vaccine->vacName);
    printf("Thanh phan vaccine: %s\n", vaccine->ingredients);
    printf("Doi tuong su dung: %s\n", vaccine->target);
    printf("Huong dan su dung: %s\n", vaccine->guide);
    printf("Luong ton kho: %d\n", vaccine->inventory);
    printf("Han su dung: ");
    displayDate(&vaccine->expiryDate);
    printf("\n");
}

/* Hàm so sánh hạn sử dụng của vaccine */
int compareExpiry(const Vaccine *a, const Vaccine *b) {
    if (a->expiryDate.year < b->expiryDate.year ||
        (a->expiryDate.year == b->expiryDate.year && a->expiryDate.month < b->expiryDate.month) ||
        (a->expiryDate.year == b->expiryDate.year && a->expiryDate.month == b->expiryDate.month && a->expiryDate.day < b->expiryDate.day)) {
        return -1;
    } else if (a->expiryDate.year == b->expiryDate.year && a->expiryDate.month == b->expiryDate.month && a->expiryDate.day == b->expiryDate.day) {
        return 0;
    } else {
        return 1;
    }
}

/* Hàm tìm kiếm vaccine theo tên */
void searchVaccine(const Vaccine vaccines[], int numVaccines, const char *vacSearch) {
    int found = 0;
    for (int i = 0; i < numVaccines; i++) {
        if (strcmp(vaccines[i].vacName, vacSearch) == 0) {
            printf("So thu tu: %d\n", i + 1);
            displayVaccine(&vaccines[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay thong tin vac xin co ten tuong ung\n");
    }
}

/* Hàm sắp xếp vaccine theo số lượng tồn kho */
void sortByInventory(Vaccine vaccines[], int numVaccines) {
    for (int i = 0; i < numVaccines - 1; i++) {
        for (int j = i + 1; j < numVaccines; j++) {
            if (vaccines[i].inventory > vaccines[j].inventory) {
                Vaccine temp = vaccines[i];
                vaccines[i] = vaccines[j];
                vaccines[j] = temp;
            }
        }
    }
    for (int i = 0; i < numVaccines; i++) {
        printf("Vac xin: %s - So luong: %d\n", vaccines[i].vacName, vaccines[i].inventory);
    }
}

/* Hàm sắp xếp vaccine theo hạn sử dụng */
void sortByExpiry(Vaccine vaccines[], int numVaccines) {
    for (int i = 0; i < numVaccines - 1; i++) {
        for (int j = i + 1; j < numVaccines; j++) {
            if (compareExpiry(&vaccines[i], &vaccines[j]) > 0) {
                Vaccine temp = vaccines[i];
                vaccines[i] = vaccines[j];
                vaccines[j] = temp;
            }
        }
    }
    for (int i = 0; i < numVaccines; i++) {
        printf("Vac xin: %s - Han su dung: ", vaccines[i].vacName);
        displayDate(&vaccines[i].expiryDate);
        printf("\n");
    }
}

/* Hàm thêm vaccine mới */
void addVaccine(Vaccine vaccines[], int *numVaccines, int newAddVac) {
    for (int i = 0; i < newAddVac; i++) {
        printf("Nhap thong tin cho vac xin thu %d:\n", *numVaccines + 1);
        inputVaccine(&vaccines[*numVaccines]);
        (*numVaccines)++;
    }
}

/* Hàm xóa vaccine */
void deleteVaccine(Vaccine vaccines[], int *numVaccines, int index) {
    if (index >= 1 && index <= *numVaccines) {
        for (int i = index - 1; i < *numVaccines - 1; i++) {
            vaccines[i] = vaccines[i + 1];
        }
        (*numVaccines)--;
    } else {
        printf("Chi so khong hop le\n");
    }
}

/* Hàm thay đổi thông tin vaccine */
void changeVaccine(Vaccine vaccines[], int numVaccines, int index) {
    if (index >= 1 && index <= numVaccines) {
        printf("Nhap thong tin muon cap nhat thanh:\n");
        inputVaccine(&vaccines[index - 1]);
    } else {
        printf("Chi so khong hop le\n");
    }
}

/* Khai báo struct cho Hồ sơ tiêm chủng */
typedef struct {
    char tk[100];
    char mk[100];
    int ID;
    char name[100]; // Họ và tên
    int day, month, year; // Ngày tháng năm sinh
    char sex[100]; // Giới tính
    char address[100]; // Địa chỉ
    char numPhone[100]; // Số điện thoại
} PersonalProfile;

/* Khai báo struct cho Thông tin y tế */
typedef struct {
    char medicalHistory[100]; // Tiền sử bệnh lý
    int vaccinationHistory; // Tiền sử tiêm chủng (các loại vaccine đã tiêm)
} HealthInfo;

/* Khai báo struct cho Lịch sử tiêm chủng */
typedef struct {
    char nameOfVaccine[100]; // Danh sách các loại vaccine đã tiêm
    int dayT, monthT, yearT; // Ngày tiêm
    char postVaccinationReaction[100]; // Phản ứng sau tiêm
} VaccinationHistory;

/* Khai báo struct cho Hồ sơ tiêm chủng */
typedef struct {
    PersonalProfile personalInfo;
    HealthInfo healthInfo;
    VaccinationHistory vaccinationInfo;
} VaccinationProfile;

/* Hàm nhập thông tin hồ sơ cá nhân */
void inputPersonalProfile(VaccinationProfile *profile) {
    //printf("Nhap ten tai khoan: ");
    //fflush(stdin);
    //gets(profile->personalInfo.tk);
    //printf("Nhap mat khau: ");
    //fflush(stdin);
    //gets(profile->personalInfo.mk);
    printf("Nhap ID: ");
    scanf("%d", &profile->personalInfo.ID);
    printf("Nhap ho va ten: ");
    fflush(stdin);
    gets(profile->personalInfo.name);
    printf("Nhap ngay thang nam sinh: ");
    scanf("%d %d %d", &profile->personalInfo.day, &profile->personalInfo.month, &profile->personalInfo.year);
    printf("Nhap gioi tinh: ");
    fflush(stdin);
    gets(profile->personalInfo.sex);
    printf("Nhap dia chi: ");
    fflush(stdin);
    gets(profile->personalInfo.address);
    printf("Nhap so dien thoai: ");
    fflush(stdin);
    gets(profile->personalInfo.numPhone);
}

/* Hàm hiển thị thông tin hồ sơ cá nhân */
void displayPersonalProfile(const PersonalProfile *profile) {
    //printf("Ten tai khoan: %s\n", profile->tk);
    //printf("Mat khau: %s\n", profile->mk);
    printf("ID: %d\n", profile->ID);
    printf("Ho va ten: %s\n", profile->name);
    printf("Ngay thang nam sinh: %d/%d/%d\n", profile->day, profile->month, profile->year);
    printf("Gioi tinh: %s\n", profile->sex);
    printf("Dia chi: %s\n", profile->address);
    printf("So dien thoai: %s\n", profile->numPhone);
}

/* Hàm nhập thông tin y tế */
void inputHealthInfo(HealthInfo *healthInfo) {
    printf("Nhap tien su benh ly: ");
    fflush(stdin);
    gets(healthInfo->medicalHistory);
    printf("Nhap tien su tiem chung: ");
    scanf("%d", &healthInfo->vaccinationHistory);
}

/* Hàm hiển thị thông tin y tế */
void displayHealthInfo(const HealthInfo *healthInfo) {
    printf("Tien su benh ly: %s\n", healthInfo->medicalHistory);
    printf("Tien su tiem chung: %d\n", healthInfo->vaccinationHistory);
}

/* Hàm nhập thông tin tiêm chủng */
void inputVaccinationHistory(VaccinationHistory *vaccinationHistory) {
    printf("Nhap ten vaccine da tiem: ");
    fflush(stdin);
    gets(vaccinationHistory->nameOfVaccine);
    printf("Nhap ngay tiem: ");
    scanf("%d %d %d", &vaccinationHistory->dayT, &vaccinationHistory->monthT, &vaccinationHistory->yearT);
    printf("Nhap phan ung sau tiem: ");
    fflush(stdin);
    gets(vaccinationHistory->postVaccinationReaction);
}

/* Hàm hiển thị thông tin tiêm chủng */
void displayVaccinationHistory(const VaccinationHistory *vaccinationHistory) {
    printf("Ten vaccine da tiem: %s\n", vaccinationHistory->nameOfVaccine);
    printf("Ngay tiem: %d/%d/%d\n", vaccinationHistory->dayT, vaccinationHistory->monthT, vaccinationHistory->yearT);
    printf("Phan ung sau tiem: %s\n", vaccinationHistory->postVaccinationReaction);
}
void processString(char* str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = tolower(str[i]);
        }
    }
    str[j] = '\0';
}
int main()
{
    int option, m, p, a;
    //char position[10];
    char nameacc[50];
    char password[50];
    //inforBN* BenhNhan = NULL;
    //inforNX* Vaccine = NULL;
    //int numBN = 0, numVC = 0;

    printf("Ban la benh nhan hay nhan vien?");
    printf("\n1. Nhan vien");
    printf("\n2. Benh nhan");
    //gets(position);
    printf("\n");
    scanf("%d",&a);
    fflush(stdin);


    if(a==1)
    {
    Vaccine vaccines[100];
    int numVaccines = 0;
    int choice;
    VaccinationProfile profile;
    TEST1:
    printf("\nTen tai khoan: "); scanf("%s", nameacc);
    fflush(stdin);
    printf("Mat khau: "); scanf("%s", password);
    if((nameacc=="buitrunghieu"&&password=="buitrunghieu")||(nameacc=="nguyentrunghieu"&&password=="nguyentrunghieu")||(nameacc=="trantrunghieu"&&password=="trantrunghieu")||(nameacc=="vuhoanghiep"&&password=="vuhoanghiep")){
    while (1) {
        Vaccine updateVac;
    printf("Nhap so luong loai vaccine: ");
    scanf("%d", &numofVac);
    Vaccine *vaccine = (Vaccine *)malloc(numofVac*sizeof(Vaccine));
    for(int i = 0; i < numofVac; i ++)
    {
        printf("\nNhap thong loai vaccine thu %d: ", i + 1);
        inputVac(&vaccine[i]);
    }
        printf("------ MENU ------\n");
        printf("1. Nhap thong tin ca nhan\n");
        printf("2. Nhap thong tin y te\n");
        printf("3. Nhap thong tin tiem chung\n");
        printf("4. Hien thi ho so ca nhan\n");
        printf("5. Hien thi thong tin y te\n");
        printf("6. Hien thi thong tin tiem chung\n");
        printf("7. Nhap thong tin vaccine moi\n");
        printf("8. Hien thi danh sach vaccine\n");
        printf("9. Tim kiem vaccine theo ten\n");
        printf("10. Sap xep vaccine theo so luong\n");
        printf("11. Sap xep vaccine theo han su dung\n");
        printf("12. Them vaccine moi\n");
        printf("13. Xoa vaccine\n");
        printf("14. Thay doi thong tin vaccine\n");
        printf("15. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputPersonalProfile(&profile);
                break;
            case 2:
                inputHealthInfo(&profile.healthInfo);
                break;
            case 3:
                inputVaccinationHistory(&profile.vaccinationInfo);
                break;
            case 4:
                displayPersonalProfile(&profile.personalInfo);
                break;
            case 5:
                displayHealthInfo(&profile.healthInfo);
                break;
            case 6:
                displayVaccinationHistory(&profile.vaccinationInfo);
                break;
            case 7:
            {
                int numVac;
                printf("Nhap so luong vaccine muon nhap: ");
                scanf("%d", &numVac);
                getchar(); // Xóa ký tự '\n' còn lại trong buffer đầu vào
                addVaccine(vaccines, &numVaccines, numVac);
                break;
            }
            case 8:
                for (int i = 0; i < numVaccines; i++) {
                    printf("So thu tu: %d\n", i + 1);
                    displayVaccine(&vaccines[i]);
                }
                break;
            case 9:
            {
                char vacSearch[100];
                printf("Nhap ten vaccine can tim: ");
                getchar(); // Xóa ký tự '\n' còn lại trong buffer đầu vào
                gets(vacSearch);
                searchVaccine(vaccines, numVaccines, vacSearch);
                break;
            }
            case 10:
                sortByInventory(vaccines, numVaccines);
                break;
            case 11:
                sortByExpiry(vaccines, numVaccines);
                break;
            case 12:
            {
                int newAddVac;
                printf("Nhap so luong vaccine muon them: ");
                scanf("%d", &newAddVac);
                getchar(); // Xóa ký tự '\n' còn lại trong buffer đầu vào
                addVaccine(vaccines, &numVaccines, newAddVac);
                break;
            }
            case 13:
            {
                int delIndex;
                printf("Nhap so thu tu vaccine muon xoa: ");
                scanf("%d", &delIndex);
                deleteVaccine(vaccines, &numVaccines, delIndex);
                break;
            }
            case 14:
            {
                int updateIndex;
                printf("Nhap so thu tu vaccine muon thay doi: ");
                scanf("%d", &updateIndex);
                changeVaccine(vaccines, numVaccines, updateIndex);
                break;
            }
            case 15:
                printf("Thoat chuong trinh\n");
                exit(0);
            default:
                printf("Lua chon khong hop le, vui long nhap lai\n");
        }
    }}
    else
    {
        printf("\nTen tai khoan hoac mat khau ban vua nhap khong dung. Vui long ban nhap lai!");
        goto TEST1;
    }
    }
    else
    if(a==2)
{
    char nameacc[50];
    char password[50];
    char ten[50],ten1[50];
    printf("\nHo va ten :");
    fgets(ten, sizeof(ten), stdin);
    processString(ten);
    TEST1:
    printf("\nTen tai khoan: "); scanf("%s", nameacc);
    fflush(stdin);
    printf("Mat khau: "); scanf("%s", password);
    if(nameacc==ten&&password==ten){
    printf("------ MENU ------\n");
    printf("\n1. Cap nhap thong tin");
    printf("2. Nhap thong tin y te\n");
    printf("3. Nhap thong tin tiem chung\n");
    printf("4. Hien thi ho so ca nhan\n");
    printf("5. Hien thi thong tin y te\n");
    printf("6. Hien thi thong tin tiem chung\n");
    printf("7. Thoat");
    printf("\nVui long nhap lua chon cua ban: ");
    //printf("\n");
    scanf("%d", &option);

    switch(option)
    {
    case 1: {
    int ID;
    char Ten[50];
    Date birth;
    char home[20];

    printf("\n  -Ma benh nhan: ");
    scanf("%d", &ID);
    getchar(); // Clear newline character left in the input buffer

    printf("  -Ten benh nhan: ");
    fgets(Ten, 50, stdin);
    printf("  -Que quan: ");
    fgets(home, 20, stdin);
    printf("\nThong tin benh nhan sau khi chinh sua:\n");
    printf("  -Ma benh nhan: %d\n", ID);
    printf("  -Ten benh nhan: %s", Ten);
    printf("  -Que quan: %s", home);
    printf("Chuc ban mot ngay tot lanh.\n");
    break;
}

    case 2:
    inputHealthInfo(&profile.healthInfo);
    break;
    case 3:
    inputVaccinationHistory(&profile.vaccinationInfo);
    break;
    case 4:
    displayPersonalProfile(&profile.personalInfo);
    break;
    case 5:
    displayHealthInfo(&profile.healthInfo);
    break;
    case 6:
    displayVaccinationHistory(&profile.vaccinationInfo);
    break;
    case 7:
     printf("Chuc ban mot ngay tot lanh.");
     return 0;
    }
    }
    else
    {
        printf("\nTen tai khoan hoac mat khau ban vua nhap khong dung. Vui long ban nhap lai!");
        goto TEST2;
    }
    }


    return 0;
}
