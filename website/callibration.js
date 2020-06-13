var cal={};
cal["Motrak_Hand"]={"Bone_00":{
"aX":{"offs":-200,"gain":(1.5708/4100)},"aY":{"offs":50,"gain":(1.5708/4100)},"aZ":{"offs":175,"gain":(1.5708/4200)},
"gX":{"offs":2,"gain":1},"gY":{"offs":-30,"gain":(90/22000)},"gZ":{"offs":16,"gain":1}
}};




cal["dummy"]={"Bone_00":{
"aX":{"offs":0,"gain":1},"aY":{"offs":0,"gain":1},"aZ":{"offs":0,"gain":1},
}};

cal["dummy"]={"Bone_00":{
"aX":{"offs":"0","gain":"1"},"aY":{"offs":"0","gain":"1"},"aZ":{"offs":"0","gain":"1"},
"gX":{"offs":"0","gain":"1"},"gY":{"offs":"0","gain":"1"},"gZ":{"offs":"0","gain":"1"},
}};



function getCalValue(device,element,axis){
	try {
		var Value=parseInt(SensorData[device][element][axis]);
		Value = (Value + cal[device][element][axis]["offs"]) * cal[device][element][axis]["gain"];
		return Value;
	} catch{
		return 0;
	};
};
