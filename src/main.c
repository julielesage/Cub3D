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

// SANS MAKEFILE :
// gcc main.c first.c ArgvChecks.c
// ./a.out truc.cub --save

#include "cub3d.h"

void	ft_init(char *cub, int save)
{
  t_all s;
  if (save == 1)
	write(1,"saved\n", 6);
  else
    write(1,"not saved\n", 10);
  if (ft_parse_cub(&s, cub) == 1)
    return (ft_close(&s, 0);;
}

int		verify_argvs(int argc, char **argv)
{
  if (argc == 3 && (my_strcmp(argc[1], "--save") == 0) && (extensionCheck(argv[1], "cub") == 0)
    //initialisation de toutes les structures av     i         int bpm 1 pour un enregistrement de la première image à apparaitre
    ft_init(argv[1], 1);
  else if (argc == 2 && (extensionCheck(argv[1], "cub") == 0)
	//same initialisation de toutes les structures mais avec image int bpm 0
    ft_init(argv[1], 0);
  else
    return (1);
}

int		main(int argc, char **argv)
{
	if (verify_argvs(argc, argv) == 1)
		write(2,"Error\nVerified: invalid arguments can not be taken", 56);
}
