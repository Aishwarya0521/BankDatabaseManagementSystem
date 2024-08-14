#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CUSTOMERS 50

struct bankaccount
{
    char name[50];
    int accno;
    float balance;
    char password[20];
};

void createAccount(struct bankaccount accounts[], int *customerCount)
{
    if (*customerCount < MAX_CUSTOMERS)
    {
        printf("Enter your name: ");
        scanf("%s", accounts[*customerCount].name);

        printf("Enter your account number: ");
        scanf("%d", &accounts[*customerCount].accno);

        printf("Set a PIN: ");
        scanf("%s", accounts[*customerCount].password);

        accounts[*customerCount].balance = 0.0;

        printf("Account created successfully!\n");

        (*customerCount)++;
    }
    else
    {
        printf("Maximum customer limit reached. Cannot create more accounts.\n");
    }
}
int findAccount(struct bankaccount accounts[], int customerCount, int accno)
{
    int i;
    for (i = 0; i < customerCount; ++i)
    {
        if (accounts[i].accno == accno)
        {
            return i;
        }
    }
    return -1;
}
int checkPassword(struct bankaccount *account, const char *password)
{
    return strcmp(account->password, password) == 0;
}

void deposit(struct bankaccount accounts[], int customerCount)
{
    int accno;
    printf("Enter your account number: ");
    scanf("%d", &accno);

    int index = findAccount(accounts, customerCount, accno);

    if (index != -1)
    {
        char password[20];
        printf("Enter your PIN: ");
        scanf("%s", password);

        if (checkPassword(&accounts[index], password))
        {
            float amount;
            printf("Enter the amount to deposit: ");
            scanf("%f", &amount);

            accounts[index].balance += amount;
            printf("$%.2f deposited successfully!\n", amount);
            printf("Now your account balance is %.2f\n", accounts[index].balance);
        }
        else
        {
            printf("Invalid PIN! Transaction aborted.\n");
        }
    }
    else
    {
        printf("Account not found!\n");
    }
}
void withdraw(struct bankaccount accounts[], int customerCount)
{
    int accno;
    printf("Enter your account number: ");
    scanf("%d", &accno);

    int index = findAccount(accounts, customerCount, accno);

    if (index != -1)
    {
        char password[20];
        printf("Enter your PIN: ");
        scanf("%s", password);

        if (checkPassword(&accounts[index], password))
        {
            float amt;
            printf("Enter the amount to withdraw: ");
            scanf("%f", &amt);

            if (amt > accounts[index].balance)
            {
                printf("Insufficient funds!\n");
            }
            else
            {
                accounts[index].balance -= amt;
                printf("$%f withdrawn successfully!\n", amt);
                printf("Now your account balance is %0.2f\n", accounts[index].balance);
            }
        }
        else
        {
            printf("Invalid PIN! Transaction aborted.\n");
        }
    }
    else
    {
        printf("Account not found!\n");
    }
}

void checkbalance(struct bankaccount accounts[], int customerCount)
{
    int accno;
    printf("Enter your account number: ");
    scanf("%d", &accno);

    int index = findAccount(accounts, customerCount, accno);

    if (index != -1)
    {
        char password[20];
        printf("Enter your PIN: ");
        scanf("%s", password);

        if (checkPassword(&accounts[index], password))
        {
            printf("Your bank balance is %0.2f\n", accounts[index].balance);
        }
        else
        {
            printf("Invalid PIN! Transaction aborted.\n");
        }
    }
    else
    {
        printf("Account not found!\n");
    }
}

void accdetail(struct bankaccount accounts[], int customerCount)
{
    int accno;
    printf("Enter your account number: ");
    scanf("%d", &accno);

    int index = findAccount(accounts, customerCount, accno);

    if (index != -1)
    {
        char password[20];
        printf("Enter your PIN: ");
        scanf("%s", password);

        if (checkPassword(&accounts[index], password))
        {
            printf("Your account details:\n");
            printf("Name: %s\n", accounts[index].name);
            printf("Account number: %d\n", accounts[index].accno);
            printf("Balance: %0.2f\n", accounts[index].balance);
        }
        else
        {
            printf("Invalid password! Transaction aborted.\n");
        }
    }
    else
    {
        printf("Account not found!\n");
    }
}

void moneytransfer(struct bankaccount accounts[], int customerCount)
{
    int senderAccno, receiverAccno;
    printf("Enter your account number: ");
    scanf("%d", &senderAccno);

    int senderIndex = findAccount(accounts, customerCount, senderAccno);

    if (senderIndex != -1)
    {
        char senderPassword[20];
        printf("Enter your PIN: ");
        scanf("%s", senderPassword);

        if (checkPassword(&accounts[senderIndex], senderPassword))
        {
            printf("Enter the receiver's account number: ");
            scanf("%d", &receiverAccno);

            int receiverIndex = findAccount(accounts, customerCount, receiverAccno);

            if (receiverIndex != -1)
            {
                struct bankaccount *sender = &accounts[senderIndex];
                struct bankaccount *receiver = &accounts[receiverIndex];

                float amt;
                printf("Enter the amount to transfer: ");
                scanf("%f", &amt);

                if (amt > sender->balance)
                {
                    printf("Insufficient funds!\n");
                }
                else
                {
                    sender->balance -= amt;
                    receiver->balance += amt;
                    printf("Transfer successful! New balance for %s: %.2f\n", sender->name, sender->balance);
                    printf("New balance for %s: %.2f\n", receiver->name, receiver->balance);
                }
            }
            else
            {
                printf("Receiver account not found!\n");
            }
        }
        else
        {
            printf("Invalid PIN! Transaction aborted.\n");
        }
    }
    else
    {
        printf("Sender account not found!\n");
    }
}


int loginUser(struct bankaccount accounts[], int customerCount, int *loggedInIndex)
{
    int accno;
    printf("Enter your account number: ");
    scanf("%d", &accno);

    *loggedInIndex = findAccount(accounts, customerCount, accno);

    if (*loggedInIndex != -1)
    {
        char password[20];
        printf("Enter your PIN: ");
        scanf("%s", password);

        if (checkPassword(&accounts[*loggedInIndex], password))
        {
            return 1; 
        }
        else
        {
            printf("Invalid PIN! Login failed.\n");
        }
    }
    else
    {
        printf("Account not found! Login failed.\n");
    }

    return 0;
}


int main()
{
    struct bankaccount accounts[MAX_CUSTOMERS];
    int customerCount = 0;
    int loggedInIndex = -1;

    FILE *file;

    int choice;
    do
    {
        printf("\nBANK MANAGEMENT SYSTEM!!\n");
        printf("1. New user\n");
        printf("2. Login\n");
        printf("0. Exit\n\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount(accounts, &customerCount);
            break;
        case 2:
            if (loginUser(accounts, customerCount, &loggedInIndex))
            {
                printf("Login successful!\n");
                do
                {
                    printf("1. Deposit Money\n");
                    printf("2. Withdraw Money\n");
                    printf("3. Check Balance\n");
                    printf("4. View Account Details\n");
                    printf("5. Transfer Money\n");
                    printf("0. Exit\n");
                    printf("Enter your choice : ");
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1:
                        deposit(accounts, customerCount);
                        break;
                    case 2:
                        withdraw(accounts, customerCount);
                        break;
                    case 3:
                        checkbalance(accounts, customerCount);
                        break;
                    case 4:
                        accdetail(accounts, customerCount);
                        break;
                    case 5:
                        moneytransfer(accounts, customerCount);
                        break;
                    case 0:
                        printf("Successfully exited!!\n");
                        break;
                    default:
                        printf("Invalid choice. Try again!!\n");
                    }
                } while (choice != 0);
            }
            break;
        case 0:
            printf("Successfully exited!!\n");

            file = fopen("accountdetails.txt", "w");
            if (file != NULL)
            {
                int i;
                for (i = 0; i < customerCount; ++i)
                {
                    fprintf(file, "Name: %s\n", accounts[i].name);
                    fprintf(file, "Account Number: %d\n", accounts[i].accno);
                    fprintf(file, "Balance: %.2f\n", accounts[i].balance);
                    fprintf(file, "-----------------------------\n");
                }
                fclose(file);
            }

            break;
        default:
            printf("Invalid choice. Try again!!\n");
        }
    } while (choice != 0);

    return 0;
}
