// ignore_for_file: constant_identifier_names
import 'dart:typed_data';
import 'dart:io';
import 'package:trivia/message.dart';
import 'dart:async';

const String SERVER_ADDRESS = '127.0.0.1';
//const String SERVER_ADDRESS = 'localhost';
const int SERVER_PORT = 6666;

class SocketService {
  late final Socket _socket;
  late StreamSubscription<Uint8List> _messageSubscription;
  late Stream<Uint8List> _bcStream;
  
  SocketService(this._socket)
  {
    _bcStream = _socket.asBroadcastStream();
  }

  void sendMessage(Message message) {
    _socket.add(message.encode());
    //_socket.write(message.encode().toString());
  }
  
  
  Future<Message> receiveMessage() async {
    _messageSubscription = _bcStream.listen((Uint8List data) {});
    _bcStream.drain();
    Uint8List messgeBytes =
        await convertSubscriptionToUint8List(_messageSubscription);
    return Message.BytesConstructor(messgeBytes);
  }
  
  /*
  Future<Message> receiveMessage() async {
  final completer = Completer<Message>();

  final subscription = _bcStream.listen((Uint8List data) async {
    final message = Message.BytesConstructor(data);
    completer.complete(message);
    await for (final nextData in _bcStream) {
      final nextMessage = Message.BytesConstructor(nextData);
    }
  });

  try {
    final message = await completer.future;
    return message;
  } finally {
    subscription.cancel();
  }
}
*/


  void close() {
    _socket.close();
    _bcStream.drain();
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



Future<Uint8List> convertSubscriptionToUint8List(
    StreamSubscription<Uint8List> subscription) {
  var completer = Completer<Uint8List>();
  var bytes = <int>[];

  subscription.onData((Uint8List data) {
    bytes.addAll(data);
  });

  subscription.onDone(() {
    final uint8List = Uint8List.fromList(bytes);
    completer.complete(uint8List);
  });

  return completer.future;
}

