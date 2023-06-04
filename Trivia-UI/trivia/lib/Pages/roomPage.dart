import 'package:flutter/material.dart';
import 'package:trivia/SocketService.dart';

class RoomPage extends StatefulWidget {
  final SocketService socketService;

  const RoomPage({super.key, required this.socketService});

  @override
  _RoomPage createState() => _RoomPage(socketService);
}

class _RoomPage extends State<RoomPage> {
  final SocketService _socketService;
  _RoomPage(this._socketService);

  @override
  Widget build(BuildContext context) {
    return Scaffold();
  }
}
