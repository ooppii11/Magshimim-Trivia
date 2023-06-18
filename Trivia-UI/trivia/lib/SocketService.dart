// ignore_for_file: constant_identifier_names
import 'dart:typed_data';
import 'dart:io';
import 'package:trivia/message.dart';
import 'dart:async';

//const String SERVER_ADDRESS = '127.0.0.1';
const String SERVER_ADDRESS = '10.10.0.13';
//const String SERVER_ADDRESS = 'localhost';
const int SERVER_PORT = 6666;

class SocketService {
  late final Socket? _socket;
  late StreamController<Message> _streamController;

  SocketService(this._socket) {
    _streamController = StreamController<Message>.broadcast();
    _receiveDataFromSocket();
  }

  void _receiveDataFromSocket() {
    _socket?.listen((Uint8List data) {
      final message = Message.BytesConstructor(data);
      _streamController.add(message);
    }, onError: (error) {
      print('Socket communication error: $error');
    }, onDone: () {
      _streamController.close();
    });
  }

  void resetStreamController() {
    _streamController = StreamController<Message>.broadcast();
  }

  void sendMessage(Message message) {
    _socket?.add(message.encode());
  }

  Future<Message> receiveMessage() async {
    return await _streamController.stream.first;
  }


  void close() {
    _streamController.close();
    _socket?.close();
  }
}

Future<Socket> createSocket() async {
  try {
    final socket = await Socket.connect(SERVER_ADDRESS, SERVER_PORT);
    print(
        'Connected to server: ${socket.remoteAddress.address}:${socket.remotePort}');
    return socket;
  } catch (error) {
    print('Socket connection error: $error');
    rethrow;
  }
}
