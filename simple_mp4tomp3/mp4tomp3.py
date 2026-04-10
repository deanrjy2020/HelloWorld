#!/usr/bin/env python
# encoding: utf-8
import subprocess
import sys
import os
import re

'''
指定文件夹下的所有mp4转成mp3

用下面的检查mp4的个数.
ls | grep "正课" | wc -l
'''

def mp4_to_mp3_trim(input_file, output_file, start_time):
    """
    Convert MP4 to MP3 and trim first `start_time` seconds
    """
    if not os.path.exists(input_file):
        print(f"Input file not found: {input_file}")
        return

    cmd = [
        "ffmpeg",
        "-y",                  # overwrite output
        "-ss", str(start_time), # start time (skip first 15s)
        "-i", input_file,
        "-vn",                 # no video
        "-map_metadata", "-1",   # 去掉所有 metadata (title, subtile, contributing artists, album, 等)
        "-acodec", "mp3",
        "-ab", "192k",
        output_file
    ]

    subprocess.run(cmd, check=True)
    print(f"Done! Output: {output_file}")

def clean_filename(filename):
    """
    从 "<num> [xx] <name> [yy].mp4"
    变成 "<num> <name>.mp3"
    """
    # 去掉扩展名
    name = os.path.splitext(filename)[0]

    # 去掉所有 [xxx]
    name = re.sub(r"\s*【.*?】\s*", " ", name)

    # 压缩多余空格
    name = re.sub(r"\s+", " ", name).strip()

    # 保留异地个中文前面的string
    m = re.search(r'[\u4e00-\u9fff]', name)
    if m:
        name = name[:m.start()]

    return name + ".mp3"

if __name__ == "__main__":
    num = 9
    path = r"D:\Movie\牛津树\牛津树1-9视频全套\1.牛津树视频 (配套绘本）\牛津树"
    input_dir = f"{path}{num}阶"
    output_dir = f"{input_dir}_mp3"
    start_time = 30

    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for file in sorted(os.listdir(input_dir)):
        # 全部都是mp4, 没有其他格式
        assert file.lower().endswith(".mp4") == True

        if "磨耳朵" in file:
            # 不做
            continue

        input_path = os.path.join(input_dir, file)
        output_name = clean_filename(file)
        output_path = os.path.join(output_dir, output_name)

        print(f"\nProcessing: {file}")
        mp4_to_mp3_trim(input_path, output_path, start_time)

    