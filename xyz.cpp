// PROJECT BY 20BCE009(AKSHAY), 20BCE032(RAJDEEP), 20BCE073(KUNJ)
// INSTRUCTIONS BEFORE USE!!
// here we set some pre decided menu but Admin can also access the menu through password
// password is INVASSN1234
/*A console-based program of Food order management system. Implementation of this program is done using NESTED DOUBLY LINKED LIST, CIRCULAR QUEUE (BY USING-ARRAY/LINKED LIST).

-It has two options:
1. Admin
2. Customer

According to the choice of user, its respective functionalities will be unlocked. Functionalities are listed below:
Following is the rough structure of program. (Further additions and subtractions of functions may take place according to requirements of program.)

1. Admin panel:
  -For insert item in menu (linked list)
  -For status of tables (queue display)
  -For status of online queue and or parcel queue (circular queue)
  -For check out customer from table (queue)
  -For check out customer in online queue (queue)
  -For Exit

2.Customer Panel:
  - For ONLINE BUY OR PARCEL (queue using linked list)
  -For TAKE FOOD AT RESTAURANT (circular queue using array)
  -For EXIT
Other functions like count_bill() , show_bill() , printmenu() are used for counting bill, displaying bill, displaying menu Respectively.*/

//---------------------------------------------------- STARTING -------------------------------------------------------------------------

#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
using namespace std;

//------------------------------------------------USER DEFINE FUNCTION -------------------------------------------------------------------

void enQueue();
void deOueue();
void create();
void Loading();
void count_bill();
void count_billR();
void insertEndMenu();
void printfd();
void print_menu();
void insertEndFd_item();
void inserttable();
void deletable();
void disptablestatus();
void displayQueue();
void Loading();
void display_billOn();
void display_billR();

//--------------------------------------------------------------- STATIC UNIVERSAL VARIABLE ----------------------------------

static int menu_no = 0, item = 0, tkk = 0;

//----------------------------------------------------------------ONLINE QUEUE AND FUNCTIONS --------------------------------------
struct Node
{
    string name;
    int bill, tkk;
    struct Node *link;
};

struct Queue
{
    struct Node *front, *rear;
};
void enQueue(Queue *q, string s)
{
    struct Node *temp = new Node;
    temp->tkk = ++tkk;
    temp->name = s;
    if (q->front == NULL)
        q->front = temp;
    else
        q->rear->link = temp;

    q->rear = temp;
    q->rear->link = q->front;
}
void deQueue(Queue *q)
{

    struct Node *temp = q->front;
    if (q->front == NULL)
    {
        cout << "\nCircular Queue Empty!!!";
    }
    else
    {
        if (q->front == q->rear)
        {

            delete (temp);
            q->front = NULL;
            q->rear = NULL;
        }
        else
        {

            q->front = q->front->link;
            q->rear->link = q->front;
            delete (temp);
        }
    }
}

void displayQueue(struct Queue *q)
{
    struct Node *temp = q->front;
    cout << "\n\n\t\t CUSTOMER IN ONLINE AND PARCEL QUEUE ARE: \n";
    cout << "\n================================================================\n";
    while (temp->link != q->front)
    {
        cout << "Token no. [" << temp->tkk << "] " << temp->name << " and BILL is " << temp->bill << endl;
        cout << "\n-----------------------------------------------------------------\n";
        temp = temp->link;
    }
    cout << "Token no. [" << temp->tkk << "] " << temp->name << " and BILL is " << temp->bill << endl;
    cout << "\n-----------------------------------------------------------------\n";
}
//-------------------------------------------------------------CUSTOMER AT RESTAURANT (QUEUE)-----------------------
struct customer_atR
{
    string name;
    int tbl, bill;
};
struct customer_atR *newtable(string s)
{
    struct customer_atR *temp = new customer_atR;
    temp->name = s;
    return temp;
}
int frontR = -1, rearR = -1;
int size = 24;
struct customer_atR *table = NULL;
void create(int size)
{

    int s = size;
    table = new customer_atR[s];
}

void inserttable(struct customer_atR *x)
{

    if (rearR == size - 1)
    {
        if (frontR != 0)
            rearR = 0;
        else
        {
            cout << "\nTables are full\n";
            return;
        }
    }
    else
        rearR++;
    table[rearR].name = x->name;
    table[rearR].tbl = rearR;

    if (frontR == -1)
        frontR = 0;
}
void deletable()
{
    if (frontR == -1)
    {
        printf("Please insert Table");
        return;
    }
    else if (rearR == frontR && frontR == 0)
    {

        table[frontR].name = "empty";
        table[frontR].bill = 0;
        table[frontR].tbl = 0;
        frontR = rearR = -1;
        // free(temp);
        return;
    }
    else if (frontR == size - 1)
    {

        table[frontR].name = "empty";
        table[frontR].bill = 0;
        table[frontR].tbl = 0;
        frontR = 0;
        // free(temp);
        return;
    }

    else
    {

        table[frontR].name = "empty";
        table[frontR].bill = 0;
        table[frontR].tbl = 0;
        frontR++;

        return;
    }
}
void disptablestatus(struct customer_atR *table)
{
    cout << "\n================================================================\n";
    for (int i = 0; i < size; i++)
    {
        // cout<<"\n================================================================\n";
        cout << "\n\n\t Table No. [" << table[i].tbl << "]"
             << " " << table[i].name << "\n ";
        cout << "\n----------------------------------------------------------------\n";
    }
    printf("\n");
}

//-------------------------------------------------LOADING-------------------------------------

void Loading()
{
    char c = 219, b = 176;

    for (int i = 0; i < 101; i++)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\t\t\t\t\t\t LOADING " << i % 101 << "%\n\t";
        for (int j = 0; j < i / 4; j++)
        {
            cout << c << b << c << b;
        }
    }
}

//-------------------------------------------- MENU -------------------------------------=

struct Menu
{
    string cuisine_type;
    int menu_no;
    struct fd_item *cusine_type;
    struct Menu *next;
    struct Menu *prev;
};
struct fd_item
{
    string fd_name;
    int item;
    int price;
    int avg_time;
    struct fd_item *next;
    struct fd_item *prev;
};

void insertEndMenu(struct Menu **menu, struct fd_item *fd_item, string cs_name)
{

    if (*menu == NULL)
    {
        struct Menu *new_node = new Menu;
        new_node->menu_no = ++menu_no;
        new_node->cusine_type = fd_item;
        new_node->cuisine_type = cs_name;
        new_node->next = new_node->prev = new_node;
        *menu = new_node;
        return;
    }

    Menu *last = (*menu)->prev;
    struct Menu *new_node = new Menu;
    new_node->menu_no = ++menu_no;
    new_node->cusine_type = fd_item;
    new_node->cuisine_type = cs_name;
    new_node->next = *menu;
    (*menu)->prev = new_node;
    new_node->prev = last;
    last->next = new_node;
}
void printfd(fd_item *fd)
{
    struct fd_item *temp = fd;
    while (temp->next != fd)
    {
        cout << "   [" << temp->item << "]     " << temp->fd_name << " |"
             << "Rs." << temp->price;
        cout << "\n-----------------------------------------------------------------\n";
        temp = temp->next;
    }
    cout << "   [" << temp->item << "]     " << temp->fd_name << " |"
         << "Rs." << temp->price << endl;
    cout << "\n-----------------------------------------------------------------\n";
}
void print_menu(Menu *menu)
{
    Menu *temp1 = menu;
    for (int i = 1; i <= menu_no; i++)
    {
        cout << "\t\t**" << temp1->cuisine_type << "**";
        cout << "\n=================================================================\n";
        printfd(temp1->cusine_type);
        temp1 = temp1->next;
    }
}

void insertEndFd_item(struct fd_item **cs_name, string fd_name, int price, int avg_time)
{

    if (*cs_name == NULL)
    {
        struct fd_item *new_node = new fd_item;
        new_node->item = ++item;
        new_node->fd_name = fd_name;
        new_node->price = price;
        new_node->avg_time = avg_time;
        new_node->next = new_node->prev = new_node;
        *cs_name = new_node;
        return;
    }

    fd_item *lst = (*cs_name)->prev;
    struct fd_item *new_node = new fd_item;
    new_node->item = ++item;
    new_node->fd_name = fd_name;
    new_node->price = price;
    new_node->avg_time = avg_time;
    new_node->next = *cs_name;
    (*cs_name)->prev = new_node;
    new_node->prev = lst;
    lst->next = new_node;
}

//--------------------------------------------------- BILLING ----------------------------------------------

void count_bill(Node *cst, int n, Menu *menu)
{
    Menu *temp1 = menu;
    for (int i = 1; i <= menu_no; i++)
    {

        struct fd_item *temp = temp1->cusine_type;
        while (temp->next != temp1->cusine_type)
        {
            if (temp->item == n)
            {
                cst->bill = cst->bill + temp->price;
            }
            temp = temp->next;
        }
        if (temp->item == n)
        {
            cst->bill = cst->bill + temp->price;
        }
        temp1 = temp1->next;
    }
}
void count_billR(customer_atR *cst, int n, Menu *menu)
{
    Menu *temp1 = menu;
    for (int i = 1; i <= menu_no; i++)
    {

        struct fd_item *temp = temp1->cusine_type;
        while (temp->next != temp1->cusine_type)
        {
            if (temp->item == n)
            {
                cst->bill = cst->bill + temp->price;
            }
            temp = temp->next;
        }
        if (temp->item == n)
        {
            cst->bill = cst->bill + temp->price;
        }
        temp1 = temp1->next;
    }
}

void display_billOn(Node *cst)
{
    int x1 = cst->bill;
    cout << "\n================================================================\n";
    cout << "\n\t\t ** THANK YOU **\n";
    cout << "\n================================================================\n\n\t\t";
    cout << cst->name << " ,Your bill is : " << cst->bill << endl;
    cout << "\n================================================================\n";

    if (x1 == 0)
    {
        return;
    }
    cout << "\t\tPlease write your card no : ";
    string h;
    cin >> h;
    int t;
    srand(time(0));
    t = rand() % 10000;
    cout << "\t\tOTP Generated : ";
    printf("%04d", t);
    cout << "\n Please enter OTP : ";
    cin >> t;
    cout << "\t\tTransaction Approved\n";
    cout << "\t\tEnter Any Character to go back to Main Menu : ";
    char x;
    cin >> x;
}
void display_billR(customer_atR *cst)
{
    int x1 = cst->bill;
    cout << "\n================================================================\n";
    cout << "\n\t\t ** THANK YOU **\n";
    cout << "\n================================================================\n\n\t\t";
    cout << cst->name << " ,Your bill is : " << cst->bill << endl;
    cout << "\n================================================================\n";
    if (x1 == 0)
    {
        return;
    }
    cout << "\t\tPlease write your card no : ";
    string h;
    cin >> h;
    int t;
    srand(time(0));
    t = rand() % 10000;
    cout << "\t\tOTP Generated : ";
    printf("%04d", t);
    cout << "\n Please enter OTP : ";
    cin >> t;
    cout << "\t\tTransaction Approved\n";
    cout << "\t\tEnter Any Character to go back to Main Menu : ";
    char x;
    cin >> x;
}

//----------------------------------------------------------------------------------------------------------

int main()
{

    //---------------------------- INITIAL DECLARACTION AND EXAMPLE CREATION OF MENU ---------------------

    char c;
    create(size);
    string password = "INVASSN1234";
    struct Menu *menu = NULL;
    struct fd_item *Fastfood = NULL;
    struct fd_item *North_Indian = NULL;
    struct fd_item *Italian = NULL;
    struct fd_item *South_indian = NULL;
    struct fd_item *Chinese = NULL;
    insertEndFd_item(&Fastfood, "Burger", 40, 5);
    insertEndFd_item(&Fastfood, "Sandwich", 30, 5);
    insertEndFd_item(&Fastfood, "French Fries", 30, 5);
    insertEndFd_item(&Fastfood, "VadaPav", 15, 5);
    insertEndFd_item(&Fastfood, "Dabeli", 15, 5);
    insertEndFd_item(&Fastfood, "Samosa", 15, 5);
    insertEndFd_item(&Fastfood, "Garlic Bread", 20, 5);
    insertEndFd_item(&North_Indian, "Full dish(2 Sabji ,2 Naan ,Jira Rice and Dal Fry))", 120, 15);
    insertEndFd_item(&North_Indian, "Chole Bhature", 50, 10);
    insertEndFd_item(&North_Indian, "Chole Kulche", 50, 7);
    insertEndFd_item(&North_Indian, "Chole Chaval", 50, 5);
    insertEndFd_item(&North_Indian, "Rajma chaval", 40, 5);
    insertEndFd_item(&Italian, "Lasagna", 100, 14);
    insertEndFd_item(&Italian, "Caprese Salad with Pesto Sauce", 100, 15);
    insertEndFd_item(&Italian, "Panzanella", 80, 10);
    insertEndFd_item(&Italian, "Focaccia Bread", 80, 10);
    insertEndFd_item(&Italian, "Veg Pizza", 100, 10);
    insertEndFd_item(&Italian, "Macaroni Pasta", 100, 14);
    insertEndFd_item(&South_indian, "Idli", 40, 10);
    insertEndFd_item(&South_indian, "Meduvada", 40, 10);
    insertEndFd_item(&South_indian, "Dosa", 50, 10);
    insertEndFd_item(&South_indian, "Rasam Bhat", 40, 10);
    insertEndFd_item(&South_indian, "Masala Dosa", 70, 10);
    insertEndFd_item(&Chinese, "Chilli Garlic Noodles", 50, 10);
    insertEndFd_item(&Chinese, "Momos", 40, 10);
    insertEndFd_item(&Chinese, "Manchurian", 50, 10);
    insertEndFd_item(&Chinese, "Chaowmin", 40, 10);
    insertEndFd_item(&Chinese, "Paneer Chilli", 80, 10);
    insertEndMenu(&menu, Fastfood, "FAST FOOD");
    insertEndMenu(&menu, North_Indian, "NORTH INDIAN");
    insertEndMenu(&menu, Italian, "ITALIAN");
    insertEndMenu(&menu, South_indian, "SOUTH INDIAN");
    insertEndMenu(&menu, Chinese, "CHINESE");
    Queue *q = new Queue;
    q->front = q->rear = NULL;
    // PRE ADDED CUSTOMER FOR ONLINE QUEUE
    enQueue(q, "AKSHAY");
    enQueue(q, "RAJDEEP");
    enQueue(q, "KUNJ");

    while (true)
    {
        Loading();
        system("cls");

        cout << "\n========================================================================================================================\n";
        cout << "\t\t\t\t######  WELCOME TO XYZ RESTAURANT  ######";
        cout << "\n========================================================================================================================\n\n";
        cout << "\t\t\t [1] For Admin login\n\n";
        cout << "\t\t\t [2] For Customer login\n\n";
        cout << "\t\t\t [3] For Exit\n";
        cout << "\n========================================================================================================================\n";
        int t = 0;
        cout << "Enter your choice : ";
        cin >> t;
        Loading();
        if (t == 1)
        {
            system("cls");
            string s;
            cout << "\n\n\n\t\t Please Enter Your Password To Login : "; // password - INVASSN1234
            cin >> s;

            if (s == password)
            {
                Loading();
                while (true)
                {
                    system("cls");
                    cout << "\n========================================================================================================================\n";
                    cout << "\t\t\t\t######  WELCOME TO XYZ RESTAURANT  ######";
                    cout << "\n========================================================================================================================\n\n";
                    cout << "\t\t\t [1] Insert Item\n\n";
                    cout << "\t\t\t [2] Status Of Tables Available\n\n";
                    cout << "\t\t\t [3] Status of Online And Parcel Queue\n\n";
                    cout << "\t\t\t [4] Check Out Customer\n\n";
                    cout << "\t\t\t [5] Check Out Customer From Online Queue \n\n";
                    cout << "\t\t\t [6] Exit\n";
                    cout << "\n========================================================================================================================\n";
                    int t1 = 0;
                    cout << "Enter your choice : ";
                    cin >> t1;
                    if (t1 == 1)
                    {
                        string csn_name;
                        struct fd_item *newfd = NULL;
                        cout << "\t\tEnter Category of Food : ";
                        cin >> csn_name;
                        cout << "\t\tEnter the number of food items to add : ";
                        int v;
                        cin >> v;

                        for (int i = 0; i < v; i++)
                        {
                            string fd_name;
                            cout << "\t\tEnter Food Item Name : ";
                            cin >> fd_name;
                            int avgtm, pr;
                            cout << "\t\tSet the Food Item price : ";
                            cin >> pr;
                            cout << "\t\tSet Average Making Time : ";
                            cin >> avgtm;
                            insertEndFd_item(&newfd, fd_name, pr, avgtm);
                        }
                        insertEndMenu(&menu, newfd, csn_name);

                        Loading();
                        system("cls");
                        continue;
                    }
                    if (t1 == 2)
                    {
                        disptablestatus(table);
                        char c;
                        cin >> c;
                        Loading();
                        system("cls");
                        continue;
                    }
                    if (t1 == 3)
                    {
                        displayQueue(q);
                        char c;
                        cin >> c;
                        system("cls");
                        continue;
                    }
                    if (t1 == 4)
                    {
                        deletable();
                        disptablestatus(table);
                        char c;
                        cin >> c;
                        Loading();
                        system("cls");
                        continue;
                    }
                    if (t1 == 5)
                    {
                        deQueue(q);
                        displayQueue(q);
                        char c;
                        cin >> c;
                        Loading();
                        system("cls");
                        continue;
                    }
                    if (t1 == 6)
                    {

                        break;
                    }
                }
                continue;
            }
            else
            {
                cout << "Incorrect Password";
                continue;
            }
        }
        if (t == 2)
        {
            system("cls");
            cout << "\n\n\t\tEnter your name : ";
            string sc;
            cin >> sc;

            cout << "\n========================================================================================================================\n";
            cout << "\n\t\t\t [1] TAKE AWAY FROM RESTAURANT\n\n";
            cout << "\t\t\t [2] DINE AT RESTAURANT\n\n";
            cout << "\t\t\t [3] EXIT\n";
            cout << "\n========================================================================================================================\n";
            int tr = 0;
            cin >> tr;
            if (tr == 1)
            {

                enQueue(q, sc);
                system("cls");
                print_menu(menu);
                // cin>>t;
                while (true)
                {
                    cout << "\n========================================================================================================================\n";
                    cout << "\n\t\t\t [1] BUY FOOD ITEM\n\n";
                    cout << "\t\t\t [2] EXIT THE MENU\n";
                    cout << "\n========================================================================================================================\n";
                    int t1 = 0;
                    cin >> t1;
                    if (t1 == 1)
                    {
                        cout << "\t Enter the Food Item Serial Number to Buy : ";
                        int itmn, qnt;
                        cin >> itmn;
                        cout << "\t Enter the Quantity : ";
                        cin >> qnt;
                        for (int i = 0; i < qnt; i++)
                        {
                            count_bill(q->rear, itmn, menu);
                        }
                    }
                    if (t1 == 2)
                    {
                        display_billOn(q->rear);
                        break;
                    }
                }
            }
            if (tr == 2)
            {
                struct customer_atR *x = newtable(sc);
                inserttable(x);
                system("cls");
                print_menu(menu);
                // cin>>t;
                while (true)
                {
                    cout << "\n========================================================================================================================\n";
                    cout << "\n\t\t\t [1] BUY FOOD ITEM\n\n";
                    cout << "\t\t\t [2] EXIT THE MENU\n";
                    cout << "\n========================================================================================================================\n";
                    int t1 = 0;
                    cin >> t1;
                    if (t1 == 1)
                    {
                        cout << "\t Enter the Food Item Serial Number to Buy : ";
                        int itmn, qnt;
                        cin >> itmn;
                        cout << "\t Enter the Quantity : ";
                        cin >> qnt;
                        for (int i = 0; i < qnt; i++)
                        {
                            count_billR(x, itmn, menu);
                        }
                    }
                    if (t1 == 2)
                    {
                        display_billR(x);
                        break;
                    }
                }
            }
            if (tr == 3)
            {
                Loading();
                system("cls");
                continue;
            }
        }
        else
        {
            break;
        }
    }

    return 0;
}