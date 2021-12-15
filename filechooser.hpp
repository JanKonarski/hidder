#pragma once

#include <fstream>

#include <gtkmm/filechooserdialog.h>

class FileChooser : public::Gtk::FileChooserDialog
{
public:
	std::string filename;

	template<class Window>
	FileChooser(Window window) :
		Gtk::FileChooserDialog()
	{

	}

	void open() {}

	void save() {}

};