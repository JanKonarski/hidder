#pragma once

#include <gtkmm/window.h>

#include "style.hpp"

class Preferences : public::Gtk::Window
{
public:
	template<class Window>
	Preferences(Window *window) {
		Style(this, "preferences");
	}
};
