// ignore_for_file: unused_local_variable

import 'package:flutter/material.dart';
import 'Pages/loginPage.dart';
import 'package:trivia/SocketService.dart';

Future<void> main() async {
  final socket = await createSocket();
  SocketService socketService = SocketService(socket);

  // Call the MyApp widget and pass the socketService instance
  runApp(MyApp(socketService));
  /*// Send data to the server
  final message = 'Hello, server!';
  socket.write(message);

  // Receive data from the server
  socket.listen((List<int> data) {
    final message = String.fromCharCodes(data).trim();
    print('Received message from server: $message');
  });*/
}

class MyApp extends StatelessWidget {
  final SocketService socketService;

  const MyApp(this.socketService, {Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: LoginPage(socketService: socketService),
    );
  }
}
