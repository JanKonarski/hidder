#pragma once

#include <gtkmm/filechooserdialog.h>

class AudioChooser : public::Gtk::FileChooserDialog
{
public:
	Glib::RefPtr<Gtk::FileFilter> wavFilter;
	Glib::RefPtr<Gtk::FileFilter> aiffFilter;
	std::string filename;

	template<class Window>
	explicit AudioChooser(Window *window, std::string title, Gtk::FileChooserAction action) :
		Gtk::FileChooserDialog(title, action)
	{
		this->set_transient_for(*window);
		this->add_button("_Cancel", Gtk::RESPONSE_CANCEL);

		wavFilter = Gtk::FileFilter::create();
		wavFilter->set_name("WAVE audio file");
		wavFilter->add_mime_type("audio/wav");
		this->add_filter(wavFilter);

		aiffFilter = Gtk::FileFilter::create();
		aiffFilter->set_name("AIFF audio file");
		aiffFilter->add_mime_type("audio/aiff");
		this->add_filter(aiffFilter);
	}
};
