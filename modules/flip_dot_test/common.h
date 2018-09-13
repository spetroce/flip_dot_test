// This file contains code used both in flip_dot_test.cpp and main.cpp

#ifndef __FLIP_DOT_TEST_COMMON_H__
#define __FLIP_DOT_TEST_COMMON_H__

#include <vector>
#include <thread>
#include <chrono>
#include "mio/altro/error.h"
#include "mio/altro/bit_byte_ops.h"
#include "mio/serial_com/serial_com.h"


int SetupSerialCom(SerialCom &serial_com, const char *kDevPort) {
  EXP_CHK(serial_com.Init(kDevPort) == 0, return(-1))
  serial_com.SetDefaultControlFlags();
  serial_com.SetOutputType(OutputType::RawOutput);
  serial_com.SetInputType(InputType::RawInput);
  serial_com.SetOutBaudRate(9600);
  serial_com.SetInBaudRate(9600);
  serial_com.SetHardwareFlowControl(false);
  serial_com.SetSoftwareFlowControl(false);
  serial_com.SetCharSize(8);
  serial_com.SetParity(ParityType::NoneParity);
  serial_com.SetParityChecking(false, false, false, false);
  serial_com.SetStopBits(1);
  serial_com.FlushIO();

  return 0;
}


/*
  bit 0 - bottom segment
  bit 1 - bottom left segment
  bit 2 - top left segment
  bit 3 - top segment
  bit 4 - top right segment
  bit 5 - bottom right segment
  bit 6 - middle segment

  0 - 0b00111111
  1 - 0b00110000
  2 - 0b01011011
  3 - 0b01111001
  4 - 0b01110100
  5 - 0b01101101
  6 - 0b01101111
  7 - 0b00111000
  8 - 0b01111111
  9 - 0b01111100
*/
uint8_t GetSegmentNumber(const uint8_t number_to_display) {
  std::vector<uint8_t> segment_number =
    {0b00111111, 0b00110000, 0b01011011, 0b01111001, 0b01110100,
     0b01101101, 0b01101111, 0b00111000, 0b01111111, 0b01111100};
  EXP_CHK(number_to_display >= 0 && number_to_display <= 9, return(0))
  return segment_number[number_to_display];
}


void GetDefaultDataPacket(std::vector<uint8_t> &data) {
  data.resize(5);
  data[0] = 0x80; // Header
  data[1] = 0x89; // Send one data byte and show it in the display 
  data[2] = 0xFF; // RS-485 address (default from factory)
  data[3] = 0; // Bits B6 – B0 are setting dots from top to bottom respectively
  data[4] = 0x8F; // End byte
}


void SegmentTest(SerialCom &serial_com) {
  const bool kDrainBuffer = true;
  std::vector<uint8_t> data;
  GetDefaultDataPacket(data);

  for (uint8_t i = 0; i < 8; ++i) {
    data[3] = 0;
    if (i != 7) {
      BIT_SET(data[3], i);
    }
    EXP_CHK(serial_com.Write(data.data(), data.size(), kDrainBuffer) == 0, return)
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}


void NumberTest(SerialCom &serial_com) {
  const bool kDrainBuffer = true;
  std::vector<uint8_t> data;
  GetDefaultDataPacket(data);

  for (uint8_t i = 0; i < 11; ++i) {
    data[3] = i != 10 ? GetSegmentNumber(i) : 0;
    EXP_CHK(serial_com.Write(data.data(), data.size(), kDrainBuffer) == 0, return)
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
  }
}


void DisplayNumber(SerialCom &serial_com, const uint8_t number) {
  EXP_CHK(number >= 0 && number <= 9, return)
  const bool kDrainBuffer = true;
  std::vector<uint8_t> data;
  GetDefaultDataPacket(data);

  data[3] = GetSegmentNumber(number);
  EXP_CHK(serial_com.Write(data.data(), data.size(), kDrainBuffer) == 0, return)
}

#endif // __FLIP_DOT_TEST_COMMON_H__

