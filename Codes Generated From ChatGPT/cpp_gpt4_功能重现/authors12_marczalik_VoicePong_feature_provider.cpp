#include <Arduino.h>
#include <AudioProvider.h>
#include <micro_features_micro_features_generator.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

namespace {
constexpr int kAudioSampleRate = 16000;
constexpr int kAudioWindowSize = 40; // 40ms时间窗口
constexpr int kAudioWindowStride = 20; // 20ms步长
constexpr int kFeatureSliceDurationMs = 10; // 10ms切片长度
constexpr int kFeatureSliceStrideMs = 5; // 5ms切片步长

tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

int8_t tensor_arena[10000] __attribute__((aligned(4)));
}  // namespace

void setup() {
  Serial.begin(115200);

  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // 初始化音频提供器
  AudioProvider audio_provider;

  // 初始化micro-feature generator
  MicroFeaturesGenerator micro_features_generator;

  // 配置模型和解释器
  model = tflite::GetModel(g_model);
  static tflite::AllOpsResolver resolver;
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, sizeof(tensor_arena), error_reporter);
  interpreter = &static_interpreter;

  interpreter->AllocateTensors();

  // 获取输入输出张量
  input = interpreter->input(0);
  output = interpreter->output(0);
}

void loop() {
  // 获取音频数据
  int32_t audio_data[kAudioSampleRate * kAudioWindowSize / 1000] = {0};
  int32_t audio_data_length = AudioProvider::GetAudioWindow(audio_data, kAudioWindowSize, kAudioWindowStride);

  // 计算声音特征
  MicroFeaturesGenerator::GenerateMicroFeatures(audio_data, audio_data_length, kFeatureSliceDurationMs, kFeatureSliceStrideMs, input->data.f);

  // 调用TensorFlow Lite API传递数据
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    error_reporter->Report("Invoke failed");
    return;
  }

  // 输出结果
  float result = output->data.f[0];
  Serial.print("Generated feature: ");
  Serial.println(result);

  delay(100);
}
