# -*- coding: utf-8 -*-

# import
import wave as we
import numpy as np
import librosa
import librosa.display
import os
import sys
import random
import urllib
import urllib2
import logging
import time
import matplotlib.pyplot as plt

logger = logging.getLogger("beat.beat")


def wavread(path, beat_config_file_path, beat_data):
    logger.info("path:%s, beat_config_file_path:%s, beat_data:%s" , path, beat_config_file_path, beat_data)
    # init
    wavfile = we.open(path, "rb")
    params = wavfile.getparams()
    # params[2] 音频的帧率 params[3] 音频总帧数
    framesra, frameswav = params[2], params[3]

    datawav = wavfile.readframes(frameswav)
    wavfile.close()
    datause = np.fromstring(datawav, dtype=np.short)
    time = np.arange(0, frameswav) * (1.0 / framesra)
    max_datause = max(datause)
    min_datause = min(datause)
    d_datause = max(abs(max_datause), abs(min_datause)) * 1.0
    if (frameswav == len(datause)):
        datause = np.array([datause, datause])
    datause.shape = -1, 2
    datause = datause.T
    i = 0
    t = round(time[-1] * 100, 0) * 10

    # beat
    sb_map = {}
    tt = int(0)
    last_tt = float(0)

    with open(beat_config_file_path, 'w') as f:
        f.write('%s' % ('{'))
        if len(beat_data) > 0:
            f.write('%s' % ('"beatList":['))
            for item in beat_data:
                tt = round(item * 100,0) * 10
                q = 100
                f.write('%s%s%s%s%s' % ('{"time":', round(item * 1000.0, 2), ',"quality":', q, '},'))

                offsetTime = float(250)
                whileCount = int(offsetTime / 10)
                startTime = float(0)
                endTime = float(tt)
                startQuality = float(0)
                endQuality = round(float(q), 0)

                if (float(tt) - offsetTime < 0):
                    whileCount = int((offsetTime - float(tt)) / 10)
                    startTime = float(0)
                    startQuality = float(0)
                else:
                    if (float(tt) - last_tt > offsetTime * 2):
                        startTime = float(tt) - offsetTime
                        startQuality = float(0)
                    else:
                        whileCount = int(round(((float(tt) - last_tt) / 2) / 10, 0))
                        startTime = float(tt) - round(((float(tt) - last_tt) / 2) / 10, 0) * 10
                        if (sb_map.has_key(str(int(startTime)))):
                            startQuality = float(sb_map[str(int(startTime))])
                        else:
                            startQuality = 0.0
                if (whileCount == 1):
                    sb_map[str(int(endTime))] = endQuality
                else:
                    for index in range(whileCount):
                        sb_map[str(int(startTime + (index * 10)))] = float(
                            startQuality + (endQuality - startQuality) * float(float(index) / float(whileCount - 1)))
                    for index in range(int(offsetTime / 10)):
                        q_value = float(endQuality - endQuality * float(float(index) / float(int(offsetTime / 10) - 1)))
                        if (q_value < 0):
                            q_value = 0.0
                        sb_map[str(int(endTime + (index * 10)))] = q_value

            f.seek(-1, os.SEEK_END)
            f.truncate()
            f.write('%s' % ('],'))
        else:
            f.write('%s' % ('"beatList":['))
            f.write('%s' % ('],'))

        # pcm
        f.write('%s' % ('"pcmList":['))
        while (i <= t):
            idx = int(i / t * len(datause[0]) - 1)
            s_v = 0.0
            if (sb_map.has_key(str(i))):
                s_v = sb_map[str(i)]

            if (abs(datause[0][idx]) < abs(datause[1][idx])):
                f.write('%s%s%s%s%s%s%s%s%s%s%s%s' % (
                    '{', '"time":', i, ',', '"strength":', datause[1][idx], ',', '"strength_ratio":',
                    abs(round(((datause[1][idx] * 1.0) / d_datause) * 100, 2)), ',"smooth_strength_ratio":', s_v, '}'))
            else:
                f.write('%s%s%s%s%s%s%s%s%s%s%s%s' % (
                    '{', '"time":', i, ',', '"strength":', datause[0][idx], ',', '"strength_ratio":',
                    abs(round(((datause[0][idx] * 1.0) / d_datause) * 100, 2)), ',"smooth_strength_ratio":', s_v, '}'))
            if (i + 10 <= t):
                f.write('%s' % (','))
            i = i + 10
        f.write('%s' % (']'))
        f.write('%s' % ('}'))

def generateFromUrl(obj, output_dir):
    #videoMp3Url = obj['music_url']
    videoMp3Url = obj
    full_file_name = urllib2.unquote(videoMp3Url).decode('utf8').split('/')[-1]
    if not os.path.exists(output_dir + full_file_name):
        urllib.urlretrieve(videoMp3Url, output_dir + full_file_name)
    #file_name = full_file_name.split('.')[0] + "_" + str(obj['id']) + "_" + str(int(time.time()))
    file_name = full_file_name.split('.')[0] + "_" + "xxx" + "_" + str(int(time.time()))
    music_format = full_file_name.split('.')

    # beat init
    y, sr = librosa.load(output_dir + full_file_name)
    tempo, beat_frames = librosa.beat.beat_track(y=y, sr=sr)
    bear_res = librosa.frames_to_time(beat_frames, sr=sr)

    if (len(music_format) > 0):
        if (len(music_format) == 1 or music_format[1] == 'mp3'):
            ext_file_name = file_name + ".wav"
            # mp3 to wav
            os.system('%s%s%s%s%s' % ('ffmpeg -i ', output_dir + full_file_name, ' ', output_dir + ext_file_name, ' -y'))
            wavread(output_dir + ext_file_name, output_dir + file_name + ".rs", bear_res)
            return 0, output_dir + file_name + ".rs"
        elif (music_format[1] == 'wav'):
            wavread(full_file_name, output_dir + file_name + ".rs", bear_res)
            return 0, output_dir + file_name + ".rs"
        else:
            print "music beat format analysis erroe!"
            return 1, "music beat format analysis erroe!"
    print file_name
    return 1, "music beat format analysis erroe!"

def testRosa(file):
    y, sr = librosa.load(file)
    
    onset_env = librosa.onset.onset_strength(y, sr=sr, aggregate=np.median)
    
    onset_frames = librosa.onset.onset_detect(onset_envelope=onset_env, sr=sr)
    
    tempo, beats = librosa.beat.beat_track(y = y, sr = sr)
    
    hop_length = 512
    times = librosa.frames_to_time(np.arange(len(onset_env)), sr=sr, hop_length=hop_length)

    plt.figure(figsize=(8, 4))
    plt.plot(times, librosa.util.normalize(onset_env), label='Onset strength')
    plt.vlines(times[beats], 0, 0.95, alpha=0.5, color='r', linestyle='--', label='Beats')
    plt.vlines(times[onset_frames], 0.95, 1, alpha=0.5, color='g', linestyle='-', label='Onsets')
    
    print(len(onset_frames))
    print(len(onset_env))
    print(len(times))
    print(len(onset_frames))
    print("---")
    
    peaks = librosa.util.peak_pick(onset_env, 3, 3, 3, 5, 0, 1)
    
    #plt.vlines(times[peaks], 0.95, 1, alpha=0.5, color='b', linestyle='--', label='Peak')
    
    for i in range(0, len(beats)):
        frameIdx = beats[i]
        print(int(times[frameIdx] * 1000 + 0.5))
    
    print("---")
    frames = []
    norm_onset_env = librosa.util.normalize(onset_env)
    for i in range(0, len(peaks)):
        frameIdx = peaks[i]
        if norm_onset_env[frameIdx] > 0.4:
            #print(i+1, int(times[frameIdx] * 1000 + 0.5), norm_onset_env[frameIdx])
            print(int(times[frameIdx] * 1000 + 0.5))
            frames.append(frameIdx)
            
    plt.vlines(times[frames], 0.9, 0.95, alpha=1., color='r', linestyle='-', label='Peak')
      
    plt.legend(frameon=True, framealpha=0.75)
    # Limit the plot to a 15-second window
    plt.xlim(0, 16)
    plt.gca().xaxis.set_major_formatter(librosa.display.TimeFormatter())
    plt.tight_layout()
    plt.show()
    
def getBeats(filename):
    y, sr = librosa.load(filename)
    tempo, beat_frames = librosa.beat.beat_track(y = y, sr = sr)
    beat_res = librosa.frames_to_time(beat_frames, sr=sr)
    x = 0
    for b in beat_res:
        nb = int(b * 1000 + 0.5)
        print str(nb) + ','# + str(nb - x)
        x = nb
    

if __name__ == '__main__':
    #generateFromUrl("http://shenqutv2.bs2dl.yy.com/08a4ddb7-b817-4481-a1ef-6ee678eecfe7.mp3", "../bs2/")
    testRosa("out.mp3")
    
    
    
