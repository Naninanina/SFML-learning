#include <SFML/Graphics.hpp>
#include <iostream>

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

	Player p("character.png", 50, 25, 68.0, 72.0);

	float CurrentFrame = 0;
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

		if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A))) {
			p.dir = 1; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(68 * int(CurrentFrame), 72, 68, 72));
		} 
		if (Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))) {
			p.dir = 0; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(68 * int(CurrentFrame), 144, 68, 72));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))) { 
			p.dir = 3; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(68 * int(CurrentFrame), 216, 68, 72));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))) { 
			p.dir = 2; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(68 * int(CurrentFrame), 0, 68, 72)); 
		}

		p.update(time);
		window.clear();
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}
