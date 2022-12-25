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

/// <summary>
/// Loads and Mangages WAV files
/// </summary>
class WAV_Loader_ {

private:
	Dictionary<audioPath, WAV_File> wavs;
public:
	WAV_File Get(audioPath path) {
		return wavs[path];
	}

	/// <summary>
	/// Load WAV file
	/// </summary>
	/// <param name="path"></param>
	/// <returns>WAV file info and buffer location</returns>
	WAV_File Add(char* path) {
		audioPath wav_path = { "" };
		wav_path = path;
		return Add(wav_path);
	}

	/// <summary>
	/// Load WAV file
	/// </summary>
	/// <param name="path"></param>
	/// <returns>WAV file info and buffer location</returns>
	WAV_File Add(audioPath path) {
		if (wavs.ContainsKey(path)) {
			return wavs[path];
		}
		WAV_File wav;
		SDL_LoadWAV(path.c_str, &wav.wavSpec, &wav.wavBuffer, &wav.wavLenght);
		wavs.Add(path,wav);
		return wav;
	}

	/// <summary>
	/// Free all WAVs buffers
	/// </summary>
	void DeleteAll() {
		for (int i = 0; i < wavs.GetCount(); i++) {
			SDL_FreeWAV(wavs.Get(i).wavBuffer);
		}
		wavs.Clear();
	}

	~WAV_Loader_() {
		DeleteAll();
	}
};
static WAV_Loader_ WAV_Loader;

/// <summary>
/// Manage audio devices and play loaded WAV files
/// </summary>
class SDL_Audio {
	SDL_AudioDeviceID deviceId;
	SDL_AudioSpec currentWavSpec;

	WAV_File music;

public:
	SDL_Audio() {
		SDL_Init(SDL_INIT_AUDIO);
		deviceId = NULL;
		music.wavBuffer = nullptr;
	}

	~SDL_Audio() {
		if (deviceId != NULL)
			SDL_CloseAudioDevice(deviceId);
	}

	/// <summary>
	/// Add audio to queue and unpause playback
	/// </summary>
	/// <param name="wav">WAV File info</param>
	void Play(WAV_File wav) {
		if (deviceId == NULL) {
			currentWavSpec = wav.wavSpec;
			deviceId = SDL_OpenAudioDevice(NULL, 0, &currentWavSpec, NULL, 0);
		}
		if (SDL_QueueAudio(deviceId, wav.wavBuffer, wav.wavLenght)) {
			Console.Log("SDL_Audio: couldn't queue audio");
		}
		music = wav;
		SDL_PauseAudioDevice(deviceId, 0);
	}

	void PlaySFX(WAV_File wav) {
		if (music.wavBuffer == nullptr) return;
		Uint32 size = SDL_GetQueuedAudioSize(deviceId);
		SDL_ClearQueuedAudio(deviceId);
		Uint8* ptr = music.wavBuffer + music.wavLenght - size;
		SDL_MixAudioFormat(ptr, wav.wavBuffer, AUDIO_S16, wav.wavLenght, SDL_MIX_MAXVOLUME / 2);
		SDL_QueueAudio(deviceId, ptr, size);
		SDL_PauseAudioDevice(deviceId, 0);
	}

	void Pause() {
		SDL_PauseAudioDevice(deviceId, 1);
	}

	void Resume() {
		SDL_PauseAudioDevice(deviceId, 0);
	}

	/// <summary>
	/// Clear audio queue, and pause playback
	/// </summary>
	void Stop() {
		SDL_PauseAudioDevice(deviceId, 1);
		SDL_ClearQueuedAudio(deviceId);
	}
};
static SDL_Audio Audio;

