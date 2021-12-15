#pragma once

#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>
#include <gtkmm/menuitem.h>

class MenuBar : public::Gtk::MenuBar
{
	Gtk::MenuItem fileItem = Gtk::MenuItem("File");
	Gtk::Menu fileSubmenu;
	Gtk::MenuItem openSubItem = Gtk::MenuItem("Open");
	Gtk::MenuItem saveSubItem = Gtk::MenuItem("Save");
	Gtk::MenuItem closeSubItem = Gtk::MenuItem("Close");
	Gtk::MenuItem prefSubItem = Gtk::MenuItem("Preferences");
	Gtk::MenuItem quitSubItem = Gtk::MenuItem("Quit");

	Gtk::MenuItem helpItem = Gtk::MenuItem("Help");
	Gtk::Menu helpSubmenu;
	Gtk::MenuItem helpSubItem = Gtk::MenuItem("Help");
	Gtk::MenuItem aboutSubItem = Gtk::MenuItem("About");

public:
	template<class Window>
	explicit MenuBar(Window *window) {
		add(fileItem);
		fileItem.set_submenu(fileSubmenu);
		fileSubmenu.add(openSubItem);
		openSubItem.signal_activate().connect(sigc::mem_fun(window, &Window::open_file));
		fileSubmenu.add(saveSubItem);
		saveSubItem.signal_activate().connect(sigc::mem_fun(window, &Window::save_file));
		fileSubmenu.add(closeSubItem);
		closeSubItem.signal_activate().connect(sigc::mem_fun(window, &Window::close_file));
		fileSubmenu.add(prefSubItem);
		prefSubItem.signal_activate().connect(sigc::mem_fun(window, &Window::preferences));
		fileSubmenu.add(quitSubItem);
		quitSubItem.signal_activate().connect(sigc::mem_fun(window, &Window::quite));

		add(helpItem);
		helpItem.set_submenu(helpSubmenu);
		helpSubmenu.add(helpSubItem);
		helpSubItem.signal_activate().connect(sigc::mem_fun(window, &Window::help));
		helpSubmenu.add(aboutSubItem);
		aboutSubItem.signal_activate().connect(sigc::mem_fun(window, &Window::about));
	}
};
