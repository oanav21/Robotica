Tema Matrice 

Snake Game

Youtube: https://youtu.be/K0zparGiEfQ

    Componente: 
    
    - Arduino Mega2560 
    - Cablu serial 
    - Fire de conexiune mama-tata/ tata-tata 
    - Breadboard x2 
    - Mini Breadboard 
    - Matrice de Led-uri 8x8 - 1088AS 
    - Driver MAX7219 
    - Joystick 
    - Capacitor ceramic 104
    - Capacitor Electrolytic 10uF 
    - Rezistenta 220 ohm/ 100k 
    - Button 
    - Display LCD 16x2


    Reguli Joc: 
    
    Pentru a incepe jocul, se va apasa butonul de "Start". Pentru a putea fi miscat sarpele se va utiliza Joystick-ul in felul urmator: sus-jos va reprezenta dreapta-stanga pe matrice, iar stanga-drepta va fi jos-sus. Scopul jocului este de a obtine cat mai multe puncte, mai precis de a creste lungimea sarpelui cat mai mult cu putinta. De-a lungul acestui joc va exista hrana, sub forma unui led intermitent, care va determina dezvoltarea imediata a sarpelui, dar si marirea vitezei cu care acesta se deplaseaza. La fiecare hrana mancata, jucatorul va castiga 10p in plus la scor. Jocul se incheie in momentul in care sarpele se va atinge pe sine. Insa, fiecare persoana care va juca, are dreptul la 3 runde (vieti), care se vor restarta automat. La finalul lor, pentru a incepe o noua repriza, cel care se va juca va fi nevoit sa apese din nou pe butonul de "Start".


    Program - arduino: 
    
    Sarpele il vom vedea ca 2 vectori: unul reprezintalinia, iar celalalt coloana pe care se afla componenta lui respectiva. Am utilizat o variabila "life" cu scopul de a putea determina la al catelea joc se afla jucatorul, in functie de asta stiind daca se va restarta singur sau se va opri. In functie de valoarea citita pentru axele Ox, Oy, determinam directia in care merge, pe care o vom retine intr-un string "direction". Variabila "inGame" ne va spune daca jocul a inceput. La Start, sarpele va merge in sus, iar mancarea va fi generata aleator. Pentru a facilita intelegerea codului am creat mai multe functii cu roluri diverse:
    
    a) newGame: va initializa varabilele necesare pentru ca jocul sa o ia de la capat 
    b) checkIfHitSelf: va verifica daca am intrat in cazul in care sarpele ajunge sa isi manance coada 
    c) checkIfHitFood: va verifica daca a atins hrana 
    d) drawSnake: va construi sarpele in momentele in care se modifica 
    e) newFood: va genera pozitia hranei aleator 
    f) isSnake: va determina daca locul unde s-a generat mancarea este cumva parte a sarpelui, caz in care o vom schimba 
    g) move: va deplasa sarpele 
    h) drawFood: deseneaza hrana 
    i) gameOver: cazul in care se mananca pe sine si unde verificam cate vieti i-au mai ramas
