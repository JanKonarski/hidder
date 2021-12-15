#pragma once

#include <gtkmm/frame.h>
#include <gtkmm/label.h>

#include "style.hpp"

class BottomBar : public::Gtk::Frame
{
	std::string charSize = "Maximum plaintext size: ";
	std::string fileSize = "Maximum binary file size: ";

public:
	Gtk::Label label;

	template<class T>
	explicit  BottomBar(T *t) {
		Style(this, "bottomBar");

		add(label);
		set_size();
		label.set_alignment(Gtk::ALIGN_START);
		label.get_style_context()->add_class("bottomText");
	}

	void set_size(std::size_t size = 0) {
		label.set_text(
			charSize + (size == 0 ? "0" : std::to_string( (size - 129) / 32)) + " and " +
			fileSize + (size == 0 ? "0" : std::to_string( (size - 129) / 8192)) + "kB"
		);
	}
};
