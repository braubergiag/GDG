#ifndef DIALOGMODEL_H
#define DIALOGMODEL_H

#include <QDialog>
#include "model.h"
namespace Ui {
class DialogModel;
}

class DialogModel : public QDialog
{
    Q_OBJECT

public:
    explicit DialogModel(QWidget *parent = nullptr);
    ~DialogModel();

private:
    Ui::DialogModel *ui;
    Model * model_ = nullptr;
};

#endif // DIALOGMODEL_H
