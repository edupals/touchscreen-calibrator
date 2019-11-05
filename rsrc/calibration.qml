import QtQuick 2.6

Canvas
{
    id: calibrationwindow
    anchors.fill: parent
    property variant pointState:[0,0,0,0]
    property variant current: 0
    //var currentPoint=0
    
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
                
                if (state==0) {
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
            var status=calibrationwindow.pointState[calibrationwindow.current];
            
            if (status<10) {
                calibrationwindow.pointState[calibrationwindow.current]=status+1;
            }
            else {
                running=false;
                calibrationwindow.current=(calibrationwindow.current+1)%4;
            }
            
            calibrationwindow.requestPaint();
        }
    }
    
    MouseArea {
        anchors.fill: parent
        
        onPressed: {
            timer.start()
        }
        
        onReleased: {
            timer.stop()
            
            var status=calibrationwindow.pointState[calibrationwindow.current];
            
            if (status>0 && status<10) {
                calibrationwindow.pointState[calibrationwindow.current]=0;
            }
        }
    }

}