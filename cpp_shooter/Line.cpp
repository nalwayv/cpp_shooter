#include <cmath>
#include "Line.h"

using sf::RenderWindow;
using sf::Color;
using sf::Vertex;
using std::sqrtf;

namespace game {
	void Line::draw(RenderWindow& window, Color color)
	{
		const size_t SIZE = 2;
		Vertex points[SIZE];

		points[0].position = start;
		points[0].color = color;
		points[1].position = end;
		points[1].color = color;

		window.draw(points, SIZE, sf::LinesStrip);
	}
}
