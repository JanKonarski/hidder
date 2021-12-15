#pragma once

#include <cmath>
#include <bitset>
#include <iostream>

class Process {
public:


	template<class Window>
	explicit Process(Window &window) {
		window.bottomBar.set_size( window.size);

		if (this->exists(window)) {
			// data exists
			bool type;
			std::size_t chanelNumber = window.chanel[64];
			std::size_t sampleNumber = window.sample[64];
			float typeData = window.audioFile.samples[chanelNumber][sampleNumber];
			if (typeData < 0)
				typeData *= -1;
			std::size_t typeData2 = typeData * 100000000;
			type = typeData2 & 0b1;

			std::size_t size = 0;
			for (int i=0; i<64; i++) {
				std::size_t chanelNumber = window.chanel[i+65];
				std::size_t sampleNumber = window.sample[i+65];
				float sizeData = window.audioFile.samples[chanelNumber][sampleNumber];
				if (sizeData < 0)
					sizeData *= -1;
				std::size_t sizeData2 = sizeData * 100000000;
				size |= (sizeData2 & 0b1)<<i;
			}

			if (!type) {
				Glib::ustring text;

				for (int i=0; i<size; i++) {
					Glib::ustring::value_type character = 0;
					int offset = 129 + i*32;
					for (int j=0; j<32; j++) {
						std::size_t chanelNumber = window.chanel[j+offset];
						std::size_t sampleNumber = window.sample[j+offset];
						float download = window.audioFile.samples[chanelNumber][sampleNumber];
						if (download < 0)
							download *= -1;
						std::size_t charData = download * 100000000;
						character |= (charData & 0b1)<<j;
					}
					text += character;
				}
				window.frame.plaintext.get_buffer()->set_text(text);
			}
			else {
				std::cout << "test" << std::endl;
				window.frame.unhideFile.set_sensitive(true);
			}
			window.frame.unhideFile.set_sensitive(true);
		}
		else {
			// data does not exists
			window.frame.plaintext.set_sensitive(true);
			window.frame.hideText.set_sensitive(true);
			window.frame.hideFile.set_sensitive(true);
		}
	}

private:
	template<class Window>
	bool exists(Window &window) {
		std::size_t hash = 0;
		const std::size_t staticMask = 0b1;

		for( int i=0; i<64; ++i) {
			std::size_t chanelNumber = window.chanel[i];
			std::size_t sampleNumber = window.sample[i];

			float tmp = window.audioFile.samples[chanelNumber][sampleNumber];
			if (tmp < 0)
				tmp *= -1;
			std::size_t sampel = tmp * 100000000;

			std::size_t bit = sampel & staticMask;
			hash |= bit<<i;
		}
		return window.hash == hash;
	}
};