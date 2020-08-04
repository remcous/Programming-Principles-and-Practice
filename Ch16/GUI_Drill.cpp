/*
    GUI_Drill.cpp

    Revision History:
*/

#include "../Libraries/std_lib_facilities.h"
#include "../Libraries/Simple_window.h"
#include "../Libraries/Graph.h"
#include "../Libraries/GUI.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

struct Lines_window : Graph_lib::Window{
    Lines_window(Point xy, int w, int h, const string& title);
private:
    // data:
    Open_polyline lines;

    // widgets:
    Button next_button; // add {next_x, next_y} to lines
    Button quit_button; // end program
    In_box next_x;
    In_box next_y;
    Out_box xy_out;
    Menu color_menu;
    Button color_menu_button;
    Menu style_menu;
    Button style_menu_button;

    void change(Color c){lines.set_color(c);}
    void change_style(Line_style l){lines.set_style(l);}

    void hide_menu(){color_menu.hide(); color_menu_button.show();
        style_menu.hide(); style_menu_button.show();}

    // actions invoked by callbacks:
    void red_pressed(){change(Color::red);redraw(); 
        hide_menu();}
    void blue_pressed(){change(Color::blue);redraw(); 
        hide_menu();}
    void black_pressed(){change(Color::black);redraw(); 
        hide_menu();}
    void color_menu_pressed(){color_menu_button.hide(); 
        color_menu.show();}
    void solid_pressed(){change_style(Line_style::solid);redraw(); 
        hide_menu();}
    void dash_pressed(){change_style(Line_style::dash);redraw(); 
        hide_menu();}
    void dot_pressed(){change_style(Line_style::dot);redraw(); 
        hide_menu();}
    void dashdot_pressed(){change_style(Line_style::dashdot);redraw(); 
        hide_menu();}
    void dashdotdot_pressed(){change_style(Line_style::dashdotdot);redraw(); 
        hide_menu();}
    void style_menu_pressed(){style_menu_button.hide();
        style_menu.show();}
    void next();
    void quit();

    // callback functions
    static void cb_red(Address, Address);       // callback for red button
    static void cb_blue(Address, Address);      // callback for blue button
    static void cb_black(Address, Address);     // callback for black button
    static void cb_color_menu(Address, Address);// callback for menu button
    static void cb_next(Address, Address);      // callback for next button
    static void cb_quit(Address, Address);      // callback for quit button
    static void cb_solid(Address, Address);     // callback for solid button
    static void cb_dash(Address, Address);      // callback for dash button
    static void cb_dot(Address, Address);       // callback for dot button
    static void cb_dashdot(Address, Address);   // callback for dashdot button
    static void cb_dashdotdot(Address, Address);// callback for dashdotdot button
    static void cb_style_menu(Address, Address);// callback for style_menu button    
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Lines_window win{Point{100,100}, 600, 400, "lines"};
        return gui_main();
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

/****************************************
*   FUNCTION DEFINITIONS - Lines_window
****************************************/

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    :Window{xy, w, h, title},
    next_button{Point{x_max()-150, 0}, 70, 20, "Next point",
        cb_next},
    quit_button{Point{x_max()-70, 0}, 70, 20, "Quit",
        cb_quit},
    next_x{Point{x_max()-320, 0}, 50, 20, "next x:"},
    next_y{Point{x_max()-210, 0}, 50, 20, "next y:"},
    xy_out{Point{100, 0}, 100, 20, "current (x,y):"},
    color_menu{Point{x_max()-70, 40}, 70, 20, Menu::vertical, "color"},
    color_menu_button{Point{x_max()-80, 30}, 80, 20, "Color menu", cb_color_menu},
    style_menu{Point{x_max()-70, 100}, 70, 20, Menu::vertical, "style"},
    style_menu_button{Point{x_max()-80, 100}, 80, 20, "Style menu", cb_style_menu}
{
    attach(next_button);
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    xy_out.put("no point");
    color_menu.attach(new Button{Point{0,0}, 0,0, "red", cb_red});
    color_menu.attach(new Button{Point{0,0}, 0,0, "blue", cb_blue});
    color_menu.attach(new Button{Point{0,0}, 0,0, "black", cb_black});
    attach(color_menu);
    color_menu.hide();
    attach(color_menu_button);
    style_menu.attach(new Button{Point{0,0}, 0,0, "-----", cb_solid});
    style_menu.attach(new Button{Point{0,0}, 0,0, "- - -", cb_dash});
    style_menu.attach(new Button{Point{0,0}, 0,0, ".....", cb_dot});
    style_menu.attach(new Button{Point{0,0}, 0,0, "-.-.-", cb_dashdot});
    style_menu.attach(new Button{Point{0,0}, 0,0, "-..-..", cb_dashdotdot});
    attach(style_menu);
    style_menu.hide();
    attach(style_menu_button);
    attach(lines);
}

void Lines_window::quit(){
    hide();     // curious FLTK idiom to delete window
}

void Lines_window::next(){
    int x = next_x.get_int();
    int y = next_y.get_int();

    lines.add(Point{x,y});

    // update current position readout:
    ostringstream ss;
    ss << "(" << x << "," << y << ")";
    xy_out.put(ss.str());

    redraw();
}

void Lines_window::cb_red(Address, Address pw){
    reference_to<Lines_window>(pw).red_pressed();
}

void Lines_window::cb_blue(Address, Address pw){
    reference_to<Lines_window>(pw).blue_pressed();
}

void Lines_window::cb_black(Address, Address pw){
    reference_to<Lines_window>(pw).black_pressed();
}

void Lines_window::cb_color_menu(Address, Address pw){
    reference_to<Lines_window>(pw).color_menu_pressed();
}

void Lines_window::cb_next(Address, Address pw){
    reference_to<Lines_window>(pw).next();
}

void Lines_window::cb_quit(Address, Address pw){
    reference_to<Lines_window>(pw).quit();
}

void Lines_window::cb_solid(Address, Address pw){
    reference_to<Lines_window>(pw).solid_pressed();
}

void Lines_window::cb_dash(Address, Address pw){
    reference_to<Lines_window>(pw).dash_pressed();
}

void Lines_window::cb_dot(Address, Address pw){
    reference_to<Lines_window>(pw).dot_pressed();
}

void Lines_window::cb_dashdot(Address, Address pw){
    reference_to<Lines_window>(pw).dashdot_pressed();
}

void Lines_window::cb_dashdotdot(Address, Address pw){
    reference_to<Lines_window>(pw).dashdotdot_pressed();
}

void Lines_window::cb_style_menu(Address, Address pw){
    reference_to<Lines_window>(pw).style_menu_pressed();
}

