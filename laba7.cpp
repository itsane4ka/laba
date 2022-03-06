#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <chrono>
#include <time.h>
#include <array>
#include <random>
#include <sstream>
#include <thread>
#include <algorithm>
#include <functional>
#include <windows.h>
#include <ShellApi.h>

using namespace sf;

const int size = 30;
 
std::string operators[] = { "bool", "bool", "bool", "bool", "bool", "bool",  // 6
 "continue", "try", "bool", "catch", "bool", "int", "bool", "bool", "bool", "bool", // 16
 "bool", "bool", "array", "void", "bool", "bool", "cash", "programming", "pow", // 24
 "bool", "bool", "bool", "bool", "bool" // 30
};

/*
std::string operators[] = { "if", "else", "switch", "case", "default", "break",  // 6
 "continue", "try", "goto", "catch", "const", "int", "long", "float", "double", "bool", // 16
 "for", "while", "array", "void", "include", "cmath", "cash", "programming", "pow", // 24
 "sizeof", "sqrt", "enum", "delete", "cmath" // 30
};
*/

enum eLetter {
	a, b, c, d, e, f, g, h, i, j, k, l,
	m, n, o, p, q, r, s, t, u, v, w, x, y, z, SPACE
} dir;

int getRandomOperator()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 29);

	return (dist(gen));
}

int main()
{	
	// obsiously, gendering the window function
	RenderWindow window(VideoMode(700, 200), "IT-stamina");

	// figures angles sharpness 
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	// top text output (about IT-stamina project)
	Font font;
	if (!font.loadFromFile("edf7f-eirik-raude.ttf"))
		return 0;
	Text text1;
	text1.setFont(font);
	text1.setString("This is IT-stamina! Train your code-typing skills with us and make your \nown records!");
	text1.setCharacterSize(22);
	text1.setFillColor(Color(0, 0, 0));
	text1.move(26, 25);


	// timing bottom text
	Text maintime;
	maintime.setFont(font);
	maintime.setString("Timing: 60");
	maintime.setCharacterSize(22);
	maintime.setFillColor(Color(0, 0, 0));
	maintime.move(545, 160);

	// score bottom text
	int words_score = 0;
	Text score;
	score.setFont(font);
	score.setString("Score: 0");
	score.setCharacterSize(22);
	score.setFillColor(Color(0, 0, 0));
	score.move(27, 160);

	// help bottom text
	Text help;
	help.setFont(font);
	help.setString("Help?");
	help.setCharacterSize(24);
	help.setFillColor(Color(0, 0, 0));
	help.move(310, 160);
	help.setStyle(Text::Underlined);

	// rectangle help
	RectangleShape rectanglehelp;
	rectanglehelp.setSize(Vector2f(56.f, 24.f));
	rectanglehelp.setOutlineThickness(2.f);
	rectanglehelp.setOutlineColor(Color::Black);
	rectanglehelp.setPosition(Vector2f(307.f, 165.f)); 

	// score bottom text
	Text result;
	result.setFont(font);
	result.setString("Score: ");
	result.setCharacterSize(40);
	result.setFillColor(Color::Red);
	result.move(50, 70);

	// speed bottom text
	Text speed;
	speed.setFont(font);
	speed.setString("Speed: ");
	speed.setCharacterSize(40);
	speed.setFillColor(Color::Red);
	speed.move(50, 120);

	// game timing (real amount)
	Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;
	int leftTime = 60;
	int timing = 60;

	// rectangle render
	ConvexShape convex;
	window.draw(convex);
	RectangleShape rectangle(Vector2f(650.f, 50.f));
	rectangle.move(25, 100);
	rectangle.setFillColor(Color(255, 255, 255));
	rectangle.setOutlineThickness(2.f);
	rectangle.setOutlineColor(Color(209, 224, 255));

	// getting text from the app INPUT
	std::string letter_entered;
	std::string last_enterd = "stop";

	// coding text from the app OUTPUT
	Text operatorstxt;
	operatorstxt.setFont(font);
	int AmountOperators = 3;
	std::string strwords;
	int flag = 0;
	for (size_t i = 0; i < 4; i++)
	{
		flag = getRandomOperator();
		std::cout << operators[flag] << " " << flag << std::endl;
		strwords = strwords + operators[flag] + ' ';
	}
	operatorstxt.setString(strwords);
	operatorstxt.setCharacterSize(30);
	operatorstxt.setFillColor(Color(0, 0, 0));
	operatorstxt.move(40, 104);

	// 
	bool same_elements = false;
	int AmountSymbols = 0;

	//main cycle
	while (window.isOpen())
	{
		// game exit
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		// help
		rectanglehelp.setOutlineColor(Color::Black);
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (rectanglehelp.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y})) )
			{
				rectanglehelp.setOutlineColor(Color::Red);
				ShellExecuteW(0, 0, L"www.google.com", NULL, NULL, SW_SHOW);
			}
		}

		// getting text + check if it is a letter/number + main func
		window.setKeyRepeatEnabled(false);
		if (event.type == Event::TextEntered)
		{
			if (event.text.unicode << 128)
			{
				std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << " !! " << last_enterd << std::endl;
				letter_entered = static_cast<char>(event.text.unicode);

				if (letter_entered != last_enterd && strwords[0] == letter_entered)
				{
					same_elements = false;

					if (strwords[0] == strwords[1])
						same_elements = true;

					// deleting the entered symbol
					strwords.erase(strwords.begin());
					operatorstxt.setString(strwords);

					// increasing the amount of symbols
					if (timing > 0)
					{
						AmountSymbols++;
						std::cout << "SSSSSSSSSSSSSSSSSs    " << AmountSymbols << std::endl;
					}
					
					// adding new word if the last is done
					if (strwords[1] == ' ')
					{
						strwords = strwords + operators[getRandomOperator()] + ' ';
						operatorstxt.setString(strwords);
						words_score++;
					}
		
					if (!same_elements)
						last_enterd = letter_entered;
					else
						last_enterd = "trash";
				}
			}
		}

		// getting correct time
		float time = clock.getElapsedTime().asMicroseconds();
		gameTime = gameTimeClock.getElapsedTime().asSeconds();
		timing = leftTime - gameTime;

		//convetring int to string and adding real timing
		std::string s1 = std::to_string(timing);
		maintime.setString("Timing: " + s1);


		//convetring int to string and adding real score
		std::string s2 = std::to_string(words_score);
		std::string s3 = std::to_string(AmountSymbols);
		score.setString("Score: " + s2);
		result.setString("Score: " + s2);
		speed.setString("Speed: " + s3);
		
		// view all text + pic output
		window.clear(Color(222, 202, 245, 0));

		// vertex line coursor
		Vertex line_without_thickness[] =
		{
			Vertex(Vector2f(36.f, 110.f)),
			Vertex(Vector2f(36.f, 145.f))
		};
		line_without_thickness->color = Color::Black;
		
		if (timing > 0)
		{
			window.draw(rectangle);
			window.draw(rectanglehelp);
			if (timing % 2 == 0)
				window.draw(line_without_thickness, 2, Lines);
			window.draw(text1);
			window.draw(maintime);
			window.draw(operatorstxt);
			window.draw(score);
			window.draw(help);
		}
		else
		{
			window.draw(result);
			window.draw(speed);
		}

		window.display();
	}
	return 0;
}
