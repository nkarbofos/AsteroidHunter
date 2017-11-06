#include <iostream>
#include <SFML/Graphics.hpp>
#include "SpaceObject.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Explosion.h"
#include "utils.h"


void delete_bullet(Bullet **bullets, int i, int &b_cnt)
{
    delete bullets[i];
    for(int i2 = i; i2 < b_cnt-1; i2++)
    {
        bullets[i2] = bullets[i2+1];
    }
    b_cnt--;
}

void check_alive_bullets(Bullet **bullets, int &b_cnt)
{
    for(int i = 0; i < b_cnt; i++)
    {
        if(!bullets[i]->is_alive())
        {
            delete_bullet(bullets, i, b_cnt);
            i--;
        }
    }
}

void delete_explosion(Explosion **explosions, int i, int &e_cnt)
{
    delete explosions[i];
    for(int i2 = i; i2 < e_cnt-1; i2++)
    {
        explosions[i2] = explosions[i2+1];
    }
    e_cnt--;
}

void check_alive_explosions(Explosion **explosions, int &e_cnt)
{
    for(int i = 0; i < e_cnt; i++)
    {
        if(!explosions[i]->is_alive())
        {
            delete_explosion(explosions, i, e_cnt);
            //i--;
        }
    }
}

void delete_asteroid(Asteroid **asteroids, int i, int &a_cnt)
{
    delete asteroids[i];
    for(int i2 = i; i2 < a_cnt-1; i2++)
    {
        asteroids[i2] = asteroids[i2+1];
    }
    a_cnt--;
}

void lose(sf::RenderWindow &window)
{
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    m_texture.loadFromFile("lose.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(0, 0);
    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.draw(m_sprite);
        window.display();
    }
}

void game(sf::RenderWindow &window)
{
    sf::Texture bullet_texture;
    bullet_texture.loadFromFile("bullet.png");

    Ship s(400, 300);

    Asteroid *asteroids[200];
    int a_cnt = 0;
    int last_ast = 0;

    Bullet *bullets[500];
    int b_cnt = 0;
    int last_fired = 20;

    Explosion *explosions[100];
    int e_cnt = 0;
    int death_timer = -1;

    bool ship_alive = true;
    /////////////// ОСНОВНОЙ ЦИКЛ ОТРИСОВКИ //////////////////
    while (window.isOpen())
    {
        last_fired++;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        if(ship_alive == true)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) s.left();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) s.right();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) s.forward(0.1);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && last_fired > 20)
            {

                bullets[b_cnt] = new Bullet(s.get_x(), s.get_y(), s.get_angle(), bullet_texture);
                last_fired = 0;
                b_cnt++;
            }

            s.update();
            window.draw(s.get_sprite());
        }

        if(last_ast % 1000 == 0)
        {
            asteroids[a_cnt] = new Asteroid(rnd(800), 0, rnd(3), rnd(360), 5, 0, rnd(3));
            a_cnt++;
        }
        last_ast++;

        for(int i=0; i<a_cnt; i++)
        {
            asteroids[i]->update();
            window.draw(asteroids[i]->get_sprite());
        }

        check_alive_bullets(bullets, b_cnt);
        for(int i=0; i<b_cnt; i++)
        {
            bullets[i]->update();
            window.draw(bullets[i]->get_sprite());
        }

        for(int c_asteroid=0; c_asteroid<a_cnt; c_asteroid++)
        {
            Asteroid *ast = asteroids[c_asteroid];
            for(int c_bullet=0; c_bullet<b_cnt; c_bullet++)
            {
                if(bullets[c_bullet]->get_sprite().getGlobalBounds().intersects(ast->get_sprite().getGlobalBounds()))
                {
                    explosions[e_cnt] = new Explosion(ast->get_x(), ast->get_y());
                    e_cnt++;
                    delete_bullet(bullets, c_bullet, b_cnt);
                    if(ast->hit()){
                        if(ast->get_size() == 0)
                        {
                            asteroids[a_cnt] = new Asteroid(ast->get_x(), ast->get_y(), rnd(3), ast->get_angle() - 15, 2, 1, ast->get_color());
                            a_cnt++;
                            asteroids[a_cnt] = new Asteroid(ast->get_x(), ast->get_y(), rnd(3), ast->get_angle() + 15, 2, 1, ast->get_color());
                            a_cnt++;
                        } else if(ast->get_size() == 1)
                        {
                            asteroids[a_cnt] = new Asteroid(ast->get_x(), ast->get_y(), rnd(3), ast->get_angle() - 15, 1, 2, ast->get_color());
                            a_cnt++;
                            asteroids[a_cnt] = new Asteroid(ast->get_x(), ast->get_y(), rnd(3), ast->get_angle() + 15, 1, 2, ast->get_color());
                            a_cnt++;
                        }
                        delete_asteroid(asteroids, c_asteroid, a_cnt);
                       // c_asteroid--;
                    }
                    //c_bullet--;

                }
            }

            if(ship_alive && s.get_sprite().getGlobalBounds().intersects(ast->get_sprite().getGlobalBounds()))
            {
                ship_alive = false;
                for(int i = 0; i<10; i++){
                    explosions[e_cnt] = new Explosion(s.get_x() - 80 + rnd(80), s.get_y() - 80 + rnd(80));
                    e_cnt++;
                }
                death_timer = 120;
            }

        }

        for(int i=0; i<e_cnt; i++)
        {
            explosions[i]->update();
            window.draw(explosions[i]->get_sprite());
        }
        check_alive_explosions(explosions, e_cnt);

        window.display();

        if(death_timer > -1){
            death_timer--;
            if(death_timer == 0) return;
        }

    }
}

bool zast(sf::RenderWindow &window)
{
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    m_texture.loadFromFile("zast.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(50, 100);
    Asteroid *asteroids[200];
    int a_cnt = 0;
    for(int i = 0; i < 10; i++)
    {
        asteroids[a_cnt] = new Asteroid(rnd(800), rnd(600), rnd(3), rnd(360), 5, 0, rnd(3));
        a_cnt++;
    }
    while (window.isOpen())
    {
        window.clear();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return true;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }
        }

        for(int i=0; i<a_cnt; i++)
        {
            asteroids[i]->update();
            window.draw(asteroids[i]->get_sprite());
        }
        window.draw(m_sprite);
        window.display();
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "ASTEROID HUNTER");
    window.setFramerateLimit(60);
    bool start_game = zast(window);
    if(start_game == true) game(window);
    lose(window);
}
