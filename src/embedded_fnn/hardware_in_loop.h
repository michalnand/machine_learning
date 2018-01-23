#ifndef _HARDWARE_IN_LOOP_
#define _HARDWARE_IN_LOOP_

#include <vector>
#include <serial_port.h>
#include <numbers_parser.h>

class HardwareInLoop
{
  private:
    CSerialPort   *serial_port;
    CNumbersParser parser;

  public:
    HardwareInLoop();
    ~HardwareInLoop();

    void send(std::vector<float> &v);
    std::vector<float> get();
};

#endif
