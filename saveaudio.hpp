#pragma once

#include "AudioFile.hpp"
#include "audiochooser.hpp"

class SaveAudio : public::AudioChooser
{
public:
	template<class Window>
	SaveAudio(Window *window) :
		AudioChooser(window, "Name", Gtk::FILE_CHOOSER_ACTION_SAVE)
	{
//		if( window->audioFile == nullptr)
//			return;

		this->add_button("_Save", Gtk::RESPONSE_OK);

		if( this->run() == Gtk::RESPONSE_CANCEL)
			return;

		filename = this->get_filename();
		if (this->get_filter() == this->wavFilter)
			window->audioFile.save(filename + ".wav", AudioFileFormat::Wave);
		else
			window->audioFile.save(filename + ".aiff", AudioFileFormat::Aiff);
	}
};
