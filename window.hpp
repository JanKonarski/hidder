#pragma once

#include <gtkmm/box.h>
#include <gtkmm/window.h>

#include "style.hpp"
#include "frame.hpp"
#include "menubar.hpp"
#include "openaudio.hpp"
#include "saveaudio.hpp"
#include "bottombar.hpp"
#include "AudioFile.hpp"
#include "preferences.hpp"

class Window : public::Gtk::Window
{
public:
	Gtk::VBox mainLayout;
	MenuBar menubar = MenuBar(this);
	Frame frame = Frame(this);
	BottomBar bottomBar = BottomBar(this);

	AudioFile<float> audioFile;

	std::size_t hash;
	std::size_t size;
	std::vector<std::size_t> chanel;
	std::vector<std::size_t> sample;

	Window() {
		set_size_request(720, 560);
		set_default_icon_from_file("../icon.svg");

		Style(this, "window");

		add(mainLayout);

		mainLayout.pack_start(menubar, Gtk::PACK_SHRINK);
		mainLayout.pack_start(frame);
		mainLayout.pack_end(bottomBar, 0, 0);

		show_all();
	}

	void open_file() {
		OpenAudio(this);
		frame.seed->set_sensitive(true);
	}

	void save_file() { SaveAudio(this); }

	void close_file() {
//		delete audioFile;

		/* -code - */
	}

	void preferences() {
//		auto app = this->get_application();
//		app->signal_startup().connect([&]{
//			Preferences preferences(this);
//			app->add_window(preferences);
//		});
	} //TODO: fix

	void quite() { this->get_application()->quit(); }

	void help() {}

	void about() {}

	void opened() {

	}
};