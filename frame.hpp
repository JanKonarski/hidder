#pragma once
#include <iomanip>

#include <fstream>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/filechooserdialog.h>

#include "seed.hpp"
#include "style.hpp"
#include "button.hpp"
#include "plaintext.hpp"
#include "AudioFile.hpp"

class Frame : public::Gtk::Frame
{
	Gtk::VBox mainLayout;
	Gtk::HBox fileLayout;

public:
//	Seed seed = Seed(this);
	Seed *seed;
	Plaintext plaintext;
	Button hideText = Button(this, "hideText", "Hide text");
	Button hideFile = Button(this, "hideFile", "Hide file");
	Button unhideFile = Button(this, "unhideFile", "Unhide file");

	template<class Window>
	explicit Frame(Window *window) : Gtk::Frame() {
		Style(this, "frame");

		seed = new Seed(*window);

		this->add(mainLayout);
		mainLayout.pack_start(*seed, 0, 0);
		mainLayout.pack_start(plaintext);
		mainLayout.pack_start(hideText, 0, 0);

		mainLayout.pack_end(fileLayout, 0, 0);
		fileLayout.pack_start(hideFile);
		fileLayout.pack_end(unhideFile);

		hideText.signal_button_release_event().connect( [=](GdkEventButton *event)->bool {
			this->hide_frame(*window, 1);

			Glib::ustring text = this->plaintext.get_buffer()->get_text();

			std::size_t size = text.length();
			for (int i=0; i<64; i++) {
				bool bit = (size & (0b1<<i))>>i;

				std::size_t chanelNumber = window->chanel[i+65];
				std::size_t sampleNumber = window->sample[i+65];

				bool sign = false;
				float download = window->audioFile.samples[chanelNumber][sampleNumber];
				if (download < 0) {
					download *= -1;
					sign = true;
				}
				std::size_t sampel = download * 100000000;
				sampel = (sampel & ~0b1) | bit;
				float upload = (float)sampel /  100000000;
				if (sign)
					upload *= -1;
				window->audioFile.samples[chanelNumber][sampleNumber] = upload;
			}

			for (int i=0; i<text.length(); i++) {
				Glib::ustring::value_type character = text[i];
				for (int j=0; j<32; j++) {
					int offset = 129 + i*32;
					bool bit = (character & (0b1<<j))>>j;

					std::size_t chanelNumber = window->chanel[j+offset];
					std::size_t sampleNumber = window->sample[j+offset];

					bool sign = false;
					float download = window->audioFile.samples[chanelNumber][sampleNumber];
					if (download < 0) {
						download *= -1;
						sign = true;
					}
					std::size_t sampel = download * 100000000;
					sampel = (sampel & ~0b1) | bit;
					float upload = (float)sampel / 100000000;
					if (sign)
						upload *= -1;
					window->audioFile.samples[chanelNumber][sampleNumber] = upload;
				}
			}

			return false;
		});

		hideFile.signal_button_release_event().connect( [=](GdkEventButton *button)->bool {
			this->hide_frame(*window, 0);

			Gtk::FileChooserDialog dialog("Select file");
			dialog.set_transient_for(*window);
			dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
			dialog.add_button("_Open", Gtk::RESPONSE_OK);
			if( dialog.run() == Gtk::RESPONSE_CANCEL)
				return false;

			std::string filename = dialog.get_filename();
			std::ifstream file(filename, std::ios::binary);
			std::size_t k=0;
			char c;
			while (file.get(c)) {
				int offset = 129 + k*8;
				for (int i=0; i<8; i++) {
					bool bit = (c & (0b1<<i))>>i;

					std::size_t chanelNumber = window->chanel[i+offset];
					std::size_t sampleNumber = window->sample[i+offset];

					bool sign = false;
					float download = window->audioFile.samples[chanelNumber][sampleNumber];
					if (download < 0) {
						download *= -1;
						sign = true;
					}
					std::size_t sampel = download * 100000000;
					sampel = (sampel & ~0x1) | bit;
					float upload = (float)sampel / 100000000;
					if (sign)
						upload *= -1;
					window->audioFile.samples[chanelNumber][sampleNumber] = upload;
				}

				k++;
			}

			for (int i=0; i<64; i++) {
				bool bit = (k & (0b1<<i))>>i;

				std::size_t chanelNumber = window->chanel[i+65];
				std::size_t sampleNumber = window->sample[i+65];

				bool sign = false;
				float download = window->audioFile.samples[chanelNumber][sampleNumber];
				if (download < 0) {
					download *= -1;
					sign = true;
				}
				std::size_t sampel = download * 100000000;
				sampel = (sampel & ~0x1) | bit;
				float upload = (float)sampel / 100000000;
				if (sign)
					upload *= -1;
				window->audioFile.samples[chanelNumber][sampleNumber] = upload;
			}

			return false;
		});

		unhideFile.signal_button_release_event().connect( [=](GdkEventButton *event)->bool {
			Gtk::FileChooserDialog dialog("Save binary file", Gtk::FILE_CHOOSER_ACTION_SAVE);
			dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
			dialog.add_button("_Save", Gtk::RESPONSE_OK);
			if( dialog.run() == Gtk::RESPONSE_CANCEL)
				return false;

			std::size_t size = 0;
			for (int i=0; i<64; i++) {
				std::size_t chanelNumber = window->chanel[i+65];
				std::size_t sampleNumber = window->sample[i+65];
				float sizeData = window->audioFile.samples[chanelNumber][sampleNumber];
				if (sizeData < 0)
					sizeData *= -1;
				std::size_t sizeData2 = sizeData * 100000000;
				size |= (sizeData2 & 0b1)<<i;
			}

			std::string filename = dialog.get_filename();
			std::ofstream file(filename, std::ios::binary);

			for (int i=0; i<size; i++) {
				char c = 0;
				int offset = 129 + i*8;

				for(int j=0; j<8; j++) {
					std::size_t chanelNumber = window->chanel[j+offset];
					std::size_t sampleNumber = window->sample[j+offset];

					float download = window->audioFile.samples[chanelNumber][sampleNumber];
					if (download < 0)
						download *= -1;

					std::size_t charData = download * 100000000;
					c |= (charData & 0b1)<<j;
				}

				file.write(&c, 1);
			}

			return false;
		});
	}

	template<class Window>
	void hide_frame(Window &window, bool type) {
		std::size_t mask = 0b1;
		const std::size_t staticMask = 0b1;

		for (int i=0; i<64; i++) {
			bool sign = false;
			std::size_t chanelNumber = window.chanel[i];
			std::size_t sampleNumber = window.sample[i];

			float download = window.audioFile.samples[chanelNumber][sampleNumber];
			if (download < 0) {
				download *= -1;
				sign = true;
			}
			std::size_t sampel = download * 100000000;

			std::size_t bit = (window.hash & (mask<<i))>>i;
			sampel = (sampel & ~0b1) | bit;

			float upload = (float)sampel / 100000000;
			if (sign)
				upload *= -1;
			window.audioFile.samples[chanelNumber][sampleNumber] = upload;
		}

		bool sign = false;
		std::size_t chanelNumber = window.chanel[64];
		std::size_t sampleNumber = window.sample[64];
		float download = window.audioFile.samples[chanelNumber][sampleNumber];
		if (download < 0) {
			download *= -1;
			sign = true;
		}
		std::size_t sampel = download * 100000000;
		sampel = (sampel & ~0x1) | type;
		float upload = (float)sampel * 100000000;
		if (sign)
			upload *= -1;
		window.audioFile.samples[chanelNumber][sampleNumber] = upload;
	}
};
