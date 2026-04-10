#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import time
import asyncio
import edge_tts
from edge_tts import Communicate
import re

import srt_to_lrc

'''
python -m pip install edge-tts

run: python tts.py
'''

#================================================
folder_path = "./"
tts_path = f"{folder_path}tts.txt"
srt_path = f"{folder_path}tts.srt"
mp3_path = f"{folder_path}tts.mp3"
lrc_path = f"{folder_path}tts.lrc"

# 单单生成txt, 用于检查, 不生成mp3 (太慢)
dry_run = False

'''
todo
segments = [
    ("zh-CN-XiaoxiaoNeural", "这是一个测试。"),
    ("en-US-AndrewNeural", "This is a test."),
    ("zh-CN-XiaoxiaoNeural", "中英文混合的语音合成。"),
]
然后每段单独 edge-tts, 最后用 ffmpeg concat。

用下面regex去掉中文, 纯英文.
[\u4e00-\u9fff]
'''
# 英文
use_voice = "en-US-AndrewNeural"
# 中文
#use_voice = "zh-CN-XiaoxiaoNeural"

#NEW_LINE = '\n'

def read_file(tts_path: str) -> str:
    raw_lines = []
    with open(tts_path, "r", encoding="utf-8") as f:
        for line_num, line in enumerate(f):
            raw_line = line.rstrip('\n')
            raw_lines.append(raw_line)
    return "\n".join(raw_lines)

def save_text(path: str, text: str):
    with open(path, "w", encoding="utf-8") as f:
        f.write(text)

'''
examples:
https://github.com/rany2/edge-tts/blob/master/examples/sync_audio_streaming_with_predefined_voice_subtitles.py

https://blog.csdn.net/qq_37292005/article/details/148950758
'''

def text_to_mp3(
    text: str,
    output_mp3: str,
    output_srt: str,
    voice: str,
    rate: str,
    volume: str
):
    """
    Convert text to speech using Edge TTS and save as mp3.
    """
    communicate = edge_tts.Communicate(
        text=text,
        voice=voice,
        rate=rate,
        volume=volume,
    )

    submaker = edge_tts.SubMaker()
    with open(output_mp3, "wb") as file:
        for chunk in communicate.stream_sync():
            if chunk["type"] == "audio":
                file.write(chunk["data"])
            elif chunk["type"] in ("WordBoundary", "SentenceBoundary"):
                submaker.feed(chunk)

    with open(output_srt, "w", encoding="utf-8") as file:
        file.write(submaker.get_srt())

def main():    
    tts_text = read_file(tts_path)

    if dry_run:
        return

    print(f"=== Generating {mp3_path} ===")
    text_to_mp3(
        text=tts_text,
        output_mp3=mp3_path,
        output_srt=srt_path,
        voice=use_voice,
        rate="-20%", # rate: str = "+0%",
        volume="+0%",
    )
    srt_to_lrc.srt_to_lrc(srt_path, lrc_path)

    print(f"MP3 saved to: {mp3_path}")

if __name__ == "__main__":
    start_time = time.time()
    main()
    print("Done, takes %.2f s" % (time.time() - start_time))
