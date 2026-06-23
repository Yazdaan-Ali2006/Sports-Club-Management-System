#include <stdio.h>
#include <stdlib.h> //because of atoi
#include <string.h> //because of strcpy
/*
 * ##########################################################
 * #                                                        #
 * #              MODULE 1: CRICKET MANAGEMENT              #
 *                     YAZDAAN ALI MIRZA                    #
 * #                                                        #
 * ##########################################################
 */
struct cricket
{
    char name[50];
    int id;
    int age;
    int score;
};
// validation functions
void getValidstr(char *name, const char *msg);
int getValidInt(const char *msg);
// CRICKER FUNCTIONS
void cricketSystem();
void saveCricketData(struct cricket cricketers[], int n);
int loadCricketData(struct cricket cricketers[]);
void menuCricket(void);
void inputCricket(struct cricket cricketers[], int *currentCount, int amount);
void displayCricket(struct cricket cricketers[], int n);
void searchCricket(struct cricket cricketers[], int n);
void updateCricketer(struct cricket cricketers[], int n);
void deleteCricketer(struct cricket cricketers[], int *n);
int isIdTaken(struct cricket cricketers[], int count, int id);

/*
 * ##########################################################
 * #                                                        #
 * #              MODULE 2: FOOTBALL MANAGEMENT             #
 *                      ALI ABBAS                           #
 * #                                                        #
 * ##########################################################
 */
#define MAX_PLAYERS 100

struct player
{
    int jerseyNumber;
    char name[50];
    char position[30];
    int age;
    int goals;
};

struct player players[MAX_PLAYERS];
int count = 0;
// FOOTBALL FUNCTIONS
void saveFootballData(struct player players[], int count);
int loadFootballData(struct player players[]);
int isJerseyTaken(int jersey);
void addPlayer();
void updatePlayer();
void deletePlayer();
void searchPlayer();
void showAllPlayers();
void printMenuFootball();
void getfootballposition(char *position);
void footballSystem();
/*
 * ##########################################################
 * #                                                        #
 * #              MODULE 3:BADMINTON MODULE                 #
 * #                  MUHAMMAD MAIR                         #
 * ##########################################################
 */
#define MAX_BADMINTON 100

struct badminton
{
    int id;
    char name[50];
    char gender[10];
    char category[20];
    int age;
    int matches_won;
    int matches_lost;
};

struct badminton badmintonPlayers[MAX_BADMINTON];
int p = 0;
// BADMINTON FUNCTIONS
void saveBadmintonData(struct badminton badmintonPlayers[], int p);
int loadBadmintonData(struct badminton badmintonPlayers[]);
void addBadmintonPlayer();
void deleteBadmintonPlayer();
void updateBadmintonPlayer();
void displayBadmintonPlayerByID();
void displayAllBadmintonPlayers();
void printMenuBadminton();
void getgenderchoice(char *gender);
void getcategorychoice(char *category);
void badmintonSystem();

/* -----------------------------
   MAIN FUNCTION
------------------------------*/
int main()
{
    /* -----------------------------
       MAIN MENU
    ------------------------------*/
    while (1)
    {
        int choice;
        printf("\n============================================\n");
        printf("   WELCOME TO SPORT CLUB MANAGEMENT SYSTEM   \n");
        printf("=============================================\n");
        printf("(1) Cricket Management System\n");
        printf("(2) Football Management System\n");
        printf("(3) Badminton Management System\n");
        printf("(4) Exit Program\n");
        printf("============================================\n");
        choice = getValidInt("Your Input: ");

        switch (choice)
        {
        case 1:
            cricketSystem();
            break;
        case 2:
            footballSystem();
            break;
        case 3:
            badmintonSystem();
            break;
        case 4:
            printf("EXITING SPORTS CLUB MANAGEMENT SYSTEM...\n");
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}

/*
 * ##########################################################
 * #                                                        #
 * #                  DATA VALIDATION HANDLING              #
 * #                                                        #
 * ##########################################################
 */
// VALIDATION OF INTEGER
int getValidInt(const char*msg)
{ /*pointer to string we are using pointer so that we can read the message directly from the 
    memory without modifying it*/
    char input[100];
    int value;
    int valid;
   do
    {
        printf("%s", msg);
        scanf("%s", input);
        while (getchar() != '\n')
            ;      // it used for cleaning the buffer to avoid the multiple printing because of data in the buffer
        valid = 1; // assume input is valid

        for (int i = 0; input[i] != '\0'; i++)
        {
            if (input[i] < '0' || input[i] > '9')
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
            printf("Invalid input. Please enter a valid number.\n");
        else
            value = atoi(input); // returning integer to value

    } while (!valid); // if valid is 1 (!valid-->0) loop will stop

    return value; // will return the integer
}

// VALIDATION OF STRING
void getValidstr(char *name, const char *msg)
{ /* Here the first argument will store the valid string in it while the second argument is for
    pointer to char array i.e("enter your name")*/
    int valid;
    do
    {
        printf("%s", msg);
        scanf(" %[^\n]", name); // read full line including spaces
        while (getchar() != '\n')
            ; // clear input buffer

        valid = 1; // assume valid

        for (int i = 0; name[i] != '\0'; i++)
        {
            if ((name[i] < 'A' || name[i] > 'Z') &&
                (name[i] < 'a' || name[i] > 'z') &&
                name[i] != ' ')
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
            printf("Invalid input.Please write correctly\n");

    } while (!valid); // repeat until valid input
}

/*
 * ##########################################################
 * #                                                        #
 * #             FUNCTIONS: CRICKET MANAGEMENT    
 *                         YAZDAAN ALI                      #
 * #                                                        #
 * ##########################################################
 */
/* Filling save/load  cricket system*/
int loadCricketData(struct cricket cricketers[])
{
    FILE *fp = fopen("cricket.dat", "rb"); // open file in read-binary mode
    if (!fp)
        return 0;
    int n = 0;
    if (fread(&n, sizeof(int), 1, fp) != 1)
    {
        fclose(fp);
        return 0;
    }
    if (n > 100) // If the file is corrupted and says more than 100 players, we reset n to 0 to prevent memory overflow.
        n = 0;   // safety
    fread(cricketers, sizeof(struct cricket), n, fp);
    fclose(fp);
    return n;
}
void saveCricketData(struct cricket cricketers[], int n)
{
    FILE *fp = fopen("cricket.dat", "wb");
    if (!fp)
    {
        printf("Error saving cricket data!\n");
        return;
    }
    fwrite(&n, sizeof(int), 1, fp);
    fwrite(cricketers, sizeof(struct cricket), n, fp);
    fclose(fp);
}


void cricketSystem()
{
    struct cricket cricketers[100];
    int num = loadCricketData(cricketers);

    while (1)
    {
        menuCricket();
        int choice;
        choice = getValidInt("Your Input: ");

        switch (choice)
        {
        case 1:
        {
            int amount = getValidInt("ENTER THE NUMBER OF CRICKETERS TO ADD: ");
            if (amount <= 0)
            {
                printf("Invalid number. Returning to menu.\n");
                break;
            }

            inputCricket(cricketers, &num, amount);
            saveCricketData(cricketers, num);
            break;
        }
        case 2:
            displayCricket(cricketers, num);
            printf("\nPress Enter to continue...");
            getchar();
            getchar();
            break;
        case 3:
            searchCricket(cricketers, num);
            printf("\nPress Enter to continue...");
            getchar(); //buffer issue
            getchar();
            break;
        case 4:
            updateCricketer(cricketers, num);
            saveCricketData(cricketers, num);
            break;
        case 5:
            deleteCricketer(cricketers, &num);
            saveCricketData(cricketers, num);
            break;
        case 6:
            printf("Exiting Cricket Management System...\n");
            saveCricketData(cricketers, num);
            return;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}

void menuCricket(void)
{
    printf("\n===========================================\n");
    printf("         CRICKET MANAGEMENT SYSTEM         \n");
    printf("===========================================\n");
    printf("(1) Add New Cricketers\n");
    printf("(2) Display All Cricketers\n");
    printf("(3) Search a Cricketer\n");
    printf("(4) Update a Cricketer\n");
    printf("(5) Delete a Cricketer\n");
    printf("(6) Main Menu\n");
    printf("===========================================\n");
}

/* check if id exists */
int isIdTaken(struct cricket cricketers[], int count, int id)
{
    for (int i = 0; i < count; i++)
        if (cricketers[i].id == id)
            return 1;
    return 0;
}

void inputCricket(struct cricket cricketers[], int *currentCount, int amount)
{
    for (int k = 0; k < amount; k++)
    {
        if (*currentCount >= 100)
        {
            printf("Maximum capacity reached (100). Cannot add more players.\n");
            return;
        }

        int i = *currentCount;
        printf("\n===========================================\n");
        printf("          ENTER DETAILS FOR CRICKETER %d\n", i + 1);
        printf("===========================================\n");

        getValidstr(cricketers[i].name, "Name: ");

        int id;
        while (1)
        {
            id = getValidInt("ID: "); // using input validation
            if (isIdTaken(cricketers, *currentCount, id))
                printf("ID already exists! Enter a different ID.\n");
            else
            {
                cricketers[i].id = id;
                break;
            }
        }

        cricketers[i].age = getValidInt("Age: "); // age

        cricketers[i].score = getValidInt("Score: "); // score

        (*currentCount)++;
    }

    printf("Player(s) added successfully!\n");
}

/* Display all players */
void displayCricket(struct cricket cricketers[], int n)
{
    if (n == 0)
    {
        printf("\nNo cricketers have been added yet!\n");
        return;
    }

    printf("\n===========================================\n");
    printf("           LIST OF CRICKETERS\n");
    printf("===========================================\n");

    for (int i = 0; i < n; i++)
    {
        printf("\n===========================================\n");
        printf("           CRICKETER %d\n", i + 1);
        printf("===========================================\n");
        printf("Name       : %s\n", cricketers[i].name);
        printf("ID Number  : %d\n", cricketers[i].id);
        printf("Age        : %d\n", cricketers[i].age);
        printf("Score      : %d\n", cricketers[i].score);
        printf("===========================================\n");
    }
}

/* Search by ID */
void searchCricket(struct cricket cricketers[], int n)
{
    int id, found = 0;
    id = getValidInt("Enter Cricketer ID to Search: ");

    for (int i = 0; i < n; i++)
    {
        if (cricketers[i].id == id)
        {
            found = 1;
            printf("\n===========================================\n");
            printf("           CRICKETER FOUND\n");
            printf("===========================================\n");
            printf("Name       : %s\n", cricketers[i].name);
            printf("Age        : %d\n", cricketers[i].age);
            printf("Score      : %d\n", cricketers[i].score);
            printf("===========================================\n");
            break;
        }
    }

    if (!found)
        printf("Cricketer not found!\n");
}

/* Menu update*/
void updateCricketer(struct cricket cricketers[], int n)
{
    int id, found = 0;
    id = getValidInt("Enter ID of the cricketer to update: ");

    for (int i = 0; i < n; i++)
    {
        if (cricketers[i].id == id)
        {
            found = 1;
            int choice;
            do // updation menu
            {
                printf("\n===========================================\n");
                printf("           UPDATE CRICKETER MENU\n");
                printf("===========================================\n");
                printf("1. Add Runs (to existing score)\n");
                printf("2. Change Name\n");
                printf("3. Change Age\n");
                printf("4. Change ID\n");
                printf("5. Return to Main Menu\n");
                printf("===========================================\n");
                choice = getValidInt("Your Input: ");

                switch (choice)
                {
                case 1:
                {
                    int newRuns;
                    newRuns = getValidInt("Enter runs scored recently: ");

                    cricketers[i].score += newRuns;
                    printf("Runs updated! Total score: %d\n", cricketers[i].score);
                    break;
                }
                case 2:
                {

                    getValidstr(cricketers[i].name, "Enter new name: ");

                    printf("Name updated successfully!\n");
                    break;
                }
                case 3:
                {
                    cricketers[i].age = getValidInt("Enter new age: ");

                    printf("Age updated successfully!\n");
                    break;
                }
                case 4:
                {
                    int newId;
                    while (1)
                    {
                        newId = getValidInt("Enter new ID: ");

                        int taken = 0;
                        for (int j = 0; j < n; j++)
                        {
                            if (j != i && cricketers[j].id == newId)
                            {
                                taken = 1;
                                break;
                            }
                        }

                        if (!taken)
                            break;

                        printf("This ID is already taken! Enter another.\n");
                    }
                    cricketers[i].id = newId;
                    printf("ID updated successfully!\n");
                    break;
                }
                case 5:
                    printf("Returning to main menu...\n");
                    break;
                default:
                    printf("Invalid choice! Try again.\n");
                }

            } while (choice != 5);

            break;
        }
    }

    if (!found)
        printf("Cricketer with ID %d not found!\n", id);
}

/* Delete by ID */
void deleteCricketer(struct cricket cricketers[], int *n)
{
    int id, found = 0;
    id = getValidInt("Enter ID of the cricketer to delete: ");

    for (int i = 0; i < *n; i++)
    {
        if (cricketers[i].id == id)
        {
            found = 1;
            for (int j = i; j < *n - 1; j++)
            {
                cricketers[j] = cricketers[j + 1];
            }
            (*n)--;
            printf("Cricketer deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Cricketer with ID %d not found!\n", id);
}


/*
 * ##########################################################
 * #                                                        #
 * #           FUNCTION  2: FOOTBALL MANAGEMENT             #
 * #                 ALI ABBAS                              #
 * ##########################################################
 */
/* Save and Load Football Data */
int loadFootballData(struct player players[])
{
    FILE *fp = fopen("football.dat", "rb");
    if (!fp)
        return 0;
    int cnt;    //cnt reads first data in file which was count so if count=1 cnt now becomes 1 as well 
                          //cnt will return the val to count which is in the main function    
    fread(&cnt, sizeof(int), 1, fp);
   fread(players, sizeof(struct player), cnt, fp);
    fclose(fp);
    return cnt;  // cnt = number of saved players
}
void saveFootballData(struct player players[], int count)
{ 
    FILE *fp = fopen("football.dat", "wb");
    if (!fp)
    {
        printf("Error saving football data!\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(players, sizeof(struct player), count, fp);
    fclose(fp);
}



void footballSystem()
{
    count = loadFootballData(players);
    while (1)
    {
        printMenuFootball();
        int choice;
        choice = getValidInt("Your Input: ");

        switch (choice)
        {
        case 1:
            addPlayer();
            saveFootballData(players, count);
            break;
        case 2:
            updatePlayer();
            saveFootballData(players, count);
            break;
        case 3:
            deletePlayer();
            saveFootballData(players, count);
            break;
        case 4:
            showAllPlayers();
            printf("\nPress Enter to continue...");
            getchar();
            getchar(); // Wait for Enter
            break;
        case 5:
            searchPlayer();
            printf("\nPress Enter to continue...");
            getchar();
            getchar(); // Wait for Enter
            break;
        case 6:
            printf("\nExiting Football Management System...\n");
            saveFootballData(players, count);
            return;

        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}

// Check if jersey number is taken
int isJerseyTaken(int jersey) //new jersey and we weill match it with the
{
    for (int i = 0; i < count; i++)
        if (players[i].jerseyNumber == jersey)
            return 1;
    return 0;
}

// Add Player(s)
void addPlayer()
{
    int numPlayers = getValidInt("How many players do you want to add? ");

    for (int k = 0; k < numPlayers; k++)
    {
        if (count >= MAX_PLAYERS)
        {
            printf("Maximum player limit reached!\n");
            return;
        }

        printf("\n===========================================\n");
        printf("          ENTER DETAILS FOR PLAYER %d\n", count + 1);
        printf("===========================================\n");

        int jersey;
        while (1)
        {
            jersey = getValidInt("Jersey Number: ");

            if (isJerseyTaken(jersey))
                printf("This jersey number is already taken! Enter another.\n");
            else
            {
                players[count].jerseyNumber = jersey;
                break;
            }
        }

      
        getValidstr(players[count].name, "Name: ");

        players[count].age = getValidInt("Age: ");

        getfootballposition(players[count].position);

        players[count].goals = getValidInt("Current Goal Count: ");

        count++;
        printf("Player added successfully!\n");
    }
}

// Update Player
void updatePlayer()
{
    int jersey, found = 0, choice;
    jersey = getValidInt("\nEnter Jersey Number to Update: ");

    for (int i = 0; i < count; i++)
    {
        if (players[i].jerseyNumber == jersey)
        {
            found = 1;
            do
            {
                printf("\n===========================================\n");
                printf("           UPDATE PLAYER MENU\n");
                printf("===========================================\n");
                printf("1. Update Goal Count (Add new goals)\n");
                printf("2. Change Player Name\n");
                printf("3. Change Jersey Number\n");
                printf("4. Change Position\n");
                printf("5. Change Age\n");
                printf("6. Return to Main Menu\n");
                printf("===========================================\n");
                choice = getValidInt("Your Input: ");

                switch (choice)
                {
                case 1:
                {
                    int newGoals = getValidInt("Enter goals scored recently: ");

                    players[i].goals += newGoals;
                    printf("Goal count updated! Total goals: %d\n", players[i].goals);
                    break;
                }
                case 2:
                  
                    getValidstr(players[i].name, "Enter new name: ");

                    printf("Name updated successfully!\n");
                    break;
                case 3:
                {
                    int newJersey;

                    newJersey = getValidInt("Enter new Jersey Number: ");

                    while (1)
                    {
                        int taken = 0;
                        for (int j = 0; j < count; j++)
                        {
                            if (j != i && players[j].jerseyNumber == newJersey)
                            {
                                taken = 1;
                                break;
                            }
                        }
                        if (!taken)
                            break;
                        newJersey = getValidInt("This jersey number is already taken! Enter another: ");
                    }
                    players[i].jerseyNumber = newJersey;
                    printf("Jersey number updated successfully!\n");
                    break;
                }
                case 4:
                   
                    getfootballposition(players[i].position);
                    printf("Position updated successfully!\n");
                    break;
                case 5:
                    players[i].age = getValidInt("Enter new age: ");

                    break;
                case 6:
                    printf("Returning to main menu...\n");
                    break;
                default:
                    printf("Invalid choice! Try again.\n");
                }
            } while (choice != 6);
            break;
        }
    }

    if (!found)
        printf("Player not found!\n");
}

// Delete Player
void deletePlayer()
{
    int jersey, found = 0;
    jersey = getValidInt("\nEnter Jersey Number to Delete: ");

    for (int i = 0; i < count; i++)
    {
        if (players[i].jerseyNumber == jersey)
        {
            found = 1;
            for (int j = i; j < count - 1; j++)
                players[j] = players[j + 1];
            count--;
            printf("Player deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Player not found!\n");
}

// Search Player
void searchPlayer()
{
    int jersey, found = 0;
    jersey = getValidInt("\nEnter Jersey Number to Search: ");

    for (int i = 0; i < count; i++)
    {
        if (players[i].jerseyNumber == jersey)
        {
            found = 1;
            printf("\n===========================================\n");
            printf("             PLAYER FOUND\n");
            printf("===========================================\n");
            printf("Jersey Number : %d\n", players[i].jerseyNumber);
            printf("Name          : %s\n", players[i].name);
            printf("Age           : %d\n", players[i].age);
            printf("Position      : %s\n", players[i].position);
            printf("Goals Scored  : %d\n", players[i].goals);
            printf("===========================================\n");
            break;
        }
    }

    if (!found)
        printf("No player found with this jersey number.\n");
}

// Show All Players
void showAllPlayers()
{
    if (count == 0)
    {
        printf("\nNo players in the club yet.\n");
        return;
    }

    printf("\n===========================================\n");
    printf("             LIST OF PLAYERS\n");
    printf("===========================================\n");

    for (int i = 0; i < count; i++)
    {
        printf("\n-------------------------------------------\n");
        printf("Player %d\n", i + 1);
        printf("Jersey Number : %d\n", players[i].jerseyNumber);
        printf("Name          : %s\n", players[i].name);
        printf("Age           : %d\n", players[i].age);
        printf("Position      : %s\n", players[i].position);
        printf("Goals Scored  : %d\n", players[i].goals);
        printf("-------------------------------------------\n");
    }
}

void printMenuFootball()
{
    printf("\n===========================================\n");
    printf("         FOOTBALL MANAGEMENT SYSTEM        \n");
    printf("===========================================\n");
    printf("(1) Add Player\n");
    printf("(2) Update Player\n");
    printf("(3) Delete Player\n");
    printf("(4) Show All Players\n");
    printf("(5) Search Player\n");
    printf("(6) Main Menu\n");
    printf("===========================================\n");
}


/*
 * ##########################################################
 * #                                                        #
 * #            FUNCTION 3: BADMINTON MANAGEMENT            #
 *                       MUHAMMAD MAIR                      #                   
 * #                                                        #
 * ##########################################################
 */
//load and save data of badminton system 
int loadBadmintonData(struct badminton badmintonPlayers[])
{
    FILE *fp = fopen("badminton.dat", "rb");
    if (!fp)
    {
        return 0;
    }
         int cnt;          //cnt reads first data in file which was p so if p=1 cnt now becomes 1 as well 
                          //cnt will return the val to p which in the main function  
        fread(&cnt, sizeof(int), 1, fp);
        fread(badmintonPlayers, sizeof(struct badminton), cnt, fp);
        fclose(fp);
        return cnt;
    
}
 void saveBadmintonData(struct badminton badmintonPlayers[], int p)
{
    FILE *fp = fopen("badminton.dat", "wb");
    if (!fp)
    {
        printf("Error saving badminton data!\n");
        return;
    }
    fwrite(&p, sizeof(int), 1, fp);
    fwrite(badmintonPlayers, sizeof(struct badminton), p, fp);
    fclose(fp);
}

void badmintonSystem()
{
    int choice;
    p = loadBadmintonData(badmintonPlayers);

    do
    {
        printMenuBadminton();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBadmintonPlayer();
            saveBadmintonData(badmintonPlayers, p);
            break;
        case 2:
            deleteBadmintonPlayer();
            saveBadmintonData(badmintonPlayers, p);
            break;
        case 3:
            updateBadmintonPlayer();
            saveBadmintonData(badmintonPlayers, p);
            break;
        case 4:
            displayBadmintonPlayerByID();
            printf("\nPress Enter to continue...");
            getchar();
            getchar();
            break;
        case 5:
            displayAllBadmintonPlayers();
            printf("\nPress Enter to continue...");
            getchar();
            getchar();
            break;
        case 6:
            printf("Exiting Badminton Management System...\n");
            saveBadmintonData(badmintonPlayers, p);
            return;
        default:
            printf("Invalid option!\n");
        }

    } while (choice != 6);
}

// Add Player
void addBadmintonPlayer()
{
    int amount = getValidInt("How many players would you like to add? ");

    for (int j = 0; j < amount; j++)
    {
        if (p >= MAX_BADMINTON)
        {
            printf("Maximum players reached.\n");
            return;
        }

        int newID, exists;
        printf("\n===========================================\n");
        printf("           ADDING PLAYER %d\n", j + 1);
        printf("===========================================\n");

        while (1)
        {
            exists = 0;
            newID = getValidInt("Enter Player ID: ");

            for (int i = 0; i < p; i++)
            {
                if (badmintonPlayers[i].id == newID)
                {
                    exists = 1;
                    break;
                }
            }
            if (!exists)
                break;

            printf("ID already exists! Enter a different ID.\n");
        }

        badmintonPlayers[p].id = newID;

        getValidstr(badmintonPlayers[p].name, "Enter Player Name: ");

        getgenderchoice(badmintonPlayers[p].gender);

        badmintonPlayers[p].age = getValidInt("Enter Player Age: ");

        getcategorychoice(badmintonPlayers[p].category);

        badmintonPlayers[p].matches_won = getValidInt("Enter Matches Won: ");

        badmintonPlayers[p].matches_lost = getValidInt("Enter Matches Lost: ");

        p++;
        printf("Player added successfully!\n");
    }
}

// Delete Player
void deleteBadmintonPlayer()
{
    int id, found = 0;
    id = getValidInt("Enter Player ID to delete: ");

    for (int i = 0; i < p; i++)
    {
        if (badmintonPlayers[i].id == id)
        {
            for (int j = i; j < p - 1; j++)
                badmintonPlayers[j] = badmintonPlayers[j + 1];
            p--;
            found = 1;
            printf("Player deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("ID not found!\n");
}

// Update Player with Menu

void updateBadmintonPlayer()
{
    int id, found = 0;
    id = getValidInt("Enter Player ID to update: ");

    for (int i = 0; i < p; i++)
    {
        if (badmintonPlayers[i].id == id)
        {
            found = 1;
            int choice;
            do
            {
                printf("\n===========================================\n");
                printf("           UPDATE PLAYER MENU\n");
                printf("===========================================\n");
                printf("1. Add Matches Won\n");
                printf("2. Add Matches Lost\n");
                printf("3. Change Name\n");
                printf("4. Change Age\n");
                printf("5. Change ID\n");
                printf("6. Change Gender\n");
                printf("7. Change Category\n");
                printf("8. Return to Main Menu\n");
                printf("===========================================\n");
                choice = getValidInt("Your Input: ");

                switch (choice)
                {
                case 1:
                {
                    int newWins;
                    newWins = getValidInt("Enter matches won recently: ");

                    badmintonPlayers[i].matches_won += newWins;
                    printf("Matches won updated! Total: %d\n", badmintonPlayers[i].matches_won);
                    break;
                }
                case 2:
                {
                    int newLoss;
                    newLoss = getValidInt("Enter matches lost recently: ");

                    badmintonPlayers[i].matches_lost += newLoss;
                    printf("Matches lost updated! Total: %d\n", badmintonPlayers[i].matches_lost);
                    break;
                }
                case 3:
              
                    getValidstr(badmintonPlayers[i].name, "Enter new name: ");

                    printf("Name updated successfully!\n");
                    break;
                case 4:
                    badmintonPlayers[i].age = getValidInt("Enter new age: ");

                    printf("Age updated successfully!\n");
                    break;
                case 5:
                {
                    int newID;
                    while (1)
                    {
                        newID = getValidInt("Enter new ID: ");

                        int taken = 0;
                        for (int j = 0; j < p; j++)
                        {
                            if (j != i && badmintonPlayers[j].id == newID)
                            {
                                taken = 1;
                                break;
                            }
                        }

                        if (!taken)
                            break;

                        printf("This ID is already taken! Enter another.\n");
                    }
                    badmintonPlayers[i].id = newID;
                    printf("ID updated successfully!\n");
                    break;
                }
                case 6:
                    
                    getgenderchoice(badmintonPlayers[i].gender);
                    printf("Gender updated successfully!\n");
                    break;
                case 7:
                    
                    getcategorychoice(badmintonPlayers[i].category);
                    printf("Category updated successfully!\n");
                    break;
                case 8:
                    printf("Returning to main menu...\n");
                    break;
                default:
                    printf("Invalid choice! Try again.\n");
                }

            } while (choice != 8);

            break;
        }
    }

    if (!found)
        printf("Player with ID %d not found!\n", id);
}

// Display Player by ID
void displayBadmintonPlayerByID()
{
    int id, found = 0;
    id = getValidInt("Enter Player ID to display: ");

    for (int i = 0; i < p; i++)
    {
        if (badmintonPlayers[i].id == id)
        {
            found = 1;
            printf("\n===========================================\n");
            printf("             PLAYER INFORMATION\n");
            printf("===========================================\n");
            printf("Name          : %s\n", badmintonPlayers[i].name);
            printf("Gender        : %s\n", badmintonPlayers[i].gender);
            printf("Age           : %d\n", badmintonPlayers[i].age);
            printf("Category      : %s\n", badmintonPlayers[i].category);
            printf("Matches Won   : %d\n", badmintonPlayers[i].matches_won);
            printf("Matches Lost  : %d\n", badmintonPlayers[i].matches_lost);
            printf("===========================================\n");
            break;
        }
    }

    if (!found)
        printf("ID not found!\n");
}

// Display All Players
void displayAllBadmintonPlayers()
{
    if (p == 0)
    {
        printf("No players have been added yet!\n");
        return;
    }

    for (int i = 0; i < p; i++)
    {
        printf("\n===========================================\n");
        printf("PLAYER %d\n", i + 1);
        printf("===========================================\n");
        printf("Name        : %s\n", badmintonPlayers[i].name);
        printf("Gender      : %s\n", badmintonPlayers[i].gender);
        printf("ID          : %d\n", badmintonPlayers[i].id);
        printf("Age         : %d\n", badmintonPlayers[i].age);
        printf("Category    : %s\n", badmintonPlayers[i].category);
        printf("Matches Won : %d\n", badmintonPlayers[i].matches_won);
        printf("Matches Lost: %d\n", badmintonPlayers[i].matches_lost);
        printf("===========================================\n");
    }
}

void printMenuBadminton()
{
    printf("\n===========================================\n");
    printf("         BADMINTON MANAGEMENT SYSTEM       \n");
    printf("===========================================\n");
    printf("(1) Add Players\n");
    printf("(2) Delete Player\n");
    printf("(3) Update Player\n");
    printf("(4) Search Player\n");
    printf("(5) Display All Players\n");
    printf("(6) Main Menu\n");
    printf("===========================================\n");
    printf("Your Input: ");
}



void getgenderchoice(char *gender)
{
    int choice;

    while (1)
    {
        printf("\nSelect Gender:\n");
        printf("1. Male\n");
        printf("2. Female\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;

        if (choice == 1)
        {
            strcpy(gender, "Male");
            break;
        }
        else if (choice == 2)
        {
            strcpy(gender, "Female");
            break;
        }
        else
        {
            printf("Invalid choice! Try again.\n");
        }
    }
}

void getcategorychoice(char *category)
{
    int choice;
    printf("Enter Category\n");
    printf("(1).Singles:\n");
    printf("(2).Doubles:\n");
    printf("Your selection: ");
    while (1)
    {
        scanf("%d", &choice);
        if (choice == 1)
        {
            strcpy(category, "Singles");
            break;
        }
        else if (choice == 2)
        {
            strcpy(category, "Doubles");
            break;
        }
        else
        {
            printf("Invalid choice! Try again.\n");
        }
    }
}

void getfootballposition(char *position)
{
    int choice;
    printf("Enter Category\n");
    printf("(1).Forward:\n");
    printf("(2).Midfielder:\n");
    printf("(3).Defender:\n");
    printf("(4).Goalkeeper:\n");
    printf("Your selection: ");
    while (1)
    {
        scanf("%d", &choice);
        if (choice == 1)
        {
            strcpy(position, "Forward");
            break;
        }
        else if (choice == 2)
        {
            strcpy(position, "Midfielder");
            break;
        }
        else if (choice == 3)
        {
            strcpy(position, "Defender");
            break;
        }

        else if (choice == 4)
        {
            strcpy(position, "Goalkeeper");
            break;
        }
        else
        {
            printf("Invalid choice! Try again.\n");
        }
    }
}
