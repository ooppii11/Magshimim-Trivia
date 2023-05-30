// ignore_for_file: unused_local_variable

import 'package:flutter/material.dart';
import 'Pages/loginPage.dart';
import 'SocketService.dart';

Future<void> main() async {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    // Create an instance of SocketService
    final SocketService socketService = SocketService();
    socketService.connect();

    return MaterialApp(
      home: LoginPage(socketService: socketService),
    );
  }
}
