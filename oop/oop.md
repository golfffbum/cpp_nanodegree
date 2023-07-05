# Structs
Structures are "user-defined" types

Generally, we want to avoid instantiating an object with undefined members. Ideally, we would like all members of an object to be in a valid state once the object is instantiated.
struct Date {
  int day{1};
  int month{1};
  int year{0};
};

# Access Modifiers 
By default members are public
- can update values of members

Public members can be changed directly, by any user of the object, whereas private members can only be changed by the object itself.
struct Date {
 private:
  int day{1};
  int month{1};
  int year{0};
};

To access private members, we typically define public "accessor" and "mutator" member functions (sometimes called "getter" and "setter" functions).
```
struct Date {
 public:
  int Day() { return day; }
  void Day(int day) { this.day = day; }
  int Month() { return month; }
  void Month(int month) { this.month = month; }
  int Year() { return year; }
  void Year(int year) { this.year = year; }

 private:
  int day{1};
  int month{1};
  int year{0};
};
```

Sometimes accessors are not necessary, or even advisable. The C++ Core Guidelines recommend, "A trivial getter or setter adds no semantic value; the data item could just as well be public."

# Invariants
An "invariant" is a rule that limits the values of member variables.
For example, in a Date class, an invariant would specify that the member variable day cannot be less than 0. Another invariant would specify that the value of day cannot exceed 28, 29, 30, or 31, depending on the month and year. Yet another invariant would limit the value of month to the range of 1 to 12.

# 
if you are just carying publically accessed data and none of them interact then a struct is ok
if wanting prvate values or invariants then good ot convert to a class

By convention, programmers use structures when member variables are independent of each other, and use classes when member variables are related by an "invariant".

By default, all members of a struct default to public, whereas all members of a class default to private
```cpp
class Date {
 public:
  int Day() { return day; }
  void Day(int d) {
    if (d >= 1 && d <= 31) day_ = d;
  }

 private:
  int day_{1};
  int month_{1};
  int year_{0};
};
```
As a general rule, member data subject to an invariant should be specified private, in order to enforce the invariant before updating the member's value.

# Encapsulation and Abstraction
encapsulation, 
- bundle related properties together in a single class and protect from modication
abstraction, 
- users of class only need to be familiar with the interface we provide, dont need to know how we store or implement 
- hides the details of how we work with this data 

# Constructor 
- no complex logic, hard to debug
- init variables
```cpp
  Date(int d, int m, int y) {  // This is a constructor.
    Day(d);
  }
  ```

  # Scope
  C++ allows different identifiers (variable and function names) to have the same name, as long as they have different scope. For example, two different functions can each declare the variable int i, because each variable only exists within the scope of its parent function.

  - use scope resolution to define costructor outside class definition
  - "::" is the scope resolution operator, specify which namespace or class to search in order to resolve an identifier.
```
Person::move(); \\ Call the move the function that is a member of the Person class.
std::map m; \\ Initialize the map container from the C++ Standard Library.  
```

This becomes particularly useful if we want to separate class declaration from class definition.

```cpp
class Date {
 public:
  int Day() const { return day; }
  void Day(int day);  // Declare member function \
...
};

// Define member function Date::Day().
void Date::Day(int day) {
  if (day >= 1 && day <= 31) Date::day = day;
}
```

## Namespaces
Namespaces allow programmers to group logically related variables and functions together
```cpp
namespace English {
void Hello() { std::cout << "Hello, World!\n"; }
}  // namespace English

namespace Spanish {
void Hello() { std::cout << "Hola, Mundo!\n"; }
}  // namespace Spanish

int main() {
  English::Hello();
  Spanish::Hello();
}
```

# Initialzer Lists
initialize member variables to specific values, just before the class constructor runs.
```cpp
class Day{
    public: 
        Day(int day, int month, int year)

    private:
        int day;
        int month;
        int year;
}
Date::Date(int day, int month, int year) : year_(y) {}
```

 This is why class member variables can be declared const, but only if the member variable is initialized through an initialization list. Trying to initialize a const class member within the body of the constructor will not work.

## Constructor optimization
Initializer lists exist for a number of reasons.
- the compiler can optimize initialization faster from an initialization list than from within the constructor.
A second reason is a bit of a technical paradox. If you have a const class attribute, you can only initialize it using an initialization list.

```cpp
struct Person {
public:
  Person(const std::string & n) : name(n){} //{} contructor is empty because we are just using the initializer list
  std::string const name;
};
// Test
int main() {
  Person alice("Alice");
  Person bob("Bob");
  assert(alice.name != bob.name);
}
```

# Encapsulation

 method() const; //wont change the state of an object of the class
```cpp
#include <cassert>

class Date {
public:
  Date(int day, int month, int year);
  int Day() const { return day_; }
  void Day(int day);
  int Month() const { return month_; }
  void Month(int month);
  int Year() const { return year_; }
  void Year(int year);

private:
  int day_{1};
  int month_{1};
  int year_{0};
  int NumberOfDays(int month, int year);
};

int Date::NumberOfDays(int month, int year){
      int days = 31;
      
      if (month == 2)
      {
          if (year % 4)
          {
              days = 29;
          }
          else
          {
              days = 28;
          }
      }
      else if( month == 4 || month == 6 || month == 9 || month == 11)
      {
          days = 30;
      }

      return days;
}
Date::Date(int day, int month, int year) {
  Year(year);
  Month(month);
  Day(day);
}

void Date::Day(int day) {
  if (day >= 1 && day <= NumberOfDays(Month(), Year()))
    day_ = day;
}

```


## Accessor Functions 
typically marked as constant, Accessor functions are public member functions that allow users to access an object's data
```cpp
class BankAccount
{
  private:
      // Class attributes:
      
      long int number;
      std::string owner;
      float amount;

  public:
      // Set  methods:
      void setNumber(long int number);
      void setOwner(std::string owner);
      void setAmount(float amount);
      // Get methods:
      long int getNumber() const;
      std::string getOwner() const;
      float getAmount() const;
};
```

## Class example
```cpp
class Pyramid {
 public:
  // constructor
  Pyramid(int length, int width, int height)
      : length_(length), width_(width), height_(height) {
    Validate();
  }

  // accessors
  int Length() const { return length_; }
  int Width() const { return width_; }
  int Height() const { return height_; }

  // mutators
  void Length(int length) {
    length_ = length;
    Validate();
  }
  void Width(int width) {
    width_ = width;
    Validate();
  }
  void Height(int height) {
    height_ = height;
    Validate();
  }

  // public Volume() function
  float Volume() const { return Length() * Width() * Height() / 3.0; }

  // private class members
 private:
  int length_;
  int width_;
  int height_;
  void Validate() {
    if (length_ <= 0 || width_ <= 0 || height_ <= 0)
      throw std::invalid_argument("negative dimension");
  }
};
```

## Exceptions 
```cpp

  void Validate()
  {
      if (grade_ < 0 || grade_ > 12 ||  gpa_ < 0.0 || gpa_ > 4.0)
      {
          throw std::invalid_argument("invalid");
      }
  }

};

// TODO: Test
int main() {
    Student student("name", 5, 3.0);
    assert(student.Name() == "name");
    assert(student.Grade() == 5);
    assert(student.Gpa() == 3.0);
    
    bool caught{false};
    try {
        student.Grade(20);
    }
    catch(...) {
        caught = true;
    }
    assert(caught);
}
```

# Abstraction
Abstraction refers to the separation of a class's interface from the details of its implementation. The interface provides a way to interact with an object, while hiding the details and implementation of how the class works.


# Static
static means that the member belongs to the entire class, instead of to a specific instance of the class. More specifically, a static member is created only once and then shared by all instances (i.e. objects) of the class. 

?That means that if the static member gets changed, either by a user of the class or within a member function of the class itself, then all members of the class will see that change the next time they access the static member.

static members are declared within their class (often in a header file) but in most cases they must be defined within the global scope. That's because memory is allocated for static variables immediately when the program begins, at the same time any global variables are initialized.
```cpp
#include <cassert>

class Foo {
 public:
  static int count;
  Foo() { Foo::count += 1; }
};

int Foo::count{0};

int main() {
  Foo f{};
  assert(Foo::count == 1);
}
```

An exception to the global definition of static members is if such members can be marked as constexpr. In that case, the static member variable can be both declared and defined within the class definition:
```cpp
struct Kilometer {
  static constexpr int meters{1000};
};
```

## static methods 
Just like static member variables, static member functions are instance-independent: they belong to the class, not to any particular instance of the class.

# Polymorphism and Inheritance 
- Public inheritance: the public and protected members of the base class listed after the specifier keep their member access in the derived class
- Protected inheritance: the public and protected members of the base class listed after the specifier are protected members of the derived class
- Private inheritance: the public and protected members of the base class listed after the specifier are private members of the derived class

Examples:
```cpp
// This example demonstrates the privacy levels
// between parent and child classes
#include <iostream>
#include <string>
using std::string;

class Vehicle {
public:
    int wheels = 0;
    string color = "blue";
    
    void Print() const
    {
        std::cout << "This " << color << " vehicle has " << wheels << " wheels!\n";
    }
};

class Car : protected Vehicle {
public:
    bool sunroof = false;
};

class Bicycle : private Vehicle {
public:
    bool kickstand = true;
};

class Scooter : public Vehicle {
public:
    bool electric = false;
};

int main() 
{
    Car car;
    Bicycle bicycle;
    Scooter scooter;
    int w = car.wheels; //protected; not accessible
    int w2 = bicycle.wheels; //private; not accesible
    int w3 = scooter.wheels; //public; accesible 
};

```

# Composition
is a closely related alternative to inheritance. Composition involves constructing ("composing") classes from other classes, instead of inheriting traits from a parent class.
 "has a" versus "is a".
 From the standpoint of composition, a cat "has a" head and "has a" set of paws and "has a" tail.

From the standpoint of inheritance, a cat "is a" mammal.

 if a class needs only extend a small amount of functionality beyond what is already offered by another class, it makes sense to inherit from that other class. However, if a class needs to contain functionality from a variety of otherwise unrelated classes, it makes sense to compose the class from those other classes.

 ```cpp

#include <iostream>
#include <cmath>
#include <assert.h>
#define PI 3.1415 //define PI using a macro 

// Define Line Class
class LineSegment{
  public:
    double length;
};
    
// Define Circle subclass using composition
class Circle{
public:
    Circle(LineSegment& r) : radius(r){};

    double Area(){
        return pow(radius.length,2) * PI;
    };
private:
    LineSegment& radius;
};
    
// Test in main()
int main() 
{
    LineSegment radius {3};
    Circle circle(radius);
    assert(int(circle.Area()) == 28);
}
 ```

# Friend Class
classes provide an alternative inheritance mechanism to derived classes. The main difference between classical inheritance and friend inheritance is that a friend class can access private members of the base class, which isn't the case for classical inheritance. In classical inheritance, a derived class can only access public and protected members of the base class.
```cpp
// Example solution for Rectangle and Square friend classes
#include <assert.h>

// Declare class Rectangle
class Rectangle;

// Define class Square as friend of Rectangle
class Square {
// Add public constructor to Square, initialize side
public:
    Square(int s) : side(s) {}

private:
    // Add friend class Rectangle
    friend class Rectangle;
    // Add private attribute side to Square
    int side;
};

// Define class Rectangle
class Rectangle {
// Add public functions to Rectangle: area() and convert()
public:
    Rectangle(const Square& a);
    int Area() const;

private:
    // Add private attributes width, height
    int width {0};
    int height {0};
};

 // Define a Rectangle constructor that takes a Square
Rectangle::Rectangle(const Square& a) : width(a.side), height(a.side) //Because rectangle is a friend of square it can access squares private member variable side 
{
}

// Define Area() to compute area of Rectangle
int Rectangle::Area() const
{
    return width * height;
}
// Update main() to pass the tests
int main()
{
    Square square(4);
    Rectangle rectangle(square);
    assert(rectangle.Area() == 16); 
}
```

# Polymorphism
means "assuming many forms".

 a paradigm in which a function may behave differently depending on how it is called. In particular, the function will perform differently based on its inputs. Polymorphism can be achieved in two ways in C++: overloading and overriding. 

 Overloading requires that we leave the function name the same, but we modify the function signature. For example, we might define the same function name with multiple different configurations of input arguments.

```cpp
#include <iostream>

class Human {};
class Dog {};
class Cat {};

void hello() { std::cout << "Hello, World!\n"; }

// Overload hello() three times
void hello(Human human) { std::cout << "Hello, Human!\n"; }
void hello(Dog dog) { std::cout << "Hello, Dog!\n"; }
void hello(Cat cat) { std::cout << "Hello, Cat!\n"; }

// TODO: Call hello() from main()
int main()
{
    hello();
    hello(Human());
    hello(Dog());
    hello(Cat());
}
```

# Operator Overloading
You can choose any operator from the ASCII table and give it your own set of rules!

Operator overloading can be useful for many things. Consider the + operator. 
In order to overload an operator, use the operator keyword in the function signature:
```cpp
#include <assert.h>

class Point {
public:
  Point(int x = 0, int y = 0) : x(x), y(y) {}

  // Define + operator overload
  Point operator+(const Point& addend) {
    Point sum;
    sum.x = x + addend.x;
    sum.y = y + addend.y;
    return sum;
  }

  // Declare attributes x and y
  int x, y;
};

// Test in main()
int main() {
  Point p1(10, 5), p2(2, 4);
  Point p3 = p1 + p2; // An example call to "operator +";
  assert(p3.x == p1.x + p2.x);
  assert(p3.y == p1.y + p2.y);
}
```

# Virtual Functions
Virtual functions are a polymorphic feature. These functions are declared (and possibly defined) in a base class, and can be overridden by derived classes.

A pure virtual function is a virtual function that the base class declares but does not define.

A pure virtual function has the side effect of making its class abstract. This means that the class cannot be instantiated. 

```cpp
 class Animal {
    virtual void Talk() const = 0; // = 0 means pure virtual function, means it is purely abstract and cant create classes of type animal
  };

 class Human : public Animal {
  public:
    void Talk() const { //will error if you dont define this method 
      std::cout << "Hello\n";
    }
 };

```
# Polymorphism: Overriding
1. A base class declares a virtual function
2. A derived class overrides that virtual function by defining its own implementation with an identical function signature (i.e. the same function name and argument types).

```cpp
class Animal {
public:
  virtual std::string Talk() const = 0;
};

class Cat {
public:
  std::string Talk() const { return std::string("Meow"); }
};
```
In this example, Animal exposes a virtual function: Talk(), but does not define it. Because Animal::Talk() is undefined, it is called a pure virtual function, as opposed to an ordinary virtual function.

Furthermore, because Animal contains a pure virtual function, the user cannot instantiate an object of type Animal. This makes Animal an abstract class.

Cat, however, inherits from Animal and overrides Animal::Talk() with Cat::Talk(), which is defined. Therefore, it is possible to instantiate an object of type Cat.

# Function Hiding
Function hiding is closely related, but distinct from, overriding.

A derived class hides a base class function, as opposed to overriding it, if the base class function is not specified to be virtual.

```cpp
class Cat { // Here, Cat does not derive from a base class
public:
  std::string Talk() const { return std::string("Meow"); }
};

class Lion : public Cat {
public:
  std::string Talk() const { return std::string("Roar"); }
};
```
In this example, Cat is the base class and Lion is the derived class. Both Cat and Lion have Talk() member functions.

When an object of type Lion calls Talk(), the object will run Lion::Talk(), not Cat::Talk().

In this situation, Lion::Talk() is hiding Cat::Talk(). If Cat::Talk() were virtual, then Lion::Talk() would override Cat::Talk(), instead of hiding it. Overriding requires a virtual function in the base class.


# Override 
"Overriding" a function occurs when a derived class defines the implementation of a virtual function that it inherits from a base class.

It is possible, but not required, to specify a function declaration as override.

Specifying a function as override is good practice, as it empowers the compiler to verify the code, and communicates the intention of the code to future users.


```cpp
class Shape {
public:
  virtual double Area() const = 0;
  virtual double Perimeter() const = 0;
};

class Circle : public Shape {
public:
  Circle(double radius) : radius_(radius) {}
  double Area() const override { return pow(radius_, 2) * PI; } // specified as an override function
  double Perimeter() const override { return 2  *radius_*  PI; } // specified as an override function

private:
  double radius_;
};
```

# Multiple Inheritance
In this exercise, you'll get some practical experience with multiple inheritance. If you have class Animal and another class Pet, then you can construct a class Dog, which inherits from both of these base classes. In doing this, you are able to incorporate attributes of multiple base classes.

The Core Guidelines have some worthwhile recommendations about how and when to use multiple inheritance:

Use multiple inheritance to represent multiple distinct interfaces[http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c136-use-multiple-inheritance-to-represent-the-union-of-implementation-attributes]
Use multiple inheritance to represent the union of implementation attributes[http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c135-use-multiple-inheritance-to-represent-multiple-distinct-interfaces]

# Templates
Templates enable generic programming by generalizing a function to apply to any class. Specifically, templates use types as parameters so that the same implementation can operate on different data types.

For example, you might need a function to accept many different data types. Rather than writing and maintaining the multiple function declarations, each accepting slightly different arguments, you can write one function and pass the argument types as parameters.
```cpp
template <typename Type> Type Sum(Type a, Type b) { return a + b; }

int main() { std::cout << Sum<double>(20.0, 13.7) << "\n"; }
std::cout << Sum<char>(‘Z’, ’j’) << "\n";
```



```cpp

```

```cpp

```