#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct address_t {
    int octet[4];
    char alias[11];
    struct address_t *next;
};

struct address_t *head = NULL;

struct address_t *findAddressByAlias(char *alias) {
    struct address_t *current = head;

    while (current != NULL) {
        if (strcmp(current->alias, alias) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

struct address_t *findAddressByValue(int octet1, int octet2, int octet3, int octet4) {
    struct address_t *current = head;

    while (current != NULL) {
        if (current->octet[0] == octet1 &&
            current->octet[1] == octet2 &&
            current->octet[2] == octet3 &&
            current->octet[3] == octet4) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}


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
    char alias[11];
    int octets[4];

    char iP[25];
    char dot;
    int IP[4];

    // Prompt user for IPv4 address/alias pair
    printf("Enter alias: ");
    scanf("%s", alias);

    if (findAddressByAlias(alias) != NULL) {
        printf("Error: alias already exists\n");
        return;
    }

    while (1) {
        // take user input for iP address
        printf("Enter address for %s: ", alias);
        scanf("%s", iP);

        // converts the string to int
        sscanf(iP, "%d%c%d%c%d%c%d", &IP[0], &dot, &IP[1], &dot, &IP[2], &dot, &IP[3]);
//    struct address_t *t;


        // check if iP address octets are valid
        if (IP[0] < 0 || IP[0] > 255) {
            printf("error: %s is an illegal address – please reenter: \n", iP);
            continue;
        }
        if (IP[1] < 0 || IP[1] > 255) {
            printf("error: %s is an illegal address – please reenter: \n", iP);
            continue;
        }
        if (IP[2] < 0 || IP[2] > 255) {
            printf("error: %s is an illegal address – please reenter: \n", iP);
            continue;
        }
        if (IP[3] < 0 || IP[3] > 255) {
            printf("error: %s is an illegal address – please reenter: \n", iP);
            continue;
        }
        break;
    }

    // Check that alias is not too long
    if (strlen(alias) > 10) {
        printf("Error: Alias must be 10 characters or less\n");
        return;
    }

    // Check if address or alias already exists in list
    if (findAddressByValue(octets[0], octets[1], octets[2], octets[3]) != NULL) {
        printf("Error: Address already exists\n");
        return;
    }

    // Create new address_t node and add to head of linked list
    struct address_t *newNode = (struct address_t *) malloc(sizeof(struct address_t));
    newNode->octet[0] = octets[0];
    newNode->octet[1] = octets[1];
    newNode->octet[2] = octets[2];
    newNode->octet[3] = octets[3];
    strcpy(newNode->alias, alias);
    newNode->next = head;
    head = newNode;

    printf("Address added successfully\n");
}


void lookUp_address() {
    char alias[11];
    printf("\nEnter alias: ");
    scanf("%s", alias);
    struct address_t *temp = head;
    while (temp != NULL) {
        if (strcasecmp(temp->alias, alias) == 0) {
            printf("Address for %s: %d.%d.%d.%d\n", alias, temp->octet[0], temp->octet[1], temp->octet[2], temp->octet[3]);
            return;
        }
        temp = temp->next;
    }
    printf("error: %s does not exist\n", alias);
}

void update_address() {
    char alias[11];
    printf("\nEnter alias: ");
    scanf("%s", alias);
    struct address_t *temp = head;
    while (temp != NULL) {
        if (strcasecmp(temp->alias, alias) == 0) {
            printf("Update address for %s: %d.%d.%d.%d\n", alias, temp->octet[0], temp->octet[1], temp->octet[2], temp->octet[3]);

            int octet[4] = {-1, -1, -1, -1};
            for(int i = 0; i < 4; i++) {
                do {
                    printf("\n");
                    printf("Enter location value # %d: (0-255): ", i+1);
                    scanf("%d", &octet[i]);
                    if (octet[i] < 0 || octet[i] > 255) {
                        printf("error: %d is an illegal entry – please reenter \n", octet[0]);
                    }
                } while (octet[i] < 0 || octet[i] > 255 );
            }


            struct address_t *temp2 = head;
            while (temp2 != NULL) {
                if (temp2 != temp && temp2->octet[0] == octet[0] && temp2->octet[1] == octet[1] &&
                    temp2->octet[2] == octet[2] &&
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
            printf("Updated address for %s \n", alias);
            return;
        }
        temp = temp->next;
    }
    printf("Error: Alias not found\n");
}


void delete_address() {
    char alias[11];
    printf("Enter alias of address to delete: ");
    scanf("%s", alias);

    // Find address node with matching alias
    struct address_t *current = head;
    struct address_t *prev = NULL;
    while (current != NULL && strcmp(current->alias, alias) != 0) {
        prev = current;
        current = current->next;
    }

    // If address node found, prompt user to confirm deletion
    if (current != NULL) {
        printf("Are you sure you want to delete the address '%s'? (y/n): ", alias);
        char confirm;
        scanf(" %c", &confirm);
        if (confirm == 'y' || confirm == 'Y') {
            // Delete address node
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("%s deleted\n" ,alias);
        } else {
            printf("Deletion cancelled\n");
        }
    } else {
        printf("Error: '%s' does not exist\n", alias);
    }
}


void display_location() {
    int first, second;
    printf("\n");
    do {
        printf("Enter location value # 1 (0-255): ");
        scanf("%d", &first);
        if (first < 0 || first > 255) {
            printf("error: %d is an illegal entry – please reenter \n", first);
        }
    } while (first < 0 || first > 255);
    printf("\n");
    do {
        printf("Enter location value # 2: (0-255): ");
        scanf("%d", &second);
    } while (second < 0 || second > 255);
    struct address_t *temp = head;
    while (temp != NULL) {
        if (temp->octet[0] == first && temp->octet[1] == second) {
            printf("%d. %s\n", temp->octet[3], temp->alias);
        }
        temp = temp->next;
    }
}

void save_to_file() {
    char filename[50];

    // Prompt user for filename
    printf("Enter file name: ");
    scanf("%s", filename);

    // Open file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Failed to open file for writing\n");
        return;
    }

    // Traverse list of addresses and write to file
    struct address_t *current = head;
    while (current != NULL) {
        fprintf(file, "%d.%d.%d.%d %s\n", current->octet[0], current->octet[1], current->octet[2], current->octet[3], current->alias);
        current = current->next;
    }

    // Close file
    fclose(file);

    printf("File saved. \n");
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
    printf("\nTotal node count: %d\n", count);
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