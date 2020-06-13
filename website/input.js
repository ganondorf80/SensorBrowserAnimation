			var Input={"KeyDown":0,"KeyUp":0,"KeyLeft":0,"KeyRight":0,"Space":0};
			function keyDown(){
				var keycode;
					if (window.event)	{
						if  (window.event.keyCode == 38) Input["KeyUp"]=1;
						if  (window.event.keyCode == 40) Input["KeyDown"]=1;
						if  (window.event.keyCode == 37) Input["KeyLeft"]=1;
						if  (window.event.keyCode == 39) Input["KeyRight"]=1;
						if  (window.event.keyCode == 32) Input["Space"]=1;
						if  (window.event.keyCode == 88) setTransformationOffsetZero("Motrak_Hand","Bone_00","aX");
					}; // if (window.event)
			}; // function

			function keyUp(){
				var keycode;
					if (window.event)	{
						if  (window.event.keyCode == 38) Input["KeyUp"]=0;
						if  (window.event.keyCode == 40) Input["KeyDown"]=0;
						if  (window.event.keyCode == 37) Input["KeyLeft"]=0;
						if  (window.event.keyCode == 39) Input["KeyRight"]=0;
						if  (window.event.keyCode == 32) Input["Space"]=0;
					}; // if (window.event)Öffnen Sie das Chrome-Menü > Einstellungen > Erweiterte Einstellungen anzeigen und deaktivieren Sie "V
			}; // function

			function ctrlCross(event){
				var y=window.innerHeight-event.touches[0].clientY;
//				var y=event.touches[0].clientY - event.currentTarget.y;
				var x=event.touches[0].clientX - event.currentTarget.x;
				var info="";
				info+="curTar.Y: "+event.currentTarget.y+"\r\n";
				info+="w.innerH: "+window.innerHeight+"\r\n";
				info+="X: "+x+"\r\n";
				info+="Y: "+y;
//				alert(info);
				Input["KeyRight"]=0;
				Input["KeyLeft"]=0;
				Input["KeyDown"]=0;
				Input["KeyUp"]=0;
				if ( (event.type=="touchmove") && (x>0) && (x<100) && (y>0) && (y<100) ){
					if (x<40) Input["KeyLeft"]=1;
					if (x>60) Input["KeyRight"]=1;
					if (y<40) Input["KeyDown"]=1;
					if (y>60) Input["KeyUp"]=1;
				}; // if (event.type="touchmove")
			}; // function


			function ctrlButton(event){

				Input["Space"]=0;
				if (event.type=="touchstart"){
					Input["Space"]=1;
				}; // if (event.type="touchstart")
			}; // function

