#include <libhal-picosdk/adc.hpp>
#include <libhal-picosdk/rp.hpp>
#include <libhal-picosdk/serial.hpp>
#include <libhal-picosdk/time.hpp>
#include <libhal-util/serial.hpp>

namespace rp = hal::rp;

int main() {
  using namespace std::chrono_literals;
  auto adc = rp::v5::adc16(hal::pin<28>);
  auto serial = rp::stdio_serial();
  for (;;) {
    hal::print<64>(serial, "ADC value: %d\n", adc.read());
    rp::sleep(1s);
  }
}
