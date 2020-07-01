// Plus le rayon va loin dans le décor, plus la distance qui sépare la caméra de l’obstacle est importante. Plus l’obstacle est loin de la caméra et plus l’objet paraîtra petit une fois projeté sur l’écran.
// Les paramètres à définir lorsqu'on va projeter les rayons sont :

// La hauteur de la caméra
// hauteu camera = hauteur mur / 2

// Le champ visuel de la camera = 60°

// L’orientation de la camera dans la map (son angle) = 60°
// si l'angle de rotation du regard est à 45° de l'axe x,
// 60 / 2 = 30 . 45 + 30 = 75 . 45 - 30 = 15
// le champ visuel de la caméra ira de 75° à 15° par rapport à l'axe X

// La position de la camera dans la map (posCamX et posCamY)

// Ecran de projection :
// Dimensions de l’écran de projection = 320 x 200 px (ou cubes)
// Centre de l’écran de projection = (160,100)
// Distance entre la camera et l’écran de projection = 277
// Angle entre deux rayons consécutifs en ° = 60°/320px
// On lance 320 rayons : toutes les colonnes de la grille

// Digital Differential Analyser :
// = vérifier à chaque intersection du rayon si mur ou non, si mur on stoppe la vérification du rayon

// fonctions autorisées : open, close, read, write,
// malloc, free, perror,
// strerror, exit + libft
// • Toutes les fonctions de
// la lib math (-lm man man 3
// math)
// • Toutes les fonctions de la
// MinilibX

// Arguments : Une map dans le format *.cub :

// R (ID résolution) 1920(x) 1080(y)
// NO ./path_to_the_north_texture (texture nord)
// SO ./path_to_the_south_texture (texture sud)
// WE ./path_to_the_west_texture (texture ouest)
// EA ./path_to_the_east_texture (texture est)

// S ./path_to_the_sprite_texture (texture sprite = obstacle)
// F 220,100,0 (couleur du sol/floor RGB range 255)
// C 225,30,0 (couleur du plafond/ceil RGB range 255)

//         1111111111111111111111111
//         1000000000110000000000001
//         1011000001110000002000001
//         1001000000000000000000001
// 111111111011000001110000000000001
// 100000000011000001110111111111111
// 11110111111111011100000010001
// 11110111111111011101010010001
// 11000000110101011100000010001
// 10002000000000001100000010001
// 10000000000000001101010010001
// 11000001110101011111011110N0111
// 11110111 1110101 101111010001
// 11111111 1111111 111111111111

// 1 = mur
// 2 = obstacle
// N = position de la caméra regardant vers le Nord

int main(int argc, char **argv)
{
  //if nb argc = 3 et arg = cub c'est ok on initialise
  //parsingInfos() gérer les espaces et lignes vides avant la map, tout peut etre dans n'importe quel ordre avant la map
  //check si fuite dans map, si oui renvoyer une erreur
  // check si only 0, 1, 2 et N ou W ou E ou S 1 seule fois dans la map sinon erreur
  // erreur
  else write(2, "Error\nYour map configuration can not be taken as it is.", 56);
}