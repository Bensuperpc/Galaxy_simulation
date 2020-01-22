#include "star.h"
#include "utils.h"
#include "block.h"



// Construit une �toile

Star::Star()
{
	is_alive = false;
	previous_position = Vector(0., 0., 0.);
	position = Vector(0., 0., 0.);
	speed = Vector(0., 0., 0.);
	acceleration = Vector(0., 0., 0.);
	color = RGB(0, 0, 0);
	mass = 0.;
	density = 0.;
	index = 0;
	block_index = 0;
}



// Construit une �toile � des coordonn�es al�atoires dans la zone

Star::Star(const double& initial_speed, const double& area, const double& step, const double& galaxy_thickness)
{
	is_alive = true;
	position = create_spherical((sqrt(random_double(0., 1.)) - 0.5) * area, random_double(0., 2. * PI), PI / 2.);
	position.z = ((random_double(0., 1.) - 0.5) * (area * galaxy_thickness));
	speed = create_spherical((((area / 2.) - position.get_radius()) / (area / 2.)) * initial_speed, position.get_phi() + PI / 2., PI / 2.);
	previous_position = position - speed * step;
	acceleration = Vector(0., 0., 0.);
	color = RGB(0, 0, 0);
	mass = 0.;
	density = 0.;
	index = 0;
	block_index = 0;
}



// Construit une �toile � partir d'une autre �toile

Star::Star(const Star& star)
{
	is_alive = star.is_alive;
	previous_position = star.previous_position;
	position = star.position;
	speed = star.speed;
	acceleration = star.acceleration;
	mass = star.mass;
	density = star.density;
	color = star.color;
	index = star.index;
	block_index = star.block_index;
}



// Assignation

void Star::operator=(const Star& star)
{
	is_alive = star.is_alive;
	previous_position = star.previous_position;
	position = star.position;
	speed = star.speed;
	acceleration = star.acceleration;
	mass = star.mass;
	density = star.density;
	color = star.color;
	index = star.index;
	block_index = star.block_index;
}



// Met � jour la position

void Star::update_position(const double& step, const bool& verlet_integration)
{
	if (verlet_integration)
	{
		Vector temp = position;

		position = 2. * position - previous_position + acceleration * step * step; // Int�gration de Verlet
		previous_position = temp;
	}

	else
		position += speed * step; // M�thode d'Euler
}



// Met � jour la vitesse

void Star::update_speed(const double& step, const double& area)
{
	speed += acceleration * step;
}



// Met � jour l'acc�l�ration et la densit�

void Star::update_acceleration_and_density(const double& precision, const std::vector<Star>& galaxy, const std::vector<Block>& blocks)
{
	density = 0.;
	double max_acceleration = 0.0000000005; // Permet de limiter l'erreur due au pas de temps (� r�gler en fonction du pas de temps)

	acceleration = force_and_density_calculation(precision, *this, blocks, 0); // Pas de division par la masse de l'�toile (c.f. ligne 122)

	if (acceleration.get_radius() > max_acceleration)
		acceleration = create_spherical(max_acceleration, acceleration.get_phi(), acceleration.get_theta());
}



// Calcule la densit� et la force exerc�e sur une �toile (divis�e par la masse de l'�toile pour �viter des calculs inutiles)

Vector force_and_density_calculation(const double& precision, Star& star, const std::vector<Block>& blocks, int index)
{
	Vector force = Vector(0., 0., 0.);
	double distance = get_distance(star.position, blocks[index].mass_center);

	if (blocks[index].stars.size() == 1)
	{
		if (distance != 0.)
		{
			force += ((star.position - blocks[index].mass_center) / distance) * ( -(G * blocks[index].mass) / (distance * distance));
			star.density += 1. / (distance / LIGHT_YEAR);
		}
	}

	else if (blocks[index].stars.size() != 0)
	{
		if (blocks[index].size / distance < precision)
		{
			force += ((star.position - blocks[index].mass_center) / distance) * (-(G * blocks[index].mass) / (distance * distance));
			star.density += blocks[index].stars.size() / (distance / LIGHT_YEAR);
		}

		else
		{
			for (int i = 0; i < 8; i++)
			{
				if (blocks[blocks[index].children[i]].as_stars)
					force += force_and_density_calculation(precision, star, blocks, blocks[index].children[i]);
			}
		}
	}

	return force;
}



// Met � jour la couleur

void Star::update_color()
{
	int color_nb = density / 3.;

	if (color_nb > 255 * 2)
		color_nb = 255 * 2;

	if (color_nb < 255)
		color = RGB(0, color_nb, 255);

	else
		color = RGB(color_nb - 255, 255, 255);
}



// Initialise la galaxie

void initialize_galaxy(std::vector<Star>& galaxy, const int& stars_number, const double& area, const double& initial_speed, const double& step, const bool& is_black_hole, const double& black_hole_mass, const double& galaxy_thickness)
{
	for (int i = 0; i <= stars_number * 0.764; i++)
	{
		galaxy.push_back(Star(initial_speed, area, step, galaxy_thickness));
		galaxy.back().mass = random_double(0.08, 0.45) * SOLAR_MASS;
		galaxy.back().color = RGB(255, 10, 10);
		galaxy.back().index = galaxy.size() - 1;
	}

	for (int i = 0; i <= stars_number * 0.121; i++)
	{
		galaxy.push_back(Star(initial_speed, area, step, galaxy_thickness));
		galaxy.back().mass = random_double(0.45, 0.8) * SOLAR_MASS;
		galaxy.back().color = RGB(255, 127, 10);
		galaxy.back().index = galaxy.size() - 1;
	}

	for (int i = 0; i <= stars_number * 0.076; i++)
	{
		galaxy.push_back(Star(initial_speed, area, step, galaxy_thickness));
		galaxy.back().mass = random_double(0.8, 1.04) * SOLAR_MASS;
		galaxy.back().color = RGB(255, 255, 10);
		galaxy.back().index = galaxy.size() - 1;
	}

	for (int i = 0; i <= stars_number * 0.030; i++)
	{
		galaxy.push_back(Star(initial_speed, area, step, galaxy_thickness));
		galaxy.back().mass = random_double(1.04, 1.4) * SOLAR_MASS;
		galaxy.back().color = RGB(255, 255, 127);
		galaxy.back().index = galaxy.size() - 1;
	}

	for (int i = 0; i <= stars_number * 0.006; i++)
	{
		galaxy.push_back(Star(initial_speed, area, step, galaxy_thickness));
		galaxy.back().mass = random_double(1.4, 2.1) * SOLAR_MASS;
		galaxy.back().color = RGB(255, 255, 255);
		galaxy.back().index = galaxy.size() - 1;
	}

	for (int i = 0; i <= stars_number * 0.0013; i++)
	{
		galaxy.push_back(Star(initial_speed, area, step, galaxy_thickness));
		galaxy.back().mass = random_double(2.1, 16) * SOLAR_MASS;
		galaxy.back().color = RGB(50, 255, 255);
		galaxy.back().index = galaxy.size() - 1;
	}

	if (is_black_hole)
	{
		galaxy.push_back(Star(initial_speed, area, step, galaxy_thickness));
		galaxy.back().position = Vector(0., 0., 0.);
		galaxy.back().speed = Vector(0., 0., 0.);
		galaxy.back().mass = black_hole_mass;
		galaxy.back().color = RGB(0, 0, 0);
		galaxy.back().index = galaxy.size() - 1;
	}
}