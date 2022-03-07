#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
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

const int size = 120;

std::string operators[] = { 
	// c++
 "if", "else", "switch", "case", "default", "break",  // 6
 "continue", "try", "goto", "catch", "const", "int", "long", "float", "double", "bool", // 16
 "for", "while", "array", "void", "include", "cmath", "cash", "programming", "pow", // 24
 "sizeof", "sqrt", "enum", "delete", "cmath", // 30
	// python
 "python", "print", "type", "int", "float", "class", "bool", "elif", "while", "input",
 "True", "const", "def", "range", "raise", "exeption", "except", "next", "list", "exit",
 "cmp", "import", "return", "if", "match", "zip", "remove", "insert", "nums", "plot" //60
	// javascript
 "alert", "forEach", "eval", "uneval", "isNan", "isFinite", "parseFloat", "parseInt", 
 "decodeURI", "decodeURIComponent", "encodeURI", "escape", "unescape", "object", "function",
 "boolean", "symbol", "error", "EvalError", "TypeError", "RangeError", "number", "math", "string",
 "date", "RegExp", "Array", "Map", "Set", "WeakMap", "ArrayBuffer", // 90
	// html
 "html", "head", "body", "title", "bgcolor", "link", "u", "pre", "vlink", "h1", "b", "i", "em",
 "tt", "cite", "font", "blockquote", "ol", "li", "div align", "img","td", "tr", "table", "frameset",
 "form", "select name", "textarea name", "input type", "strong" // 120
};

enum eLanguage {
	c_lang, py_lang, js_lang, html_lang
} language;

int getRandomOperator(enum eLanguage language)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int flag = 0;
	switch (language)
	{
	case c_lang:
		flag = gen() % 30;
		break;
	case py_lang:
		flag = gen() % 30 + 30;
		break;
	case js_lang:
		flag = gen() % 30 + 60;
		break;
	case html_lang:
		flag = gen() % 30 + 90;
		break;
	}
	return flag;
}

void stamina()
{
	// obsiously, gendering the window function
	RenderWindow window(VideoMode(700, 200), "IT-stamina");

	// figures angles sharpness 
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	// top text output (about IT-stamina project)
	Font font;
	if (!font.loadFromFile("edf7f-eirik-raude.ttf"))
		exit(0);
	Text text1;
	text1.setFont(font);
	text1.setString("This is IT-stamina! Train your code-typing skills with us and make your \nown records!");
	text1.setCharacterSize(22);
	text1.setFillColor(Color(0, 0, 0));
	text1.move(26, 25);

	// top text 
	Text choose_language;
	choose_language.setFont(font);
	choose_language.setString("Choose your programming language!");
	choose_language.setCharacterSize(30);
	choose_language.setFillColor(Color(255, 255, 255));
	choose_language.move(145, 15);
	choose_language.setOutlineThickness(1.f);
	choose_language.setOutlineColor(Color::Black);

	// c++
	Text c;
	c.setFont(font);
	c.setString("c++");
	c.setCharacterSize(30);
	c.setFillColor(Color(255, 255, 255));
	c.move(110, 65);
	c.setOutlineThickness(1.f);
	c.setOutlineColor(Color::Black);

	// rectangle c++
	RectangleShape rectanglec;
	rectanglec.setSize(Vector2f(40.f, 32.f));
	rectanglec.setOutlineThickness(2.f);
	rectanglec.setOutlineColor(Color::Black);
	rectanglec.setPosition(Vector2f(110.f, 70.f));

	// python
	Text py;
	py.setFont(font);
	py.setString("python");
	py.setCharacterSize(30);
	py.setFillColor(Color(255, 255, 255));
	py.move(110, 130);
	py.setOutlineThickness(1.f);
	py.setOutlineColor(Color::Black);

	// rectangle py
	RectangleShape rectanglepy;
	rectanglepy.setSize(Vector2f(80.f, 30.f));
	rectanglepy.setOutlineThickness(2.f);
	rectanglepy.setOutlineColor(Color::Black);
	rectanglepy.setPosition(Vector2f(110.f, 133.f));

	// java script
	Text js;
	js.setFont(font);
	js.setString("JavaScript");
	js.setCharacterSize(30);
	js.setFillColor(Color(255, 255, 255));
	js.move(520, 65);
	js.setOutlineThickness(1.f);
	js.setOutlineColor(Color::Black);

	//rectangle js
	RectangleShape rectanglejs;
	rectanglejs.setSize(Vector2f(125.f, 32.f));
	rectanglejs.setOutlineThickness(2.f);
	rectanglejs.setOutlineColor(Color::Black);
	rectanglejs.setPosition(Vector2f(520.f, 65.f));

	// html
	Text html;
	html.setFont(font);
	html.setString("HTML 5.0");
	html.setCharacterSize(30);
	html.setFillColor(Color(255, 255, 255));
	html.move(530, 130);
	html.setOutlineThickness(1.f);
	html.setOutlineColor(Color::Black);

	//rectangle html
	RectangleShape rectanglehtml;
	rectanglehtml.setSize(Vector2f(120.f, 32.f));
	rectanglehtml.setOutlineThickness(2.f);
	rectanglehtml.setOutlineColor(Color::Black);
	rectanglehtml.setPosition(Vector2f(520.f, 130.f));

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

	// creating texture
	Texture mainpic;
	mainpic.loadFromFile("C:\\programming\\igorolhovatiy\\igorolhovatiy\\choose.png");
	Sprite sprite(mainpic);

	// important variables
	bool same_elements = false;
	bool choosen = false;
	int AmountSymbols = 0;

	// coding text from the app OUTPUT
	Text operatorstxt;
	operatorstxt.setFont(font);
	int AmountOperators = 3;
	std::string strwords;
	int flag = 0;
	for (size_t i = 0; i < 4; i++)
	{
		std::cout << language << std::endl;
		flag = getRandomOperator(language);
		std::cout << operators[flag] << " " << flag << std::endl;
		strwords = strwords + operators[flag] + ' ';
	}
	operatorstxt.setString(strwords);
	operatorstxt.setCharacterSize(30);
	operatorstxt.setFillColor(Color(0, 0, 0));
	operatorstxt.move(40, 104);

	//main cycle
	while (window.isOpen())
	{
		// game exit
		Event event;
		while (window.pollEvent(event))
		{
			// closing
			if (event.type == Event::Closed)
				window.close();

			// getting fixed size
			if (event.type == Event::Resized)
			{
				std::cout << "trying to resize window" << std::endl;
				window.setSize(Vector2u(700, 200));
			}

			// help
			rectanglehelp.setOutlineColor(Color::Black);
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (rectanglehelp.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
				{
					rectanglehelp.setOutlineColor(Color::Red);
					ShellExecuteW(0, 0, L"www.google.com", NULL, NULL, SW_SHOW);
				}
			}
		}

		if (!choosen)
		{
			// c++
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (rectanglec.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
				{
					// rectanglec.setOutlineColor(Color::Red);
					language = c_lang;
					choosen = true;
					Sleep(500);
				}
				if (rectanglepy.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
				{
					// rectanglepy.setOutlineColor(Color::Red);
					language = py_lang;
					choosen = true;
					Sleep(500);
				}
				if (rectanglejs.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
				{
					// rectanglejs.setOutlineColor(Color::Red);
					language = js_lang;
					choosen = true;
					Sleep(500);
				}
				if (rectanglehtml.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
				{
					// rectanglehtml.setOutlineColor(Color::Red);
					language = html_lang;
					choosen = true;
					Sleep(500);
				}
			}
		}
		else if (choosen)
		{
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
						if (same_elements)
						{
							strwords.insert(strwords.begin() + 1, strwords[0]);
						}
						same_elements = false;

						if (strwords[0] == strwords[1])
							same_elements = true;

						// deleting the entered symbol
						strwords.erase(strwords.begin());
						operatorstxt.setString(strwords);

						std::cout << ".......AFTER ERASING..........." << std::endl;
						std::cout << "letter_entered " << letter_entered << std::endl;
						std::cout << "last_enterd " << last_enterd << std::endl;
						std::cout << "string " << strwords << std::endl;
						std::cout << ".................." << std::endl;

						// increasing the amount of symbols
						if (timing > 0)
						{
							AmountSymbols++;
							std::cout << "Amount Symbols:  " << AmountSymbols << std::endl;
						}

						// adding new word if the last is done
						if (strwords[1] == ' ')
						{
							strwords = strwords + operators[getRandomOperator(language)] + ' ';
							operatorstxt.setString(strwords);
							words_score++;
						}

						if (!same_elements)
							last_enterd = letter_entered;
						else
						{
							//letter_entered = "trash";
							last_enterd = "trash";
							//strwords.insert(strwords.begin()+1, strwords[0]);
							same_elements = false;
						}
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
		}

		// vertex line coursor (behind the cycle)
		Vertex line_without_thickness[] =
		{
			Vertex(Vector2f(36.f, 110.f)),
			Vertex(Vector2f(36.f, 145.f))
		};
		line_without_thickness->color = Color::Black;

		if (!choosen)
		{
			// first window
			window.draw(sprite);
			window.draw(choose_language);
			// window.draw(rectanglec);
			window.draw(c);
			// window.draw(rectanglepy);
			window.draw(py);
			// window.draw(rectanglejs);
			window.draw(js);
			// window.draw(rectanglehtml);
			window.draw(html);
			// window.draw(rectanglehelp);
			window.draw(help);
		}
		else
		{
			if (timing > 0)
			{
				// second main window
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
				//third result window
				window.draw(result);
				window.draw(speed);
			}
		}

		window.display();
	}
}

int main()
{	
	stamina();
	return 0;
}
