//
// Created by 周庆 on 2019-05-26.
//

#ifndef C___SCREEN_H
#define C___SCREEN_H

#include <string>
#include <vector>

class Screen;

class Window_mgr{
public:
    Window_mgr();
    using screen_index = std::vector<Screen>::size_type ;
    void clear(screen_index i);

private:
    std::vector<Screen> screens;
};

class Screen{
    friend void Window_mgr::clear(screen_index i);

public:
    using pos = std::string::size_type ;
    using content_type = char ;

    Screen() = default;
    Screen(pos ht, pos wd): height(ht), width(wd), contents(ht * wd, ' ') {}
    Screen(pos ht, pos wd, content_type c): height(ht), width(wd), contents(ht * wd, c) {}

    const content_type &get() const { return contents[cursor];}
    const content_type &get(pos row, pos col) const;

    Screen set(content_type c);
    Screen set(pos row, pos col, content_type c);

    Screen move(pos row, pos col);

    const Screen display(std::ostream &os) const { do_display(os); return *this;}
    Screen display(std::ostream &os) { do_display(os); return *this;}

private:
    void do_display(std::ostream &os) const;

    pos cursor = 0;
    pos width = 0;
    pos height = 0;
    std::string contents;
};

inline
const Screen::content_type &Screen::get(Screen::pos row, Screen::pos col) const {
    return contents[row * width + col];
}

inline
Screen Screen::set(Screen::content_type c) {
    contents[cursor] = c;
    return *this;
}

inline
Screen Screen::set(Screen::pos row, Screen::pos col, Screen::content_type c) {
    contents[row * width + col] = c;
    return *this;
}

inline
Screen Screen::move(Screen::pos row, Screen::pos col) {
    cursor = row * width + col;
    return *this;
}

inline
void Screen::do_display(std::ostream &os) const {
    //os << contents;
    for (pos i = 0; i != contents.size(); ++i) {
        os << contents[i];
        if ((i + 1) % width == 0 && i + 1 != contents.size())
            os << "\n";
    }
}

Window_mgr::Window_mgr() : screens{Screen(24, 80, ' ')} {}

void Window_mgr::clear(Window_mgr::screen_index i) {
    Screen &s = screens[i];
    s.contents = std::string(s.width * s.height, ' ');
}

#endif //C___SCREEN_H
