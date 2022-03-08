#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    functionsLibrary_ = new FunctionsLibrary();
    setFunctionsLibrary();

    counterPlot_ = new QCustomPlot();
    ui->verticalLayout->addWidget(counterPlot_);


    model_ = new Model();

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
        int dim = 2;
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

        FunctionHandler fh_1(f1,{f1_dx,f1_dy},dim,f1View);
        (*functionsLibrary_)[f1View] = fh_1;
    }

    {
        int dim = 1;
        auto f2View = "(x * x * cos(x) - x) / 10";
        auto f2 = [](const Point &  functionLoc) {
            double x = functionLoc.at(0);
            return (x * x * cos(x) - x) / 10;
        };
        auto f2_dx = [](const Point &  functionLoc) {
            double x = functionLoc.at(0);
            return -1./10*x*x*sin(x) + 1./5*x*cos(x) - 1./10;
        };

        FunctionHandler fh_2(f2,{f2_dx},dim,f2View);
        (*functionsLibrary_)[f2View] = fh_2;


    }
    {
        int dim = 1;
        auto f3View = "x^4 + 2 * x^3 - 6 * x^2 + 4*x + 2";
        auto f3 = [](const Point &  functionLoc) {
            double x = functionLoc.at(0);
            return pow(x,4) + 2 * pow(x,3) - 6 * x *x + 4*x + 2;
        };
        auto f3_dx = [](const Point &  functionLoc) {
            double x = functionLoc.at(0);
            return 4 * pow(x,3) + 6 * x * x - 12 * x + 4;
        };

        FunctionHandler fh_3(f3,{f3_dx},dim,f3View);
        (*functionsLibrary_)[f3View] = fh_3;

    }
    {
        int dim = 2;
        auto f4View = "x * x + y * y";
        auto f4 = [](const Point & functionLoc) {
            double x = functionLoc.at(0);
            double y = functionLoc.at(1);
            return x * x + y * y;

        };
        auto f4_dx = [](const Point& functionLoc) {
            double x  = functionLoc.at(0);
            return 2 * x;
        };
        auto f4_dy = [](const Point& functionLoc) {
            double y  = functionLoc.at(1);
            return 2 * y;
        };
        FunctionHandler fh_4(f4,{f4_dx,f4_dy},dim,f4View);
        std::vector<Domain> domain = {{-2,2},{-2,2}};
        fh_4.setFunctionDomain(domain);
        fh_4.setStartPoint({0,0});
        (*functionsLibrary_)[f4View] = fh_4;
    }
    {


        int dim = 2;
        auto f5View = "x * exp(-|y|^2)";
        auto f5 = [](const Point & functionLoc) {
            double x = functionLoc.at(0);
            double y = functionLoc.at(1);
            return x * exp(-pow(abs(y),2));
        };
        auto f5_dx = [](const Point& functionLoc) {
            double x  = functionLoc.at(0);
            double y  = functionLoc.at(1);
            return exp(-pow(abs(y),2));
        };
        auto f5_dy = [](const Point& functionLoc) {
            double x  = functionLoc.at(0);
            double y  = functionLoc.at(1);
            return -2 * x * exp(-pow(y,2)) * y;
        };
        FunctionHandler fh_5(f5,{f5_dx,f5_dy},dim,f5View);
        std::vector<Domain> domain = {{-2,2},{-2,2}};
        fh_5.setFunctionDomain(domain);
        fh_5.setStartPoint({0,0});
        (*functionsLibrary_)[f5View] = fh_5;

    }
    {
        int dim = 2;
        auto f6View = "400 * (pow(sin(x/30),2) + (pow(cos(y/30),2)))";
        auto f6 = [](const Point & functionLoc) {
            double x = functionLoc.at(0);
            double y = functionLoc.at(1);
            return 400 * (pow(sin(x/30),2) + (pow(cos(y/30),2)));
        };
        auto f6_dx = [](const Point& functionLoc) {
            double x  = functionLoc.at(0);
            double y  = functionLoc.at(1);
            return 80./3 * sin(x/30.) * cos(x/30.);
        };
        auto f6_dy = [](const Point& functionLoc) {
            double x  = functionLoc.at(0);
            double y  = functionLoc.at(1);
            return -80./3 * sin(y/30.) * cos(y/30.);
        };
        FunctionHandler fh_6(f6,{f6_dx,f6_dy},dim,f6View);
        std::vector<Domain> domain = {{-2,2},{-2,2}};
        fh_6.setFunctionDomain(domain);
        fh_6.setStartPoint({0,0});
        (*functionsLibrary_)[f6View] = fh_6;
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
    int nx = 10;
    int ny = 10;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(-100, 100), QCPRange(-100, 100)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;

    for (int xIndex=0; xIndex<nx; ++xIndex )
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        auto func = model_->functionHandler().objectFunction();
        z = func({x,y});
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
    colorMap->setGradient(QCPColorGradient::gpThermal);
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




    //QCustomPlot * customPlot = new QCustomPlot();

    QVector<double> x1,y1;
     model_->setHistory(model_->gd().history());
    for (auto i = 1; i < model_->history().size(); ++i){
        x1.push_back( model_->history().at(i).at(0));
        y1.push_back(model_->history().at(i).at(1));
    }


    customPlot->addGraph();
    customPlot->graph(0)->setData(x1,y1);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot));
    QString graphTitle = QString("graphTitle");
    customPlot->graph(0)->setName(graphTitle);

    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(-10,10);


    customPlot->yAxis->setRange(-10,10);


    QVector<double> ticks;
    QVector<QString> labels;
//    for (const auto & value: model->sampleSizeInterval()){
//        ticks << value;
//        labels << QString::number(value);
//    }


//    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
//    textTicker->addTicks(ticks, labels);
//    customPlot->xAxis->setTicker(textTicker);
//    customPlot->xAxis->setTickLabelRotation(60);

    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);
//     QFont legendFont = font();
//     legendFont.setPointSize(10);
//     customPlot->legend->setFont(legendFont);
    //customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);



    QString info = "info";
    customPlot->plotLayout()->insertRow(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, info, QFont("sans", 10, QFont::Normal)));
    customPlot->replot();

    return customPlot;
}


void MainWindow::on_actionSet_Model_triggered()
{
    DialogModel * dlg = new DialogModel(this,model_,functionsLibrary_ );
    dlg->exec();
    if (dlg->result() == QDialog::Accepted){
        model_->Run();

        if (counterPlot_) {
            ui->verticalLayout->removeWidget(counterPlot_);
            delete counterPlot_;
            counterPlot_ = nullptr;
        }

        counterPlot_ = createCounterPlot();
        loadCounterPlot(counterPlot_);
    }

}

