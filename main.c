#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>



const char* art =
"ooooooooo.   oooooooooooo oooooo     oooo ooooo  .oooooo..o ooooo   .oooooo.   ooooo      ooo\n"
"`888   `Y88. `888'     `8  `888.     .8'  `888' d8P'    `Y8 `888'  d8P'  `Y8b  `888b.     `8'\n"
" 888   .d88'  888           `888.   .8'    888  Y88bo.       888  888      888  8 `88b.    8 \n"
" 888ooo88P'   888oooo8       `888. .8'     888   `\"Y8888o.   888  888      888  8   `88b.  8 \n"
" 888`88b.     888    \"        `888.8'      888       `\"Y88b  888  888      888  8     `88b.8 \n"
" 888  `88b.   888       o      `888'       888  oo     .d8P  888  `88b    d88'  8       `888 \n"
"o888o  o888o o888ooooood8       `8'       o888o 8\"\"88888P'  o888o  `Y8bood8P'  o8o        `8 \n";




struct date{
    int D,M,Y;
};
struct time
{   int H,M;
    /* data */
};
struct session
{   char subject [20];
    struct date d;
    struct time t;
    int priority ;
    /* data */
};


void break_time()
{
    int x;
    do{
        printf("Do you want to continue , if yes tap 1  \n");
        scanf("%d",&x);


    }
    while(x!=1);


}

int get_current_date_int() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    int year = t->tm_year + 1900;
    int month = t->tm_mon + 1;
    int day = t->tm_mday;

    // Return date as integer: yyyymmdd
    return year * 10000 + month * 100 + day;
}




bool leap (int year)
{
    if ((year%4==0 && year%100!=0)||(year%400==0))
    { return true;
    }
    else {
    return false ;}
}

bool dayverify(int day ,int month,int year)
{
    int d,s;
    int today =get_current_date_int();
    switch (month)
    {
    case 1 : {
        d=31;
        break;
        }
    case 3 : {
        d=31;
        break;
        }
    case 4 : {
        d=30;
        break;
        }
    case 5 : {
        d=31;
        break;
        }
    case 6 : {
        d=30;
        break;
        }
    case 7 : {
        d=31;
        break;
        }
    case 8 : {
        d=31;
        break;
        }
    case 9 : {
        d=30;
        break;
        }
    case 10 : {
        d=31;
        break;
        }
    case 11 : {
        d=30;
        break;
        }

    case 12 : {
        d=31;
        break;
        }

    case 2 : {
        if (leap(year))
        {
        d=29;
        }
        else {
        d=28;
        }
        break;
        }
   default :
   {
   printf("the month don't exist \n");
   return false;
   }


    }

    if (d<day || day<0)
    {
    printf ("The %d th day don't exist in this month %d",day,month);
    return false;
    }
    else{
        s=year*10000+month*100+ day;
        if (s<today)
        {
            printf("You can't program the session in the past \n ");
            return false ;
        }
        else {
        return true;
    }


    }


}
void save_session(char filename[30],struct session* T, int size)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < size; i++) {

        fprintf(file, "%s %d %d %d %d %d %d\n", T[i].subject, T[i].d.D, T[i].d.M, T[i].d.Y, T[i].t.H, T[i].t.M, T[i].priority);
    }

    fclose(file);
}



void load_session(char filename[30], struct session* T, int* size)
{
    *size = 0;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[100]; // Buffer to hold each line from the file

    while (*size < 100 && fgets(line, sizeof(line), file) != NULL) {
        // Try to split line into parts: subject can contain spaces, so handle it differently
        char subject[50];
        int d, m, y, h, min, p;

        // Use sscanf with scanset to read subject until the first digit
        if (sscanf(line, "%[^\n0-9] %d %d %d %d %d %d", subject, &d, &m, &y, &h, &min, &p) == 7) {
            // Remove trailing space from subject
            while (subject[strlen(subject)-1] == ' ')
                subject[strlen(subject)-1] = '\0';

            strcpy(T[*size].subject, subject);
            T[*size].d.D = d;
            T[*size].d.M = m;
            T[*size].d.Y = y;
            T[*size].t.H = h;
            T[*size].t.M = min;
            T[*size].priority = p;
            (*size)++;
        } else {
            printf("Error reading session data on line: %s\n", line);
        }
    }

    fclose(file);
}



void add_session(struct session* T, int* size)
{
    printf("Enter the subject: ");
    //scanf("%s",T[size].subject);
    getchar();
    fgets(T[*size].subject,sizeof(T[*size].subject),stdin);
    T[*size].subject[strcspn(T[*size].subject,"\n")]=0;
    do {

        printf("\n\nEnter the date (DD MM YYYY): \n");
        printf("Enter the day : ");
        scanf("%d",&T[*size].d.D);
        printf("Enter the month : ");
        scanf("%d",&T[*size].d.M);
        printf("Enter the year : ");
        scanf("%d",&T[*size].d.Y);

    }
    while (dayverify(T[*size].d.D,T[*size].d.M,T[*size].d.Y)==false);
    do {
        printf("\nEnter the time (HH MM): \n");
        printf("Enter the hour : ");
        scanf("%d",&T[*size].t.H);
        printf("Enter the minutes : ");
        scanf("%d",&T[*size].t.M);

        if (T[*size].t.H>=25 || T[*size].t.H<0 || T[*size].t.M>=60 || T[*size].t.M<0)
            {printf("There is a problem in time , please enter a valuable time \n");}
    }
    while(T[*size].t.H>=25 || T[*size].t.H<0 || T[*size].t.M>=60 || T[*size].t.M<0);


     do {
        printf("\nEnter the new priority: ");
        scanf("%d", &T[*size].priority);
        if (T[*size].priority <=0)
        {
            printf("The priority must be strictly positive \n");
        }
    }
    while(T[*size].priority <=0);

    printf("\nSession added successfully!\n");
    (*size)++;
}





void modify_session(struct session* T, int size, int index)
{


    if (index < 0 || index >= size) {
        printf("Invalid index!\n");
        index=-5;
        return;
    }

    printf("Enter the new subject: ");
    //scanf("%s",T[index].subject);
    getchar();
    fgets(T[index].subject,sizeof(T[index].subject),stdin);
    T[index].subject[strcspn(T[index].subject,"\n")]=0;
    do {
        printf("Enter the new date (DD MM YYYY): \n");
        printf("Enter the day : ");
        scanf("%d",&T[index].d.D);
        printf("Enter the month : ");
        scanf("%d",&T[index].d.M);
        printf("Enter the year : ");
        scanf("%d",&T[index].d.Y);


    }
    while (dayverify(T[index].d.D,T[index].d.M,T[index].d.Y)==false);

    do {
        printf("\nEnter the new time (HH MM): \n");
        printf("Enter the hour : ");
        scanf("%d",&T[index].t.H);
        printf("Enter the minutes : ");
        scanf("%d",&T[index].t.M);

        if (T[index].t.H>=25 || T[index].t.H<0 || T[index].t.M>=60 || T[index].t.M<0)
            {printf("There is a problem in time , please enter a valuable time \n");}
    }
    while(T[index].t.H>=25 || T[index].t.H<0 || T[index].t.M>=60 || T[index].t.M<0);


    do {
        printf("\nEnter the new priority: ");
        scanf("%d", &T[index].priority);
        if (T[index].priority <=0)
        {
            printf("The priority must be strictly positive \n");
        }
    }
    while(T[index].priority <=0);


    printf("Session modified successfully!\n");
}

void search (struct session* T, int size)
{
    int choix;
    bool find=false;
    char sub[20];
    struct date x;
    do
    {
        printf("\nDo you want to search by : \n1. Subject \n2. Date \n\n");
    scanf("%d",&choix);
    switch (choix)
    {
    case 1:

        printf("Enter the subject: ");
        //scanf("%s", sub);
        getchar();
        fgets(sub,sizeof(sub),stdin);
        sub[strcspn(sub,"\n")]=0;
        for (int i=0;i<size ;i++)
        {
            if (strcmp(sub,T[i].subject)==0)
            {
                printf("\nIndex: %d\n",i);
                printf("Subject: %s\n", T[i].subject);
                printf("Date: %d/%d/%d\n", T[i].d.D, T[i].d.M, T[i].d.Y);
                printf("Time: %d h %d min\n", T[i].t.H, T[i].t.M);
                printf("Priority: %d\n", T[i].priority);
                printf("\n");
                find=true;
            }


        }
        break;
        case 2:

        printf("Enter the date (DD MM YYYY): ");
        scanf("%d %d %d", &x.D, &x.M, &x.Y);
        for (int i=0;i<size ;i++)
        {
            if (x.D==T[i].d.D && x.M==T[i].d.M && x.Y==T[i].d.Y)
            {
                printf("\nIndex: %d\n",i);
                printf("Subject: %s\n", T[i].subject);
                printf("Date: %d/%d/%d\n", T[i].d.D, T[i].d.M, T[i].d.Y);
                printf("Time: %d h %d min\n", T[i].t.H, T[i].t.M);
                printf("Priority: %d\n", T[i].priority);
                printf("\n");
                find=true;
            }


        }
        break;
    default:
        printf("Please enter a number between 1-2 \n");
        break;
    }
    } while (choix!=1 && choix!=2);
    if (find==false)
    {
        printf("There is no session with this subject or date\n");
    }

};

void delete_session(struct session* T, int *size, int index) {
    if (index < 0 || index >= *size) {
        printf("Invalid index!\n");
        return;
    }


    for (int i = index; i < *size - 1; i++) {
        T[i] = T[i + 1];
    }
    (*size)--; // Decrease the size of the array
    printf("Session deleted successfully!\n");
}



void sessionbydate(struct session* T, int* size)
{
    int i,j;
    struct date G[100];
    int count[100];
    int unique=0;
    bool find;
    for (i=0;i<*size;i++)
    {
        find=false;
        for (j=0;j<unique;j++)
        {
            if (G[j].D==T[i].d.D && G[j].M==T[i].d.M && G[j].Y==T[i].d.Y)

            {
                count[j]++;
                find=true;
                break;
            }
        }
        if (find==false)
        {
            G[unique].D=T[i].d.D;

            G[unique].M=T[i].d.M;
            G[unique].Y=T[i].d.Y;
            count[unique]=1;
            unique++;
        }

    }

    for (i=0;i<unique;i++)
    {
        printf("The %d/%d/%d : \t\t%d sessions\n",G[i].D,G[i].M,G[i].Y,count[i]);
    }
    printf("_________________________________\n\n");

}

int time_min(struct time t)
{
    int min=0;
    min+=t.H*60+t.M;
    return min;
}

void frequencysubject(struct session* T, int* size)
{
    int i,j;
    char subject[100][20];
    int minsession[100];
    int maxtime;
    int count[100];
    int unique=0;
    bool find;
    for (i=0;i< *size;i++)
    {
        find=false;
        for (j=0;j<unique;j++)
        {
            if (strcmp(subject[j],T[i].subject)==0)


            {
                count[j]++;
                minsession[j]+=time_min(T[i].t);
                find=true;
                break;
            }
        }
        if (find==false)
        {
            subject[unique][0] = '\0';
            strcpy(subject[unique], T[i].subject);
            count[unique]=1;
            minsession[unique]=time_min(T[i].t);
            unique++;
        }

    }
    maxtime=0;
    for (i=0;i<unique;i++)
    {
        printf("%d. %s : \t\t%d sessions \tTotal time : %d  minutes\n",i+1,subject[i],count[i],minsession[i]);
        if (minsession[i]>maxtime)
        {
            maxtime=minsession[i];
            j=i;
        }


    }
    printf("\nThe subject with the most time is : %s with %d minutes\n",subject[j],maxtime);
    printf("_____________________________________________________\n\n");

}


// statistics procedure
void statistics(struct session* T, int size)
{
    int i;
    int count=0;


    printf("The total number of session is : %d\n____________________________________________________\n",size);
    printf("\nThe number of session by subject  : \n\n");
    frequencysubject(T, &size);
    printf("The number of session by date is : \n\n");
    sessionbydate(T, &size);


}


void connexion(char filename[20])
{
    struct  session T[100]; // Array to store sessions
    int i, choix, size=0;
    int index;

    // Load sessions from file

    load_session(filename, T, &size);
    printf("Final size : %d \n",size);

    do {
    system("clear");

    printf("%s", art);
    printf("\n\n");
    printf("\t\tName account :  %s \n\n",filename);
    printf("===== PRINCIPAL MENU ======= \n\n");
    printf("1. Add a session\n");
    printf("2. Modify a session\n");
    printf("3. Delete a session\n");
    printf("4. Display the full planing \n");
    printf("5. Search by subject or date \n");
    printf("6. Statistics \n");
    printf("7. Save the session \n");
    printf("8. Log out \n");
    printf("\n\n\nPlease select an option: \n");

    scanf("%d",&choix);
    switch(choix)
    {
        case 1: {
            system("clear");
            add_session(T, &size);
            printf(" size : %d\n", size);
            break_time();
            break;
        }
         case 2: {
            system("clear");
            printf("You need to search firstly the session to modify \n");
            search(T, size);
            printf("Enter the index of the session to modify: ");

            scanf("%d", &index);
            modify_session(T, size, index);
            break_time();

            break;
        }
         case 3: {
            system("clear");
            printf("\n\nDisplay the full session\n");
            if (size>0){
                    for (i=0; i<size; i++)
            {
                printf("\n");
                printf("Index : %d\n",i);
                printf("Subject: %s\n", T[i].subject);
                printf("Date: %d/%d/%d\n", T[i].d.D, T[i].d.M, T[i].d.Y);
                printf("Time: %d h %d min\n", T[i].t.H, T[i].t.M);
                printf("Priority: %d\n", T[i].priority);
                printf("\n");
            }
            }
            printf("Enter the index of the session to delete: ");

            scanf("%d", &index);
            delete_session(T, &size, index);
            printf(" size : %d\n", size);
            break_time();
            break;
        }
         case 4: {

            system("clear");
            printf("\n\nDisplay the full session\n");
            if (size>0){
                    for (i=0; i<size; i++)
            {
                printf("\n");
                printf("Subject: %s\n", T[i].subject);
                printf("Date: %d/%d/%d\n", T[i].d.D, T[i].d.M, T[i].d.Y);
                printf("Time: %d h %d min\n", T[i].t.H, T[i].t.M);
                printf("Priority: %d\n", T[i].priority);
                printf("\n");
            }

            }
            else
            {
                printf("There is no session to display\n");
            }
            break_time();
            break;
        }
         case 5: {
            system("clear");
            search(T, size);
            break_time();
            break;
        }
        case 6: {
            system("clear");
            printf("\tStatistics of the session \n\n\n");
            statistics(T, size);
            break_time();
            break;
        }
        case 7: {
            save_session(filename, T, size);
            system("clear");


            printf("\nSuccessfully saved \n\n\n");
            break_time();
            break;
        }
         case 8: {
            save_session(filename, T, size);
            system("clear");
            printf("%s", art);
            printf("\n\n\t\tName account :  %s \n\n",filename);
            printf("\n\n\nThanks for using our app . Have a good day \n");
            break;
        }
        default: printf("Please enter a number between 1-7 \n");
    }
    printf("\n********************************************************************************\n");
    }
    while(choix!=8);

}

void create_account(FILE* flogin,char filename[20])
{
    FILE* new;

    flogin=fopen("login.txt","a");
    if (flogin==NULL)
            {
                printf("Error to open file\n");
                printf("We can' t create a new account please try again");
                exit (1);
            }
    fprintf(flogin,"%s\n",filename);
    fclose(flogin);
    new=fopen(filename,"w");
    fclose(new);
    printf("Account created successfully!\n");

}


int main()

{
    int option,i,j;
    char nameaccount[100][20];
    bool find=false;
    char filename[20], client[20];
    FILE* flogin=fopen("login.txt","a");
    fclose(flogin);

    do {
        system("clear");
        printf("%s", art);
        printf("\n\n");
        printf("Welcome to the session management system!\n\n");
        printf("1. Create an account \n");
        printf("2. Login \n");
        printf("3. Quit \n");
        printf("Please select an option: \n");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {

            system("clear");
            printf("Enter a name for your account ,in this form : yourname (no space allowed) \n");
            getchar();
            fgets(filename,sizeof(filename),stdin);
            filename[strcspn(filename,"\n")]=0;

            find=false;
            //loop inside the filename to check the spaces
            for (i=0;i<strlen(filename);i++)
            {
                if (filename[i]==' ')
                {
                    printf("There is a space in the name of your account , please try again \n");
                    find=true;

                    break;
                }
            }

            if (find==false) {
                strcat(filename,".txt");
                create_account(flogin,filename);

            }
            break_time();
            break;
        }


        case 2:
            system("clear");
            printf("This is the account we have already on our app !!\n\n");

            flogin=fopen("login.txt","r");
            if (flogin == NULL) {
                printf("Error opening file\n");
            }
            i=0;
            while (fscanf(flogin, "%s", client)==1)
            {

                    printf("%d. %s",i+1,client);
                    i++;
                    printf("\n");
                    strcpy(nameaccount[i],client);



                /* code */
            }
            fclose(flogin);
            printf("\n\nEnter the number corresponding to your account !!\n");
            scanf("%d",&j);
            if (j-1>=i||j-1<0)
            {
                printf("Account not found. Please try again \n ");
            }
            else {
                strcpy(filename,nameaccount[j]);
                printf("%s",filename);
                connexion(filename);
            }


            break_time();



            break;

        case 3:
            system("clear");
            printf("%s", art);
            printf("\n\n\nThanks for using our app . Have a good day \n");
            break;
        default:
            break;
        }

    }
    while (option!=3);



    return 0;
}
