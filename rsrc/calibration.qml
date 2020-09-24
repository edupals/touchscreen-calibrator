import org.kde.kirigami 2.4 as Kirigami
import QtQuick 2.6
import QtQuick.Controls 2.6 as QQC2

Canvas
{
    id: calibrationWindow
    anchors.fill: parent
    property variant pointState:[0,0,0,0]
    property variant current: 0
    property variant points:[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
    //var currentPoint=0

    Connections {
        target: proxy
        function onButtonPressed(x,y) {
            //console.log("qml pressed "+x+","+y);
            timer.start()
        }
        
        function onButtonReleased(x,y) {
            //console.log("qml released "+x+","+y);
            timer.stop()
            
            var status=calibrationWindow.pointState[calibrationWindow.current];
            
            if (status>0 && status<10) {
                calibrationWindow.pointState[calibrationWindow.current]=0;
                calibrationWindow.requestPaint();
            }
            else {
                var px = x/calibrationWindow.width;
                var py = y/calibrationWindow.height;
                console.log("Using point:"+px+","+py);
                var n=(current-1)*2;
                points[n]=px;
                points[n+1]=py;
                
                if (calibrationWindow.current==4) {
                    console.log("pushing calibration...");
                    proxy.pushPoints(calibrationWindow.points);
                    
                    calibrationWindow.current=0;
                }
            }
        }
    }
    
    QQC2.Dialog {
        id: dlgSelection
        width:500
        height:500
        anchors.centerIn: parent
        modal: true
        visible:true
        title: "Select an input device"
        standardButtons: QQC2.Dialog.Ok | QQC2.Dialog.Cancel
        
        //onAccepted: accept(devices[devicesList.currentIndex].id);
        onAccepted: proxy.accept(proxy.devices[devicesList.currentIndex].id);
        onRejected: proxy.cancel();
        
        ListView {
            //anchors.fill:parent
            height:450
            width:parent.width
            id: devicesList
            currentIndex: 2
            model: proxy.devices
            delegate: Kirigami.BasicListItem {
                label: proxy.devices[index].name
                checkable: true
                checked: devicesList.currentIndex == index
                separatorVisible: true
                reserveSpaceForIcon: false
            }
        }
        /*
        Row {
            anchors.top: devicesList.bottom
            anchors.right:parent.right
            spacing:10
            
            QQC2.Button {
                text: "Cancel"
                onClicked: cancel();
            }
            QQC2.Button {
                text: "Accept"
                onClicked: accept(devices[devicesList.currentIndex].id);
            }
        }
        */
    }

    onPaint: {
        var ctx = getContext("2d");
        ctx.fillStyle = "#fcfcfc";
        ctx.fillRect(0, 0, width, height);
        
        ctx.strokeStyle = "#bdc3c7";
        
        var stepH=height/20.0;
        
        for (var j=0;j<20;j++) {
            ctx.beginPath();
            
            ctx.moveTo(0,stepH*j);
            ctx.lineTo(width,stepH*j);
            
            ctx.stroke();
        }
        
        var stepW=width/20.0;
        
        for (var i=0;i<20;i++) {
            ctx.beginPath();
            
            ctx.moveTo(stepW*i,0);
            ctx.lineTo(stepW*i,height);
            
            ctx.stroke();
        }
        
        
        for (var i=0;i<2;i++) {
            for (var j=0;j<2;j++) {
                
                var p = i+j*2;
                var x = (0.1*width) + (i*0.8*width);
                var y = (0.1*height) + (j*0.8*height);
                
                var state = pointState[p];
                
                if (current==p && state==0) {
                    ctx.beginPath();
                    ctx.fillStyle = "#bdc3c7";
                    ctx.arc(x,y,10,0,2*3.1416,false);
                    ctx.fill();
                }
                
                if (state>0 && state<10) {
                    ctx.beginPath();
                    ctx.fillStyle = "#da4453";
                    ctx.arc(x,y,10,0,(state/10.0)*2*3.1416,false);
                    ctx.lineTo(x,y);
                    ctx.lineTo(x+5,y);
                    ctx.fill();
                }
                
                if (state==10) {
                    ctx.beginPath();
                    ctx.fillStyle = "#3498db";
                    ctx.arc(x,y,10,0,2*3.1416,false);
                    ctx.fill();
                }
            }
        }
        
    }
    
    Timer {
        id: timer
        interval: 100
        running: false
        repeat: true
        
        onTriggered: {
            var status=calibrationWindow.pointState[calibrationWindow.current];
            
            if (status<10) {
                calibrationWindow.pointState[calibrationWindow.current]=status+1;
            }
            else {
                running=false;
                calibrationWindow.current=calibrationWindow.current+1;
            }
            
            calibrationWindow.requestPaint();
        }
    }
}
