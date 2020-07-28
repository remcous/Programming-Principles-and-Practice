/*
    GraphicsClassDrill.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"
#include <cstdlib>
#include <ctime>

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define WIDTH 1000
#define HEIGHT 800

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Point tl{0,0};

        Simple_window win{tl, WIDTH, HEIGHT, "Chapter 13 - Graphics Classes Drill"};

        constexpr int x_size = 800;
        constexpr int y_size = 800;
        constexpr int space = 100;

        Lines grid;
        for(int x=0; x<=x_size; x+=space)
            grid.add(Point{x,0}, Point{x,x_size});  // Vertical lines
        for(int y=0; y<=y_size; y+=space)
            grid.add(Point{0,y}, Point{y_size,y});  // Horizontal lines
        grid.set_color(Color::black);

        bool valid_point[x_size/space][y_size/space];
        for(int x=0; x<x_size/space; x++){
            for(int y=0; y<y_size/space; y++){
                valid_point[x][y] = true;
            }
        }

        Vector_ref<Rectangle> rects;
        for(int i=0; i< x_size/space; i++){
            rects.push_back(new Rectangle{Point{i*space,i*space},space,space});
            rects[rects.size()-1].set_fill_color(Color::red);
            rects[rects.size()-1].set_color(Color::invisible);
            win.attach(rects[rects.size()-1]);

            valid_point[i][i] = false;
        }

        Image im1{Point{2*space,0}, "89303.gif"};
        valid_point[2][0] = false; valid_point[3][0] = false;
        valid_point[2][1] = false; valid_point[3][1] = false;

        Image im2{Point{5*space,space}, "89303.gif"};
        valid_point[5][1] = false; valid_point[6][1] = false;
        valid_point[5][2] = false; valid_point[6][2] = false;
        
        Image im3{Point{space,4*space}, "89303.gif"};
        valid_point[1][4] = false; valid_point[2][4] = false;
        valid_point[1][5] = false; valid_point[2][5] = false;

        win.attach(grid);
        win.attach(im1);
        win.attach(im2);
        win.attach(im3);

        Image mobile{Point{space,0}, "sponge.gif"};
        int cur_x = 1, cur_y = 0;
        win.attach(mobile);

        srand(time(NULL));
        
        while(true){
            static int tar_x, tar_y;
            tar_x = rand() % 8;
            tar_y = rand() % 8;

            if(!valid_point[tar_x][tar_y]) continue;
            mobile.move((tar_x-cur_x)*space, (tar_y-cur_y)*space);
            cur_y = tar_y;
            cur_x = tar_x;
            win.attach(mobile);

            win.wait_for_button();
        }
    }
    catch(exception& e){
        cerr << e.what() << '\n';
        keep_window_open("~~");
        return 1;
    }
    catch(...){
        cerr << "exception\n";
        keep_window_open("~~");
        return 2;
    }
    return 0;
}