#include "dialogmodel.h"
#include "ui_dialogmodel.h"

DialogModel::DialogModel(QWidget *parent,Model * model,FunctionsLibrary * functionsLibrary) :
    QDialog(parent),
    ui(new Ui::DialogModel),model_(model),functionsLibrary_ ( functionsLibrary)
{
    ui->setupUi(this);

    for (auto & fh : *functionsLibrary_) {
       ui->comboBoxFunc->addItem(QString::fromStdString(fh.first) );

    }

}

DialogModel::~DialogModel()

{
    delete ui;
}

std::vector<double> DialogModel::parseTxtToVector(QLineEdit *lineEdit)
{

        QString txt  = lineEdit->text();
        QStringList value_list = txt.split(" ");
        std::vector<double> v;
        bool ok;
        for (qsizetype i = 0 ; i < value_list.size(); ++i){
           double value = value_list[i].toDouble(&ok);
           if (ok) {
               v.push_back(value);
               qDebug() << v[i] << " ";
           }

        }


        return v;

}

void DialogModel::on_buttonBox_accepted()
{
       auto funcStrView = ui->comboBoxFunc->currentText().toStdString();
       std::vector<double> startPoint = parseTxtToVector(ui->lineEdit_coords);
       int iterCount = ui->lineEdit_iterCount->text().toInt();

       double alpha = ui->lineEdit_4->text().toDouble();




       FunctionHandler fh{(*functionsLibrary_)[funcStrView].objectFunction(),
                         (*functionsLibrary_)[funcStrView].gradFunction()};

       if ((*functionsLibrary_)[funcStrView].dim() != startPoint.size()) {
           reject();
           return;
       } else {
           fh.setDim((*functionsLibrary_)[funcStrView].dim());
       }

       model_->setFunctionHandler(fh);
       model_->setAlpha(alpha);
       model_->setStartPoint(startPoint);
       model_->setGradientThreshHold(1e-09);
       model_->setIterCount(iterCount);

       accept();


}

