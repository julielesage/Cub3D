#include "../../cub3d.h"

unsigned int pixelize_spr(t_all *s, int index, unsigned int color)
{
	int t;
	int r;
	int g;
	int b;
	printf("pixelizing sprite\n");
	if (color >= NONE)
		return (s->img.adr[index]);
	else if (color < 256 * 256 * 256)
		return (color);
	t = color / (256 * 256 * 256);
	r = (color / (256 * 256) % 256) * (1 - (double)t / 256);
	g = (color / 256 % 256) * (1 - (double)t / 256);
	b = (color % 256) * (1 - (double)t / 256);
	r += (s->img.adr[index] / (256 * 256) % 256) * ((double)t / 256);
	g += (s->img.adr[index] / 256 % 256) * ((double)t / 256);
	b += (s->img.adr[index] % 256) * ((double)t / 256);
	return (r * 256 * 256 + g * 256 + b);
}

void draw_sprite(t_all *s, int loc, double dist)
{
	int index;
	int i;
	int j;
	unsigned int color;
	double size;
	printf("drawing sprite\n");
	i = 0;
	j = 0;
	size = s->window.y / dist / 2;
	loc = loc - size / 2;
	while (i < size)
	{
		printf("loc = %d, i = %d, j = %d, size = %f, s->stock[loc + i].dis = %f , dist = %f\n", loc, i, j, size, s->stock[loc + i].dis, dist);
		while ((loc + i >= 0 && loc + i < s->window.x) && (j < size && s->stock[loc + i].dis > dist))
		{
			color = 64 * floor(64 * (double)j / size) + (double)i / size * 64; //=case couleur texture
			color = s->texture.spr[color];
			index = loc + i + (s->window.y / 2 + j) * s->window.x;
			printf("index = %d, le tout ** = %d\n", index, s->window.x * s->window.y);
			if (index < s->window.x * s->window.y)
				s->img.adr[index] = pixelize_spr(s, index, color);
			j++;
		}
		i++;
		j = 0;
	}
}

void locate_sprite(t_all *s, double sprx, double spry, double sprdis)
{
	double angle;
	printf("locating sprite\n");
	sprx = (sprx - s->pos.x) / sprdis; // remet à jour les coord en fonction de la position joueur
	spry = (spry - s->pos.y) / sprdis;
	if (spry <= 0)
		angle = acos(sprx) * 180 / M_PI; // acos renvoie l'angle à partir d'un cosinus
	else
		angle = 360 - acos(sprx) * 180 / M_PI;
	angle = s->dir.angle - angle + 33;
	if (angle >= 180)
		angle -= 360;
	else if (angle <= -180)
		angle += 360;
	draw_sprite(s, angle * s->window.x / 66, sprdis);
}

void unsort_sprite(t_all *s) // range du plus loin au plus proche
{
	t_spr temp;
	int i;
	int j;

	i = 0;
	while (i < s->map.nbspr - 1)
	{
		j = i + 1;
		while (j < s->map.nbspr)
		{
			printf("distance du sprite i = %d ==> %f\n", i, s->sprite[i].dis);
			if (s->sprite[i].dis < s->sprite[j].dis) // si sprite est plus proche que sprite +1
			{
				temp = s->sprite[i];
				s->sprite[i] = s->sprite[j];
				s->sprite[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void handle_sprite(t_all *s)
{
	int i;
	double distance;
	printf("handling sprite\n");
	distance = hypot(s->dir.x, s->dir.y); // renvoie la racine carrée de la somme des carrés de ses arguments direction
	if (s->dir.y <= 0)
		s->dir.angle = acos(s->dir.x / distance) * 180 / M_PI; // acos retourne l'angle dont le cosinus est le nombre spécifié
	else
		s->dir.angle = 360 - acos(s->dir.x / distance) * 180 / M_PI;
	i = 0;
	while (i < s->map.nbspr)
	{
		s->sprite[i].dis = hypot(s->sprite[i].x - s->pos.x, s->sprite[i].y - s->pos.y); // renvoie la distance pour chaque sprite
		i++;
	}
	unsort_sprite(s);
	i = 0;
	while (i < s->map.nbspr)
	{
		locate_sprite(s, s->sprite[i].x, s->sprite[i].y, s->sprite[i].dis);
		i++;
	}
	free(s->stock);
}