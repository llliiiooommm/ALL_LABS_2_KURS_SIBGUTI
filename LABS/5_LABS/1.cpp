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


		//Деструктор
	    virtual ~Figure() = default;
};



class Circle : public Figure{
	protected:
	    double radius;
	public:
		// Конструктор по умолчанию
	    Circle() : Figure() {
	        radius = 1 + rand() % 50;
	    }


	    // Конструктор с параметрами: Используем конструктор класса Figure
	    Circle(double x, double y, double r) : Figure(x, y), radius(r) {}


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


		// Деструктор
	    ~Circle() override = default;
};



class Line : public Figure{
	protected:
	    double x2, y2;
	    double length;

	    void updateLength() {
	        length = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
	    }

	public:
		// Конструктор по умолчанию
	    Line() : Figure() {
	        x2 = rand() % 100;
	        y2 = rand() % 100;
	        updateLength();
	    }


	    // Конструктор по умолчанию - Используем конструктор класса Figure
	    Line(double x1, double y1, double x2, double y2) : Figure(x1, y1), x2(x2), y2(y2) {
	        updateLength();
	    }


		// Расчёты
	    double getLength() const {
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


		// Деструктор
	    ~Line() override = default;
};



class Square : public Line{
	public:
		// Конструктор по умолчанию - используем конструктор по умолчанию из класса line
	    Square() : Line() {}


		// Конструктор с параметрами - используем конструктор класса Line
	    Square(double x1, double y1, double x2, double y2) : Line(x1, y1, x2, y2) {}


		// Расчёты
	    double getSide() const {
	        return length;
	    }
	    double getPerimeter() const {
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


		// Десттрукторы
	    ~Square() override = default;
};

class Rectangle : public Square {
	private:
	    double height;

	public:
		// Конструктор по умолчанию - используем конструктор класса Square
	    Rectangle() : Square() {
	        height = 1 + rand() % 50;
	    }


		// Консктруктор с параметрами - используем конструктор с параметрами класса Square
	    Rectangle(double x1, double y1, double x2, double y2, double h) : Square(x1, y1, x2, y2), height(h) {}


		// Расчёты
	    double getWidth() const {
	        return getSide();
	    }
	    double getPerimeter() const {
	        return 2 * (getWidth() + height);
	    }
	    double getArea() const {
	        return getWidth() * height;
	    }


	    // Ввод случайных значений (требование задания!)
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


		// Деструктор
	    ~Rectangle() override = default;
};



class Ellipse : public Circle {
	private:
	    double secondRadius;
	public:
		// Конструктор по умолчанию
	    Ellipse() : Circle() {
	        secondRadius = 1 + rand() % 50;
	    }


		// Конструктор с параметрами - Используем конструктор Circle
	    Ellipse(double x, double y, double r1, double r2): Circle(x, y, r1), secondRadius(r2) {}


		// Расчёты
	    double getArea() const {
	        return M_PI * radius * secondRadius;
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


	    // Деструктор
	    ~Ellipse() override = default;
};


int main() {
    srand(time(0));

    Circle c1;
    Circle c2(10, 20, 5);

    Line l1;
    Line l2(0, 0, 3, 4);

    Square sq1;
    Square sq2(0, 0, 2, 2);

    Rectangle r1;
    Rectangle r2(1, 1, 4, 1, 3);

    Ellipse e1;
    Ellipse e2(5, 5, 3, 2);

    // --- Линии: вычислить длину и вывести ---
    cout << "\n--- Линии ---\n";

    l1.output();
    cout << endl;
    l1.OutputLegth();

    l2.output();
    cout << endl;
    l2.OutputLegth();

    // --- Квадраты: периметр и площадь ---
    cout << "\n--- Квадраты ---\n";

    sq1.output();
    cout << endl;
    cout << "Периметр: " << sq1.getPerimeter() << ", Площадь: " << sq1.getArea() << endl;

    sq2.output();
    cout << endl;
    cout << "Периметр: " << sq2.getPerimeter() << ", Площадь: " << sq2.getArea() << endl;

    // --- Прямоугольники: периметр и площадь ---
    cout << "\n--- Прямоугольники ---\n";

    r1.output();
    cout << endl;
    cout << "Периметр: " << r1.getPerimeter() << ", Площадь: " << r1.getArea() << endl;

    r2.output();
    cout << endl;
    cout << "Периметр: " << r2.getPerimeter() << ", Площадь: " << r2.getArea() << endl;

    // --- Эллипсы: площадь ---
    cout << "\n--- Эллипсы ---\n";

    e1.output();
    cout << endl;
    cout << "Площадь: " << e1.getArea() << endl;

    e2.output();
    cout << endl;
    cout << "Площадь: " << e2.getArea() << endl;

    // --- Динамический массив из 3х прямоугольников ---
    Rectangle* rectArray = new Rectangle[3]{
        Rectangle(0, 0, 1, 0, 2),
        Rectangle(2, 2, 5, 2, 4),
        Rectangle(1, 3, 1, 6, 3)
    };

    cout << "\n--- Массив прямоугольников ---\n";
    for (int i = 0; i < 3; ++i) {
        rectArray[i].output();
        cout << endl;
        cout << "Периметр: " << rectArray[i].getPerimeter()
             << ", Площадь: " << rectArray[i].getArea() << endl;
    }

    delete[] rectArray;

    return 0;
}
