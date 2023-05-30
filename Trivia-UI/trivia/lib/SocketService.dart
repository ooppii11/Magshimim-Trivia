// ignore_for_file: constant_identifier_names
import 'package:socket_io_client/socket_io_client.dart' as SocketIO;
//import 'dart:io';

const int PORT = 5555;
const String ADDRESS = '127.0.0.1';

class SocketService {
  //late Socket _socket;
  late SocketIO.Socket _socket;

  Future<void> connect() async {
    _socket = SocketIO.io('http://localhost:5555', 
    SocketIO.OptionBuilder()
      .setTransports(['websocket']) // for Flutter or Dart VM
      .disableAutoConnect()  // disable auto-connection
      .disableForceNewConnection()
      .disableReconnection()
      .build()
  );
  _socket.connect();
  }

  void sendRequest(String request) {
    // Send request to the server
    //_socket.write(request);
  }

  void close() {
    // Close the socket connection
    //_socket.close();
  }
}
