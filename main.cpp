#include <iostream>


#include "wavstream.h"
#include "soundplayer.h"
#include <alsa/asoundlib.h>
#include <stdio.h>


int main(int argc, char *argv[])
{

    const char *file = argc > 1 ? argv[1]: "/usr/local/tmp/tts_in.wav";
    auto wav = StreamCreator::createSoundStream(file);
    if(wav) {
        SoundPlayer player("default");

        player.load(wav);

        wav->open();
        std::cout << "total seconds: " << wav->total() << std::endl;
        std::cout << "sample rate: " << wav->sample_rate() << "Hz" << std::endl;

        if(!player.start()) {
            std::cerr << player.error_msg() << std::endl;
        }

        while(player.is_playing()) {
            std::cout << player.currentSecond() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    return 0;
}