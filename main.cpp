#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"

using namespace sf; //пространство имен sfml
class Characteristics{ //общие характеристики для персонажа и монстра

public:
    float x, y, w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    int dir = 0; //направление (direction) движения игрока
    int score = 0;
    bool life; // жизнь
    bool cherry; //ягодка специальный предемет
    Image image;//сфмл изображение
    Texture texture;//сфмл текстура
    Sprite sprite;//сфмл спрайт
    std::string File;

    Characteristics(std::string F, float X, float Y, float W, float H){  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
        life = true;
        cherry = false;
        w = W; h = H;//высота и ширина
        File = F;
        image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта.
        texture.loadFromImage(image);//закидываем наше изображение в текстуру
        sprite.setTexture(texture);//заливаем спрайт текстурой
        x = X; y = Y;//координата появления спрайта
        sprite.setTextureRect(IntRect(0, 0, w, h));  //Задаем спрайту один прямоугольник для вывода картинки
    };

};

class Player: public Characteristics{// класс Игрока

public:
    int timer;
    Player(std::string F, float X, float Y, float W, float H):Characteristics(F, X, Y, W, H){  //Конструктор с параметрами(формальными) для класса Player.
        // При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
    }

    void update(float time) //отвечает за движение персонажа(обновление положения спрайта + описание скорости)
    {
        switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
        {
            case 0:
                dx = speed;
                dy = 0;
            break;//по иксу задаем положительную скорость, по игреку зануляем. получается, что персонаж идет только вправо

            case 1:
                dx = -speed;
                dy = 0;
            break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево

            case 2:
                dx = 0;
                dy = speed;
            break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз

            case 3:
                dx = 0;
                dy = -speed;
            break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх

        }
        x += dx*time; // скорость по х
        y += dy*time; // скорость по y
        speed = 0;//зануляем скорость, чтобы персонаж остановился. (как бы общая скорость)
        sprite.setPosition(x,y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
        interactionWithMap();
    }
    void interactionWithMap()//ф-ция взаимодействия с картой
    {

        for (int i = y / 20; i < (y + h) / 20; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера *20
            for (int j = x / 20; j<(x + w) / 20; j++)//икс делим на 20, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 20*20, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 20 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
            {
                if (TileMap[i][j] == '1'|| TileMap[i][j] =='2')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
                {
                    if (dy>0)//если мы шли вниз,
                    {
                        y = i * 20 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
                    }

                    if (dy<0)
                    {
                        y = i * 20 + 20;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх
                    }

                    if (dx>0)
                    {
                        x = j * 20 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                    }

                    if (dx < 0)
                    {
                        x = j * 20 + 20;//аналогично идем влево
                    }

                }

                if (TileMap[i][j] == 's')
                { //если символ равен 's' (желтый кружок)
                    score += 50; // счет игрок, +50 за каждый кружок
                    TileMap[i][j] = ' ';//убираем кружок
                }

                if (TileMap[i][j] == 'f')
                { //если символ равен 'c' (камень)
                    cherry = true; // включаем функцию cherry (скорость + возможность есть монстров)
                    TileMap[i][j] = ' ';//убираем ягодку
                }
            }
    }

};
class Monstr: public Characteristics{ //класс наших монстров
public:
    Sprite sprite1;
    int moveTimer;
    Monstr(std::string F, float X, float Y, float W, float H): Characteristics(F, X, Y, W, H){
        sprite.setPosition(x,y);//Конструктор с параметрами(формальными) для класса монстр. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
        dx = 0.05;

    }
    void checkCollisionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой
    {
        for (int i = y / 20; i < (y + h) / 20; i++)//проходимся по элементам карты
            for (int j = x / 20; j<(x + w) / 20; j++)
            {
                if (TileMap[i][j] == '1'||TileMap[i][j] == '2')//если элемент наш тайлик стены, то
                {
                    if (Dy>0){
                        y = i * 20 - h;
                        dy = -0.05;
                    }//столкновение с потолком
                    if (Dy<0){
                        y = i * 20 + 20;
                        dy = 0.05;
                    }//столкновение с полом
                    if (Dx>0){
                        x = j * 20 - w;
                        dx = -0.05;
                    }//с правым краем карты
                    if (Dx<0){
                        x = j * 20 + 20;
                        dx = 0.05;
                    }// с левым краем карты
                }
            }
    }

    void update(float time) { //функция отвечающая за перемещение монстров
        moveTimer += time;

        if (moveTimer>4000&&dx!=0)
        {
            dx = 0;
            dy = 0.05;
            moveTimer = 0;
        }

        if (moveTimer>4000&&dy!=0)
        {
            dy = 0;
            dx = 0.05;
            moveTimer = 0;
        }
        //меняет направление примерно каждые 4 сек
        x += dx * time;
        checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х

        y += dy * time;
        checkCollisionWithMap(0, dy);//обрабатываем столкновение по y

        sprite.setPosition(x, y); //задаем позицию спрайта
    }
    void update1(float time) {
        moveTimer += time;

        if (moveTimer > 1500 && dx != 0)
        {
            dx = 0;
            dy = 0.05;
            moveTimer = 0;
        }

        if (moveTimer > 1500 && dy != 0)
        {
            dy = 0;
            dx = -0.05;
            moveTimer = 0;
        }

        x += dx * time;
        checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х

        y += dy * time;
        checkCollisionWithMap(0, dy);//обрабатываем столкновение по y

        sprite.setPosition(x, y); //задаем позицию спрайта
    }
    void death()
    {
        Image image1;
        image1.loadFromFile("D:\\monsterafr3.png");
        Texture texture1;
        texture1.loadFromImage(image1);
        Sprite sprite1;
        sprite1.setTexture(texture1);
    }
};
//void attack(double k, double b){
   // std::cout<<"line is "<< k <<"*x + " << b << std::endl;

//}

//менюшка
void menu(RenderWindow & window) {

    Texture menuTexture1;
    Texture menuTexture2;
    Texture menuTexture3;
    Texture aboutTexture;
    Texture menuBackground;
    Texture controlsTexture;

    menuTexture1.loadFromFile("D:\\2.png");
    menuTexture2.loadFromFile("D:\\3.png");
    menuTexture3.loadFromFile("D:\\4.png");
    aboutTexture.loadFromFile("D:\\5.png");
    controlsTexture.loadFromFile("D:\\6.png");
    menuBackground.loadFromFile("D:\\7.png");

    Sprite menu1(menuTexture1);
    Sprite menu2(menuTexture2);
    Sprite menu3(menuTexture3);
    Sprite about(aboutTexture);
    Sprite menuBg(menuBackground);
    Sprite control(controlsTexture);

    bool isMenu = 1;
    int menuNum = 0;

    menu1.setPosition(0, 30);
    menu2.setPosition(0, 90);
    menu3.setPosition(0, 150);
    menuBg.setPosition(400, 0);

    while (isMenu)
    {
        menu1.setColor(Color::White);
        menu2.setColor(Color::White);
        menu3.setColor(Color::White);

        menuNum = 0;

        if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window)))
        {
            menu1.setColor(Color::Blue);
            menuNum = 1;
        }

        if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window)))
        {
            menu2.setColor(Color::Blue);
            menuNum = 2;
        }

        if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window)))
        {
            menu3.setColor(Color::Blue);
            menuNum = 3;
        }

        if (Mouse::isButtonPressed(Mouse::Left))
        {

            if (menuNum == 1)
            {
                isMenu = false;//если нажали первую кнопку, то выходим из меню, стартуем игру
            }

            if (menuNum == 2)
            {
                window.draw(control);
                window.display();

                while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }

            if (menuNum == 3)
            {
                window.draw(about);
                window.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }

        }
        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);
        window.display();
    }
}

int main()
{
    Player p("D:\\pacmanfinal1.png", 720, 780, 100, 100); //заполняем конструктор и создаем игрока
    Monstr m("D:\\monster4.png", 700, 150, 80, 80);  // заполняем конструктор и создаем монстра
    Monstr m1("D:\\monster6.png", 620, 150, 82, 78); // заполняем конструктор и создаем монстра

    Image tile1; //загружаем картинку с предметами(стенки, кружок, ягодка)
    tile1.loadFromFile("D:\\map.png");

    Texture texturetile1; //создаем текстуру по картинке
    texturetile1.loadFromImage(tile1);

    Sprite tile1sprite;//создаем спрайт = выделение прямоугольника на спрайте
    tile1sprite.setTexture(texturetile1);
    tile1sprite.setPosition(100,100);

    Clock clock; //создаем часы и несколько счетчиков
    float CurrentFrame = 0;
    int i;
    int counttime;
    int count=15000;

    RenderWindow window(VideoMode(1460, 1000), "PACMAN_MIPT!"); //создает игровое окно

    Font font;//добавляем шрифт
    font.loadFromFile("D:\\CyrilicOld.ttf");
    //создаем три текста
    Text text("Score: ", font, 40);
    text.setFillColor(sf::Color::Blue);

    Text text1("GAME OVER!", font, 100);
    text1.setFillColor(sf::Color::Red);

    Text text2("YOU WIN!", font, 100);
    text2.setFillColor(sf::Color::Green);

//работа с игровый окном, пока открыто вызов функций и обновление игры по времени и клоку
    menu(window);
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart(); //перезагружает время
        time = time/350; //скорость игры

        Event event;//служит для закрытия игры (нажимаем крестик)
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        //взаимодействие тайлов монстра и игрока
        if(((p.x<=m.x&&m.x<=p.x+75)&&(p.y<=m.y&&m.y<=p.y+75))||((p.x>=m.x&&m.x>=p.x-75)&&(p.y>=m.y&&m.y>=p.y-75))||
        ((p.x<=m.x&&m.x<=p.x+75)&&(p.y>=m.y&&m.y>=p.y-75))||((p.x>=m.x&&m.x>=p.x-75)&&(p.y<=m.y&&m.y<=p.y+75)))
        {
            if(p.cherry==false&&(m.dx!=0||m.dy!=0))
            {//если коснулись монстра и нет ягодки, игрок умирает
                p.life = false;
            }

            else if(p.cherry == true)
            { //если коснулись монстра и есть вишенка, то умирает монстр - останавливаем и стираем спрайт
                m.sprite.setTextureRect(IntRect(100, 100, 80,80));
                m.dx =0;
                m.dy =0;
            }

        }
        //взаимодействие другого монстра 2, то же самое
        if(((p.x<=m1.x&&m1.x<=p.x+75)&&(p.y<=m1.y&&m1.y<=p.y+75))||((p.x>=m1.x&&m1.x>=p.x-75)&&(p.y>=m1.y&&m1.y>=p.y-75))||
        ((p.x<=m1.x&&m1.x<=p.x+75)&&(p.y>=m1.y&&m1.y>=p.y-75))||((p.x>=m1.x&&m1.x>=p.x-75)&&(p.y<=m1.y&&m1.y<=p.y+75)))
        {
            if(p.cherry==false&&(m1.dx!=0||m1.dy!=0))
            {
                p.life = false;
            }

            else if(p.cherry == true)
            {
                m1.sprite.setTextureRect(IntRect(80, 0, 80,80));
                m1.dx = 0;
                m1.dy = 0;
            }

        }

        if(p.life==true&&p.score!=7650)
        {//описание управления игроком в случае если он жив и счет не м
            if ((Keyboard::isKeyPressed(Keyboard::Left) ||(Keyboard::isKeyPressed(Keyboard::A))))
            { //движение влево
                counttime += time;

                if (counttime > 250)
                {
                    CurrentFrame += 1;
                    counttime = 0;
                }

                if (CurrentFrame > 2)
                {
                    CurrentFrame -= 3;
                }

                p.dir = 1;
                p.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения.

                if(p.cherry == true&&count>0)
                {
                    p.speed = 0.15;
                    count -= time;
                }

                else{

                    p.cherry = false;
                }
                p.sprite.setTextureRect(IntRect(300, 100 * CurrentFrame, 100,
                                                100)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

            }

            if ((Keyboard::isKeyPressed(Keyboard::Right) ||
                (Keyboard::isKeyPressed(Keyboard::D))))
            {//движение вправо
                counttime += time;

                if (counttime > 250)
                {
                    CurrentFrame += 1;
                    counttime = 0;
                }

                if (CurrentFrame > 2)
                {
                    CurrentFrame -= 3;
                }

                p.dir = 0;
                p.speed = 0.1;//направление вправо, см выше

                if(p.cherry == true&&count>0)
                {
                    p.speed = 0.15;
                    count -= time;
                }
                p.sprite.setTextureRect(IntRect(0, 100 * CurrentFrame, 100,
                                                100));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
            }

            if ((Keyboard::isKeyPressed(Keyboard::Up) ||
                (Keyboard::isKeyPressed(Keyboard::W))))
            {//движение вверх
                counttime += time;

                if (counttime > 250)
                {
                    CurrentFrame += 1;
                    counttime = 0;
                }

                if (CurrentFrame > 2)
                {
                    CurrentFrame -= 3;
                }

                p.dir = 3;
                p.speed = 0.1;//направление вниз, см выше

                if(p.cherry == true&&count>0)
                {
                    p.speed = 0.15;
                    count -= time;
                }
                p.sprite.setTextureRect(IntRect(100, 100 * CurrentFrame, 100,
                                                100));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

            }

            if ((Keyboard::isKeyPressed(Keyboard::Down) ||
                 (Keyboard::isKeyPressed(Keyboard::S))))
            { //движение вниз
                counttime += time;

                if (counttime > 250)
                {
                    CurrentFrame += 1;
                    counttime = 0;
                }

                if (CurrentFrame > 2)
                {
                    CurrentFrame -= 3;
                }

                p.dir = 2;
                p.speed = 0.1;//направление вверх, см выше

                if(p.cherry == true&&count>0)
                {
                    p.speed = 0.15;
                    count -= time;
                }

                p.sprite.setTextureRect(IntRect(200, 100 * CurrentFrame, 100,
                                                100)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96

            }
        }

        p.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
        m.update(time);//аналогично
        m1.update1(time);//аналогично

        //double k = (m.y - p.y)/(m.x - p.x);
        //double b = (m.x*p.y - p.x*m.y)/(m.x - p.x);
        //attack(k, b);
        //пробегаемся по всей карте в map.h и заместо символов делаем спрайт
        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == '2')
                {
                    tile1sprite.setTextureRect(IntRect(0, 0, 20, 20));
                    tile1sprite.setPosition(j * 20, i * 20);
                }

                if ((TileMap[i][j] == '1'))
                {
                    tile1sprite.setTextureRect(IntRect(0, 0, 20, 20));
                    tile1sprite.setPosition(j*20, i*20);
                }

                if ((TileMap[i][j] == 's'))
                {
                    tile1sprite.setTextureRect(IntRect(50, 0, 20, 20));
                    tile1sprite.setPosition(j*20, i*20);
                }

                if ((TileMap[i][j] == 'f'))
                {
                    tile1sprite.setTextureRect(IntRect(50, 21, 40, 40));
                    tile1sprite.setPosition(j*20, i*20);
                }

                 tile1sprite.getPosition().x;
                 tile1sprite.getPosition().y;
                 window.draw(tile1sprite);
                //double k1 = (tile1sprite.getPosition().y - p.y)/(tile1sprite.getPosition().x - p.x);
                //double b1 = (tile1sprite.getPosition().x*p.y - p.x*tile1sprite.getPosition().y)/(tile1sprite.getPosition().x - p.x);
                /*if(k1!=k){
                    m.x = 0;
                    m.y = 0;
                }
                 */
                //attack(k,b);
            }

        if(p.life == false)
        {//завершение игры в случае смерти
            m1.dx = 0;
            m1.dy = 0;
            m.dx = 0;
            m.dy = 0;
            text1.setPosition(450, 400);
            window.draw(text1);
        }

        if(p.score == 7650)
        {//завершение игры в случае набора нужного счета
            m1.dx = 0;
            m1.dy = 0;
            m.dx = 0;
            m.dy = 0;
            text2.setPosition(450, 400);
            window.draw(text2);
        }
        //рисуем на экране все наши объекты + текст
        text.setString("Score: " + std:: to_string(p.score));
        text.setPosition(1200,950);
        window.draw(text);
        window.draw(m.sprite);
        window.draw(m1.sprite);
        window.draw(p.sprite);
        window.draw(tile1sprite);
        window.display();
        window.clear();
    }

    return 0;
}