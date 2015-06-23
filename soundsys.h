#ifndef SOUNDSYS_H
#define SOUNDSYS_H

#include <QSound>

class SoundSys
{
public:
    SoundSys();

    static void playIntro(){
        const QString intro = QString(":/sounds/shot_intro.wav");
        QSound::play(intro);
    }
    static void playApplause(){
        const QString intro = QString(":/sounds/applause_finish.wav");
        QSound::play(intro);
    }
    static void playClack()
    {

    }
};

#endif // SOUNDSYS_H
