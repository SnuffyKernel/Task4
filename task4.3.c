#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char lastName[50];
    char firstName[50];
    char job[50];
    char position[50];
    char phone[15];
    char email[50];
    char socialLink[50];
    char messenger[50];
} Contact;

typedef struct Node {
    Contact contact;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

Node* createNode(Contact contact) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->contact = contact;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return node;
}

int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b)? a : b;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

int compareContacts(Contact c1, Contact c2) {
    int lastNameComparison = strcmp(c1.lastName, c2.lastName);
    if (lastNameComparison == 0) {
        return strcmp(c1.firstName, c2.firstName);
    }
    return lastNameComparison;
}

Node* insert(Node* node, Contact contact) {
    if (node == NULL)
        return createNode(contact);

    if (compareContacts(contact, node->contact) < 0)
        node->left = insert(node->left, contact);
    else if (compareContacts(contact, node->contact) > 0)
        node->right = insert(node->right, contact);
    else 
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);


    if (balance > 1 && compareContacts(contact, node->left->contact) < 0)
        return rightRotate(node);

    if (balance < -1 && compareContacts(contact, node->right->contact) > 0)
        return leftRotate(node);

    if (balance > 1 && compareContacts(contact, node->left->contact) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && compareContacts(contact, node->right->contact) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

Node* deleteNode(Node* root, Contact contact) {
    if (root == NULL)
        return root;
        if (compareContacts(contact, root->contact) < 0)
        root->left = deleteNode(root->left, contact);
    else if (compareContacts(contact, root->contact) > 0)
        root->right = deleteNode(root->right, contact);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp; 

            free(temp);
        } else {
            Node* temp = minValueNode(root->right);

            root->contact = temp->contact;

            root->right = deleteNode(root->right, temp->contact);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* search(Node* root, Contact contact) {
    if (root == NULL  || compareContacts(root->contact, contact) == 0)
        return root;

    if (compareContacts(contact, root->contact) < 0)
        return search(root->left, contact);
    return search(root->right, contact);
}

void printContact(Contact contact) {
    printf("\n");
    printf("Ф.И.О.: %s %s\n", contact.lastName, contact.firstName);
    if (strlen(contact.job) > 0) printf("Место работы: %s\n", contact.job);
    if (strlen(contact.position) > 0) printf("Должность: %s\n", contact.position);
    if (strlen(contact.phone) > 0) printf("Номер телефона: %s\n", contact.phone);
    if (strlen(contact.email) > 0) printf("Электронная почта: %s\n", contact.email);
    if (strlen(contact.socialLink) > 0) printf("Ссылка на страницу в соцсети: %s\n", contact.socialLink);
    if (strlen(contact.messenger) > 0) printf("Профиль в мессенджере: %s\n", contact.messenger);
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printContact(root->contact);
        inOrder(root->right);
    }
}

void editContact(Node* root, Contact oldContact, Contact newContact) {
    Node* node = search(root, oldContact);
    if (node != NULL) {
        node->contact = newContact;
    }
}

Contact createContact() {
    Contact contact;
    printf("Введите фамилию: ");
    scanf("%s", contact.lastName);
    printf("Введите имя: ");
    scanf("%s", contact.firstName);
    printf("Введите место работы: ");
    scanf("%s", contact.job);
    printf("Введите должность: ");
    scanf("%s", contact.position);
    printf("Введите номер телефона: ");
    scanf("%s", contact.phone);
    printf("Введите адрес электронной почты: ");
    scanf("%s", contact.email);
    printf("Введите ссылку на страницу в соцсети: ");
    scanf("%s", contact.socialLink);
    printf("Введите профиль в мессенджере: ");
    scanf("%s", contact.messenger);
    return contact;
}

int main() {
    Node* root = NULL;
    int choice;
    Contact contact, oldContact, newContact;

    do {
        printf("\nТелефонная книга:\n");
        printf("1. Добавить контакт\n");
        printf("2. Удалить контакт\n");
        printf("3. Редактировать контакт\n");
        printf("4. Показать все контакты\n");
        printf("5. Выйти\n");
        printf("Выберите опцию: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                contact = createContact();
                root = insert(root, contact);
                break;
            case 2:
                printf("Введите фамилию и имя контакта для удаления:\n");
                printf("Фамилия: ");
                scanf("%s", oldContact.lastName);
                printf("Имя: ");
                scanf("%s", oldContact.firstName);
                root = deleteNode(root, oldContact);
                break;
            case 3:
                printf("Введите фамилию и имя контакта для редактирования:\n");
                printf("Фамилия: ");
                scanf("%s", oldContact.lastName);
                printf("Имя: ");
                scanf("%s", oldContact.firstName);
                newContact = createContact();
                editContact(root, oldContact, newContact);
                break;
            case 4:
                inOrder(root);
                break;
            case 5:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный ввод, попробуйте снова.\n");
        }
    } while (choice != 5);

    return 0;
}

