#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void maze();

int mazeMenu(){
    printf("How to play : \nZ : height move \nQ : right move \nS : Downward move \nD : Left move \n");
    printf("\n\n|===== MAZE ! =====|\n");
    printf("p Play || l Leave\n");
    printf("Enter your choice : ");

    char value;
    scanf("%c", &value);

    return (value);
}



#define HAUTEUR 18
#define LARGEUR 66

// On vérifie si le déplacement est valide et autorisé

int valide(int x, int y, int hauteur, int largeur, char grille[hauteur][largeur]) {
return (x >= 0 && y >= 0 && x < largeur && y < hauteur && grille[y][x] != '#');
}

// On vérifie à chaque déplacement si le labyrinthe est fini

int fini(int x, int y, int hauteur, int largeur, char grille[hauteur][largeur]) {
return valide(x, y, hauteur, largeur, grille) && grille[y][x] == '.';
}


// Début du jeu du labyrinthe

// Initialisation du labyrinthe
void maze(){
char grille[HAUTEUR][LARGEUR] = {
"# ##############################################################",
"#    #  #   #    #          #                     #       #   ##",
"### ###  ##  ##### ##### ## ### ### ### ##### #  # ## ##   #   #",
"#   # # # #  #  #       ###     ############          #        #",
"##    # ### #### ### ####  #####    ##    ##### ### #### ## ####",
"#### ##   # ##                         ######       #       #  #",
"#  #  ##        ##    ##### #### ###           # ###   #       #",
"#        #####     #     ##   #   ########### ####    #####    #",
"# # # ################ ###### #################### #############",
"#   #     #          #   #### ####     ####  #####             #",
"# #  #   #    # #   #   #         ####        #   #  ####  #  ##",
"### # ## #    # # ### ##### ###         ### #    #  #    ##   ##",
"#   #  # ####   #       #        ##########  ##  #           ###",
"# #### # #   ####### ######## #                  ###### # ######",
"# #  # #   #       #    #      ### ####### #########  ###      #",
"# ## # ########### ###### #####        ###     #####    ##  ####",
"#    #              #             #####    ###     #### #      #",
"##############################################################.#"};

// Initilisation de la position de départ

int x = 1, y = 0;

// Initilisation des variables de déplacement

int deplacement_x, deplacement_y;
int i;

// Initialisation de la librairies ncurses

initscr();
noecho();
cbreak();

// Boucle du jeu du labyrinthe

do {

    // Nettoyage du terrain de jeu

    clear();

    // Création et affichage du labyrinthe ainsi que du joueur

    for(i = 0; i < HAUTEUR; ++i) {
        mvprintw(i, 0, "%s", grille[i]);
    }
    mvprintw(y, x, "@");
    mvprintw(y, x, "");
    refresh();
    deplacement_x = x; deplacement_y = y;

    // Gestion des entrées clavier pour les déplacements

    switch(getch()) {
        case 'z': deplacement_y = y - 1; break;
        case 's': deplacement_y = y + 1; break;
        case 'q': deplacement_x = x - 1; break;
        case 'd': deplacement_x = x + 1; break;
    }

    // Vérification si le déplacement est autorisé, valable et déplacement du joueur si oui

    if(valide(deplacement_x, deplacement_y, HAUTEUR, LARGEUR, grille)) {
    x = deplacement_x; y = deplacement_y;
    }

    // Répétition de la boucle tant que le joueur n'est pas arrivé à la fin

} while(! fini(x, y, HAUTEUR, LARGEUR, grille));
refresh();
clrtoeol();
refresh();
endwin();
}

int main() {
    char value;
    value = mazeMenu();
    switch (value){
        case 'p':
            maze();
            break;
        case 'l':
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Invalid choice\n");
            main();
            break;
    }
}
