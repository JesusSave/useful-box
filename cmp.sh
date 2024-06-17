#!/bin/bash

# 定义源目录和目标目录
SOURCE_DIR="/home/qchen/Documents/Techs/arduino/esp8266/useless/useless-box"
TARGET_DIR="/home/qchen/Documents/Techs/arduino/esp32wroom32d/useless-box"

# 检查目录是否存在
if [ ! -d "$SOURCE_DIR" ]; then
  echo "Source directory does not exist: $SOURCE_DIR"
  exit 1
fi

if [ ! -d "$TARGET_DIR" ]; then
  echo "Target directory does not exist: $TARGET_DIR"
  exit 1
fi

# 遍历源目录中的所有文件
for SRC_FILE in "$SOURCE_DIR"/*; do
  # 提取文件名
  FILENAME=$(basename "$SRC_FILE")
  
  # 定义目标文件路径
  TGT_FILE="$TARGET_DIR/$FILENAME"
  
  # 检查目标文件是否存在
  if [ -f "$TGT_FILE" ]; then
    # 比较文件内容
    cmp -s "$SRC_FILE" "$TGT_FILE"
    if [ $? -eq 0 ]; then
      echo "Files are the same: $FILENAME"
    else
      echo "Files differ: $FILENAME"
    fi
  else
    echo "Target file does not exist: $TGT_FILE"
  fi
done
