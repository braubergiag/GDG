#include "dialogmodel.h"
#include "ui_dialogmodel.h"

DialogModel::DialogModel(QWidget *parent,Model * model,FunctionsLibrary * functionsLibrary) :
    QDialog(parent),
    ui(new Ui::DialogModel),model_(model),functionsLibrary_ (functionsLibrary)
{
    ui->setupUi(this);


}

DialogModel::~DialogModel()
{
    delete model_;
    delete ui;
}
