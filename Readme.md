# Strzelanka multiplayerowa 2d typu splite screen dla 2 graczy SFML - "Planet Shooter"

## 1.Ogólne założenia:
>gra to dwuosobowa strzelanka która odbywa się w środowisku, które jest zapętloną mapą

>do około mapy są rozmieszczone różne platformy, by urozmaicić środowisko gry

>aby zdynamizować rozgrywkę gracze mają do dyspozycji jetpacki

>gracz ma do użytku interface tj. ilość życia, minimalistyczna tabela wyników

>aby używać jetpacku gracz musi oderwać się od ziemi - stworzy to pewną trudność w poruszaniu, a tym samym urozmaici rozgrywkęaby

## 2. Wygląd:
>okno gry jest podzielone na 3 elementy: okno gracza 1., okno gracza 2. i interface

>kamera porusza się razem z graczem - jest wycentrowana na jego postać

>animacje ruchu gracza – lot prawo, lewo,  góra, dół i pozycja spoczynkowa gdy stoi na planecie, osobne textury podzcas używania jetpacka

>pociski to zwykłe zielone koła

>proste prostokątne platformy z nałożoną teksturą

>niebieskie tło

>różne bonusy dające różne moce graczom.

## 3. Działanie:
#### Pociski, zabicia, odrodzenia, życie:
>gracze otrzymują obrażenia za pomocą pocisków wystrzelonych przez innych graczy oraz gdy wylecą poza daną wysokość – ograniczy to pole rozgrywki

>pociski znikają gdy nalecą na przeszkodę - gracza, platformę

>gracz umiera gdy jego pasek zdrowia osiągnie 0

>gracze odradzają się na powierzchni losowej platformy

>rozgrywka kończy się po osiągnięciu danej liczby zabić (3)
#### Sterowanie:

>gracze sterują swoimi postaciami za pomocą kontrolerów xbox-owych - zarówno gracz 1. jak i 2.

>gracze używają lewej gałki by przesówać postać w prawo i lewo

>sterowanie strzelaniem odbywa się przez wychylanie prawej gałki - za jej pomocą gracz nadaje kierunek pociskom

>pojedynczy klawisz - użycie jetpaka

>pojedynczy klawisz - skok - wymagane jest oderwanie się od ziemi by użyć jetpacka


#### Platformy:

>platformy są nieruchome

>gracze mogą stawać na platformach

>pociski znikają po zderzeniu z platformą

>są rozmieszczane losowo na różnnych poziomach

#### Przedmioty:
>graczę mogą podnosić rozmieszczone po mapie przedmioty

>przedmioty mają określony czas działania, potem znikają

>przedmioty są losowo rozmieszczone po mapie

>pistolet - zwiększa szybkostrzelność gracza

>apteczka dodaje 20 punktów życia, jednak nie pozwala na uleczenie gdy ma się więcej niż 80 punktów życia

>błyskawica zwiększa szybkość poruszania się

#### Mapa:
>platformy są rozmieszczane losowo

>dół stanowi jedna duża platforma

>mapa jest zapętlona - gracz teleportuje się z jednego końca na drugi

>mapa jest ograniczona z góry - gracze tracą życie po przekroczeniu danego pułapu


## 4. Klasy i ich zawartość:
#### Background:
Ułatia tworznie tła i nakładania tekstur.

```c++
class Background : public sf::RectangleShape
{
        public:
            Background();
            Background(sf::Vector2f size, sf::Vector2f texture_size, std::string texture_name);
            void repeate(float x, float y = 1.0);
        private:
            sf::Texture texture_;
            sf::Vector2f size_;
            sf::Vector2f texture_size;
        };

#endif // BACKGROUND_H

```

#### Bonus
Zawiera mechanizmy losujące typ bonusu oraz miejsce jego wystąpienia.
Wszystko skupione zostaje w funkcji statycznej "bonus_generator".
```c++
class Bonus : public sf::Sprite
{
public:
    Bonus(std::vector<std::unique_ptr<sf::Drawable>> &things);
    static void bonus_generator(sf::Time &time, sf::Clock &clock, std::vector<std::unique_ptr<sf::Drawable>> &things, int bonus_pause);
    Type random();
    Type type(Type type);
    bool touch(std::unique_ptr<Player> &player);
    void send(std::unique_ptr<Player> &player);
private:
    Type type_;
    int size_ = 50;
    int hight = 10;
    sf::Texture texture_;
    sf::Vector2f speed_;
    int aid_;
    int fire_rate_;
};

```

#### Bullet:
Odpowiada za tworzenie pocisków jako elementów fizycznych rozgrywki - obiekty te są wykorzystywana w klacsie "Player".
```c++
class Bullet : public sf::CircleShape
{
public:
    Bullet();
    ~Bullet();
    int getSpeed();
    void setDir(sf::Vector2f dir);
    sf::Vector2f getDir();
    bool is_dead(sf::Vector2f window_size, const std::vector<std::unique_ptr<sf::Drawable>> &vector);
    bool dead = false;

private:
    int size_ = 5;
    int speed_ = 500;
    sf::Vector2f dir;
};
```

#### Platform:
Głównym jej zadaniem jest generowanie platform za pomocą funkcji "platform_maker". Klasa przechowuje także tekstury i wielkości platform.

```c++
class Platform : public sf::RectangleShape
{
public:
    Platform();
    Platform(int x, int y, sf::Vector2f size, sf::Vector2f texture_size, std::string texture_name);
    void repeate(float x, float y = 1);
    static void platform_maker(sf::Vector2f quantity, sf::Vector2f size, sf::Vector2f screen,
    sf::Vector2f texture_size, std::string texture_name, sf::Vector2f texture_multi, std::vector<std::unique_ptr<sf::Drawable>> &vector);
    sf::Vector2f get_size();
private:
    sf::Texture texture_;
    sf::Vector2f size_;
    sf::Vector2f texture_size;

};
```
#### Player:
Najważniejsza klasa projektu - odpowiada za całe działanie gracza takie jak:
- sterowanie
- poruszanie się
- strzelanie
- obsługa bonusów
- zadawnie obrażeń i utrata życia
- przechowywanie wyników rozgrywki
- kolizje
- animacje
- respawn-y

```c++
class Player : public sf::Sprite
{
public:
    Player(sf::RenderWindow &window, std::string texture_name, input, unsigned int joy=0);
    sf::Texture texture;
    void control(bool on_platform);
    void jetpack(bool on_platform);
    void hit(const std::unique_ptr<Player> &player);
    void collision(const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    void animation(bool on_platform);
    void teleport();
    void movement();
    void shooting();
    void bulets_remove();
    void respawn(int hight, const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    void bonus();
    void hight_limit();
    int get_life();
    int get_score();
    bool gravity(float a, const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    bool active_bonus = false;
    Type bonus_type;
    std::vector<std::unique_ptr<Bullet>> bullets;

private:


    void image_select(float x, float y, bool is_right = true);
    sf::Vector2f shooting_dir();
    sf::Vector2f velocity = {0, 0};
    sf::Vector2f window_size;
    sf::Vector2f sprite_size;
    sf::Vector2f image_count;
    sf::IntRect rect;
    sf::Clock clock;
    sf::Clock clock2;
    sf::Clock bonus_clock;

    input input_;
    Bullet bullet_;
    unsigned int joy_nr;
    int bonus_duration = 10;
    int life = 0;
    int score = -1;
    int damage = 10;
    float fire_rate = 5;
    float fire_rate_old;
    float move_speed_ = 200;
    float jump_speed_ = 200;
    float move_speed_old;
    float jump_speed_old;

    bool jetpack_ = false;
};

#endif // PLAYER_H

```
#### Text:
Odpowiedzialna za wyświetlanie tekstu.

```c++
class Text : public sf::Text
{
public:
    Text();
    Text(sf::Vector2f position, int size_);
private:
    int size_;
    sf::Font font;

};
```







![Map](https://github.com/Liwusek/Projekt-PSiO-planet-shooter/blob/master/images/planet_shooter1.png)
![One player](https://github.com/Liwusek/Projekt-PSiO-planet-shooter/blob/master/images/planet_shooter3.png)
![Full game](https://github.com/Liwusek/Projekt-PSiO-planet-shooter/blob/master/images/planet_shooter2.png)
