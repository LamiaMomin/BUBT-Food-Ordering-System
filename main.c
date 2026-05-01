#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_CART_SIZE 100
#define MAX_USERS 100
#define MAX_FOOD_ITEMS 11
#define MAX_ORDER_ITEMS 50
#define ADMIN_PASSWORD "password123"

void cls(){
    system("cls");
}
// Define user structure
typedef struct {
    char name[50];
    int id;
    char email[50];
    char password[50];
    char mobile[20];
    float total_bill;
    float discount;
} User;

// Define food structure
typedef struct {
    char cname[30];
    char name[50];
    int quantity;
    float price;
    float discount;
} Food;

Food canteen1[MAX_FOOD_ITEMS]={{"BUBT Building-3 Canteen","Chicken Burger",20,50.0},{"BUBT Building-3 Canteen","Burger",16, 55},{"BUBT Building-3 Canteen","Chicken Roll",22, 35},
                               {"BUBT Building-3 Canteen","Sandwich",25, 45},{"BUBT Building-3 Canteen","Pizza",8, 70},{"BUBT Building-3 Canteen","Chicken nugget",4, 20},
                               {"BUBT Building-3 Canteen","Chips",20, 10},{"BUBT Building-3 Canteen","French Fries",15, 60},{"BUBT Building-3 Canteen","Ice cream",24, 50},
                               {"BUBT Building-3 Canteen","Noodles",16, 350}};



Food canteen2[MAX_FOOD_ITEMS]={{"BUBT BBA Canteen","Burger",20,50.0},{"BUBT BBA Canteen","Khichuri",16, 55},{"BUBT BBA Canteen","Chicken Roll",22, 45},
                               {"BUBT BBA Canteen","Sandwich",25, 45},{"BUBT BBA Canteen","Pizza(Family size)",8, 70},{"BUBT BBA Canteen","Ice cream",12, 200},
                               {"BUBT BBA Canteen","Beef Burger",7, 80},{"BUBT BBA Canteen","French Fries",19, 100},{"BUBT BBA Canteen","Club Sandwich",20, 180},
                               {"BUBT BBA Canteen","Cake",18, 350}};

// Define global variables
User users[MAX_USERS];
int user_count = 0;
Food menu[MAX_FOOD_ITEMS];
int menu_count = 0;
Food order1[MAX_ORDER_ITEMS];
int order_count = 0;
Food cart[MAX_CART_SIZE];
int cart_count = 0;
float total_bill = 0;
float discount =0;
int a=0;


// Function prototypes
void print_customer_menu();
void handle_customer_input(int input);
void signup();
int login();
void Canteen1_initialize();
void Canteen2_initialize();
void search_by_canteen();
void search_by_food();
void add_to_cart(Food food, int quantity);
void show_cart();
void payment_method(int choice);
void finalize_order();
void print_admin_menu();
void handle_admin_input(int input);
void show_menu();
void add_food();
void delete_food();
void show_instant_order_preview();
void show_total_cash_today();



int main() {
    system("COLOR B5");
    FILE *fp;
    fp = fopen("users.dat", "rb");
    if (fp != NULL) {
        User user;
        while (fread(&user, sizeof(User), 1, fp)) {
            users[user_count] = user;
            user_count++;
        }
        fclose(fp);
    }
    int choice;
    printf("\n\n\t**********************Welcome to BUBT Food Ordering System(CFOS)**********************\n\n");
    do {
        printf("Please select an option:\n\n");Sleep(300);
        printf("\t1) Customer\n");Sleep(300);
        printf("\t2) Admin Panel\n");Sleep(300);
        printf("\t3) Exit\n\n");Sleep(300);
        printf("Enter your choice: ");Sleep(300);
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input.\n");Sleep(300);
            return;
        }
        cls();
        switch (choice) {
            case 1:
                print_customer_menu();
                break;
            case 2:
                printf("\nEnter admin password: ");Sleep(300);
                char admin_password[50];
                int i;
                char c=' ';
                while(i<20)
                {
                    admin_password[i]=getch();
                    c=admin_password[i];
                    if(c=='\r') break;
                    else printf("*");
                    i++;
                }
                admin_password[i]='\0';
                if (strcmp(admin_password, ADMIN_PASSWORD) == 0) {
                    print_admin_menu();
                } else {
                    printf("\nIncorrect password\n\n");
                }
                break;
            case 3:
                printf("\n\n\tGoodbye!\n\n");
                exit(0);
            default:
                printf("\nInvalid choice. Please enter a valid option.\n\n");
        }
    } while (1);

    return 0;
}
void print_customer_menu() {
    int input;
    do {
        printf("\n\n\t**********Customer Menu**********\n\n");
        printf("Please select an option:\n\n");Sleep(300);
        printf("\t1) Signup\n");Sleep(300);
        printf("\t2) Login\n");Sleep(300);
        printf("\t3) Back\n\n");Sleep(300);
        printf("Enter your choice: ");Sleep(300);
        scanf("%d", &input);
        cls();
        handle_customer_input(input);

    } while (input != 3);
}
void handle_customer_input(int input) {
    switch (input) {
        case 1:
            signup();
            break;
        case 2:
            if (login()!=-1) {
                int choice;
                cls();
                do {
                    printf("\n\n\t**********Search Menu**********\n\n");
                    printf("Please select an option:\n\n");Sleep(300);
                    printf("\t1) Search by Canteen\n");Sleep(300);
                    printf("\t2) Search by Food\n");Sleep(300);
                    printf("\t3) Show Cart\n");Sleep(300);
                    printf("\t4) Finalize Order\n");Sleep(300);
                    printf("\t5) Logout\n\n");Sleep(300);
                    printf("Enter your choice: ");Sleep(300);
                    scanf("%d", &choice);
                    cls();
                    switch (choice) {
                        case 1:
                            search_by_canteen();
                            break;
                        case 2:
                            search_by_food();
                            break;
                        case 3:
                            show_cart();
                            break;
                        case 4:
                            finalize_order();
                            break;
                        case 5:
                            printf("\nLogged out successfully\n\n");
                            return;
                        default:
                            printf("\nInvalid choice. Please enter a valid option.\n\n");
                    }
                } while (1);
            } else {
                printf("\nIncorrect email or password\n\n");
            }
            break;
        case 3:
            printf("\n\n\tGoing back to main menu...\n\n");
            return;
        default:
            printf("\nInvalid choice. Please enter a valid option.\n\n");
    }
}

void signup(){
    cls();
    printf("\n\n\t**********Signup**********\n\n");
    User user;
    while (1) {
        printf("Enter your name: ");
        fflush(stdin);
        fgets(user.name, 50, stdin);
        user.name[strcspn(user.name, "\n")] = 0;

        int valid = 1;
        for (int i = 0; i < strlen(user.name); i++) {
            if (!isalpha(user.name[i]) && !isspace(user.name[i])) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            break;
        }
        printf("\tInvalid name! Please enter a name with alphabets only.\n\t");
    }
    // Get user's email, checking for @ and .
    while (1) {
        printf("Enter your email: ");
        fflush(stdin);
        fgets(user.email, 50, stdin);
        user.email[strcspn(user.email, "\n")] = 0;

        if (strlen(user.email) < 5 || strchr(user.email, '@') == NULL || strchr(user.email, '.') == NULL) {
            printf("\n\nInvalid email! Please enter a valid email address.\n");
        } else {
            break;
        }
    }
    // Get user's mobile, checking for digits only
    while (1) {
        printf("Enter your mobile number: ");
        fflush(stdin);
        fgets(user.mobile, 20, stdin);
        user.mobile[strcspn(user.mobile, "\n")] = 0;

        int valid = 1;
        for (int i = 0; i < strlen(user.mobile); i++) {
            if (!isdigit(user.mobile[i])) {
                valid = 0;
                break;
            }
        }
        if (valid && strlen(user.mobile) == 11) {
            break;
        } else {
            printf("\nInvalid mobile number! Please enter a valid 11-digit number.\n");
        }
    }
    // Get user's password, checking for length and complexity
    while (1) {
        printf("Enter a password: ");
        fflush(stdin);
        fgets(user.password, 50, stdin);
        user.password[strcspn(user.password, "\n")] = 0;

        int valid = 1;
        if (strlen(user.password) < 5 || strlen(user.password) > 12) {
            valid = 0;
            printf("Password length must be between 5 to 12 characters.\n");
        } else {
            for (int i = 0; i < strlen(user.password); i++) {
                    if (!isupper(user.password[i]) && !islower(user.password[i]) && !isdigit(user.password[i]) && isalnum(user.password[i])) {
                        valid = 0;
                        printf("Password must contain at least one uppercase letter, one lowercase letter, one digit, and one special character.\n");
                }
            }
        }
        if (valid) {
            break;
        }
        printf("\nInvalid password! Please enter a valid password.\n");
    }
    user.id = user_count + 1;
    user.total_bill = 0.0;
    user.discount = 0.0;

    // Save user information to file
    FILE *fp;
    fp = fopen("users.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&user, sizeof(User), 1, fp);
    fclose(fp);

    users[user_count] = user;
    user_count++;

    printf("\n\n\tSignup successful! Please login to continue.\n");
    printf("\n\n\tPress any key to continue...");Sleep(300);
    getch();
}

int login() {
    char email[50], password[50];
    printf("\n\n\t**********Login**********\n\n");
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            printf("\nLogin successful. Welcome %s!\n\n", users[i].name);
            Sleep(900);
            return i;
        }
    }
    return -1;
}

void Canteen1_initialize(){
            printf("\t\tWelcome to BUBT Building-3 Canteen\t\t");Sleep(400);
            printf("\n\n\t  Food Code       Name                        Quantity      Price      ");Sleep(300);
            printf("\n\t");
            printf("-----------------------------------------------------------------------");Sleep(300);
            for (int i = 0; i < MAX_FOOD_ITEMS; i++) {
                printf("\n\t");
                printf("  %2d        |  %-25s      |    %2d      |  %0.2f   ",i+1, canteen1[i].name, canteen1[i].quantity, canteen1[i].price);Sleep(300);
                printf("\n\t");
                printf("-----------------------------------------------------------------------");Sleep(300);
            }
            printf("\n\n");
}
void Canteen2_initialize(){
            printf("\t\tWelcome to BUBT BBA Canteen\t\t");Sleep(400);
            printf("\n\n\t  Food Code       Name                       Quantity      Price      ");Sleep(300);
            printf("\n\t");
            printf("-----------------------------------------------------------------------");Sleep(300);
            for (int i = 0; i < MAX_FOOD_ITEMS; i++) {
                printf("\n\t");
                printf("  %2d      |  %-25s      |    %2d      |  %0.2f   ",i+1, canteen2[i].name, canteen2[i].quantity, canteen2[i].price);Sleep(300);
                printf("\n\t");
                printf("-----------------------------------------------------------------------");Sleep(300);
            }
            printf("\n\n");
}
void search_by_canteen() {
    printf("\n\n\tSearch by Canteen\n\n");Sleep(300);
    int input;
    printf("Please select an option:\n");Sleep(300);
    printf("\t1) Building-2 Canteen\n");Sleep(300);
    printf("\t2) BBA Canteen\n");Sleep(300);
    printf("\t3) Back\n");Sleep(300);
    printf("Enter canteen number: ");
    scanf("%d",&input);
    switch(input){
        case 1:
            Canteen1_initialize();
            break;
        case 2:
            Canteen2_initialize();
            break;
        case 3:
            return;
        default:
            printf("\nPlease Enter the valid choice\n\n");
            return;
    }
    int item_choice;
    int d=1;
    while(d!=0){
        printf("Enter item number to add to cart (enter 0 to cancel): ");
        scanf("%d", &item_choice);
        if (item_choice < 0 || item_choice > MAX_FOOD_ITEMS) {
            printf("\nInvalid choice. Please enter a valid item number.\n");
        } else if (item_choice == 0) {
            cls();
            return;
        } else {
            int qunti;
            printf("Enter quantity: ");
            scanf("%d", &qunti);
            if (qunti <= 0) {
                printf("\nQuantity should be greater than zero.\n");
            } else if (order_count + qunti > MAX_CART_SIZE) {
                printf("\nCannot add more items. Cart size limit exceeded.\n");
            } else {
                if(input==1){
                    add_to_cart(canteen1[item_choice-1], qunti);
                }
                else if(input==2){
                    add_to_cart(canteen2[item_choice-1], qunti);
                }
            }
        }
    }
}
void search_by_food() {
    printf("\n\n\tSearch by Food\n\n");
    char food[50];
    printf("Enter food name: ");
    scanf("%s",food);
    printf("\nResults");
    int count = 0;
    printf("\n\n\t  Food Code       Name                     Quantity      Price       Canteen Name");Sleep(300);
    printf("\n\t");
    printf("--------------------------------------------------------------------------------------");Sleep(300);
    printf("\n\t");
    for (int i = 0; i < MAX_FOOD_ITEMS; i++) {
        if (strstr(canteen1[i].name, food) != NULL) {
            printf("  %2d      |  %-25s   |    %2d      |  %0.2f     %s", count+1, canteen1[i].name, canteen1[i].quantity, canteen1[i].price,canteen1->cname);Sleep(300);
            printf("\n\t");
            printf("--------------------------------------------------------------------------------------");Sleep(300);
            printf("\n\t");
            menu[count]=canteen1[i];
            count++;
        }
    }
    for (int i = 0; i < MAX_FOOD_ITEMS; i++) {
        if (strstr(canteen2[i].name, food) != NULL) {
            printf("  %2d      |  %-25s   |    %2d      |  %0.2f     %s", count+1, canteen2[i].name, canteen2[i].quantity, canteen2[i].price,canteen2->cname);Sleep(300);
            printf("\n\t");
            printf("--------------------------------------------------------------------------------------");Sleep(300);
            printf("\n\t");
            menu[count]=canteen2[i];
            count++;
        }
    }
    if (count== 0) {
        printf("\n\n\tNo results found for food '%s'\n", food);
    } else {
        int item_choice;
        printf("\n\nEnter item number to add to cart (enter 0 to cancel): ");
        if (scanf("%d", &item_choice) != 1) {
            printf("\nInvalid input. Please enter a numeric item number.\n");
            cls(); // Assuming cls() is a function to clear screen
            return;
        }
        if (item_choice < 0 || item_choice > count) {
            printf("\nInvalid choice. Please enter a valid item number.\n");
        } else if (item_choice == 0) {
            printf("\nCancelled\n");
            cls();
            return;
        } else {
            int qunty;
            printf("\nEnter quantity: ");
            scanf("%d", &qunty);
            if (qunty <= 0) {
                printf("\nQuantity should be greater than zero.\n");
            } else if (order_count + qunty > MAX_CART_SIZE) {
                printf("\nCannot add more items. Cart size limit exceeded.\n");
            } else if (qunty > menu[item_choice-1].quantity) {
                printf("\nQuantity exceeds available quantity.\n");
            } else {
                add_to_cart(menu[item_choice-1], qunty);
            }
        }
    }
}
// Function to add a food item to the cart
void add_to_cart(Food food, int quantity) {
    // Check if the cart is already full
    if (cart_count == MAX_CART_SIZE) {
        printf("\n\tSorry, the cart is full.\n");
        return;
    }
    // Check if there is enough quantity of the selected food item
    if (quantity > food.quantity) {
        printf("\n\tSorry, there is not enough quantity of the selected food item.\n\n");
        return;
    }
    // Check if the quantity entered is valid
    if (quantity <= 0) {
        printf("Please enter a valid quantity.\n\n");
        return;
    }

    // Add the food item to the cart
    cart[cart_count] = food;
    cart[cart_count].quantity = quantity;
    total_bill += food.price * quantity;
    food.quantity -= quantity;
    cart_count++;
    printf("Item added to cart\n\n");
}

void show_cart() {
    float total = 0;
    printf("\n\tCart Contents:\n");
    printf("\n\n\t  Name                       Quantity      Price      Total");Sleep(300);
    printf("\n\t");
    printf("-----------------------------------------------------------------------");Sleep(300);
    printf("\n\t");
    for (int i = 0; i < cart_count; i++) {
        printf("  %-25s  |    %2d      |  %0.2f   |  %0.2f   ",  cart[i].name, cart[i].quantity, cart[i].price, cart[i].price * cart[i].quantity);Sleep(300);
        printf("\n\t");
        printf("-----------------------------------------------------------------------");Sleep(300);
        printf("\n\t");
        total += cart[i].price * cart[i].quantity;
    }
    printf("  Total                                                : %0.2f\n", total);Sleep(300);

    printf("\t-----------------------------------------------------------------------\n");
}

void payment_method(int choice){
    int num;
    char pin[20];
    switch(choice){
    case 1:
        printf("\n\t===>THANK YOU<===\n\n\n");
        break;
    case 2:
        printf("\nEnter your card number: ");
        scanf("%d",&num);
        printf("\nEnter your pin number: ");
        int i;
                char c=' ';
                while(i<20)
                {
                    pin[i]=getch();
                    c=pin[i];
                    if(c=='\r') break;
                    else printf("*");
                    i++;
                }
                pin[i]='\0';
    }
}

// Function to finalize the order and update the quantity of food items
void finalize_order() {
    // Check if the cart is empty
    if (cart_count == 0) {
        printf("\nThe cart is empty.\n");
        return;
    }

    show_cart();

    // Calculate discounted total bill, if applicable
    if(total_bill >= 300 && total_bill < 500) {
        discount = (total_bill * 0.05);
        printf("\t  Discount: %0.2f\n",discount);Sleep(300);
        printf("\t-----------------------------------------------------------------------\n");Sleep(300);
        printf("\t  Total bill (after 5%% discount): %0.2f\n", total_bill-discount);Sleep(300);
        printf("\t-----------------------------------------------------------------------\n\n");Sleep(300);
    }
    else if(total_bill >= 500) {
        discount = (total_bill * 0.1);
        printf("\t  Discount: %0.2f\n",discount);Sleep(300);
        printf("\t-----------------------------------------------------------------------\n");Sleep(300);
        printf("\t  Total bill (after 10%% discount): %0.2f\n", total_bill-discount);Sleep(300);
        printf("\t-----------------------------------------------------------------------\n\n");Sleep(300);
    }
    else{
        discount =0.0;
    }
    int confirm;
    printf("\n\nDo you want to confirm your order?\n");
    printf("\t1) Yes\n");Sleep(300);
    printf("\t2) No\n");Sleep(300);
    printf("Enter your choice: ");
    scanf("%d", &confirm);
    if(confirm==1){
        printf("\nPayment Method:\n");
        printf("\t1.Cash\n\t2.Credit\n\t");Sleep(300);
        int c;
        scanf("%d",&c);
        payment_method(c);

        // Update the quantity of food items and order history
        for (int i = 0; i < cart_count; i++) {
            for (int j = 0; j < MAX_FOOD_ITEMS; j++) {
                if (strcmp(cart[i].name, canteen1[j].name) == 0) {
                    if (cart[i].quantity > canteen1[j].quantity) {
                        printf("Sorry, there is not enough quantity of %s in Canteen 1.\n", cart[i].name);
                        return;
                    }
                    canteen1[j].quantity -= cart[i].quantity;
                }
                else if (strcmp(cart[i].name, canteen2[j].name) == 0) {
                    if (cart[i].quantity > canteen2[j].quantity) {
                        printf("Sorry, there is not enough quantity of %s in Canteen 2.\n", cart[i].name);
                        return;
                    }
                    canteen2[j].quantity -= cart[i].quantity;
                }
            }
            order1[order_count] = cart[i];
            order1[a].discount = discount;
            order_count++;
        }

        // Reset the cart and total bill
        memset(cart, 0, sizeof(cart));
        cart_count = 0;
        total_bill = 0;
        a++;
        printf("\n\nThe order has been placed successfully.\n");
    }else{
        cls();
        return;
    }

}

void print_admin_menu() {
    int input;
    do {
        printf("\n\n\tAdmin Panel\n\n");
        printf("Please select an option:\n\n");
        printf("\t1) Show Menu\n");Sleep(300);
        printf("\t2) Add Food\n");Sleep(300);
        printf("\t3) Delete Food\n");Sleep(300);
        printf("\t4) Show Instant Order Preview\n");Sleep(300);
        printf("\t5) Show Total Cash Today\n");Sleep(300);
        printf("\t6) Logout\n\n");Sleep(300);
        printf("Enter your choice: ");
        scanf("%d", &input);
        cls();
        handle_admin_input(input);

    } while (input != 6);
}

void handle_admin_input(int input) {
    switch (input) {
        case 1:
            show_menu();
            break;
        case 2:
            add_food();
            break;
        case 3:
            delete_food();
            break;
        case 4:
            show_instant_order_preview();
            break;
        case 5:
            show_total_cash_today();
            break;
        case 6:
            printf("\n\n\tLogged out successfully...\n\n");
            return;
        default:
            printf("\nInvalid choice. Please enter a valid option.\n\n");
    }
}
void show_menu() {
    printf("\n\tMenu\n\n");
    Canteen1_initialize();
    Canteen2_initialize();
}
void add_food() {
    char name[50];
    float price;
    int quantity;
    int canteen_choice;

    printf("Enter the name of the food item: ");
    scanf("%s", name);

    printf("Enter the price of the food item: ");
    scanf("%f", &price);

    printf("Enter the quantity of the food item: ");
    scanf("%d", &quantity);

    printf("Enter the canteen for the food item (1/2): ");
    scanf("%d", &canteen_choice);

    Food* canteen;
    if (canteen_choice == 1) {
        canteen = canteen1;
    } else if(canteen_choice == 2) {
        canteen = canteen2;
    } else{
        printf("Invalid choice. Please enter 1 or 2.\n");
    }
    for (int i = 0; i < MAX_FOOD_ITEMS; i++) {
        if (strlen(canteen[i].name) == 0) {
            strcpy(canteen[i].name, name);
            canteen[i].price = price;
            canteen[i].quantity = quantity;
            printf("The food item has been added to %s.\n",canteen->cname);
            return;
        }
    }
    printf("\n\nSorry, %s menu is already full.\n",canteen->cname);

}

void delete_food() {
    char name[50];
    int canteen_choice;

    printf("Enter the name of the food item to delete: ");
    scanf("%s", name);

    // Check if the food item exists in any canteen
    int item_found = 0;
    for (int i = 0; i < MAX_FOOD_ITEMS; i++) {
        if (strcmp(canteen1[i].name, name) == 0 || strcmp(canteen2[i].name, name) == 0) {
            item_found = 1;
            break;
        }
    }
    if (!item_found) {
        printf("The food item does not exist in any canteen.\n");
        return;
    }

    printf("Enter the canteen for the food item (1/2): ");
    scanf("%d", &canteen_choice);
    if (canteen_choice != 1 && canteen_choice != 2) {
        printf("Invalid canteen choice.\n");
        return;
    }

    // Delete the food item from the selected canteen
    Food* canteen;
    if (canteen_choice == 1) {
        canteen = canteen1;
    } else {
        canteen = canteen2;
    }
    int item_deleted = 0;
    for (int i = 0; i < MAX_FOOD_ITEMS; i++) {
        if (strcmp(canteen[i].name, name) == 0) {
            memset(&canteen[i], 0, sizeof(canteen[i]));
            printf("The food item has been deleted.\n");
            item_deleted = 1;
            break;
        }
    }
    if (!item_deleted) {
        printf("The food item does not exist in the selected canteen.\n");
    }
}

// Function to show instant order preview
void show_instant_order_preview() {
    // Print header
    printf("\n\tRecent Orders\n");Sleep(300);
    printf("\t--------------");Sleep(300);
    printf("\n\n\t  Food Code       Name                        Quantity      Price      ");Sleep(300);
    printf("\n\t");
    printf("-----------------------------------------------------------------------");Sleep(300);
    // Print orders
    for (int i = order_count - 1; i >= 0; i--) {
        printf("\n\t  %2d        |  %-25s      |    %2d      |  %0.2f   ", order_count - i, order1[i].name, order1[i].quantity, order1[i].price*order1[i].quantity);Sleep(300);
        printf("\n\t");
        printf("-----------------------------------------------------------------------");Sleep(300);
    }
    printf("\n");
}

// Function to show total cash earned today
void show_total_cash_today() {
    float total_cash = 0;
    float total_discount = 0;
    float net_cash = 0;

    // Calculate total cash earned from orders
    for (int i = 0; i < order_count; i++) {
         total_cash += (order1[i].price * order1[i].quantity);
    }

    // Calculate the total discount
    for (int i = 0; i < a; i++) {
        total_discount += order1[i].discount;
    }
    net_cash=total_cash-total_discount;
    printf("\nTotal cash earned today: %.2f\n", total_cash);
    printf("\nTotal discount applied today: %.2f\n", total_discount);
    printf("\nNet cash earned today: %.2f\n", net_cash);
} 


