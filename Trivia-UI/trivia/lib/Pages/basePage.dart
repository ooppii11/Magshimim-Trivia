import 'package:flutter/material.dart';
import 'package:trivia/SocketService.dart';

class BasePage extends StatelessWidget {
  final SocketService socketService;
  BasePage({required this.socketService});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('App Title'),
      ),
      body: Container(
          // Base page content
          ),
    );
  }
}
