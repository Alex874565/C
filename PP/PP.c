#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char FORMS_FILE[100] = "/home/alex874565/Desktop/Facultate/C/PP/Forms.txt";
char UNIVERSITIES_FILE[100] = "/home/alex874565/Desktop/Facultate/C/PP/Universities.txt";


int action = 10000;
int NR_UNIV = 2;

struct SPECIALIZARE{
    char nume[100];
    int nr_aplicari;
};

struct FACULTATE{
    char nume[100];
    struct SPECIALIZARE specializari[100];
    char nr_specializari;
    int nr_aplicari;
};

struct UNIVERSITATE{
    char nume[100];
    struct FACULTATE facultati[100];
    char nr_facultati;
    int nr_aplicari;
}LISTA_UNIV[100];

void citire(int *NR_UNIV, struct UNIVERSITATE (*LISTA_UNIV)[], char *filepath){ 
    struct UNIVERSITATE *univ;
    struct FACULTATE *fac;
    struct SPECIALIZARE *spec;
    char tmp[100];
    FILE *file;
    file = fopen(filepath, "r");
    fscanf(file, "%d\n", NR_UNIV);
    for(int univ_index = 0; univ_index < *NR_UNIV; univ_index++){
        univ = &((*LISTA_UNIV)[univ_index]);
        fgets(univ->nume, 100, file);
        univ->nume[strcspn(univ->nume, "\n")] = 0;
        fscanf(file, "%d\n", &(univ->nr_facultati));
        fscanf(file, "%d\n", &(univ->nr_aplicari));
        for (int fac_index = 0; fac_index < univ->nr_facultati; fac_index++){
            fac = &(univ->facultati[fac_index]);
            fgets(fac->nume, 100, file);
            fac->nume[strcspn(fac->nume, "\n")] = 0;
            fscanf(file, "%d\n", &(fac->nr_specializari));
            fscanf(file, "%d\n", &(fac->nr_aplicari));
            fflush(stdout);
            for(int spec_index = 0; spec_index < fac->nr_specializari; spec_index++){
                spec = &(fac->specializari[spec_index]);
                fgets(spec->nume, 100, file);
                spec->nume[strcspn(spec->nume, "\n")] = 0;
                fscanf(file, "%d\n", &(spec->nr_aplicari));
            }
        }
    }
}

void update(int *NR_UNIV, struct UNIVERSITATE (*LISTA_UNIV)[], char* filepath){
    struct UNIVERSITATE *univ;
    struct FACULTATE *fac;
    struct SPECIALIZARE *spec;
    char tmp[100];
    FILE *file;
    file = fopen(filepath, "w");
    fprintf(file, "%d\n", *NR_UNIV);
    for(int univ_index = 0; univ_index < *NR_UNIV; univ_index++){
        univ = &((*LISTA_UNIV)[univ_index]);
        //fgets(univ->nume, 100, file);
        fprintf(file, "%s\n", univ -> nume);
        //univ->nume[strcspn(univ->nume, "\n")] = 0;
        fprintf(file, "%d\n", univ->nr_facultati);
        fprintf(file, "%d\n", univ->nr_aplicari);
        for (int fac_index = 0; fac_index < univ->nr_facultati; fac_index++){
            fac = &(univ->facultati[fac_index]);
            //fgets(fac->nume, 100, file);
            fprintf(file, "%s\n", fac -> nume);
            //fac->nume[strcspn(fac->nume, "\n")] = 0;
            fprintf(file, "%d\n", fac->nr_specializari);
            fprintf(file, "%d\n", fac->nr_aplicari);
            fflush(stdout);
            for(int spec_index = 0; spec_index < fac->nr_specializari; spec_index++){
                spec = &(fac->specializari[spec_index]);
                //fgets(spec->nume, 100, file);
                //spec->nume[strcspn(spec->nume, "\n")] = 0;
                fprintf(file, "%s\n", spec->nume);
                fprintf(file, "%d\n", spec->nr_aplicari);
            }
        }
    }
    fclose(file);
}


void main_menu();
char alegere_universitate(struct UNIVERSITATE [100], short);
char alegere_facultate(struct UNIVERSITATE [100], char);
char alegere_specializare(struct UNIVERSITATE [100], short, short);
char statistici_universitate(struct UNIVERSITATE [100], short);
char statistici_facultate(struct UNIVERSITATE [100], char);
char statistici_specializare(struct UNIVERSITATE [100], short, short);
char vizualizare_statistici(struct UNIVERSITATE [], int);
char formular(struct UNIVERSITATE (*)[], short, short, short, char []);
char vizualizare_formulare(char []);

int main(){
    int nr_univ;
    citire(&NR_UNIV, &LISTA_UNIV, UNIVERSITIES_FILE);
    main_menu();
}

void main_menu(){
    char returned = 1; 
    do{
    system("clear"); // "cls" pentru windows
    printf(ANSI_COLOR_CYAN "--== MENIU PRINCIPAL  ==--" ANSI_COLOR_RESET"\n\n");
    printf("(1) -Alegeti o universitate-\n");
    printf("(2) -Vizualizati formularele completate-\n");
    printf("(3) -Vizualizati statistici-\n");
    printf("\n" ANSI_COLOR_CYAN"(0) -Iesire-\n\n");
        printf("Alegeti o optiune: ");
        scanf("%d", &action);
        while(action < 0 || action > 3){
            printf("Optiune nevalida. Incercati din nou: ");
            scanf("%d", &action);
        }
        if (action == 1){
            returned = alegere_universitate(LISTA_UNIV, NR_UNIV);
        }else if (action == 2){
            vizualizare_formulare(FORMS_FILE);
        }else if (action == 3){
            vizualizare_statistici(LISTA_UNIV, NR_UNIV);
        }else if (action == 0){
            printf("Abandonare..." ANSI_COLOR_RESET "\n"); return;
        }
    }while(returned);
}

char alegere_universitate(struct UNIVERSITATE universitati[100], short nr_univ){
    char returned = 1;
    do{
        system("clear"); // "cls" pentru windows
        printf(ANSI_COLOR_CYAN "--== Alegere Universitate ==--" ANSI_COLOR_RESET"\n\n");
        for(char index = 0; index < nr_univ; index++){
            printf("(%d) -%s-\n", index + 1, universitati[index].nume);
        }
        printf("\n" ANSI_COLOR_CYAN "(-1) -Inapoi-\n");
        printf("(0) -Iesire-\n\n");
        printf("Alegeti o optiune: ");
        scanf("%d", &action);
        while(-1 > action || NR_UNIV < action){
            printf("Optiune nevalida. Incercati din nou: ");
            scanf("%d", &action);
        }
        if (action == 0){
            printf("Abandonare..." ANSI_COLOR_CYAN "\n");
            exit(0);
        }else if(action == -1){
            action = 1;
            return 1;
        }else{
            returned = alegere_facultate(LISTA_UNIV, action-1);
        }
    }while (returned == 1);
    if (returned == 2){
        return 2;
    }
}

char alegere_facultate(struct UNIVERSITATE universitati[100], char nr_universitate){
    char returned = 1;
    do{
        system("clear"); // "cls" pentru windows
        printf(ANSI_COLOR_CYAN "--== Alegere Facultate ==--" ANSI_COLOR_RESET "\n\n");
        struct UNIVERSITATE universitate = universitati[nr_universitate];
        for (short index = 0; index < universitate.nr_facultati; index++){
            printf("(%d) -%s-\n", index + 1, universitate.facultati[index].nume);
        }
        printf("\n" ANSI_COLOR_CYAN "(-1) -Inapoi-\n");
        printf("(0) -Iesire-\n\n");
        printf("Alegeti o optiune: ");
        scanf("%d", &action);
        while(-1 > action || universitate.nr_facultati < action){
            printf("Optiune nevalida. Incercati din nou: ");
            scanf("%d", &action);
        }
        if (action == 0){
            printf("Abandonare..." ANSI_COLOR_RESET "\n");
            exit(0);
        }else if(action == -1){
            action = nr_universitate + 1;
            return 1;
        }else{
            returned = alegere_specializare(LISTA_UNIV, nr_universitate, action - 1);
        }
    }while(returned == 1);
    if (returned == 2){
        return 2;
    }
}

char alegere_specializare(struct UNIVERSITATE universitati[100], short nr_universitate, short nr_facultate){
    char returned = 1;
    do{
        system("clear"); // "cls" pentru windows
        struct UNIVERSITATE universitate = universitati[nr_universitate];
        struct FACULTATE facultate = universitate.facultati[nr_facultate];
        printf( ANSI_COLOR_CYAN "--== Alegere Specializare ==--" ANSI_COLOR_RESET "\n\n");
        for(char index = 0; index < facultate.nr_specializari; index++){
            printf("(%d) -%s-\n", index + 1, facultate.specializari[index].nume);
        }
        printf("\n" ANSI_COLOR_CYAN "(-1) -Inapoi-\n");
        printf("(0) -Iesire-\n\n");
        printf("Alegeti o optiune: ");
        scanf("%d", &action);
        while(-1 > action || facultate.nr_specializari < action){
            printf("Optiune nevalida. Incercati din nou: ");
            scanf("%d", &action);
        }
        if (action == 0){
            printf("Abandonare..." ANSI_COLOR_RESET "\n");
            exit(0);
        }else if(action == -1){
            action = nr_facultate + 1;
            return 1;
        }else{
            int nr_specializare = action - 1;
            returned = formular(&LISTA_UNIV, nr_universitate, nr_facultate, nr_specializare, FORMS_FILE);
        }
    }while(returned == 1);
    if (returned == 2){
        return 2;
    }
}

char vizualizare_statistici(struct UNIVERSITATE *LISTA_UNIV, int NR_UNIV){
    system("clear"); // "cls" pentru windows
    printf(ANSI_COLOR_CYAN "--== Statistici ==--" ANSI_COLOR_RESET"\n\n");
    struct UNIVERSITATE univ;
    struct FACULTATE fac;
    struct SPECIALIZARE spec;
    for(int univ_index = 0; univ_index < NR_UNIV; univ_index++){
        univ = LISTA_UNIV[univ_index];
        printf("\n~ %s -- %d aplicanti ~", univ.nume, univ.nr_aplicari);
        for(int fac_index = 0; fac_index < univ.nr_facultati; fac_index++){
            fac = univ.facultati[fac_index];
            printf("\n        ~ %s -- %d aplicanti ~\n", fac.nume, fac.nr_aplicari);
            for(int spec_index = 0; spec_index < fac.nr_specializari; spec_index++){
                spec = fac.specializari[spec_index];
                printf("              ~ %s -- %d aplicanti ~\n", spec.nume, spec.nr_aplicari);
            }
        }
    }
    printf( ANSI_COLOR_CYAN "\n(-1) -Inapoi-\n");
    printf("(0) -Iesire-\n\n");
    printf("Alegeti o optiune: ");
    scanf("%d", &action);
    while(-1 > action || 0 < action){
        printf("Optiune nevalida. Incercati din nou: ");
        scanf("%d", &action);
    }
    if (action == 0){
        printf("Abandonare..." ANSI_COLOR_CYAN "\n");
        exit(0);
    }else if(action == -1){
        return 1;
    }
}

char formular(struct UNIVERSITATE (*LISTA_UNIV)[], short nr_universitate, short nr_facultate, short nr_specializare, char *filepath){
    char nume[100], prenume[100], tel[20];
    struct UNIVERSITATE *univ = &((*LISTA_UNIV)[nr_universitate]);
    struct FACULTATE *fac = &(univ->facultati[nr_facultate]);
    struct SPECIALIZARE *spec = &(fac->specializari[nr_specializare]);
    system("clear"); // "cls" pentru windows
    printf( ANSI_COLOR_CYAN "--== Completare Formular ==--" ANSI_COLOR_RESET "\n");
    printf( ANSI_COLOR_CYAN "\n(-1) -Inapoi-\n");
    printf("(0) -Iesire-" ANSI_COLOR_RESET "\n\n");
    
    printf("-Nume: ");
    scanf("%s", nume);
    if (strcmp(nume, "0") == 0){
        printf( ANSI_COLOR_CYAN "Abandonare..." ANSI_COLOR_RESET "\n");
        exit(0);
    }else if (strcmp(nume, "-1") == 0){
        return 1;
    }

    printf("-Prenume: ");
    scanf("%s", prenume);
    if (strcmp(prenume, "0") == 0){
        printf( ANSI_COLOR_CYAN "Abandonare..." ANSI_COLOR_RESET "\n");
        exit(0);
    }else if (strcmp(prenume, "-1") == 0) {
        return 1;
    }

    printf("-Tel: ");
    scanf("%s", tel);
    if (strcmp(tel, "0") == 0){
        printf( ANSI_COLOR_CYAN "Abandonare..." ANSI_COLOR_RESET "\n");
        exit(0);
    }else if (strcmp(tel, "-1") == 0){
        return 1;
    }
    FILE *file = fopen(filepath, "a");
    fprintf(file, "%s, %s, %s\nNume: %s\nPrenume: %s\nTel: %s\n", univ->nume, fac->nume, spec->nume, nume, prenume, tel);
    univ->nr_aplicari+=1;
    fac->nr_aplicari+=1;
    spec->nr_aplicari+=1;
    fclose(file);
    update(&NR_UNIV, LISTA_UNIV, UNIVERSITIES_FILE);
    return 2;
}

char vizualizare_formulare(char filepath[]){
    system("clear"); // "cls" pentru windows
    printf( ANSI_COLOR_CYAN "--== Formulare Completate ==--" ANSI_COLOR_RESET "\n\n");
    int index = 1;
    FILE *file = fopen(filepath, "r");
    char *output = (char *) malloc (100);
    output = fgets(output, 200, file);
    while(output){
        printf("%d. ", index);
        printf("%s", output);
        output = fgets(output, 100, file);
        printf("%s", output);
        output = fgets(output, 100, file);
        printf("%s", output);
        output = fgets(output, 100, file);
        printf("%s", output);
        output = fgets(output, 200, file);
        
        index += 1;
    }
    printf("\n" ANSI_COLOR_CYAN "(-1) -Inapoi-\n");
    printf("(0) -Iesire-\n\n");
    printf("Alegeti o optiune: ");
    scanf("%d", &action);
    while(-1 > action || 0 < action){
        printf("Optiune nevalida. Incercati din nou: ");
        scanf("%d", &action);
    }
    if (action == 0){
        printf("Abandonare..." ANSI_COLOR_RESET "\n");
        exit(0);
    }else if(action == -1){
        return 1;
    }
    scanf("%d", &action);
}