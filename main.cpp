#include <gtkmm/main.h>

#include "window.hpp"

int main(int argc, char **argv) {
	Gtk::Main app(argc, argv);
	Window window;
	app.run(window);

	return EXIT_SUCCESS;
}
