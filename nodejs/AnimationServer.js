var WebSocketServer = require('websocket').server;
var http = require('http');

const Net = require('net');


var wsPort=8888;
var IoTport=8889;

var IoTclientBuffer={};
var SensorArray={};


/*
    -------------------------------------------------------------
     \/ \/ \/   IoT Server STUFF    IoT Server STUFF     IoT Server STUFF   \/ \/ \/
    -------------------------------------------------------------
*/



const IoTserver = new Net.Server();
IoTserver.listen(IoTport, function() {
    console.log('IoT-Server       is listening on port ' + IoTport);
});


IoTserver.on('connection', function(socket) {
//    console.log('A new connection has been established.');
//    console.log(socket);

    var sRemoteAddress=socket.remoteAddress;
    if (typeof(IoTclientBuffer[String(sRemoteAddress)]) == "undefined") IoTclientBuffer[String(sRemoteAddress)]=new String("");//"";

    // Now that a TCP connection has been established, the server can send data to
    // the client by writing to its socket.
    //socket.write('Hello, client.');

    // The server can also receive data from the client by reading from its socket.
    socket.on('data', function(chunk) {
//        console.log('Data received from client: \r\n');
//        console.log(chunk.toString());
        var sRemoteAddress=socket.remoteAddress;
        IoTclientBuffer[String(sRemoteAddress)]+=chunk.toString();
        var sFrameEnd="//---END---";
        if (IoTclientBuffer[String(sRemoteAddress)].indexOf(sFrameEnd) > 0) {
            // Put Buffer to SensorArray
            var n = IoTclientBuffer[String(sRemoteAddress)].indexOf(sFrameEnd);
            var DeviceData=IoTclientBuffer[String(sRemoteAddress)].substring(0,n);
            DeviceData = JSON.parse(DeviceData);
            DeviceData["rxTimeStamp"]=String(Date.now());
            if (typeof(DeviceData["Info"]["name"]) != "undefined") SensorArray[DeviceData["Info"]["name"]]=DeviceData;
            else SensorArray[String(sRemoteAddress)]=DeviceData;
            IoTclientBuffer[String(sRemoteAddress)]="";
        };
    });

    // When the client requests to end the TCP connection with the server, the server
    // ends the connection.
    socket.on('end', function() {
        console.log('Closing connection with the client');
    });
});
    // Don't forget to catchJSON.stringify(SensorArray)-------------------------------------








var server = http.createServer(function(request, response) {
    console.log((new Date()) + ' Received request for ' + request.url);
    response.writeHead(404);
    response.end();
});

server.listen(wsPort, function() {
    console.log('WebSocket-Server is listening on port ' + wsPort);
});

wsServer = new WebSocketServer({httpServer: server, autoAcceptConnections: false});



function originIsAllowed(origin) {
    // put logic here to detect whether the specified origin is allowed.
    //console.log(origin);
    return true;
};



wsServer.on('request', function(request) {
    //console.log(request);
    if (!originIsAllowed(request.origin)) {
      // Make sure we only accept requests from an allowed origin
      request.reject();
      console.log((new Date()) + ' Connection from origin ' + request.origin + ' rejected.');
      return;
    };

    
    var connection = request.accept('bone-stream', request.origin);
//    console.log((new Date()) + ' Connection accepted.');

    connection.on('message', function(message) {
        if (message.type === 'utf8') {
//            console.log('Received Message: ' + message.utf8Data);
            if (message.utf8Data=="getAll") {
                //console.log(JSON.stringify(SensorArray));
                connection.sendUTF(JSON.stringify(SensorArray));
            }; // if getAll
        }
        else if (message.type === 'binary') {
            console.log('Received Binary Message of ' + message.binaryData.length + ' bytes');
            connection.sendBytes(message.binaryData);
        }
    }); // on 'message'
    connection.on('close', function(reasonCode, description) {
        console.log((new Date()) + ' Peer ' + connection.remoteAddress + ' disconnected.');
    });// on 'close'
}); //wsServer.on 'request'
