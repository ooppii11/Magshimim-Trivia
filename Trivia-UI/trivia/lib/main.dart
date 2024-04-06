// ignore_for_file: unused_local_variable

import 'package:flutter/material.dart';
import 'Pages/loginPage.dart';
import 'package:trivia/SocketService.dart';

Future<void> main() async {
  final socket = await createSocket();
  SocketService socketService = SocketService(socket);

  // Call the MyApp widget and pass the socketService instance
  runApp(MyApp(socketService));
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
