import 'package:trivia/SocketService.dart';
import 'package:trivia/components/loadingToast.dart';
import 'package:trivia/user.dart';
import 'package:flutter/material.dart';
import 'package:trivia/Pages/loginPage.dart';
import 'package:trivia/Pages/UserPage.dart';
import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/Pages/roomPage.dart';
import 'dart:async';
import 'package:trivia/message.dart';
import 'package:trivia/components/erroToast.dart';

class LeaderBoardPage extends StatefulWidget {
  final SocketService socketService;

  const LeaderBoardPage({super.key, required this.socketService});

  @override
  _LeaderBoardPage createState() => _LeaderBoardPage(socketService);
}

class _LeaderBoardPage extends State<LeaderBoardPage> {
  late List<User> _leaderboardScores;
  late Timer? _timer;
  final SocketService _socketService;
  bool _isFloatingScreenOpen = false;
  String _enteredValue = '';
  _LeaderBoardPage(this._socketService) {
    getUsersStatistic();
  }

  void getUsersStatistic() async {
    _leaderboardScores = [];
    _socketService.sendMessage(Message(6, {}));
    final receivedMessage = await _socketService.receiveMessage();

    if (receivedMessage.getCode() == 5) {
      Map<String, dynamic> UsersScoreMap =
          receivedMessage.getData()["HighScores"];
      for (String key in UsersScoreMap.keys) {
        _leaderboardScores.add(User(key, UsersScoreMap[key]));
        setState(() {
          _leaderboardScores;
        });
        await Future.delayed(const Duration(milliseconds: 500));
      }
    }
  }

  void _startTimer() {
    _timer = Timer.periodic(const Duration(seconds: 60), (timer) {
      //throw toast that says "updating leaderboard"
      getUsersStatistic();
      loadingToast(context, 2);
    });
  }

  @override
  void initState() {
    super.initState();
    _startTimer();
  }

  @override
  void dispose() {
    _timer?.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      bottomNavigationBar: BottomNavigationBar(
          type: BottomNavigationBarType.fixed,
          items: [
            BottomNavigationBarItem(
                icon: Icon(Icons.person, color: Colors.grey[600]), label: ''),
            const BottomNavigationBarItem(icon: Icon(Icons.add_box), label: ''),
            const BottomNavigationBarItem(
                icon: Icon(
                  Icons.leaderboard_rounded,
                  color: Colors.blue,
                ),
                label: ''),
            const BottomNavigationBarItem(
                icon: Icon(
                  Icons.home,
                ),
                label: ''),
          ],
          onTap: (value) {
            if (value == 0) {
              Navigator.pushReplacement(
                context,
                MaterialPageRoute(
                  builder: (_) => UserPage(
                    socketService: widget.socketService,
                  ),
                ),
              );
            }
            if (value == 1) {
              _openPopUp();
            }
            if (value == 3) {
              Navigator.pushReplacement(
                context,
                MaterialPageRoute(
                  builder: (_) => HomePage(
                    socketService: widget.socketService,
                  ),
                ),
              );
            }
          }),
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
                    _socketService.sendMessage(Message(3, {}));
                    final Message response =
                        await _socketService.receiveMessage();
                    if (response.getCode() == 2) {
                      Navigator.pushReplacement(
                          context,
                          MaterialPageRoute(
                              builder: (_) => LoginPage(
                                    socketService: widget.socketService,
                                  )));
                    }
                  }),
            ),
          ]),
      body: Container(
            decoration: BoxDecoration(
            gradient: LinearGradient(
            //colors: [Color(0xff1542bf), Color(0xff51a8ff)],
            colors: [Color.fromARGB(255, 194, 199, 204), Color.fromARGB(255, 62, 69, 78)],
            begin: FractionalOffset(0.5, 1)
            ) // LinearGradient
            ), // BoxDecoration
          child: Stack(children: [
        SingleChildScrollView(
            child: Center(
                child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
              const Text("Leaderboard"),
              const SizedBox(height: 20),
              Container(
                  decoration: BoxDecoration(
                      borderRadius: BorderRadius.circular(20),
                      border: Border.all(
                        color: Colors.black,
                        width: 5,
                      ),
                      gradient: LinearGradient(colors: [
                        Colors.yellow.shade600,
                        Colors.orange,
                        Colors.red
                      ])),
                  height: 575,
                  width: 325,
                  child: SingleChildScrollView(
                      child: DefaultTextStyle(
                    style: const TextStyle(color: Colors.white),
                    child: DataTable(
                        dataTextStyle: const TextStyle(color: Colors.white),
                        columns: const [
                          DataColumn(
                            label: Text('Rank'),
                          ),
                          DataColumn(
                            label: Text('Name'),
                          ),
                          DataColumn(
                            label: Text('Score'),
                          ),
                        ],
                        rows: List.generate(_leaderboardScores.length, (index) {
                          final leaderboard = _leaderboardScores[index];
                          return DataRow(
                            cells: [
                              DataCell(Text('${index + 1}',
                                  style: TextStyle(
                                      color: leaderboard.getUsername() == 'You'
                                          ? Colors.grey[600]
                                          : Colors.black))),
                              DataCell(
                                Text(
                                  leaderboard.getUsername(),
                                  style: TextStyle(
                                      color: leaderboard.getUsername() == 'You'
                                          ? Colors.grey[600]
                                          : Colors.black),
                                ),
                              ),
                              DataCell(Text(leaderboard.getScore().toString(),
                                  style: TextStyle(
                                      color: leaderboard.getUsername() == 'You'
                                          ? Colors.grey[600]
                                          : Colors.black))),
                            ],
                          );
                        })),
                  )))
            ]))),
        if (_isFloatingScreenOpen) _buildFloatingScreen(),
      ]),
      ),
    );
  }

  void _openPopUp() {
    setState(() {
      _isFloatingScreenOpen = true;
    });
  }

  Widget _buildFloatingScreen() {
    return Stack(
      fit: StackFit.expand,
      children: [
        Positioned.fill(
          child: GestureDetector(
            onTap: () {
              setState(() {
                _isFloatingScreenOpen = false;
              });
            },
            child: Container(color: Colors.transparent),
          ),
        ),
        Align(
          alignment: Alignment.bottomCenter,
          child: Container(
            height: 60,
            color: Colors.grey[200],
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                InkWell(
                  onTap: () {
                    showDialog(
                      context: context,
                      builder: (BuildContext context) {
                        return AlertDialog(
                          title: const Text('Join'),
                          content: Column(
                            mainAxisSize: MainAxisSize.min,
                            children: [
                              TextField(
                                onChanged: (value) {
                                  _enteredValue = value;
                                },
                                keyboardType: TextInputType.number,
                                decoration: const InputDecoration(
                                  hintText: 'Enter Room ID',
                                ),
                              ),
                              const SizedBox(height: 10),
                              ElevatedButton(
                                child: const Text('Join'),
                                onPressed: () {
                                  Navigator.of(context).pop();
                                  joinRoom();
                                },
                              ),
                            ],
                          ),
                        );
                      },
                    );
                    setState(() {
                      _isFloatingScreenOpen = false;
                    });
                  },
                  child: const Icon(Icons.people),
                ),
                InkWell(
                  onTap: () {
                    // Handle Create icon press
                    setState(() {
                      _isFloatingScreenOpen = false;
                    });
                  },
                  child: const Icon(Icons.create),
                )
              ],
            ),
          ),
        ),
      ],
    );
  }

  void joinRoom() async {
    _socketService
        .sendMessage(Message(11, {"roomId": int.parse(_enteredValue)}));
    final Message response = await _socketService.receiveMessage();
    if (response.getCode() == 10) {
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(
          builder: (_) => RoomPage(
            socketService: _socketService,
            admin: false,
            roomId: int.parse(_enteredValue),
          ),
        ),
      );
    } else {
      errorToast(context, response.getData()["Error"], 2);
    }
  }
}
