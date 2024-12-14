#include "win.h"

MyWin::MyWin(const int numBtns,
             const int nBtnsPerRow,
             const int btnWidth,
             const int btnHeight,
             const int width,
             const int height)
  : font("Cantarell Normal Bold 40")
{
  set_title("Touch me...");
  
  if ((width < 0) || (height < 0)) {
    auto screen  = get_screen();
    screenWidth  = screen->get_width();
    screenHeight = screen->get_height();
    set_default_size(screenWidth, screenHeight);
  }
  else {
    screenWidth  = width;
    screenHeight = height;
  }

  add(fixed);

  int xPad = (screenWidth - (nBtnsPerRow * btnWidth)) / (nBtnsPerRow + 1);
  int nRows = (numBtns / nBtnsPerRow) + ((numBtns % nBtnsPerRow) ? 1 : 0);
  int yPad = (screenHeight - (nRows * btnHeight)) / (nRows + 1);

  int x = xPad, y = yPad;
  for (int i = 0; i < numBtns; ++i) {
    if (i && (!(i % nBtnsPerRow))) {
      x = xPad;
      y += (btnHeight + yPad);
    }

    std::unique_ptr<Gtk::Button> btn =
      std::unique_ptr<Gtk::Button>(new Gtk::Button(i ? "Click me!" : "Quit"));
    btn->get_child()->modify_font(font);
    btn->set_size_request(btnWidth, btnHeight);
    fixed.put((*btn), x, y);
    btn->signal_clicked().connect(sigc::mem_fun(*this,
                                                i ? &MyWin::OnBtnMsgClicked
                                                  : &MyWin::OnBtnQuitClicked));
    btns.push_back(std::move(btn));

    x += (btnWidth + xPad);
  }

  show_all();
}

void MyWin::on_show()
{
  Gtk::Window::on_show();
  move(0, 0);
}

void MyWin::OnBtnMsgClicked()
{
  char buf[256] = { '\0' };
  snprintf(buf, sizeof(buf), "%dx%d", screenWidth, screenHeight);

  Glib::ustring msg;
  try {
    msg = Glib::locale_to_utf8(buf);
  }
  catch (Glib::ConvertError const& err) {
    msg = err.what();
  }
  Gtk::MessageDialog dlg(*this, msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
  dlg.run();
}

void MyWin::OnBtnQuitClicked()
{
  hide();
}
