# Strzelanka multiplayerowa 2d typu splite screen dla 4 graczy SFML - "Planet Shooter"

## 1.Ogólne założenia:
>mapą jest rotująca planeta

>do około planety są rozmieszczone różne platformy, by urozmaicić środowisko gry

>aby zdynamizować rozgrywkę gracze mają do dyspozycji jetpacki

>różne planety, a co za tym idzie inne rozłożenie platform oraz inna grawitacja

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
>gracze do sterowania postaciami korzystają z kontrolerów xbox-owych, które są wspierane prze SFML-a – pozwoli to na równoczesną rozgrywkę 4 graczy

>lewym analogiem będzie realizowany ruch gracza po okręgu wokół planety - wychylenie gałki w lewą stronę powoduje jego orbitowanie w prawo, w lewą lewo

>sterowanie strzelaniem odbywa się przez wychylanie drugiej gałki - za jej pomocą gracz nadaje kierunek pociskom

>pojedynczy klawisz - użycie jetpaka

#### Poruszanie się:
>nie ma skoku - zamiast tego gracze mają do dyspozycji jetpaki za pomocą których mogą odrywać się od powierzchni planety - ich użycie (aktywacja za pomocą pojedynczego  zwiększa promień okręgu po którym realizowany jest aktualny ruch

#### Platformy:
>platformy są nieruchome

>gracze mogą stawać na platformach

>pociski znikają po zderzeniu z platformą
#### Przedmioty:
>przedmioty do podniesienia (na chwilę obecną): zwiększenie prędkości poruszania się oraz druga broń - karabin maszynowy o zwiększonej szybkostrzelności (domyślnie jest wolny pistolet)

>przedmioty mają określony czas działania, potem znikają

>przedmioty są losowo rozmieszczone po mapie

#### Mapa:
>pierwsza wersja będzie mieć dwie planety - Mars i księżyc. Będą one mocno różnić się przyciąganiem oraz rozmieszczeniem platform.

>planeta kręci się podczas gry; gracze stając na planecie dostają "premię" do prędkości w kierunku, w którym kręci się planeta oraz "karę" do ruchu w drugą stronę
