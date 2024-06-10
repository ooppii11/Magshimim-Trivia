import 'dart:async';
import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/message.dart';
import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/User.dart';
import 'package:trivia/room.dart';
import 'package:trivia/components/erroToast.dart';
import 'package:trivia/Pages/QuestionPage.dart';
//import 'dart:convert';

class RoomPage extends StatefulWidget {
  final SocketService socketService;
  final bool admin;
  final int roomId;

  const RoomPage(
      {Key? key,
      required this.socketService,
      required this.admin,
      required this.roomId})
      : super(key: key);

  @override
  _RoomPageState createState() => _RoomPageState(socketService, admin, roomId);
}

class _RoomPageState extends State<RoomPage> {
  late List<User> _users = [];
  late Timer _timer;
  final SocketService _socketService;
  final bool _admin;
  final int _roomId;
  bool _hasGameBegun = false;
  late double _questionTimeout;
  late int _numOfQuestionsInGame;

  _RoomPageState(this._socketService, this._admin, this._roomId) {
    getUsersInRoom();
  }

  getUsersInRoom() async {
    _users.clear();
    if (_hasGameBegun) {
      _timer.cancel();
      Future.delayed(Duration.zero, () {
        Navigator.pushReplacement(
            context,
            MaterialPageRoute(
                builder: (_) => QuestionPage(
                    socketService: _socketService,
                    maxTimePerQuestion: _questionTimeout,
                    currentQuestionNumber: 0,
                    numberOfQuestion: _numOfQuestionsInGame)));
      });
    } else {
      _socketService.sendMessage(Message(19, {}));
      final Message response = await _socketService.receiveMessage();
      if (response.getCode() == 18) {
        List<dynamic> dynamicList = response.getData()["players"];
        List<String> data =
            dynamicList.map((element) => element.toString()).toList();
        List<User> updatedUsers = [];
        for (var user in data) {
          updatedUsers.add(User(user, 0));
        }
        int timeout = response.getData()["answerTimeout"];
        setState(() {
          _users = updatedUsers;
          _numOfQuestionsInGame = response.getData()["questionCount"];
          _questionTimeout = timeout.toDouble();
          _hasGameBegun = response.getData()["hasGameBegun"];
        });
      } else if (response.getCode() == 99) {
        //await _socketService.receiveMessage();
        if (response
            .getData()["Error"]
            .toString()
            .contains("Admin closed the Room")) {
          errorToast(context, response.getData()["Error"], 2);
        }
        _timer.cancel();
        Navigator.pushReplacement(
          context,
          MaterialPageRoute(
            builder: (_) => HomePage(
              socketService: widget.socketService,
            ),
          ),
        );
      }
    }
  }

  void _startTimer() {
    _timer = Timer.periodic(const Duration(milliseconds: 200), (timer) {
      getUsersInRoom();
    });
  }

  Future<void> leaveRoom() async {
    _timer.cancel();
    bool error = false;
    if (_admin) {
      _socketService.sendMessage(Message(17, {}));
      final response = await _socketService.receiveMessage();
      if (response.getCode() != 16) {
        error = true;
      }
    } else {
      _socketService.sendMessage(Message(20, {}));
      final Message response = await _socketService.receiveMessage();
      if (response.getCode() != 19) {
        error = true;
      }
    }
    if (!error) {
      
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(
          builder: (_) => HomePage(
            socketService: widget.socketService,
          ),
        ),
      );
    }
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
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Colors.transparent,
        elevation: 0,
        actions: <Widget>[
          Padding(
            padding: const EdgeInsets.only(top: 15, bottom: 15),
            child: Container(
              height: 20,
              decoration: BoxDecoration(
                color: Colors.redAccent,
                borderRadius: BorderRadius.circular(12.5),
              ),
              child: TextButton(
                child: Text(
                  "Leave Room",
                  style: TextStyle(fontSize: 20, color: Colors.white),
                ),
                onPressed: () async {
                  await leaveRoom();
                },
              ),
            ),
          ),
        ],
      ),
      body: Container(
        decoration: BoxDecoration(
        gradient: LinearGradient(
        //colors: [Color(0xff1542bf), Color(0xff51a8ff)],
        colors: [Color.fromARGB(255, 29, 45, 68), Color.fromARGB(255, 81, 168, 255)],
        begin: FractionalOffset(0.5, 1)
        ) // LinearGradient
        ), // BoxDecoration
      child: Column(
          children: [
            Container(
              height: MediaQuery.of(context).size.height * 0.15,
              width: MediaQuery.of(context).size.width,
              color: Color.fromARGB(255, 111, 156, 235),
              padding: const EdgeInsets.all(16.0),
              child: SingleChildScrollView(
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Align(
                    alignment: Alignment.center,
                    child: const Text(
                      "Room Name",
                      style: TextStyle(fontSize: 24, color: Colors.black),
                    ),
                  ),
                  Align(
                    alignment: Alignment.center,
                    child: const SizedBox(height: 8.0),
                  ),
                  Align(
                    alignment: Alignment.center,
                    child: Text(
                      "Room ID: ${_roomId.toString()}",
                      style: const TextStyle(
                        fontSize: 22,
                        fontWeight: FontWeight.bold,
                        color: Colors.black,
                      ),
                    ),
                  ),
                ],
              ),
              ),
            ),
            Expanded(
              child: Container(
                //height: MediaQuery.of(context).size.height * 0.7,
                width: MediaQuery.of(context).size.width,
                //color: Color.fromARGB(255, 29, 45, 68),
                padding: const EdgeInsets.all(16.0),
                child: SingleChildScrollView(
                  child: Align(
                    alignment: Alignment.topLeft,
                    child: Wrap(
                      spacing: 16.0,
                      runSpacing: 16.0,
                      children: _users
                          .map(
                            (user) => Container(
                              padding: EdgeInsets.symmetric(
                                vertical: 4.0,
                                horizontal: 8.0,
                              ),
                              decoration: BoxDecoration(
                                color: Color.fromARGB(255, 88, 128, 185),
                                borderRadius: BorderRadius.circular(8.0),
                              ),
                              child: Text(
                                user.getUsername(),
                                style: TextStyle(
                                  color: Colors.black,
                                  fontSize: 20,
                                ),
                              ),
                            ),
                          )
                          .toList(),
                    ),
                  ),
                ),
              ),
            ),
            if (_admin)
              Container(
                height: MediaQuery.of(context).size.height * 0.15,
                width: MediaQuery.of(context).size.width,
                //color: Color.fromARGB(255, 29, 45, 68),
                padding: const EdgeInsets.all(16.0),
                child: Align(
                  alignment: Alignment.bottomCenter,
                  child: Container(
                    padding: const EdgeInsets.all(16.0),
                    decoration: BoxDecoration(
                      color: Color.fromARGB(255, 50, 101, 172),
                      borderRadius: BorderRadius.circular(32.0),
                    ),
                    child: ElevatedButton(
                      style: ElevatedButton.styleFrom(
                        minimumSize: Size(90, 64.0),
                        backgroundColor: Color.fromARGB(255, 196, 255, 249),
                        shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(32.0),
                        ),
                      ),
                      child: Text(
                        "Start Game",
                        style: TextStyle(fontSize: 20, color: Colors.black),
                      ),
                      onPressed: () async {
                        _timer.cancel();
                        _socketService.sendMessage(Message(18, {}));
                        final Message response =
                            await _socketService.receiveMessage();
                        if (response.getCode() == 17) {

                          Navigator.pushReplacement(
                            context,
                            MaterialPageRoute(
                              builder: (_) => QuestionPage(
                                socketService: _socketService,
                                maxTimePerQuestion: _questionTimeout,
                                currentQuestionNumber: 0,
                                numberOfQuestion: _numOfQuestionsInGame,
                              ),
                            ),
                          );
                        }
                      },
                    ),
                  ),
                ),
              ),
          ],
        ),
      ),
    );
  }
}
