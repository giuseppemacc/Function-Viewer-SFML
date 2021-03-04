#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <SFML\Graphics\Color.hpp>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <cmath>
using namespace std;
using namespace sf;
int window_H=64*15;
int window_W=64*15;
int border=50;
float W=window_W-(2*border);
float H=window_H-(2*border);
int size_=4;

int dim=size_*2;

double x_cartesian_to_global(double x){return border+(W/2.f)+(x*(W/dim));}
double y_cartesian_to_global(double y){return border+(H/2.f)-(y*(H/dim));}

void return_line(VertexArray& line,double m, double q){
    line[0].position=Vector2f(x_cartesian_to_global((dim/2.d)*-1),y_cartesian_to_global(m*((dim/2.d)*-1)+q));
    line[0].color=Color::Red;
    line[1].position=Vector2f(x_cartesian_to_global(dim/2.d),y_cartesian_to_global(m*(dim/2.d)+q));
    line[1].color=Color::Red;
}
void set_text(Text& text,Font& font,string stringa,float x,float y,Color color,int character_size){
    text.setFont(font);
    text.setColor(color);
    text.setString(stringa);
    text.setPosition(x,y);
    text.setCharacterSize(character_size);
}
void set_circle(CircleShape& circle,Color color,double x, double y,double radius){
    circle.setFillColor(color);
    circle.setRadius(radius);
    circle.setOrigin(radius,radius);
    circle.setPosition(x,y);
}
void set_grid(VertexArray& grid, Color color){
    int pos=0;
    float n=0;
    //Verticale//
    for(int i=0;i<=dim;i++){
        grid[pos].position=Vector2f(border+n,border);
        grid[pos].color=color;
        pos++;
        grid[pos].position=Vector2f(border+n,border+H);
        grid[pos].color=color;
        pos++;
        n=n+(H/dim);
    }
    //Orizzontale//
    n=0;
    for(int i=0;i<=dim;i++){
        grid[pos].position=Vector2f(border,border+n);
        grid[pos].color=color;
        pos++;
        grid[pos].position=Vector2f(border+W,border+n);
        grid[pos].color=color;
        pos++;
        n=n+(H/dim);
    }
}

void draw_circles_axis(RenderWindow& window,Color color){
    float n=0;
    CircleShape circle;
    //Verticale
    for(int i=0;i<=dim;i++){
        set_circle(circle,color,(H/2.f)+border,border+n,3.f);
        window.draw(circle);
        n=n+(H/dim);
    }
    //Orizzontale
    n=0;
    for(int i=0;i<=dim;i++){
        set_circle(circle,color,border+n,(H/2.f)+border,3.f);
        window.draw(circle);
        n=n+(H/dim);
    }
}
void draw_number_axis(RenderWindow& window,Color color,Font& font,int charcater_size){
    float n=0;
    Text text;
    //Verticale
    for(int i=0,j=size_;i<dim;i++,j--){
        set_text(text,font,to_string(j),(H/2.f)+border,border+n,color,charcater_size);
        window.draw(text);
        n=n+(H/dim);
    }
    //Orizzontale
    n=0;
    for(int i=0,j=size_*-1;i<dim;i++,j++){
        set_text(text,font,to_string(j),border+n,(H/2.f)+border,color,charcater_size);
        n=n+(H/dim);
        if(j!=0)
            window.draw(text);
    }
}

double example_function(double x){
    double y = sin(x);
    return y;
}

void draw_function(VertexArray& point){
    long double y=0;
    int n=0;
    for(double x=-size_;x<=size_;x=x+0.001){
        y=example_function(x);
        point[n].position=Vector2f(x_cartesian_to_global(x),y_cartesian_to_global(y));
        point[n].color=Color::Red;
        n++;
    }
}

int main(){

    RenderWindow window(VideoMode(window_W,window_H), " ");
    Font font;
    if (!font.loadFromFile("arial.ttf")){
        std::cerr << "error";
    }
    Color grey=Color(100,100,100,255);
    VertexArray point(Points, 10000000);
    VertexArray grid(Lines, 10000000);
    VertexArray line(Lines, 10000000);
    set_grid(grid,grey);
    long double Vm=0.5,f=0;
    while (window.isOpen()){

        draw_function(point);

        Event event;
        while (window.pollEvent(event)){
            if(event.type == Event::Closed)
                window.close();
        }
        window.clear(Color::White);
        draw_circles_axis(window,grey);
        draw_number_axis(window,Color::Blue,font,12);
        window.draw(grid);
        window.draw(point);
        window.display();
    }
    return 0;
}
