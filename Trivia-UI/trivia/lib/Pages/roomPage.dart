import 'dart:async';
import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/message.dart';
import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/User.dart';
import 'package:trivia/Pages/GamePage.dart';
//import 'dart:convert';

class RoomPage extends StatefulWidget {
  final SocketService socketService;
  final bool admin;
  final int roomId;

  const RoomPage({Key? key, required this.socketService, required this.admin, required this.roomId}) : super(key: key);

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
  late int _questionTimeout;
  late int _numOfQuestionsInGame;

  _RoomPageState(this._socketService, this._admin, this._roomId);

  getUsersInRoom() async {
    _users.clear();
    if (_hasGameBegun) {
      Future.delayed(Duration.zero, () {
        Navigator.pushReplacement(
          context,
          MaterialPageRoute(
            builder: (_) => GamePage(
              socketService: widget.socketService,
              admin: _admin,
              roomId: _roomId,
              questionTimeout: _questionTimeout,
              numOfQuestionsInGame: _numOfQuestionsInGame,
            ),
          ),
        );
      });
    }
    else
    {
      _socketService.sendMessage(Message(19 , {}));
      final Message response = await _socketService.receiveMessage();
      print("code:");
      print(response.getCode());
      print(response.getData());
      if (response.getCode() == 18 ) {
        List<dynamic> dynamicList = response.getData()["players"];
        List<String> data = dynamicList.map((element) => element.toString()).toList();
        print("data:");
        print(data);
        List<User> updatedUsers = [];
        for (var user in data) {
          updatedUsers.add(User(user, 0));
        }
        setState(() {
          _users = updatedUsers;
          _numOfQuestionsInGame = response.getData()["questionCount"];
          _questionTimeout = response.getData()["answerTimeout"];
          _hasGameBegun = response.getData()["hasGameBegun"];
        });
        
      } else if(response.getCode() == 20) {
        await _socketService.receiveMessage();
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
    _timer = Timer.periodic(const Duration(seconds: 3), (timer) {
      /*
      setState(() {
        getUsersInRoom();
      });
      */
      getUsersInRoom();
    });
  }

  @override
  void initState() {
    super.initState();
    /*
    setState(() {
      _startTimer();
    });
    */
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
            padding: const EdgeInsets.only(right: 20.0),
            child: IconButton(
              icon: const Icon(
                Icons.logout,
                color: Colors.black,
                size: 26.0,
              ),
              onPressed: () async {
                bool error = false;
                if (_admin) {
                  _socketService.sendMessage(Message(17, {}));
                  final response = await _socketService.receiveMessage();
                  if(response.getCode() != 16)
                  {
                    error = true;
                  }
                  print("code:");
                  print(response.getCode());
                }
                else
                {
                  _socketService.sendMessage(Message(20, {}));
                  final Message response = await _socketService.receiveMessage();
                  if(response.getCode() != 19)
                  {
                    error = true;
                  }
                  print("code:");
                  print(response.getCode());
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
              },
            ),
          ),
        ],
      ),
      body: Container(
        color: Colors.lightBlue,
        child: Column(
          children: [
            Container(
              height: MediaQuery.of(context).size.height * 0.25,
              width: MediaQuery.of(context).size.width,
              color: Color.fromARGB(255, 111, 156, 235),
              padding: const EdgeInsets.all(16.0),
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
                      style: const TextStyle(fontSize: 22, fontWeight: FontWeight.bold, color: Colors.black),
                    ),
                  ),
                ],
              ),
            ),
            Expanded(
              child: Container(
                width: MediaQuery.of(context).size.width,
                color: Color.fromARGB(255, 29, 45, 68),
                padding: const EdgeInsets.all(16.0),
                child: Column(
                  children: [
                    SingleChildScrollView(
                      child: Wrap(
                        spacing: 16.0,
                        runSpacing: 16.0,
                        children: _users.map((user) => Text(user.getUsername(), style: TextStyle(color: Colors.white))).toList(),
                      ),
                    ),
                    if (_admin)
                      Expanded(
                        child: Align(
                          alignment: Alignment.bottomCenter,
                          child: Container(
                            //color: Color.fromARGB(255, 43, 68, 103),
                            padding: const EdgeInsets.all(16.0),
                            decoration: BoxDecoration(
                              color: Color.fromARGB(255, 43, 68, 103),
                              borderRadius: BorderRadius.circular(32.0),
                            ),
                            child: ElevatedButton(
                              style: ElevatedButton.styleFrom(
                                //foregroundColor:Color(0xFF000000),
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
                              onPressed: () async{
                                _socketService.sendMessage(Message(18, {}));
                                final Message response = await _socketService.receiveMessage();
                                if (response.getCode() == 17) {
                                  Navigator.pushReplacement(
                                    context,
                                    MaterialPageRoute(
                                      builder: (_) => GamePage(
                                        socketService: widget.socketService,
                                        admin: _admin,
                                        roomId: _roomId,
                                        questionTimeout: _questionTimeout,
                                        numOfQuestionsInGame: _numOfQuestionsInGame,
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
            ),
          ],
        ),
      ),
    );
  }
}
