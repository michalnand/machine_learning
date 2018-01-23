#include "hardware_in_loop.h"

HardwareInLoop::HardwareInLoop()
{
  serial_port = new CSerialPort("/dev/ttyUSB0");
}

HardwareInLoop::~HardwareInLoop()
{
  delete serial_port;
}

void HardwareInLoop::send(std::vector<float> &v)
{
  std::string res;

  for (unsigned int i = 0; i < v.size(); i++)
  {
    int tmp = v[i]*127;
    res+= std::to_string(tmp)+ " ";
  }

  res+="\n";
  serial_port->put_string(res);
}

std::vector<float> HardwareInLoop::get()
{
  while (parser.updated() == false)
  {
    if (serial_port->is_char())
      parser.add(serial_port->get_char());
  }

  std::vector<float> result = parser.get();

  for (unsigned int i = 0; i < result.size(); i++)
    result[i]/= 127.0;

  return result;
}
