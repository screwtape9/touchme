#ifndef __TOUCH_IT_I_DARE_YOU_WIN_H_
#define __TOUCH_IT_I_DARE_YOU_WIN_H_

#include <memory>
#include <gtkmm.h>
#include <pangomm/fontdescription.h>

class MyWin : public Gtk::Window
{
public:
  MyWin(const int nBtns,
        const int nBtnsPerRow,
        const int btnWidth,
        const int btnHeight,
        const int width,
        const int height);
  virtual ~MyWin() { }

protected:
  void on_show();
  void OnBtnMsgClicked();
  void OnBtnQuitClicked();

  int screenWidth;
  int screenHeight;
  Pango::FontDescription font;
  Gtk::Fixed fixed;
  std::vector<std::unique_ptr<Gtk::Button> > btns;
};

#endif // __TOUCH_IT_I_DARE_YOU_WIN_H_
