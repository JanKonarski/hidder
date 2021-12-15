#pragma once

#include <algorithm>
#include <set>
#include <gtkmm/entry.h>

#include "style.hpp"
#include "process.hpp"

class Seed : public::Gtk::Entry
{
public:
	Seed() {}

	template<class Window>
	explicit Seed(Window &window) : Gtk::Entry() {
		Style(this, "seed");

		this->set_placeholder_text("Seed");
		this->set_sensitive(false);

		this->signal_key_release_event().connect( [&](GdkEventKey *event) -> bool {
			if( this->get_text_length() == 0)
				return false;

			window.hash = std::hash<std::string>()(this->get_text());

			srand(window.hash);

			window.size = (rand() % window.audioFile.getNumSamplesPerChannel()) / 10;

			window.chanel = std::vector<std::size_t>();
			while( window.chanel.size() < window.size)
				window.chanel.push_back( rand() % window.audioFile.getNumChannels());

			std::set<std::size_t> setSample;
			while( setSample.size() < window.size)
				setSample.insert(rand() % window.audioFile.getNumSamplesPerChannel());
			window.sample = std::vector<std::size_t>(setSample.begin(), setSample.end());

			(Process(window));

			return false;
		});
	}
};
