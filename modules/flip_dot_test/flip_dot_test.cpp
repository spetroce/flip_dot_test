#include "flip_dot_test.h"
#include "ui_flip_dot_test.h"
#include "flip_dot_test/common.h"


FlipDotTest::FlipDotTest(QWidget *parent) :
    QMainWindow(parent), ui_(new Ui::FlipDotTest) {
  ui_->setupUi(this);
  connect(ui_->push_button_connect, SIGNAL(clicked()), this, SLOT(Connect()));
  connect(ui_->push_button_disconnect, SIGNAL(clicked()), this, SLOT(Disconnect()));
  connect(ui_->push_button_segment_test, SIGNAL(clicked()), this, SLOT(SegmentTest()));
  connect(ui_->push_button_number_test, SIGNAL(clicked()), this, SLOT(NumberTest()));
  connect(ui_->push_button_display_number, SIGNAL(clicked()), this, SLOT(DisplayNumber()));
}


FlipDotTest::~FlipDotTest() {
  if(serial_com_.IsInit())
    Disconnect();
  delete ui_;
}


void FlipDotTest::ConnectEnable(const bool connected) {
  ui_->push_button_connect->setEnabled(!connected);
  ui_->push_button_disconnect->setEnabled(connected);
  ui_->push_button_segment_test->setEnabled(connected);
  ui_->push_button_number_test->setEnabled(connected);
  ui_->push_button_display_number->setEnabled(connected);
  ui_->spin_box_number->setEnabled(connected);
}


void FlipDotTest::Connect() {
  EXP_CHK(SetupSerialCom(serial_com_, ui_->line_edit_dev_str->text().toUtf8().constData()) == 0, return)
  std::cout << FFL_STRM << "connected\n";
  ConnectEnable(true);
}


void FlipDotTest::Disconnect() {
  EXP_CHK(serial_com_.Uninit() == 0, return)
  std::cout << FFL_STRM << "disconnected\n";
  ConnectEnable(false);
}


void FlipDotTest::SegmentTest() {
  ::SegmentTest(serial_com_);
}


void FlipDotTest::NumberTest() {
  ::NumberTest(serial_com_);
}


void FlipDotTest::DisplayNumber() {
  ::DisplayNumber(serial_com_, ui_->spin_box_number->value());
}

