import 'package:flutter/material.dart';
import 'package:trivia/SocketService.dart';

class RoomPage extends StatefulWidget {
  final SocketService socketService;
  final bool admin;

  const RoomPage({super.key, required this.socketService, required this.admin});

  @override
  _RoomPage createState() => _RoomPage(socketService, this.admin);
}

class _RoomPage extends State<RoomPage> {
  final SocketService _socketService;
  final bool _admin;

  _RoomPage(this._socketService, this._admin);

  @override
  Widget build(BuildContext context) {
    return Scaffold();
  }
}
