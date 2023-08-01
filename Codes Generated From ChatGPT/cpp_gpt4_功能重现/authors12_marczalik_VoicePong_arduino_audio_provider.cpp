// PDM_Audio_Input_Library.h

#ifndef PDM_AUDIO_INPUT_LIBRARY_H
#define PDM_AUDIO_INPUT_LIBRARY_H

#include <Arduino.h>
#include <PDM.h>

// 版权信息
// Copyright (C) 2023 Your_Name
//
// 授权信息
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// 宏定义和条件编译
#define AUDIO_BUFFER_SIZE 256
#define PDM_BUFFER_SIZE (AUDIO_BUFFER_SIZE * 2)

// 函数声明
void CaptureSamples();
void InitAudioRecording();
uint32_t GetAudioSamples(int16_t *buffer, uint32_t start_sample, uint32_t end_sample);

// 全局变量
extern int16_t g_audio_buffer[AUDIO_BUFFER_SIZE];
extern volatile uint32_t g_latest_audio_timestamp;

#endif // PDM_AUDIO_INPUT_LIBRARY_H

// PDM_Audio_Input_Library.cpp

#include "PDM_Audio_Input_Library.h"

// 全局变量
int16_t g_audio_buffer[AUDIO_BUFFER_SIZE] = {0};
int16_t g_pdm_buffer[PDM_BUFFER_SIZE] = {0};
volatile uint32_t g_latest_audio_timestamp = 0;

// 回调函数 CaptureSamples
void CaptureSamples() {
  uint32_t current_timestamp = millis();
  uint32_t buffer_start_pos = (current_timestamp * AUDIO_BUFFER_SIZE) % PDM_BUFFER_SIZE;

  for (uint32_t i = 0; i < AUDIO_BUFFER_SIZE; i++) {
    g_audio_buffer[i] = g_pdm_buffer[buffer_start_pos + i];
  }

  g_latest_audio_timestamp = current_timestamp;
}

// 初始化音频录制
void InitAudioRecording() {
  PDM.begin(1, PDM_BUFFER_SIZE);
  PDM.setGain(80);
  PDM.onReceive(CaptureSamples);

  while (g_latest_audio_timestamp == 0) {
    delay(10);
  }
}

// 获取音频采样
uint32_t GetAudioSamples(int16_t *buffer, uint32_t start_sample, uint32_t end_sample) {
  uint32_t buffer_start_pos = (start_sample * AUDIO_BUFFER_SIZE) % PDM_BUFFER_SIZE;
  uint32_t buffer_end_pos = (end_sample * AUDIO_BUFFER_SIZE) % PDM_BUFFER_SIZE;
  uint32_t samples_to_copy = buffer_end_pos - buffer_start_pos;

  memcpy(buffer, &g_audio_buffer[buffer_start_pos], samples_to_copy * sizeof(int16_t));

  return samples_to_copy;
}
