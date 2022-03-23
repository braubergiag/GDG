#ifndef DIALOGMODEL_H
#define DIALOGMODEL_H

#include <QDialog>
#include <QLineEdit>
#include <QDebug>
#include "model.h"
#include "functionhandler.h"
namespace Ui {
class DialogModel;
}

class DialogModel : public QDialog
{
    Q_OBJECT

public:
    explicit DialogModel(QWidget *parent = nullptr,
                         Model * model = nullptr);
    ~DialogModel();


    void UpdateCoordinatesListWidget();
    void LoadModelConfig();
    StoppingCriterion GetStoppingCriterion();
    void InitStoppingCriterion();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogModel *ui;
    Model * model_ = nullptr;

};

#endif // DIALOGMODEL_H
