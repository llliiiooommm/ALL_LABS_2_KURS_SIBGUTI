#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Для эллипса
/*-----------------------------------*/
#ifndef M_PI
#define M_PI 3.14
#endif
/*-----------------------------------*/


class Figure {
	protected:
	    double x, y;


	public:
	    // Конструктор по умолчанию
	    Figure(){
	        x = rand() % 100;
	        y = rand() % 100;
	    }


	    // Конструктор с параметрами
	    Figure(double x, double y) : x(x), y(y) {}


	    // Ввод и вывод
	    virtual void input(){
	        cout << "Введите x и y: ";
	        cin >> x >> y;
	    }
	    virtual void output() const {
	        cout << "Координаты: (" << x << ", " << y << ")";
	    }


	    virtual double getPerimeter() const = 0;


	    // Деструктор
	    virtual ~Figure() = default;
};



class Circle : public Figure{
	protected:
	    double radius;

	    static int totalCreated;
	    static int currentAlive;


	public:
	    // Конструктор по умолчанию
	    Circle() : Figure() {
	        radius = 1 + rand() % 50;
	        ++totalCreated;
	        ++currentAlive;
	    }


	    // Конструктор с параметрами: Используем конструктор класса Figure
	    Circle(double x, double y, double r) : Figure(x, y), radius(r) {
	        ++totalCreated;
	        ++currentAlive;
	    }


	    // Ввод и вывод
	    void input() override {
	        Figure::input();
	        
	        cout << "Введите радиус: ";
	        cin >> radius;
	    }
	    void output() const override{
	        Figure::output();

	        cout << ", Радиус: " << radius;
	    }


	    // Периметр круга
	    double getPerimeter() const override {
	        return 2 * M_PI * radius;
	    }


	    static int getTotalCreated() { return totalCreated; }
	    static int getCurrentAlive() { return currentAlive; }


	    // Деструктор
	    ~Circle() override {
	        --currentAlive;
	    }
};

int Circle::totalCreated = 0;
int Circle::currentAlive = 0;



class Line : public Figure{
	protected:
	    double x2, y2;
	    double length;

	    static int totalCreated;
	    static int currentAlive;


	    void updateLength() {
	        length = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
	    }


	public:
	    // Конструктор по умолчанию
	    Line() : Figure() {
	        x2 = rand() % 100;
	        y2 = rand() % 100;
	        updateLength();
	        ++totalCreated;
	        ++currentAlive;
	    }


	    // Конструктор с параметрами - Используем конструктор класса Figure
	    Line(double x1, double y1, double x2, double y2) : Figure(x1, y1), x2(x2), y2(y2) {
	        updateLength();
	        ++totalCreated;
	        ++currentAlive;
	    }


	    // Расчёты
	    double getLength() const {
	        return length;
	    }
	    double getPerimeter() const override {
	        return length;
	    }


	    // Ввод и вывод
	    void input() override{
	        Figure::input();
	        cout << "Введите x2 и y2: ";
	        cin >> x2 >> y2;
	        updateLength();
	    }
	    void output() const override{
	        cout << "Линия: (" << x << ", " << y << ") -> (" << x2 << ", " << y2 << ")";
	    }
	    void OutputLegth() const {
	        cout << "Длина линии: " << length << endl;
	    }



	    static int getTotalCreated() { return totalCreated; }
	    static int getCurrentAlive() { return currentAlive; }


	    // Деструктор
	    ~Line() override {
	        --currentAlive;
	    }
};

int Line::totalCreated = 0;
int Line::currentAlive = 0;



class Square : public Line{
	protected:
	    static int totalCreated;
	    static int currentAlive;


	public:
	    // Конструктор по умолчанию - используем конструктор по умолчанию из класса Line
	    Square() : Line() {
	        ++totalCreated;
	        ++currentAlive;
	    }


	    // Конструктор с параметрами - используем конструктор класса Line
	    Square(double x1, double y1, double x2, double y2) : Line(x1, y1, x2, y2) {
	        ++totalCreated;
	        ++currentAlive;
	    }


	    // Расчёты
	    double getSide() const {
	        return length;
	    }
	    double getPerimeter() const override {
	        return 4 * getSide();
	    }
	    double getArea() const {
	        double s = getSide();
	        return s * s;
	    }


	    // Ввод с клавиатуры
	    void input() override {
	        Line::input();
	    }
	    void inputRandom() {
	        x = rand() % 100;
	        y = rand() % 100;
	        x2 = rand() % 100;
	        y2 = rand() % 100;
	        updateLength();
	    }
	    void output() const override {
	        cout << "Квадрат: ";
	        Line::output();
	        cout << ", Сторона: " << getSide();
	    }


	    static int getTotalCreated() { return totalCreated; }
	    static int getCurrentAlive() { return currentAlive; }


	    // Деструктор
	    ~Square() override {
	        --currentAlive;
	    }
};

int Square::totalCreated = 0;
int Square::currentAlive = 0;



class Rectangle : public Square {
	private:
	    double height;

	    static int totalCreated;
	    static int currentAlive;


	public:
	    // Конструктор по умолчанию - используем конструктор класса Square
	    Rectangle() : Square() {
	        height = 1 + rand() % 50;
	        ++totalCreated;
	        ++currentAlive;
	    }


	    // Конструктор с параметрами - используем конструктор с параметрами класса Square
	    Rectangle(double x1, double y1, double x2, double y2, double h) : Square(x1, y1, x2, y2), height(h) {
	        ++totalCreated;
	        ++currentAlive;
	    }


	    // Расчёты
	    double getWidth() const {
	        return getSide();
	    }
	    double getPerimeter() const override {
	        return 2 * (getWidth() + height);
	    }
	    double getArea() const {
	        return getWidth() * height;
	    }


	    // Ввод с клавиатуры
	    void input() override {
	        Square::input();
	        cout << "Введите высоту: ";
	        cin >> height;
	    }
	    void inputRandom() {
	        Square::inputRandom();
	        height = 1 + rand() % 50;
	    }
	    void output() const override {
	        cout << "Прямоугольник: ";
	        Line::output();
	        cout << ", Высота: " << height;
	    }


	    static int getTotalCreated() { return totalCreated; }
	    static int getCurrentAlive() { return currentAlive; }


	    // Деструктор
	    ~Rectangle() override {
	        --currentAlive;
	    }
};

int Rectangle::totalCreated = 0;
int Rectangle::currentAlive = 0;



class Ellipse : public Circle {
	private:
	    double secondRadius;

	    static int totalCreated;
	    static int currentAlive;


	public:
	    // Конструктор по умолчанию
	    Ellipse() : Circle() {
	        secondRadius = 1 + rand() % 50;
	        ++totalCreated;
	        ++currentAlive;
	    }


	    // Конструктор с параметрами - Используем конструктор Circle
	    Ellipse(double x, double y, double r1, double r2): Circle(x, y, r1), secondRadius(r2) {
	        ++totalCreated;
	        ++currentAlive;
	    }


	    // Площадь эллипса
	    double getArea() const {
	        return M_PI * radius * secondRadius;
	    }


	    // Приближённый периметр эллипса (формула Рамануджана)
	    double getPerimeter() const override {
	        double a = radius;
	        double b = secondRadius;
	        if (a < b) {
	            double temp = a;
	            a = b;
	            b = temp;
	        }
	        double h = (a - b) * (a - b) / ((a + b) * (a + b));
	        return M_PI * (a + b) * (1 + (3 * h) / (10 + sqrt(4 - 3 * h)));
	    }


	    // Ввод и вывод
	    void input() override {
	        Circle::input();
	        cout << "Введите вторую полуось: ";
	        cin >> secondRadius;
	    }
	    void output() const override {
	        Circle::output();
	        cout << ", Вторая полуось: " << secondRadius;
	    }


	    static int getTotalCreated() { return totalCreated; }
	    static int getCurrentAlive() { return currentAlive; }


	    // Деструктор
	    ~Ellipse() override {
	        --currentAlive;
	    }
};

int Ellipse::totalCreated = 0;
int Ellipse::currentAlive = 0;



int main() {
    srand(time(0));

    cout << "=== СОЗДАНИЕ ОБЪЕКТОВ ВСЕХ КЛАССОВ ===\n";
    Circle c1, c2(10, 20, 5);
    Line l1, l2(0, 0, 3, 4);
    Square sq1, sq2(0, 0, 2, 2);
    Rectangle r1, r2(1, 1, 4, 1, 3);
    Ellipse e1, e2(5, 5, 3, 2);

    cout << "\nПосле создания r1 и r2:\n";
    cout << "Всего создано объектов класса Rectangle: " << Rectangle::getTotalCreated() << "\n";
    cout << "Сейчас существует (живых): " << Rectangle::getCurrentAlive() << "\n";

    cout << "\n=== ОБЪЯВЛЕНИЕ УКАЗАТЕЛЯ (без создания объекта) ===\n";
    Rectangle* ptr = nullptr;
    cout << "Указатель объявлен, но объект не создан.\n";
    cout << "Количество Rectangle не изменилось:\n";
    cout << "Создано: " << Rectangle::getTotalCreated() << ", Живых: " << Rectangle::getCurrentAlive() << "\n";

    cout << "\n=== СОЗДАНИЕ ДИНАМИЧЕСКОГО ОБЪЕКТА Rectangle ===\n";
    Rectangle* dynRect = new Rectangle(0, 0, 1, 0, 2);
    cout << "Создан ещё один Rectangle через new.\n";
    cout << "Теперь:\n";
    cout << "Создано: " << Rectangle::getTotalCreated() << ", Живых: " << Rectangle::getCurrentAlive() << "\n";

    cout << "\n=== СОЗДАНИЕ МАССИВА ИЗ 4 РАЗНЫХ ФИГУР ===\n";
    Figure* figures[4] = {
        new Square(0, 0, 1, 1),
        new Rectangle(2, 2, 5, 2, 4),
        new Circle(1, 1, 3),
        new Ellipse(3, 3, 2, 1)
    };
    cout << "В массиве ТОЛЬКО ОДИН объект типа Rectangle (второй элемент).\n";
    cout << "Поэтому счётчик Rectangle увеличился на 1:\n";
    cout << "Создано: " << Rectangle::getTotalCreated() << ", Живых: " << Rectangle::getCurrentAlive() << "\n";

    cout << "\n=== ВЫВОД ПЕРИМЕТРОВ ВСЕХ ФИГУР В МАССИВЕ ===\n";
    for (int i = 0; i < 4; ++i) {
        cout << "Фигура " << (i+1) << " (";
        if (i == 0) cout << "Square";
        else if (i == 1) cout << "Rectangle";
        else if (i == 2) cout << "Circle";
        else cout << "Ellipse";
        cout << "): периметр = " << figures[i]->getPerimeter() << endl;
    }

    cout << "\n=== УДАЛЕНИЕ МАССИВА (все 4 объекта) ===\n";
    for (int i = 0; i < 4; ++i) {
        delete figures[i];
    }
    cout << "Удалён один Rectangle (из массива).\n";
    cout << "Теперь живых Rectangle на 1 меньше:\n";
    cout << "Создано: " << Rectangle::getTotalCreated() << ", Живых: " << Rectangle::getCurrentAlive() << "\n";

    cout << "\n=== УДАЛЕНИЕ ДИНАМИЧЕСКОГО ОБЪЕКТА ===\n";
    delete dynRect;
    cout << "Удалён ещё один Rectangle (dynRect).\n";
    cout << "Финальное состояние:\n";
    cout << "Создано: " << Rectangle::getTotalCreated() << ", Живых: " << Rectangle::getCurrentAlive() << "\n";

    return 0;
}
