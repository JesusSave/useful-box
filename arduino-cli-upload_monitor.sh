#!/bin/bash

# 设置你的项目路径和串口端口
PROJECT_PATH="./"
SERIAL_PORT="/dev/ttyUSB0"
FQBN="esp8266:esp8266:nodemcuv2"
BAUD_RATE=115200

# 检查 /dev/ttyUSB0 是否具有 a+rw 权限
if [ ! -r /dev/ttyUSB0 ] || [ ! -w /dev/ttyUSB0 ]; then
  echo "Adding a+rw permissions to /dev/ttyUSB0"
  sudo chmod a+rw /dev/ttyUSB0
else
  echo "/dev/ttyUSB0 already has a+rw permissions"
fi

# 编译项目
arduino-cli compile --fqbn $FQBN $PROJECT_PATH

# 检查编译是否成功
if [ $? -ne 0 ]; then
  echo "Compilation failed!"
  exit 1
fi

# 上传项目
arduino-cli upload -p $SERIAL_PORT --fqbn $FQBN $PROJECT_PATH

# 检查上传是否成功
if [ $? -ne 0 ]; then
  echo "Upload failed!"
  exit 1
fi

# 启动串口监视器
#arduino-cli monitor -p $SERIAL_PORT -c $BAUD_RATE # Arduino-cli 0.35.3
arduino-cli monitor -p $SERIAL_PORT -c $BAUD_RATE --fqbn $FQBN $PROJECT_PATH
