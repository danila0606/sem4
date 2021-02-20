#include <cmath>
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

#define WINDOW_LENGHT 1920
#define WINDOW_HEIGHT 1080

#define STICK_LENGHT 12
#define STICK_HEIGHT 2

#define STEP_X 20
#define STEP_Y 20

struct Charge {

	Charge(int size,  float value, float x, float y) :
		x_(x), y_(y), value_(value), circle_ (sf::CircleShape(size)) {

		if (value > 0) {
			circle_.setFillColor({ 255, 0, 0 }); //red
		}
		else {
			circle_.setFillColor({ 0,51,255 }); // blue
		}

		circle_.setPosition(x_, y_);
	};

	float x_, y_;
	float value_;
	sf::CircleShape circle_;

	void Draw(sf::RenderWindow& window);
};

struct Stick {

	Stick(float angle, float x, float y) :
		x_(x), y_(y), angle_(angle){

		rect_ = sf::RectangleShape(sf::Vector2f(lenght_, height));
		rect_.setFillColor({ 255,255,255 });

		rect_.setOrigin({ lenght_ / 2, height / 2 });
		rect_.setPosition(x_, y_);
		rect_.setRotation(angle_ * 180/3.1415);
	};

	float x_, y_;
	float lenght_ = STICK_LENGHT, height = STICK_HEIGHT;
	float angle_;

	sf::RectangleShape rect_;

	void Draw(sf::RenderWindow& window);
};

void Charge::Draw(sf::RenderWindow& window) {

	window.draw(circle_);
}

void Stick::Draw(sf::RenderWindow& window) {

	window.draw(rect_);
}


std::vector<Stick> FieldCalculation(const std::vector<Charge>& charges) {

	std::vector<Stick> rects;

	for (int i = 0; i < WINDOW_LENGHT; i += STEP_X) {

		for (int j = 0; j < WINDOW_HEIGHT; j += STEP_Y) {
			
			float modul;
			float x, y;
			
			sf::Vector2f Eij(0, 0);

			for (const auto& elem : charges) {
				
				x = i - elem.x_;
				y = j - elem.y_;

				modul = elem.value_ /(std::pow((x * x + y * y), 1.5));
				sf::Vector2f Eij_elem( x * modul, y * modul );
		
				Eij += Eij_elem;
			}

			Stick stick(std::atan2(Eij.y,  Eij.x), i, j);
			rects.push_back(stick);
		}
	}

	return rects;
}

int main()
{
	std::vector<Charge> charges;

	Charge ch_plus1(5,10000,WINDOW_LENGHT / 3, WINDOW_HEIGHT / 2);
	Charge ch_minus1(5,-10000,WINDOW_LENGHT * 2 / 3, WINDOW_HEIGHT / 2);
	Charge ch_minus2(5,-10000,WINDOW_LENGHT / 5, WINDOW_HEIGHT / 4);
	Charge ch_minus3(5,-10000,WINDOW_LENGHT * 3 / 5, WINDOW_HEIGHT * 3 / 4);
    
	charges.push_back(ch_plus1);
	charges.push_back(ch_minus1);
	charges.push_back(ch_minus2);
	charges.push_back(ch_minus3);

	auto sticks = FieldCalculation(charges);

	sf::RenderWindow window(sf::VideoMode(WINDOW_LENGHT, WINDOW_HEIGHT), "CHARGES");

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (auto& elem : charges) {
			elem.Draw(window);
		}
		for (auto& elem : sticks) {
			elem.Draw(window);
		}

		window.display();
	}
	return 0;
}
