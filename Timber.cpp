#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <sstream>

using namespace sf;
using namespace std;

int main()
{

	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Chaos Game", Style::Default);

	sf::Font font;										//title and directions
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Chaos Game");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	sf::Text text2;
	text2.setFont(font);
	text2.setString("Click 3 times to make a triangle and then click abunch");
	text2.setCharacterSize(15);
	text2.setFillColor(sf::Color::Red);
	text2.setPosition(0, 30);

	bool start = false;						//variables
	int i = 0;  //click counter
	int j = 0; //corner counter
	int rngNum = 0;
	sf::Event event;
	std::vector<sf::Vector2f> vertices;
	std::vector<sf::Vector2f> generatedPoints;

	sf::CircleShape dot(2);
	dot.setFillColor(sf::Color::Green);
	sf::CircleShape corner(5);
	corner.setFillColor(sf::Color::Red);
	

	while (window.isOpen())
	{
		if (!start)					//starting display
		{
			window.clear();
			window.draw(text);
			window.draw(text2);
			window.display();
		}

		while (window.pollEvent(event))
		{

			switch (event.type)
			{

			case sf::Event::Closed:					//exit event
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					if (!start)
					{
						vertices.push_back(mousePos);			// draws vertices
						

						cout << "Vertex " << j + 1 << ": (" << vertices[j].x << ", " << vertices[j].y << ")" << endl;
						j += 1;

						if (vertices.size() == 3)
						{
							for (i = 0; i < 3; i++)
							{
								corner.setPosition(vertices[i]);
								window.draw(corner);  // ******* need to output vertices to console  *******
							}
							start = true;
						}
					}
					else
					{
						for (j = 0; j < 200; j++)
						{
							if (i == 3) dot.setPosition(mousePos);				// draws inside dots, lots of instances per click to make it fast, i value?
							i += 1;
							rngNum = rand() % 3;
							sf::Vector2f newPos = (vertices[rngNum] + dot.getPosition()) / 2.f;
							generatedPoints.push_back(newPos); //not needed
							dot.setPosition(newPos);
							window.draw(dot);
						}
					}
				}
				break;

			default:
				break;
			}
			window.display();
		}
	}
	return 0;
}