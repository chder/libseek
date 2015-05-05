#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    thermal.init();
    thermal.frame_init(frame);

    int h = frame.height();
    int w = frame.width();

    image = QImage(w,h, QImage::Format_ARGB32);
    pixmap = QPixmap::fromImage(image);

    ui->videoLabel->setGeometry(64,64, w,h);
    timer.setSingleShot(true);
    timer.setInterval(30);

    connect(&timer, SIGNAL(timeout()), this, SLOT(doSomething()));

}

MainWindow::~MainWindow()
{
    timer.stop();
    thermal.frame_exit(frame);
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    liveMode = !liveMode;
    if (liveMode) {
        timer.start();
    }
}

void MainWindow::doSomething()
{
    thermal.frame_acquire(frame);

    int h = frame.height();
    int w = frame.width();

    uint16_t min = -1;
    uint16_t max = 0;

    // Find the min and max.
    if (1) {
        const int margin = 8;
        for (int y = 0 + margin; y < (h - margin); ++y) {
            for (int x = 0 + margin; x < (w - margin); ++x) {
                uint16_t pixel = frame.data()[y*w+x];

                min = qMin(min, pixel);
                max = qMax(max, pixel);
            }
        }
    }else{
        max = 0x8200;
        min = 0x7e00;
    }

    qDebug() << "Min: " << min << "  Max: " << max;

    // Rescale into QImage
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            uint16_t pixel = frame.data()[y*w+x];

            float v = float(pixel - min) / (max - min);
            if (v < 0.0) { v = 0; }
            if (v > 1.0) { v = 1; }



            uint8_t ror = abs(0xff  * (float(0.01-v)));
            uint8_t gog = abs(0xff  * (float(0.5-v)));
            uint8_t bob = abs(0xff  * (float(0.99-v)));

            image.setPixel(x, y, qRgb(ror,gog,bob));
            if (pixel == 0x8000)
            {
                image.setPixel(x, y, qRgb(0,0,0));
            }
        }
    }
    int scale = 6;

    QPixmap tmp = QPixmap::fromImage(image);
    pixmap = tmp.scaled(w*scale,h*scale);

    ui->videoLabel->setGeometry(16,16,w*scale,h*scale);

    ui->videoLabel->setPixmap(pixmap);
    if (liveMode)
        timer.start();
}
