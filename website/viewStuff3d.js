

var ModelList=[
	{"file":"models/scene.glb","scale":new THREE.Vector3(1,1,1),"position":new THREE.Vector3(0,0,0)}
];

/*
var ModelList=[
	{"file":"models/Kayserbett_Olaf_Doors.glb","scale":new THREE.Vector3(1,1,1),"position":new THREE.Vector3(0,0,0)}
	,{"file":"models/Kayserbett_Olaf.glb","scale":new THREE.Vector3(1,1,1),"position":new THREE.Vector3(0,0,0)}
	,{"file":"models/home.glb","scale":new THREE.Vector3(1,1,1),"position":new THREE.Vector3(0,0,0)}
];
*/

var ModelLoaderState={
	"loadIndex":0,
	"modelList":ModelList
};


var AnimatedModels=[];


function loadModels_onSuccess(element){
	//scene.add(element.scene);	return;// DEBUG remove this line after code corrections like replace element by element.scene

	scene.add(element.scene);
	ModelLoaderState.loadIndex++;
	if (ModelLoaderState.loadIndex<ModelLoaderState.modelList.length) loadModels();
};

function loadModels_onProgress( element ){
	var test=1; // For Debug Breakpoint
};

function loadModels_onError( error){
	console.log("Error Loading Model \"" +  + "\".")
	console.error( error );
	ModelLoaderState.loadIndex++;
	if (ModelLoaderState.loadIndex<ModelLoaderState.modelList.length) loadModels();
};


function loadModels(){
	var loader = new THREE.GLTFLoader();
	if (ModelLoaderState.loadIndex<ModelLoaderState.modelList.length) {
		loader.load(ModelLoaderState.modelList[ModelLoaderState.loadIndex].file,loadModels_onSuccess,loadModels_onProgress,loadModels_onError);
	};// if Models remaining
};


function resize3Dviewport(){
	camera.aspect=window.innerWidth/window.innerHeight;
	renderer.setSize( window.innerWidth, window.innerHeight );
};


