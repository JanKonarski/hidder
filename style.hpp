#pragma once

#include <string>
#include <gtkmm/cssprovider.h>
#include <gtkmm/messagedialog.h>

class Style
{
	const std::string cssFile = std::string("../style.css");
	Glib::RefPtr<Gtk::CssProvider> css{nullptr};

	class Error : public::Gtk::MessageDialog {
	public:
		explicit Error(std::string message) :
			MessageDialog("CSS error", false, Gtk::MESSAGE_ERROR)
		{
			set_secondary_text(message);
			run();
		}
	};

public:
	template<class T>
	Style(T *t, std::string class_name, std::string class_name2 = "") {
		css = Gtk::CssProvider::create();

		try {
			css->load_from_path(cssFile);
		} catch( Gtk::CssProviderError &e) {
			Error error(e.what());
			exit(EXIT_FAILURE);
		}

		t->get_style_context()->add_provider_for_screen(Gdk::Screen::get_default(),
														css,
													    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		t->get_style_context()->add_class(class_name);
		t->get_style_context()->add_class(class_name2);
	}
};
