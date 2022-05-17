HA:
    - Vokabelwiederholung: 
        AB. S. 74-75
    - AB. S. 76, 77, 78
    - Zusatzblatt Passiv (Moodle)
    - Vokabelheft kaufen 
    

...wenn man vom Teufel spricht

Idiome vom 16.05.:
    - den Bund fürs Leben schließen
    - auf gut Deutsch gesagt
    - auf de.m falschen Dampfer sein
    - im Eimer sein
    (müde / erledigt / erschöpft)
    - wie ein Elefant im Porzellanladen
    (ungeschickt / tollpatschig) 
    mit: sich bewegen / sich verhalten / aufteten / sein )HA:
    - Vokabelwiederholung: 
        AB. S. 74-75
    - AB. S. 76, 77, 78
    - Zusatzblatt Passiv (Moodle)
    - Vokabelheft kaufen 
    

...wenn man vom Teufel spricht

Idiome vom 16.05.:
    - den Bund fürs Leben schließen
    - auf gut Deutsch gesagt
    - auf de.m falschen Dampfer sein
    - im Eimer sein
    (müde / erledigt / erschöpft)
    - wie ein Elefant im Porzellanladen
    (ungeschickt / tollpatschig) 
    mit: sich bewegen / sich verhalten / aufteten / sein )#include "cub3d.h"

void free_cub3d(t_cub3d *cub)
{
	int i;

	// free img
	i = 0;
	while (i < MAX)
	{
		if (cub->img[i])
		{
			if(cub->img[i]->path_tex)
				free(cub->img[i]->path_tex);
			free(cub->img[i]);
		}
		i++;
	}
	i = 0;
	while (i < cub->map.nolines)
	{
		if (cub->map.map[i])
			free(cub->map.map[i]);
		i++;
	}
	if (cub->map.map)
		free(cub->map.map);
}
