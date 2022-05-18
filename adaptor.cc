#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

class MediaPlayer {
 public:
  virtual void play(std::string audio_type, std::string filename) = 0;
};

class AdvancedMediaPlayer {
 public:
  virtual void playVlc(std::string fileName) = 0;
  virtual void playMp4(std::string fileName) = 0;
};

class VlcPlayer : public AdvancedMediaPlayer {
  void playVlc(std::string fileName) override {
    std::cout << "playVlc fileName=" << fileName << std::endl;
  }
  void playMp4(std::string fileName) override {
    // non thing
  }
};

class Mp4Player : public AdvancedMediaPlayer {
  void playVlc(std::string fileName) override {
    // non thing
  }
  void playMp4(std::string fileName) override {
    std::cout << "playMp4 fileName=" << fileName << std::endl;
  }
};

class MediaAdaptor : public MediaPlayer {
 public:
  MediaAdaptor(std::string audio_type) {
    if (!audio_type.compare("Vlc")) {
      advancedMusicPlayer = std::make_shared<VlcPlayer>();
    } else if (!audio_type.compare("Mp4")) {
      advancedMusicPlayer = std::make_shared<Mp4Player>();
    }
  }

  void play(std::string audio_type, std::string filename) {
    if (!audio_type.compare("Vlc")) {
      advancedMusicPlayer->playVlc(filename);
    } else if (!audio_type.compare("Mp4")) {
      advancedMusicPlayer->playMp4(filename);
    }
  }

 private:
  std::shared_ptr<AdvancedMediaPlayer> advancedMusicPlayer;
};

class AudioPlayer : public MediaPlayer {
 public:
  void play(std::string audio_type, std::string filename) override {
    if (!audio_type.compare("Mp3")) {
      std::cout << "Playing mp3 file. Name: " << filename << std::endl;
    } else if (!audio_type.compare("Mp4") || !!audio_type.compare("Vlc")) {
      mediaAdaptor = std::make_shared<MediaAdaptor>(audio_type);
      mediaAdaptor->play(audio_type, filename);
    } else {
      std::cout << "Invalid media." << audio_type << " format not supported"
                << std::endl;
    }
  }

 private:
  std::shared_ptr<MediaAdaptor> mediaAdaptor;
};

int main(int argc, char *argv[]) {
  AudioPlayer audioPlayer;
  audioPlayer.play("Mp3", "beyond the horizon.mp3");
  audioPlayer.play("Mp4", "alone.mp4");
  audioPlayer.play("Vlc", "far far away.vlc");
  audioPlayer.play("Avi", "mind me.avi");

  return 0;
}