#include "form_ugv.h"
#include "ui_form_ugv.h"

Form_ugv::Form_ugv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_ugv)
{
    ui->setupUi(this);
}

Form_ugv::~Form_ugv()
{
    delete ui;
}
