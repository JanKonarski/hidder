#pragma once

#include <gtkmm/textview.h>

#include "style.hpp"

// TODO: fix scrolling
class Plaintext : public::Gtk::TextView
{
public:
	Plaintext() {
		Style(this, "plaintext");

		this->set_sensitive(false);
	}
};
