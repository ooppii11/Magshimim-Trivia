import 'package:flutter/material.dart';
import 'package:trivia/SocketService.dart';

class BasePage extends StatelessWidget {
  final SocketService socketService;
  const BasePage({super.key, required this.socketService});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('App Title'),
      ),
      body: Container(
          // Base page content
          ),
    );
  }
}
