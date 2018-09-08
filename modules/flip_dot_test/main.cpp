#include <vector>
#include <thread>
#include <chrono>
#include "mio/serial_com/serial_com.h"
#include "mio/altro/error.h"
#include "mio/altro/bit_byte_ops.h"

SerialCom g_ser_port;


int main(int argc, char *argv[]){
  EXP_CHK_M(argc > 1, return(-1), "usage: flip_dot_test")

  EXP_CHK(g_ser_port.Init(argv[1]) == 0, return(-1))
  g_ser_port.SetDefaultControlFlags();
  g_ser_port.SetOutputType(OutputType::RawOutput);
  g_ser_port.SetInputType(InputType::RawInput);
  g_ser_port.SetOutBaudRate(9600);
  g_ser_port.SetInBaudRate(9600);
  g_ser_port.SetHardwareFlowControl(false);
  g_ser_port.SetSoftwareFlowControl(false);
  g_ser_port.SetCharSize(8);
  g_ser_port.SetParity(ParityType::NoneParity);
  g_ser_port.SetParityChecking(false, false, false, false);
  g_ser_port.SetStopBits(1);

  const size_t kDataBufSize = 5;
  uint8_t data[kDataBufSize];

  data[0] = 0x80; // Header
  data[1] = 0x89; // Send one data byte and show it in the display 
  data[2] = 0xFF; // RS-485 address (default from factory)
  data[3] = 0; // Bits B6 – B0 are setting dots from top to bottom respectively
  data[4] = 0x8F; // End byte

  const bool drain_buffer = true;
  const unsigned int time_out_sec = 3,
                     time_out_limit = 3;
  g_ser_port.FlushIO();

  /*
    bit 0 - bottom segment
    bit 1 - bottom left segment
    bit 2 - top left segment
    bit 3 - top segment
    bit 4 - top right segment
    bit 5 - bottom right segment
    bit 6 - middle segment

    0 - 0x3F
    1 - 0x30
    2 - 0x5B
    3 - 0x79
    4 - 0x74
    5 - 0x6D
    6 - 0x6F
    7 - 0x38
    8 - 0x7F
    9 - 0x7C
  */

  std::vector<uint8_t> numbers = {0x3F, 0x30, 0x5B, 0x79, 0x74,
                                  0x6D, 0x6F, 0x38, 0x7F, 0x7C};

  for (uint8_t i = 0; i < 8; ++i) {
    data[3] = 0;
    if (i != 7) {
      BIT_SET(data[3], i);
    }
    g_ser_port.Write(data, kDataBufSize, drain_buffer,
                     time_out_sec, time_out_limit);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  for (uint8_t i = 0; i < 11; ++i) {
    data[3] = i != 10 ? numbers[i] : 0;
    g_ser_port.Write(data, kDataBufSize, drain_buffer,
                     time_out_sec, time_out_limit);
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
  }

  g_ser_port.Uninit(true);
  return 0;
}

