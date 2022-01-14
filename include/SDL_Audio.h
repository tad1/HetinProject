#pragma once
#include <SDL.h>
#include "../libs/Dictionary.h"
#include "../libs/Copyable.h"
#include "../Console.h"

typedef CopyableString<40> audioPath;

struct WAV_File {
	SDL_AudioSpec wavSpec;
	Uint32 wavLenght;
	Uint8* wavBuffer;
};

class WAV_Loader_ {

private:
	Dictionary<audioPath, WAV_File> wavs;
public:
	WAV_File Get(audioPath path) {
		return wavs[path];
	}

	WAV_File Add(char* path) {
		audioPath wav_path = { "" };
		wav_path = path;
		return Add(wav_path);
	}

	WAV_File Add(audioPath path) {
		if (wavs.ContainsKey(path)) {
			return wavs[path];
		}
		WAV_File wav;
		SDL_LoadWAV(path.c_str, &wav.wavSpec, &wav.wavBuffer, &wav.wavLenght);
		wavs.Add(path,wav);
		return wav;
	}

	~WAV_Loader_() {
		for (int i = 0; i < wavs.GetCount(); i++) {
			SDL_FreeWAV(wavs.Get(i).wavBuffer);
		}
	}
} WAV_Loader;

class SDL_Audio {
	SDL_AudioDeviceID deviceId;
	SDL_AudioSpec currentWavSpec;

public:
	SDL_Audio() {
		SDL_Init(SDL_INIT_AUDIO);
		deviceId = NULL;

	}

	~SDL_Audio() {
		if(deviceId != NULL)
			SDL_CloseAudioDevice(deviceId);
	}
	void Play(WAV_File wav) {
		if (deviceId == NULL) {
			currentWavSpec = wav.wavSpec;
			deviceId = SDL_OpenAudioDevice(NULL, 0, &currentWavSpec, NULL, 0);
		}
		if (SDL_QueueAudio(deviceId, wav.wavBuffer, wav.wavLenght)) {
			Console.Log("SDL_Audio: couldn't queue audio");
		}
		SDL_PauseAudioDevice(deviceId, 0);
	}
} Audio;

