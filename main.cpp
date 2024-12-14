#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <gtkmm.h>
#include "win.h"

extern const char *__progname;

static void usage(int status)
{
  std::cout << "Usage: "  << __progname << " [options]\n"
            << "Options:\n"
            << "  -h  Display this information.\n"
            << "  -d  Dimensions. Ex. 800x600. Default fullscreen.\n"
            << "  -n  Total number of buttons. Default 2.\n"
            << "  -r  Number of buttons per row. Default 3.\n"
            << "  -w  Button pixel width. Default 400.\n"
            << "  -j  Button pixel height. Default 200." << std::endl;
  _exit(status);
}

static void parseDimensions(std::string const& dim, int& width, int& height)
{
  std::string::size_type pos = dim.find('x');
  if ((pos != dim.npos) && (pos > 0) && (pos != (dim.length() - 1))) {
    try {
      width  = std::stoi(dim.substr(0, pos), nullptr, 10);
      height = std::stoi(dim.substr(++pos),  nullptr, 10);
      if ((width > 0) && (height > 0))
        return;
    }
    catch (std::exception const& ex) {
      std::cerr << ex.what() << '\n';
    }
  }
  std::cerr << "Invalid dimensions:  " << optarg << '.' << std::endl;
  _exit(EXIT_FAILURE);
}

static void parseInt(int& n, std::string const& optarg, const char *errmsg)
{
  try {
    n = std::stoi(optarg, nullptr, 10);
  }
  catch (std::exception const& ex) {
    std::cerr << ex.what() << '\n' << errmsg << std::endl;
    _exit(EXIT_FAILURE);
  }
}

static void GetOpts(int argc,
                    char *argv[],
                    int& numBtns,
                    int& btnsPerRow,
                    int& btnWidth,
                    int& btnHeight,
                    int& width,
                    int& height)
{
  int opt = 0;
  while ((opt = getopt(argc, argv, "hd:n:r:w:j:")) != -1) {
    switch (opt) {
    case 'h':
      usage(EXIT_SUCCESS);
      break;
    case 'd':
      parseDimensions(optarg, width, height);
      break;
    case 'n':
      parseInt(numBtns, optarg, "Invalid total number of buttons.");
      break;
    case 'r':
      parseInt(btnsPerRow, optarg, "Invalid number of buttons per row.");
      break;
    case 'w':
      parseInt(btnWidth, optarg, "Invalid button width.");
      break;
    case 'j':
      parseInt(btnHeight, optarg, "Invalid button height.");
      break;
    default:
      usage(EXIT_FAILURE);
      break;
    }
  }
}

int main(int argc, char *argv[])
{
  int nBtns = 2, nBtnsPerRow = 3, btnWidth = 400, btnHeight = 200, width = -1,
      height = -1;
  GetOpts(argc, argv, nBtns, nBtnsPerRow, btnWidth, btnHeight, width, height);
  Gtk::Main kit(argc, argv);
  MyWin win(nBtns, nBtnsPerRow, btnWidth, btnHeight, width, height);
  kit.run(win);
  return EXIT_SUCCESS;
}
