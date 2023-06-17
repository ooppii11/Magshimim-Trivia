import 'package:flutter/material.dart';
import 'package:trivia/SocketService.dart';

class GamePage extends StatefulWidget {
  final SocketService socketService;
  final bool admin;
  final int roomId;
  final int questionTimeout;
  final int numOfQuestionsInGame;

  const GamePage(
      {Key? key,
      required this.socketService,
      required this.admin,
      required this.roomId,
      required this.numOfQuestionsInGame,
      required this.questionTimeout})
      : super(key: key);

  @override
  _GamePageState createState() => _GamePageState(socketService, admin, roomId);
}

class _GamePageState extends State<GamePage> {
  final SocketService _socketService;
  final bool _admin;
  final int roomId;

  _GamePageState(this._socketService, this._admin, this.roomId);

  @override
  Widget build(BuildContext context) {
    return Scaffold();
  }
}
