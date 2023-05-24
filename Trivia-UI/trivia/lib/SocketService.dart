// ignore_for_file: constant_identifier_names

import 'dart:io';

const int PORT = 5555;
const String ADDRESS = '127.0.0.1';

class SocketService {
  late Socket _socket;

  Future<void> connect() async {
    // Connect to the server
    _socket = await Socket.connect(ADDRESS, PORT);
    print('Connected to: '
        '${_socket.remoteAddress.address}:${_socket.remotePort}');
  }

  void sendRequest(String request) {
    // Send request to the server
    _socket.write(request);
  }

  void close() {
    // Close the socket connection
    _socket.close();
  }
}
