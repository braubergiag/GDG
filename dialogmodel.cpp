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

    ui->rb_stop_1->setText("||grad f(x_{n})|| < eps");
    ui->rb_stop_2->setText("||x_{n} - x_{n-1}|| < eps");
    ui->rb_stop_3->setText("||f(x_{n}) - f(x_{n-1})|| < eps");

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


        for (auto i = 0; i < fh.dim(); ++i) {
            QListWidgetItem * item;
            item->setData(Qt::DisplayRole,"x" + QString::number(i) + ":" + QString::number(fh.startPoint().at(i)));
            ui->list_start_coords->addItem(item);
        }


       StoppingCriterion stoppingCriterion;
       if (ui->rb_stop_1->isChecked()) {
           stoppingCriterion = StoppingCriterion::byGradientMagnitude;
       } else if (ui->rb_stop_2->isChecked()) {
           stoppingCriterion = StoppingCriterion::byDeltaChangeMagnitude;
       } else if (ui->rb_stop_3->isChecked()) {
           stoppingCriterion = StoppingCriterion::byValueChangeMagnitude;
       }



       model_->setFunctionHandler(fh);
       model_->setAlpha(alpha);
       model_->setStoppingCriterion(stoppingCriterion);
       model_->setStartPoint(startPoint);
       model_->setGradientThreshHold(0.0000001);
       model_->setIterCount(iterCount);

       accept();


}

