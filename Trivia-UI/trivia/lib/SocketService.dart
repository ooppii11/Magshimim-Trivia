// ignore_for_file: constant_identifier_names
import 'dart:typed_data';
import 'dart:io';
import 'package:trivia/message.dart';
import 'dart:async';

const String SERVER_ADDRESS = '127.0.0.1';
const int SERVER_PORT = 6666;

class SocketService {
<<<<<<< HEAD
  late Socket? _socket;
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

  void sendMessage(Message message) {
    _socket?.add(message.encode());
  }

  Future<Message> receiveMessage() async {
    return await _streamController.stream.first;
=======
  late final Socket _socket;
  late StreamSubscription<Uint8List> _messageSubscription;
  late Stream<Uint8List> _bcStream;

  SocketService(this._socket) {
    _bcStream = _socket.asBroadcastStream();
  }
  void sendMessage(Message message) {
    _socket.add(message.encode());
  }

  Future<Message> receiveMessage() async {
    _messageSubscription = _bcStream.listen((Uint8List data) {});
    Uint8List messgeBytes =
        await convertSubscriptionToUint8List(_messageSubscription);
    return Message.BytesConstructor(messgeBytes);
>>>>>>> 03c6666be99a436906e18dc0001983516d1ad67f
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
