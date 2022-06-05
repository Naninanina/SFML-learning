#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"

using namespace sf;

class Player {
public:
	float x, y, w, h, dx, dy, speed = 0; //координаты игрока x и у, высота, ширина, ускоре (по х и по у), сама скорость
	int dir = 0; //направление (direction) движения игрока
	String File; //файл с расширением
	Image image; //сфмл изображение
	Texture texture; //сфмл текстура
	Sprite sprite; //сфмл спрайт
	Player(String F, int X, int Y, float W, float H) { //Конструктор с параметрами (формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координаты х и у, ширину высотку спрайта
		File = F; //имя файла+расширение
		w = W; h = H; //высота и ширина
		image.loadFromFile("../img/" + File); //запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта
		texture.loadFromImage(image); //закидываем наше изображение в текстуру
		sprite.setTexture(texture); //заливаем спрайт текстурой
		x = X; y = Y; //координата появления спрайта
		sprite.setTextureRect(IntRect(w, h, w, w)); //Задаем спрайту один прямоуголььник для вывода одной шаути, а кучу шаути-герлз. IntRect — приведение типов
	}
	void update(float time) //функция "оживления" объекта класса. update — обновление, принимает в себя время SFML, вследствие чего работает бесконечно, давая персонажу движение
	{
		switch (dir) //реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 0: dx = speed; dy = 0; break; //по иксу задаем положительную скорость, по игреку зануляем. получается, что персонаж идет только вправо
		case 1: dx = -speed; dy = 0; break; //по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет влево
		case 2: dx = 0; dy = speed; break; //по иксу зануляем, по игреку задаем положительную скорость. получается, что персонаж идет вниз
		case 3: dx = 0; dy = -speed; break; //по иксу зануляем, по игреку задаем отрицательную скорость
		}
		x += dx * time;
		y += dy * time;

		speed = 0; //зануляем скорость, чтобы персонаж остановился. можно не удалять, тогда персонаж будет постоянно двигаться в ту сторону, что мы ему указали. получится что-то вроде змейки
		sprite.setPosition(x, y); //вывод спрайта в позиции x y
	}
};

int main()
{
	RenderWindow window(VideoMode(640, 400), "☺ya hochu snegom stat'☺");

	Image map_image; //объект изображения для карты
	map_image.loadFromFile("../img/map_2.png"); //загружаем файл для карты
	Texture map; //текстура карты
	map.loadFromImage(map_image); //добавляем в текстуру картинку
	Sprite s_map; //создаем спрайт для карты
	s_map.setTexture(map); //заливаем спрайт текстурой

	Player p("character.png", 50, 25, 68.0, 72.0);
	Player cat("character_2.png", 50, 25, 160.0, 160.0);

	float CurrentFrame = 0;
	float CurrentFrameCat = 0;
	Clock clock; //создаем переменную времени, т.е. привязка ко времени (а не загруженности/мощности процессора)

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/800;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if ((Keyboard::isKeyPressed(Keyboard::A))) {
			p.dir = 1; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(68 * int(CurrentFrame), 72, 68, 72));
		} 
		if ((Keyboard::isKeyPressed(Keyboard::D))) {
			p.dir = 0; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(68 * int(CurrentFrame), 144, 68, 72));
		}
		if ((Keyboard::isKeyPressed(Keyboard::W))) { 
			p.dir = 3; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(68 * int(CurrentFrame), 216, 68, 72));
		}
		if ((Keyboard::isKeyPressed(Keyboard::S))) { 
			p.dir = 2; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(68 * int(CurrentFrame), 0, 68, 72)); 
		}

		if ((Keyboard::isKeyPressed(Keyboard::Left))) {
			cat.dir = 1; cat.speed = 0.2;
			CurrentFrameCat += 0.005 * time;
			if (CurrentFrameCat > 4) CurrentFrameCat -= 4;
			cat.sprite.setTextureRect(IntRect(160 * int(CurrentFrameCat), 480, 160, 160));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			cat.dir = 0; cat.speed = 0.2;
			CurrentFrameCat += 0.005 * time;
			if (CurrentFrameCat > 4) CurrentFrameCat -= 4;
			cat.sprite.setTextureRect(IntRect(160 * int(CurrentFrameCat), 160, 160, 160));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			cat.dir = 3; cat.speed = 0.2;
			CurrentFrameCat += 0.005 * time;
			if (CurrentFrameCat > 4) CurrentFrameCat -= 4;
			cat.sprite.setTextureRect(IntRect(160 * int(CurrentFrameCat), 320, 160, 160));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			cat.dir = 2; cat.speed = 0.2;
			CurrentFrameCat += 0.005 * time;
			if (CurrentFrameCat > 4) CurrentFrameCat -= 4;
			cat.sprite.setTextureRect(IntRect(160 * int(CurrentFrameCat), 0, 160, 160));
		}

		p.update(time);
		cat.update(time);
		window.clear();

		///////////////////////////////////////////////////////////////
		Vector2f targetSize(32.0f, 32.0f);
		for (int i = 0; i < HEIGHT_MAP; i++)
		{	
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(160, 0, 160, 160)); 
				if (TileMap[i][j] == 's') s_map.setTextureRect(IntRect(0, 0, 160, 160));
				if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(320, 0, 160, 160));

				s_map.setScale(targetSize.x / s_map.getLocalBounds().width, targetSize.y / s_map.getLocalBounds().height);

				s_map.setPosition(j * 32, i * 32);

				window.draw(s_map);
			}
		}
		window.draw(p.sprite);
		window.draw(cat.sprite);
		window.display();
	}

	return 0;
}
