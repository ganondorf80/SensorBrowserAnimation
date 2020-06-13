var transformationOffset={};

function setTransformationOffsetZero(device,element){
	if (typeof(SensorData[device]) == "undefined") return false;
	if (typeof(transformationOffset[device]) == "undefined") { transformationOffset[device] = {};transformationOffset[device][element]={}; };
	if (typeof(transformationOffset[device][element]) == "undefined") transformationOffset[device][element] = {"aX":0, "aY":0, "aZ":0, "gX":0, "gY":0, "gZ":0};
	transformationOffset[device][element]["aX"] = (getCalValue(device,element,"aX") * -1);
	transformationOffset[device][element]["aY"] = (getCalValue(device,element,"aY") * -1);
	transformationOffset[device][element]["aZ"] = (getCalValue(device,element,"aZ") * -1);
	transformationOffset[device][element]["gX"] = (getCalValue(device,element,"gX") * -1);
	transformationOffset[device][element]["gY"] = (getCalValue(device,element,"gY") * -1);
	transformationOffset[device][element]["gZ"] = (getCalValue(device,element,"gZ") * -1);
};


function collision(actor){
};

function TimeTransformation(){
};


function KeyboardTransformation(){
//	if ( (Input["KeyUp"] != 0)   && (collision["forward"]!=1) ) camera.translateZ(-0.2);//camera.position.z+=-1;
//	if ( (Input["KeyDown"] != 0) && (collision["backward"]!=1) ) camera.translateZ(0.2);//camera.position.z+=1;
	if ( (Input["KeyUp"] != 0) ) camera.translateZ(-0.2);//camera.position.z+=-1;
	if ( (Input["KeyDown"] != 0) ) camera.translateZ(0.2);//camera.position.z+=1;
	if (Input["KeyLeft"] != 0) camera.rotation.y+=0.08;
	if (Input["KeyRight"] != 0) camera.rotation.y+=-0.08;
};


function SensorTransformation(){
	if (typeof(transformationOffset["Motrak_Hand"])!="undefined") {
		scene.children[1].rotation.x=getCalValue("Motrak_Hand","Bone_00","aX")+transformationOffset["Motrak_Hand"]["Bone_00"]["aX"];
//		scene.children[1].rotation.y=getCalValue("Motrak_Hand","Bone_00","aY")+transformationOffset["Motrak_Hand"]["Bone_00"]["aY"];
		scene.children[1].rotation.z=-1*(getCalValue("Motrak_Hand","Bone_00","aY")+transformationOffset["Motrak_Hand"]["Bone_00"]["aY"]);
	}; // if Motrak_Hand
};
