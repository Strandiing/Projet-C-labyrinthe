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

// On v�rifie si le d�placement est valide et autoris�

int valide(int x, int y, int hauteur, int largeur, char grille[hauteur][largeur]) {
return (x >= 0 && y >= 0 && x < largeur && y < hauteur && grille[y][x] != '#');
}

// On v�rifie � chaque d�placement si le labyrinthe est fini

int fini(int x, int y, int hauteur, int largeur, char grille[hauteur][largeur]) {
return valide(x, y, hauteur, largeur, grille) && grille[y][x] == '.';
}


// D�but du jeu du labyrinthe

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

// Initilisation de la position de d�part

int x = 1, y = 0;

// Initilisation des variables de d�placement

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

    // Cr�ation et affichage du labyrinthe ainsi que du joueur

    for(i = 0; i < HAUTEUR; ++i) {
        mvprintw(i, 0, "%s", grille[i]);
    }
    mvprintw(y, x, "@");
    mvprintw(y, x, "");
    refresh();
    deplacement_x = x; deplacement_y = y;

    // Gestion des entr�es clavier pour les d�placements

    switch(getch()) {
        case 'z': deplacement_y = y - 1; break;
        case 's': deplacement_y = y + 1; break;
        case 'q': deplacement_x = x - 1; break;
        case 'd': deplacement_x = x + 1; break;
    }

    // V�rification si le d�placement est autoris�, valable et d�placement du joueur si oui

    if(valide(deplacement_x, deplacement_y, HAUTEUR, LARGEUR, grille)) {
    x = deplacement_x; y = deplacement_y;
    }

    // R�p�tition de la boucle tant que le joueur n'est pas arriv� � la fin

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
