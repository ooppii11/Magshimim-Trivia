import 'dart:async';
import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/message.dart';
import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/User.dart';

class RoomPage extends StatefulWidget {
  final SocketService socketService;
  final bool admin;
  final int roomId;

  const RoomPage({super.key, required this.socketService, required this.admin, required this.roomId});

  @override
  _RoomPage createState() => _RoomPage(socketService, admin, roomId);
}

class _RoomPage extends State<RoomPage> {
  late List<User> _users;
  late Timer _timer;
  final SocketService _socketService;
  final bool _admin;
  final int roomId;

  _RoomPage(this._socketService, this._admin, this.roomId);

  getUsersInRoom() async{
    _socketService.sendMessage(Message(0 /*TODO: set get users in room code*/, {}));
    final Message response = await _socketService.receiveMessage();
    if (response.getCode() == 0 /*TODO: set get users in room code*/) {
     
    }
  }

   void _startTimer() {
    _timer = Timer.periodic(const Duration(seconds: 3), (timer) {
      setState(() {
        getUsersInRoom();
        _timer.cancel();
      });
    });
  }
  @override
  void initState() {
    super.initState();
    _startTimer();
  }
  @override
  void dispose() {
    _timer.cancel();
    super.dispose();
  }


  @override
  @override
Widget build(BuildContext context) {
  return Scaffold(
    appBar: AppBar(
      backgroundColor: Colors.transparent,
      elevation: 0,
      actions: <Widget>[
        Padding(
          padding: const EdgeInsets.only(right: 20.0),
          child: IconButton(
            icon: const Icon(
              Icons.logout,
              color: Colors.black,
              size: 26.0,
            ),
            onPressed: () async {
              _socketService.sendMessage(Message(0 /*TODO: set leave room code*/, {}));
              final Message response = await _socketService.receiveMessage();
              if (response.getCode() == 0 /*TODO: set leave room code*/) {
                Navigator.pushReplacement(
                  context,
                  MaterialPageRoute(
                    builder: (_) => HomePage(
                      socketService: widget.socketService,
                    ),
                  ),
                );
              }
            },
          ),
        ),
      ],
    ),
    body: Column(
      children: [
        Container(
          height: MediaQuery.of(context).size.height * 0.25,
          color: Colors.lightBlue,
          padding: EdgeInsets.all(16.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Text(
                "Room Name",
                style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
              ),
              SizedBox(height: 8.0),
              Text(
                "Room ID: ${roomId.toString()}",
                style: TextStyle(fontSize: 16),
              ),
            ],
          ),
        ),
        Expanded(
          child: Container(
            color: Colors.blue,
            padding: EdgeInsets.all(16.0),
            child: SingleChildScrollView(
              child: Wrap(
                spacing: 16.0,
                runSpacing: 16.0,
                children: _users.map((user) => Text(user.getUsername())).toList(),
              ),
            ),
          ),
        ),
      ],
    ),
  );
}
}
