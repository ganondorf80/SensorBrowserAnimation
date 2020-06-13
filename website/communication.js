const socket = new WebSocket('ws://127.0.0.1:8888','bone-stream');

var SensorData={};


function onMessage(event) {
	var dataJson=JSON.parse(event.data);
	SensorData=dataJson;

	var calValue=0;
	var Value=0;
	var dataByKey="<table>\r\n";
//	document.getElementById("data").innerHTML=event.data + "<br>\r\n-------<br>\r\n";

/*	
	Value    = parseInt(SensorData["Motrak_Hand"]["Bone_00"]["aX"]);	calValue = (Value + cal["Motrak_Hand"]["Bone_00"]["aX"]["offs"]) * cal["Motrak_Hand"]["Bone_00"]["aX"]["gain"];
	dataByKey+="<tr><td>aX:" + Value + "</td><td>" + calValue + "</td><tr>\r\n";

	Value    = parseInt(SensorData["Motrak_Hand"]["Bone_00"]["aY"]);	calValue = (Value + cal["Motrak_Hand"]["Bone_00"]["aY"]["offs"]) * cal["Motrak_Hand"]["Bone_00"]["aY"]["gain"];
	dataByKey+="<tr><td>aY:" + Value + "</td><td>" + calValue + "</td><tr>\r\n";

	Value    = parseInt(SensorData["Motrak_Hand"]["Bone_00"]["aZ"]);	calValue = (Value + cal["Motrak_Hand"]["Bone_00"]["aZ"]["offs"]) * cal["Motrak_Hand"]["Bone_00"]["aZ"]["gain"];
	dataByKey+="<tr><td>aZ:" + Value + "</td><td>" + calValue + "</td><tr>\r\n";

	Value    = parseInt(SensorData["Motrak_Hand"]["Bone_00"]["gX"]);	calValue = (Value + cal["Motrak_Hand"]["Bone_00"]["gX"]["offs"]) * cal["Motrak_Hand"]["Bone_00"]["gX"]["gain"];
	dataByKey+="<tr><td>gX:" + Value + "</td><td>" + calValue + "</td><tr>\r\n";

	Value    = parseInt(SensorData["Motrak_Hand"]["Bone_00"]["gY"]);	calValue = (Value + cal["Motrak_Hand"]["Bone_00"]["gY"]["offs"]) * cal["Motrak_Hand"]["Bone_00"]["gY"]["gain"];
	dataByKey+="<tr><td>gY:" + Value + "</td><td>" + calValue + "</td><tr>\r\n";

	Value    = parseInt(SensorData["Motrak_Hand"]["Bone_00"]["gZ"]);	calValue = (Value + cal["Motrak_Hand"]["Bone_00"]["gZ"]["offs"]) * cal["Motrak_Hand"]["Bone_00"]["gZ"]["gain"];
	dataByKey+="<tr><td>gZ:" + Value + "</td><td>" + calValue + "</td><tr>\r\n";

	dataByKey+="</table>\r\n";
	document.getElementById("dataByKey").innerHTML=dataByKey
*/
}; // onMessage
// Listen for messages

socket.addEventListener('message', onMessage);



function timeoutUpdate(){
	socket.send("getAll");
	setTimeout(timeoutUpdate,100);
};

setTimeout(timeoutUpdate,100);

