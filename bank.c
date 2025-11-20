#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct account {
    int acc_no;
    char name[50];
    float balance;
};

void createAccount() {
    struct account acc;
    FILE *fp = fopen("bank.dat", "ab");

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.acc_no);
    printf("Enter Name: ");
    scanf("%s", acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("\nAccount Created Successfully!\n");
}

void depositMoney() {
    struct account acc;
    int acc_no;
    float amount;
    int found = 0;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);

    FILE *fp = fopen("bank.dat", "rb+");

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.acc_no == acc_no) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);

            acc.balance += amount;

            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("\nAmount Deposited Successfully!\n");
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("\nAccount Not Found!\n");
}

void withdrawMoney() {
    struct account acc;
    int acc_no;
    float amount;
    int found = 0;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);

    FILE *fp = fopen("bank.dat", "rb+");

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.acc_no == acc_no) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (acc.balance >= amount) {
                acc.balance -= amount;
                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);

                printf("\nWithdrawal Successful!\n");
            } else {
                printf("\nInsufficient Balance!\n");
            }

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("\nAccount Not Found!\n");
}

void checkBalance() {
    struct account acc;
    int acc_no;
    int found = 0;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);

    FILE *fp = fopen("bank.dat", "rb");

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.acc_no == acc_no) {
            printf("\nAccount Holder: %s", acc.name);
            printf("\nCurrent Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("\nAccount Not Found!\n");
}

void displayAll() {
    struct account acc;
    FILE *fp = fopen("bank.dat", "rb");

    printf("\n------ ALL ACCOUNTS ------\n");

    while (fread(&acc, sizeof(acc), 1, fp)) {
        printf("\nAccount No.: %d", acc.acc_no);
        printf("\nName: %s", acc.name);
        printf("\nBalance: %.2f", acc.balance);
        printf("\n------------------------------");
    }

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n\n====== BANK MANAGEMENT SYSTEM ======\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Display All Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: displayAll(); break;
            case 6: exit(0);
            default: printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
