import QtQuick 2.0
import QtCharts 2.14
import QtQuick.Controls 1.4

Rectangle{
    color: "white"

    function getSpringData(springIndex, row, col){
        var x = springs.getSpringData(springIndex, row, col);
        var y = springs.getSpringData(springIndex, 0, 1);
    }

    function updateChartView(index){
        chart.removeAllSeries();
        var series = chart.createSeries(ChartView.SeriesTypeLine, "Spring", xAxis, yAxis);
        series.pointsVisible = false;
        series.color = "blue";
        var pointsCount = springs.getNumberOfPoints();
        var minX = 0;
        var maxX = 0;
        var minY = 0;
        var maxY = 0;
        for(var j = 0;j < pointsCount;j ++)
        {
            var x = springs.getSpringData(index, j, 0);
            var y = springs.getSpringData(index, j, 1);
            series.append(x, y);
            if (x < minX){
                minX = x
            } else if (x > maxX){
                maxX = x
            }

            if (y < minY){
                minY = y
            } else if (y > maxY){
                maxY = y
            }
        }
        xAxis.min = minX;
        xAxis.max = maxX;
        yAxis.min = minY;
        yAxis.max = maxY;
    }

    function drawPoint(springIndex, pointIndex){
        chart.removeSeries(chart.series(1))
        var series2 = chart.createSeries(ChartView.SeriesTypeScatter, "Point", xAxis, yAxis);
        series2.color = "black";
        var x = springs.getSpringData(springIndex, pointIndex, 0);
        var y = springs.getSpringData(springIndex, pointIndex, 1);
        series2.append(x, y);
    }

    property double xMouse: 0;
    property double yMouse: 0;

    ChartView {
        id: chart
        anchors.fill: parent
        antialiasing: true
        legend.visible: false

        axes: [
            ValueAxis{
                id: xAxis
                min: -4
                max: 4
                titleText: "Displacement"
            },
            ValueAxis{
                id: yAxis
                min: -0.001
                max: 0.001
                titleText: "Force"
            }
        ]

        MouseArea{
            anchors.fill: parent
            onWheel: {
                if (wheel.angleDelta.y > 0){
                    xAxis.min =  xAxis.min * 1.1;
                    xAxis.max =  xAxis.max * 1.1;
                    yAxis.min =  yAxis.min * 1.1;
                    yAxis.max =  yAxis.max * 1.1;
                } else {
                    xAxis.min =  xAxis.min * 0.9;
                    xAxis.max =  xAxis.max * 0.9;
                    yAxis.min =  yAxis.min * 0.9;
                    yAxis.max =  yAxis.max * 0.9;
                }
            }
            onClicked: {
                xMouse = mouseX;
                yMouse = mouseY;
                contextMenu.popup();
            }
            onPressAndHold: {
                var x = mouseX - xMouse;
                var y = mouseY - yMouse;
                xAxis.min =  xAxis.min + x / 100;
                xAxis.max =  xAxis.max + x / 100;
                yAxis.min =  yAxis.min + y / 100;
                yAxis.max =  yAxis.max + y / 100;
            }
        }
    }

    Connections{
        target: springs
        onDoUpdateChart: {
          updateChartView(index)
        }
        onDoDrawPointChart:{
          drawPoint(springIndex, pointIndex)
        }
    }

    Menu {
        id: contextMenu
        MenuItem {
            text: "Show Data"
            onTriggered: {
                mainWindow.callDataWindow();
            }
        }
    }
}

