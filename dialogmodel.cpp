#include "dialogmodel.h"
#include "ui_dialogmodel.h"

DialogModel::DialogModel(QWidget *parent,Model * model) :
    QDialog(parent),
    ui(new Ui::DialogModel),model_(model)
{
    ui->setupUi(this);
}

DialogModel::~DialogModel()
{
    delete model_;
    delete ui;
}
