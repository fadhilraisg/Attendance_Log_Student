#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct node {
    long long NIM;
    char name[100];
    int hour, minute, second;
    struct node *left, *right;
};

struct node* createNewNode(char name[], long long NIM, int hour, int minute, int second) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    strcpy(newNode->name, name);
    newNode->NIM = NIM;
    newNode->hour = hour;
    newNode->minute = minute;
    newNode->second = second;

    newNode->left = NULL;
    newNode->right = NULL;
}

void inOrder(struct node* root) {
    if(root != NULL) {
        inOrder(root->left);
        printf("Name : %s - NIM : %lld - Time Attendance : %02d:%02d:%02d\n", root->name, root->NIM, root->hour, root->minute, root->second);
        inOrder(root->right);
    }
}

struct node* insert(struct node* root, char name[], long long NIM, int hour, int minute, int second) {
    if(root == NULL) {
        return createNewNode(name, NIM, hour, minute, second);
    } else if(NIM > root->NIM) {
        root->right = insert(root->right, name, NIM, hour, minute, second);
    } else if(NIM < root->NIM) {
        root->left = insert(root->left, name, NIM, hour, minute, second);
    }
    return root;
}

struct node* search(struct node* root, long long NIM) {
    if(root != NULL) {
        if(root->NIM == NIM) {
            return root;
        } else if(root->NIM < NIM) {
            return search(root->right, NIM);
        } else if(root->NIM > NIM) {
            return search(root->left, NIM);
        }
        return NULL;
    }
}

int main () {
    struct node* root = NULL;
    long long NIM;
    char name[100];
    int hour, minute, second;
    int MENU;

    do {
        printf("\n\nA T T E N D A N C E   A P P L I C A T I O N\n\n");
        printf("1. Input Student Attendance\n");
        printf("2. Show Student Attendance\n");
        printf("3. Search Student Attendance by NIM\n");
        printf("\nChoose >> ");
        scanf("%d", &MENU); getchar();

        switch(MENU) {
            case 1 :
                system("cls");
                printf("I N P U T   A T T E N D A N C E\n\n");
                printf("Input Name : ");
                scanf("%[^\n]", name); getchar();
                printf("Input NIM : ");
                scanf("%lld", &NIM); getchar();

                time_t t = time(NULL);
                struct tm currtime = *localtime(&t);
                hour = currtime.tm_hour;
                minute = currtime.tm_min;
                second = currtime.tm_sec;

                printf("\nName : %s", name);
                printf("\nNIM : %lld", NIM);
                printf("\nAttendance Time : %02d:%02d:%02d", hour, minute, second);

                root = insert(root, name, NIM, hour, minute, second);

                break;
            
            case 2 :
                system("cls");
                printf("S H O W   A T T E N D A N C E\n\n");
                inOrder(root);
                break;

            case 3 :
                system("cls");
                printf("S E A R C H   S T U D E N T\n\n");
                printf("Input the NIM : ");
                scanf("%lld", &NIM); getchar();
                root = search(root, NIM);
                if(root == NULL) {
                    printf("The Student was not present\n");
                } else {
                    printf("\nName : %s\n", root->name);
                    printf("Attendance Time : %02d:%02d:%02d\n", root->hour, root->minute, root->second);
                }
                break;
            
            default :
                printf("Menu doesn't exist >>> Choose other Menu :)\n");
                break;
        }
    } while(MENU != 0);

    return 0;
}