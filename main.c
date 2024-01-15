#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAX_SIZE 200


void generate_monthly_report(){
    printf("Monthly Report Generated\n");
    char line[100];
FILE *report = fopen("Report Leave.txt", "r");
FILE *monthly_report = fopen("monthly report.txt", "w");

if (report == NULL || monthly_report == NULL) {
    printf("Error: Unable to open file.\n");
    return;
}

// Print the header for the monthly report
fprintf(monthly_report, "| %-10s | %-12s | %-12s | %-10s |\n", "ID", "Date" , "Type Leave", "Status");
fprintf(monthly_report, "|%-12s|%-14s|%-14s|%-12s|\n", "-----------", "-------------", "-----------", "-------------", "-----------");
printf("| %-10s | %-12s | %-12s | %-10s |\n", "ID", "Date" , "Type Leave", "Status");
printf("|%-12s|%-14s|%-14s|%-12s|\n", "-----------", "-------------", "-----------", "-------------", "-----------");

while (fgets(line, sizeof(line), report) != NULL) {
    // Remove newline character from the line
    line[strcspn(line, "\n")] = '\0';

    // Parse the data from the line (assumes data is separated by commas)
    char *id = strtok(line, ",");
    char *date = strtok(NULL, ",");
    char *type_leave = strtok(NULL, ",");
    char *status = strtok(NULL, ",");

    // Print the data in a formatted row
    fprintf(monthly_report, "| %-10s | %-12s | %-12s | %-10s |\n", id, date, type_leave, status);
    printf("| %-10s | %-12s | %-12s | %-10s |\n", id, date, type_leave, status);
}

fprintf(monthly_report, "|%-11s|%-13s|%-11s|%-13s|%-11s|\n", "-----------", "-------------", "-----------", "-------------", "-----------");

fclose(report);
fclose(monthly_report);
}

void update_leave_balance(){
    char line[100];
    FILE * balance = fopen("leavebalance.txt","r");
    FILE * temp1 = fopen("temp1.txt","w");

    if(balance != NULL && temp1 != NULL) {
        while(fgets(line, 100, balance)!= NULL){
            char * ID = strtok(line,",");
            fprintf(temp1,"%s,20,20,\n",ID);
        }

        fclose(balance);
        fclose(temp1);

        FILE * replace = fopen("leavebalance.txt","w");
        FILE * updated = fopen("temp1.txt","r");

        if(replace != NULL && updated != NULL) {
            while(fgets(line,100,updated)!= NULL){
                fprintf(replace,"%s",line);
            }

            fclose(replace);
            fclose(updated);
        }
    }
    printf("Leave Balance Have been Updated");
}

void search_staff(){
    int number = 1;
    char line[100];
    int checking = 1;
    char id[100];
    printf("Insert ID: ");
    scanf("%s",&id);
    FILE * find = fopen("Report Leave.txt","r");

    if(find != NULL) {
        while (fgets(line,100,find) != NULL){
            char*ID = strtok(line,",");
            char*date = strtok(NULL,",");
            char*typeleave = strtok(NULL,",");
            char*status = strtok(NULL,",");

            if (strcmp(id,ID)==0){
                printf("%d) %s , %s , %s , %s\n",number,ID,date,typeleave,status);
                number++;
                checking = 0;
            }
        }

        fclose(find);
    }

    if (checking == 1){
        printf("Invalid User ID\n\n\n");
    }
}

void add_new_stuff(){
    FILE* input = fopen("data.txt","a");
    FILE* newbalance = fopen("leavebalance.txt","a");
    FILE * SService = fopen("S ID.txt","r");
    FILE * acedemic = fopen("A ID.txt","r");
    FILE * IT = fopen("I ID.txt","r");
    char last_line[MAX_SIZE];
    char next_id[MAX_SIZE];
    int id;
    int GID;
    char name[100];
    char password[100];
    int role;

    while (1) {
        printf("Choose Department\n1)Academic\n2)Student Service\n3)IT\n: ");
        if (scanf("%d", &id) != 1) {

            printf("Invalid input. Please enter an integer.\n");

            while (getchar() != '\n');
            admin_menu();
        } else {

            break;
        }
    }


    if (id == 1){
    while(fgets(last_line,100,acedemic)!= NULL){
    }
    GID = atoi(last_line + 1);
    GID++;
    snprintf(next_id, 100, "A%02d", GID);

    fclose(SService);
    fclose(acedemic);
    fclose(IT);
    FILE * acedemic2 = fopen("A ID.txt","a");
    fprintf(acedemic2,"%s",next_id);
    fclose(acedemic2);
    }
    else if(id ==2){
    while(fgets(last_line,100,SService)!= NULL){
    }
    GID = atoi(last_line + 1);
    GID++;
    snprintf(next_id, 100, "S%02d", GID);

    fclose(SService);
    fclose(acedemic);
    fclose(IT);

    FILE * SService2 = fopen("S ID.txt","a");
    fprintf(SService2,"%s",next_id);
    fclose(SService2);
    }

    else if(id == 3){
    while(fgets(last_line,100,IT)!= NULL){
    }
    GID = atoi(last_line + 1);
    GID++;
    snprintf(next_id, 100, "I%02d", GID);

    fclose(SService);
    fclose(acedemic);
    fclose(IT);
    FILE * IT2 = fopen("S ID.txt","a");
    fprintf(IT2,"%s",next_id);
    fclose(IT2);
    }

    printf("Enter Name:");
    scanf("%s",name);
    printf("Enter Password:");
    scanf("%s",password);
    F:
    while (1) {
        printf("Choose role\n 1.Staff\n 2.Admin\n 3.Superior\n:");
        if (scanf("%d", &role) != 1) {

            printf("Invalid input. Please enter an integer.\n");

            while (getchar() != '\n');
            goto F;
        } else {

            break;
        }
    }
    printf("Successful Added");
    fprintf(input,"%s,%s,%s,%d,\n",next_id,name,password,role);
    fprintf(newbalance,"%s,10,10,\n",next_id);
    fclose(input);
    fclose(newbalance);
}

void admin_menu(){
    int option;

    do {
        printf("\n\nAdmin Menu\n");
        printf("1. Add New Staff Details\n");
        printf("2. Update Leave Balance\n");
        printf("3. Search Staff\n");
        printf("4. Generate Monthly Report\n");
        printf("0. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            scanf("%*s"); // Clear input buffer
            continue;
        }

        switch (option) {
            case 1:
                add_new_stuff();
                break;
            case 2:
                update_leave_balance();
                break;
            case 3:
                search_staff();
                break;
            case 4:
                generate_monthly_report();
                break;
            case 0:
                printf("Exiting Admin Menu...\n");
                main();
                break;
            default:
                printf("Invalid option. Please choose a valid option.\n");
                break;
        }

        printf("\n");

    } while (option != 0);
}



void apply_leave(char *current_ID){
    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    int option;
    char line[MAX_SIZE];
    char type_leave[MAX_SIZE];
    char dayleave[MAX_SIZE];
    printf("Applying for leave...\n\n");
C:
    while (1) {
        printf("\nChoose your type of leave\n\n 1.Annual leave\n 2.Sick Leave\n\n: ");
        if (scanf("%d", &option) != 1) {

            printf("Invalid input. Please enter an integer.\n");

            while (getchar() != '\n');
            goto C;
        } else {

            break;
        }
    }
    switch(option){
       case 1:
           strcpy(type_leave,"Annual Leave");
           break;
       case 2:
           strcpy(type_leave,"Sick Leave");
           break;
       default:
           printf("Invalid option\n");
           goto C;
           break;
    }
/////////////////////////////////////////////////////
        int day, month, year;
        int days_in_month;
        while (1) {
            J:
            while (1) {
            printf("Enter the month: ");
            if (scanf("%d", &month) != 1) {

                printf("Invalid input. Please enter an integer.\n");

                while (getchar() != '\n');
                goto J;
            } else {

                break;
            }
        }
            K:
            while (1) {
            printf("Enter the day: ");
            if (scanf("%d", &day) != 1) {

                printf("Invalid input. Please enter an integer.\n");

                while (getchar() != '\n');
                goto K;
            } else {

                break;
            }
        }
            L:
            while (1) {
            printf("Enter the year: ");
            if (scanf("%d", &year) != 1) {

                printf("Invalid input. Please enter an integer.\n");

                while (getchar() != '\n');
                goto L;
            } else {

                break;
            }
        }

        if (year < now->tm_year + 1900 ||
            (year == now->tm_year + 1900 && month < now->tm_mon + 1) ||
            (year == now->tm_year + 1900 && month == now->tm_mon + 1 && day < now->tm_mday)) {
            printf("Invalid date! Date must be on or after today.\n");
            goto J;
        }
        else if (month < 1 || month > 12) {
            printf("Invalid month! Please enter a valid month.\n");
            goto J;
        }
        else if (day < 1 || day > 31) {
            printf("Invalid day! Please enter a valid day.\n");
            goto J;
        }
        else if (month == 2) {
            // Check for leap year
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                days_in_month = 29;
            } else {
                days_in_month = 28;
            }
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11) {
            days_in_month = 30;
        }
        else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
            days_in_month = 31;
        }
        else if(day < 1 || day > days_in_month) {
            printf("Invalid day\n");
            goto J;
        }
        else if (month == now ->tm_mon){
            if(day < now ->tm_mday){
                printf("invalid date");
                goto J;
            }
        }
        break;
    }
///////////////////////////////////////////////////////
int a = (14 - month) / 12;
int y = year - a;
int m = month + 12 * a - 2;
int d = day;
int q = d + (31 * m) / 12 + y + (y / 4) - (y / 100) + (y / 400);
int dow = q % 7;
if (dow == 0 || dow == 6) {
    printf("\nCant apply leave on weekend\n");
    goto J;
}

//////////////////////////////////////////////////////
char start_date[MAX_SIZE];
sprintf(start_date,"%d/%d/%d",day,month,year);
FILE * check = fopen("Report Leave.txt","r");
while(fgets(line,100,check) != NULL){
        char*ID = strtok(line,",");
        char*date = strtok(NULL,",");
        char*typeleave = strtok(NULL,",");
        char*status = strtok(NULL,",");
        if (strcmp(ID,current_ID) == 0 ){
            if (strcmp(date,start_date) == 0){
                printf("\nThis date leave is applied\n");
                goto J;
            }
        }
        else{
            continue;
        }
}
printf("\nDate Valid\n");

///////////////////////////////////////////////////
    printf("Upload Complete.......");
    FILE * inputdata = fopen("Report Leave.txt", "a");
    fprintf(inputdata, "%s,%s,%s,PENDING,\n",current_ID,start_date,type_leave);
    fclose(inputdata);
}

void cancel_leave(char *current_ID){
    int option;
    char line[100];
    int number = 1;
    printf("Cancelling leave...\n");
    FILE * leave = fopen("Report Leave.txt","r");
    FILE * temp1 = fopen("temp1.txt","w");
    FILE * temp2 = fopen("temp2.txt","w");
    while(fgets(line,100,leave) != NULL){
        char*ID = strtok(line,",");
        char*date = strtok(NULL,",");
        char*typeleave = strtok(NULL,",");
        char*status = strtok(NULL,",");
        if (strcmp(current_ID,ID)==0){
            printf("%d) %s , %s , %s , %s\n",number,ID,date,typeleave,status);
            fprintf(temp1,"%s,%s,%s,%s,%s,\n",ID,date,typeleave,status);
            number++;
        }
        else{
            fprintf(temp2,"%s,%s,%s,%s,\n",ID,date,typeleave,status);
        }
    }

    while (1) {
        printf("Which leave you want to cancel\n");
        if (scanf("%d", &option) != 1) {

            printf("Invalid input. Please enter an integer.\n");

            while (getchar() != '\n');
            login_menu_staff(current_ID);
        } else {

            break;
        }
    }
    fclose(leave);
    fclose(temp1);
    fclose(temp2);
    //////////////////////////////////////////////////////////////////////////////
    number = 1;
    FILE * tempread = fopen("temp1.txt","r");
    FILE * tempinput = fopen("temp2.txt","a");
    while(fgets(line,100,tempread) != NULL){
        char*ID = strtok(line,",");
        char*date = strtok(NULL,",");
        char*typeleave = strtok(NULL,",");
        char*status = strtok(NULL,",");
        if (number != option){
            fprintf(tempinput,"%s,%s,%s,%s,%s,\n",ID,date,typeleave,status);
        }
        number++;
    }
    fclose(temp1);
    fclose(temp2);
    ////////////////////////////////////////////////////////////////////////////////////////////////
    FILE * clone = fopen("temp2.txt","r");
    FILE * updated = fopen("Report Leave.txt","w");
    while(fgets(line,100,clone) != NULL){
            fprintf(updated,"%s",line);
        }
    fclose(clone);
    fclose(updated);
    printf("Successfully Removed\n");


}

void check_leave_status(char *current_ID){
    char line[100];
    int number = 1;
    FILE * leave = fopen("Report Leave.txt","r");
    FILE * leavebalance = fopen("leavebalance.txt","r");
    while(fgets(line,100,leave) != NULL){
        char*ID = strtok(line,",");
        char*date = strtok(NULL,",");
        char*typeleave = strtok(NULL,",");
        char*status = strtok(NULL,",");
        if (strcmp(current_ID,ID)==0){
            printf("%d) %s , %s , %s , %s\n",number,ID,date,typeleave,status);
            number++;
        }
    }
    while(fgets(line,100,leavebalance) != NULL){
        char*ID = strtok(line,",");
        char*AL = strtok(NULL,",");
        char*SL = strtok(NULL,",");
        if (strcmp(current_ID,ID)==0){
            printf("ID: %s\nAnnual Leave: %s\nSick Leave: %s\n",ID,AL,SL);
            number++;
        }
    }
    fclose(leave);
    fclose(leavebalance);
}

void login_menu_staff(char *current_ID) {
    int option;
    while(1){
        printf("\n\nStaff MENU\n");
        while (1) {
        printf("1. Apply leave\n2. Cancel leave\n3. Check leave status\n0. Quit\n: ");
        if (scanf("%d", &option) != 1) {

            printf("Invalid input. Please enter an integer.\n");

            while (getchar() != '\n');
            login_menu_staff(current_ID);
        } else {

            break;
        }
    }
        switch (option){
            case 1:
                apply_leave(current_ID);
                break;
            case 2:
                cancel_leave(current_ID);
                break;
            case 3:
                check_leave_status(current_ID);
                break;
            case 0:
                printf("Exiting...\n\n\n");
                main();
                return;
            default:
                printf("Invalid entry\n");
                break;
        }
    }
}



void searchstaffdate(){
    int option;
    printf("------Search for Staff on a Specific Date------\n\n");
    printf("1. Search\n2. Quit\n\n");
    scanf("%d",&option);
            char day[100];
            char month[100];
            char year[100];
            char wholedate[100];
    switch(option) {
        case 1:
            printf("\nEnter day (DD): ");
            scanf("%s", day);
            printf("Enter month (MM): ");
            scanf("%s", month);
            printf("Enter year (YYYY): ");
            scanf("%s", year);
            sprintf(wholedate, "%s/%s/%s", day, month, year);
            printf("\nSearching for staff on %s...\n", wholedate);

            char line[100];
            int number = 1;
            FILE * leave = fopen("Report Leave.txt","r");
            while(fgets(line,100,leave) != NULL){
                char*ID = strtok(line,",");
                char*date = strtok(NULL,",");
                char*typeleave = strtok(NULL,",");
                char*status = strtok(NULL,",");
                if (strcmp(date,wholedate)==0){
                    printf("%d) %s , %s , %s , %s , %s\n",number,ID,date,typeleave,status);
                    number++;
        }
    }
    fclose(leave);
    superior_menu();

            break;

        case 2:
            printf("\nQuitting...\n");
            superior_menu;
            break;

        default:
            printf("\nInvalid option selected. Please choose 1 or 2.\n");
            break;
    }
}

void AR(char *current_ID){
    char line[100];
    char line2[100];
    int number = 1;
    int option;
    printf("\nAll pending list\n");
    FILE * pending = fopen("Report Leave.txt","r");
    FILE * temp1 = fopen("temp1.txt","w");
    FILE * temp2 = fopen("temp2.txt","w");
    while(fgets(line,100,pending) != NULL){
        char*ID = strtok(line,",");
        char*date = strtok(NULL,",");
        char*typeleave = strtok(NULL,",");
        char*status = strtok(NULL,",");
        if (strcmp(status,"PENDING")== 0 ){
            printf("%d) %s , %s , %s , %s , %s\n",number,ID,date,typeleave,status);
            fprintf(temp1,"%s,%s,%s,%s,%s,\n",ID,date,typeleave,status);
            number++;
        }
        else{
            fprintf(temp2,"%s,%s,%s,%s,%s,\n",ID,date,typeleave,status);

        }
    }

    fclose(pending);
    fclose(temp1);
    fclose(temp2);
    ///////////////////////////////////////////////////////

    FILE * balance = fopen("leavebalance.txt","r");
    FILE * bclone = fopen("clonebalance.txt","a");
    printf("Choose a ID to Accept or Reject\n: ");
    scanf("%d",&option);
    int option2;
    int remaining;
    number = 1;
    FILE * temp3 = fopen("temp1.txt","r");
    FILE * temp4 = fopen("temp2.txt","a");
    while(fgets(line,100,temp3) != NULL){
        char*ID = strtok(line,",");
        char*date = strtok(NULL,",");
        char*typeleave = strtok(NULL,",");
        char*status = strtok(NULL,",");
        if (number == option){
            printf("1.Accept\n2.Reject\n");
            scanf("%d",&option2);
            switch(option2){
                case 1:
                    while (fgets(line2,100,balance)!= NULL){
                            char * BID = strtok(line2,",");
                            char * AL = strtok(NULL,",");
                            char * SL = strtok(NULL,",");
                            if (strcmp(BID,ID)==0){
                                if (strcmp(typeleave,"Annual Leave")==0){
                                    remaining = atoi(AL) - 1;
                                    if (remaining > 0 || remaining == 0){
                                        strcpy(status,"ACCEPTED\n");
                                        fprintf(bclone,"%s,%d,%s,",BID,remaining,SL);
                                    }
                                    else{
                                        strcpy(status,"REJECTED");
                                        printf("THIS ID HAVE NOT ENOUGH LEAVE\n");
                                        fprintf(bclone,"%s,%s,%s,\n",BID,AL,SL);
                                    }
                                    }
                                    else if (strcmp(typeleave,"Sick Leave")==0){
                                    remaining = atoi(SL) - 1;
                                        if (remaining > 0 || remaining == 0){
                                            strcpy(status,"ACCEPTED\n");
                                            fprintf(bclone,"%s,%s,%d,\n",BID,AL,remaining);
                                    }
                                        else{
                                            strcpy(status,"REJECTED");
                                            printf("THIS ID HAVE NOT ENOUGH LEAVE(AUTO REJECT)\n");
                                            fprintf(bclone,"%s,%s,%s,\n",BID,AL,SL);
                                    }
                                }
                            }
                            else{
                                fprintf(bclone,"%s,%s,%s,\n",BID,AL,SL);

                        }
                        }
                    break;
                case 2:
                    strcpy(status,"REJECTED");
                    break;
            }
            fprintf(temp4,"%s,%s,%s,%s,\n",ID,date,typeleave,status);
        }
        else{
            fprintf(temp4,"%s,%s,%s,%s,\n",ID,date,typeleave,status);
        }
        number ++;
    }
    fclose(temp3);
    fclose(temp4);
    fclose(bclone);
    fclose(balance);
    //////////////////////////////////////////
    printf("Changes have been made\n");
    FILE * clone = fopen("temp2.txt","r");
    FILE * updated = fopen("Report Leave.txt","w");
    while(fgets(line,100,clone) != NULL){
            fprintf(updated,"%s",line);
        }
    FILE * bbclone = fopen("clonebalance.txt","r");
    FILE * bupdated = fopen("leavebalance.txt","w");
    while(fgets(line,100,bbclone) != NULL){
            fprintf(bupdated,"%s",line);
        }
    fclose(bbclone);
    fclose(bupdated);
    fclose(clone);
    fclose(updated);
    superior_menu();
}

void superior_menu(char *current_ID){
    printf("\n\nSuperior Menu");
    int option;
    printf("\n1.Accept or Reject leave\n2.Search staff(date)\n0.back to login\n:");
    scanf("%d",&option);
    switch (option){
        case 1:
            AR(current_ID);
            break;
        case 2:
            searchstaffdate();
            break;
        case 0:
            main();
            break;
    }
}



void clear(){
    FILE * temp1 = fopen("temp1.txt","w");
    FILE * temp2 = fopen("temp2.txt","w");
    FILE * bclone = fopen("clonebalance.txt","w");
    fclose(temp1);
    fclose(temp2);
    fclose(bclone);
}

void choose_school(){
    int option;
    while (1) {
        printf("Choose School\n");
        printf("1. School Of Computing\n2. School of Foundation\n3. School of Psychology\n:");
        if (scanf("%d", &option) != 1) {

            printf("Invalid input. Please enter an integer.\n");

            while (getchar() != '\n');
            choose_school;
        } else {

            break;
        }
    }
    switch(option){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            printf("Invalid choice\n");
            choose_school();
    }
}

int main(){
    choose_school();
    R:
        clear();
        char current_user[100];
        char current_ID[100];
        char input_ID[100];
        char input_password[100];
        char line[100];
        int access = 1;
        char current_role[100];
        char department[100];
        printf("Welcome\n");
        printf("ID: ");
        scanf("%s",input_ID);
        printf("Password: ");
        scanf("%s",input_password);
        FILE * database = fopen("data.txt", "r");
        if (database == NULL) {
            printf("Error: Unable to open file\n");
            return 1;
        }
        while(fgets(line,100,database) != NULL){
            char *id = strtok(line,",");
            strcpy(current_ID,id);
            if(strcmp(input_ID, id) == 0){
                char *username = strtok(NULL, ",");
                char *password = strtok(NULL, ",");
                if(strcmp(input_password, password) == 0){
                    char *role = strtok(NULL, ",");
                    int int_role = (int) strtol(role, (char **)NULL, 10);
                    strcpy(current_user, username);
                    strcpy(current_role,id);
                    if (current_role[0]== 'A'){
                        strcpy(current_role,"Acedemic Department");
                    }
                    else if (current_role[0]== 'I'){
                        strcpy(current_role,"IT Department");
                    }
                    else if (current_role[0]== 'S'){
                        strcpy(current_role,"Student Service Department");
                    }
                    switch(int_role){
                        case 1:
                            access = 0;
                            printf("Access granted for staff\n");
                            printf("( %s,%s,%s )",current_ID,current_user,current_role);
                            login_menu_staff(current_ID);
                            break;
                        case 2:
                            access = 0;
                            printf("Access granted for Admin\n");
                            printf("( %s,%s,%s )",current_ID,current_user,current_role);
                            admin_menu();
                            break;
                        case 3:
                            access = 0;
                            printf("Access granted for Superior\n");
                            printf("( %s,%s,%s )",current_ID,current_user,current_role);
                            superior_menu(current_ID);
                            break;
                        default:
                            printf("Invalid role\n");
                            break;
                    }
                }
            }
        }
        fclose(database);
        if (access == 1){
            printf("wrong username or password\n\n");
            goto R;
        }
    return 0;
    }
