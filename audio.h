#ifndef AUDIO_H
#define AUDIO_H

class Audio
{
 protected:
  Audio();

 private:
  static Audio* _self;

 public:
  static Audio* instancia();
};

#endif
