#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct address_t {
    int octet[4];
    char alias[11];
    struct address_t *next;
};

struct address_t *head = NULL;

void readFile() {
    FILE *fp = fopen("/home/hilla/Desktop/C_PLAIN/linked_dsa_CS531/CS531_Inet.txt", "r");
    if (fp == NULL) {
        printf("\nUnable to find file CS531_Inet.txt\n");
        return;
    }
    int first, second, third, fourth;
    char alias[11];
    while (fscanf(fp, "%d.%d.%d.%d %s\n", &first, &second, &third, &fourth, alias) == 5) {
        struct address_t *add = (struct address_t *) malloc(sizeof(struct address_t));
        add->octet[0] = first;
        add->octet[1] = second;
        add->octet[2] = third;
        add->octet[3] = fourth;
        strcpy(add->alias, alias);
        add->next = head;
        head = add;
    }
}

void add_address() {
    char address[50];
    printf("\nEnter IPV4/alias pair: ");
    char c;
    scanf("%c", &c);
    fgets(address, 50, stdin);
    int octet[4];
    char alias[11];
    sscanf(address, "%d.%d.%d.%d %s", &octet[0], &octet[1], &octet[2], &octet[3], alias);
    struct address_t *temp = head;
    while (temp != NULL) {
        if (temp->octet[0] == octet[0] && temp->octet[1] == octet[1] && temp->octet[2] == octet[2] &&
            temp->octet[3] == octet[3]) {
            printf("\nError: This address already_exists\n");
            return;
        }
//mqtches two strings with case insensitive comparison
        if (strcasecmp(temp->alias, alias) == 0) {
            printf("\nError: This address already_exists\n");
            return;
        }
        temp = temp->next;
    }
    temp = (struct address_t *) malloc(sizeof(struct address_t));
    temp->octet[0] = octet[0];
    temp->octet[1] = octet[1];
    temp->octet[2] = octet[2];
    temp->octet[3] = octet[3];
    strcpy(temp->alias, alias);
    temp->next = head;
    head = temp;
    printf("Address added\n");
}

void lookUp_address() {
    char alias[11];
    printf("\nEnter alias: ");
    scanf("%s", alias);
    struct address_t *temp = head;
    while (temp != NULL) {
        if (strcasecmp(temp->alias, alias) == 0) {
            printf("\nIPV4 Address %d.%d.%d.%d\n", temp->octet[0], temp->octet[1], temp->octet[2], temp->octet[3]);
            return;
        }
        temp = temp->next;
    }
    printf("Not Found\n");
}

//void update_address() {
//    char alias[11];
//    printf("\nEnter alias: ");
//    scanf("%s", alias);
//    struct address_t *temp = head;
//    while (temp != NULL) {
//        if (strcasecmp(temp->alias, alias) == 0) {
//            printf("\nIPV4 Address %d.%d.%d.%d\n", temp->octet[0], temp->octet[1], temp->octet[2], temp->octet[3]);
//            printf("\nEnter new IPV4: ");
//            char address[50];
//            scanf("%s", address);
//            int octet[4];
//            sscanf(address, "%d.%d.%d.%d", &octet[0], &octet[1], &octet[2], &octet[3]);
//            struct address_t *temp2 = head;
//            while (temp2 != NULL) {
//                if (temp2->octet[0] == octet[0] && temp2->octet[1] == octet[1] && temp2->octet[2] == octet[2] &&
//                    temp2->octet[3] == octet[3]) {
//                    printf("\nThis IPV4 already_exists\n");
//                    return;
//                }
//                temp2 = temp2->next;
//            }
//            temp->octet[0] = octet[0];
//            temp->octet[1] = octet[1];
//            temp->octet[2] = octet[2];
//            temp->octet[3] = octet[3];
//            printf("Address updated\n");
//            return;
//        }
//        temp = temp->next;
//    }
//    printf("Not Found\n");
//}

void update_address() {
    char alias[11];
    printf("\nEnter alias: ");
    scanf("%s", alias);
    struct address_t *temp = head;
    while (temp != NULL) {
        if (strcasecmp(temp->alias, alias) == 0) {
            printf("\nIPV4 Address %d.%d.%d.%d\n", temp->octet[0], temp->octet[1], temp->octet[2], temp->octet[3]);
            printf("\nEnter new IPV4: ");
            char address[50];
            scanf("%s", address);
            int octet[4];
            if (sscanf(address, "%d.%d.%d.%d", &octet[0], &octet[1], &octet[2], &octet[3]) != 4) {
                printf("Invalid input! Please enter the address in the correct format\n");
                return;
            }
            for (int i = 0; i < 4; i++) {
                if (octet[i] < 0 || octet[i] > 255) {
                    printf("Invalid input! Please enter values between 0-255\n");
                    return;
                }
            }
            struct address_t *temp2 = head;
            while (temp2 != NULL) {
                if (temp2 != temp && temp2->octet[0] == octet[0] && temp2->octet[1] == octet[1] && temp2->octet[2] == octet[2] &&
                    temp2->octet[3] == octet[3]) {
                    printf("Error: The entered address already exists\n");
                    return;
                }
                temp2 = temp2->next;
            }
            temp->octet[0] = octet[0];
            temp->octet[1] = octet[1];
            temp->octet[2] = octet[2];
            temp->octet[3] = octet[3];
            printf("IPV4 Address updated\n");
            return;
        }
        temp = temp->next;
    }
    printf("Error: Alias not found\n");
}


void delete_address() {
    char alias[11];
    printf("\nEnter alias: ");
    scanf("%s", alias);
    struct address_t *temp = head;
    struct address_t *prev = NULL;
    while (temp != NULL) {
        if (strcasecmp(temp->alias, alias) == 0) {
            printf("\nIPV4 Address %d.%d.%d.%d\n", temp->octet[0], temp->octet[1], temp->octet[2], temp->octet[3]);
            printf("Do you want to delete this address (y/n): ");
            char choice;
//            fflush(stdin);
            scanf("%c", &choice);
            if (choice == 'y') {
                // if head node is to be removed
                if (prev == NULL) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                free(temp);
                printf("Address deleted\n");
                return;
            } else return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Not Found\n");
}

void display_location() {
    int first, second;
    printf("\n");
    do {
        printf("Enter location value # 1 (0-255): ");
        scanf("%d", &first);
        if (first < 0 || first > 255) {
            printf("error: %d is an illegal entry – please reenter ", first);
        }
    } while (first < 0 || first > 255);
    printf("\n");
    do {
        printf("Enter location value # 2: (0-255):");
        scanf("%d", &second);
    } while (second < 0 || second > 255);
    struct address_t *temp = head;
    while (temp != NULL) {
        if (temp->octet[0] == first && temp->octet[1] == second) {
            printf("%s\n", temp->alias);
        }
        temp = temp->next;
    }
}

void save_to_file() {
    if (head == NULL) {
        printf("\nList empty nothing to save\n");
        return;
    }
    printf("\nEnter filename: ");
    char filename[30];
    scanf("%s", filename);
    FILE *fp = fopen(filename, "w");
    struct address_t *temp = head;
    while (temp != NULL) {
        fprintf(fp, "%d.%d.%d.%d %s\n", temp->octet[0], temp->octet[1], temp->octet[2], temp->octet[3], temp->alias);
        temp = temp->next;
    }
    printf("Saved data to %s\n", filename);
}

void display_list() {
    printf("\n");
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct address_t *temp = head;
    int count = 0;
    while (temp != NULL) {
        printf("%d.%d.%d.%d  %s\n", temp->octet[0], temp->octet[1], temp->octet[2], temp->octet[3], temp->alias);
        count++;
        temp = temp->next;
    }
    printf("\n%d nodes in List\n", count);
}

void quit() {
    printf("Goodbye!");
    exit(0);
}

int menu() {
    printf("\n1.Add Address  "
           "\n2.Look Up Address  "
           "\n3.update Address  "
           "\n4.Delete Address");
    printf(""
           "\n5.Display List  "
           "\n6.Display aliases for location  "
           "\n7.Save to file  "
           "\n8.Quit: ");
    int choice;
    scanf("%d", &choice);
    return choice;
}

int main() {
    readFile();
    while (1) {
        int choice = menu();
        if (choice == 1) add_address();
        else if (choice == 2) lookUp_address();
        else if (choice == 3) update_address();
        else if (choice == 4) delete_address();
        else if (choice == 5) display_list();
        else if (choice == 6) display_location();
        else if (choice == 7) save_to_file();
        else if (choice == 8) quit();
        else printf("Invalid choice\n");
    }
}