#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    functionsLibrary_ = new FunctionsLibrary();
    setFunctionsLibrary();


    counterPlot_ = createCounterPlot();
    loadCounterPlot(counterPlot_);




}

MainWindow::~MainWindow()
{
    delete counterPlot_;
    delete functionsLibrary_;
    delete model_;
    delete ui;
}

void MainWindow::loadCounterPlot( QCustomPlot * customPlot)
{
    if (customPlot){
        ui->verticalLayout->addWidget(customPlot);
    }


}

void MainWindow::setFunctionsLibrary()
{
    {
        auto f1View = "(1 - x) * (1 - x) + 100 * (y - x * x) * (y - x * x)";
        auto f1 = [](const Point &  functionLoc) {
            double x = functionLoc.at(0);
            double y = functionLoc.at(1);
            return (1 - x) * (1 - x) + 100 * (y - x * x) * (y - x * x);
        };
        auto f1_dx = [](const Point &  functionLoc) {
            double x = functionLoc.at(0);
            double y = functionLoc.at(1);
            return x * (400* x * x + 2) - 400*x*y - 2;
        };
        auto f1_dy = [](const Point &  functionLoc) {
            double x = functionLoc.at(0);
            double y = functionLoc.at(1);
            return 200*y - 200* x * x;
        };

        FunctionHandler fh_1(f1,{f1_dx,f1_dy},f1View);
        (*functionsLibrary_)[f1View] = fh_1;
    }

    {
        auto f2View = "(x * x * cos(x) - x) / 10";
        auto f2 = [](const Point &  functionLoc) {
            double x = functionLoc.at(0);
            return (x * x * cos(x) - x) / 10;
        };
        auto f2_dx = [](const Point &  functionLoc) {
            double x = functionLoc.at(0);
            return -1./10*x*x*sin(x) + 1./5*x*cos(x) - 1./10;
        };

        FunctionHandler fh_2(f2,{f2_dx},f2View);
        (*functionsLibrary_)[f2View] = fh_2;


    }
    {
        auto f3View = "x^4 + 2 * x^3 - 6 * x^2 + 4*x + 2";
        auto f3 = [](const Point &  functionLoc) {
            double x = functionLoc.at(0);
            return pow(x,4) + 2 * pow(x,3) - 6 * x *x + 4*x + 2;
        };
        auto f3_dx = [](const Point &  functionLoc) {
            double x = functionLoc.at(0);
            return 4 * pow(x,3) + 6 * x * x - 12 * x + 4;
        };

        FunctionHandler fh_3(f3,{f3_dx},f3View);
        (*functionsLibrary_)[f3View] = fh_3;

    }










}

QCustomPlot *MainWindow::createCounterPlot()
{
    QCustomPlot * customPlot = new QCustomPlot();
    customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    customPlot->axisRect()->setupFullAxesBox(true);
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(-4, 4), QCPRange(-4, 4)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        double r = 3*qSqrt(x*x+y*y)+1e-2;
        z = 2*x*(qCos(r+2)/r-qSin(r+2)/r); // the B field strength of dipole radiation (modulo physical constants)
        colorMap->data()->setCell(xIndex, yIndex, z);
      }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Magnetic Field Strength");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    customPlot->rescaleAxes();

    return customPlot;
}


void MainWindow::on_actionSet_Model_triggered()
{
    DialogModel * dlg = new DialogModel(this,model_);
    dlg->exec();
}

