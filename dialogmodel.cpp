#include "dialogmodel.h"
#include "ui_dialogmodel.h"
#include <memory>
DialogModel::DialogModel(QWidget *parent,Model * model) :
    QDialog(parent),
    ui(new Ui::DialogModel),
    model_(model)
{
    ui->setupUi(this);


    // Loading functions
    for (const auto & fh : model_->functionsLibrary()) {
       ui->comboBoxFunc->addItem(QString::fromStdString(fh.first) );

    }
    double minDomain = -10e5;
    double maxDomain = 10e5;
    double minDomainRange = 0.01;
    ui->minDoubleSpinBox->setRange(minDomain,maxDomain- minDomainRange);
    ui->maxDoubleSpinBox->setRange(minDomain + minDomainRange,maxDomain);




    ui->sb_alpha->setSingleStep(0.001);
    ui->sb_alpha->setDecimals(3);
    ui->sb_alpha->setMinimum(0.001);
    ui->sb_alpha->setMaximum(1);


    ui->sb_iterCount->setSingleStep(1000);
    ui->sb_iterCount->setMaximum(10e9);


    if (model_->isInitialized()) {
        LoadModelConfig();
    } else {
        ui->sb_alpha->setValue(0.001);
        ui->sb_iterCount->setValue(1000);
        ui->cb_magnitude->setCurrentIndex(0);
    }





    // Сhanging minValue for Domain
    connect(ui->minDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),this,[=](double newValue) {
         if (ui->list_start_coords->currentRow() != -1) {
             ui->minDoubleSpinBox->setMaximum(ui->maxDoubleSpinBox->value());
             int itemIndex = ui->list_start_coords->currentRow();
             ui->list_start_coords->activateWindow();

             std::vector<Domain> domain = model_->functionHandler().getFunctionDomain();
             domain[itemIndex].first = newValue;
             model_->functionHandler().setFunctionDomain(domain);
             ui->startValueDoubleSpinBox->setMinimum(ui->minDoubleSpinBox->value());
         };

    });

    // Сhanging maxValue for Domain
    connect(ui->maxDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),this,[=](double newValue) {
         if (ui->list_start_coords->currentRow() != -1) {
             ui->maxDoubleSpinBox->setMinimum(ui->minDoubleSpinBox->value());
            int itemIndex = ui->list_start_coords->currentRow();
            std::vector<Domain> domain = model_->functionHandler().getFunctionDomain();
            domain[itemIndex].second = newValue;
            model_->functionHandler().setFunctionDomain(domain);
             ui->startValueDoubleSpinBox->setMaximum(ui->maxDoubleSpinBox->value());
        }


    });

    // Сhanging starValue
    connect(ui->startValueDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),this,[=](double newValue) {
        auto functionName = ui->comboBoxFunc->currentText().toStdString();
        if (ui->list_start_coords->currentRow() != -1) {
            int itemIndex = ui->list_start_coords->currentRow();
            Point point = model_->functionHandler().getStartPoint();
            point[itemIndex] = newValue;
            model_->functionHandler().setStartPoint(point);
        }


    });




    // Changing Function
    connect(ui->comboBoxFunc, QOverload<int>::of(&QComboBox::activated),
        [=](int index){

        ui->list_start_coords->clear();
        ui->list_start_coords->setCurrentRow(0);
        ui->startValueDoubleSpinBox->clear();
        ui->minDoubleSpinBox->clear();
        ui->maxDoubleSpinBox->clear();
        auto functionName = ui->comboBoxFunc->currentText().toStdString();


        model_->setFunctionHandler( model_->functionsLibrary().at(functionName));


        const auto & fh = model_->functionHandler();
         for (auto i = 0; i < fh.getDim(); ++i) {
             QListWidgetItem * item = new QListWidgetItem();
             QString coordiateData = "x" + QString::number(i + 1) + " : " + QString::number(fh.getStartPoint().at(i))
                     +    "\t [" + QString::number(fh.getFunctionDomain().at(i).first) + ", "
                     +    QString::number(fh.getFunctionDomain().at(i).second) + "]";
             item->setData(Qt::DisplayRole,coordiateData);
             ui->list_start_coords->addItem(item);
         }




    });

    // Show start Point and domain
    connect(ui->list_start_coords,&QListWidget::itemClicked,this,[=](QListWidgetItem *item){
        auto functionName = ui->comboBoxFunc->currentText().toStdString();
        int itemIndex = ui->list_start_coords->currentRow();

        ui->startValueDoubleSpinBox->setValue(model_->functionHandler().getStartPoint().at(itemIndex));
        ui->minDoubleSpinBox->setValue(model_->functionHandler().getFunctionDomain().at(itemIndex).first);
        ui->maxDoubleSpinBox->setValue(model_->functionHandler().getFunctionDomain().at(itemIndex).second);
        ui->startValueDoubleSpinBox->setRange(ui->minDoubleSpinBox->value(),ui->maxDoubleSpinBox->value());
    });


    // Updating start Point and domain
    connect(ui->btn_save,&QPushButton::clicked,this,[=](bool checked){
        ui->startValueDoubleSpinBox->clear();
        ui->minDoubleSpinBox->clear();
        ui->maxDoubleSpinBox->clear();
        UpdateCoordinatesListWidget();

    });


}

DialogModel::~DialogModel()

{
    delete ui;
}


void DialogModel::UpdateCoordinatesListWidget()
{


        ui->list_start_coords->clear();
        const auto & fh =  model_->functionHandler();

         for (auto i = 0; i < fh.getDim(); ++i) {
             QListWidgetItem * item = new QListWidgetItem();
             item->setData(Qt::DisplayRole,"x" + QString::number(i + 1) + " : " + QString::number(fh.getStartPoint().at(i))
                           +    "\t [" + QString::number(fh.getFunctionDomain().at(i).first) + ", "
                           +    QString::number(fh.getFunctionDomain().at(i).second) + "]");
             ui->list_start_coords->addItem(item);
         }



}

void DialogModel::LoadModelConfig()
{

      int index_1 = ui->comboBoxFunc->findText(QString::fromStdString(model_->functionHandler().getFunctionStrView()));
      if (index_1 != -1){
             ui->comboBoxFunc->setCurrentIndex(index_1);
       }

        ui->sb_alpha->setValue(model_->alpha());
        ui->sb_iterCount->setValue(model_->iterCount());
        int index_2 = ui->cb_magnitude->findText(QString::fromStdString(model_->getMagnitudeENotation()));
        if (index_2 != -1) {
          ui->cb_magnitude->setCurrentIndex(index_2);
        }

        InitStoppingCriterion();
        UpdateCoordinatesListWidget();


}

StoppingCriterion DialogModel::GetStoppingCriterion()
{

    if  (ui->rb_stop_1->isChecked()) {
        return StoppingCriterion::byGradientMagnitude;
    }
    else if (ui->rb_stop_2->isChecked()){
        return StoppingCriterion::byDeltaChangeMagnitude;
    }
    else if (ui->rb_stop_3->isChecked()){
        return StoppingCriterion::byValueChangeMagnitude;
    }
    else {
         qDebug() << "(Get) Using default stopping criterion";
         return StoppingCriterion::byGradientMagnitude;
    }


}

void DialogModel::InitStoppingCriterion()
{
    switch (model_->stoppingCriterion()) {
    case StoppingCriterion::byGradientMagnitude:
        ui->rb_stop_1->setChecked(true);
        break;
    case StoppingCriterion::byDeltaChangeMagnitude:
        ui->rb_stop_2->setChecked(true);
        break;
    case StoppingCriterion::byValueChangeMagnitude:
        ui->rb_stop_3->setChecked(true);
        break;
    default:
        qDebug() << "(Init) Load default stopping criterion";
        ui->rb_stop_1->setChecked(true);
        break;
    }
}

void DialogModel::on_buttonBox_accepted()
{


//       if (!model_->functionHandler()) {
//           reject();
//           perror("Function does not set");
//           return;

//       }


       model_->setAlpha(ui->sb_alpha->value());
       model_->setStoppingCriterion(GetStoppingCriterion());
       model_->setStartPoint(model_->functionHandler().getStartPoint());
       model_->setMagnitudeThreshHold((ui->cb_magnitude->currentText().toDouble());
       model_->setMagnitudeENotation(ui->cb_magnitude->currentText().toStdString());
       model_->setIterCount(ui->sb_iterCount->value());
       model_->setIsInitialized(true);


       accept();


}

