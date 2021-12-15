#pragma once

#include "AudioFile.hpp"
#include "audiochooser.hpp"

class OpenAudio : public::AudioChooser
{
public:
	template<class Window>
	OpenAudio(Window *window) :
		AudioChooser(window, "Select file", Gtk::FILE_CHOOSER_ACTION_OPEN)
	{
		this->add_button("_Open", Gtk::RESPONSE_OK);

		if( this->run() == Gtk::RESPONSE_CANCEL)
			return;

		filename = this->get_filename();
		window->audioFile = AudioFile<float>();
		if( !window->audioFile.load(filename)) {
//			delete window->audioFile;
//			window->audioFile = nullptr;
			return;
		}
		window->audioFile.setBitDepth(32);
		window->opened();
	}
};
