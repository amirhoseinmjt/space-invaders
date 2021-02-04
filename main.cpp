#include<iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include<math.h>
#include<vector>
#include<cstdlib>



using namespace sf;

class Enemy
{
public:
	int hp;
	int hpmax ;
	Sprite  Shape ;
	Enemy(Texture *texture , Vector2u windowsize )
	{
		this-> hpmax = rand()%3 + 1;
		this->hp = this->hpmax ;
		this->Shape.setTexture(*texture);
		this->Shape.setScale(0.1f, 0.1f);
		this->Shape.setPosition(rand()%windowsize.x - this->Shape.getGlobalBounds().width, this->Shape.getGlobalBounds().height);

	}

	~Enemy(){}

};

class Bullet
{
public:
	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;

	Bullet(float radius = 5.f)
		: currVelocity(0.f, 0.f), maxSpeed(15.f)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(Color::Red);
	}
};

int main()
{
	srand(time(NULL));

	RenderWindow window(sf::VideoMode(1000, 800), "space invades",  sf::Style::Titlebar | sf::Style::Close
                         | sf::Style::Resize );
    window.setMouseCursorVisible(true);
    window.setFramerateLimit(60);
	//Player
	CircleShape player(50.f);
	player.setFillColor(Color::White);
	player.setPointCount(3);
	player.setOrigin(50.f, 50.f);
    player.setPosition(950, 750) ;

    Texture ship ;
    ship.loadFromFile("ship.png");
    player.setTexture(&ship);

	//Bullets
	Bullet b1;
	std::vector<Bullet> bullets;

	

	//Vectors
	Vector2f playerCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;

	//Enemy
	/*RectangleShape enemy;
	enemy.setFillColor(Color::White);
	enemy.setPosition(100 , 100) ;
	enemy.setSize(Vector2f(50.f, 50.f));
	int spawnCounter = 20;
	
	int y ;*/
	Vector2f movement(5.f ,0.f );
	Texture ent ;
	ent.loadFromFile("enemyve.png");

	std::vector<Enemy> enemies;
	enemies.push_back(Enemy(&ent , window.getSize()));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			 if ((event.type == sf::Event::Closed) ||
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
				window.close();
		}

		//Update
		//Vectors
		playerCenter = Vector2f(player.getPosition());
		mousePosWindow = Vector2f(Mouse::getPosition(window));
		aimDir = mousePosWindow - playerCenter;
		aimDirNorm.x = aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
        aimDirNorm.y = aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		float PI = 3.14159265f;
		float deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / PI;
		player.setRotation(deg + 90);
     
		//Player
		if (Keyboard::isKeyPressed(Keyboard::A))
			player.move(-10.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.move(10.f, 0.f);
			
			//dont go out :))
		
		if(player.getPosition().x <= 0)
		{
			player.setPosition(0.f, player.getPosition().y) ;
		}
		else if(player.getPosition().x >= window.getSize().x)
		{
			//player.setPosition(window.getSize().x - player.getLocalBounds().width, player.getPosition().y) ;
			player.setPosition(window.getSize().x , player.getPosition().y) ;
		}
		
		
		//Shooting
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			b1.shape.setPosition(playerCenter);
			b1.currVelocity = aimDirNorm * b1.maxSpeed;

			bullets.push_back(Bullet(b1));
		}

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].shape.move(bullets[i].currVelocity);

			//Out of bounds
			if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x
				|| bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y)
				bullets.erase(bullets.begin() + i);

			
				
		}

		//enemy 

		//enemy movment control
		/*if(enemy.getPosition().x >= window.getSize().x -25)
		{
			movement.x *= -1;

			enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y+50 ) ;
		}
		if(enemy.getPosition().x <= 0)
		{
			movement.x *= -1;
			enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y+50 );
		}
	
		enemy.move(movement) ;*/

		//Draw
		window.clear();
		window.draw(player);

		for (size_t i = 0; i < bullets.size(); i++)		
			window.draw(bullets[i].shape);
		//window.draw(enemy);
		for (size_t i = 0; i < enemies.size(); i++)
		{	
			//enemy move
			if(enemies[i].Shape.getPosition().x >= window.getSize().x -25)
			{
				movement.x *= -1;

				enemies[i].Shape.setPosition(enemies[i].Shape.getPosition().x, enemies[i].Shape.getPosition().y+50 ) ;
			}
			if(enemies[i].Shape.getPosition().x <= 0)
			{
				movement.x *= -1;
				enemies[i].Shape.setPosition(enemies[i].Shape.getPosition().x, enemies[i].Shape.getPosition().y+50 );
			}
	
			enemies[i].Shape.move(movement) ;

			window.draw(enemies[i].Shape);


		}
		

		
		window.display();
	}
	return 0;
}