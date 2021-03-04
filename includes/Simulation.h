#ifndef SIMULATION_H
#define SIMULATION_H
#include "Menu.h"
#include "Star.h"
#include "utils.h"
#include "Vector.h"
#include "Block.h"

typedef std::array<Galaxy::iterator, 2> Part;	// Typedef d�signant une partie de la galaxie

// Classe d�finissant la simulation

class Simulation
{
public:

	sf::Image						void_image;	// Image vide
	sf::Image						image;		// Image � afficher
	sf::Texture						texture;	// Texture supportant l'image
	sf::RenderWindow*				window;		// Pointeur sur la fen�tre
	uint8_t							thread_nb;	// Nombre de coeurs utilis�s par le CPU
	std::vector<std::atomic<bool>>	finished;	// Indique pour chaque thread si il a termin�
	Galaxy							galaxy;		// Galaxie
	uint32_t						nb_stars;	// Nombre d'�toiles
	Block							block;		// Blocs de l'algorithme de Barnes�Hut
	Float							area;		// Zone d'apparition des �toiles
	Float							acc_max;	// Acc�l�ration maximum
	Float							precision;	// Pr�cision de l'algorithme de Barnes�Hut
	Float							step;		// Pas de temps

									Simulation();
									Simulation(const Menu& menu, sf::RenderWindow* window, My_event& my_event);

	void							restart(const Menu& menu, sf::RenderWindow* window, My_event& my_event);
	void							center_galaxy();
	std::vector<Part>				split_galaxy();
	void							acceleration_update(const Galaxy::iterator& begin, const Galaxy::iterator& end, uint8_t thread_id);
	void							position_update(const Galaxy::iterator& begin, const Galaxy::iterator& end, uint8_t thread_id);
	bool							check_events(My_event& my_event, std::vector<std::thread>& threads);
	bool							check_events(My_event& my_event, std::thread& thread);
	void							update(My_event& my_event);
	void							draw_simulation();
	void							draw();
	void							save_image(const std::string& folder);
};

#endif