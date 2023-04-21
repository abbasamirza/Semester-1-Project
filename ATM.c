#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>


struct Users
{
	char NAME[30], NIC[14], PIN[5];
	int BALANCE;
} user;


int maximize_window(CONSOLE_SCREEN_BUFFER_INFO, HANDLE);
void print_welcome(int, HANDLE, WORD);
void print_thanks(int, HANDLE, WORD);
int print_menu(HANDLE, WORD);
int print_get_withdrawal(int, HANDLE, WORD);
void print_user(int, HANDLE, WORD);
void print_reciept(int, int, int, HANDLE, WORD, FILE *);
void print_spaces(int, int);
void print_pin_updation(int, HANDLE, WORD);
void print_balance_addition(int, int, int, HANDLE, WORD, FILE *);
void print_account_deletion(int, HANDLE, WORD);
int get_entry(HANDLE, WORD);
void get_NIC(HANDLE, WORD);
void get_PIN(HANDLE, WORD);
void get_PINc(char [], HANDLE, WORD);
int check_existing(FILE *);
int check_PIN(FILE *, int);
void signup(int, HANDLE, WORD, FILE *);
void login(int, HANDLE, WORD, FILE *);
void perform_desired_req(int, int, int, HANDLE, WORD, FILE *);
void withdraw(int, int, FILE *);
void update_PIN(int, FILE *);
void add_BALANCE(int, int, FILE *);
void delete_account(int, FILE *);


int main(void)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD oldcolor;
	CONSOLE_SCREEN_BUFFER_INFO info;
	FILE *fp;
	int entry, width = maximize_window(info, out);
	
	SetConsoleTitle("ATM");
	
	fp = fopen("DATA.txt", "a");
	
	if (fp == NULL)
	{
		printf("File unable to open\n");
		return 1;
	}
	
	fclose(fp);
	GetConsoleScreenBufferInfo(out, &info);
	oldcolor = info.wAttributes;
	
	print_welcome(width, out, oldcolor);
	printf("\nEnter the number of action you want to perform\n\n");
	printf("1. Login\n");
	printf("2. Register\n");
	printf("0. Exit\n\n");
	
	entry = get_entry(out, oldcolor);
	
	if (entry != 0)
	{
		system("cls");
		print_welcome(width, out, oldcolor);
		printf("\nEnter your NIC number\n");
		get_NIC(out, oldcolor);
		system("cls");
		print_welcome(width, out, oldcolor);
		
		if (entry == 1)
		{
			login(width, out, oldcolor, fp);
		}
		
		else if (entry == 2)
		{
			signup(width, out, oldcolor, fp);
		}
	}
	
	else if (entry == 0)
	{
		system("cls");
	}
	
	print_thanks(width, out, oldcolor);
	
	return 0;
}

int maximize_window(CONSOLE_SCREEN_BUFFER_INFO info, HANDLE out)
{
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
	
	if (!out || !GetConsoleScreenBufferInfo(out, &info))
	{
		return 80;
	}
	
	return info.dwSize.X;
}


void print_welcome(int width, HANDLE out, WORD oldcolor)
{
	print_spaces(width, 14);
	SetConsoleTextAttribute(out, FOREGROUND_BLUE);
	printf("WELCOME TO ATM\n");
	SetConsoleTextAttribute(out, oldcolor);
}

void print_thanks(int width, HANDLE out, WORD oldcolor)
{
	printf("\n\n\n");
	print_spaces(width, 25);
	SetConsoleTextAttribute(out, FOREGROUND_BLUE);
	printf("Thankyou for choosing us!\n");
	SetConsoleTextAttribute(out, oldcolor);
}

int print_menu(HANDLE out, WORD oldcolor)
{
	int choice;
	
	printf("\nEnter the number of action you want to perform\n\n");
	printf("1. Cash Withdrawal\n");
	printf("2. Update PIN\n");
	printf("3. Add Balance\n");
	printf("4. Delete Account\n");
	printf("0. Exit\n\n");
	SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
	fflush(stdin);
	scanf("%d", &choice);
	
	while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 0)
	{
		SetConsoleTextAttribute(out, FOREGROUND_RED);
		printf("\nInvalid input, please re-enter your choice\n");
		SetConsoleTextAttribute(out, oldcolor);
		SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
		fflush(stdin);
		scanf("%d", &choice);
	}
	
	SetConsoleTextAttribute(out, oldcolor);
	
	return choice;
}

int print_get_withdrawal(int width, HANDLE out, WORD oldcolor)
{
	int choice;
	
	printf("\nEnter the number of your desired choice\n\n");
	printf("1. 500\n");
	printf("2. 1000\n");
	printf("3. 5000\n");
	printf("4. 10000\n");
	printf("5. 15000\n");
	printf("6. 20000\n");
	printf("7. Custom Amount\n\n");
	SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
	fflush(stdin);
	scanf("%d", &choice);
	
	while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7)
	{
		SetConsoleTextAttribute(out, FOREGROUND_RED);
		printf("\nInvalid input, please re-enter your choice\n");
		SetConsoleTextAttribute(out, oldcolor);
		SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
		fflush(stdin);
		scanf("%d", &choice);
	}
	
	SetConsoleTextAttribute(out, oldcolor);
	
	switch (choice)
	{
		case 1:
			return 500;
		
		case 2:
			return 1000;
			
		case 3:
			return 5000;
			
		case 4:
			return 10000;
			
		case 5:
			return 15000;
			
		case 6:
			return 20000;
			
		case 7:
			system("cls");
			print_welcome(width, out, oldcolor);
			print_user(width, out, oldcolor);
			printf("\nEnter Amount: ");
			SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
			fflush(stdin);
			scanf("%d", &choice);
			
			while ((choice < 0 && choice > 25000) || (choice % 500 != 0))
			{
				SetConsoleTextAttribute(out, FOREGROUND_RED);
				printf("\nAmount can not be less than 0 or greater than 25000 and should be a multiple of 500, please re-enter\n");
				SetConsoleTextAttribute(out, oldcolor);
				SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
				fflush(stdin);
				scanf("%d", &choice);
			}
			
			SetConsoleTextAttribute(out, oldcolor);
			
			return choice;
	}
}

void print_user(int width, HANDLE out, WORD oldcolor)
{
	int i, temp = user.BALANCE, c = 0;
	
	puts("");
	
	for (i = 0; i < width - (6 + strlen(user.NAME)); i++)
	{
		printf(" ");
	}
	
	SetConsoleTextAttribute(out, FOREGROUND_BLUE);
	printf("Name: ");
	SetConsoleTextAttribute(out, oldcolor);
	printf("%s\n", user.NAME);
	
	for (i = 0; i < width - 13; i++)
	{
		printf(" ");
	}
	
	printf("%s\n", user.NIC);
	
	while (temp != 0)
	{
		temp /= 10;
		c++;
	}
	
	for (i = 0; i < width - (c + 9); i++)
	{
		printf(" ");
	}
	
	SetConsoleTextAttribute(out, FOREGROUND_BLUE);
	printf("Balance: ");
	SetConsoleTextAttribute(out, oldcolor);
	printf("%d\n", user.BALANCE);
}

void print_reciept(int width, int amount, int index, HANDLE out, WORD oldcolor, FILE *fp)
{
	char str[] = "Cash Withdrawn Successfully!";
	int i, temp, c = 0;

	fseek(fp, index, SEEK_SET);
	fread(&user, sizeof(user), 1, fp);
	temp = user.BALANCE + amount;
	
	printf("\n\n");
	print_spaces(width, 32);
	
	for (i = 0; i < 34; i++)
	{
		printf("-");
	}
	
	printf("\n");
	print_spaces(width, 32);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|  ");
	SetConsoleTextAttribute(out, FOREGROUND_GREEN);
	
	for (i = 0; i < 28; i++)
	{
		Sleep(70);
		printf("%c", str[i]);
	}
	
	SetConsoleTextAttribute(out, oldcolor);
	printf("  |\n");
	print_spaces(width, 32);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|  ");
	strcpy(str, "Old Amount: ");
	SetConsoleTextAttribute(out, FOREGROUND_BLUE);
	
	for (i = 0; i < 12; i++)
	{
		Sleep(70);
		printf("%c", str[i]);
	}
	
	SetConsoleTextAttribute(out, oldcolor);
	printf("%d", temp);
	
	while (temp != 0)
	{
		temp /= 10;
		c++;
	}
	
	for (i = 0; i < 18 - c; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|  ");
	strcpy(str, "New Amount: ");
	SetConsoleTextAttribute(out, FOREGROUND_BLUE);
	
	for (i = 0; i < 12; i++)
	{
		Sleep(70);
		printf("%c", str[i]);
	}
	
	SetConsoleTextAttribute(out, oldcolor);
	temp = user.BALANCE;
	c = 0;
	
	while (temp != 0)
	{
		temp /= 10;
		c++;
	}
	
	printf("%d", user.BALANCE);
	
	for (i = 0; i < 18 - c; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	
	for (i = 0; i < 34; i++)
	{
		printf("-");
	}
}

void print_spaces(int width, int len)
{
	int i;
	
	for (i = 0; i < (width - len) / 2; i++)
	{
		printf(" ");
	}
}

void print_pin_updation(int width, HANDLE out, WORD oldcolor)
{
	char str[] = "PIN Updated Successfully!";
	int i;
	
	printf("\n\n");
	print_spaces(width, 34);
	
	for (i = 0; i < 34; i++)
	{
		printf("-");
	}
	
	printf("\n");
	print_spaces(width, 34);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 34);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 34);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 34);
	printf("|    ");
	SetConsoleTextAttribute(out, FOREGROUND_GREEN);
	
	for (i = 0; i < 25; i++)
	{
		Sleep(70);
		printf("%c", str[i]);
	}
	
	SetConsoleTextAttribute(out, oldcolor);
	printf("   |\n");
	print_spaces(width, 34);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 34);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 34);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 34);
	
	for (i = 0; i < 34; i++)
	{
		printf("-");
	}
}

void print_balance_addition(int width, int amount, int index, HANDLE out, WORD oldcolor, FILE *fp)
{
	char str[] = "Balance Updated Successfully!";
	int i, temp, c = 0;

	fseek(fp, index, SEEK_SET);
	fread(&user, sizeof(user), 1, fp);
	temp = user.BALANCE - amount;
	
	printf("\n\n");
	print_spaces(width, 32);
	
	for (i = 0; i < 34; i++)
	{
		printf("-");
	}
	
	printf("\n");
	print_spaces(width, 32);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|  ");
	SetConsoleTextAttribute(out, FOREGROUND_GREEN);
	
	for (i = 0; i < 29; i++)
	{
		Sleep(70);
		printf("%c", str[i]);
	}
	
	SetConsoleTextAttribute(out, oldcolor);
	printf(" |\n");
	print_spaces(width, 32);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|  ");
	strcpy(str, "Old Amount: ");
	SetConsoleTextAttribute(out, FOREGROUND_BLUE);
	
	for (i = 0; i < 12; i++)
	{
		Sleep(70);
		printf("%c", str[i]);
	}
	
	SetConsoleTextAttribute(out, oldcolor);
	printf("%d", temp);
	
	while (temp != 0)
	{
		temp /= 10;
		c++;
	}
	
	for (i = 0; i < 18 - c; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|  ");
	strcpy(str, "New Amount: ");
	SetConsoleTextAttribute(out, FOREGROUND_BLUE);
	
	for (i = 0; i < 12; i++)
	{
		Sleep(70);
		printf("%c", str[i]);
	}
	
	SetConsoleTextAttribute(out, oldcolor);
	temp = user.BALANCE;
	c = 0;
	
	while (temp != 0)
	{
		temp /= 10;
		c++;
	}
	
	printf("%d", user.BALANCE);
	
	for (i = 0; i < 18 - c; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	printf("|");
	
	for (i = 0; i < 32; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 32);
	
	for (i = 0; i < 34; i++)
	{
		printf("-");
	}
}


int get_entry(HANDLE out, WORD oldcolor)
{
	int entry;
	
	SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
	fflush(stdin);
	scanf("%d", &entry);
	
	while (entry != 1 && entry != 2 && entry != 0)
	{
		SetConsoleTextAttribute(out, FOREGROUND_RED);
		printf("\nInvalid input, please re-enter your choice\n");
		SetConsoleTextAttribute(out, oldcolor);
		SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
		fflush(stdin);
		scanf("%d", &entry);
	}
	
	SetConsoleTextAttribute(out, oldcolor);
	
	return entry;
}

void print_account_deletion(int width, HANDLE out, WORD oldcolor)
{
	char str[] = "Your account has been deleted!";
	int i;
	
	printf("\n\n");
	print_spaces(width, 34);
	
	for (i = 0; i < 39; i++)
	{
		printf("-");
	}
	
	printf("\n");
	print_spaces(width, 34);
	printf("|");
	
	for (i = 0; i < 37; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 34);
	printf("|");
	
	for (i = 0; i < 37; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 34);
	printf("|");
	
	for (i = 0; i < 37; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 34);
	printf("|    ");
	SetConsoleTextAttribute(out, FOREGROUND_GREEN);
	
	for (i = 0; i < 30; i++)
	{
		Sleep(70);
		printf("%c", str[i]);
	}
	
	SetConsoleTextAttribute(out, oldcolor);
	printf("   |\n");
	print_spaces(width, 34);
	printf("|");
	
	for (i = 0; i < 37; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 34);
	printf("|");
	
	for (i = 0; i < 37; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 34);
	printf("|");
	
	for (i = 0; i < 37; i++)
	{
		printf(" ");
	}
	
	printf("|\n");
	print_spaces(width, 34);
	
	for (i = 0; i < 39; i++)
	{
		printf("-");
	}
}

void get_NIC(HANDLE out, WORD oldcolor)
{
	char ch;
	int i = 0;
	
	SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
	fflush(stdin);
	
	while (1)
	{
		ch = getch();
		
		if ((ch == 13 || ch == 9) && i == 13)
		{
			user.NIC[i] = '\0';
			break;
		}
		
		else if (ch == 8 && i > 0)
		{
			--i;
			printf("\b \b");
		}
		
		else if (ch > 47 && ch < 58 && i != 13)
		{
			user.NIC[i++] = ch;
			printf("%c \b", ch);
		}
	}
	
	SetConsoleTextAttribute(out, oldcolor);
}

void get_PIN(HANDLE out, WORD oldcolor)
{
	char ch;
	int i = 0;
	
	SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
	fflush(stdin);
	
	while (1)
	{
		ch = getch();
		
		if ((ch == 13 || ch == 9) && i == 4)
		{
			user.PIN[i] = '\0';
			break;
		}
		
		else if (ch == 8 && i > 0)
		{
			--i;
			printf("\b \b");
		}
		
		else if (ch > 47 && ch < 58 && i != 4)
		{
			user.PIN[i++] = ch;
			printf("* \b", ch);
		}
	}
	
	SetConsoleTextAttribute(out, oldcolor);
}

void get_PINc(char pin[5], HANDLE out, WORD oldcolor)
{
	char ch;
	int i = 0;
	
	SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
	fflush(stdin);
	
	while (1)
	{
		ch = getch();
		
		if ((ch == 13 || ch == 9) && i == 4)
		{
			pin[i] = '\0';
			break;
		}
		
		else if (ch == 8 && i > 0)
		{
			--i;
			printf("\b \b");
		}
		
		else if (ch > 47 && ch < 58 && i != 4)
		{
			pin[i++] = ch;
			printf("* \b", ch);
		}
	}
	
	SetConsoleTextAttribute(out, oldcolor);
}

int check_existing(FILE *fp)
{
	char tempNIC[14];
	
	fp = fopen("DATA.txt", "r");
	
	if (fp == NULL)
	{
		printf("\nFile unable to open\n");
		exit(2);
	}
	
	strcpy(tempNIC, user.NIC);
	
	while (fread(&user, sizeof(user), 1, fp))
	{
		if (strcmp(user.NIC, tempNIC) == 0)
		{
			return ftell(fp) - sizeof(user);
		}
	}
	
	strcpy(user.NIC, tempNIC);
	fclose(fp);
	
	return -1;
}

int check_PIN(FILE *fp, int index)
{
	char tempPIN[5];
	
	fp = fopen("DATA.txt", "r");
	strcpy(tempPIN, user.PIN);
	
	fseek(fp, index, SEEK_SET);
	fread(&user, sizeof(user), 1, fp);
	
	if (strcmp(user.PIN, tempPIN) == 0)
	{
		return 1;
	}
	
	strcpy(user.PIN, tempPIN);
	fclose(fp);
	
	return 0;
}


void signup(int width, HANDLE out, WORD oldcolor, FILE *fp)
{
	char choice, pin[5];
	int entry, action, index = check_existing(fp);
	
	if (index == -1)
	{
		printf("\nEnter 4 digit PIN\n");
		get_PIN(out, oldcolor);
		system("cls");
		print_welcome(width, out, oldcolor);
		printf("\nRe-enter PIN to confirm\n");
		get_PINc(pin, out, oldcolor);
		
		if (strcmp(user.PIN, pin) == 0)
		{
			system("cls");
			print_welcome(width, out, oldcolor);
			printf("\nEnter your name\n");
			SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
			fflush(stdin);
			scanf("%[^\n]s", user.NAME);
			print_welcome(width, out, oldcolor);
			
			system("cls");
			print_welcome(width, out, oldcolor);
			printf("\nEnter your balance\n");
			SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
			fflush(stdin);
			scanf("%d", &user.BALANCE);
			print_welcome(width, out, oldcolor);
			
			fp = fopen("DATA.txt", "a");
			fwrite(&user, sizeof(user), 1, fp);
			fclose(fp);
			
			system("cls");
			print_welcome(width, out, oldcolor);
			SetConsoleTextAttribute(out, FOREGROUND_GREEN);
			printf("\nAccount created successfully!\n\n");
			SetConsoleTextAttribute(out, oldcolor);
			
			printf("Do you want to make a transaction?[Y/N]: ");
			SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
			fflush(stdin);
			scanf("%c", &choice);
			
			while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
			{
				SetConsoleTextAttribute(out, FOREGROUND_RED);
				printf("\nInvalid input, please re-enter\n");
				SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
				SetConsoleTextAttribute(out, oldcolor);
				fflush(stdin);
				scanf("%c", &choice);
			}
			
			SetConsoleTextAttribute(out, oldcolor);
			
			switch (choice)
			{
				case 'Y':
				case 'y':
					system("cls");
					print_welcome(width, out, oldcolor);
					print_user(width, out, oldcolor);
					action = print_menu(out, oldcolor);
					system("cls");
					print_welcome(width, out, oldcolor);
					index = check_existing(fp);
					perform_desired_req(action, index, width, out, oldcolor, fp);
					break;
					
				case 'N':
				case 'n':
					system("cls");
					break;
			}
		}
		
		else
		{
			system("cls");
			print_welcome(width, out, oldcolor);
			SetConsoleTextAttribute(out, FOREGROUND_RED);
			printf("\nThe entered PINs didnot match, re-enter a new PIN\n");
			SetConsoleTextAttribute(out, oldcolor);
			signup(width, out, oldcolor, fp);
		}
	}
	
	else
	{
		SetConsoleTextAttribute(out, FOREGROUND_RED);
		printf("\nThe entered NIC already exists\n\n");
		SetConsoleTextAttribute(out, oldcolor);
		printf("Enter the number of action you want to perform\n\n");
		printf("1. Proceed with login\n");
		printf("2. Signup with another NIC\n");
		printf("0. Exit\n\n");
		SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
		fflush(stdin);
		scanf("%d", &entry);
		
		while (entry != 1 && entry != 2 && entry != 0)
		{
			SetConsoleTextAttribute(out, FOREGROUND_RED);
			printf("\nInvalid input, please re-enter\n");
			SetConsoleTextAttribute(out, oldcolor);
			SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
			fflush(stdin);
			scanf("%d", &entry);
		}
		
		SetConsoleTextAttribute(out, oldcolor);
		
		if (entry == 1)
		{
			system("cls");
			print_welcome(width, out, oldcolor);
			login(width, out, oldcolor, fp);
		}
		
		else if (entry == 2)
		{
			system("cls");
			print_welcome(width, out, oldcolor);
			printf("\nEnter your NIC number\n");
			get_NIC(out, oldcolor);
			system("cls");
			print_welcome(width, out, oldcolor);
			signup(width, out, oldcolor, fp);
		}
		
		else
		{
			system("cls");
		}
	}
}

void login(int width, HANDLE out, WORD oldcolor, FILE *fp)
{
	char success[] = "Login Successful!";
	int action, i, entry, index = check_existing(fp);
	
	if (index != -1)
	{
		printf("\nEnter 4 digit PIN\n");
		get_PIN(out, oldcolor);
		
		if (check_PIN(fp, index) == 1)
		{
			system("cls");
			print_welcome(width, out, oldcolor);
			SetConsoleTextAttribute(out, FOREGROUND_GREEN);
			puts("");
			
			for (i = 0; i < 17; i++)
			{
				Sleep(40);
				printf("%c", success[i]);
			}
			
			SetConsoleTextAttribute(out, oldcolor);
			Sleep(130);
			system("cls");
			print_welcome(width, out, oldcolor);
			print_user(width, out, oldcolor);
			action = print_menu(out, oldcolor);
			system("cls");
			print_welcome(width, out, oldcolor);
			print_user(width, out, oldcolor);
			perform_desired_req(action, index, width, out, oldcolor, fp);
		}
		
		else
		{
			system("cls");
			print_welcome(width, out, oldcolor);
			SetConsoleTextAttribute(out, FOREGROUND_RED);
			printf("\n\nThe PIN you entered is incorrect\n");
			SetConsoleTextAttribute(out, oldcolor);
			login(width, out, oldcolor, fp);
		}
	}
	
	else
	{
		SetConsoleTextAttribute(out, FOREGROUND_RED);
		printf("\nThe entered NIC doesnot exist\n\n");
		SetConsoleTextAttribute(out, oldcolor);
		printf("Enter the number of action you want to perform\n\n");
		printf("1. Login with a different NIC\n");
		printf("2. Proceed with signup\n");
		printf("0. Exit\n\n");
		SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
		fflush(stdin);
		scanf("%d", &entry);
		
		while (entry != 1 && entry != 2 && entry != 0)
		{
			SetConsoleTextAttribute(out, FOREGROUND_RED);
			printf("\nInvalid input, please re-enter\n");
			SetConsoleTextAttribute(out, oldcolor);
			SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
			fflush(stdin);
			scanf("%d", &entry);
		}
		
		SetConsoleTextAttribute(out, oldcolor);
		
		if (entry == 1)
		{
			system("cls");
			print_welcome(width, out, oldcolor);
			printf("\nEnter your NIC number\n");
			get_NIC(out, oldcolor);
			system("cls");
			print_welcome(width, out, oldcolor);
			login(width, out, oldcolor, fp);
		}
		
		else if (entry == 2)
		{
			system("cls");
			print_welcome(width, out, oldcolor);
			signup(width, out, oldcolor, fp);
		}
		
		else
		{
			system("cls");
		}
	}
}

void perform_desired_req(int action, int index, int width, HANDLE out, WORD oldcolor, FILE *fp)
{
	char pin[5], choice;
	int amount, entry;
	
	switch (action)
	{
		case 1:
			// Cash Withdrawal
			amount = print_get_withdrawal(width, out, oldcolor);
			system("cls");
			
			if (amount <= user.BALANCE)
			{
				withdraw(index, amount, fp);
				print_reciept(width, amount, index, out, oldcolor, fp);
			}
			
			break;
			
		case 2:
			// Update PIN
			system("cls");
			print_welcome(width, out, oldcolor);
			print_user(width, out, oldcolor);
			printf("\nEnter new PIN\n");
			get_PINc(pin, out, oldcolor);
			
			while (strcmp(user.PIN, pin) == 0)
			{
				system("cls");
				print_welcome(width, out, oldcolor);
				print_user(width, out, oldcolor);
				SetConsoleTextAttribute(out, FOREGROUND_RED);
				printf("\nNew PIN cannot be the same as old PIN, please re-enter\n");
				SetConsoleTextAttribute(out, oldcolor);
				get_PINc(pin, out, oldcolor);
			}
			
			system("cls");
			print_welcome(width, out, oldcolor);
			print_user(width, out, oldcolor);
			printf("\nRe-enter new PIN to confirm\n");
			get_PIN(out, oldcolor);
			
			if (strcmp(user.PIN, pin) == 0)
			{
				system("cls");
				update_PIN(index, fp);
				print_pin_updation(width, out, oldcolor);
			}
			
			else
			{
				system("cls");
				print_welcome(width, out, oldcolor);
				print_user(width, out, oldcolor);
				SetConsoleTextAttribute(out, FOREGROUND_RED);
				printf("\nThe entered PINs didnot match\n\n");
				SetConsoleTextAttribute(out, oldcolor);
				printf("Enter the number of action you want to perfrom\n\n");
				printf("1. Go to menu\n");
				printf("0. Exit\n\n");
				SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
				fflush(stdin);
				scanf("%d", &entry);
				
				while (entry != 1 && entry != 0)
				{
					SetConsoleTextAttribute(out, FOREGROUND_RED);
					printf("\nInvalid input, please re-enter\n");
					SetConsoleTextAttribute(out, oldcolor);
					SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
					fflush(stdin);
					scanf("%d", &entry);
				}
				
				if (entry == 1)
				{
					system("cls");
					print_welcome(width, out, oldcolor);
					print_user(width, out, oldcolor);
					action = print_menu(out, oldcolor);
					system("cls");
					print_welcome(width, out, oldcolor);
					print_user(width, out, oldcolor);
					perform_desired_req(action, index, width, out, oldcolor, fp);
				}
			}
			
			break;
			
		case 3:
			// Add Balance
			system("cls");
			print_welcome(width, out, oldcolor);
			print_user(width, out, oldcolor);
			printf("\nEnter amount to add: ");
			SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
			fflush(stdin);
			scanf("%d", &amount);
			
			while (amount < 0 || amount > 25000)
			{
				system("cls");
				print_welcome(width, out, oldcolor);
				print_user(width, out, oldcolor);
				SetConsoleTextAttribute(out, FOREGROUND_RED);
				printf("\nAmount can only range from 0 to 25000, please re-enter: ");
				SetConsoleTextAttribute(out, oldcolor);
				SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
				fflush(stdin);
				scanf("%d", &amount);
			}
			
			system("cls");
			add_BALANCE(amount, index, fp);
			print_balance_addition(width, amount, index, out, oldcolor, fp);
			
			break;
			
		case 4:
			// Delete Account
			system("cls");
			print_welcome(width, out, oldcolor);
			print_user(width, out, oldcolor);
			SetConsoleTextAttribute(out, FOREGROUND_RED);
			printf("\nAre you sure you want to delete your account?[Y/N]: ");
			SetConsoleTextAttribute(out, oldcolor);
			SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
			fflush(stdin);
			scanf("%c", &choice);
			
			while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
			{
				system("cls");
				print_welcome(width, out, oldcolor);
				print_user(width, out, oldcolor);
				SetConsoleTextAttribute(out, FOREGROUND_RED);
				printf("\nPlease enter a valid character\n");
				SetConsoleTextAttribute(out, oldcolor);
				SetConsoleTextAttribute(out, FOREGROUND_INTENSITY);
				fflush(stdin);
				scanf("%c", &choice);
			}
			
			if (choice == 'Y' || choice == 'y')
			{
				system("cls");
				delete_account(index, fp);
				print_account_deletion(width, out, oldcolor);
			}
			
			else
			{
				system("cls");
			}
			
			break;
			
		case 0:
			system("cls");
			break;
	}
}

void withdraw(int index, int amount, FILE *fp)
{
	FILE *fptemp;
	
	fp = fopen("DATA.txt", "r");
	fptemp = fopen("TEMPDATA.txt", "w");
	
	if (fptemp == NULL)
	{
		printf("\nUnable to open file\n");
		exit(3);
	}
	
	while (fread(&user, sizeof(user), 1, fp))
	{
		if (index == (ftell(fp) - sizeof(user)))
		{
			user.BALANCE -= amount;
		}
		
		fwrite(&user, sizeof(user), 1, fptemp);
	}
	
	fclose(fp);
	fclose(fptemp);
	
	fp = fopen("DATA.txt", "w");
	fptemp = fopen("TEMPDATA.txt", "r");
	
	while (fread(&user, sizeof(user), 1, fptemp))
	{
		fwrite(&user, sizeof(user), 1, fp);
	}
	
	fclose(fp);
	fclose(fptemp);
}

void update_PIN(int index, FILE *fp)
{
	FILE *fptemp;
	char pin[5];
	
	fp = fopen("DATA.txt", "r");
	fptemp = fopen("TEMPDATA.txt", "w");
	strcpy(pin, user.PIN);
	
	while (fread(&user, sizeof(user), 1, fp))
	{
		if (index == (ftell(fp) - sizeof(user)))
		{
			strcpy(user.PIN, pin);
		}
		
		fwrite(&user, sizeof(user), 1, fptemp);
	}
	
	fclose(fp);
	fclose(fptemp);
	
	fp = fopen("DATA.txt", "w");
	fptemp = fopen("TEMPDATA.txt", "r");
	
	while (fread(&user, sizeof(user), 1, fptemp))
	{
		fwrite(&user, sizeof(user), 1, fp);
	}
	
	fclose(fp);
	fclose(fptemp);
}

void add_BALANCE(int amount, int index, FILE *fp)
{
	FILE *fptemp;
	
	fp = fopen("DATA.txt", "r");
	fptemp = fopen("TEMPDATA.txt", "w");
	
	while (fread(&user, sizeof(user), 1, fp))
	{
		if (index == (ftell(fp) - sizeof(user)))
		{
			user.BALANCE += amount;
		}
		
		fwrite(&user, sizeof(user), 1, fptemp);
	}
	
	fclose(fp);
	fclose(fptemp);
	
	fp = fopen("DATA.txt", "w");
	fptemp = fopen("TEMPDATA.txt", "r");
	
	while (fread(&user, sizeof(user), 1, fptemp))
	{
		fwrite(&user, sizeof(user), 1, fp);
	}
	
	fclose(fp);
	fclose(fptemp);
}

void delete_account(int index, FILE *fp)
{
	FILE *fptemp;
	
	fp = fopen("DATA.txt", "r");
	fptemp = fopen("TEMPDATA.txt", "w");
	
	while (fread(&user, sizeof(user), 1, fp))
	{
		if (index == (ftell(fp) - sizeof(user)))
		{
			continue;
		}
		
		fwrite(&user, sizeof(user), 1, fptemp);
	}
	
	fclose(fp);
	fclose(fptemp);
	
	fp = fopen("DATA.txt", "w");
	fptemp = fopen("TEMPDATA.txt", "r");
	
	while (fread(&user, sizeof(user), 1, fptemp))
	{
		fwrite(&user, sizeof(user), 1, fp);
	}
	
	fclose(fp);
	fclose(fptemp);
}
