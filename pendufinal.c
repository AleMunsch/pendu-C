#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ESSAIS 8
#define NB_MOTS 835

char motSecret[50];		// mot a deviner
char motPartiel[50];		// mot composé des lettres trouvés et des '_'
char lettresFausses[26];	// tableau conttenant toutes les lettres comptées fausses
int essais = 0;			// compteur d fautes
int gg = 0;			// compteur de parties gagnées
int lose = 0;			// compteur de parties perdues

void initialiserMotSecret() {	// Ouvre le fichier "words.txt"

    FILE *fichier = fopen("words.txt", "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier 'words.txt'\n");
        exit(1);
    }

    srand( (unsigned int) time(NULL)); // Lis aléatoirement un mot du fichier
    int ligne = 0;
    int choix = rand() % NB_MOTS;
    while (fgets(motSecret, sizeof(motSecret), fichier) != NULL) {
        if (ligne == choix) {
            break;
        }
        ligne++;
    }
    fclose(fichier);
    
    motSecret[strcspn(motSecret, "\n")] = '\0'; // Supprime le caractère '_'
}

void afficherMot() {
    for (size_t i = 0; i < strlen(motSecret); i++) {
        if (motPartiel[i] == 0) {
            printf("_ ");
        } else {
            printf("%c ", motPartiel[i]);
        }
    }
    printf("\n");
}

void afficherPendu() {	// affichage pendu
    
     switch (essais) {
     	case 0:
            printf("       \n");
            printf("        \n");
            printf("        \n");
            printf("        \n");
            printf("        \n");
            printf("        \n");
            break;
    	case 1:
            printf("       \n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            break;
        case 2:
            printf("  _____\n");
            printf(" |     |\n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            break;
        case 3:
            printf("  _____\n");
            printf(" |     |\n");
            printf(" O     |\n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            break;
        case 4:
            printf("  _____\n");
            printf(" |     |\n");
            printf(" O     |\n");
            printf(" |     |\n");
            printf("       |\n");
            printf("       |\n");
            break;
        case 5:
            printf("  _____\n");
            printf(" |     |\n");
            printf(" O     |\n");
            printf("/|     |\n");
            printf("       |\n");
            printf("       |\n");
            break;
        case 6:
            printf("  _____\n");
            printf(" |     |\n");
            printf(" O     |\n");
            printf("/|\\    |\n");
            printf("       |\n");
            printf("       |\n");
            break;
        case 7:
            printf("  _____\n");
            printf(" |     |\n");
            printf(" O     |\n");
            printf("/|\\    |\n");
            printf("/      |\n");
            printf("       |\n");
            break;
        case 8:
            printf("  _____\n");
            printf(" |     |\n");
            printf(" O     |\n");
            printf("/|\\    |\n");
            printf("/ \\    |\n");
            printf("       |\n");
            break;
    }
}
/*
void afficherNbLettres() {
    printf("Le mot à deviner contient %d lettres.\n", (int)strlen(motSecret));
}
*/
char demanderLettre() {
    char lettre;
    printf("Devinez une lettre : ");
    scanf(" %c", &lettre);
    return lettre;
}

int lettreDejaDonnee(char lettre) {
    for (int i = 0; i < essais; i++) {
        if (lettresFausses[i] == lettre) {
            return 1;	// La lettre a déjà été donnée
        }
    }
    return 0;	// La lettre n'a pas encore été donnée
}


void verifierLettre(char lettre) {	// vérifie si la lettre entrée est dans le mot à trouvé et incrémente essaie si ce n'est pas le cas 
    if (lettreDejaDonnee(lettre)) {
        printf("Vous avez déjà donné cette lettre.\n");
        return;
    }

    int trouve = 0;
    for (size_t i = 0; i < strlen(motSecret); i++) {
        if (motSecret[i] == lettre) {
            motPartiel[i] = lettre;
            trouve = 1;
        }
    }
    if (!trouve) {
        lettresFausses[essais] = lettre;
        essais++;
    }
}

int estPartieGagnee() {		//  
    for (size_t i = 0; i < strlen(motSecret); i++) {
        if (motPartiel[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int estPartiePerdue() {
    return essais >= MAX_ESSAIS;
}

int rejouer() {
    char reponse;
    printf("Voulez-vous rejouer (o/n) ? ");
    scanf(" %c", &reponse);
    return (reponse == 'o' || reponse == 'O');
}

int main(void) {

    printf(" _____  ______ _   _ _____  _    _      \n");
    printf("|  __ \\|  ____| \\ | |  __ \\| |  | |  \n");
    printf("| |__) | |__  |  \\| | |  | | |  | |    \n");
    printf("|  ___/|  __| |     | |  | | |  | |     \n");
    printf("| |    | |____| |\\  | |__| | |__| |    \n");
    printf("|_|    |______|_| \\_|_____/ \\____/    \n\n");
 
    char nomJoueur[50];
    printf("Entrez votre nom : ");
    scanf("%s", nomJoueur);

    do {
        initialiserMotSecret();
        memset(motPartiel, 0, sizeof(motPartiel));
        memset(lettresFausses, 0, sizeof(lettresFausses));
        essais = 0;

        while (!estPartieGagnee() && !estPartiePerdue()) {
            printf("Essais restants : %d\n", MAX_ESSAIS - essais);
            afficherPendu();
            afficherMot();
            char lettre = demanderLettre();
            verifierLettre(lettre);
        }

        if (estPartieGagnee()) {
            printf("Félicitations, vous avez deviné le mot secret : %s!\n", motSecret);
            gg++;
        } else {
            printf("Désolé, vous avez épuisé tous vos essais. Le mot secret était : %s\n", motSecret);
            lose++;
        }       

    } while (rejouer());        

            FILE *score = fopen("score.txt", "a");	    // Sauvegarde du score dans le fichier classement
            if (score != NULL) {
                fprintf(score, "%s : %d parties gagnées, %d parties perdues\n", nomJoueur, gg, lose);
                fclose(score);
            } else {
                printf("Impossible de sauvegarder le score.\n");
            }
       

    return EXIT_SUCCESS;
}
