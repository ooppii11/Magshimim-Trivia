import 'package:trivia/SocketService.dart';
import 'package:trivia/user.dart';
import 'package:flutter/material.dart';
import 'package:trivia/Pages/loginPage.dart';
import 'package:trivia/Pages/UserPage.dart';
import 'package:trivia/Pages/HomePage.dart';
import 'dart:async';
import 'package:trivia/message.dart';

class LeaderBoardPage extends StatefulWidget {
  final SocketService socketService;

  const LeaderBoardPage({super.key, required this.socketService});

  @override
  _LeaderBoardPage createState() => _LeaderBoardPage(socketService);
}

class _LeaderBoardPage extends State<LeaderBoardPage> {
  late List<User> _leaderboardScores;
  late Timer _timer;
  final SocketService _socketService;
  _LeaderBoardPage(this._socketService)
  {
    getUsersStatistic();
  }

  void getUsersStatistic() async{
    _socketService.sendMessage(Message(2/*TODO: update to the right code*/, {}));
    final receivedMessage = await _socketService.receiveMessage();
    if (receivedMessage.getCode() == 4/*TODO: update to the right code*/) {
      _leaderboardScores = receivedMessage.getData()["users"];
      /*
      setState(() {
        _leaderboardScores = receivedMessage.getData()["users"];
      });
      */
    }
  }

   void _startTimer() {
    _timer = Timer.periodic(Duration(seconds: 60), (timer) {
      setState(() {
        getUsersStatistic();
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
                    onPressed: () {
                      Navigator.pushReplacement(
                          context,
                          MaterialPageRoute(
                              builder: (_) => LoginPage(
                                    socketService: widget.socketService,
                                  )));
                    }),
              ),
            ]),
        body: SingleChildScrollView(
            child: Center(
                child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
              const Text("Leadrboard"),
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
            ]))));
  }
}
