#ifdef HAVE_QT
#include <QApplication>
#include "flip_dot_test/flip_dot_test.h"
#else
#include "flip_dot_test/common.h"
#endif


#ifndef HAVE_QT
int CommandLineTest(const char *kDevPort) {
  SerialCom serial_com;
  EXP_CHK(SetupSerialCom(serial_com, kDevPort) == 0, return(-1))

  SegmentTest(serial_com);
  NumberTest(serial_com);

  serial_com.Uninit();
  return 0;
}
#endif


int main(int argc, char *argv[]) {
#ifdef HAVE_QT
  QApplication a(argc, argv);
  FlipDotTest w;
  w.show();
  return a.exec();
#else
  EXP_CHK_M(argc > 1, return(-1), "usage: flip_dot_test /path/to/serial/dev")
  return CommandLineTest(argv[1]);
#endif
}

