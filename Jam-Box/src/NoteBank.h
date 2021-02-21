
const char NotesString[61][4] =	{"1C"  , "1C#" , "1D"  , "1D#" , "1E"  , "1F"  , "1F#" , "1G"  , "1G#" , "1A"  , "1A#" , "1B"  , "2C"  , "2C#" , "2D"  , "2D#" , "2E"  , "2F"  , "2F#" , "2G"  , "2G#"  , "2A"   , "2A#"  , "2B"   , "3C"   , "3C#"  , "3D"   , "3D#"  , "3E"   , "3F"   , "3F#"  , "3G"   , "3G#"  , "3A"   , "3A#"  , "3B"   , "4C"   , "4C#"  , "4D"   , "4D#"  , "4E"   , "4F"   , "4F#"  , "4G"   , "4G#"  , "4A"   , "4A#"  , "4B"   , "5C"   , "5C#"  , "5D"   , "5D#"  , "5E"   , "5F"   , "5F#"  , "5G"   , "5G#"  , "5A"   , "5A#"  , "5B"   , "6C"};
const float NoteFrequency[61] =	{32.70f, 34.65f, 36.71f, 38.89f, 41.20f, 43.65f, 46.25f, 49.00f, 51.91f, 55.00f, 58.27f, 61.74f, 65.41f, 69.30f, 73.42f, 77.78f, 82.41f, 87.31f, 92.50f, 98.00f, 103.83f, 110.00f, 116.54f, 123.47f, 130.81f, 138.59f, 146.83f, 155.56f, 164.81f, 174.61f, 185.00f, 196.00f, 207.65f, 220.00f, 233.08f, 246.94f, 261.63f, 277.18f, 293.66f, 311.13f, 329.63f, 349.23f, 369.99f, 392.00f, 415.30f, 440.00f, 466.16f, 493.88f, 523.25f, 554.37f, 587.33f, 622.25f, 659.25f, 698.46f, 739.99f, 783.99f, 830.61f, 880.00f, 932.33f, 987.77f, 1046.50f}; 
	
// https://pages.mtu.edu/~suits/notefreqs.html

// possibly reduce the frequency range if sample rate isn't sufficient


const char ModeNames[7][11] = {"Major", "Dorian", "Phyrgian", "Lydian", "Mixolydian", "Minor", "Locrian"};

// https://en.wikipedia.org/wiki/Mode_(music)#Major_modes