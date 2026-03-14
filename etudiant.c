#include <stdio.h>
#include <stdlib.h>

struct student {
    int id;
    char fullName[50];
    int age;
};

void saisir(int *n) {
    do {
        printf("Donnez n : ");
        scanf("%d", n);
    } while (*n <= 0);
}

void remplir(int n, struct student *t) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Etudiant %d ---\n", i + 1);

        printf("ID : ");
        scanf("%d", &t[i].id);

        printf("Nom complet : ");
        scanf(" %49[^\n]", t[i].fullName);

        printf("Age : ");
        scanf("%d", &t[i].age);
        while (t[i].age < 5 || t[i].age > 100) {
            printf("Age invalide ! Entrez un age entre 5 et 100 : ");
            scanf("%d", &t[i].age);
        }
    }
}

void afficher(int n, struct student *t) {
    printf("\n========== Liste des etudiants ==========\n");
    for (int i = 0; i < n; i++) {
        printf("Etudiant %d :\n", i + 1);
        printf("  ID       : %d\n", t[i].id);
        printf("  Nom      : %s\n", t[i].fullName);
        printf("  Age      : %d\n", t[i].age);
        printf("-----------------------------------------\n");
    }
}

int main() {
    int n;
    saisir(&n);

    struct student *t;
    t = (struct student *)malloc(sizeof(struct student) * n);

    if (t == NULL) {
        printf("Erreur d'allocation memoire.\n");
        return 1;
    }

    remplir(n, t);
    afficher(n, t);

    free(t);
    return 0;
}
