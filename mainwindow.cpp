#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"
#include "QPixmap"
#include "QLabel"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browse_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File",
                                                    "C:CVIPtool/images",
                                                    "*.* ALL Files;;*.bmp;;*.jpeg;;*.ppm;;*.png;;*.jpg");
    if (filename.isEmpty())
        return;
    ui->ln_filename->setText(filename);

    QPixmap pixmap(filename);
    QLabel *label = new QLabel();
    label->setPixmap(pixmap);
    label->setWindowTitle(QFileInfo(filename).fileName());
    label->show();
}
void MainWindow::DisplayImage(QImage &img, QString title){
    QLabel *label = new QLabel();
    label->setPixmap(QPixmap::fromImage(img));
    label->setWindowTitle(title);
    label->show();
}

void MainWindow::on_ab_mau_clicked()
{
    QString filename = ui->ln_filename->text();
    QImage image_in(filename);
    QImage image_out(image_in.width(), image_in.height(), QImage::Format_ARGB32);
//    int c = ui->in_c->text().toInt();
    for (int x=0; x<image_in.width(); x++)
        for (int y=0; y<image_in.height(); y++){
//            QRgb rgb = image_in.pixel(x, y);
//            QColor color_in(rgb);
//            int h, s, v;
//            color_in.getHsv(&h, &s, &v);
//            int v_out = 255-v;
//            if (v_out>255)
//                v_out=255;
//            else if (v_out<0)
//                v_out=0;
//            QColor color_out = QColor::fromHsv(h, s, v_out);
//            image_out.setPixel(x, y, color_out.rgb());
            QRgb color = image_in.pixel(x,y);//lay mau gia tri pixel(x,y)
            int red_in = qRed(color);//doi gia tri mau thanh muc do
            int red_out = 255 - red_in;//thay doi do am ban anh
            int green_in = qGreen(color);//doi gia tri mau thanh muc xanh la
            int green_out = 255 - green_in;//thay doi do am ban anh
            int blue_in = qBlue(color);//doi gia tri mau thanh muc xanh duong
            int blue_out = 255 - blue_in;//thay doi do am ban anh
            QRgb color_out = qRgb(red_out, green_out, blue_out);//anh xam (R=G=B)
            image_out.setPixel(x,y,color_out);
        }
    DisplayImage(image_out, QFileInfo(filename).fileName()+"_His_Slide");
}

void MainWindow::on_ab_xam_clicked()
{
    QString filename = ui->ln_filename->text();
    QImage image_in(filename);
    QImage image_out(image_in.width(), image_in.height(), QImage::Format_ARGB32);
    for (int x = 0; x<image_in.width(); x++)
        for (int y = 0; y<image_in.height(); y++){
            QRgb color = image_in.pixel(x, y);
            int gray_in = qGray(color);
            int gray_out = gray_in;
            if (gray_out>255)
                gray_out=255;
            else if (gray_out<0)
                gray_out=0;
            QRgb color_out = qRgb (gray_out, gray_out, gray_out);
            image_out.setPixel(x, y, color_out);
        }
    DisplayImage(image_out, QFileInfo(filename).fileName());
    for (int x=0; x<image_out.width(); x++)
        for (int y=0; y<image_out.height(); y++){
            QRgb rgb = image_out.pixel(x, y);
            QColor color_in(rgb);
            int h, s, v;
            color_in.getHsv(&h, &s, &v);
            int v_out = 255-v;
            QColor color_out = QColor::fromHsv(h, s, v_out);
            image_out.setPixel(x, y, color_out.rgb());
        }


    DisplayImage(image_out, QFileInfo(filename).fileName()+"_His_Slide");

}

