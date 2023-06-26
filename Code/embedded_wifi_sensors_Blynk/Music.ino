
// runs only once at start up to play the music 
#include "pitches.h"

// notes in the melody:
int melody[] = {

  NOTE_C6,NOTE_C5, NOTE_G5, NOTE_F5, NOTE_C5, NOTE_C6, NOTE_G5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {

  4, 8, 4, 4, 4, 4, 2
};

void setupMusic() {
  delay(4000);

  // iterate over the notes of the melody:

  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(40, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(40);

  }
}

void loopMusic() {   // stops no need to do enything
  delay(10000);
}
