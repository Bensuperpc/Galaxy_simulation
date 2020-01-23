#ifndef BLOCK_H
#define BLOCK_H
#include "vector.h"
#include "star.h"



// Classe d�finissant une zone de l'algorithme de Barnes�Hut

class Block
{

public:

	bool	as_stars;		// Pr�sence d'�toiles dans le bloc
	bool	as_children;	// Pr�sence de blocs enfants
	bool	as_parents;		// Pr�sence de blocs parents
	int		parent;			// Indice du bloc parent
	Vector	position;		// Position du bloc
	double	mass;			// Masse contenue dans le bloc (en kilogrames)
	Vector	mass_center;	// Centre de gravit� du bloc
	size_t 	nb_stars;		// Nombre d'�toiles contenues dans le block
	double	size, halfsize;	// Taille du bloc (en m�tres)

	std::variant<Star::container::iterator, std::vector<Block>> contains;
	
	Block();
	Block(const Block& block);

	void operator=(const Block& block);

	void update_mass_center_and_mass(const Star::range& stars);
	void divide(Star::range galaxy);
	void set_size(const double& size);
};

bool is_in(const Block& block, const Star& star);
void create_blocks(const double& area, Block& block, Star::range& galaxy);

#endif