#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <sstream>

using namespace sf;
using namespace std;

int main()
{
	int vertexNum = 0;			//starting console
	cout << "Enter the number of vertices of the shape you want:" << endl;
	cin >> vertexNum;



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
	text2.setString("Make your shape vertices with clicks (in the same order as if you're writing) and then click away!");
	text2.setCharacterSize(15);
	text2.setFillColor(sf::Color::Red);
	text2.setPosition(0, 30);

	bool start = false;
	int i = 0;  //click counter
	int j = 0; //corner counter
	int rngNum = 0;
	int rngNum2 = 0;
	int previousRNG = 0;
	sf::Event event;
	std::vector<sf::Vector2f> vertices;
	std::vector<sf::Vector2f> generatedPoints;   //not needed

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


						cout << "Vertex " << j + 1 << ": (" << vertices[j].x << ", " << vertices[j].y << ")" << endl;   //vertex console output
						j += 1;

						if (vertices.size() == vertexNum)				//draws vertices
						{
							for (i = 0; i < vertexNum; i++)
							{
								corner.setPosition(vertices[i]);
								window.draw(corner);
							}
							start = true;
						}
					}
					else
					{
						if (vertices.size() == 3)		//triangle
						{
							for (j = 0; j < 200; j++)
							{
								if (i == vertexNum) dot.setPosition(mousePos);				// so dot picks up the fourth click and not (0,0)
								i += 1;
								rngNum = rand() % vertexNum;
								sf::Vector2f newPos = (vertices[rngNum] + dot.getPosition()) / 2.f;

								generatedPoints.push_back(newPos); //not needed
								dot.setPosition(newPos);
								window.draw(dot);
							}
						}
						else if (vertices.size() == 4)	//square
						{
							for (j = 0; j < 200; j++)							// square      0 1
																				//			   2 3
							{
								if (i == vertexNum) dot.setPosition(mousePos);				// so dot picks up the fifth click and not (0,0)
								i += 1;
								previousRNG = rngNum;
								rngNum = rand() % vertexNum;
								rngNum2 = rand();

								if (previousRNG == 3 && rngNum == 0)
								{
									if (rngNum2 % 2 == 0) rngNum += 1;
									else rngNum += 2;
								}
								else if (previousRNG == 2 && rngNum == 1)
								{
									if (rngNum2 % 2 == 0) rngNum += 2;
									else rngNum -= 1;
								}
								else if (previousRNG == 1 && rngNum == 2)
								{
									if (rngNum2 % 2 == 0) rngNum -= 2;
									else rngNum += 1;
								}
								else if (previousRNG == 0 && rngNum == 3)
								{
									if (rngNum2 % 2 == 0) rngNum -= 1;
									else rngNum -= 2;
								}

								sf::Vector2f newPos = (vertices[rngNum] + dot.getPosition()) / 2.f;
								generatedPoints.push_back(newPos); //not needed
								dot.setPosition(newPos);
								window.draw(dot);
							}
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