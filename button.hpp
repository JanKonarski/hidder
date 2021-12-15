#pragma once

#include <gtkmm/button.h>

#include "style.hpp"

class Button : public::Gtk::Button
{
public:
	template<class Frame>
	Button(Frame *frame, std::string class_name, std::string label) :
		Gtk::Button(label)
	{
		Style(this, "button", class_name);

		this->set_sensitive(false);
	}
};