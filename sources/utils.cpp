#include "utils.h"
#include "block.h"



// Donne un int al�atoire entre deux bornes

int random_int(const int& min, const int& max)
{
	return rand() % (max - min) + min;
}



// Donne un double al�atoire entre deux bornes

double random_double(const double& min, const double& max)
{
	return (double(rand()) / double(RAND_MAX)) * (max - min) + min;
}



// Affiche les �toiles de la galaxie

void draw_stars(std::vector<Star>& galaxy, const Vector& mass_center, const double& area, const double& zoom, const View& view)
{
	double x;
	double y;
	double z;
	Vector screen_position;

	Vector camera = Vector(0., area / 2., area / 2.);

	for (int i = 0; i < galaxy.size(); i++)
	{
		if (galaxy[i].is_alive)
		{
			if (view == default_view)
			{
				x = (galaxy[i].position - mass_center).x;
				y = (galaxy[i].position - mass_center).y / 3. - (galaxy[i].position - mass_center).z / 1.5;

				screen_position = create_spherical(Vector(x, y, 0.).get_radius() / (get_distance(galaxy[i].position, camera)), Vector(x, y, 0.).get_phi(), Vector(x, y, 0.).get_theta());

				x = screen_position.x * zoom + WIDTH / 2.;
				y = screen_position.y * zoom + HEIGHT / 2.;
			}

			if (view == xy)
			{
				x = (galaxy[i].position - mass_center).x / (area / zoom) + WIDTH / 2.;
				y = (galaxy[i].position - mass_center).y / (area / zoom) + HEIGHT / 2.;
			}

			if (view == xz)
			{
				x = (galaxy[i].position - mass_center).x / (area / zoom) + WIDTH / 2.;
				y = (galaxy[i].position - mass_center).z / (area / zoom) + HEIGHT / 2.;
			}

			if (view == yz)
			{
				x = (galaxy[i].position - mass_center).y / (area / zoom) + WIDTH / 2.;
				y = (galaxy[i].position - mass_center).z / (area / zoom) + HEIGHT / 2.;
			}

			SDL_SetRenderDrawColor(renderer, GetRValue(galaxy[i].color), GetGValue(galaxy[i].color), GetBValue(galaxy[i].color), SDL_ALPHA_OPAQUE);

			SDL_RenderDrawPoint(renderer, x - 1, y);
			SDL_RenderDrawPoint(renderer, x, y - 1);
			SDL_RenderDrawPoint(renderer, x, y);
			SDL_RenderDrawPoint(renderer, x, y + 1);
			SDL_RenderDrawPoint(renderer, x + 1, y);

			SDL_SetRenderDrawColor(renderer, GetRValue(galaxy[i].color), GetGValue(galaxy[i].color), GetBValue(galaxy[i].color), SDL_ALPHA_OPAQUE / 2.);

			SDL_RenderDrawPoint(renderer, x - 1, y - 1);
			SDL_RenderDrawPoint(renderer, x - 1, y + 1);
			SDL_RenderDrawPoint(renderer, x + 1, y - 1);
			SDL_RenderDrawPoint(renderer, x + 1, y + 1);
		}
	}
}



// Affiche les blocs (ne fonctionne pas en vue "delault_view")

void draw_blocks(const std::vector<Block>& blocks, const Vector& mass_center, const double& area, const double& zoom, const View& view)
{
	if (view == default_view)
		return;

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

	int x;
	int y;
	int block_size;

	for (int i = 0; i < blocks.size(); i++)
	{
		if (view == default_view)
		{
			x = ((blocks[i].position - mass_center).x - blocks[i].size / 2.) / (area / zoom) + WIDTH / 2.;
			y = (((blocks[i].position - mass_center).y - blocks[i].size / 2.) / (area / zoom)) / 2. - (((blocks[i].position - mass_center).z - blocks[i].size / 2.) / (area / zoom)) / 2. + HEIGHT / 2.;
		}

		if (view == xy)
		{
			x = ((blocks[i].position - mass_center).x - blocks[i].size / 2.) / (area / zoom) + WIDTH / 2.;
			y = ((blocks[i].position - mass_center).y - blocks[i].size / 2.) / (area / zoom) + HEIGHT / 2.;
		}

		if (view == xz)
		{
			x = ((blocks[i].position - mass_center).x - blocks[i].size / 2.) / (area / zoom) + WIDTH / 2.;
			y = ((blocks[i].position - mass_center).z - blocks[i].size / 2.) / (area / zoom) + HEIGHT / 2.;
		}

		if (view == yz)
		{
			x = ((blocks[i].position - mass_center).y - blocks[i].size / 2.) / (area / zoom) + WIDTH / 2.;
			y = ((blocks[i].position - mass_center).z - blocks[i].size / 2.) / (area / zoom) + HEIGHT / 2.;
		}

		block_size = blocks[i].size / (area / zoom);

		for (int j = 0; j < block_size; j++)
		{
			SDL_RenderDrawPoint(renderer, x, y + j);
			SDL_RenderDrawPoint(renderer, x + block_size, y + j);
		}

		for (int j = 0; j < block_size; j++)
		{
			SDL_RenderDrawPoint(renderer, x + j, y);
			SDL_RenderDrawPoint(renderer, x + j, y + block_size);
		}
	}
}