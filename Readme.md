# Strzelanka multiplayerowa 2d typu splite screen dla 4 graczy SFML - "Planet Shooter"

## 1.Ogólne założenia:
>gra to dwuosobowa strzelanka która odbywa się na tzw, "planecie" - środowisku, które jest zapętloną mapą

>do około planety są rozmieszczone różne platformy, by urozmaicić środowisko gry

>aby zdynamizować rozgrywkę gracze mają do dyspozycji jetpacki

>różne planety, a co za tym idzie inne rozłożenie platform oraz inna grawitacja (na razie dwie - jedna predefiniowana (Mars), druga losowo generowana).

>gracz ma do użytku interface tj. ilość życia, posiadane umiejętności, minimalistyczna tabela wyników

>ruch gracza charakteryzuje pewna bezwładność - stworzy to pewną trudność w poruszaniu, a tym samym urozmaici rozgrywkę

## 2. Wygląd:
>kamera danego gracza ma być statyczna tj. gdy porusza się po powierzchni wokół planety kamera nie przekręca się z graczem – ma to być najważniejsza mechanika rozgrywki

>animacje ruchu gracza – lot prawo, lewo,  góra, dół i pozycja spoczynkowa gdy stoi na planecie.

## 3. Działanie:
#### Pociski, zabicia, odrodzenia, życie:
>gracze otrzymują obrażenia za pomocą pocisków wystrzelonych przez innych graczy oraz gdy wylecą poza daną wysokość – ograniczy to pole rozgrywki

>pociski znikają gdy nalecą na przeszkodę - gracza, platformę, planetę

>gracz umiera gdy jego pasek zdrowia osiągnie 0

>gracze odradzają się po przeciwnej stronie planety od miejsca zgonu

>rozgrywka kończy się po osiągnięciu danej liczby zabić
#### Sterowanie:

>postać gracza 1. jest sterowana za pomocą myszki i klawiatury, gracz 2. ma do dyspozycji controller xbox-owy

>sterowanie strzelaniem odbywa się przez wychylanie gałki - za jej pomocą gracz nadaje kierunek pociskom lub myszki - pociski kierują sie w stronę kursora

>pojedynczy klawisz - użycie jetpaka

#### Poruszanie się:
>nie ma skoku - zamiast tego gracze mają do dyspozycji jetpaki za pomocą których mogą odrywać się od powierzchni planety.
#### Platformy:

>platformy są nieruchome

>gracze mogą stawać na platformach

>pociski znikają po zderzeniu z platformą
#### Przedmioty:
>przedmioty do podniesienia (na chwilę obecną): zwiększenie prędkości poruszania się oraz druga broń - karabin maszynowy o zwiększonej szybkostrzelności (domyślnie jest wolny pistolet)

>przedmioty mają określony czas działania, potem znikają

>przedmioty są losowo rozmieszczone po mapie

#### Mapa:
>pierwsza wersja będzie mieć dwie opcje map - predefiniowany Mars oraz mapę generowaną losowo. Nie tylko platformy się zmieniają, ale też siła grwitacji


## 4. Klasy i ich zawartość:
#### Animation:
Odtwarzanie animacji:

```c++
class Animation
{
public:
    Animation(sf::Vector2f current_image, sf::Vector2f image_count, sf::IntRect rect, float delta_time); //konstruktor
    ~Animation();
    sf::Vector2f update(float current_image.y, float delta_time, bool is_fliped = true) //wyświetla animacje, zwraca wielkość uzyskanego sprita
private:
    sf::Vector2f current_image //przechowuje indeks obecnie używanej tekstury
    sf::Vector2f image_count //przechwuje ilość pojedynczych tekstur pliku .png w obu osiach
    sf::IntRect rect //służy do wycinania poszczególnych fragmentów tekstury
    float delta_time //zmienna służąca do kontroli długości trwania animacji
    bool is_fliped //sygnalizuje czy teksture należy obrócić wzdłuż osi y
};
```

#### Functions
Przechowuje zmienne i funkcje przydatne dla wszystkich elementów rozgrywki:
-czas
-wielkość pola rozgrywki
-tekstury

```c++
class Functions : public sf::Clock
{
public:
    virtual ~Functions() = default;
    Functions(sf::RenderWindow &window, std::string name); //konstruktor - name to nazwa pliku z teksturą
    virtual void getBounds(sf::RenderWindow &window); //nadpisuje this->screen_bounds wielkością wyświetlanego okna
    virtual float getTime(); //zwraca clock.restart().asSeconds();

protected:
    sf::Texture texture //przechowuje tekstury
    sf::Vector2f screen_bounds; //przechowuje wielkość wyświetlanego okna
};
```

#### Gravity:

```c++
class Gravity
{
public:
    Gravity(float  power, sf::Vector2f position);
    apply() //uruchamia grawitacje
private:
    sf::Vector2f position; //punkt do którego przyciąga grawitacja
    float power; //siła grawitacji
};
```

#### Planet:
Klasa mapy - informacje o planecie:

```c++
class Planet : public sf::CircleShape, Functions
{
public:
    Planet(int radius, int spin, sf::RenderWindow &window);
    void change_spin(float spin); //nadpisywanie this->spin
    void spin(); //wykonywanie animacji obrotu wokół własnej osi
private:
    Animation animation; //służy do aniimacji tekstur
    int radius; //promień planety
    int height; //wysokość okraniczająca rozgrywkę
    int spin; //prędkość obrotu planety
    int gravity; //siła grawitacji
};
```
#### Platform:
Informacje o planecie:
```c++
class Platform : public sf::Rectangleshape, Functions
{
public:
    Planet(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow &window);
    void spin(int spin, sf::Vector2f center = screen_bounds/2); //wykonywanie animacji obrotu wokół środka planety, gdzie spin to szybkość obrotu
private:
    Animation animation; //animacja tekstur
    sf::Vector2f size;  //wielkość platformy
    sf::Vector2f position; //pozycja platformy
};
```
#### Player:
Informacje o postaci gracza:

```c++
class Player : public sf::Sprite, public Functions
{
public:
    Player(sf::RenderWindow &window);
    Player();
    void collision(const std::vector<std::unique_ptr<sf::Drawable>> &things); //wykrywa kolizje z obiektmi
    void control(bool is_midair); //sterowanie postacią gracza
private:
    Animation animation //animacja tekstur
    Gravity gravity; //grawitacja
    bool is_midair; //zmienna mówiąca czy gracz znajduje się w powietrzu
    sf::Vector2f speed = {100, 100}; //speed.x prędkość gracza, speed.y wysokość skoku
    sf::Vector2f size //wielkość sprita
};
```







![Map](https://github.com/Liwusek/Projekt-PSiO-planet-shooter/blob/master/images/planet_shooter1.png)
![One player](https://github.com/Liwusek/Projekt-PSiO-planet-shooter/blob/master/images/planet_shooter3.png)
![Full game](https://github.com/Liwusek/Projekt-PSiO-planet-shooter/blob/master/images/planet_shooter2.png)
