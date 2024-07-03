/**
 * @file code_nhombtl.cpp
 * @author Nguyen Trung Hieu (Hieu.NT234009@sis.hust.edu.vn)
 *         Vu Hoang Hiep (Hiep.VH234005@sis.hust.edu.vn)
 *         Bui Trung Hieu (Hieu.BT234006@sis.hust.edu.vn)
 *         Tran Trung Hieu (Hieu.TT234010@sis.hust.edu.vn)
 * @brief He thong quan ly tiem chung
 * @version 1.0
 * @date 2024-07-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include<stdio.h> // thu vien cho lenh nhap xuat du lieu
#include<string.h> // thu vien cho string
#include<stdlib.h> // thu vien cho cap phat mang dong trong C

/* KHAI BAO STRUCT */

/* PHAN NHAN VIEN NHAP KHO VAC XIN */
typedef struct
{
    int day;
	int month;
	int year;
} Date1;

typedef struct
{
    int  ID;
    char Ten[50];
    Date1 birth;
    char home[20];
} inforBN;

typedef struct
{
    char TenVC[20];
    int  countVC;
    Date1 birth;
} inforNX;

/* PHAN BENH NHAN */
// Ho so ca nhan:
typedef struct 
{
    char tk[100];
    char mk[100];
    int ID;
    char name[100]; // Ho va ten
    int day,month,year; // Ngay thang nam sinh
    char sex[100]; // Gioi tinh
    char address[100]; // Dia chi
    char numPhone[100]; // So dien thoai
}caNhan;

// Thong tin y te:
typedef struct  
{
    char tienBenhLy[100]; // Tien su benh ly
    int tienTiemChung; // Tien su tiem chung (Cac loai vac xin da tiem)
}yTe;

// Lich su tiem chung:
typedef struct   
{
    char nameOfVaccine[100]; // Danh sach cac loai vac xin da tiem
    int dayT,monthT,yearT; // Ngay tiem
    char DDT[100]; // Dia diem tiem
}LichSuTiemChung;

// Lich tiem chung:
typedef struct   
{
    char duKien[1000]; // Lich tiem chung du kien
    char nhacNho[1000]; // Nhac nho ve cac mui tiem sap den han
}lichTiemChung;

/* PHAN VACCINE CUA NHAN VIEN Y TE */
/* Khai bao struct cho Date */
typedef struct
{
    int day;
    int month;
    int year;
} Date;

/* Khai bao struct cho vac xin */
typedef struct 
{
    char vacName[50];
    char ingredients[100]; // thanh phan cua vac xin
    char target[100]; // doi tuong su dung vac xin
    char guide[100]; // huong dan su dung
    int inventory; // luong ton kho
    Date expiryDate; // han su dung
} Vaccine;

/* KHAI BAO CAC HAM SE SU DUNG */

/* PHAN NHAN VIEN NHAP KHO VAC XIN */
void inputBN(inforBN *bn);
void outputBN(inforBN bn);
void inputVC(inforNX *vc);
void outputVC(inforNX vc);
void deleteBN(inforBN *bn, int *n, int id);
void deleteVC(inforNX *vc, int *n, char *tenVC);

/* PHAN BENH NHAN */
// xoa bo nho dem dau vao scanf
void clear() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// bien toan cuc
int dem=0;
int tangDem()  // dem gan cho phan ID voi moi benh nhan duoc nhap, id duoc gan tang 1
{
    ++dem;
    return dem;
}
int reset()    // reset dem ve 0
{
    dem=0;
    return dem;
}

// kiem tra ngay thang nam
int validateDate(int day, int month, int year) {
    if (year > 2024) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return 0;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29) return 0;
        } else {
            if (day > 28) return 0;
        }
    }
    return 1;
}

// Khai bao ham nhap data thong tin ca nhan va thong tin y te 
void dtCaNhan(caNhan* , yTe* , int);  

// Khai bao ham nhap data lich tiem chung
void dtLichTiemChung(lichTiemChung* , int); 

// display funcions:

// Hien thi thong tin ca nhan
void displayCaNhan(caNhan*,yTe*,LichSuTiemChung*,lichTiemChung* ,int,int*);  

// tra cuu thong tin benh nhan
void if_bn(caNhan*,yTe*,LichSuTiemChung*,lichTiemChung* ,int,int*);  

// Xóa thông tin bệnh nhân
void deletePatient(caNhan*, yTe*, LichSuTiemChung*, lichTiemChung*, int*, int*);

// Thêm bệnh nhân mới
void addPatient(caNhan*, yTe*, LichSuTiemChung*, lichTiemChung*, int*, int*);

/* PHAN VACCINE CUA NHAN VIEN Y TE */
// Ham kiem tra tinh hop le cua ngay thang nam nhap vao
int validDate(Date date);

// Ham nhap thong tin vac xin
void inputVac(Vaccine *vaccine);

// Ham hien thi thong tin vac xin
void displayVac(Vaccine vaccine);

// Ham tim kiem  va hien thi vac xin qua ten vac xin
void searchVac(Vaccine vaccine[], int numofVac, char vacSearch[]); //numofVac la so loai vac xin; vacSearch la ten loai vac xin muon tim kiem

// Ham sap xep va hien thi nhung loai vac xin theo han su dung
void searchExpiry(Vaccine vaccine[], int numofVac);

// Ham so sanh han su dung hai loai vac xin
int cmpVac(Vaccine v1, Vaccine v2);

// Ham sap xep so luong ton kho moi loai vac xin
void sortInven(Vaccine vaccine[], int numofVac);

// Ham nhap them vac xin moi 
void addVac(Vaccine **vaccine, int *numofVac, int newAddvac); // newAddvac la so luong vac xin moi muon nhap

// Ham cap nhat thong tin 1 vac xin da nhap
void changeVac(Vaccine **vaccine, int index, Vaccine *updateVac); // updateVac la thong tin vac xin duoc cap nhat

// Ham xoa thong tin 1 vac xin da nhap
void deleteVac(Vaccine **vaccine, int *numofVac, int index); // index la so thu tu cua vac xin 

int main() // ham main
{
    /* KHAI BAO BIEN SU DUNG TRONG HAM MAIN */

    /* PHAN NHAN VIEN (CHUNG) & NHAN VIEN NHAP KHO VAC XIN */
    int option1, option2, option3, m, p;
    int s = 0;
    //char position[10];
    char nameacc[10];
    char password[10];
    inforBN* BenhNhan = NULL;
    inforNX* Vaccine1 = NULL;
    int numBN = 0, numVC = 0;
    
    /* PHAN BENH NHAN */
    // khai bao va cap phat
    int numOfBn; // so luong of patient
    LichSuTiemChung lichSuTiemChung[100]; //   khai báo 1 mang struct ( khong han )
    int numOfVaccine[1000];   // so luong vaccine cua 1 object
    caNhan* infor_cn;  // khai co con tro kieu caNhan
    yTe* infor_yt;  // khai bao con tro kieu yTe
    lichTiemChung* infor_ltc;

    /* PHAN VACCINE CUA NHAN VIEN Y TE */
    int numofVac; // So luong loai vac xin
    char vacSearch[50]; // Ten loai vac xin tim kiem
    int choice; // bien phuc vu menu lua chon hanh dong
    char continueInput;
    int newAddvac, index1, index2;
    Vaccine updateVac;

    /* MENU HANH DONG VA CAC CHUC NANG */

    /* DANG NHAP */
    printf("Chao mung den voi he thong thong tin tiem chung");
    printf("\nVui long dang nhap");
    printf("\n");
    TEST1:
    printf("\nTen tai khoan: "); scanf("%s", nameacc);
    fflush(stdin);
    printf("Mat khau: "); scanf("%s", password);
    if ((strcmp(nameacc, "baitaplon") == 0 && strcmp(password, "baitaplon") == 0))
    {
        while(1)
        {
            printf("\nDua ra lua chon cua ban: ");
            printf("\n1. Lien quan den benh nhan");
            printf("\n2. Lien quan den vac xin");
            printf("\n3. Thoat chuong trinh");
            printf("\nVui long nhap lua chon cua ban: ");
            scanf("%d", &option1);

            switch(option1)
            {
                case 1:
                    {
                    	printf("______THONG TIN LIEN QUAN DEN BENH NHAN______\n");
                    	printf("Nhap so luong benh nhan: ");
    					scanf("%d", &numOfBn);
    					clear(); // Xóa bộ đệm sau khi nhập số lượng bệnh nhân

    					infor_cn = (caNhan*)malloc(numOfBn * sizeof(caNhan)); // Cấp phát động thông tin cá nhân
    					infor_yt = (yTe*)malloc(numOfBn * sizeof(yTe)); // Cấp phát động thông tin y tế
    					infor_ltc = (lichTiemChung*)malloc(numOfBn * sizeof(lichTiemChung)); // Cấp phát động thông tin lịch tiêm
						// Nhập thông tin cá nhân và y tế
						printf("**THONG TIN CA NHAN CUA BENH NHAN**\n");
    					dtCaNhan(infor_cn, infor_yt, numOfBn);

    					for (int i = 0; i < numOfBn; i++) 
    					{
        					if (infor_yt[i].tienTiemChung == 1)
        					{
            					printf("\n**THONG TIN LICH SU TIEM CHUNG** :\n");
            					printf(" \nBenh nhan %d\n",i+1);
            					printf(" So luong vaccine da tiem: ");
            					scanf("%d", &numOfVaccine[i]); // Số lượng vaccine của object i+1
            					clear();

            					for (int j = 0; j < numOfVaccine[i]; j++)
            					{
                					int temp = 0;
                					printf("\n Vaccine thu %d\n", j + 1);
                					printf("  Ten vaccine la: ");
                					fgets(lichSuTiemChung[j].nameOfVaccine, 99, stdin);
                					strtok(lichSuTiemChung[j].nameOfVaccine, "\n");

                					do {
                    					printf("  Thoi gian tiem (dd/mm/yyyy): ");
                    					scanf("%d/%d/%d", &lichSuTiemChung[j].dayT, &lichSuTiemChung[j].monthT, &lichSuTiemChung[j].yearT);
                    					clear();
                    					if (0 >= lichSuTiemChung[j].dayT || 31 < lichSuTiemChung[j].dayT || lichSuTiemChung[j].monthT <= 0 || lichSuTiemChung[j].monthT > 12 || lichSuTiemChung[j].yearT > 2024 || lichSuTiemChung[j].yearT < infor_cn[i].year)
                    					{
                        					printf("Khong hop le, nhap lai ngay thang nam!! \n");
                    					}
                    					else temp = 1;

                					} while (temp == 0);

                					printf("  Dia diem tiem: ");
                					fgets(lichSuTiemChung[j].DDT, 99, stdin);
                					strtok(lichSuTiemChung[j].DDT, "\n");
            					}
        					}
        					else printf("Benh nhan %d khong co lich su tiem chung !", i + 1);
    					}

    					// Nhập thông tin lịch tiêm chủng
    					dtLichTiemChung(infor_ltc, numOfBn);

    					int choice;
    					while (1) {
        					printf("\nMenu\n");
        					printf("1. Hien thi thong tin benh nhan\n");
        					printf("2. Tra cuu thong tin benh nhan\n");
        					printf("3. Them benh nhan moi\n");
        					printf("4. Xoa thong tin benh nhan\n");
        					printf("5. Thoat\n");
        					printf("Chon mot chuc nang: ");
        					scanf("%d", &choice);
        					clear();

        					switch (choice) {
            				case 1:
            					printf("\n**DUOI DAY LA THONG TIN BENH NHAN**\n");
                				displayCaNhan(infor_cn, infor_yt, lichSuTiemChung, infor_ltc, numOfBn, numOfVaccine);
                				break;
            				case 2:
            					printf("\n**TRA CUU THONG TIN BENH NHAN**\n");
                				if_bn(infor_cn, infor_yt, lichSuTiemChung, infor_ltc, numOfBn, numOfVaccine);
                				break;
            				case 3:
            					printf("\n**THEM BENH NHAN MOI**\n");
                				addPatient(infor_cn, infor_yt, lichSuTiemChung, infor_ltc, &numOfBn, numOfVaccine);
                				break;
            				case 4:
            					printf("\n**XOA THONG TIN BENH NHAN**\n");
                				deletePatient(infor_cn, infor_yt, lichSuTiemChung, infor_ltc, &numOfBn, numOfVaccine);
                				break;
            				case 5:
            					printf("************************THOAT HE THONG************************\n");
                				free(infor_cn);
                				free(infor_yt);
                				free(infor_ltc);
                				exit(0);
            				default:
                			printf("Chon sai, vui long chon lai!\n");
        					}
    					}
						break;
                    }
                case 2:
                {
                    printf("\nBan la: ");
                    printf("\n1. Nhan vien nhap kho vac xin");
                    printf("\n2. Nhan vien y te");
                    printf("\nVui long nhap lua chon cua ban: ");
                    scanf("%d", &option2);

                    switch(option2)
                    {
                        case 1:
                        {
                            printf("\nBan muon lam gi?");
                            printf("\n1. Nhap thong tin vaccine");
                            printf("\n2. Hien thi thong tin vaccine");
                            printf("\n3. Xoa thong tin vaccine");
                            printf("\n4. Thoat");
                            printf("\nVui long nhap lua chon cua ban: ");
                            scanf("%d", &option3); 

                            switch(option3)
                            {
                                case 1:
                                {
                                    printf("Tong so loai vaccine muon nhap kho: ");
                                    scanf("%d", &p);
                                    Vaccine1 = (inforNX *)realloc(Vaccine1, (numVC + p) * sizeof(inforNX));
                                    for(int i = 0; i < p; i++)
                                    {
                                        printf("Nhap thong tin loai vaccine thu %d: ", numVC + 1);
                                        inputVC(&Vaccine1[numVC]);
                                        numVC++; 
                                        printf("\n");
                                    }
                                    break;
                                }
                                case 2:
                                {
                                    printf("\nThong tin cac vac xin da nhap: ");
                                    for(int i = 0; i < numVC; i++)
                                    {
                                        printf("\nVac xin thu %d: ", i + 1);
                                        outputVC(Vaccine1[i]);
                                        printf("\n");
                                    }
                                    for(int i=0; i<numVC; i++)
                                    {
                    	                s+=Vaccine1[i].countVC;
                                    }
                                    printf("Tong so lieu vaccine da nhap kho: %d lieu ",s);

                                    break;
                                    }
                                case 3:
                                {
                                    char tenVC[20];
                                    printf("\nNhap ten vaccine can xoa: ");
                                    fflush(stdin);
                                    gets(tenVC);
                                    deleteVC(Vaccine1, &numVC, tenVC);
                                    break;
                                    }
                                case 4:
                                {
                                    free(Vaccine1);
                                    printf("Chuc ban mot ngay tot lanh.");
                                    break;
                                }
                            }
                        break;
                        }
                        case 2:
                        {
                            printf("Nhap so luong loai vaccine: ");
                            scanf("%d", &numofVac);
                            Vaccine *vaccine = (Vaccine *)malloc(numofVac*sizeof(Vaccine));
                            for(int i = 0; i < numofVac; i ++)
                            {
                                printf("\nNhap thong loai vaccine thu %d: ", i + 1);
                                inputVac(&vaccine[i]);
                            }
                            do
                            {
                                printf("\n1.Tim kiem vac xin qua ten (Nhap ban phim so 1)");
                                printf("\n2.Sap xep vac xin theo so luong ton kho (Nhap ban phim so 2)");
                                printf("\n3.Sap xep vac xin theo han su dung (Nhap ban phim so 3)");
                                printf("\n4.Nhap thong tin them vac xin moi (Nhap ban phim so 4)");
                                printf("\n5.Xoa 1 vac xin da nhap (Nhap ban phim so 5)");
                                printf("\n6.Cap nhat thong tin 1 loai vac xin (Nhap ban phim so 6)"); 
                                printf("\nHay lua chon hanh dong tiep theo cua ban: ");
                                scanf("%d", &choice);
                                switch(choice)
                                {
                                    case 1:
                                        printf("\nNhap ten loai vac xin muon tim kiem: ");
                                        fflush(stdin);
                                        fgets(vacSearch, sizeof(vacSearch), stdin);
                                        vacSearch[strlen(vacSearch) - 1] = '\0';
                                        searchVac(vaccine, numofVac, vacSearch);
                                        break;
                                    case 2:
                                        printf("\nDanh sach vac xin sap xep theo so luong ton kho:");
                                        sortInven(vaccine, numofVac);
                                        break;
                                    case 3:
                                        printf("\nDanh sach vac xin sap xep theo han su dung: ");
                                        searchExpiry(vaccine, numofVac);
                                        break;
                                    case 4:
                                        printf("\nNhap so luong vac xin them moi: ");
                                        scanf("%d", &newAddvac);
                                        addVac(&vaccine, &numofVac, newAddvac);
                                        break;
                                    case 5:
                                        printf("\nNhap so thu tu cua vac xin muon xoa: ");
                                        scanf("%d", &index1);
                                        deleteVac(&vaccine, &numofVac, index1);
                                        break;
                                    case 6:
                                        printf("\nNhap so thu tu cua vac xin muon cap nhat: ");
                                        scanf("%d", &index2);
                                        printf("\nNhap thong tin muon cap nhat thanh:");
                                        changeVac(&vaccine, index2, &updateVac);
                                        break;
                                    default:
                                        printf("\nKhong hop le. Hay nhap mot so tu 1 den 6");
                                        continue;
                                }
                                printf("\nBan co muon tiep tuc khong? (Y/N): ");
                                fflush(stdin);
                                scanf("%c", &continueInput);
                            } while (continueInput == 'y' || continueInput == 'Y');
                            free(vaccine);
                        break;
                        }
                        default:
                            printf("\nKhong hop le. Vui long nhap lai");
                            continue;
                    }
                break;
                }
                case 3:
                {
                    return 0;
                }
                default:
                    printf("\nKhong hop le. Vui long nhap lai");
                    continue;
            }
        }
    }
    else
    {
        printf("\nTen tai khoan hoac mat khau ban vua nhap khong dung. Vui long ban nhap lai!");
        goto TEST1;
    }
}
    
/* DINH NGHIA CAC HAM DA SU DUNG */

/* PHAN NHAN VIEN NHAP KHO VAC XIN */
void inputVC(inforNX *vc)
{
    fflush(stdin);
    printf("\nNhap ten vaccine: ");
    gets(vc->TenVC);
    fflush(stdin);
    printf("Nhap so luong vaccine nhap (lieu): ");
    scanf("%d",&vc->countVC);
    fflush(stdin);
    int t = 0;
    do{
    printf("Nhap ngay sinh(DD MM YYYY): ");
    scanf("%d%d%d",&vc->birth.day,&vc->birth.month,&vc->birth.year);
    fflush(stdin);
    if( 0>=vc->birth.day || 31<vc->birth.day || vc->birth.month<=0 || vc->birth.month >12 || vc->birth.year > 2024 )
	{
		printf("Ngay nhap vaccine cua ban khong hop le, hay nhap lai ngay thang nam!! \n");
	}
	else t =1;
		
	}while(t==0);
}
void outputVC(inforNX vc)
{
	printf("\n  -Ten vaccine             : %s", vc.TenVC);
	printf("\n  -So luong vaccine da nhap: %d lieu", vc.countVC);
	printf("\n  -Ngay nhap vaccine       : %d/%d/%d", vc.birth.day, vc.birth.month, vc.birth.year);
}

void deleteVC(inforNX *vc, int *n, char *tenVC)
{
    int found = 0;
    for(int i = 0; i < *n; i++)
    {
        if(strcmp(vc[i].TenVC, tenVC) == 0)
        {
            found = 1;
            for(int j = i; j < *n - 1; j++)
            {
                vc[j] = vc[j + 1];
            }
            (*n)--;
            break;
        }
    }
    if(found)
    {
        printf("\nVaccine %s da bi xoa.\n", tenVC);
        printf("\nDanh sach vaccine hien tai la: ");
        for(int i=0;i<*n;i++){
        	printf("\nVaccine thu %d: ",i+1);
        	for(int i=0;i<*n;i++){
        		outputVC(vc[i]);
			}
        	
		}
    }
    else
    {
        printf("\nKhong tim thay vaccine %s.\n", tenVC);
    }
}

/* PHAN BENH NHAN */
// Định nghĩa hàm nhập thông tin cá nhân
void dtCaNhan(caNhan* infor_cn, yTe* infor_yt, int numOfBn) {
    for (int i = 0; i < numOfBn; i++) {
        int validDate = 0;
        printf("Benh nhan %d\n", i + 1);

        printf(" Tai khoan: ");
        fgets(infor_cn[i].tk, sizeof(infor_cn[i].tk), stdin);
        strtok(infor_cn[i].tk, "\n");

        printf(" Mat khau: ");
        fgets(infor_cn[i].mk, sizeof(infor_cn[i].mk), stdin);
        strtok(infor_cn[i].mk, "\n");

        printf(" Ten benh nhan: ");
        fgets(infor_cn[i].name, sizeof(infor_cn[i].name), stdin);
        strtok(infor_cn[i].name, "\n");

        do {
            printf(" Ngay thang nam sinh (dd/mm/yyyy): ");
            scanf("%d/%d/%d", &infor_cn[i].day, &infor_cn[i].month, &infor_cn[i].year);
            clear();
            if (!validateDate(infor_cn[i].day, infor_cn[i].month, infor_cn[i].year)) {
                printf("Khong hop le, nhap lai ngay thang nam!! \n");
            } else {
                validDate = 1;
            }
        } while (!validDate);

        printf(" Gioi tinh: ");
        fgets(infor_cn[i].sex, sizeof(infor_cn[i].sex), stdin);
        strtok(infor_cn[i].sex, "\n");

        printf(" Dia chi thuong tru: ");
        fgets(infor_cn[i].address, sizeof(infor_cn[i].address), stdin);
        strtok(infor_cn[i].address, "\n");

        printf(" ID ca nhan: ");
        scanf("%d", &infor_cn[i].ID);
        clear();

        printf(" So dien thoai: ");
        fgets(infor_cn[i].numPhone, sizeof(infor_cn[i].numPhone), stdin);
        strtok(infor_cn[i].numPhone, "\n");

        printf(" Tien su benh ly cua benh nhan: ");
        fgets(infor_yt[i].tienBenhLy, sizeof(infor_yt[i].tienBenhLy), stdin);
        strtok(infor_yt[i].tienBenhLy, "\n");

        printf(" Da tiem chung hay chua? (0 -> Chua; 1 -> Da): ");
        scanf("%d", &infor_yt[i].tienTiemChung);
        clear();
    }
}

// Định nghĩa hàm nhập thông tin lịch tiêm chủng
void dtLichTiemChung(lichTiemChung* infor_ltc, int numOfBn)
{
	printf("\n");
    for (int i = 0; i < numOfBn; i++)
    {
    	printf("\n**BENH NHAN %d**",i+1);
        printf("\n Lich tiem chung du kien: ");
        fgets(infor_ltc[i].duKien, 999, stdin);
        strtok(infor_ltc[i].duKien, "\n");

        printf(" Nhac nho ve mui tiem: ");
        fgets(infor_ltc[i].nhacNho, 999, stdin);
        strtok(infor_ltc[i].nhacNho, "\n");
    }
}

// Định nghĩa hàm hiển thị thông tin cá nhân
void displayCaNhan(caNhan* infor_cn, yTe* infor_yt, LichSuTiemChung* lichSuTiemChung, lichTiemChung* infor_ltc, int numOfBn, int* numOfVaccine)
{
    for (int i = 0; i < numOfBn; i++)
    {
        printf("\n Benh nhan %d \n", i + 1);
        printf(" Tai khoan: %s \n", infor_cn[i].tk);
        printf(" Mat khau: %s \n", infor_cn[i].mk);
        printf(" Ten benh nhan: %s \n", infor_cn[i].name);
        printf(" Ngay thang nam sinh: %d/%d/%d \n", infor_cn[i].day, infor_cn[i].month, infor_cn[i].year);
        printf(" Gioi tinh: %s \n", infor_cn[i].sex);
        printf(" Dia chi thuong tru: %s \n", infor_cn[i].address);
        printf(" ID: %d \n", infor_cn[i].ID);
        printf(" So dien thoai: %s \n", infor_cn[i].numPhone);
        printf(" Tien su benh ly cua benh nhan: %s \n", infor_yt[i].tienBenhLy);
        if (infor_yt[i].tienTiemChung == 1)
        {
            printf("  Danh sach cac loai vaccine da tiem:\n");
            for (int j = 0; j < numOfVaccine[i]; j++)
            {
                printf("   Vaccine thu %d:\n", j + 1);
                printf("    Ten vaccine: %s\n", lichSuTiemChung[j].nameOfVaccine);
                printf("    Thoi gian tiem: %d/%d/%d\n", lichSuTiemChung[j].dayT, lichSuTiemChung[j].monthT, lichSuTiemChung[j].yearT);
                printf("    Dia diem tiem: %s\n", lichSuTiemChung[j].DDT);
            }
        }
        else
        {
            printf("Benh nhan chua co lich su tiem chung.\n");
        }
        printf("Lich tiem chung du kien: %s\n", infor_ltc[i].duKien);
        printf("Nhac nho muoi tiem: %s\n", infor_ltc[i].nhacNho);
    }
}

// Định nghĩa hàm tra cứu thông tin bệnh nhân
void if_bn(caNhan* infor_cn, yTe* infor_yt, LichSuTiemChung* lichSuTiemChung, lichTiemChung* infor_ltc, int numOfBn, int* numOfVaccine)
{
    int id;
    printf("Nhap ID benh nhan can tra cuu: ");
    scanf("%d", &id);
    clear();
    for (int i = 0; i < numOfBn; i++)
    {
        if (infor_cn[i].ID == id)
        {
            printf("\n *****************************************\nThong tin benh nhan %d\n", i + 1);
            printf(" Tai khoan: %s \n", infor_cn[i].tk);
            printf(" Mat khau: %s \n", infor_cn[i].mk);
            printf(" Ten benh nhan: %s \n", infor_cn[i].name);
            printf(" Ngay thang nam sinh: %d/%d/%d \n", infor_cn[i].day, infor_cn[i].month, infor_cn[i].year);
            printf(" Gioi tinh: %s \n", infor_cn[i].sex);
            printf(" Dia chi thuong tru: %s \n", infor_cn[i].address);
            printf(" ID: %d \n", infor_cn[i].ID);
            printf(" So dien thoai: %s \n", infor_cn[i].numPhone);
            printf(" Tien su benh ly cua benh nhan: %s \n", infor_yt[i].tienBenhLy);
            if (infor_yt[i].tienTiemChung == 1)
            {
                printf("  Danh sach cac loai vaccine da tiem:\n");
                for (int j = 0; j < numOfVaccine[i]; j++)
                {
                    printf("   Vaccine thu %d:\n", j + 1);
                    printf("    Ten vaccine: %s\n", lichSuTiemChung[j].nameOfVaccine);
                    printf("    Thoi gian tiem: %d/%d/%d\n", lichSuTiemChung[j].dayT, lichSuTiemChung[j].monthT, lichSuTiemChung[j].yearT);
                    printf("    Dia diem tiem: %s\n", lichSuTiemChung[j].DDT);
                }
            }
            else
            {
                printf("Benh nhan chua co lich su tiem chung.\n");
            }
            printf("Lich tiem chung du kien: %s\n", infor_ltc[i].duKien);
            printf("Nhac nho muoi tiem: %s\n", infor_ltc[i].nhacNho);
            return;
        }
    }
    printf("Khong tim thay benh nhan voi ID %d.\n", id);
}

// Định nghĩa hàm xóa thông tin bệnh nhân
void deletePatient(caNhan* infor_cn, yTe* infor_yt, LichSuTiemChung* lichSuTiemChung, lichTiemChung* infor_ltc, int* numOfBn, int* numOfVaccine)
{
    int id;
    printf("Nhap ID benh nhan can xoa: ");
    scanf("%d", &id);
    clear();
    for (int i = 0; i < *numOfBn; i++)
    {
        if (infor_cn[i].ID == id)
        {
            for (int j = i; j < *numOfBn - 1; j++)
            {
                infor_cn[j] = infor_cn[j + 1];
                infor_yt[j] = infor_yt[j + 1];
                infor_ltc[j] = infor_ltc[j + 1];
                numOfVaccine[j] = numOfVaccine[j + 1];
            }
            (*numOfBn)--;
            printf("Da xoa benh nhan voi ID %d.\n", id);
            return;
        }
    }
    printf("Khong tim thay benh nhan voi ID %d.\n", id);
}

// Định nghĩa hàm thêm bệnh nhân mới
void addPatient(caNhan* infor_cn, yTe* infor_yt, LichSuTiemChung* lichSuTiemChung, lichTiemChung* infor_ltc, int* numOfBn, int* numOfVaccine)
{
    int new_numOfBn = *numOfBn + 1;
    infor_cn = (caNhan*)realloc(infor_cn, new_numOfBn * sizeof(caNhan));
    infor_yt = (yTe*)realloc(infor_yt, new_numOfBn * sizeof(yTe));
    infor_ltc = (lichTiemChung*)realloc(infor_ltc, new_numOfBn * sizeof(lichTiemChung));

    dtCaNhan(&infor_cn[*numOfBn], &infor_yt[*numOfBn], 1);

    if (infor_yt[*numOfBn].tienTiemChung == 1)
    {
        printf("\nThong tin lich su tiem chung cua benh nhan %d :\n", *numOfBn + 1);
        printf(" So luong vaccine da tiem: ");
        scanf("%d", &numOfVaccine[*numOfBn]); // Số lượng vaccine của object i+1
        clear();

        for (int j = 0; j < numOfVaccine[*numOfBn]; j++)
        {
            int temp = 0;
            printf("\n Vaccine thu %d\n", j + 1);
            printf("  Ten vaccine la: ");
            fgets(lichSuTiemChung[j].nameOfVaccine, 99, stdin);
            strtok(lichSuTiemChung[j].nameOfVaccine, "\n");

            do {
                printf("  Thoi gian tiem (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &lichSuTiemChung[j].dayT, &lichSuTiemChung[j].monthT, &lichSuTiemChung[j].yearT);
                clear();
                if (0 >= lichSuTiemChung[j].dayT || 31 < lichSuTiemChung[j].dayT || lichSuTiemChung[j].monthT <= 0 || lichSuTiemChung[j].monthT > 12 || lichSuTiemChung[j].yearT > 2024 || lichSuTiemChung[j].yearT < infor_cn[*numOfBn].year)
                {
                    printf("Khong hop le, nhap lai ngay thang nam!! \n");
                }
                else temp = 1;

            } while (temp == 0);

            printf("  Dia diem tiem: ");
            fgets(lichSuTiemChung[j].DDT, 99, stdin);
            strtok(lichSuTiemChung[j].DDT, "\n");
        }
    }
    else printf("Benh nhan %d khong co lich su tiem chung !", *numOfBn + 1);

    dtLichTiemChung(&infor_ltc[*numOfBn], 1);

    *numOfBn = new_numOfBn;
}

/* PHAN VACCINE CUA NHAN VIEN Y TE */
int validDate(Date date)
{
    if(date.year < 2024) // Kiem tra nam
        return 0;
    if(date.month < 1 || date.month > 12) // Kiem tra thang
        return 0;
    int daysInmonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // So ngay trong thang
    if ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0)) // Kiem tra nam nhuan
    {
        daysInmonth[1] = 29;
    }
    if (date.day < 1 || date.day > daysInmonth[date.month - 1]) // Kiem tra so ngay trong thang
        return 0;
    return 1;
}

void inputVac(Vaccine *vaccine)
{
    printf("\nNhap ten loai vaccine: ");
    fflush(stdin);
    fgets(vaccine->vacName, sizeof(vaccine->vacName), stdin);
    vaccine->vacName[strlen(vaccine->vacName) - 1] = '\0'; // Bo ky tu xuong dong
    printf("\nNhap thanh phan cua vaccine: ");
    fflush(stdin);
    fgets(vaccine->ingredients, sizeof(vaccine->ingredients), stdin);
    vaccine->ingredients[strlen(vaccine->ingredients) - 1] = '\0';
    printf("\nNhap doi tuong su dung: ");
    fflush(stdin);
    fgets(vaccine->target, sizeof(vaccine->target), stdin);
    vaccine->target[strlen(vaccine->target) - 1] = '\0';
    printf("\nNhap huong dan su dung: ");
    fflush(stdin);
    fgets(vaccine->guide, sizeof(vaccine->guide), stdin);
    vaccine->guide[strlen(vaccine->guide) - 1] = '\0';
    while(1)
    {
        printf("\nNhap so luong thuoc ton kho: ");
        scanf("%d", &vaccine->inventory);
        if(vaccine->inventory > 0)
        {
            break;
        }
        else
        {
            printf("Vui long nhap so luong thuoc hop le");
        }
    }
    while(1)
    {
        printf("\nNhap han su dung (YYYY-MM-DD): ");
        scanf("%d-%d-%d", &vaccine->expiryDate.year, &vaccine->expiryDate.month, &vaccine->expiryDate.day);
        if(validDate(vaccine->expiryDate))
        {
            break;
        }
        else
        {
            printf("\nXin nhap ngay thang nam hop le");
        }
    }
   
}

void displayVac(Vaccine vaccine)
{
    printf("\nTen loai vaccine: %s", vaccine.vacName);
    printf("\nThanh phan vaccine: %s", vaccine.ingredients);
    printf("\nDoi tuong su dung: %s", vaccine.target);
    printf("\nHuong dan su dung: %s", vaccine.guide);
    printf("\nLuong ton kho: %d", vaccine.inventory);
    printf("\nHan su dung: %d-%d-%d", vaccine.expiryDate.day, vaccine.expiryDate.month, vaccine.expiryDate.year);
}

void searchVac(Vaccine vaccine[], int numofVac, char vacSearch[])
{
    int found = 0;
    for(int i = 0; i < numofVac; i ++)
    {
        if(strcmp(vaccine[i].vacName, vacSearch) == 0)
        {
            printf("\nSo thu tu: %d", i + 1);
            displayVac(vaccine[i]);
            found = 1;
        }
    }
    if(!found)
    {
        printf("\nKhong tim thay thong tin vac xin co ten tuong ung");
    }
}

void sortInven(Vaccine vaccine[], int numofVac)
{
    Vaccine temp;
    for(int i = 0; i < numofVac - 1; i ++)
    {
        for(int j = i + 1; j < numofVac; j ++)
        {
            if(vaccine[i].inventory > vaccine[j].inventory)
            {
                temp = vaccine[i];
                vaccine[i] = vaccine[j];
                vaccine[j] = temp;
            }
        }
    }
    for(int i = 0; i < numofVac; i ++)
    {
        printf("\nVac xin: %s - So luong: %d", vaccine[i].vacName, vaccine[i].inventory);
    }
}

int cmpVac(Vaccine v1, Vaccine v2)
{
    if(v1.expiryDate.year != v2.expiryDate.year)
    {
        return v1.expiryDate.year - v2.expiryDate.year;
    }   
    if(v1.expiryDate.month != v2.expiryDate.month)
    {
        return v1.expiryDate.month - v2.expiryDate.month;
    }
    return v1.expiryDate.day - v2.expiryDate.day;
}
void searchExpiry(Vaccine vaccine[], int numofVac)
{
    Vaccine temp;
    for(int i = 0; i < numofVac - 1; i ++)
    {
        for(int j = i + 1; j < numofVac; j ++)
        {
            if(cmpVac(vaccine[i], vaccine[j]) > 0)
            {
                temp = vaccine[i];
                vaccine[i] = vaccine[j];
                vaccine[j] = temp;
            }
        }
    }
    for(int i = 0; i < numofVac; i ++)
    {
        printf("\nVac xin: %s - Han su dung(YYYY-MM-DD): %d-%d-%d", vaccine[i].vacName, vaccine[i].expiryDate.year, vaccine[i].expiryDate.month, vaccine[i].expiryDate.day);
    }
}

void addVac(Vaccine **vaccine, int *numofVac, int newAddvac)
{
    *vaccine = (Vaccine *)realloc(*vaccine, (*numofVac + newAddvac) * sizeof(Vaccine));
    for (int i = 0; i < newAddvac; i++) 
    {
        printf("Nhap thong tin cho vac xin thu %d:\n", *numofVac + 1);
        inputVac(&(*vaccine)[*numofVac]);
        (*numofVac)++;
    }
}

void deleteVac(Vaccine **vaccine, int *numofVac, int stt) // so thu tu cua vac xin
{
    for(int i = stt - 1; i < *numofVac - 1; i ++ )
    {
        (*vaccine)[i] = (*vaccine)[i + 1];
    }
    *vaccine = (Vaccine *)realloc(*vaccine, (*numofVac - 1) * sizeof(Vaccine));
    (*numofVac) --;
}

void changeVac(Vaccine **vaccine, int stt, Vaccine *updateVac)
{
    inputVac(updateVac);
    (*vaccine)[stt -1] = *updateVac;
}

