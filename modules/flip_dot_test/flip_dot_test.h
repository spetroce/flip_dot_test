#ifndef FLIP_DOT_TEST_H
#define FLIP_DOT_TEST_H

#include <QMainWindow>
#include "mio/serial_com/serial_com.h"

namespace Ui {
  class FlipDotTest;
}

class FlipDotTest : public QMainWindow {
  Q_OBJECT
  Ui::FlipDotTest *ui_;
  SerialCom serial_com_;

  public:
    explicit FlipDotTest(QWidget *parent = 0);
    ~FlipDotTest();

  public slots:
    void Connect();
    void Disconnect();
    void SegmentTest();
    void NumberTest();
    void DisplayNumber();
};

#endif // FLIP_DOT_TEST_H

